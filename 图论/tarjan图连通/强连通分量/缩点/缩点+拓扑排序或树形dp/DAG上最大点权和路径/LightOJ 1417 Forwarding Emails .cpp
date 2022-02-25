#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 50100
#define M 50100
using namespace std;
//ac 139ms
/*
题意:要发送一封邮件,尽可能传给更多的人,如果发给a,a能发给b,b能发给c,这样满足传递性,
现在发给谁能发给更多的人.输出这个人的编号,若答案一样输出编号较小的人的编号.
链接:http://lightoj.com/volume_showproblem.php?problem=1417
思路:要传给更多的人,那就应该把邮件发给入度为0的人,再继续传递.
显然tarjan缩点在DAG上跑点权和最大路径.
为什么缩点,因为不缩点如果为了求解出更长路径,直接dfs遇到环程序不能正常结束.

注意:这题只能用树形dp求解最大点权和路径,因为树形dp最大点权和路径恰好在入度为0的点,
而拓扑序最大点权和在路径末端点,最后输出的人的编号是错的.
*/
int n,m,dfn[N],low[N],clock,cnt,block[N],cost[N],dp[N],id,head[N],ans,vis[N];
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
    int T,u,v,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        ans=id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(cost,0,sizeof(cost));
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        m=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&u,&v);
            m=max(m,max(u,v));
            addEdge(u,v);
        }
        for(int i=1;i<=m;i++)
            G[i].clear();
        for(int i=1;i<=m;i++){
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])
                G[block[u]].push_back(block[v]);
        }
        for(int i=1;i<=id;i++){//DAG可能被分割为几个连通块
            if(!vis[i]){//编号靠前的点不一定就是入度为0的点
                dfs(i);
                ans=max(ans,dp[i]);
            }
        }
        for(int i=1;i<=m;i++){
            if(dp[block[i]] == ans){//最大的点 一定是scc入度为0的点
                printf("Case %d: %d\n",cas,i);
                break;
            }
        }
    }
    return 0;
}
