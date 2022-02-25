/*
����F(n)Ϊn��ʱ�ķ�����
�������һ��
������һ��Ϊ���ŷţ��򷽰���ΪF(n-1)
������һ�����������ŷţ��򷽰���ΪF(n-2)
����F(n)=F(n-1)+F(n-2)
��Ȼ��F(1) = 1��F(2) = 2
1,2,3,5,8,13,21,43,...
Fibonacci��
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
