/*
题意:n个城镇,共有n-1条道路连接所有的城镇,任意两条城镇间都有
一条特定的道路构成路径相通.每个城镇有一定价值val[i],每条道路
从一端走到另一端需要w天,现在给定m天时间限制,问在时间m天内从k城镇
出发再回到k城镇所能获得的最大的价值和.
n<=100,m<=200,1<=w<=10.0<=val[i]<=1000.
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827369271
思路:n个城镇构成树形结构,要遍布全局最优解需要从叶子节点到父节点开始考虑,树上分组背包.
从k点出发又回到k点,那么之前遍历的边一定都走了两遍,但是每个点的价值只获取一次,可以考虑
在m/2时间限制下不往回走,遍历从k点出发的子树最多能获得得到的价值,实际时间就是遍历一遍的2倍,
因为要走回k点,这是对背包容量总时间的一个优化.
dp[i][j]表示从以i点为根节点的子树出发在时间为j天下遍历子树节点最多能获得的价值.
状态转移方程:dp[u][j]=max(dp[u][j],dp[u][j-t-w]+dp[v][t]);
因为只走一遍,实际一条边花费时间是w,注意给v节点分t时间获得的最大价值,之前遍历子树剩下的时间是
j-t-w,因为u->v这条边还需花费时间w.这里不能优化子树背包容量为u节点子树的所有边权和,因为实际m可能
并未用完,要尽可能多地装满背包,所以背包容量恒为m.

有依赖关系,要走到子节点,必须先走到父节点.
注意:
不能以价值作为背包容量,dp[i][j]=x表示以i为根节点的子树在选取子节点价值为j时最少花费的时间为x
求解给定价值下所需要的最少的时间,最后按照最大价值降序判断dp[1][i]<=m是否合法,
M=100*1000=10^5 N*M=10^7 会TLE.
*/
//ac 15ms m/2时间内,边权只走一遍花费为w
//dp[u][j]=max(dp[u][j],dp[u][j-t-w]+dp[v][t]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
using namespace std;

int cnt,head[N],n,m,k,val[N],dp[N][M];

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    //初始状态,下界是0,因为对于到达u节点时间刚好剩下为0,但是仍然能获得该u节点子树中u节点一个点的价值
    for(int i=0;i<=m;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        int w=edge[i].w;
        if(v == fa) continue;
        dfs(v,u);
        //容量下界是边权w,因为要获得v点价值最少也得有w时间走完当前u->v的边
        for(int j=m;j>=w;j--){
            //给子树分配的时间上界是j-w,因为得保证dp[u][j-t-w]中的j-t-w不能为负数,数组下标不能为负
            for(int t=0;t<=j-w;t++)
                //之所以u点之前遍历的兄弟子树分配时间是j-t-w,那是因为分配给v子树t时间,
                //实际需要先走u->v这条边权花费w时间,那么剩下时间就是j-t-w.
                dp[u][j]=max(dp[u][j],dp[u][j-t-w]+dp[v][t]);
        }
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        scanf("%d%d",&k,&m);
        //实际返回k点所有边都会走两遍,可以考虑花费时间限为m一半时,
        //k点出发子树每条边只走一遍能获得的最大价值
        m/=2;
        //注意 起点是会影响实际m天时间限制内的结果的 题目要求从k节点出发
        dfs(k,-1);
        printf("%d\n",dp[k][m]);
    }
    return 0;
}

/*
//ac 49ms m时间内,按照回到k点算,每条边刚好走2遍(一来一回)
//dp[u][j]=max(dp[u][j],dp[u][j-t-2*w]+dp[v][t]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
using namespace std;

int cnt,head[N],n,m,k,val[N],dp[N][M];

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=0;i<=m;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        int w=edge[i].w;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=m;j>=2*w;j--){
            for(int t=0;t<=j-2*w;t++)
                dp[u][j]=max(dp[u][j],dp[u][j-t-2*w]+dp[v][t]);
        }
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        scanf("%d%d",&k,&m);
        dfs(k,-1);
        printf("%d\n",dp[k][m]);
    }
    return 0;
}
*/

