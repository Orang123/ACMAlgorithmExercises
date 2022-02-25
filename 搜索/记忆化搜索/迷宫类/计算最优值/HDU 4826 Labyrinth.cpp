/*
题意:度度熊是一只喜欢探险的熊，一次偶然落进了一个m*n矩阵的迷宫，
该迷宫只能从矩阵左上角第一个方格开始走，只有走到右上角的第一个格子
才算走出迷宫，每一次只能走一格，且只能向上向下向右走以前没有走过的格子，
每一个格子中都有一些金币（或正或负，有可能遇到强盗拦路抢劫，度度熊身上
金币可以为负，需要给强盗写欠条），度度熊刚开始时身上金币数为0，问度度
熊走出迷宫时候身上最多有多少金币？
m,n<=100,-100<=金币数量<=100.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4826
思路:dfs记忆化搜索
dp[x][y][d] 表示以d方向到达(x,y),从(x,y)出发再到(1,n)所能获得的最大金币数.
之所以dp数组要标记为三维多加一个到达(x,y)的方向,是因为可走动的方向有3个,
上、下、右而在递归计算从(x,y)到达目标点(1,n)的最大金额时,前面父节点走过的
方向不能再走其反方向,会影响最优解的选取,而且不同路径到达该点的方向不同,
对于该点出发能走到的方向也不同,如果之前走下面,现在不能走上面,反之之前走上面,
现在不能走下面(避免死循环),而之前走右边,现在3个方向都可走.因此需要给每个点
设置一个到达该点的方向作为标记,这样就能统计出(x,y)出发所有方向的解,以便比较求出最优解.
*/
//ac 78ms 记忆化搜索
//dp[x][y][d] 表示以d方向到达(x,y),从(x,y)出发再到(1,n)所能获得的最大金币数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF -0x3f3f3f3f
using namespace std;

int m,n,mp[N][N],dp[N][N][3],dir[3][2]={{-1,0},{1,0},{0,1}};

int dfs(int x,int y,int d){
    if(dp[x][y][d]!=INF)//重叠子问题 直接返回结果
        return dp[x][y][d];
    if(x == 1 && y == n)
        return dp[x][y][d]=mp[x][y];
    int nx,ny,res=INF;
    for(int i=0;i<3;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>m || ny<1 || ny>n)
            continue;
        //如果之前从下往上走,现在就不能从上往下走 或 如果之前从上往下走,现在就不能从下往上走
        if((d == 0 && i == 1) || (d == 1 && i == 0))
            continue;
        res=max(res,mp[x][y]+dfs(nx,ny,i));
    }
    return dp[x][y][d]=res;
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=INF;//有可能最优解是0或是负数,因此dp初始化为负无穷
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        printf("Case #%d:\n",cas);
        printf("%d\n",dfs(1,1,1));//注意这里到达(1,1)点的方向初始时要设置为1向上,这样才不会影响dfs时从(1,1)向下搜索(d=0,i=1的条件触发)
    }
    return 0;
}

/*
//ac 62ms 正向dp
//dp[x][y][0]表示从(1,1)出发从上面往下面走到(x,y)获得的最大金币数
//dp[x][y][1]表示从(1,1)出发从下面往上面走到(x,y)获得的最大金币数
//往右边走,dp[x][y-1][0]和dp[x][y-1][1]两个状态都可以转移到dp[x][y][0]和dp[x][y][1]
//参考博客:https://blog.csdn.net/keshuai19940722/article/details/26517843
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF -0x3f3f3f3f
using namespace std;

int m,n,mp[N][N],dp[N][N][2];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        //第0行和m+1行 是不合法状态,设置为负无穷
        for(int i=1;i<=n;i++)
            dp[0][i][0]=dp[m+1][i][1]=INF;
        dp[0][1][0]=0;//方便初始化第一列 dp[i][1][0]=dp[i-1][1][0]+mp[i][1];
        for(int i=1;i<=m;i++){
            dp[i][1][0]=dp[i-1][1][0]+mp[i][1];
            dp[i][1][1]=INF;//从下面往上走,刚开始是由从上面往下面走的第一列转移而来的
        }
        for(int j=2;j<=n;j++){
            for(int i=1;i<=m;i++)//从上面往下面走
                dp[i][j][0]=max(dp[i-1][j][0],max(dp[i][j-1][0],dp[i][j-1][1]))+mp[i][j];
            for(int i=m;i>=1;i--)//从下面往上面走
                dp[i][j][1]=max(dp[i+1][j][1],max(dp[i][j-1][0],dp[i][j-1][1]))+mp[i][j];
        }
        printf("Case #%d:\n",cas);
        //注意有可能只有一列即:n=1,此时dp[1][n][1]是不合法的,因为刚开始就在(1,1)点不需要走动,就已经到达了 目标点(1,n)=(1,1)
        printf("%d\n",max(dp[1][n][0],dp[1][n][1]));
    }
    return 0;
}
*/

/*
//ac 62ms 滚动数组优化 一维数组dp
//来自博客:https://www.cnblogs.com/Tovi/p/6194807.html
//dp。第一列最大直接求出，因为只有一种走法（向下）。然后后面有两种、==向下|| 向上。
//可推到出状态方程为
//dp[i][j] = max(dp[i-1][j],dp[i][j-1]) + a[i][j] （向下）
//dp[i][j] = max(dp[i+1][j], dp[i][j-1]) + a[i][j] (向上）
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <utility>

#define INF 0xfffffff
#define max1 110

int a[max1][max1], dp[max1][max1], dp1[max1], dp2[max1];

int max(int a, int b) {
	return a>b?a:b;
}

int main() {
	int t, flag = 1;
	scanf("%d",&t);
	while (t --) {
		memset(a, 0, sizeof(a));
		int m, n;
		scanf("%d%d",&m, &n);
		for (int i = 1; i<=m; i++)
			for (int j = 1; j<=n; j++)		scanf("%d",&a[i][j]);
		memset(dp, 0, sizeof(dp));
		for (int i = 2; i<=m; i++) {
			a[i][1] = a[i][1] + a[i-1][1];
		}
		dp1[0] = dp2[0] = dp1[m+1] = dp2[m+1] = -9999999;
		for (int j = 2; j<=n; j++) {
			//向下
			for (int i = 1; i<=m; i++) {
				dp1[i] = max(dp1[i-1], a[i][j-1]) + a[i][j];
			}
			//向上
			for (int i = m; i>=1; i--) {
				dp2[i] = max(dp2[i+1], a[i][j-1]) + a[i][j];
			}
			for (int i = 1; i<=m; i++) {
				a[i][j] = max(dp1[i], dp2[i]);
			}
		}
		printf("Case #%d:\n%d\n",flag++, a[1][n]);
	}
	return 0;
}
*/
