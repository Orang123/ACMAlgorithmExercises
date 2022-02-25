/*
题意:给定一个n,只允许使用2的幂次数,问有多少种不同的方案组成n.
链接:http://poj.org/problem?id=2229
思路:完全背包
*/
//ac 422ms 完全背包统计方案数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 21
#define M 1000010
#define mod 1000000000
typedef long long ll;
using namespace std;

int n,val[N],dp[M];

int main(){
    val[0]=1;
    //n最大只有10^6,而2的20次方为1048576 按道理只需计算到2的19次方,但是只算到2^19次方会wa,所以推断n可能大于10^6
    for(int i=1;i<N;i++)
        val[i]=val[i-1]*2;
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    for(int i=0;val[i]<=n;i++){
        for(int j=val[i];j<=n;j++){
            dp[j]+=dp[j-val[i]];
            if(dp[j]>mod)//直接取模复杂度太大,超出时减少mod就好
                dp[j]-=mod;
        }
    }
    printf("%d\n",dp[n]);
    return 0;
}
