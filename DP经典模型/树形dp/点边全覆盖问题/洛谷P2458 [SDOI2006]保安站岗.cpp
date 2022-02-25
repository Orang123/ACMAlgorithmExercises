#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1600
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:https://www.luogu.com.cn/problem/P2458
链接:https://www.luogu.com.cn/problem/P2458
思路:和洛谷P2899思路一致,只不过对于每个点的选择需要再加上权值.
因为关系到最优值的选取,并不单只是问至少选取多少个点使得保安能看守所有岗位,
因此这个不能用dfs+贪心解法.
*/

int cnt,n,m,head[N],dp[N][3],cost[N];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    int t=INF;
    dp[u][0]=cost[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        dp[u][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
        dp[u][1]+=min(dp[v][0],dp[v][2]);
        dp[u][2]+=min(dp[v][0],dp[v][2]);
        t=min(t,dp[v][0]-min(dp[v][0],dp[v][2]));
    }
    dp[u][2]+=t;
}

int main(){
    int u,v,k;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&u);
        scanf("%d%d",&cost[u],&k);
        while(k--){
            scanf("%d",&v);
            addEdge(u,v);
            addEdge(v,u);
        }
    }
    dfs(1,-1);
    printf("%d",min(dp[1][0],dp[1][2]));
    return 0;
}
