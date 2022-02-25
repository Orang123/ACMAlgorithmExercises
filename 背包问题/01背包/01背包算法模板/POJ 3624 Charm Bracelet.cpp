#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3500
#define M 13000
using namespace std;
//ac 266ms 01背包裸题
/*
题意:01背包裸题
链接:http://poj.org/problem?id=3624
思路:01背包裸题
*/

int n,v,w[N],val[N],dp[M];
int main(){
    memset(dp,0,sizeof(dp));//尽可能装满背包,初始化为0
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&w[i],&val[i]);
    for(int i=1;i<=n;i++)
        //这里逆序是因为正序会导致j在较小时dp[j]更新后,当j较大时,更新dp[j]=dp[j-w[i]]+val[i]会把之前较小的j的值重复累加,即第i件物品重复选取,显然是错的
        //而逆序刚开始更新的是较大的j,j是不断减少的,dp[j-w[i]]永远是没有更新过的,所以正确
        for(int j=v;j>=w[i];j--)
            dp[j]=max(dp[j],dp[j-w[i]]+val[i]);//dp[j]代表dp[i-1][j],dp[j-w[i]]代表dp[i-1][j-w[i]]
    printf("%d",dp[v]);
    return 0;
}
