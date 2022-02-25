/*
题意:
如果一个整数各个位上的数字之和能被3整除，那么这个整数本身也能被3整除。
在这个问题中，我们要把这个性质推广到其它数上。
给定A,B,K，请问在[A,B]中，有多少个整数本身能被K整除，并且各个位上数字之和也能被K整除？
A,B<2^31.K<10000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2346
思路:数位dp.
*/
//ac 420ms 记忆化搜索
#include<cstdio>
#include<cstring>
#define N 11
#define M 10000

int len,a[N];
int A,B,K,dp[N][100][M];

int dfs(int k,int mod1,int mod2,int limit){
    if(!k)
        return !mod1 && !mod2;
    if(!limit && dp[k][mod1][mod2]!=-1)
        return dp[k][mod1][mod2];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,(mod1+i)%K,(mod2*10+i)%K,limit && i == last);
    if(!limit)
        dp[k][mod1][mod2]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,0,1);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&A,&B,&K);
        if(K>82)//2^31次方以内最大的数位和为1999999999,9*9+1=82,如果K>82,则各位之和取模结果一定不会为0
            printf("0\n");
        else{
            memset(dp,-1,sizeof(dp));
            printf("%d\n",solve(B)-solve(A-1));
        }
    }
    return 0;
}

/*
//ac 70ms 递推
//摘自博客:https://blog.csdn.net/keshuai19940722/article/details/26164549
//数位dp，dp[i][j][x]表示第i为的时候，n整除k余j，n（以及考虑到的位数）的各个位置
//上的数字之和整除k余x的情况总数，并且每次要计算上限的临界值。
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 15;
const int M = 105;

int a, b, k, n, d[N];
int dp[N][M][M];

void cat(int u) {
    n = 1;
    memset(d, 0, sizeof(d));
    while (u) {
        d[n++] = u%10;
        u /= 10;
    }

    for (int i = 1; i <= n/2; i++)
        swap(d[i], d[n-i+1]);
}

int solve (int u) {
    if (u == 0)
        return 1;

    cat(u);
    memset(dp, 0, sizeof(dp));
    int p = 0, q = 0;

    for (int i = 1; i <= n; i++) {

        for (int j = 0; j <= k; j++) {
            for (int t = 0; t <= k; t++) {

                for (int x = 0; x < 10; x++)
                    dp[i][(j*10+x)%k][(t+x)%k] += dp[i-1][j][t];
            }
        }

        for (int j = 0; j < d[i]; j++)
            dp[i][(p*10+j)%k][(q + j)%k]++;

        p = (p*10+d[i])%k;
        q = (q+d[i])%k;
    }

    if (p == 0 && q == 0)
        dp[n][0][0]++;
    return dp[n][0][0];
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d%d", &a, &b, &k);
        if (k > 100)
            printf("0\n");
        else
            printf("%d\n", solve(b) - solve(a-1));
    }
    return 0;
}
*/
