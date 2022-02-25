/*
题意:n*m的网格,'.'代表可行走,'#'代表不可行走,'@'代表KFC,'Y'是yifenfei的初始位置,
'M'是Merceki的初始位置,yifenfei和Merceki只能向上下左右4个方向行走,每走一步需要花费
11分钟,现在问yifenfei和Merceki要在KFC见面最少需要多长时间.
2<=n,m<=200.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2612
思路:2次bfs,分别以Y M两点开始,记录到达每个(x,y)的最短距离,最后每个KFC求出dis1+dis2的
最小时间即可.
*/
//ac 46ms bfs
//时间复杂度O(n*m)=4*10^4
#include<cstdio>
#include<queue>
#include<cstring>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},dis1[N][N],dis2[N][N],vis[N][N];
char mp[N][N];
struct State{
    int x,y,s;
    State(int x=0,int y=0,int s=0):x(x),y(y),s(s){}
};

void bfs(int sx,int sy,int dis[][N]){
    queue<State> Q;
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]!='#' && !vis[nx][ny]){
                vis[nx][ny]=1;
                if(mp[nx][ny] == '@')
                    dis[nx][ny]=tp.s+11;
                Q.push(State(nx,ny,tp.s+11));
            }
        }
    }
}

int main(){
    int x1,y1,x2,y2;
    while(scanf("%d%d",&n,&m)!=EOF){
        //注意dis初始化为INF,因为有些KFC可能不能走到,因此初始值要无穷大,不然会wa
        memset(dis1,0x3f,sizeof(dis1));
        memset(dis2,0x3f,sizeof(dis2));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'Y')
                    x1=i,y1=j;
                else if(mp[i][j] == 'M')
                    x2=i,y2=j;
            }
        }
        memset(vis,0,sizeof(vis));
        bfs(x1,y1,dis1);
        memset(vis,0,sizeof(vis));
        bfs(x2,y2,dis2);
        int ans=INF;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp[i][j] == '@')
                    ans=min(ans,dis1[i][j]+dis2[i][j]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//TLE dfs
//复杂度O(4^(200*200))
#include<cstdio>
#include<queue>
#include<cstring>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},dp1[N][N],dp2[N][N];
char mp[N][N];

void dfs(int x,int y,int s,int dp[][N]){
    if(s>=dp[x][y])
        return;
    dp[x][y]=s;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]!='#')
            dfs(nx,ny,s+11,dp);
    }
}

int main(){
    int x1,y1,x2,y2;
    while(scanf("%d%d",&n,&m)!=EOF){
        //注意dp初始化为INF,因为有些KFC可能不能走到,因此初始值要无穷大,不然会wa
        memset(dp1,0x3f,sizeof(dp1));
        memset(dp2,0x3f,sizeof(dp2));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'Y')
                    x1=i,y1=j;
                else if(mp[i][j] == 'M')
                    x2=i,y2=j;
            }
        }
        dfs(x1,y1,0,dp1);
        dfs(x2,y2,0,dp2);
        int ans=INF;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp[i][j] == '@')
                    ans=min(ans,dp1[i][j]+dp2[i][j]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
因为目的地KFC有多个,所以无法使用一个目的地的迭代加深搜索的曼哈顿距离剪枝
*/
