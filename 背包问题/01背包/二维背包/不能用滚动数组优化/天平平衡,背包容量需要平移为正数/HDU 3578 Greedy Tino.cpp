#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 4100
using namespace std;
//ac 124ms 扩大背包容量为正数进行01背包 模拟扁担平衡
//不一定所有橘子都要放上
/*
题意:n个橘子,每个橘子有一定重量w[i],需要用一根扁担挑
起来,使得扁担两侧重量相同,求出使得扁担平衡的最大重量,
输出一侧的重量.
n<=100,w[i]<=2000,w[1]+w[2]+...+w[n]<=2000
注意:并不是每个橘子都要用扁担挑起来,可以有橘子不放.
因为所以橘子都放不一定能平衡.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3578
思路:和 POJ 1837 类同,不同的是本题不一定要求所有橘子都放上,
而POJ 1837 要求所有砝码都放上,平衡区间[-2000,2000],平衡点为0，
但背包容量不能为负,所以区间向右平移2000个单位,即[0,4000],
此时平衡点为2000.初始状态为dp[0][2000]=0.其余状态-INF,需要
恰好装满背包.
*/
int cas,n,w[N],dp[N][M],sum;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];//sum表示所有橘子放在扁担一侧能产生的最大重量
        }
        sum<<=1;//sum乘2代表将区间平移后 扩大为之前两倍.
        dp[0][sum/2]=0;//初始状态平衡点为sum/2
        //dp[i][j] 代表考虑i个橘子放用扁担挑起来,扁担两侧重量差为j-sum/2时扁担挑起的橘子最大重量和
        for(int i=1;i<=n;i++){
            //注意不能用滚动数组优化,因为无论j升序还是降序,dp[i-1][j+w[i]] dp[i-1][j-w[i]]同一时刻必然有一个不能表示前i-1个状态
            for(int j=0;j<=sum;j++){
                dp[i][j]=dp[i-1][j];//继承上一状态
                //前i-1个状态最大重量 j+w[i]-sum/2<=sum-sum/2
                if(j+w[i]<=sum)//因为dp[i-1][j+w[i]]本身就可能不合法,所以要判断
                    //代表将橘子放在扁担左侧
                    //若j+w[i]<sum/2 则前i-1个状态左侧较重,那么将第i个橘子放在扁担左侧,会使得两侧重量差变大.j-sum/2<j+w[i]-sum/2,j一定小于sum/2,j-sum/2<0 前者绝对值较大
                    //若j+w[i]>sum/2 则前i-1个状态右侧较重,那么将第i个橘子放在扁担左侧,j-sum/2 j+w[i]-sum/2,j可能<sum/2 因为w[i]不确定,所以2者绝对者大小不定,两侧重量差可能减小也可能增大
                    dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);//dp[i][j]是之前 dp[i-1][j]代表前i-1个状态没有放入第i个橘子
                //前i-1个状态最大重量 j-w[i]-sum/2>=0-sum/2
                if(j-w[i]>=0)
                    //代表将橘子放在扁担右侧
                    //若j-w[i]<sum/2 则前i-1个状态左侧较重,那么将第i个橘子放在扁担右侧,j-sum/2 j-w[i]-sum/2,j可能>sum/2 因为w[i]不确定,所以2者绝对者大小不定,两侧重量差可能减小也可能增大
                    //若j-w[i]>sum/2 则前i-1个状态右侧较重,那么将第i个橘子放在扁担右侧,会使得两侧重量差变大.j-sum/2>j-w[i]-sum/2,j-sum/2>0 前者较大
                    dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+w[i]);//这里dp[i][j]可能是前i-1个状态也可能是第i个橘子放在左侧的状态
            }
        }
        printf("Case %d: ",cas);
        if(dp[n][sum/2]>0)//合法状态
            printf("%d\n",dp[n][sum/2]/2);//单侧的重量,sum/2代表平衡状态
        else{//若不合法 但存在橘子重量为0,还是会使得扁担平衡,则可以携带橘子,则输出重量0
            int flag=0;
            for(int i=1;i<=n;i++){
                if(!w[i]){
                    flag=1;
                    printf("0\n");
                    break;
                }
            }
            if(!flag)
                printf("-1\n");
        }
    }
    return 0;
}

