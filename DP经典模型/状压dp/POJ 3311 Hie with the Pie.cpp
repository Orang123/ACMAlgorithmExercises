/*
题意:摘自网上
输入一个数n，现在有n个地方（标号1到n）要从标号为0的地方出去，经过所有的
地方之后回来，求最短的时间，输入(n+1)*(n+1)的矩阵表示每两点之间到达所需要的时间。
n<=10.
链接:http://poj.org/problem?id=3311
思路:状压dp.dp[u][sta]所经过点的二进制位状态为sta起点为u并且能返回0点所花费的最短时间
*/
//ac 0ms 记忆化搜索
//时间复杂度O(n^2*(1<<n))
//dp[u][sta]所经过点的二进制位状态为sta起点为u并且能返回0点所花费的最短时间
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define INF 0x3f3f3f3f
using namespace std;

int n,dp[N][1<<N],mp[N][N];

void floyd(){
    for(int k=0;k<=n;k++){
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++)
                mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
        }
    }
}

int dfs(int u,int cur){
    if(dp[u][cur]!=-1)
        return dp[u][cur];
    if(!cur && !u)//已经遍历完n+1个点,并且能回到0起点 才是合法状态,返回0
        return dp[u][cur]=0;
    dp[u][cur]=INF;
    for(int i=0;i<n;i++){
        if(cur & 1<<i)
            dp[u][cur]=min(dp[u][cur],dfs(i,cur ^ 1<<i)+mp[u][i]);
    }
    return dp[u][cur];
}


int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        floyd();
        n++;//把起点0也算进去,所以二进制状态中点的个数为n+1
        printf("%d\n",dfs(0,(1<<n)-1));//搜索出发点从0开始,但并不算入当前二进制状态
    }
    return 0;
}

/*
//ac 0ms 递推
//相比记忆化搜索,这个递推的做法,还是需要更多的技巧的.
//摘自博客;https://blog.csdn.net/m0_46082460/article/details/115916192
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;

int n;
int G[505][505];
int dp[1<<15][20];

void floyd(){
	for(int k = 0;k < n;k++){
		for(int i = 0;i < n;i++){
			for(int j = 0;j < n;j++){
				G[i][j] = min(G[i][j],G[i][k]+G[k][j]);
			}
		}
	}
}

int main(){
	while(~scanf("%d",&n)){
		if(n == 0) break;
		memset(G,0x3f3f3f3f,sizeof(G));
		for(int i = 0;i <= n;i++){
			for(int j = 0;j <= n;j++){
				scanf("%d",&G[i][j]);
			}
		}
		n++;
		for(int i = 0;i <=(1<<n);i++)
			memset(dp[i],0x3f3f3f3f,sizeof(dp[i]));
		floyd();
		dp[(1<<n)-1][0] = 0;
		for(int S = (1<<n)-2;S >= 0;S--){
			for(int v = 0;v < n;v++){
				for(int u = 0;u < n;u++){
					if((S&(1 << u)) == 0){
						dp[S][v] = min(dp[S][v],dp[S|(1<<u)][u]+G[v][u]);
					}
				}
			}
		}
		printf("%d\n",dp[0][0]);
	}
	return 0;
}
*/
