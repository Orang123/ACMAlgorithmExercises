/*
题意:有m元,有n种礼物,给出每种礼物的价格w[i],买x个第i种礼物则会
获得a[i]*x+b[i]个糖,问怎么买能使获得的糖最多.
n<=1000,m<=2000,w[i]<=2000
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5410
思路:首先购买每种礼物获得的糖果是:a[i]*x+b[i],可以看到对于
b[i]这个参数实际只有这种礼物买与不买,而a[i]是买几个这种礼物,
就会有几个a[i],那么对于b[i]实际是01背包,而a[i]是完全背包只要不断
累加即可.因此对于第i种礼物先判断买与不买即dp[j]=max(dp[j],dp[j-w[i]]+a[i]+b[i]);
而具体第i种物品是否还要继续买转移是dp[j]=max(dp[j],dp[j-w[i]]+a[i]);只是不断累加a[i]
这里如果第i种礼物没买,那么后续的完全背包自然最优解也是没买的,
如果第i种礼物买了一个后,会继续决策是否继续买能获得更优解.
*/
//ac 93ms 01背包+完全背包
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 2100
typedef long long ll;
using namespace std;

int n,m,w[N],a[N],b[N];
ll dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&a[i],&b[i]);
        for(int i=1;i<=n;i++){
            //这里先进行01背包还是完全背包顺序 并不影响最优解
            for(int j=m;j>=w[i];j--)//01背包
                dp[j]=max(dp[j],dp[j-w[i]]+a[i]+b[i]);
            for(int j=w[i];j<=m;j++)//完全背包
                dp[j]=max(dp[j],dp[j-w[i]]+a[i]);
        }
        printf("%lld\n",dp[m]);
    }
    return 0;
}

/*
//ac 78ms 01背包+完全背包
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 2100
typedef long long ll;
using namespace std;

int n,m,w[N],a[N],b[N];
ll dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&a[i],&b[i]);
        for(int i=1;i<=n;i++){
            for(int j=m;j>=w[i];j--)
                dp[j]=max(dp[j],dp[j-w[i]]+a[i]+b[i]);
        }
        for(int i=1;i<=n;i++){
            for(int j=w[i];j<=m;j++)
                dp[j]=max(dp[j],dp[j-w[i]]+a[i]);
        }
        printf("%lld\n",dp[m]);
    }
    return 0;
}
*/

/*
物品个数最大可达1000,背包容量最大2000,
如果dfs搜索的深度会很深,肯定tle
*/
