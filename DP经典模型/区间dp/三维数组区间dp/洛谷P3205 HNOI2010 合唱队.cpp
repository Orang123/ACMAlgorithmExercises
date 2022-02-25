#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 19650827
using namespace std;

/*
链接:https://www.luogu.com.cn/problem/P3205
题意:给定一串序列，问有多少种初始序列经过如题操作可以得到此序列。
思路:
dp[i][j][0]代表排在第i位的人是从之前的队列[i+1,j]左边插入的方案数 第i位的上一位只能是i+1或j位
dp[i][j][1]代表排在第j位的人是从之前的队列[i,j-1]右边插入的方案数 第j位的上一位只能是i或j-1位
案例:对于理想队列 1 2 3 4共有8种初始队列
{1,2,3,4} {4,3,2,1} {3,4,2,1} {2,1,3,4} {3,2,1,4} {3,2,4,1} {2,3,1,4} {2,3,4,1}
*/

int dp[1100][1100][2],a[1100],n;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)//初始状态排第一个人时,部分左右,只记录它是从左侧进入,左右两侧都记录结果会偏大
        dp[i][i][0]=1;
    for(int l=1;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            //排在最左端的数的上一位排在第i+1位,且a[i]<a[i+1] 累加上之前的方案
            if(a[i]<a[i+1]) dp[i][j][0]+=dp[i+1][j][0];
            if(a[i]<a[j]) dp[i][j][0]+=dp[i+1][j][1];
            //排在最右端的数的上一位排在第i位,且a[j]>a[i]
            if(a[j]>a[i]) dp[i][j][1]+=dp[i][j-1][0];
            if(a[j]>a[j-1]) dp[i][j][1]+=dp[i][j-1][1];
            dp[i][j][0]%=mod;
            dp[i][j][1]%=mod;
        }
    }
    printf("%d",(dp[1][n][0]+dp[1][n][1])%mod);
    return 0;
}
