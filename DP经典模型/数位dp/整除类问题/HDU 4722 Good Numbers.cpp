/*
题意:摘自网上
假设一个数每位数上之和能被10整除，称这个数为好数，给定两个数A,B，
求在这个范围[A,B]内的好数.
A,B<=10^18.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4722
思路:数位dp.
dp[k][mod]表示数位从len到k-1位数位之和对10取模为mod,
(从右至左计算数位下标)再从k位到末尾这部分能构成的所有
不超过原始n的数位串累加数位满足能整除10的数字个数.
*/
//ac 31ms 记忆化搜索
//dp[k][mod]表示数位从len到k-1位数位之和对10取模为mod,(从右至左计算数位下标)再从k位到末尾这部分能构成的所有不超过原始n的数位串累加数位
//满足能整除10的数字个数
#include<cstdio>
#include<cstring>
#define N 20
typedef long long ll;

int len,a[N];
ll A,B,dp[N][10];

ll dfs(int k,int mod,int limit){
    if(!k)
        return mod == 0;
    if(!limit && dp[k][mod]!=-1)
        return dp[k][mod];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,(mod+i)%10,limit && i == last);
    if(!limit)
        dp[k][mod]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,1);
}

int main(){
    int T,cas=0;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%lld%lld",&A,&B);
        printf("Case #%d: %lld\n",cas,solve(B)-solve(A-1));
    }
    return 0;
}
