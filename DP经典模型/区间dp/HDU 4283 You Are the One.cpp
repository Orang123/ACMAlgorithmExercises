#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:一排男孩上台表演,每个男孩有个屌丝值D,对于一个男孩如果是第k个上台,则它的不快乐度就是(k-1)*D,
现在有一个栈可以调整男孩上台的次序,栈满足后进入的男孩先上台,男孩入栈的顺序是连续的一排男孩同时入栈.
问最小的不快乐度是多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4283
对于1,2,3若想让3第一个上场,则按照1,2,3顺序入栈,则上场的顺序为3,2,1,最后入栈的3第一个出栈.
dp[i][j]代表i~j个人上场的最小不开心度和,对于[i,j]中第i个人上场的顺序可以为1~j-i+1,若第i个人
是第k个上场的,则在它后面相邻的k-1个人一定比它先上场,因为i一定是第一个入栈,最后一个上场的.
*/

int dp[110][110],a[110],sum[110];

int main(){
    int T,n,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum[i]=sum[i-1]+a[i];//屌丝值的前缀和
        }
        for(int l=1;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=INF;
                //枚举第i个人可能第几个上场1~(l+1)
                for(int k=1;k<=l+1;k++)
                    /*
                    若第i个人是第k个上场的,则不开心度为(k-1)*a[i],他后面k-1个人[i+1,i+k-1]中的人上场的顺序则为1~(k-1),
                    需要再加上dp[i+1][i+k-1]的不开心度,然后对于[i+k,j]即前k个人后面的j-i-k+1个人的不开心度需要在原先
                    dp[i+k][j],原先上场的顺序为1~(j-i-k+1),而现在上场的顺序为k+1~j-i+1,上场的顺序向后移动了k个位置,所以需要
                    再加上k个原先的屌丝值,即:k*(sum[j]-sum[i+k-1]).
                    对于第i个人按照本身的顺序第1个上场,此时dp[i+1][i+k-1]=dp[i+1][i]=0,后面的j-i个人上场的顺序为2~j-i+1,
                    对于第i个人若是第l+1(j-i+1)个上场,则dp[i+k][j]=dp[i+l+1][j]=dp[i+j-i+1][j]=dp[j+1][j]=0,sum[i+k-1]=sum[i+j-i+1-1]=sum[j]
                    */
                    dp[i][j]=min(dp[i][j],dp[i+1][i+k-1]+(k-1)*a[i]+dp[i+k][j]+k*(sum[j]-sum[i+k-1]));
            }
        }
        printf("Case #%d: %d\n",cas,dp[1][n]);
    }
    return 0;
}
