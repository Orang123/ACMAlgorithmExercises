/*
题意:给出T个数字,编号1~T,每个类型的数字有N[i]个.
输入数字的总个数为a.在这些数字中选出指定数量的集
合问有多少种方案,问集合个数在S~B之间的方案数总共有
多少.方案数可能会很大,只需保留结果的后6位数字即可.
T<=1000,N[i]<=100.
释义:有T个种类的蚂蚁family，下面给你a只蚂蚁，数字代表来自第几个family的，
求在这a只中取出x只组成长度大小在[s,b]之间的集合数量有多少个。 转化一下题意，
给你T种类型 a 个个体，从中任取 [s,b] 个组成的集合个数有多少个。
链接:http://poj.org/problem?id=3046
思路:实际就是求 指定个数不重复组合的方案个数,显然直接
把所有物品放到一起做01背包,相同的类型的数字有多个会导致
有重复的组合个数重复计数,会超出这种类型数字的上限.所以可采用分组背包计数,即相同
类型的数字作为一组,每组内的物品为这种类型数字的可能个数,
这样每次计数都是一次性地取第i类型的数字k个,而前面前i-1种
类型的数字中并不包括第i种类型的数字,就不会重复计数.
*/
//ac 282ms 分组背包统计方案数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 100100
#define mod 1000000
using namespace std;

int T,a,s,b,num[N],dp[M];

int main(){
    int x;
    memset(dp,0,sizeof(dp));
    memset(num,0,sizeof(dp));
    scanf("%d%d%d%d",&T,&a,&s,&b);
    for(int i=1;i<=a;i++){
        scanf("%d",&x);
        num[x]++;
    }
    dp[0]=1;
    for(int i=1;i<=T;i++){
        for(int j=a;j>=1;j--){
            for(int k=1;k<=num[i];k++)
                dp[j]=(dp[j]+dp[j-k])%mod;
        }
    }
    int ans=0;
    for(int i=s;i<=b;i++)
        ans=(ans+dp[i])%mod;
    printf("%d",ans);
    return 0;
}

/*
//ac 110ms 递推做法
//参考博客:https://blog.csdn.net/stay_accept/article/details/50118457
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdlib.h>
using namespace std;
const long long MOD=1000000;
long long dp[1005][100005];
long long num[1005];
int main(){
    long long T,A,S,B,i,j,x,ans;
    while(scanf("%I64d%I64d%I64d%I64d",&T,&A,&S,&B)!=EOF){
        memset(num,0,sizeof(num));
        for(i=0;i<A;i++){
            scanf("%I64d",&x);
            num[x-1]++;
        }                                               //定义dp[i][j]是从前i种物品中取出j个的组合总数
        for(i=0;i<=T;i++)                               //所以可以从前i-1中物品中取出j-k个，再从第i种物
        dp[i][0]=1;                                     //品种取出k个，可以推出递推关系式
        for(i=0;i<T;i++)                                //dp[i+1][j]=∑{k=0~min(j,a[i])}dp[i][j-k]可以展开
        for(j=1;j<=B;j++){                              //因此可以看出∑{k=0~min(j-1,a[i])}dp[i][j-1-k]相比
            if(j-1-num[i]>=0)                           //∑{k=0~min(j,a[i])}dp[i][j-k]差了一个dp[i][j]和
            dp[i+1][j]=(dp[i+1][j-1]+dp[i][j]-dp[i][j-1-num[i]]+MOD)%MOD;
            else                                        //dp[i][j-1-ai],又因为dp[i+1][j]=∑{k=0~min(j,a[i])}
            dp[i+1][j]=(dp[i+1][j-1]+dp[i][j])%MOD;     //dp[i][j-k]，所以∑{k=0~min(j-1,a[i])}dp[i][j-1-k]=
        }                                               //dp[i+1][j-1].所以可以推出优化后的递推式
        ans=0;                                          //dp[i+1][j]=dp[i+1][j-1]+dp[i][j]-dp[i][j-1-ai]
        for(j=S;j<=B;j++)
        ans=(ans+dp[T][j])%MOD;                         //从S到B加和并取余
        printf("%I64d\n",ans);
    }
    return 0;
}
*/

/*
//ac 0ms 类似多重背包的做法
//复杂度O(n^2)
参考博客:https://blog.csdn.net/sdj222555/article/details/10440021
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#define MAXN 111111
#define INF 1000000007
using namespace std;
int dp[2][MAXN], num[1111];
int sum[MAXN], up[1111];
int main()
{
    int T, S, A, B, x;
    scanf("%d%d%d%d", &T, &A, &S, &B);
    for(int i = 1; i <= A; i++)
    {
        scanf("%d", &x);
        num[x]++;
    }
    for(int i = 1; i <= T; i++)
        up[i] = up[i - 1] + num[i];
    dp[0][0] = 1;
    int *pre = dp[0], *nxt = dp[1];
    for(int i = 1; i <= T; i++)
    {
        sum[0] = pre[0];
        for(int j = 1; j <= up[i]; j++)
            sum[j] = (sum[j - 1] + pre[j]) % 1000000;
        for(int j = 0; j <= up[i]; j++)
        {
            int tmp = max(0, j - num[i]);
            nxt[j] = (tmp == 0 ? sum[j] : (sum[j] - sum[tmp - 1] + 1000000));
            nxt[j] %= 1000000;
        }
        swap(nxt, pre);
    }
    int ans = 0;
    for(int i = S; i <= B; i++)
        ans = (ans + pre[i]) % 1000000;
    printf("%d\n", ans);
    return 0;
}
*/
