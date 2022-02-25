/*
题意:公司有n个仓库,需要安保.现在有m个人应聘职位,每个人有个值P[i](1 ≤P[i]≤1000);
安排第i个人看守k个仓库,则这k个仓库的安全值是p[i]/k,并且花费为p[i].公司要保证所有
仓库的最小安全值尽可能的大,求解这个值并且求这个方案的最小花费.
n<=100,m<=30.
链接:https://www.luogu.com.cn/problem/UVA10163
思路:很明显将m个仓库作为背包容量,n个人作为物品,物品容积是管理的仓库个数k,
物品价值为p[i],01背包.只是物品体积k没有给定,需要在dp过程中枚举.
分两次dp,第一次dp求出最小安全值,即:dp[i][j]=max(dp[i][j],min(dp[i-1][j-k],p[i]/k)),
比较在前i-1个人中管理j-k个仓库的最小安全值与当前第i个人管理k个仓库的安全值,取较小的
与之前dp[i][j]比较取最小值中的较大值,这个dp[i][j]可能是前i-1个人管理j个仓库的安全值
也可能是第i个人管理不同k个仓库时前i个人管理j个仓库的安全值.
第二次dp求出最小花费,dp时需要判断当前第个人的安全值是否>=第一次的最小安全值最大化的值.
dp[i][j]=min(dp[i][j],dp[i-1][j-k]+p[i]);

实际就是分组背包,背包容量是n个仓库,将每个人看做一组,每组的物品是当前第i个人看守k(1..n)
个仓库的各个可能情况,还需保证p[i]/k为整数.
*/
//ac 0ms 不给定物品体积 01背包枚举物品体积 一维数组实现
//实际就是分组背包,将人看做单独一组,每组物品为 第i个人负责1个仓库、第i个人负责2个仓库、...、第i个人负责n个仓库
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 35
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p[N],dp[M];

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d",&p[i]);
        memset(dp,0,sizeof(dp));
        dp[0]=INF;
        //dp[i][j]代表 前i个人管理j个仓库时最大的最小安全值
        for(int i=1;i<=m;i++){
            //滚动数组优化这里j必须放在第二层,并且降序,才能保证每次的dp[j-k]是前i-1个工作人的最优解
            for(int j=n;j>=1;j--){
                //枚举第i个人可以负责k个仓库,k的上界是min(j,p[i]) 实际就是第i组中物品的可能性
                for(int k=1;k<=j && k<=p[i];k++){//因为要求p[i]/k安全值为整数,所以k<=p[i]
                    if(dp[j-k]){
                        dp[j]=max(dp[j],min(dp[j-k],p[i]/k));
                    }
                }
            }
        }
        int ans=dp[n];
        if(!ans){
            printf("0 0\n");
            continue;
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0]=0;
        //dp[i][j]代表前i个人管理j个仓库时的最小花费
        for(int i=1;i<=m;i++){
            for(int j=n;j>=1;j--){
                //每个人的安全值必须不小于之前dp最小化中最大的安全值
                for(int k=1;k<=j && p[i]/k>=ans;k++)
                    dp[j]=min(dp[j],dp[j-k]+p[i]);
            }
        }
        printf("%d %d\n",ans,dp[n]);
    }
    return 0;
}

/*
//ac 0ms 01背包枚举物品体积 二维数组实现
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 35
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p[N],dp[N][M];

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d",&p[i]);
        memset(dp,0,sizeof(dp));
        dp[0][0]=INF;
        for(int i=1;i<=m;i++){
            for(int j=0;j<=n;j++)//继承前i-1的状态,注意下界是0
                dp[i][j]=dp[i-1][j];
            for(int k=1;k<=p[i];k++){//对于二维数组,这里k、j的顺序可以颠倒
                for(int j=n;j>=k;j--){
                    if(dp[i-1][j-k])
                        dp[i][j]=max(dp[i][j],min(dp[i-1][j-k],p[i]/k));
                }
            }
        }
        int ans=dp[m][n];
        if(!ans){
            printf("0 0\n");
            continue;
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0][0]=0;
        for(int i=1;i<=m;i++){
            for(int j=0;j<=n;j++){
                dp[i][j]=dp[i-1][j];
                for(int k=1;k<=j && p[i]/k>=ans;k++)
                    dp[i][j]=min(dp[i][j],dp[i-1][j-k]+p[i]);
            }
        }
        printf("%d %d\n",ans,dp[m][n]);
    }
    return 0;
}
*/

