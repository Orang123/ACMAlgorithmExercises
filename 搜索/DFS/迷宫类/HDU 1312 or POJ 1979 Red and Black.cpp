/*
题意:w*h的网格,‘#’表示红方块,‘.’表示黑方块,某人初始位置在‘@'代表黑块,
可以向上下左右四个方向走,他只能走黑块,问从起点(黑块)他能走的黑块的个数共有多少？
w,h<=20.
同POJ 1979 Red and Black是同一道题
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1312 or http://poj.org/problem?id=1979
思路:bfs或dfs从四个方向遍历不是'#'的,遍历过的点都设置成'#',不能再遍历,并统计其个数.
*/
//ac bfs 15ms
//复杂度O(w*h)=400
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

int w,h,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},cnt;
char mp[N][N];
struct State{
    int x,y;
    State(int x=0,int y=0):x(x),y(y){}
};

void bfs(int sx,int sy){
    queue<State> Q;
    mp[sx][sy]='#';
    Q.push(State(sx,sy));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=h && ny>=1 && ny<=w && mp[nx][ny] != '#'){
                cnt++;
                mp[nx][ny]='#';
                Q.push(State(nx,ny));
            }
        }
    }
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&w,&h) && w+h){
        cnt=1;
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        bfs(sx,sy);
        printf("%d\n",cnt);
    }
    return 0;
}

/*
//ac 15ms dfs
//时间复杂度O(w*h)=400
#include<cstdio>
#include<cstring>
#define N 25
using namespace std;

int w,h,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},cnt;
char mp[N][N];

void dfs(int x,int y){
	if(mp[x][y] == '#')
		return;
	mp[x][y]='#';
	cnt++;
	int nx,ny;
	for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=h && ny>=1 && ny<=w && mp[nx][ny] != '#')
            dfs(nx,ny);
    }
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&w,&h) && w+h){
        cnt=0;
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        dfs(sx,sy);
        printf("%d\n",cnt);
    }
    return 0;
}
*/
