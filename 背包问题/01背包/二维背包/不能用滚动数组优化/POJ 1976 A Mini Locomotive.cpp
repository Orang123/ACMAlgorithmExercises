#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 4
using namespace std;
//ac 0ms 二维01背包
//将连续物品看成一个整体装入 划分段的背包
//这个dp做法实际存在问题会被下面这组数据hack掉
//此题的做法和HDU 3602 大容量背包问题比较像
/*
1
5
35 40 50 10 10
2
程序输出的是135,遗漏掉了最后一个车厢10,实际答案是5个车厢全
都能拉,即答案:145
*/
/*
题意:n节车厢,每节车厢上有一定数量乘客,有三辆火车头最多可拉连续k辆车厢,
问这三个火车头最终可以拉的车厢中乘客数最多是多少.
通俗来讲就是:求一个连续数列中3个长度为不超过k的连续子序列最大值和
链接:http://poj.org/problem?id=1976
思路:可以将每段连续的k个车厢看做一个整体,其价值为k个车厢的乘客人数和.
因为要将这n个车厢装入3个火车头,这3个火车头就可看做背包容量,那么dp[i][j]
表示前i个车厢链接到前j个火车头最多能拉的乘客数.

不能用滚动数组优化因为dp[i-k][j-1] i-k只有二维才能保证是前面的状态
*/
//sum[i]表示编号为 (i-k+1)~i的连续k个车厢的总乘客数
//dp[i][j]表示前i个车厢链接到前j个火车头最多能拉的乘客数.
int n,k,a[N],dp[N][M],sum[N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&k);
        int tp=0;
        for(int i=1;i<=n;i++){
            tp+=a[i];
            if(i>=k){
                sum[i]=tp;
                tp-=a[i-k+1];
            }
        }
        for(int i=k;i<=n;i++){
            for(int j=1;j<=3;j++)
                //dp[i-1][j]表示前i-1个车厢连接到前j个火车头承载最多的乘客数,即(i-k+1)~i的车厢不连接到第j个火车头
                //dp[i-k][j-1]+sum[i] 是(i-k+1)~i的车厢连接到第j个火车头,所以上一状态就是前i-k个车厢连接到前j-1个火车头承载最多乘客数
                dp[i][j]=max(dp[i-1][j],dp[i-k][j-1]+sum[i]);
        }
        printf("%d\n",dp[n][3]);
    }
    return 0;
}

/*
//正解dp
//ac 0ms POJ discuss模块网友提供
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAX_N	50000


int n, m;
int cars[MAX_N];
int results[7][MAX_N + 1];


int calc()
{
	for (int i = 1; i < 7; ++i) {
		results[i][0] = 0;

		if (i % 2 == 0) {
			for (int j = 1; j <= n; ++j) {
				results[i][j] = max(results[i][j - 1], results[i - 1][j]);
			}
		}
		else {
			int sum = 0;
			for (int j = 1; j <= n; ++j) {
				if (j <= m) {
					sum += cars[j - 1];
					results[i][j] = sum;
				}
				else {
					sum += cars[j - 1];
					sum -= cars[j - m - 1];
					results[i][j] = sum + results[i - 1][j - m];
				}
			}
		}
	}

	return results[6][n];
}


int main()
{
	int t; scanf("%d", &t);
	for (int i = 0; i < t; ++i) {
		scanf("%d", &n);
		while (n < 1 || n > MAX_N) printf("...");

		for (int j = 0; j < n; ++j) {
			scanf("%d", &cars[j]);
		}
		scanf("%d", &m);

		printf("%d\n", calc());
	}
    return 0;
}
*/

/*
//正解线段树
//ac 16ms POJ discuss模块网友提供
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int Read(){
    int e = 0; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while('0' <= ch && ch <= '9') e = e*10 + (ch-'0'), ch = getchar();
    return e;
}

const int maxn = 1e5 + 7;
int tree[maxn<<2], k[maxn], s[maxn];

inline int max(int u, int v){
    return u>v? u: v;
}

void Buildtree(int l, int r, int key){
    if(l == r){
        tree[key] = k[l];
        return;
    }
    int mid = (l + r) >> 1;
    Buildtree(l, mid, key<<1);
    Buildtree(mid+1, r, key<<1|1);
    tree[key] = max(tree[key<<1], tree[key<<1|1]);
}

int Query(int l, int r, int ls, int rs, int key){
    if(ls <= l && r <= rs) return tree[key];
    int mid = (l + r) >> 1, ans = 0;
    if(ls <= mid) ans = max(ans, Query(l, mid, ls, rs, key<<1));
    if(mid < rs) ans = max(ans, Query(mid+1, r, ls, rs, key<<1|1));
    return ans;
}

int main(){
    int t = Read(), n, len;
    while(t --){
        n = Read();
        for(int i = 1; i <= n; i ++) k[i] = Read();
        len = Read();
        for(int i = 1; i <= n; i ++){
            k[i] += k[i-1];
            s[i] = k[i] - k[max(i-len, 0)];
        }
        for(int i = 1; i <= n; i ++) k[i] = s[i];
        Buildtree(1, n, 1);
        for(int i = len+1; i <= n; i ++) k[i] = Query(1, n, 1, i-len, 1) + s[i];
        Buildtree(1, n, 1);
        int ans = 0;
        for(int i = 2*len+1; i <= n; i ++){
            k[i] = Query(1, n, 1, i-len, 1) + s[i];
            ans = max(k[i], ans);
        }
        printf("%d\n", ans);
    }
    return 0;
}
*/

/*
//ac 32ms 记忆化搜索 这个结果可能也是比较凑巧吧 因为实际子问题可能并不能全部遍历到
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50010
int dp[3][N];
int a[N];
int b[N];
int n,k;
int dfs(int num,int l)
{
    if(num<0||l<0||l>=n) return 0;
    if(dp[num][l]) return dp[num][l];
    return dp[num][l]=max(dfs(num,l-1),dfs(num-1,l-k)+b[l]);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(b,0,sizeof(b));
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
            scanf("%d",&k);
        for(int i=k-1;i<n;i++)
                for(int j=i;j>=i-k+1;j--)
            b[i]+=a[j];
        printf("%d\n",dfs(2,n-1));
    }
    return 0;
}
*/
