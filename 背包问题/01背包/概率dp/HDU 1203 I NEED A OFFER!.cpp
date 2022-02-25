#include<cstdio>
#include<algorithm>
#define N 11000
using namespace std;
//ac 0ms 一维数组dp 尽可能多装,不要求恰好装满
/*
前置知识:数学中的独立事件概率.
eg:三人射击,甲命中率为二分之一,乙命中率为三分之一,丙命中率为四分之一.
(1)三人都击中的概率？(2)三人中至少有一人击中的概率？
(1).(1/2)*(1/3)*(1/4)=1/24
(2).两种做法:
一种是从正面考虑,至少一人命中,分为1人命中,2人命中,3人命中,
这三种情况.
1人命中:
甲命中:(1/2)*(1-1/3)*(1-1/4)=1/4
乙名中:(1-1/2)*(1/3)*(1-1/4)=1/8
丙名中:(1-1/2)*(1-1/3)*(1/4)=1/12
1人命中概率=1/4+1/8+1/12=11/24

2人命中:
乙丙命中:(1-1/2)*(1/3)*(1/4)=1/24
甲丙命中:(1/2)*(1-1/3)*(1/4)=1/12
甲乙命中:(1/2)*(1/3)*(1-1/4)=1/8
2人命中概率:1/24+1/12+1/8=6/24

三人命中:(1/2)*(1/3)*(1/4)=1/24

综上所述至少一人命中概率=P(1人命中)+P(2人命中)+P(3人命中)=11/24+6/24+1/24=3/4

另一种方法是从反面考虑:"至少1人命中"的对立事件为"所有人都未命中",即两个事件互斥
所以,P(至少1人命中)=1-P(所有人都未命中)=1-(1-1/2)*(1-1/3)*(1-1/4)=1-1/4=3/4
*/

/*
题意:V(V<=10^4)元钱,N(N<=10^4)个学校,每个学校的申请费为w[i],
通过概率是val[i],每个学校申请事件是相互独立的,现在求可以收到
至少一份offer的最大概率.
注意:0<=v<=10^4,0<=n<=10^4,v和n可为0,w[i]也可能为0,也就是存在
不花钱申请学校的情况.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1203
思路:每个学校只有申请与不申请2个状态,且只可以申请一次,但是
问的是"至少获得一份offer的最大概率",直接考虑得分很多情况一个学校通过,
2个学校通过,3个学校通过,...,n个学校通过,这样考虑原问题会变成一个在
给定n个物品中选取指定数目物品的暴力枚举问题,而且复杂度较高,但是
"至少获得一份offer的最大概率"的对立事件为“一个offer也不能获得的最小概率”,
即所有学校都不通过的最小概率(1-val[i]),而现在所给出的V元钱显然是要
小于所有学校的申请费用总和的,根据乘法原理问题转化成了尽可能多地选择学校之间
不通过率相乘结果最小的概率积,显然V元钱多数情况下不能申请所有的学校,那么对于
每个学校申请与否就需要有所取舍,那么对于求取最小的没有offer的最小概率就构成了
一个01背包问题,并且背包容量应该是尽可能多地装而不必恰好装满的这种情况,
所以初始化dp都为1.0,因为概率独立事件之间是乘法原理累乘概率,V有可能是会有剩余的,
而剩下的钱也不够申请剩下的任何一个学校.只是相对经典的01背包是问累加的最大价值,
这里是按照乘法原理累乘求取最小没有offer的概率,状态转移方程为dp[j]=min(dp[j],dp[j-w[i]]*(1-val[i])),
初始化dp[v]=1.0,这样越累乘结果就越小,符合背包舍取选择的思想.
*/
int w[N],n,v;
double dp[N],val[N];

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        for(int i=0;i<=v;i++)
            dp[i]=1.0;//因为是累乘,所以初始化为1.0
        for(int i=1;i<=n;i++){
            for(int j=v;j>=w[i];j--)
                dp[j]=min(dp[j],dp[j-w[i]]*(1-val[i]));//越累乘结果越小符合背包取舍物品的原则
        }
        printf("%.1f%%\n",(1-dp[v])*100);//输出原问题要取反,即至少获得一个offer的最大概率
    }
    return 0;
}

