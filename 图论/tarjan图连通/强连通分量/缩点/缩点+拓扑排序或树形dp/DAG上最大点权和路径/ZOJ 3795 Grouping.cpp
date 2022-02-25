#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 100100
#define M 300100
using namespace std;
//ac 80ms tarjan缩点+DAG上拓扑序求解路径上最大点权和
/*
题意:n个人,m条单向年龄大小关系,si->ti代表,si的年龄大于等于ti的年龄,
现在我们需要把这些n个人至少分成几个小组,一个人的年龄不应该直接或间接地
在同一群体中相互比较,也就是说同组内的人年龄大小关系是未知的不可比较的.
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827369801
思路:对于一个循环闭环 s1>=s2>=s3>=s4>=s1,说明一个scc内所有人的年龄都是相等的,
显然同一scc内年龄大小关系一定是已知的,那么对于一个scc内的点每个人必须被分到不同
的组,组的个数就为scc内点的个数,对于这个问题我们可以tarjan缩点构造DAG,只有在DAG
上不同路径分支的点之间大小关系才是未知不能比较的,那么对于一条路径上的点每个点(scc)都应该
分到不同的组,同时每个scc内的点也应在不同的组,而对于不同路径上的点是可以分到同一组的,因为大小未知,
如果其他路径上点权和更大,那么点权和较大的路径肯定有点剩余还需要再单独分组,那么显然至少要分的组
应参照权值和最大的路径,我们要求解的正是不同路径分支上的最大点权和,点权为每个scc内点的个数.

注意:拓扑序和树形dfs的dp代表的含义不同,dp[u]拓扑序代表的是入度代表从入度为0的点到u点路径上的最大点权和,
入度为0的点dp[u]是最小的,路径末端点的dp才是最大的.
树形dp dp[u]代表u的子树分支路径中(包括u点)最大的点权和 只有入度为0的点才是dp[u]才是最大的,叶子节点的dp值是最小的
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
//dp[u]代表从入度为0的点到u点路径上的最大点权和
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
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        ans=id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(dp,0,sizeof(dp));
        memset(cost,0,sizeof(cost));
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
//ac 83ms tarjan缩点+DAG上树形dp
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 100100
#define M 300100
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
    dp[u]=cost[u];//这里是为了避免叶子节点dp[u]没有赋值
    for(int &v : G[u]){
        if(!vis[v])//如果之前以计算出dp 就不再dp
            dfs(v);
        dp[u]=max(dp[u],cost[u]+dp[v]);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        ans=id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(cost,0,sizeof(cost));
        memset(vis,0,sizeof(vis));
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