/*
//TLE MLE M=100*1000=10^5 O(N*M^2)=10^12
//以价值作为背包容量
//dp[i][j]=x表示以i为根节点的子树在选取子节点价值为j时最少花费的时间为x
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

int cnt,head[N],n,m,k,val[N],siz[N],dp[N][M];

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
	siz[u]=val[u];
	dp[u][val[u]]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        int w=edge[i].w;
        if(v == fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        //从k点出发 只要走过的边花费了时间,必然会选取走过的父节点的价值
        //也就是要选取子节点 必然选取父节点.
		//j下界 val[u]保证选取父节点u
        for(int j=siz[u];j>=val[u];j--){
        	//t上界j-val[u]和siz[v]的最小值 保证j-t>=val[u]能选取到父节点u以及dp[v][t]的合法性
        	//t下界是val[v],因为是恰好装满背包,v子树最少能获得的价值就是v点一个点的价值val[v]
        	//j-t>siz[u]-siz[v]时 之前u遍历的兄弟子树最多的价值和是siz[u]-siz[v]超过这个值显然都是不合法的状态
        	for(int t=min(siz[v],j-val[u]);t>=val[v] && j-t<=siz[u]-siz[v];t--)
                dp[u][j]=min(dp[u][j],dp[u][j-t]+dp[v][t]+w);
        }
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        scanf("%d%d",&k,&m);
        //实际返回k点所有边都会走两遍,可以考虑花费时间限为m一半时,
        //k点出发子树每条边只走一遍能获得的最大价值
        m/=2;
        memset(dp,0x3f,sizeof(dp));
        dfs(k,-1);
        for(int i=siz[k];i>=0;i--){
        	if(dp[k][i]<=m){
        		printf("%d\n",i);
        		break;
			}
		}
    }
    return 0;
}
*/

/*
//ac 41ms m时间内边权走2遍
//摘自博客:https://www.cnblogs.com/lienus/p/4204042.html
//dp[u][j+2*w]=max(dp[u][j+2*w],dp[u][j-k]+dp[v][k]); 容量上界为m-2*w
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <stack>
#include <vector>
#include <set>
#include <map>
#define LL long long
#define mod 1000000007
#define inf 0x3f3f3f3f
#define N 1010
#define clr(a) (memset(a,0,sizeof(a)))
using namespace std;
struct edge
{
    int v,w,next;
    edge(){}
    edge(int v,int w,int next):v(v),w(w),next(next){}
}e[2*N];
int head[N],dp[N][N],val[N],tot,n,m;
void addedge(int u,int v,int w)
{
    e[tot]=edge(v,w,head[u]);
    head[u]=tot++;
}
void dfs(int u,int fa)
{
    for(int i=0;i<=m;i++)dp[u][i]=val[u];
    for(int i=head[u];~i;i=e[i].next)
    {
        int v=e[i].v,w=e[i].w;
        if(v==fa)continue;
        dfs(v,u);
        for(int j=m-2*w;j>=0;j--)
        for(int k=0;k<=j;k++)
        {
            //之所以是j+2w,是因为dp[u][j-k]+dp[v][k]实际用掉了u->v这条边的花费,走了2遍,因此实际的时间为j+2w
           dp[u][j+2*w]=max(dp[u][j+2*w],dp[u][j-k]+dp[v][k]);
        }
    }
}
int main()
{
    int u,v,w,x,k;
    while(scanf("%d",&n)>0)
    {
        memset(head,-1,sizeof(head));
        clr(dp);tot=0;
        for(int i=1;i<=n;i++)scanf("%d",&val[i]);
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
            addedge(v,u,w);
        }
        scanf("%d%d",&k,&m);
        dfs(k,-1);
        printf("%d\n",dp[k][m]);
    }
}
*/
