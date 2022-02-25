#include<cstdio>
#include<algorithm>
using namespace std;
#define cal(y,x) (y-x)*(y-x)
/*
题意:有n件物品,每次搬一对物品,一共搬k次求min{sum(每次物品重量差的平方)}
思路:若a<b<c<d,4个物品取2对,则(b-a)^2+(d-c)^2是代价最小的,因此采取贪心策略,
先对物品按重量从小到大排序,再dp,这是一个类背包问题.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1421
*/
int dp[2005][1005];//dp[i][j]代表前i个物品取j对最小代价
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
                当i为奇数,此转移方程是正确的,当i为偶数j为i/2时,dp[i-1][j]前i-1个物品不能取i/2对物品这个值为0,由于求取的是min,所以取了0值
                因此状态转移完成后要对i特判,若为偶数则取i/2对的情况只能按顺序全取
                */
                dp[i][j]=min(dp[i-1][j],dp[i-2][j-1]+cal(a[i],a[i-1]));
            }
            if(~i&1)//若i为偶数
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
                dp[i][j]=min(dp[i-1][j],dp[i-2][j-1]+(w[i-1]-w[i-2])*(w[i-1]-w[i-2])); //从i件物品中选j对
        printf("%d\n",dp[n][k]);
    }
    return 0;
}*/
