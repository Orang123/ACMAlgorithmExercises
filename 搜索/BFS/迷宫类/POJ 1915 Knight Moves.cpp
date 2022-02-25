/*
题意:一个n*n的棋牌上,问国际象棋的马从一个指定点走到另外一个指定点最少需要多少步.
输入一个数t表示测试样例有T个
每个测试样例有三行,第一行n代表棋盘大小为n*n,第二行表示起点的坐标,第三行表示终点坐标
每一步都按照国际象棋骑士的走法走,求最少的步数中起点走到终点.
4<=n<=300.
链接:http://poj.org/problem?id=1915
思路:bfs.国际象棋 马有8种走法.
因此dir[8][2]={{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}}.
因为n<=300,dfs会TLE 最坏时间界O(8^(300*300)) 1s时限 TLE.
*/
//ac 141ms bfs
//时间复杂度O(n*n)=300*300=90000
#include<cstdio>
#include<queue>
#include<cstring>
#define N 310
using namespace std;

int n,dir[8][2]={{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}},vis[N][N],ex,ey;
struct State{
    int x,y,s;
    State(int x=0,int y=0,int s=0):x(x),y(y),s(s){}
};

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x == ex && tp.y == ey)
            break;
        Q.pop();
        for(int i=0;i<8;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=0 && nx<n && ny>=0 && ny<n && !vis[nx][ny]){
                vis[nx][ny]=1;
                Q.push(State(nx,ny,tp.s+1));
            }
        }
    }
    return tp.s;
}

int main(){
    int T,sx,sy;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        scanf("%d%d",&sx,&sy);
        scanf("%d%d",&ex,&ey);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}

/*
因为n<=300.
最坏时间界O(8^(300*300)) 1s时限 TLE
直接dfs会超时

因为这国际象棋马的走法 并不是超上下左右4个方向走的,因此无法应用迭代加深dfs的曼哈顿距离剪枝
*/
