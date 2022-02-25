#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
typedef long long ll;

/*
题意:给定一棵n个点的树，问其中有多少条长度为偶数的路径。路径的长度为经过的边的条数。
x到y与y到x被视为同一条路径。路径的起点与终点不能相同。
Wannafly挑战赛1链接:https://ac.nowcoder.com/acm/contest/15#question
链接:https://ac.nowcoder.com/acm/contest/15/A
思路:
dp[u][0]代表从u节点出发和子树节点构成偶数长度路径的个数
dp[u][1]代表从u节点出发和子树节点构成奇数长度路径的个数
*/

ll dp[N][2],head[N],cnt,n,ans;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}


void dfs(int u,int fa){
    /*
    至于最先开始 的叶子节点dp[u][0]=1,是为了 让它的父节点的dp[u][1]=1,
    这个父节点将棵子树连接时,根节点各自到2棵子树根节点长度为1的这两端构成长度为2的偶数路径的计算dp[u][1]*dp[to][0]这一条。
    对于其余节点dp[u][0]=1,代表的是u->v这条边的长度为1可以和v节点的子树中的技术长度路径组成1条偶数长度路径 即:奇数+1=偶数.
    */
    dp[u][0]=1;
    dp[u][1]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        /*
        dp[u][0]*dp[v][1]代表从u节点已经遍历过的子树中长度为偶数的路径个数和当前子树v中长度为奇数的个数连接而成的长度为偶数的个数,
        因为u->v是长度为1的路径,即偶数+(1+奇数)=偶数+偶数=偶数,此外一开始遍历第一个子树v时,
        dp[u][0]=1,dp[u][0]*dp[v][1]代表 u-v和v中经过v长度为奇数的路径组合成长度为偶数的路径.
        ans累加会将之前遍历过的每棵子树都和当前子树v乘法原理计算一次.
        dp[u][1]*dp[v][0]这里同理,第一次情况是,u结点的两颗子树u->v1 u->V2两个长度为1的边 v1->u->v2组成的长度为2的偶数路径
        */
        ans+=dp[u][0]*dp[v][1];
        ans+=dp[u][1]*dp[v][0];
        dp[u][0]+=dp[v][1];//偶数长度路径由子树的奇数路径加上u->v(1)这条边转移而来
        dp[u][1]+=dp[v][0];//奇数长度路径由子树的偶数路径加上u->v(1)这条边转移而来
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    printf("%lld",ans);
    return 0;
}
