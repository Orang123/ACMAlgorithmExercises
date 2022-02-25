/*
题意:一个小偷,它的背包能拿k个物品,商店有n种物品,每种物品都有无限多个.
每种物品价值是a[i],现在要求出小偷可能偷走的物品价值之和的所有情况并输出.
1<=n,k<=1000,1<=a[i]<=1000
链接:http://codeforces.com/contest/632/problem/E
思路:直接用二维费用指定物品个数的价值之和肯定会mle,tle,背包容量最大可达10^6,
n*k最大10^6,总复杂度O(10^12)显然不可行.可以考虑将物品排序,把除第一个最小物品
外的其它物品价值都减去这个物品的价值,用编号为2~n的物品做完全背包,dp[j]=i表示
得到物品价值总和为j时最少要偷的物品个数.最后判断只要dp[j]<=k,则实际偷得的物品价值
为j+a[i]*k,这个结果可以这么理解,分为两部分,首先这些价值里是没有含第一个最小的物品
的,而现在dp[j]偷得的物品数小于k,那么就想办法来补一些物品是其达到k个物品,原先偷得的
那些物品价值都少加了个第一个物品的价值,这些部分要全部补上a[1],总共是dp[j]个物品,剩下
k-dp[j]个物品是单纯没有选第一个物品,把剩下的物品全部选成第一个物品,这样就凑出了k个物品,
而真实获得的价值和为j+a[1]*k.如果dp[j]刚好等于k,那实际这些物品的价值和只要把原先每个物品
缺少的a[1]补齐就好,所以价值仍旧是j+a[1]*k.
*/
//ac 545ms 完全背包
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000100
#define INF 0x3f3f3f3f
using namespace std;

int n,k,a[N],dp[M],sum;

int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(int i=2;i<=n;i++)
        a[i]-=a[1];
    dp[0]=0;
    for(int i=2;i<=n;i++){
        //dp每个阶段的背包容量是递增的,第i个阶段背包容量为只选k个第i种物品的价值和
        sum=a[i]*k;
        for(int j=a[i];j<=sum;j++)
            dp[j]=min(dp[j],dp[j-a[i]]+1);
    }
    sum=a[n]*k;
    //这里下界是0,
    for(int i=0;i<=sum;i++){
        if(dp[i]<=k)
            printf("%d ",i+a[1]*k);
    }
    return 0;
}

/*
//二维费用完全背包 TLE MLE
//dp[k][j]=1代表选k个物品构成价值为j的这种情况是存在的
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;

int n,k,a[N],dp[N][M],sum;

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    dp[0][0]=1;//初始状态
    for(int i=1;i<=n;i++){
    	sum=a[i]*k;
        for(int j=a[i];j<=sum;j++){//完全背包这里背包容量是升序
        	for(int t=1;t<=k;t++)//这里升序 降序都可以
            	if(dp[t-1][j-a[i]])//上一个状态合法 才可以转移,否则标记好的合法状态会更新成不合法的
                	dp[t][j]=dp[t-1][j-a[i]];
		}
    }
    //选物品个数和背包容量可以颠倒循环
    //for(int i=1;i<=n;i++){
        //for(int t=1;t<=k;t++){//完全背包这里背包容量是升序
    		//sum=a[i]*t;
        	//for(int j=a[i];j<=sum;j++){//完这里升序、降序都可
            	//if(dp[t-1][j-a[i]])//上一个状态合法 才可以转移,否则标记好的合法状态会更新成不合法的
                	//dp[t][j]=dp[t-1][j-a[i]];
			//}
		//}
    //}
    sum=a[n]*k;
    //遍历选k个物品下 物品价值和哪些情况是存在
    for(int i=1;i<=sum;i++){
        if(dp[k][i])
            printf("%d ",i);
    }
    return 0;
}
*/

/*
//ac 1294ms 生成函数做法
//摘自博客:https://www.cnblogs.com/Memory-of-winter/p/9718254.html
#include <cstdio>
#include <algorithm>
#define maxn 1 << 20 | 3
const int G = 3;
int mod, ans;
int lim, ilim, s, rev[maxn], Wn[maxn];
inline int pw(int base, long long p) {
    base %= mod, p %= mod - 1;
    int ans = 1;
    for (; p; p >>= 1, base = 1ll * base * base % mod) if (p & 1) ans = 1ll * ans * base % mod;
    return ans;
}
inline int Inv(int x) {
    return pw(x, mod - 2);
}
inline void up(int &a, int b) {if ((a += b) >= mod) a -= mod;}
inline void NTT(int *A, int op) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        int t = lim / mid >> 1;
        for (int i = 0; i < lim; i += mid << 1) {
            for (int j = 0; j < mid; j++) {
                int W = op ? Wn[t * j] : Wn[lim - t * j];
                int X = A[i + j], Y = 1ll * A[i + j + mid] * W % mod;
                up(A[i + j], Y), up(A[i + j + mid] = X, mod - Y);
            }
        }
    }
    if (!op) for (int i = 0; i < lim; i++) A[i] = 1ll * A[i] * ilim % mod;
}
inline void init(int n, int mod) {
    ::mod = mod;
    lim = 1, s = -1; while (lim < n) lim <<= 1, s++; ilim = Inv(lim);
    for (int i = 0; i < lim; i++) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    int W = pw(G, (mod - 1) / lim);
    Wn[0] = 1; for (int i = 1; i <= lim; i++) Wn[i] = 1ll * Wn[i - 1] * W % mod;
}
int n, k;
int a[maxn], b[maxn];
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0, tmp; i < n; i++) scanf("%d", &tmp), a[tmp] = b[tmp] = 1;
    init(1 << 20, 998244353);
    NTT(a, 1);
    for (int i = 0; i < lim; i++) a[i] = pw(a[i], k);
    NTT(a, 0);
    init(1 << 20, 1004535809);
    NTT(b, 1);
    for (int i = 0; i < lim; i++) b[i] = pw(b[i], k);
    NTT(b, 0);
    for (int i = 0; i < lim; i++) if (a[i] | b[i]) printf("%d ", i);
    return 0;
}
*/
