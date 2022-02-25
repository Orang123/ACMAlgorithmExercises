#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 1100
#define M 50100
using namespace std;
//ac 50ms tarjan����+������dp����Ȩ������·��
//��ZOJ 3795 ���P3387 ��һ����·,�����Ǹ���POJ 2762�ı��
/*
����:����һ������ͼG,��һ����������Ľ�㼯,ʹ�øý�㼯�е������������u��v����:
Ҫôu���Դ�v,Ҫôv���Դ�u,u��v�໥�ɴ�Ҳ��.
����:https://www.luogu.com.cn/problem/UVA11324
˼·:���ȶ���ͬһscc�ڵĵ���Ϊ�������㻥��ɴ���Ȼ�������.
����ֱ�Ӷ�ԭͼӦ�����������·,�������������޷���������.����������.
��ôtarjan���scc��ͳ��scc�ڵ����,�������DAG,���ȨΪscc�ڵ�ĸ���,
��ô�����ת������DAG�ϵ�Ȩ�����Ŀɴ�·��������,��Ȼ������dp����.

��ȻDAG������dpҲ�ǿ��Ե�.
*/
int n,m,dfn[N],low[N],clock,cnt,block[N],cost[N],dp[N],id,head[N],inde[N],ans;
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
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            cost[id]++;
        }while(v!=u);
    }
}

void topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i]){
            dp[i]=cost[i];
            Q.push(i);
        }
    }
    int u;
    while(!Q.empty()){
        u=Q.front();
        ans=max(ans,dp[u]);
        Q.pop();
        for(int &v : G[u]){
            dp[v]=max(dp[v],dp[u]+cost[v]);
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(dp,0,sizeof(dp));
        memset(cost,0,sizeof(cost));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear();
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
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 50ms DAG������dp
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 1100
#define M 50100
using namespace std;

int n,m,dfn[N],low[N],clock,cnt,block[N],cost[N],dp[N],id,head[N],inde[N],ans,vis[N];
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
            cost[id]++;
        }while(v!=u);
    }
}
//dp[u]����u����·����(����u��)���ĵ�Ȩ��
void dfs(int u){
    vis[u]=1;
    dp[u]=cost[u];
    for(int &v : G[u]){
        if(!vis[v])//���֮ǰ�Լ����dp �Ͳ���dp
            dfs(v);
        dp[u]=max(dp[u],cost[u]+dp[v]);
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(cost,0,sizeof(cost));
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
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
        for(int i=1;i<=id;i++){//DAG���ܱ��ָ�Ϊ������ͨ��
            if(!vis[i]){//��ſ�ǰ�ĵ㲻һ���������Ϊ0�ĵ�
                dfs(i);
                ans=max(ans,dp[i]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
