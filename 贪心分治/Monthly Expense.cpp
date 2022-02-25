#include<stdio.h>
#define N 100010
int a[N],n,m;
void erfen(int left,int right)
{
    if(left==right)
    {
        printf("%d",right);
        return;
    }
    int cnt=0,sum=0,mid;
    mid=(left+right)/2;
    for(int i=0;i<n;i++)
    {
        sum+=a[i];
        if(sum>mid)//此时的sum中的各个a[i]可以构成一个预算段,其实mid我觉得应该只是一种衡量的标准
        {
            cnt++;
            sum=a[i];
        }
    }
    cnt++;//这里是把最后不够的那些份额也要构成一个预算段,因为会有不足的,但也要将其构成一个预算段虽然比其它预算段要小
    if(cnt<=m)
        erfen(left,mid);
    else
        erfen(mid+1,right);//这里mid+1主要是因为整型有些值除2两次的mid值一样会无限递归下去,浮点数的话就可以不考虑这种情况因为有精确位的保留
}
int main()
{
    int maxn=0,sum=0;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%d",a+i);
        if(maxn<a[i])
            maxn=a[i];
        sum+=a[i];
    }
    erfen(maxn,sum);
    return 0;
}
