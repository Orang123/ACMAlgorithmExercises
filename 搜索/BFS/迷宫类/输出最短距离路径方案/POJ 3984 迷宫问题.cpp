/*
题意:定义一个二维数组：
int maze[5][5] = {

	0, 1, 0, 0, 0,

	0, 1, 0, 1, 0,

	0, 0, 0, 0, 0,

	0, 1, 1, 1, 0,

	0, 0, 0, 1, 0,

};
它表示一个迷宫,其中的1表示墙壁,0表示可以走的路,只能横着走或竖着走,
不能斜着走,要求编程序找出从左上角到右下角的最短路线.输出路径上的点的坐标.
链接:http://poj.org/problem?id=3984
思路:bfs 向4个方向扩展状态,记录一个State(x,y)的二维数组pre[N][N],记录
最短路径格子的上一个格子的State.即:pre[nx][ny]=tp(State);
*/
//ac 16ms bfs
#include<cstdio>
#include<queue>
#include<cstring>
#define N 5
using namespace std;

int mp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
struct State{
    int x,y;
    State(int x=0,int y=0):x(x),y(y){}
}pre[N][N];

void bfs(){
    queue<State> Q;
    mp[0][0]=1;
    Q.push(State(0,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x == 4 && tp.y == 4)
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=0 && nx<=4 && ny>=0 && ny<=4 && !mp[nx][ny]){
                mp[nx][ny]=1;//只需一次bfs 直接修改mp[nx][ny]=1 不能走即可,无需再开vis[N][N]数组单独做标记
                pre[nx][ny]=tp;
                Q.push(State(nx,ny));
            }
        }
    }
}

void print(int x,int y){
    if(!x && !y)
        printf("(0, 0)\n");
    else{
        print(pre[x][y].x,pre[x][y].y);
        printf("(%d, %d)\n",x,y);
    }
}

int main(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            scanf("%d",&mp[i][j]);
    }
    bfs();
    print(4,4);
    return 0;
}

/*
//ac 0ms dfs 普通的dfs已经能ac,就不必考虑迭代加深搜索的曼哈顿距离剪枝了
//因为dfs先行遍历到(4,4)的路径并不一定是最短的,所以要记录更新到达每个点(x,y)的最短距离才行.
//dp[x][y]表示走到(x,y)点时所用最短距离.
//剪枝: 当当前行走方案 所用距离不能比之前走到(nx,ny)点距离更小时就不必 继续走下去.
//时间复杂度(4^25) 每个格子都能向四周上下左右4个方向走 总共25个格子 但是实际相邻的点是不会重复往回走的,因此实际复杂度比这个还是要小许多
#include<cstdio>
#include<queue>
#include<cstring>
#define N 5
using namespace std;

int mp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},dp[N][N];
struct State{
    int x,y;
    State(int x=0,int y=0):x(x),y(y){}
}pre[N][N];

void dfs(int x,int y,int s){
    if(x == 4 && y == 4)
        return;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        //剪枝: 当当前行走方案 所用距离不能比之前走到(nx,ny)点距离更小时就不必 继续走下去.
        if(nx>=0 && nx<=4 && ny>=0 && ny<=4 && !mp[nx][ny] && s+1<dp[nx][ny]){
            dp[nx][ny]=s+1;
            pre[nx][ny]=State(x,y);
            dfs(nx,ny,s+1);
        }
    }
}

void print(int x,int y){
    if(!x && !y)
        printf("(0, 0)\n");
    else{
        print(pre[x][y].x,pre[x][y].y);
        printf("(%d, %d)\n",x,y);
    }
}

int main(){
    memset(dp,0x3f,sizeof(dp));
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            scanf("%d",&mp[i][j]);
    }
    dp[0][0]=0;
    dfs(0,0,0);
    print(4,4);
    return 0;
}
*/
