#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 3100
#define M 8500
#define INF 0x3f3f3f3f
using namespace std;
//���P1262 �������
//ac 61ms tarjan����+������
//����ڶ����ų����ܻ�¸�����������һЩ
//ͬFZU 1719 Spy Network ����FZU�Ĳ��������е�����
/*
����:n�����֮����m����ϵ,a->b,������a������b������֤��,��������,
���a->b,b->c,c->d,��ôֻ��Ҫ���ռ��a��֤��,����ͬʱ����b��c��d��
֤��,������p����������ջ�¸,ÿ������Ļ�¸Ǯ��ͬ,���������Ҫ����
���м����֤��,������Ҫ����Ǯ,����������ռ��������֤��,�����
�����ƿ�֤�ݵļ������С���.
����:https://www.luogu.com.cn/problem/P1262 or http://acm.fzu.edu.cn/problem.php?pid=1719
˼·:����tarjan���scc�����scc�пɻ�¸����С����,���㹹��DAG,
��DAG�����������,����ǰ���ӵĽڵ�scc�����е㶼���ܽ��ܻ�¸ʱ,
��ô���scc�����е��֤�ݶ��ǲ������յĲ��ҽ����ӵ���ȼ�1,������ӵ����Ϊ0��,�����,
���scc���е��ܽ��ܻ�¸,��ô�ͼ������scc����С����,�����ӵ㲢�������,���Һ���·��Ҳ
�����ٹ���,������Ϊ�����Զ����Ϊ0,Ҳ�������.��������������С���Ѻ����в�������֤��
�ļ��.
*/
int n,m,p,dfn[N],low[N],id,clk,cnt,block[N],head[N],cost[N],inde[N],ans;
stack<int> s;

struct SCC{
    int id,cost;
    SCC(int id=0,int cost=0):id(id),cost(cost){}
    bool operator < (const SCC &x)const{
        return cost<x.cost;
    }
};
vector<SCC> scc[N];
vector <int> G[N],seq;//seq�ǲ�������֤�ݵļ�����


struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clk;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            scc[id].push_back(SCC(v,cost[v]));
            block[v]=id;
        }while(v!=u);
        sort(scc[id].begin(),scc[id].end());//���ջ��Ѵ�С�������� �����ջ�¸�ļ���������INF
    }
}

void topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i])
            Q.push(i);
    }
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        if(scc[u].front().cost == INF){//�����С���� �����ջ�¸ �����SCC��ȫ�����ջ�¸ ����seq
            for(SCC &tmp : scc[u])
                seq.push_back(tmp.id);
        }
        else{
            ans+=scc[u].front().cost;
            continue;//u���֤���Ѿ�����,��ôu֮���֤����Ȼ��ȫ������,�Ͳ��ؼ��������.
        }
        for(int &v : G[u]){
            //���u�㲻���ƿ�֤��,���迼��v��
            //��������Ƿ�Ϊ0�����Ƿ����,������Ϊ0��,˵��ǰ��Ľڵ�û��һ��֤���������յ�,
            //����Ȼv���֤�ݾ�ֻ�ܿ���v�еļ���Ƿ����ջ�¸����������
            if(!--inde[v])
                Q.push(v);
        }
    }
}

void init(){
    ans=id=clk=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(cost,0x3f,sizeof(cost));
    memset(inde,0,sizeof(inde));
    memset(dfn,0,sizeof(dfn));
    seq.clear();
    for(int i=1;i<=n;i++){
        G[i].clear();
        scc[i].clear();
    }
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    scanf("%d",&p);
    while(p--){
        scanf("%d%d",&u,&v);
        cost[u]=v;
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            inde[block[v]]++;
            G[block[u]].push_back(block[v]);
        }
    }
    topSort();
    if(!seq.size()){
        printf("YES\n");
        printf("%d\n",ans);
    }
    else{
        sort(seq.begin(),seq.end());
        printf("NO\n");
        printf("%d\n",seq.front());
    }
    return 0;
}

