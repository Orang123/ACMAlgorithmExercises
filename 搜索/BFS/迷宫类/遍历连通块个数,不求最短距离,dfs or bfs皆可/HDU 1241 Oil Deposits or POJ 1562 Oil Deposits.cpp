/*
题意:m*n的网格,‘@’表示油井,‘*’表示无油,已知'@'油井之间上下左右、相邻对角线
8个方向的和其它油井是相互连通的,问共有多少个独立的连通油井.
1<=m,n<=100.
同POJ 1979 Oil Deposits是同一道题
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1241 or http://poj.org/problem?id=1562
思路:bfs或dfs考虑从每个'@'开始向8个方向遍历是'@'的,遍历过的点都设置成'#',不能再遍历,
并统计总共遍历了几次bfs或dfs,这就是实际独立连通分支油井个数.
*/
//ac bfs 31ms
//时间复杂度O(m*n)=10^4 每个点(x,y)只会遍历一次
#include<cstdio>
#include<queue>
#include<cstring>
#define N 110
using namespace std;

//dir[8][2]代表上下左右、邻对角线这八个方向
int m,n,dir[8][2]={{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}},cnt;
char mp[N][N];
struct State{
    int x,y;
    State(int x=0,int y=0):x(x),y(y){}
};

void bfs(int sx,int sy){
    queue<State> Q;
    mp[sx][sy]='*';
    Q.push(State(sx,sy));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<8;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=m && ny>=1 && ny<=n && mp[nx][ny] == '@'){
                mp[nx][ny]='*';
                Q.push(State(nx,ny));
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&m,&n) && m+n){
        cnt=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j] == '@'){
                    cnt++;
                    bfs(i,j);
                }
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}

/*
//ac 32ms dfs
//时间复杂度O(m*n)=10^4 每个点(x,y)只会遍历一次
#include<cstdio>
#include<queue>
#include<cstring>
#define N 110
using namespace std;

int m,n,dir[8][2]={{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}},cnt;
char mp[N][N];

void dfs(int x,int y){
	int nx,ny;
	for(int i=0;i<8;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=m && ny>=1 && ny<=n && mp[nx][ny] == '@'){
            mp[nx][ny]='*';
            dfs(nx,ny);
        }
    }
}

int main(){
    while(scanf("%d%d",&m,&n) && m+n){
        cnt=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j] == '@'){
                    cnt++;
                    mp[i][j]='*';
                    dfs(i,j);
                }
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}
*/
