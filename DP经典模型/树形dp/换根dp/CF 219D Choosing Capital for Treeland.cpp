#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define N 200010
using namespace std;

/*
题意:一颗n个节点的有向树,需要设置某个节点为首都,为了能够从首都到达所有节点,可能个别边需要反向处理,
现在要求 选取哪些点作为首都可使得反向边数量最少.
链接:https://codeforces.ml/problemset/problem/219/D
思路:在建边的是否对于正向边赋值0,代表不需要改边,对于反向边赋值1,代表要改变,这个问题就转化成了
每个点都其他点的权值之和.最终的权值之和代表需要改变的边数.
dp[i]代表以i为首都,需要改变的边数,第一次dfs1求出节点1作为首都要改变的边数
第二次dfs2()顺次求出u的子节点v作为首都要改变的边数,v只需要在u的基础上改变1条边的走向,
需要在dp[u]的基础上改变u->v的导向,如果u->v本身就是正向边,则dp[v]=dp[u]+1,若u->v是反向边,即v->u是正向边则,dp[v]=dp[u]-1
*/

int cnt,n,dp[N],head[N],ans=INF;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

//计算1节点作为首都要改变的边数 子节点向父节点转移
void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        dp[u]+=dp[v]+edge[i].w;
    }
}

//计算1节点之后的儿子作为首都要改变的边数 父节点向子节点转移
void dfs2(int u,int fa){
    if(dp[u]<ans) ans=dp[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(edge[i].w)//u->v是反向 此时v->u正向 故dp[u]-1
            dp[v]=dp[u]-1;
        else//u->v正向 v->u反向 故dp[u]+1
            dp[v]=dp[u]+1;
        dfs2(v,u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v,0);
        addEdge(v,u,1);
    }
    dfs1(1,-1);
    dfs2(1,-1);
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){
        if(dp[i] == ans)
            printf("%d ",i);
    }
    return 0;
}