/*
//���P1262 �������
//ac 54ms tarjan�ų����ܻ�¸������scc�������Ϊ0�����С����
//�������Danny_boodman����
//2�����:
//һ���е��ﷸ�Ȳ��ܻ�¸��Ҳû���ﷸ�ܽҷ���,��ô�����޽�,�����ڱ���ʱ���ϱ��,
//Ȼ���С����ö��,ֻҪ����û�б�ǵľ����Ȼ���˳�����.
//�������е��ﷸ����ֱ�ӻ��ӵر��ܻ�¸���ﷸ�ҷ�.������,Ҳ���������,һ��û�л�,
//��ô�ʽ���ǻ�¸�Ǹ�û����ȵ��ﷸ,�����л�,��ô�ʽ�����Ǹ������ﷸ�����ʽ���С��.
//������,������ǰѻ�����ﷸ����һ����,��ôȫ����ǰ�ߵ������.

//�����������һ��ʼ��ʱ��tarjan�Ͳ������ܻ�¸�ļ��,ֻ���ܽ��ܻ�¸�ļ����ʼtarjan����,
//��������ĵ�û�ܱ�������Щ���ܽ��ܻ�¸�ļ��,��ô�����ܻ�¸�ҵļ����֤����Ȼ���޷�����,Ҳ����dfn[i] == 0.
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 3100
#define M 8500
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p,dfn[N],low[N],id,clk,cnt,block[N],head[N],cost[N],min_cost[N],inde[N],ans;
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clk;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            min_cost[id]=min(min_cost[id],cost[v]);
            block[v]=id;
        }while(v!=u);
    }
}

void init(){
    ans=id=clk=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(cost,0x3f,sizeof(cost));
    memset(min_cost,0x3f,sizeof(min_cost));
    memset(inde,0,sizeof(inde));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    init();
    scanf("%d",&n);
    scanf("%d",&p);
    while(p--){
        scanf("%d%d",&u,&v);
        cost[u]=v;
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i] && cost[i]!=INF)//ֻ���ܽ��ܻ�¸�ļ����ʼ����
            dfs(i);
    }
    for(int i=1;i<=n;i++){//����ı���������
        //��������ĸ���û�б�tarjan������,˵��������ܻ�¸�ļ����֤��Ҳû�б������������,��Ȼ��֤�ݲ�������
        if(!dfn[i]){
            printf("NO\n");
            printf("%d\n",i);
            return 0;
        }
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v])
            inde[block[v]]++;
    }
    //���ձ�������scc�����һ�����������յ�֤�ݵļ��,��ôֻ��������Ϊ0�ĵ�scc����Ҫ������С�ļ������
    for(int i=1;i<=id;i++){
        if(!inde[i])
            ans+=min_cost[i];
    }
    printf("YES\n");
    printf("%d\n",ans);
    return 0;
}
*/

/*
//FZU 1719 Spy Network http://acm.fzu.edu.cn/problem.php?pid=1719
//ac 78ms tarjan����+������
//���� FZU 1719 �ų����ܻ�¸�����tarjan���ּ�������wa ����.
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 3100
#define M 8500
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p,dfn[N],low[N],id,clk,cnt,block[N],head[N],cost[N],inde[N],ans;
stack<int> s;

struct SCC{
    int id,cost;
    SCC(int id=0,int cost=0):id(id),cost(cost){}
    bool operator < (const SCC &x)const{
        return cost<x.cost;
    }
};
vector<SCC> scc[N];
vector <int> G[N],seq;//seq�ǲ�������֤�ݵļ�����


struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clk;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            scc[id].push_back(SCC(v,cost[v]));
            block[v]=id;
        }while(v!=u);
        sort(scc[id].begin(),scc[id].end());//���ջ��Ѵ�С�������� �����ջ�¸�ļ���������INF
    }
}

void topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i])
            Q.push(i);
    }
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        if(scc[u].front().cost == INF){//�����С���� �����ջ�¸ �����SCC��ȫ�����ջ�¸ ����seq
            for(int i=0;i<scc[u].size();i++)
                seq.push_back(scc[u][i].id);
        }
        else{
            ans+=scc[u].front().cost;
            continue;//u���֤���Ѿ�����,��ôu֮���֤����Ȼ��ȫ������,�Ͳ��ؼ��������.
        }
        for(int i=0;i<G[u].size();i++){
            int v=G[u][i];
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        ans=id=clk=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(cost,0x3f,sizeof(cost));
        memset(inde,0,sizeof(inde));
        memset(dfn,0,sizeof(dfn));
        seq.clear();
        for(int i=1;i<=n;i++){
            G[i].clear();
            scc[i].clear();
        }
        scanf("%d",&p);
        while(p--){
            scanf("%d%d",&u,&v);
            cost[u]=v;
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                inde[block[v]]++;
                G[block[u]].push_back(block[v]);
            }
        }
        topSort();
        if(!seq.size()){
            printf("YES\n");
            printf("%d\n",ans);
        }
        else{
            sort(seq.begin(),seq.end());
            printf("NO\n");
            printf("%d\n",seq.front());
        }
    }
    return 0;
}
*/