/*
//TLE 暴力搜索dfs
//O(2*n^m)
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 35
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p[N],dp[M],ans;
//O(2*n^m)
void dfs(int i,int sum,int pk){
    if(pk<ans)//剪枝 如果当前最小值不能比ans大,那么继续搜索下去之后更小,对ans的最大化没有帮助
        return;
    if(sum == n){
        ans=max(ans,pk);
        return;
    }
    if(i == m+1)
        return;
    //第i个人 枚举负责k个仓库
    for(int k=1;k<=n;k++){
        if(sum+k<=n && p[i]>=k)//只有当 p[i]/k是整数是才是合法 安全值
            dfs(i+1,sum+k,min(pk,p[i]/k));
    }
    //第i个人一个仓库也不负责
    dfs(i+1,sum,pk);
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        ans=0;
        for(int i=1;i<=m;i++)
            scanf("%d",&p[i]);
        memset(dp,0,sizeof(dp));
        dfs(1,0,INF);
        if(!ans){
            printf("0 0\n");
            continue;
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=m;i++){
            for(int j=n;j>=1;j--){
                //每个人的安全值必须不小于之前dp最小化中最大的安全值
                for(int k=1;k<=j && p[i]/k>=ans;k++)
                    dp[j]=min(dp[j],dp[j-k]+p[i]);
            }
        }
        printf("%d %d\n",ans,dp[n]);
    }
    return 0;
}
*/

/*
//ac 0ms 二分答案
//洛谷rayluo网友题解
#include<bits/stdc++.h>
using namespace std;
#define in inline
#define ll long long
const int N=110;
in int read()
{
	int w=0,r=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')r=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		w=(w<<1)+(w<<3)+(ch^48);
		ch=getchar();
	}
	return w*r;
}
int n,m,p[N];
int ans1,ans2;

in int min_(int x,int y)
{
	return x<y?x:y;
}

in int max_(int x,int y)
{
	return x>y?x:y;
}

int mx;
bool check(int x)  //判断函数
{
	if(x==0)return true;  //除数为零会导致运行时错误，提前判断。
	int cnt=0;  //最多可被守护的仓库
	for(int i=1;i<=m;i++)
	{
		cnt+=(p[i]/x);
		if(cnt>=n)return true;
	}
	return false;
}

void bs()  //二分答案
{
	int l=0,r=mx;  //上界为所有p中最大的一个
	ans1=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			l=mid+1;  //可行，则说明还可以尝试一下更大的
			ans1=mid;
		}
		else
		{
			r=mid-1;  //不行，就必须减少
		}
	}
}
int f[N];  //i个仓库的最小花费
int solve(int x)
{
	memset(f,0x3f,sizeof(f));
	f[0]=0;  //不取，则花费为0
	for(int i=1;i<=m;i++)
	{
		for(int j=n;j>=1;j--)  //优化空间
		{
			for(int k=1;k<=j;k++)
			{
				if(x<=(p[i]/k))  //k是否符合要求
				{
					f[j]=min_(f[j],f[j-k]+p[i]);  //转移
				}
			}
		}
	}
	return f[n];
}

int main()
{
	n=read();
	m=read();
	while(n!=0||m!=0)
	{
		ans1=0;
		ans2=0;
		for(int i=1;i<=m;i++)
		{
			p[i]=read();
			mx=max_(mx,p[i]);//统计二分上界
		}
		bs();
		if(ans1==0)//特判
		{
			puts("0 0");
		}
		else
		{
			cout<<ans1<<" "<<solve(ans1)<<endl;
		}
		n=read();
		m=read();
	}
	return 0;
}
*/
