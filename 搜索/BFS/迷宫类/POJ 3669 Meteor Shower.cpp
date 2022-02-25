/*
题意:有m个炸弹分别将在ti时间上在(xi,yi)点爆炸,爆炸涉及包括这
个点在内的上下左右五个点,爆炸过的点不能走,问从(0,0)出发,在
第一象限内能否跑到安全区域.
0<=x,y<=300.t<=1000
链接:http://poj.org/problem?id=3669
思路:bfs,可以预先处理出每个点(x,y)会被炸弹爆炸影响到的最早时间mp[x][y].
mp初始化为INF(0x3f3f3f3f).
然后从(0,0)点开始bfs,入队条件是走到(tp.x,tp.y)所用时间tp.t+1<mp[x][y]才行,
如果走到的点(x,y) mp[x][y] == INF,说明该点已经不会被炸弹波及影响到.那么就已经
抵达安全区域了.
*/
//ac 94ms bfs
//复杂度O(300*300)=90000
#include<cstdio>
#include<queue>
#include<cstring>
#define N 310
#define INF 0x3f3f3f3f
using namespace std;

int m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
};

int bfs(){
    queue<State> Q;
    mp[0][0]=0;
    Q.push(State(0,0,0));
    int nx,ny;
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx<0 || ny<0 || tp.t+1>=mp[nx][ny])
                continue;
            if(mp[nx][ny] == INF)//已到达 没有炸弹爆炸波及的点(nx,ny)就返回  最早时间tp.t+1.
                return tp.t+1;
            mp[nx][ny]=0;//走过的点 不能再走,因为后面用时肯定比当前更长. 设置为最少时间代表不可达
            Q.push(State(nx,ny,tp.t+1));
        }
    }
    return -1;
}

int main(){
    int x,y,t,nx,ny;
    while(scanf("%d",&m)!=EOF){
        memset(mp,0x3f,sizeof(mp));
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&x,&y,&t);
            mp[x][y]=min(mp[x][y],t);//本身点
            for(int i=0;i<4;i++){//炸弹波及的 上下左右4个点
                nx=x+dir[i][0];
                ny=y+dir[i][1];
                if(nx<0 || ny<0)
                    continue;
                mp[nx][ny]=min(mp[nx][ny],t);
            }
        }
        printf("%d\n",bfs());
    }
    return 0;
}
