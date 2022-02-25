/*
题意:
设sum(i)表示i的二进制表示中1的个数。给出一个正整数n，
花神要问你sum(1)*sum(2)*..*sum(n)是多少.
1<=n<=10^15.
链接:https://www.luogu.com.cn/problem/P4317
思路:求出二进制位进行数位dp.
*/
//ac 21ms 记忆化搜索
#include<cstdio>
#include<cstring>
#define N 64
#define mod 10000007
typedef long long ll;

int len,a[N];
ll n,dp[N][N];

ll dfs(int k,int num,int limit){
    if(!k)
        return num?num:1;
    if(!limit && dp[k][num]!=-1)
        return dp[k][num];
    int last=limit?a[k]:1;
    ll ans=1;
    for(int i=0;i<=last;i++)
        ans=(ans*dfs(k-1,num+i,limit && i == last))%mod;
    if(!limit)
        dp[k][num]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%2;
        val/=2;
    }
    return dfs(len,0,1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%lld",&n);
    printf("%lld",solve(n));
    return 0;
}
