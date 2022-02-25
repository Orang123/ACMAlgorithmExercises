#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 1100
#define M 6500
using namespace std;
//ac 344ms tarjan����+��������
//�������㹹��DAG+��С·������ �������
/*
����:һ������ͼ,�Ƿ������������u,v������u��v��v��u��һ��·��.
����:http://poj.org/problem?id=2762
˼·:ע���Ǵ�����������u��v��v��u��·��,��������һ�����򼴿�,
��ô������tarjan+���㹹��DAG,ֻҪ����DAG��һ�����������Ϊ0�ĵ��
�����ͳ���Ϊ0�ĵ��������ֻ��һ��,�����Ϊ0��2��,���������Ϊ0�Ļ����ɴ�,����ͬ��,
����Ҫ�ǵ��������з�֧,����з�֧2����֧�ϵĵ���ǻ����ɴ��.�ж�
��֧���������������жϵ�ǰ�����еĵ�ĸ����Ƿ����1��ʵ�ֻ���Ҳ���Բ�ȡdfs�ж�
���׽ڵ�ķ�֧����,������1ʱ��˵���з�֧.

��չ:�����Ŀ�ʵ���u->v��v->u˫��ɴ��·��,��ôֻ���ж�ԭͼ�Ƿ�ΪSCG(ǿ��ͨͼ),
scc����Ϊ1����.
*/

int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id,inde[N];
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        //���Բ�����in�ж��Ƿ���ջ��,ֱ����block[v]�Ƿ񱻻��ֵ�scc,����û����������ջ��,����һ����ջ���ֳ�scc,��Ҫÿ�γ�ʼ��blockΪ0
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

int topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i])
            Q.push(i);
    }
    int u,v;
    while(!Q.empty()){
        if(Q.size()>1) return 0;//���>1 ˵���з�֧
        u=Q.front();
        Q.pop();
        for(int i=0;i<G[u].size();i++){//POJ ��֧��C++11��д��
            v=G[u][i];
            if(!--inde[v])
                Q.push(v);
        }
    }
    //�������DAG,�����ڱպϻ�·,�����жϵ�ĸ����Ƿ�ﵽ��scc�ĸ���. �����в��ִ��� �����ж�
    return 1;
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        clock=id=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(block,0,sizeof(block));
        memset(inde,0,sizeof(inde));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            G[i].clear();
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
        if(topSort()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

/*
//ac 344ms
//tarjan����+dfs����DAG��ÿһ��ķ�֧����,������1��˵����֧�ϵ����㻥���ɴ�.
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 1100
#define M 6500
using namespace std;

int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id,inde[N],vis[N];
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
        if(!dfn[v]){
            tarjan(v);
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
            block[v]=id;
        }while(v!=u);
    }
}

//����� u�� ����ΪDAG��û�бպϻ�·,��Զ�����з����
int dfs(int u){
    int son=0;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!vis[v]){//����Ƿ񱻷���,DAG�ϻ���ǰ���,�������еĽڵ��Ѿ�dfs������ȷ��ʹ�
            vis[v]=1;
            son++;
            if(son>1) return 0;//u�����������1 ˵����·�����з�֧ ����0,ֱ���˳�dfs ��ջ.
            if(!dfs(v)) return 0;
        }
    }
    return 1;//û�з�֧
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        clock=id=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(block,0,sizeof(block));
        memset(vis,0,sizeof(vis));
        memset(inde,0,sizeof(inde));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            G[i].clear();
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                inde[block[v]]++;
                G[block[u]].push_back(block[v]);
            }
        }
        int ans=0;
        for(int i=1;i<=id;i++){
            if(!inde[i]){
                ans++;
                u=i;
            }
        }
        if(ans == 1){//���ж����Ϊ0�� ����� �պ�Ϊ1,��Ӹõ㿪ʼdfs,�������No
            if(dfs(u)) printf("Yes\n");
            else printf("No\n");
        }
        else
            printf("No\n");
    }
    return 0;
}
*/

/*
//ac 344ms tarjan����+DAG����С·������ ��С·������=������-���ƥ��
//��ֻ��һ��ֱ����:��С·��������Ϊ1,�����Yes,�������No
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 1100
#define M 6500
using namespace std;

int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id,vis[N],link[N],ans;
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        //���Բ�����in�ж��Ƿ���ջ��,ֱ����block[v]�Ƿ񱻻��ֵ�scc,����û����������ջ��,����һ����ջ���ֳ�scc,��Ҫÿ�γ�ʼ��blockΪ0
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

int hungary(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || hungary(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=clock=id=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(link,0,sizeof(link));
        memset(block,0,sizeof(block));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            G[i].clear();
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])
                G[block[u]].push_back(block[v]);
        }
        for(int i=1;i<=id;i++){
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        if(id-ans == 1) printf("Yes\n");//��С·������=������-���ƥ��
        else printf("No\n");
    }
    return 0;
}
*/
