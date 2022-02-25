/*
题意:在一个国家仅有1分,2分,3分硬币,将钱N兑换成硬币有很多种兑法.
请你编程序计算出共有多少种兑法.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1284
思路:每个硬币可以兑换多次,因此是完全背包问题,因为是恰好装满的
方案数,所以状态转移方程dp[j]+=dp[j-val[i]],dp[0]=1;
*/
#include<bits/stdc++.h>
#define N 32780
using namespace std;
int v,val[4]={0,1,2,3},dp[N];
int main(){
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    //先枚举物品种类,后枚举背包容量,只能求出不同组合的个数,不能求出相同组合不同顺序的个数
    for(int i=1;i<=3;i++)
        for(int j=val[i];j<N;j++)
            dp[j]+=dp[j-val[i]];
    /*
    //先枚举背包容量 后枚举物品种类,这样就能考虑所有顺序不同的所有组合的个数
    //详情leetcode 377. 组合总和 Ⅳ https://leetcode-cn.com/problems/combination-sum-iv/
    for(int j=0;j<=N;j++){
        for(int i=1;i<=3;i++){
            if(j>=val[i])
                dp[j]+=dp[j-val[i]];
        }
    }
    */
    while(scanf("%d",&v)!=EOF)
        printf("%d\n",dp[v]);
    return 0;
}

/*
//ac 109ms 一维数组实现完全背包统计方案数
#include<bits/stdc++.h>
#define N 32780
using namespace std;
int v,val[4]={0,1,2,3},dp[N];
int main(){
    while(scanf("%d",&v)!=EOF){
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        for(int i=1;i<=3;i++)
            for(int j=val[i];j<=v;j++)
                dp[j]+=dp[j-val[i]];
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 234ms 二维数组实现
#include<bits/stdc++.h>
#define N 4
#define M 32780
using namespace std;
int v,val[N]={0,1,2,3},dp[N][M];
int main(){
    while(scanf("%d",&v)!=EOF){
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=1;i<=3;i++){
            for(int j=0;j<=v;j++){
                if(j>=val[i])//注意这里是在前i种物品基础上累加第i种物品 即:dp[i][j-val[i]]
                    dp[i][j]=dp[i-1][j]+dp[i][j-val[i]];
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%d\n",dp[3][v]);
    }
    return 0;
}
*/

/*
暴力搜索枚举,这个做法是错的,有些方案本身是重复的.
void dfs(int sum){
    if(sum>v)
        return;
    if(sum == v)
        ans++;
    ans[sum]++;
    dfs(sum+1);
    dfs(sum+2);
    dfs(sum+3);
}
*/

/*
bfs枚举状态进行转移,也会出现某些重复的方案,会错.
*/

/*
//ac 390ms 母函数做法
//摘自博客:https://www.cnblogs.com/Taskr212/p/9561041.html
#include <bits/stdc++.h>
using namespace std;
const int maxn = 32769;
int n,ans[maxn],tans[maxn];
void init()
{
    for(int i = 0; i < maxn; ++i)
    {
        ans[i] = 1;
        tans[i] = 0;
    }
    for(int i = 2; i <= 3; ++i)
    {
        for(int j = 0; j < maxn; ++j)
            for(int k = 0; j+k < maxn; k+=i)
                tans[j+k]+=ans[j];
        for(int j = 0; j < maxn; ++j)
        {
            ans[j] = tans[j];
            tans[j] = 0;
        }
    }
}
int main()
{
    init();
    while(~scanf("%d",&n))
        printf("%d\n",ans[n]);
    return 0;
}
*/
