#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int dp[110][110],a[110];
/*
题意:乘法游戏是用一排牌玩的，每一张牌都包含一个正整数。在移动过程中，
玩家从一排牌中取出一张牌，得分等于所选牌上的数字与该牌左右两侧牌上数字的乘积。
不允许取出第一张和最后一张牌。最后一招过后，这一排只剩下两张牌。
每次取牌,保证了两侧都是有牌的.
注意:和HDU 5115 不同的是,纸牌需要留下第1张牌和最后一张牌,而HDU 5115狼是可以全部杀掉的
链接:http://poj.org/problem?id=1651
思路:第一次取的时候一定是原先的序列连续的三个数,所以最小的子状态就是连续的三个数取中间那个再相乘,
然后不断转移到大区间,枚举区间的分割点k,dp[i][j]=dp[i][k]+dp[k][j]+a[i]*a[k]*a[j],这里的k是之前子区间状态的边界点,
再和别的区间组合,其中dp[i][k]、dp[k][j]中间的数在上个长度len的枚举下已经被掏空,随着长度增加，数越来越少了.

此问题还可转化成矩阵连乘问题.
*/

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int l=2;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            dp[i][j]=INF;
            for(int k=i+1;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+a[i]*a[k]*a[j]);
            }
        }
    }
    printf("%d",dp[1][n]);
	return 0;
}
/*
区间dp 枚举左右端点转移
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int dp[110][110],a[110];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=n-2;i>=1;i--){
        for(int j=i+2;j<=n;j++){
            dp[i][j]=INF;
            for(int k=i+1;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+a[i]*a[k]*a[j]);
            }
        }
    }
    printf("%d",dp[1][n]);
	return 0;
}
*/
/*
记忆化搜索
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int dp[110][110],a[110];

int dfs(int st,int ed){
    if(ed-st==1) return 0;//最小子问题就是第一次取数连续的三个数,这里是连续的2个数返回0,上一级dfs里是连续的三个数
    if(dp[st][ed]!=INF) return dp[st][ed];
    for(int i=st+1;i<ed;i++)//首先分割大区间,那就优先递归解决小区间子问题
        dp[st][ed]=min(dp[st][ed],dfs(st,i)+dfs(i,ed)+a[st]*a[i]*a[ed]);
    return dp[st][ed];
}

int main(){
    int n;
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    printf("%d",dfs(1,n));
	return 0;
}
*/
