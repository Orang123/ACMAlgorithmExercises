#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2100
#define MOD 1000000007
using namespace std;
typedef long long ll;

/*
题意:给出一棵n个节点的树,问有多少个连通子集满足,最大值减最小值
小于等于d.
链接:https://codeforces.ml/problemset/problem/486/D
思路:dp[u]代表以u为根节点的连通子集的个数
可以枚举每个点作为连通子集中最大的点,访问每个和它连通且比根节点值
小的节点不断加入连通子集,根据乘法原理 连通子集的个数就为dp[u]+dp[u]*dp[v]
代表u本身的连通子集个数加上u的各个连通子集分别于v的各个连通子集组合成的新的
连通字集的个数.不过当u v两点权值相等时会重复计算,所以计算时要标明u v节点编号关系,
必须节点编号递增方向.
*/

int n,d,head[N],cnt,a[N];
ll ans,dp[N];//用ll避免溢出
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int rt){
    dp[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if((a[v]<a[rt] && a[rt]-a[v]<=d) || (a[v] == a[rt] && rt<v) ){
            dfs(v,u,rt);
            /*
            表示u本身的连通子集个数加上u的各个连通子集分别于v的各个连通子集组合成的新的
            连通字集的个数.不过当u v两点权值相等时会重复计算,所以计算时要标明u v节点编号关系,
            必须节点编号递增方向.
            */
            dp[u]=(dp[u]+dp[u]*dp[v])%MOD;
        }
    }
}

int main() {
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&d,&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        dfs(i,-1,i);
        ans=(ans+dp[i])%MOD;
    }
    printf("%lld",ans);
    return 0;
}
