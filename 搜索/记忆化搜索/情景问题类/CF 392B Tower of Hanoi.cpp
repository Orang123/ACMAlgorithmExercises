/*
题意:摘自网上
在经典的汉诺塔的基础上进行了改造，不是问最少移动次数，而是问最少移动代价;
从i柱移动到j柱的代价是t[i][j],求最少移动代价.
n<=40,1<=t[i][j]<=10000.
链接:https://codeforces.com/contest/392/problem/B
思路:对于汉诺塔问题是通过递归将问题的规模缩小,通过回溯记录移动的方式,直至
找到最小子问题最上面盘子的移动方式开始转移回溯构造出较大规模问题的解.
对于前k个盘子中的第k个盘子,从1移动到3,有两种方式,
要么直接移动,要么以另外一个盘子为媒介移动即:1->3或1->2,2->3
1.第k个盘子直接从1移动到3,前k-1个盘子从1移动到2,前k-1个盘子再从2移动到3.
2.第k个盘子从1移动到2,前k-1个盘子从1移动到3,前k-1个盘子再从3移动到1,
第k个盘子从2再移动到3,最后前k-1个盘子再从1移动到3.
需要比较两种移动方式 求取最小移动代价.
两种方式在缩小问题规模时会有重叠子问题,因此记忆化搜索,
dp[k][from][to]表示将前k个盘子从from杆移动到to杆所需要的最小花费.
*/
//ac 31ms 记忆化搜索
//dp[k][from][to]表示将前k个盘子从from杆移动到to杆所需要的最小花费
//复杂度O(40*3*3)=360
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 45
using namespace std;
typedef long long ll;

int n,t[4][4];
ll dp[N][4][4];

ll dfs(int k,int from,int by,int to){
    if(dp[k][from][to]!=-1)
        return dp[k][from][to];
    if(k == 1)//初始状态最上面的盘子 有两种移动方式,一种直接移动from->to,一种间接移动from->by,by->to
        return dp[k][from][to]=min(t[from][to],t[from][by]+t[by][to]);
    ll res1,res2;
    res1=dfs(k-1,from,to,by)+t[from][to]+dfs(k-1,by,from,to);
    res2=dfs(k-1,from,by,to)+t[from][by]+dfs(k-1,to,by,from)+t[by][to]+dfs(k-1,from,by,to);
    dp[k][from][to]=min(res1,res2);
    return dp[k][from][to];
}

int main(){
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++)
            scanf("%d",&t[i][j]);
    }
    scanf("%d",&n);
    printf("%lld",dfs(n,1,2,3));
    return 0;
}
/*
//ac 15ms 记忆化搜索 中间辅助盘子通过6-from-to得到,因为三个盘子的编号之和一定为6.
//dp[k][from][to]表示将前k个盘子从from杆移动到to杆所需要的最小花费
//复杂度O(40*3*3)=360
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 45
using namespace std;
typedef long long ll;

int n,t[4][4];
ll dp[N][4][4];

ll dfs(int k,int from,int to){
    if(dp[k][from][to]!=-1)
        return dp[k][from][to];
    int by=6-from-to;
    if(k == 1)
        return dp[k][from][to]=min(t[from][to],t[from][by]+t[by][to]);
    ll res1,res2;
    res1=dfs(k-1,from,by)+t[from][to]+dfs(k-1,by,to);
    res2=2*dfs(k-1,from,to)+t[from][by]+dfs(k-1,to,from)+t[by][to];
    dp[k][from][to]=min(res1,res2);
    return dp[k][from][to];
}

int main(){
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++)
            scanf("%d",&t[i][j]);
    }
    scanf("%d",&n);
    printf("%lld",dfs(n,1,3));
    return 0;
}
*/

/*
//ac 31ms 正向dp
//摘自博客:https://www.cnblogs.com/dmoransky/p/12483477.html
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 45;

typedef long long LL;

int t[3][3], g[3][3], n;
LL f[N][3][3];


int main() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) scanf("%d", &t[i][j]), g[i][j] = t[i][j];
	scanf("%d", &n);
	for (int k = 0; k < 3; k++)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
	memset(f, 0x3f, sizeof f);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			f[1][i][j] = t[i][j];

	for (int i = 2; i <= n; i++) {
		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {
				if (a == b) continue;
				int c = 3 - a - b;
				f[i][a][b] = min(f[i - 1][a][c] + g[a][b] + f[i - 1][c][b], f[i - 1][a][b] + g[a][c] + f[i - 1][b][a] + g[c][b] + f[i - 1][a][b]);
			}
		}
	}
	printf("%lld\n", f[n][0][2]);
	return 0;
}
*/
