#include<stdio.h>
#define Pi 3.1415926535898
#define EPS 1e-4
int main()
{
    int k,n,f,sum;
    double a[10000];
    scanf("%d",&k);
    while(k--)
    {
        double low=0.0,high=0.0,mid;
        scanf("%d%d",&n,&f);
        for(int i=0;i<n;i++)
        {
            scanf("%lf",a+i);
            a[i]*=a[i];
            if(a[i]>high)
                high=a[i];
        }
     mid=(low+high)/2;
     while(high-low>EPS)
     {
         sum=0;
         mid=(low+high)/2;
         for(int i=0;i<n;i++)
             sum+=(int)(a[i]/mid);
         if(sum<f+1)
            high=mid;
         else
            low=mid;
     }
     printf("%.4f\n",mid*Pi);
    }
    return 0;
}
