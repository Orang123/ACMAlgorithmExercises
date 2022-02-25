/*
题意:摘自网上
有一个大小有N（最多75）的方格，要你从（1，1）走到（n,n）。
有如下规则：你只有三个方向，左、右、下。不能走出方格。一个
方格只能走一次。你要保证你的路径上的格子的和最大。你最多只
能走k(最多为5)个负权值的格子，从起点到终点。如果可达输出最大的和，
如果不可达输出”impossible”。
n<=75,k<=5.
链接:https://www.luogu.com.cn/problem/UVA10913
思路:很明显在搜索的过程中会产生重叠路径,因此需要记忆化搜索.只是
记忆化搜索对(x,y)网格点的状态的表示需要考虑额外的两个因素,第一个是
走到当前格子还剩下能走的负整数网格数目,还有走到当前(x,y)点的方向,
走到(x,y)点的负整数不同会影响接下来路径的选取,走到(x,y)点方向不同,
因为一左一右是不能往回走的,因此也会影响最优值的选取.

因此dp[x][y][d][s]表示还剩下s个能走的负整数网格,以d方向到达(x,y),从
(x,y)走到(n,n)所能获得的最大权值和.注意dp的权值和INF也是一个合法状态,
所以,需要对状态比较额外采用一个vis[x][y][d][s]数组,否则会TLE.
需要注意的是出发点(1,1)有可能也是负整数,因此需要额外判断,初始的k是否要减一.
*/
//ac 0ms 记忆化搜索,vis数组单独标记
//dp[x][y][d][s]表示还剩下s个能走的负整数网格,以d方向到达(x,y),从
//(x,y)走到(n,n)所能获得的最大权值和.
//时间复杂度O(75*75*5*3)=84375
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 80
#define INF -0x3f3f3f3f
using namespace std;

int n,k,mp[N][N],dp[N][N][3][6],vis[N][N][3][6],dir[3][2]={{0,-1},{0,1},{1,0}};

int dfs(int x,int y,int d,int s){
    if(vis[x][y][d][s])
        return dp[x][y][d][s];
    if(x == n && y == n)
        return dp[n][n][d][s]=mp[n][n];
    int nx,ny,res;
    for(int i=0;i<3;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>n || ny<1 || ny>n)
            continue;
        if((d==0 && i==1) || (d==1 && i ==0))//不能往回走,一个格子最多走一次
            continue;
        if(mp[nx][ny]<0){
            if(s>=1)//负整数网格 s需至少为1
                res=dfs(nx,ny,i,s-1);
            else
                continue;
        }
        else
            res=dfs(nx,ny,i,s);
        if(res!=INF)//不合法直接标记为INF,不再累加,方便后续判断
            dp[x][y][d][s]=max(dp[x][y][d][s],res+mp[x][y]);
    }
    vis[x][y][d][s]=1;//标记当前状态已搜索过
    return dp[x][y][d][s];
}

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&k) && n+k){
        cas++;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                for(int t=0;t<=k;t++)
                    dp[i][j][0][t]=dp[i][j][1][t]=dp[i][j][2][t]=INF;
        }
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        if(mp[1][1]<0)//出发点有可能 就是负整数,因此k减一
            k--;
        dfs(1,1,2,k);//初始方向 要向下(2),否则会影响后续搜索方向的选取
        if(dp[1][1][2][k]!=INF)
            printf("Case %d: %d\n",cas,dp[1][1][2][k]);
        else
            printf("Case %d: impossible\n",cas);
    }
    return 0;
}

/*
//ac 10ms 记忆化搜索,对于不可达的状态设置为INF-1,不用vis数组
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 80
#define INF -0x3f3f3f3f
using namespace std;

int n,k,mp[N][N],dp[N][N][3][6],dir[3][2]={{0,-1},{0,1},{1,0}};

int dfs(int x,int y,int d,int s){
    if(dp[x][y][d][s]!=INF)
        return dp[x][y][d][s];
    if(x == n && y == n)
        return dp[n][n][d][s]=mp[n][n];
    int nx,ny,res;
    for(int i=0;i<3;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>n || ny<1 || ny>n)
            continue;
        if((d==0 && i==1) || (d==1 && i ==0))
            continue;
        if(mp[nx][ny]<0){
            if(s>=1)
                res=dfs(nx,ny,i,s-1);
            else
                continue;
        }
        else
            res=dfs(nx,ny,i,s);
        if(res!=INF-1)
            dp[x][y][d][s]=max(dp[x][y][d][s],res+mp[x][y]);
    }
    if(dp[x][y][d][s] == INF)
    	dp[x][y][d][s]=INF-1;
    return dp[x][y][d][s];
}

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&k) && n+k){
        cas++;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                for(int t=0;t<=k;t++)
                    dp[i][j][0][t]=dp[i][j][1][t]=dp[i][j][2][t]=INF;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        if(mp[1][1]<0)
            k--;
        dfs(1,1,2,k);
        if(dp[1][1][2][k]!=INF-1)
            printf("Case %d: %d\n",cas,dp[1][1][2][k]);
        else
            printf("Case %d: impossible\n",cas);
    }
    return 0;
}
*/
