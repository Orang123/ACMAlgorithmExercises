#include<cstdio>
#include<algorithm>
using namespace std;
#define cal(y,x) (y-x)*(y-x)
/*
����:��n����Ʒ,ÿ�ΰ�һ����Ʒ,һ����k����min{sum(ÿ����Ʒ�������ƽ��)}
˼·:��a<b<c<d,4����Ʒȡ2��,��(b-a)^2+(d-c)^2�Ǵ�����С��,��˲�ȡ̰�Ĳ���,
�ȶ���Ʒ��������С��������,��dp,����һ���౳������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1421
*/
int dp[2005][1005];//dp[i][j]����ǰi����Ʒȡj����С����
int main()
{
    int n,k,a[2005];
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        for(int i=1; i<=n; i++)
            scanf("%d",a+i);
        sort(a+1,a+n+1);
        dp[2][1]=cal(a[2],a[1]);
        for(int i=3,j; i<=n; i++)
        {
            for(j=1; j<=k&&j<=i/2; j++)
            {
                /*
                ��iΪ����,��ת�Ʒ�������ȷ��,��iΪż��jΪi/2ʱ,dp[i-1][j]ǰi-1����Ʒ����ȡi/2����Ʒ���ֵΪ0,������ȡ����min,����ȡ��0ֵ
                ���״̬ת����ɺ�Ҫ��i����,��Ϊż����ȡi/2�Ե����ֻ�ܰ�˳��ȫȡ
                */
                dp[i][j]=min(dp[i-1][j],dp[i-2][j-1]+cal(a[i],a[i-1]));
            }
            if(~i&1)//��iΪż��
                dp[i][i>>1]=dp[i-2][(i>>1)-1]+cal(a[i],a[i-1]);
        }
        printf("%d\n",dp[n][k]);
    }
    return 0;
}
/*
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[2002][1002];
int main()
{
    int w[2002];
    int n,k;
    int i,j;
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        for(i=0;i<n;i++)
            scanf("%d",&w[i]);
        sort(w,w+n);
        for(i=0;i<=n;i++)
            for(j=1;j<=k;j++)
                dp[i][j]=0xfffffff;
        for(i=2;i<=n;i++)
            for(j=1;j<=i/2&&j<=k;j++)
                dp[i][j]=min(dp[i-1][j],dp[i-2][j-1]+(w[i-1]-w[i-2])*(w[i-1]-w[i-2])); //��i����Ʒ��ѡj��
        printf("%d\n",dp[n][k]);
    }
    return 0;
}*/
