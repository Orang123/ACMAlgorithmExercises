#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define N 100010
using namespace std;

/*
题意:给出一棵树n个节点,给出m个点,在所有的点中(包括在m个点)确认哪些点距离这m个点的距离都不大于d
链接:https://codeforces.ml/contest/337/problem/D
思路:换根dp
可以参考HDU 2196这题的换根dp,求取每个点离这m个点最远的距离
dp[u][0]代表u距子树中这m个点的正向最大距离.
dp[u][1]代表u距子树中这m个点的正向次大距离
dp[u][2]代表u距其走过的父节点向上路径里这m个点的反向最大距离
dp[u][0],dp[u][1]这里正向次大距离和正向最大距离一定是在u节点
输入时需要将dp初始化为负无穷,然后将m个点的dp[u][0] dp[u][1]正向最大/次大距离初始化为0,
这样dfs1中每个点求出的才是距离m个点中的最大距离
*/

int cnt,n,m,d,dp[N][3],head[N];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        //对于u属于m个点,v不属于时,dp[u][0]本身0大于负无穷不会更新 dp[u][1]同理,回溯时会更新父节点距离这m个点中点的距离
        if(dp[u][0]<dp[v][0]+1){
            dp[u][1]=dp[u][0];
            dp[u][0]=dp[v][0]+1;
        }
        else if(dp[u][1]<dp[v][0]+1)
            dp[u][1]=dp[v][0]+1;
    }
}

void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        /*
        dp[v][2]无需初始化,若u和u前面的节点不属于m,dp[v][2]这里更新的是负无穷,
        若u属于m,若本身只有一个分支路径,这时dp[u][1]是0,可更新反向距离m的最大路径.
        dp[v][2]是通过dp[u][0] dp[u][1]  去转移的,即使u是m中的点,第一个0也是通过dp[u][1](0)转移
        */
        if(dp[u][0] == dp[v][0]+1) dp[v][2]=max(dp[u][2],dp[u][1])+1;
        else dp[v][2]=max(dp[u][2],dp[u][0])+1;
        dfs2(v,u);
    }
}

int main(){
    int u,v,ans=0;
    memset(dp,-INF,sizeof(dp));
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&d);
    while(m--){
        scanf("%d",&v);
        dp[v][0]=dp[v][1]=0;
    }
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs1(1,-1);
    dfs2(1,-1);
    for(int i=1;i<=n;i++)
        ans+=max(dp[i][0],dp[i][2])<=d?1:0;
    printf("%d\n",ans);
    return 0;
}

