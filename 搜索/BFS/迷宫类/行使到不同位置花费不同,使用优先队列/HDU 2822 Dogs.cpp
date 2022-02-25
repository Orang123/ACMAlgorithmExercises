/*
题意:有一只小狗要去找另一只小狗,给出两只小狗的坐标都知道,
m*n的地图里有有两种元素,'X'表示房子,'.'表示空地,
如果小狗经过房子'X',则不用挖格子,如果经过的是空地'.',
求出小狗到达目标的时候所需要挖的最小格子数.
1<=m,n<=1000.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4198
思路:由于走到'X'和'.'花费时间分别为0和1,使用普通的队列
先出队的花费时间不一定是最少的,所以出队需要按照当前花费
时间最少的状态先出队,因此使用优先队列priority_queue<State> Q;
按照状态花费时间最少的先出队.
*/
//ac 670ms bfs
//时间复杂度O(m*n)=10^6
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1100
using namespace std;

int m,n,d,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ex,ey;
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int bfs(int sx,int sy){
    priority_queue<State> Q;
    mp[sx][sy]='#';
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.top();
        if(tp.x == ex && tp.y == ey)
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(mp[nx][ny] == '.'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+1));
            }
            else if(mp[nx][ny] == 'X'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t));
            }
        }
    }
    return tp.t;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&m,&n) && m+n){
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        scanf("%d%d",&sx,&sy);
        scanf("%d%d",&ex,&ey);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
