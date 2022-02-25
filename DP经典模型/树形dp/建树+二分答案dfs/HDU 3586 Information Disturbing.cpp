#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define INF 1<<20//最大值不能去太大,否则dp[u]累加时可能会溢出,或者dp数组采用ll也可以避免溢出
using namespace std;

/*
题意:一棵树需要切断一些边使得初始根节点(编号为1)与叶子节点不连通,并且对于切割的边权值有一个最大的限制,
并且切割的所有边权和不能超过m的预算,现在要求这个最大的限制最少是多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3586
思路:首先这个最大限制不确定,其次如果从极大值开始线性验证,那么也会超时,所以考虑二分最大限制.
二分最大限制,dfs验证是否可以分离根节点与所有叶子节点,若能分离,则二分右边界更小的,若不能分离则二分左边界更大点
dp[u]代表分离u与其子树中的叶子节点最少要切割的边权和
*/

int cnt,n,m,head[N],dp[N],ans;
struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa,int maxw){
    dp[u]=0;
    int flag=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        flag=1;
        dfs(v,u,maxw);
        //若u->v边权和小于最大限制,则比较u->v当前边权与v子树中的边权取较小边权
        if(edge[i].w<=maxw)
            dp[u]+=min(edge[i].w,dp[v]);
        else//否则就选v的子树中较小的边权
            dp[u]+=dp[v];
    }
    //对于叶子节点设置INF,如果回溯到根节点没有一个父节点与子节点之间的边权比最大限制小,则说明无法分割根节点与叶子节点连通
    if(!flag)
        dp[u]=INF;
}

int judge(int maxw){
    dfs(1,-1,maxw);
    if(dp[1]<=m) return 1;
    else return 0;
}

int main(){
    int u,v,w,l,r;
    while(scanf("%d%d",&n,&m) && n && m){
        ans=-1;
        r=cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            r=max(r,w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        if(!judge(m)){
            printf("-1\n");
            continue;
        }
        l=1;
        //对最大限制进行二分,求解最小值
        while(l<r){
            int mid=(l+r)/2;
            if(judge(mid)) r=mid;//若最终权值和小于m预算 尝试将最大限制再分小点
            //若最终限制含有INF,则说明上一次最大限制太小,导致某条路径没有一条边权小于这个最大限制,所以要将最大限制调大点
            else l=mid+1;
        }
        printf("%d\n",l);
    }
    return 0;
}
