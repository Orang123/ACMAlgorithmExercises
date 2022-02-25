#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 500100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
//ac 912ms tarjan���㹹��DAG+spfa�·
//���spfa����TLE�Ļ�,���Կ���������dp���·������Ȩ��
/*
����:����ͼ,n��·��ÿ��·����������ATM��,m�������·,
ÿ��ATM������ȡ��һ������Ǯ,��p���ưɷֲ���n��·����,
ÿ��·��ֻ��һ���ư�,���Ҳ���ÿ��·�ڶ��оư�,����һ��С͵
Ҫ��s�����,��������ȥ����,����������Ҫ��һ�Ҿư���ף.
ÿ��·�ں͵�·���ɶ�ξ���,��ֻ��ȡһ��Ǯ.
����:https://www.luogu.com.cn/problem/P3627
˼·:tarjan���㹹��DAG,spfa���㵽������ư�����Ȩ��.
*/

int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],vis[N],val[N],cost[N],dis[N],bar[N],sccbar[N];
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            if(bar[v]) sccbar[id]=1;//���v�������оư�,��ô��scc�ھͱ���оư�
            cost[id]+=val[v];
        }while(v!=u);
    }
}

void spfa(int s){
    queue<int> Q;
    vis[s]=1;
    dis[s]=cost[s];
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int &v : G[u]){
            if(dis[v]<dis[u]+cost[v]){
                dis[v]=dis[u]+cost[v];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,ans=0,s,p;//ע��ansҪ��ʼ��Ϊ0,�п���û�оư�,���������ֽ�Ϊ0
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    scanf("%d%d",&s,&p);
    while(p--){
        scanf("%d",&u);
        bar[u]=1;
    }
    tarjan(s);//ֻ���s���ܵ�����SCC����
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(!block[u]) continue;//����ֻ���s���ܵ���ĵ�,���Ա�����s���ܵ���ĵ��SCC
        if(block[u]!=block[v])//����DAG
            G[block[u]].push_back(block[v]);
    }
    spfa(block[s]);
    for(int i=1;i<=id;i++){
        if(sccbar[i])//DAG���յ�����оư�,��û��һ��scc�оư�,��Ĭ�ϳ�ʼֵΪ0
            ans=max(ans,dis[i]);
    }
    printf("%d",ans);
    return 0;
}

/*
//���spfa������ʱ�Ļ�,���Բ���DAG���������������Ȩ��
//ac 943ms tarjan���㹹��s��������ܵ�����scc+�������������Ȩ��·��
//ע��������Ҫ�õ�DAGֻ���Ǵ�s������ɴ��,��Ȼ��Ӱ����.���tarjan������ͼ������DAG,�����ʼ���������Ϊ0�����,
//�ᵼ�¸���������Զ������Ϊ0,������������Ϊ0�ĵ㶼��ӻᵼ�²��Ǵ�s�������·��Ҳ�����ȥ,���½������.
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 500100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],val[N],cost[N],dis[N],bar[N],sccbar[N],inde[N];
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            if(bar[v]) sccbar[id]=1;
            cost[id]+=val[v];
        }while(v!=u);
    }
}

void topSort(int s){
    queue<int> Q;
    //��ǰ������ͼ,s������һ����Ϊ0��,��Ϊֻ��������s��������ĵ��DAG,
    //������ĵ�����ֻ����Դ��s��s�������ĵ�
    dis[s]=cost[s];
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int &v : G[u]){
            dis[v]=max(dis[v],dis[u]+cost[v]);
            //ֻ�е����Ϊ0ʱ,��ʱ�Ϳ��ǵ������д�s��������v���·��,ֻ��¼����dis[v]��Ȩ��,
            //��ʱ����v�����,��ʼ��v���������ʣ�µĵ�
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int u,v,ans=0,s,p;//ע��ansҪ��ʼ��Ϊ0,�п���û�оư�,���������ֽ�Ϊ0
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    scanf("%d%d",&s,&p);
    while(p--){
        scanf("%d",&u);
        bar[u]=1;
    }
    //��Ϊ�Ǵ�s����,����ֻ��Ҫ���s�ܱ�������scc,ʵ����Ϊ����topSortҪ���s����·��������Ȩ��,
    //Ϊ�˱�������s���������ĵ� ��topSortʱӰ��s·���ϵ���ȼ�Ϊ0,Ҳֻ�����s�ܱ�������scc.
    tarjan(s);
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        //u���������,v���ȻҲ�ܱ�����.
        //��u��û������,v��Ҳ�п��ܱ�����,��ʱ����������߹����DAG,
        //��ôtopSortʱblock[v]�������ԶҲ���ܼ�Ϊ0,��Ϊblock[s]��������block[u],����ͻ����
        //���Լӽ�DAG�ı�һ��Ҫ��֤u���Ǵ�s�����ܱ�������
        if(!dfn[u]) continue;//�����ж�!block[u]Ҳ�ǿ��Ե�
        if(block[u]!=block[v]){//����DAG
            G[block[u]].push_back(block[v]);
            inde[block[v]]++;
        }
    }
    topSort(block[s]);//ֱ�Ӵ�block[s]��������
    for(int i=1;i<=id;i++){
        if(sccbar[i])
            ans=max(ans,dis[i]);
    }
    printf("%d",ans);
    return 0;
}
*/
