/*
题意:从[1,1]出发到[n,n],每次走的步长是当前格子中的数字,只能朝右或下两个方向走,
问可以走到终点的方案数是多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1208
思路:记忆化搜索
dp[x][y]表示从(x,y)出发到达(n,n)时的方案个数
*/
//ac 0ms 记忆化搜索
//dp[x][y]表示从(x,y)出发到达(n,n)时的方案个数
#include<cstring>
#include<algorithm>
#define N 40
typedef long long ll;
using namespace std;

int n,dir[2][2]={{1,0},{0,1}};
ll dp[N][N];
char mp[N][N];

ll dfs(int x,int y){
    if(dp[x][y]!=-1)
        return dp[x][y];
    if(mp[x][y] == '0')//这里对只能待在原地 不能扩展,否则会进入死循环
        return 0;
    int nx,ny,k=mp[x][y]-'0';
    ll res=0;
    for(int i=0;i<2;i++){
        nx=x+dir[i][0]*k;
        ny=y+dir[i][1]*k;
        if(nx<1 || nx>n || ny<1 || ny>n)
            continue;
        res+=dfs(nx,ny);
    }
    return dp[x][y]=res;
}

int main(){
    while(scanf("%d",&n) && n!=-1){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        dp[n][n]=1;
        printf("%lld\n",dfs(1,1));
    }
    return 0;
}

/*
//ac 0ms 正向dp
//dp[x][y]表示从(1,1)出发到达(x,y)时的方案个数
#include<cstring>
#include<algorithm>
#define N 40
typedef long long ll;
using namespace std;

int n,dir[2][2]={{1,0},{0,1}};
ll dp[N][N];
char mp[N][N];

int main(){
    while(scanf("%d",&n) && n!=-1){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        dp[1][1]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int nx,ny;
                if(mp[i][j] == '0')
                    continue;
                for(int k=0;k<2;k++){
                    nx=i+dir[k][0]*(mp[i][j]-'0');
                    ny=j+dir[k][1]*(mp[i][j]-'0');
                    if(nx<1 || nx>n || ny<1 || ny>n)
                        continue;
                    dp[nx][ny]+=dp[i][j];
                }
            }
        }
        printf("%lld\n",dp[n][n]);
    }
    return 0;
}
*/
