/*
题意:n*m的网格,1代表站台,求出每个(x,y)格子距离最近的站台1
的最短距离,输出所有点距离1的最短距离得到存储矩阵.
1<=n,m<=182.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2645
思路:
方法1:以每个点(x,y)为起点做一次bfs,第一次遇到1站台时结束,
记录最短距离res[x][y]=tp.d;
方法2:将所有的1点入队,求出到达其它位置的最短距离
res[nx][ny]=tp.d+1;
*/
//ac 452ms bfs 所有点(x,y)作为起点开始bfs,求出第一个到达的1点就结束
//时间复杂度O(n*m*n*m)
#include<cstdio>
#include<queue>
#include<cstring>
#define N 200
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N],res[N][N];
char mp[N][N];
struct State{
    int x,y,d;
    State(int x=0,int y=0,int d=0):x(x),y(y),d(d){}
};

void bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == '1'){
            res[sx][sy]=tp.d;
            break;
        }
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && !vis[nx][ny]){
                vis[nx][ny]=1;
                Q.push(State(nx,ny,tp.d+1));
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                memset(vis,0,sizeof(vis));
                bfs(i,j);
                printf("%d",res[i][j]);
                if(j!=m)
                    printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}

/*
//ac 31ms 将所有的1入队,求出到达其它位置的最短距离
//时间复杂度O(n*m)
#include<cstdio>
#include<queue>
#include<cstring>
#define N 200
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},res[N][N];
char mp[N][N];
struct State{
    int x,y,d;
    State(int x=0,int y=0,int d=0):x(x),y(y),d(d){}
};
queue<State> Q;

void bfs(){
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && res[nx][ny] == -1){//res[nx][ny] == -1 必须是还未到达过的,已经到达的点 已经是最短距离了
                res[nx][ny]=tp.d+1;
                Q.push(State(nx,ny,tp.d+1));
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
    	memset(res,-1,sizeof(res));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
            	if(mp[i][j] == '1'){
            		res[i][j]=0;//1点 距离最近的1点是自己本身,因此最短距离为0
            		Q.push(State(i,j,0));
				}
			}
        }
        bfs();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                printf("%d",res[i][j]);
                if(j!=m)
                    printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}
*/
