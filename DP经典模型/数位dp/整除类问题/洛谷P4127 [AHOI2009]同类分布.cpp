/*
题意:
给出两个数l,r,求出[l,r]中各位数字之和能整除原数的数的个数.
1<=l,r<=10^18.
链接:https://www.luogu.com.cn/problem/P4127
思路:因为枚举数位的过程中,各数位之和是不断变化的,因此需要枚举
各个可能的数位之和再进行数位dp.要注意每次数位dp都是针对一个确定
好的数位之和mod,不同数位dp 数位之和mod是不同的,因此每次都需要初始化dp数组.
*/
//ac 3.37s 记忆化搜索
#include<cstdio>
#include<cstring>
#define N 20
#define M 171//19*9
typedef long long ll;

int len,a[N],mod;
ll l,r,dp[N][M][M];

ll dfs(int k,int sum1,int sum2,int limit){
    if(!k)
        return sum1 == mod && !sum2;
    if(!limit && dp[k][sum1][sum2]!=-1)
        return dp[k][sum1][sum2];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,sum1+i,(sum2*10+i)%mod,limit && i == last);
    if(!limit)
        dp[k][sum1][sum2]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    ll ans=0;
    int sum=len*9;//确定数位之和的最大值,如果比实际val大,dfs返回的结果也为0,不影响
    for(mod=1;mod<=sum;mod++){
        memset(dp,-1,sizeof(dp));//每次dp mod不同,因此要初始化dp数组
        ans+=dfs(len,0,0,1);
    }
    return ans;
}

int main(){
    scanf("%lld%lld",&l,&r);
    printf("%lld",solve(r)-solve(l-1));
    return 0;
}
