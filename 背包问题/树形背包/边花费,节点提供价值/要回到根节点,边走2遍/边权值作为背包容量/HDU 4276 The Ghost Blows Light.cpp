/*
题意:n个点的树,每个点有价值val[i],每条边需要花费时间w,初始在1点有时间T,
现在问从1点出发,在最终能到达n点的前提下,一路上能能获得最大价值.
若不能到达n点输出"Human beings die in pursuit of wealth, and birds die in pursuit of food!".
n<=100,T<=500,0<=w<=100.
2012 ACM/ICPC Asia Regional Changchun Online
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4276
思路:和ZOJ 3626 一样,都是在节点获得价值,花费再边权上.
树上分组背包.
dp[i][j]表示从以i点为根节点的子树出发在时间为j下遍历子树节点最多能获得的价值.
因为要求从1点出发最后必须能到达n点,那么1节点到n点的路径上的边实际只会遍历一次,
因为要回到1到n的路径边上,其余子树上的路径边会一来一回走两遍,也有一些子树的边是
没有遍历的,这个在分组背包转移过程中会被更优解决策掉.
所以先一遍深度搜索搜索出从1到n需要的时间,如果时间不超过总时间T,说明可以满足前提条件,
就将1到n路径上边权设置为0,总时间T减去1到n路径花费的总时间sum.之后从1点开始对整棵树
遍历进行树形dp即可,转移方程:dp[u][j]=max(dp[u][j],dp[u][j-t-2*w]+dp[v][t]);因为除过
1到n路径其它路径只要选择走,都会走两遍,而1到n路径边权为0所以不影响总时间花费.

有依赖关系,要走到子节点,必须先走到父节点.

注意:不能以价值作为背包容量 dp[i][j]=x表示以i为根节点的子树在选取子节点价值为j时最少花费的时间为x
这样空间复杂度 O(NM)=100*100*100=10^6 时间复杂度O(N*M^2)=100*10000^2=10^10 会TLE.
*/
//ac 78ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 510
using namespace std;

int cnt,head[N],n,T,val[N],dp[N][M],sum;

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

int dfs1(int u,int fa){
    if(u == n)
        return 1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(dfs1(v,u)){
            sum+=edge[i].w;
            edge[i].w=0;
            return 1;
        }

    }
    return 0;
}

void dfs2(int u,int fa){
    //初始状态,下界是0,因为对于到达u节点时间刚好剩下为0,但是仍然能获得该u节点子树中u节点一个点的价值
    for(int i=0;i<=T;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        int w=edge[i].w;
        if(v == fa) continue;
        dfs2(v,u);
        //容量下界是边权2w,因为要获得v点价值最少也得有2w时间一来一回走当前u->v的边两遍
        for(int j=T;j>=2*w;j--){
            //给子树分配的时间上界是j-2w,因为得保证dp[u][j-t-2w]中的j-t-2w不能为负数,数组下标不能为负
            for(int t=0;t<=j-2*w;t++)
                //之所以u点之前遍历的兄弟子树分配时间是j-t-2w,那是因为分配给v子树t时间,
                //实际需要先走u->v这条边权一来一回花费2w时间,那么剩下时间就是j-t-2w.
                dp[u][j]=max(dp[u][j],dp[u][j-t-2*w]+dp[v][t]);
        }
    }
}

int main(){
    int u,v,w;
    while(scanf("%d%d",&n,&T)!=EOF){
        sum=cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        dfs1(1,-1);
        if(sum>T){//从1直接走到n花费已经超过总时间T了 说明不能到达n点
            printf("Human beings die in pursuit of wealth, and birds die in pursuit of food!\n");
            continue;
        }
        T-=sum;//剩下时间T-sum
        //T-sum=0时,还是有可能能走其它边的子树的,因为w有可能为0
        memset(dp,0,sizeof(dp));
        //注意 起点是会影响实际k步限制内的结果的 题目要求从1节点出发
        dfs2(1,-1);
        printf("%d\n",dp[1][T]);
    }
    return 0;
}
