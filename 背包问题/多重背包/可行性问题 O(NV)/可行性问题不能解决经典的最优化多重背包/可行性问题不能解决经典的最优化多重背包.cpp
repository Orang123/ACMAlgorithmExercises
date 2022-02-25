//可行性问题O(nv)不能解决经典的最优化多重背包

/*
一点自己的理解
对完全背包来说这个物品数量因为是无限制的,因此能保证这样的背包容积升序转移
结果一定还是最优的.

但是多重背包这个物品数量在刚开始 包容积较小时物品数量还没到达上限,
如果持续放入第i个物品能够得到更优的解是正确的,但是一旦往后背包容积越大
dp[j]<dp[j-w[i]]+val[i]再次放入第i个物品本身是能更优的,但是现在你第i种
物品数量到达上限已经不能再放入了,也就是这个dp[j]你需要考虑前i种物品的dp[j-1]
和前i-1种物品的dp[j]到达哪个较优,但是即使这样做 仍然还是有问题,就总之本身01背包
的思维是背包容积降序,才能考虑全局最优,现在你明明并不是物品数量无线,结果你
假设它是无线,等真正需要考虑到并不把第i个物品放入很多件的时候,你已经把之前的
dp[0..j]前i-1种物品的状态改变了,对于一维数组就错了,但是搞成二维好像也还是错的.

知乎技工 网友的理解:
"除非你每个位置都额外开一维记录，否则就相当于“贪心”了"
leetcode 张晴川的理解:
"因为你不知道f[i][j-v]是不是已经用完了第i种物品.如果用完了,f[i][j]就不能从f[i][j-v]转移过来了."
*/
//下面是我自己二维数组的做法 这个只能水过AcWing那个多重背包的水题
//链接:https://www.acwing.com/problem/content/description/4/
//实际这个做法还是错的
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[N][M],sum[M];

int main(){
	int T;
	//scanf("%d",&T);
	//while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        for(int i=1;i<=n;i++){
            memset(sum,0,sizeof(sum));
            for(int j=0;j<=v;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=w[i];j<=v;j++){
                if(dp[i][j]<dp[i][j-w[i]]+val[i]){
                    if(sum[j-w[i]]+1<=num[i]){
                        dp[i][j]=dp[i][j-w[i]]+val[i];
                        sum[j]=sum[j-w[i]]+1;
                        //printf("dp[%d]+val[%d]=%d dp[%d]=%d sum[%d]=%d\n",j-w[i],i,dp[j-w[i]]+val[i],j,dp[j],j,sum[j]);
                    }
                    else{
                        if(dp[i-1][j-w[i]]+val[i]>max(dp[i][j],dp[i][j-1])){
                            dp[i][j]=dp[i-1][j-w[i]]+val[i];
                        }
                        else{

                        if(dp[i][j]<dp[i][j-1]){
                            dp[i][j]=dp[i][j-1];
                            sum[j]=sum[j-1];
                    //printf("dp[%d]+val[%d]=%d dp[%d]=%d sum[%d]=%d\n",j-w[i],i,dp[j-w[i]]+val[i],j,dp[j],j,sum[j]);
                        }
                        }
                    }
                }
            }
        }
        printf("%d\n",dp[n][v]);
    //}
    return 0;
}
