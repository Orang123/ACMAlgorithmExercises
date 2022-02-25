/*
假设F(n)为n列时的方案数
考察最后一列
如果最后一列为竖着放，则方案数为F(n-1)
如果最后一列是两个横着放，则方案数为F(n-2)
所以F(n)=F(n-1)+F(n-2)
显然，F(1) = 1，F(2) = 2
1,2,3,5,8,13,21,43,...
Fibonacci数
*/
#include<stdio.h>
void dp(long long *f)
{
    f[0]=1,f[1]=2;
    for(int i=2;i<50;i++)
        f[i]=f[i-1]+f[i-2];
}
int main()
{
    int n;
    long long f[50];
    dp(f);
    while(scanf("%d",&n)!=EOF)
        printf("%lld\n",f[n-1]);
        return 0;
}
