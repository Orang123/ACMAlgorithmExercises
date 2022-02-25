#include<stdio.h>
int main()
{
    int dp[31]={0},n;
    dp[0]=1,dp[2]=3;
    for(int i=4;i<31;i+=2)
        dp[i]=4*dp[i-2]-dp[i-4];
    while(scanf("%d",&n),n!=-1)
        printf("%d\n",dp[n]);
    return 0;
}
