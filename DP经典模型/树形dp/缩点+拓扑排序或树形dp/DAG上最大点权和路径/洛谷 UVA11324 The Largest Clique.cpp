#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 1100
#define M 50100
using namespace std;
//ac 50ms tarjan缩点+拓扑序dp求解点权和最大的路径
//和ZOJ 3795 洛谷P3387 是一个套路,并且是根据POJ 2762改编的
/*
题意:给你一张有向图G,求一个结点数最大的结点集,使得该结点集中的任意两个结点u和v满足:
要么u可以达v,要么v可以达u,u、v相互可达也行.
链接:https://www.luogu.com.cn/problem/UVA11324
思路:首先对于同一scc内的点因为任意两点互相可达显然满足情况.
不能直接对原图应用拓扑序跑最长路,那样遇到环就无法继续走了.所以先缩点.
那么tarjan求解scc并统计scc内点个数,缩点后建立DAG,另点权为scc内点的个数,
那么问题就转化成了DAG上点权和最大的可达路径的问题,显然拓扑序dp即可.

当然DAG上树形dp也是可以的.
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
//ac 50ms DAG上树形dp
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
//dp[u]代表u的子路径中(包括u点)最大的点权和
void dfs(int u){
    vis[u]=1;
    dp[u]=cost[u];
    for(int &v : G[u]){
        if(!vis[v])//如果之前以计算出dp 就不再dp
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
        for(int i=1;i<=id;i++){//DAG可能被分割为几个连通块
            if(!vis[i]){//编号靠前的点不一定就是入度为0的点
                dfs(i);
                ans=max(ans,dp[i]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
