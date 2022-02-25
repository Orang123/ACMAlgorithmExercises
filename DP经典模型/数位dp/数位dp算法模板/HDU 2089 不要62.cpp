/*
题意:统计区间 [n,m] 中不含4和62的数字有多少个。
n,m<=10^6.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2089
思路:经典数位dp.
分别统计出0~m和0~n-1的不含4和62的个数作差即可,dp数组
可以只初始化一次,因为第二次dfs可以用第一次dfs记忆化的dp值降低复杂度.
*/
//ac 0ms 记忆化搜索
//dp[k][pre]表示n的数位从k到末尾(从右至左计算数位下标)这部分能构成的所有不超过原始n的数字串满足不出现“4”和"62"的数字串的个数
//pre == 0表示上一位不是6
//pre == 1表示上一位是6
//空间复杂度O(8*2)=16
//时间复杂度O(10*8*2)=160
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 8
using namespace std;

int n,m,len,a[N],dp[N][2];

int dfs(int k,int pre,int limit){
    if(!k)
        return 1;
    if(!limit && dp[k][pre]!=-1)
        return dp[k][pre];
    int last=limit?a[k]:9,ans=0;
    for(int i=0;i<=last;i++){
        if(i == 4 || (pre == 1 && i == 2)) continue;
        ans+=dfs(k-1,i == 6,limit && i == last);
    }
    //如果只初始化一次dp数组,这里就要加上!limit
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,1);
}

int main(){
    memset(dp,-1,sizeof(dp));//dp数组只用初始化一次
    while(scanf("%d%d",&n,&m) && n+m){
        len=0;
        //这里计算了两次dfs,但是dp只初始化了一次,第一次对m的dfs的dp值,同样适用于第二次对n-1的dfs,
        printf("%d\n",solve(m)-solve(n-1));
    }
    return 0;
}

/*
//ac 46ms 暴力做法O(n)遍历 统计区间数是不出现4和62的个数
//摘自博客:https://www.cnblogs.com/2000liuwei/p/10604834.html
#include<string.h>
#include<stdio.h>
int d[1000010];
int c[10];
int e[1000010];
int main()
{
    int a,b,ans=0;
    memset(e,0,sizeof(d));
    for(int i=1;i<1000000;i++)
    {
        int flag=0;
        memset(c,0,sizeof(c));
        c[1]=i/100000;
        c[2]=i%100000/10000;
        c[3]=i%10000/1000;
        c[4]=i%1000/100;
        c[5]=i%100/10;
        c[6]=i%10;
        for(int j=1;j<=6;j++)
        {
           if(c[j]==4)
           {
               flag=1;
           break;
    }
           if(c[j]==6&&c[j+1]==2)
           {
               flag=1;
           break;
    }
        }
        if(!flag)
        ans++;
        d[i]=ans;
    }
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        if(a==0&&b==0)break;
        printf("%d\n",d[b]-d[a-1]);
    }
    return 0;
}
*/

/*
//ac 15ms 正向递推 没怎么看
//摘自博客:https://www.cnblogs.com/wenruo/p/4725005.html
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int dp[10][10];
int d[10];

void init()
{
    dp[0][0] = 1;
    for (int i = 1; i <= 7; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = 0; k <= 9; ++k)
                if (j != 4 && !(j == 6 && k == 2))
                    dp[i][j] += dp[i - 1][k];
}

int solve(int n)
{
    int ans = 0;
    int len = 0;
    while (n) {
        ++len;
        d[len] = n % 10;
        n /= 10;
    }
    d[len + 1] = 0;
    for (int i = len; i >= 1; --i) {
        for (int j = 0; j < d[i]; ++j) {
            if (d[i + 1] != 6 || j != 2)
                ans += dp[i][j];
        }
        if (d[i] == 4 || (d[i + 1] == 6 && d[i] == 2))
            break;
    }
    return ans;
}

int main()
{
    int m, n;
    init();
    while (scanf("%d%d", &m, &n) == 2) {
        if (n == 0 && m == 0) break;
        printf("%d\n", solve(n + 1) - solve(m));
    }
    return 0;
}
*/

/*
//ac 187ms dfs暴力 不对重叠子问题标记,数据量太小
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 8
using namespace std;

int n,m,len,a[N],dp[N][2];

int dfs(int k,int pre,int limit){
    if(!k)
        return 1;
    //if(!limit && dp[k][pre]!=-1)
        //return dp[k][pre];
    int last=limit?a[k]:9,ans=0;
    for(int i=0;i<=last;i++){
        if(i == 4 || (pre == 1 && i == 2)) continue;
        ans+=dfs(k-1,i == 6,limit && i == last);
    }
    //如果只初始化一次dp数组,这里就要加上!limit
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,1);
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        len=0;
        memset(dp,-1,sizeof(dp));
        //这里计算了两次dfs,但是dp只初始化了一次,第一次对m的dfs的dp值,同样适用于第二次对n-1的dfs,
        printf("%d\n",solve(m)-solve(n-1));
    }
    return 0;
}
*/