/*
//ac 15ms 一维数组dp 恰好装满背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11000
#define INF 1e18
using namespace std;

int w[N],n,v;
double dp[N],val[N];

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        for(int i=0;i<=v;i++)
            dp[i]=INF;
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        dp[0]=1.0;
        for(int i=1;i<=n;i++){
            for(int j=v;j>=w[i];j--)
                dp[j]=min(dp[j],dp[j-w[i]]*(1-val[i]));//越累乘结果越小符合背包取舍物品的原则
        }
        double ans=1.0;//如果本身的钱v不够申请任何一所学校,则dp[0..v]>1,需要初始化ans=1.0,至少获得offer的概率为1-ans=0
        //这组样例:v=0,n=1 w[1]=0,val[1]=1,实际可以不花钱申请到offer,通过率实际为1,但是只有dp[0]=0<1.0,所以i的下限要到0
        for(int i=v;i>=0;i--){
            if(dp[i]<1.0)
            //不一定花的钱越多,没有获得offer的概率就越小,虽然乘积会越乘越小,
            //但可能只有1、2个学校的花费很高,而实际不通过率本身就很大,
            //而实际所花钱较小的,可能是很多个学校的不通过率乘积 也可能更小,所以要遍历所有情况
                ans=min(ans,dp[i]);
        }
        printf("%.1f%%\n",(1-ans)*100);//输出原问题要取反,即至少获得一个offer的最大概率
    }
    return 0;
}
*/

/*
//TLE 暴力枚举搜索+剪枝
#include<cstdio>
#include<algorithm>
#define N 11000
#define INF 0x3f3f3f3f
using namespace std;

//sufxv[i]表示i~n后缀学校里最小的申请费用
//sufxval[i]表示i~n后缀所有学校的申请不通过率的积
int w[N],n,v,sufxv[N];
double ans,val[N],sufxval[N];

//num为已经申请的学校数量,V为剩余钱,res为当前申请学校都不能获得offer的概率
int dfs(int k,int num,int V,double res){
    if(res<ans)
        ans=res;
    //剪枝1 当所有学校都申请时,不能获得offer的概率一定是最小的(小数乘积,越乘越小),无需再比较,直接返回1,退出搜索
    if(num == n) return 1;
    if(V<sufxv[k]) return 0;//剪枝2 前剩余钱比编号为k~n的学校中申请费用最小的还少时,就不能再申请,返回0,停止当前搜索,回溯上一层
    if(res*sufxval[k]>=ans) return 0;//剪枝3 当当前概率res乘编号为k~n所有学校的申请不通过率之积的积不比ans小时,停止当前搜索,回溯到上一层
    if(k == n+1) return 0;//枚举所有物品结束,结束,回溯到上一层
    if(V>=w[k])//只有当剩余钱足够支付第k个学校申请费用时 才申请
        if(dfs(k+1,num+1,V-w[k],res*(1-val[k]))) return 1;
    if(dfs(k+1,num,V,res)) return 1;//不申请第k个学校
    return 0;
}

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        sufxv[n+1]=INF;
        sufxval[n+1]=1.0;
        ans=1.0;
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        for(int i=n;i>=1;i--)
            sufxv[i]=min(sufxv[i+1],w[i]);
        for(int i=n;i>=1;i--)
            sufxval[i]=sufxval[i+1]*(1-val[i]);
        dfs(1,0,v,1.0);
        printf("%.1f%%\n",(1-ans)*100);
    }
    return 0;
}
*/

/*
//MLE 二维数组dp
//N<=10^4 N*N<=10^8,空间超标
#include<cstdio>
#include<algorithm>
#define N 11000
using namespace std;

int w[N],n,v;
double dp[N][N],val[N];

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        for(int i=0;i<=v;i++)
            dp[0][i]=1.0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=v;j++){
                if(j>=w[i])
                    dp[i][j]=min(dp[i-1][j],dp[i-1][j-w[i]]*(1-val[i]));
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%.1f%%\n",(1-dp[n][v])*100);
    }
    return 0;
}
*/

/*
//MLE 二维数组记忆化搜索
//N<=10^4 N*N<=10^8,空间超标
#include<cstdio>
#include<algorithm>
#define N 11000
using namespace std;

int w[N],n,v;
double dp[N][N],val[N];

double dfs(int i,int j){
    if(!i) return 1.0;
    if(dp[i][j]) return dp[i][j];
    if(j>=w[i])
        dp[i][j]=min(dfs(i-1,j),dfs(i-1,j-w[i])*(1-val[i]));
    else
        dp[i][j]=dfs(i-1,j);
    return dp[i][j];
}

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        for(int i=1;i<=n;i++)
            for(int j=0;j<=v;j++)
                dp[i][j]=0;
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        printf("%.1f%%\n",(1-dfs(n,v))*100);
    }
    return 0;
}
*/

/*
//谢勇老师08背包初探.pptx上的标程不理解这个状态转移方程
//dp[j] = MAX(dp[j],w[i]+(1.0-w[i])*dp[j-c[i]]) 为啥要再加w[i],应该是写错了
#define V 11111
#define N 1111
#define MAX(x,y) ((x)>(y)?(x):(y))
double dp[V];
int c[N];
double w[N];
void solve(int n,int v){
	int i,j;
	memset(dp,0,sizeof(double)*(v+1));
	for(i=0;i<n;i++){
		for(j=v;j>=c[i];j--) dp[j] = MAX(dp[j],w[i]+(1.0-w[i])*dp[j-c[i]]);
	}
}
*/

