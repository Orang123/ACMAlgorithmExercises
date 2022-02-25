/*
题意:摘自网上
给你n*n的矩阵，a[i][j]代表第i个男人和第j个女人之间的满意度，
求男女一一配对后，最大的满意度之和。
n<=16.
链接:http://lightoj.com/volume_showproblem.php?problem=1011
思路:实际这个问题就是弱化版的八皇后,求取行列之间的匹配,取n个
不同行不同列的位置,要求权值和最大.但是若八皇后暴力回溯求解复杂度最大可达16!.
方法1:KM算法求取最优匹配,行和列匹配,复杂度O(n^3)=16^3=4096
方法2:因为n<=16,很小可以状压.可以在八皇后求解问题基础上对还未选取的列做一个
状态压缩,dp[sta]表示为选取列的状态为sta时能获得大最大满意度,这样在枚举列时
对于重叠子问题就可常数时间返回结果,大大缩减了时间复杂度,时间复杂度可达O(1<<16)=65536
*/
//ac 182ms 记忆化搜索+状压
//dp[sta]表示为选取列的状态为sta时能获得大最大满意度
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 16
using namespace std;

int n,a[N][N],dp[1<<16];

int dfs(int sta,int row){
    int &res=dp[sta];
    if(res)
        return res;
    if(!sta)//所有列都选取完
        return 0;
    for(int i=0;i<n;i++){
        if(sta & 1<<i)//第i列还未选取
            res=max(res,dfs(sta ^ 1<<i,row+1)+a[row][i]);//row+1 判断下一行
    }
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                scanf("%d",&a[i][j]);
        }
        printf("Case %d: %d\n",i,dfs((1<<n)-1,0));//初始未选取的列有n个
    }
    return 0;
}

/*
//TLE 八皇后模拟暴力回溯
//摘自博客:https://blog.csdn.net/qq_34374664/article/details/54586529
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 20;
int dp[maxn][maxn], book[maxn], max1, n;
void dfs(int i, int ans)
{
    if(i == n+1)
    {
        if(ans > max1) max1 = ans;
        return;
    }
    for(int j = 1; j <= n; j++)
    {
        if(book[j])
            continue;
        book[j] = 1;
        ans += dp[i][j];
        dfs(i+1, ans);
        book[j] = 0;
        ans -= dp[i][j];
    }
}
int main()
{
    int t, ca = 1;
    scanf("%d", &t);
    while(t--)
    {
        memset(book, 0, sizeof(book));
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &dp[i][j]);
        max1 = -1;
        dfs(1,0);
        printf("Case %d: %d\n",ca++, max1);

    }
    return 0;
}
*/

/*
//ac 567ms 正向dp
//摘自博客:https://www.cnblogs.com/wangzhili/p/3950255.html
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 16;
int dp[MAXN][1 << MAXN], mat[MAXN][MAXN];
int main(){
    int t, n, CASE(0);
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i = 0;i < n;i ++){
            for(int j = 0;j < n;j ++) scanf("%d", &mat[i][j]);
        }
        int len = (1 << n);
        memset(dp, 0, sizeof dp);
        for(int i = 0;i  < n; i ++) dp[0][1 << i] = mat[0][i];
        for(int i = 1;i < n;i ++){
            for(int j = 0;j < n;j ++){
                for(int k = 0;k < len;k ++){
                    if(!dp[i-1][k] || (1 << j) & k) continue;
                    dp[i][k|(1 << j)] = max(dp[i][k|(1 << j)], dp[i-1][k]+mat[i][j]);
                }
            }
        }
        printf("Case %d: %d\n", ++CASE, dp[n-1][len-1]);
    }
    return 0;
}
*/