/*
//ac 124ms 另一种转移方式
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 4100
using namespace std;

int cas,n,w[N],dp[N][M],sum,flag;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        flag=sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            if(!w[i]) flag=1;
            sum+=w[i];
        }
        sum<<=1;
        dp[0][sum/2]=0;
        for(int i=1;i<=n;i++){
            //这里必须提前继承前i-1个橘子最优解的状态
            //因为状态转移方程是由dp[i-1][j]到dp[i][j-w[i]],上一个状态是dp[i][j-w[i]] 不是dp[i][j]
            for(int j=0;j<=sum;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=0;j<=sum;j++){
            	if(dp[i-1][j]<0) continue;
            	//如果dp[i-1][j]是合法的,那么j-w[i]/j+w[i]一定在[0,sum]范围内
                dp[i][j-w[i]]=max(dp[i][j-w[i]],dp[i-1][j]+w[i]);
                dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);

            }
        }
        printf("Case %d: ",cas);
        if(dp[n][sum/2]>0){
            printf("%d\n",dp[n][sum/2]/2);
        }
        else{
            if(flag)
                printf("0\n");
            else
                printf("-1\n");
        }
    }
    return 0;
}
*/

/*
//ac 78ms 不扩大区间做法
//dp[i][j]表示考虑i个橘子放用扁担挑起来,扁担两侧重量差为j时扁担挑起的橘子最大重量和
//这里并不区分到底左侧重还是右侧重
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 2100
using namespace std;

int cas,n,w[N],dp[N][M],sum,flag;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        flag=sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            if(!w[i]) flag=1;
            sum+=w[i];
        }
        dp[0][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=sum;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=0;j<=sum;j++){
            	if(dp[i-1][j]<0) continue;
                dp[i][abs(j-w[i])]=max(dp[i][abs(j-w[i])],dp[i-1][j]+w[i]);
                dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);

            }
        }
        printf("Case %d: ",cas);
        if(dp[n][0]>0){
            printf("%d\n",dp[n][0]/2);
        }
        else{
            if(flag)
                printf("0\n");
            else
                printf("-1\n");
        }
    }
    return 0;
}
*/

/*
//ac 93ms 一维数组dp做法
//一维数组思路 和HDU 5616是类似的
#include <map>
#include <stack>
#include <queue>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#define N 4005
#define M
#define E
#define INF 0x3f3f3f3f
#define eps 1e-8
#define LL long long
#define D(a) ((a)*(a))
using namespace std;

int dp[N],n,a[N],b[N];

void re(void)
{
	scanf("%d",&n);
}

void run(void)
{
	memset(dp,-1,sizeof(dp));
	dp[2000]=0;
	int flag=0;
	for(int i=0;i<n;i++)
	{
	    int v;
	    scanf("%d",&v);
	    if(v==0)flag++;
	    memset(a,-1,sizeof(a));
	    memset(b,-1,sizeof(b));
	    for(int i=0;i<=4000;i++)
	        if(~dp[i])
                a[i-v]=max(dp[i-v],dp[i]+v),
                b[i+v]=max(dp[i+v],dp[i]+v);
        for(int i=0;i<=4000;i++)
            dp[i]=max(dp[i],max(a[i],b[i]));
	}
	if(dp[2000]==0&&flag<1)printf("-1\n");
	else printf("%d\n",dp[2000]/2);
}

int main()
{
	int ncase;
	scanf("%d",&ncase);
	for(int i=1;i<=ncase;i++)
	{
		re();
		printf("Case %d: ",i);
		run();
	}
	return 0;
}
*/

/*
//MLE 应该也会TLE 暴力枚举搜索+剪枝
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 2100
using namespace std;

//vis[k][l][r]=1代表 前k个橘子放扁担两侧,左侧重量l,右侧重量r的情况已经遍历过
int cas,n,w[N],ans,flag,vis[N][M][M];

//O(3^n) n<=100,n^100 每个橘子如果放可以放在左侧或右侧,或者不放
void dfs(int k,int l,int r){
    //剪枝 前k个橘子 左右侧重量为l、r的情况之前已遍历过,
    //后面的k+1、k+2、...、n个橘子的枚举放的位置或不放是相同的过程,不必重复枚举可能情况
    if(vis[k][l][r])
        return;
    vis[k][l][r]=1;
    if(l == r && l>ans)
        ans=l;
    if(k == n+1)
        return;
    dfs(k+1,l+w[k],r);//第i个橘子放左侧
    dfs(k+1,l,r+w[k]);//第i个橘子放右侧
    dfs(k+1,l,r);//不放第i个橘子
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        flag=ans=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            if(!w[i])
                flag=1;
        }
        dfs(1,0,0);
        if(ans!=-1)
            printf("Case %d: %d\n",cas,ans);
        else{
            if(flag)
                printf("0\n");
            else
                printf("-1\n");
        }
    }
    return 0;
}
*/
