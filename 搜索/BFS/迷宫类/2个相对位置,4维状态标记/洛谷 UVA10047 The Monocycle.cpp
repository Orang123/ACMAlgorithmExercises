/*
//题意摘自网上
题意:一自行车的轮子被分成5个扇区,涂了5种不同颜色.
分别是绿、黑、红、蓝、白,车轮每顺时针向前转动一个位置,
紧贴地面的颜色就会变成后面的颜色,如当前绿色向前转动1
个位置,黑色就会紧贴地面.自行车每1秒要么骑到当前
朝向的下一个格子,要么左转或者右转车头90度,只是在
原位置调转方向而不前进.一开始自行车头面向北,车轮
紧贴地面的颜色为绿,到达目标格时,车轮紧贴地面的扇形
区域颜色必须是绿色,但车头朝向无限制.求到达目标格的最短时间.
地图是n*m的网格,'#'代表不能走的方块,其余网格都是可以走的.
'S'代表出发点,'T'代表目标点.
1<=n,m<=25.
链接:https://www.luogu.com.cn/problem/UVA10047
思路:bfs,因为要求到达目标点颜色为绿色,而颜色的变动只和车轮转动
的时间有关,将绿、黑、红、蓝、白分别以0、1、2、3、4得到数字代替,
那么到达目标点时车轮紧贴地面的颜色就是车轮向前转动的时间t模5,即t%5.
对于网格(x,y)状态标记除了需要用颜色标记外,还应用自行车的车头方向标记,
因为有可能颜色相同,但是随着车头方向不同,到达的时间不同,就会影响最终
到达目标点时的车轮颜色.
vis[x][y][i][color]表示在(x,y)位置时,自行车的方向为i,车轮上扇形区域与地面相贴的颜色为color.
关于判断左右方向可以将dir方向数组设置成连续的顺时针方向 北(0)、东(1)、南(2)、西(3),
相邻的方向间相差刚好都是1.只是注意北的数字0,减1如果小于0,这个要特判为3,西(3)+1大于3
要特判为0,相当于将连续方向0、1、2、3看成一个环.
如果当前车头方向curDir+1/-1可以等于枚举的左右方向i,那么说明方向i属于 向左、向右90度的范畴.
否则说明这个方向是当前车头的反方向(180度)不能调转.
实际可以通过取模(curDir+1)%4和(curDir+3)%4分别表示 当前方向curDir的左侧、右侧方向.

注意:不能用优先队列 直接将车头调转之后直接按调转后的方向前行一格子 花费2s 入队,这样无法在原位置
分2步分别调转90度 调转到原来的反方向180度,实际花费的时间可能较大,结果就会wa.
*/
//ac 0ms bfs+四维状态标记
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#define N 30
using namespace std;

//green、black、red、blue、white 5种颜色分别对应数字0 1 2 3 4
//vis[x][y][i][color]表示在(x,y)位置时,自行车的方向为i,车轮上扇形区域与地面相贴的颜色为color.
//dir方向必须是按顺时针方向连续排放的 北(0)、东(1)、南(2)、西(3)
int n,m,dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}},vis[N][N][4][5];
char mp[N][N];
struct State{
    int x,y,dir,col,t;
    State(int x=0,int y=0,int dir=0,int col=0,int t=0):
        x(x),y(y),dir(dir),col(col),t(t){}
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>m || mp[x][y] == '#')
        return 1;
    return 0;
}

int judgeDir(int i,int nextDir){
    if(nextDir<0)//小于0时对应的方向是环上的3
        nextDir=3;
    else if(nextDir>3)//大于3对应方向是环上的0
        nextDir=0;
    if(nextDir == i)//方向属于 调转90度范畴
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy][0][0]=1;
    Q.push(State(sx,sy,0,0,0));
    State tp;
    int nx,ny,nc;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == 'T' && tp.col == 0)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            if(tp.dir == i){//和车头方向一致 就前行
                nx=tp.x+dir[i][0];
                ny=tp.y+dir[i][1];
                if(check(nx,ny))
                    continue;
                nc=(tp.col+1)%5;//颜色变成下一位
                if(!vis[nx][ny][i][nc]){
                    vis[nx][ny][i][nc]=1;
                    Q.push(State(nx,ny,i,nc,tp.t+1));
                }
            }
            //车头方向不一样 只能调转90度 花费1s 还是在原位置,颜色不变
            //else if(judgeDir(i,tp.dir+1) || judgeDir(i,tp.dir-1)){//ac
            else if((tp.dir+1)%4 == i || (tp.dir+3)%4 == i){//ac 2种判断左右90度方向的方式 +1表示+1 +3表示-1
                if(!vis[tp.x][tp.y][i][tp.col]){
                    vis[tp.x][tp.y][i][tp.col]=1;
                    Q.push(State(tp.x,tp.y,i,tp.col,tp.t+1));
                }
            }
        }
    }
    return -1;
}

int main(){
    int cas=0,sx,sy,ans;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S')
                    sx=i,sy=j;
            }
        }
        ans=bfs(sx,sy);
        if(cas!=1)//样例之间要空出一行 否则会Presentation Error
            printf("\n");
        printf("Case #%d\n",cas);
        if(ans!=-1)
            printf("minimum time = %d sec\n",ans);
        else
            printf("destination not reachable\n");
    }
    return 0;
}
