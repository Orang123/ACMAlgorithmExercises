/*
题意:矿工在原点(0,0)抓金矿,抓取每块金矿需要对应的时间t,能够获得价值v.
但是当多块金矿在和原点的连线在同一直线上时,矿工那只能先抓近的,再抓远的.
求矿工在给定时间T下,所能获得的最大价值.
n<=200,T<=40000.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4341
思路:不考虑多块金矿在同一直线上,这个问题就是裸的01背包,但是实际抓取金矿
对于在同一直线上(斜率相同)的金矿,只能先抓近的,在抓排在后面的,不能出现前面的
没抓,就把后面的抓了,可以将所有的金矿按照斜率分组,对于同一直线上的金矿分为
一次性抓取前1个金矿、前2个金矿...n个金矿,即:分组后组内的第i个物品的体积和价值是
前i个物品体积、价值的前缀和.这样实际同一直线金矿抓取只能抓取前i个金矿,就满足分组
背包每组内物品最多只能取一个.
*/
//ac 124ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 40010
using namespace std;

int n,T,w[N][N],val[N][N],num[N],k,dp[M];

struct Node{
    int x,y,t,v;
    bool operator < (const Node &a)const{
        //按照金矿与原点相连的直线的斜率分组,同一直线上按照离原点距离有近到远排序
        //因为用浮点数y/x < a.y/a/x 可能会出现精度误差,所以改用十字相乘法判断
        return (y*a.x <a.y*x || (y*a.x == a.y*x && y<a.y));
    }
}node[N];

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&T)!=EOF){
        cas++;
        memset(dp,0,sizeof(dp));
        memset(num,0,sizeof(num));
        k=0;
        for(int i=1;i<=n;i++)
            scanf("%d%d%d%d",&node[i].x,&node[i].y,&node[i].t,&node[i].v);
        sort(node+1,node+1+n);
        for(int i=1;i<=n;i++){
            //斜率相同分在一组
            if(node[i].y*node[i-1].x == node[i-1].y*node[i].x && i!=1){
                num[k]++;
                w[k][num[k]]=w[k][num[k]-1]+node[i].t;//每组第i个物品是直线上前i个物品的体积、价值前缀和
                val[k][num[k]]=val[k][num[k]-1]+node[i].v;
            }
            else{
                num[++k]++;
                w[k][num[k]]=node[i].t;
                val[k][num[k]]=node[i].v;
            }
        }
        for(int i=1;i<=k;i++){
            for(int j=T;j>=1;j--){//每个金矿至少需要时间1,因此j下界是1
                for(int t=1;t<=num[i];t++){
                    if(j>=w[i][t])
                        dp[j]=max(dp[j],dp[j-w[i][t]]+val[i][t]);
                    else//前缀和会越来越大,当前体积比j大 就结束
                        break;
                }
            }
        }
        printf("Case %d: %d\n",cas,dp[T]);
    }
    return 0;
}
/*
//ac 156ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 40010
using namespace std;

int n,T,w[N][N],val[N][N],num[N],k,dp[M];

struct Node{
    double x,y;
    int t,v;
    bool operator < (const Node &a)const{
        return (x/y <a.x/a.y || (x/y == a.x/a.y && y<a.y));
    }
}node[N];

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&T)!=EOF){
        cas++;
        memset(dp,0,sizeof(dp));
        memset(num,0,sizeof(num));
        k=0;
        for(int i=1;i<=n;i++)
            scanf("%lf%lf%d%d",&node[i].x,&node[i].y,&node[i].t,&node[i].v);
        sort(node+1,node+1+n);
        for(int i=1;i<=n;i++){
            if(node[i].x/node[i].y == node[i-1].x/node[i-1].y && i!=1){
                num[k]++;
                w[k][num[k]]=w[k][num[k]-1]+node[i].t;
                val[k][num[k]]=val[k][num[k]-1]+node[i].v;
            }
            else{
                num[++k]++;
                w[k][num[k]]=node[i].t;
                val[k][num[k]]=node[i].v;
            }
        }
        for(int i=1;i<=k;i++){
            for(int j=T;j>=1;j--){
                for(int t=1;t<=num[i];t++){
                    if(j>=w[i][t])
                        dp[j]=max(dp[j],dp[j-w[i][t]]+val[i][t]);
                    else
                        break;
                }
            }
        }
        printf("Case %d: %d\n",cas,dp[T]);
    }
    return 0;
}
*/

/*
//ac 124ms
//转化为依赖背包,建树用dfs序进行01背包 树形背包做法
//摘自博客:https://blog.csdn.net/ice_crazy/article/details/9236951
#include"iostream"
#include"cstdio"
#include"cmath"
#include"cstring"
#include"algorithm"
using namespace std;
const int N=205;
const int M=40005;

int n,m,now,pre,dp[2][M];
struct node{
    int x,y,dis2,cost,val;
}E[N];
struct Edge{
    int v,next;
}edge[N];
int tot,head[N];
void add(int a,int b){
    edge[tot].v=b;edge[tot].next=head[a];head[a]=tot++;
}

int cmp(node n1,node n2){
    return n1.dis2<n2.dis2;
}
void build()
{
    int i,l,ff;
    double k1,k2;
    tot=0;
    memset(head,-1,sizeof(head));
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d%d",&E[i].x,&E[i].y,&E[i].cost,&E[i].val);
        E[i].dis2=E[i].x*E[i].x+E[i].y*E[i].y;
    }
    sort(E,E+n,cmp);
    for(i=n-1;i>=0;i--)
    {
        ff=0;
        if(!E[i].x) k1=123456;
        else        k1=1.0*E[i].y/E[i].x;
        for(l=i-1;l>=0;l--)
        {
            if(ff)    break;
            if(!E[l].x) k2=123456;
            else        k2=1.0*E[l].y/E[l].x;
            if(fabs(k1-k2)>1e-5)    continue;
            ff=1;
            add(l,i);
        }
        if(!ff) add(i,i);
    }
}
void dfs(int j,int k,int acc_val,int acc_cost)
{
    int l;
    int sum_val=acc_val+E[k].val;
    int sum_cost=acc_cost+E[k].cost;
    for(l=0;l<sum_cost;l++) dp[now][l]=dp[pre][l];
    for(;l<=m;l++)
    {
        dp[now][l]=dp[pre][l];
        if(dp[now][l] < dp[pre][l-sum_cost]+sum_val)
            dp[now][l]=dp[pre][l-sum_cost]+sum_val;
    }
    j=edge[j].next;
    if(j!=-1)   dfs(j,edge[j].v,sum_val,sum_cost);
}
void DP()
{
    int i,j;
    now=1;pre=0;
    memset(dp,0,sizeof(dp));
    for(i=0;i<n;i++)
    {
        j=head[i];
        if(j==-1) continue;
        if(edge[j].v!=i)  continue;
        now=(now+1)%2;
        pre=1-now;
        dfs(j,edge[j].v,0,0);
    }
}
int main()
{
    int Case=1;
    while(scanf("%d%d",&n,&m)!=-1)
    {
        build();
        DP();
        printf("Case %d: %d\n",Case++,dp[now][m]);
    }
    return 0;
}
*/
