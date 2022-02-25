/*
//题意摘自网上
题意:有n个架子,每个架子从左到右摆放着num个瓷器,每个瓷器都有对应的价值.
现在公主发飙了,发出了m声尖叫,每次尖叫意味着会有一个瓷器被摔了.瓷器
每次只能拿某个架子上最左边或者最右边的一个,问损失的最大价值为多少?
n<=100,num[i]<=100,m<=10000
链接:http://codeforces.com/problemset/problem/148/E
思路:01背包并不能按照题意模拟只取左右两端瓷器.需要用分组背包在每层架子列出可能的取出
瓷器最大价值的情况.
和CF 946D Timetable做法基本一样.
分组背包,将能取的瓷器总数m作为背包容量.每个架子单独作为一组,组内的物品
分别为取走这个架子左右两端共1、2、3、..min(m,num[i])个瓷器会损失的最大价值.
因为题目说明所有瓷器的个数至少会是m,所以保证了背包一定能装满,所以按照尽可能多
地装满背包初始化全0即可.
*/
//ac 78ms 区间预处理+分组背包
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
#define M 10010
using namespace std;

//prefx[i][j]代表第i个架子上前j个瓷器的价值和 前缀和
//sufx[i][j]代表第i个架子上后j个瓷器的价值和 后缀和
int a[N],prefx[N][N],sufx[N][N];
//num[i]第i个架子上瓷器的个数
//val[i][j]第i个架子上取走左右两端共j个瓷器所能得到的最大价值和
//dp[i][j]代表前i个架子上按照只取每个架子左右两端共j个瓷器最多能获得的价值和
int n,m,num[N],val[N][N],dp[M];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d",&a[j]);
        for(int j=1;j<=num[i];j++)
            prefx[i][j]=prefx[i][j-1]+a[j];
        for(int j=num[i];j>=1;j--)
            //这里num[i]-j+1才是后缀和的瓷器的个数
            sufx[i][num[i]-j+1]=sufx[i][num[i]-j]+a[j];
    }
    for(int i=1;i<=n;i++){
        int k=min(num[i],m);
        for(int j=1;j<=k;j++){
            if(j == num[i]){//取走所有瓷器,价值直接就是前缀和 无需后续的循环遍历
                val[i][j]=prefx[i][j];
                break;
            }
            for(int l=0;l<=j;l++){
                int r=j-l;
                val[i][j]=max(val[i][j],prefx[i][l]+sufx[i][r]);
            }
        }
    }
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            int tp=min(num[i],j);//第i个架子最多能取走的合法的瓷器个数tp
            for(int k=1;k<=tp;k++)
                //dp[j-k]是前i-1个架子取走j-k个瓷器最多能获得的价值和
                dp[j]=max(dp[j],dp[j-k]+val[i][k]);
        }
    }
    printf("%d",dp[m]);
    return 0;
}

/*
//ac 109ms 预处理+分组背包 用前缀和的差表示出后缀和
//摘自洛谷题解
#include<iostream>
#include<vector>
using namespace std;
int n,m,N,ans,dp1[105][105],sum[105][105],dp2[105][10005];
vector<int> a[105];
int cal(int k,int i,int j) //第 k 层取了前 i 个和后 j 个的总价值
{
	int N=a[k].size();
	return sum[k][N]-sum[k][N-j]+sum[k][i];
}
int main()
{
	int N,x;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>N;
		for(int k=1;k<=N;k++)
			cin>>x,a[i].push_back(x),sum[i][k]=sum[i][k-1]+x;//因为每一层长度不定，用一个vector保存，同时计算前缀和
	}
	for(int k=1;k<=n;k++)
		for(int l=1;l<=a[k].size();l++)
			for(int i=0;i<=l;i++) {int j=l-i;dp1[k][l]=max(dp1[k][l],cal(k,i,j));}//dp1转移
	for(int k=1;k<=n;k++)
		for(int i=0;i<=m;i++)
			for(int j=0;j<=a[k].size() && j<=i;j++)
				dp2[k][i]=max(dp2[k][i],dp2[k-1][i-j]+dp1[k][j]);//dp2转移
	cout<<dp2[n][m];
	return 0;
}
*/
