/*
题意:m*n的网格,三个小女警初始位置在a,b,c要回到家'h',
其中'm'和'#'都不能经过求至少需要多久才能全部到达.
链接:http://lightoj.com/volume_showproblem.php?problem=1238
思路:分三次分别对三个人的初始位置bfs 求出三个人到达'h'的最短时间,
输出最大值max(t1,t2,t3).
*/
//ac 8ms bfs
//时间复杂度O(T*m*n)=100*20*20=4*10^4
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

int m,n,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N];
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
};

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == 'h')
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=m && ny>=1 && ny<=n && mp[nx][ny]!='#' && mp[nx][ny]!='m' && !vis[nx][ny]){
                vis[nx][ny]=1;
                Q.push(State(nx,ny,tp.t+1));
            }
        }
    }
    return tp.t;
}

int main(){
    int T,x1,x2,x3,y1,y2,y3,t1,t2,t3,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'a')
                    x1=i,y1=j;
                else if(mp[i][j] == 'b')
                    x2=i,y2=j;
                else if(mp[i][j] == 'c')
                    x3=i,y3=j;
            }
        }
        memset(vis,0,sizeof(vis));
        t1=bfs(x1,y1);
        memset(vis,0,sizeof(vis));
        t2=bfs(x2,y2);
        memset(vis,0,sizeof(vis));
        t3=bfs(x3,y3);
        printf("Case %d: %d\n",cas,max(t1,max(t2,t3)));
    }
    return 0;
}

/*
dfs O(4^(20*20))会TLE
*/
