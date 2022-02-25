#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

/*
题意:一颗树n个点,n-1条边,经过每条边都要花费一定的时间,任意两个点都是联通的.
有K个人(分布在K个不同的点)要集中到一个点举行聚会.
聚会结束后需要一辆车从举行聚会的这点出发,把这 K 个人分别送回去.
请你回答,对于 i=1∼n,如果在第i个点举行聚会,司机最少需要多少时间把K个人都送回家.
链接:https://www.luogu.com.cn/problem/P6419
思路:换根dp
dp1[u]代表u节点到达k个点的路径权值和
dp2[u][0/1/2]分别代表u节点距离k个点距离的正向最大值/次大值和反向最大值
*/

int n,k,head[N],cnt,son[N];
ll dp1[N],dp2[N][3];
struct Node{
    int to,next;
    ll w;
}edge[N<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        son[u]+=son[v];//计算u节点的子树中包含k个人中的要回家的节点
        if(!son[v]) continue;//若果v及其子树中没有这k个节点则不必dp计算距离
        dp1[u]+=dp1[v]+edge[i].w;//计算u点距离这k个点的路径权值和
        if(dp2[u][0]<dp2[v][0]+edge[i].w){
            dp2[u][1]=dp2[u][0];
            dp2[u][0]=dp2[v][0]+edge[i].w;
        }
        else if(dp2[u][1]<dp2[v][0]+edge[i].w)
            dp2[u][1]=dp2[v][0]+edge[i].w;
    }
}

void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!son[v])//当v及其v的子树中没有标记的k个节点时,dp1[v]需要在父亲dp1[u]的基础上在加上u->v这条边的权值
            dp1[v]=dp1[u]+edge[i].w;
        else if(son[v]<k)//当v的子树中的包含的标记节点个数小于k时,v点距k个点的权值和等于父亲u点距离k个点的权值和.
            dp1[v]=dp1[u];
        if(dp2[u][0] == dp2[v][0]+edge[i].w)//更新v节点向上反向距离k个节点的最大距离
            dp2[v][2]=max(dp2[u][2],dp2[u][1])+edge[i].w;
        else
            dp2[v][2]=max(dp2[u][2],dp2[u][0])+edge[i].w;
        dfs2(v,u);
    }
}

int main() {
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    memset(dp2,-INF,sizeof(dp2));//方便区分,只计算别的点距离k个点的距离
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    for(int i=1;i<=k;i++){
        scanf("%d",&u);
        son[u]=1;//标记k个点是需要计算距离
        dp2[u][0]=dp2[u][1]=0;//将k个点初始距离设置为0
    }
    dfs1(1,-1);
    dfs2(1,-1);
    /*
    司机送这k个人回家,一定是1个1个地送,即送完1人后再原路返回寻找另一条路径送另外一个人回家,
    直到最后一个人送回家,这个过程中,从聚会点i到最后一个人回家的路径只走了一遍,其它人回家的路径
    一来一回走了2遍,所以最小的时间花费应该是将k个人中距离聚会点i的路径只走一遍,也就是最后再送最长
    的路径距离的人回家,这样最长的路径就只走了一遍,每个点i作为聚会点送k个人回家的时间开销就是
    dp1[i]*2-max(dp2[i][0],dp2[i][2]),max(dp2[i][0],dp2[i][2])距离k个人的正向/反向距离取最大值
    */
    for(int i=1;i<=n;i++)
        printf("%lld\n",dp1[i]*2-max(dp2[i][0],dp2[i][2]));
    return 0;
}
