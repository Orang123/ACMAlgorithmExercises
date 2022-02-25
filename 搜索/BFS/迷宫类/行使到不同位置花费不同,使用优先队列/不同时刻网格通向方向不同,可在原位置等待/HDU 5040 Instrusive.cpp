/*
//题意摘自网上
题意:给一张n*n网格图，Matt要从M移动到T取偷东西，N，W，S，E表示这些位置监控的初始方向为
北、西、南、东的监控器，'M'初始位置,'#'表示障碍物,'T'表示目的地，'.'表示空地,并且每一秒
顺时针旋转90度,每个摄像头的观察范围为它所在的点，和当前它面向的那个点，现在Matt每移动一格
需要花一秒，但是如果当前他所在的位置或者他要去的位置被监控器监视，那么如果他要移动，就必须
躲在箱子里移动，时间需要花费3秒。或者也可以选择不移动，躲在箱子里1秒，问说Matt最少花费多少时间移动到T。
1<=n<=500.
注意:这里判断当前位置和下一位置是否被监控监控到时间都是按照当前时刻tp.t去算的.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5040
思路:bfs,因为不被监控器监控只需1s移动一格,被监控监控到需要3s移动,
因此采用优先队列.只是每走一格需要判断当前位置和所走到下一位置是否
会被周围上下左右4个方向是否被监控监控到.位置标记用三维数组vis[x][y][t%4]标记,
因为后出队的状态 虽然时间较大,但是当前步骤可能用时小,可能不会被监控发现.
2种做法记录每个监控器能监控到的位置.
方式1:pos一维数组记录.pos['N']=k表示监控器初始监控方向为北的情况下所能监控到的Matt所在
位置在向南走时能走到该监控器,而南这个方向在dir数组中的下标为k.
pos记录的是它监控方向的反方向在dir方向数组的下标,但是要保证pos['N'],pos['E'],pos['S'],pos['W]
记录的方向下标一定要是连续的,因为随着时间t增加要取模,但pos['N']记录的下标不一定要求是0,可以是1、2、3
只是要pos记录的值一定要连续.

方式2:pos三维数组记录pos[x][y][t%4]=0/1表示(x,y)位置在时间t下是否能被监控器监控到.
预处理出'N'、'E'、'S'、'W'监控器在各个方向下在时间取模t%4下是否能被监控pos[x+/-1][y+/-1][0..3].

*/
//ac 390ms bfs
//摄像机反方向用pos一维数组记录
//方式1:pos一维数组记录.pos['N']=k表示监控器初始监控方向为北的情况下所能监控到的Matt所在
//位置在向南走时能走到该监控器,而南这个方向在dir数组中的下标为k.
//pos记录的是它监控方向的反方向在dir方向数组的下标,但是要保证pos['N'],pos['E'],pos['S'],pos['W]
//记录的方向下标一定要是连续的,因为随着时间t增加要取模,但pos['N']记录的下标不一定要求是0,可以是1、2、3
//只是要pos记录的值一定要连续.
#include<cstdio>
#include<queue>
#include<cstring>
#define N 510
using namespace std;

//pos数组下标为'N'大写字母,因此取到'Z'最大的ASCII码
//dir存储的方向是根据pos记录的反向预设的 为南、西、北、东
int n,dir[4][2]={{1,0},{0,-1},{-1,0},{0,1}},pos[90],vis[N][N][4];
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>n || mp[x][y] == '#')
        return 1;
    return 0;
}

//判断是否为监控器
int isCamera(int x,int y){
    if(mp[x][y] == 'N' || mp[x][y] == 'E' || mp[x][y] == 'S' || mp[x][y] == 'W')
        return 1;
    return 0;
}

//判断(x,y)位置在时间t时是否会被监控器监控到
int judge(int x,int y,int t){
    if(isCamera(x,y))
        return 1;
    int nx,ny;
    char ch;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(check(nx,ny) || !isCamera(nx,ny))
            continue;
        //监控器监控方向为ch
        ch=mp[nx][ny];
        //监控方向在时间t后实际 能监控到的位置反方向在dir中下标为(pos[ch]+t)%4
        //如果(pos[ch]+t)%4 == i说明,当前(x,y)在(nx.ny)监控器监控方向内
        if((pos[ch]+t)%4 == i)
            return 1;
    }
    return 0;
}

int bfs(int sx,int sy){
    priority_queue<State> Q;
    vis[sx][sy][0]=1;//初始状态位置 0时刻被标记
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny,nt,flag;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.x][tp.y] == 'T')
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny))
                continue;
            flag=0;
            //判断当前位置(tp.x,tp.y)和即将要走到位置(nx,ny)在当前时刻tp.t是否能被监控器监控到
            //注意这里当前位置和下一位置都是当前时刻tp.t
            //若能监控到 则在箱子内3s从(tp.x,tp.y)移动到(nx,ny)
            if(judge(tp.x,tp.y,tp.t) || judge(nx,ny,tp.t)){
                nt=tp.t+3;
                flag=1;
            }
            else//否则不会被监控到 只需1s就能从(tp.x,tp.y)移动到(nx,ny)
                nt=tp.t+1;
            //判断时刻nt下的(nx,ny)是否已经走过,没走过入队
            //实际优先队列后出队的时间较大,但是时间点不同,有可能从(tp.x,tp.y)到(nx,ny)就不会被监控器监控到,原先用3s,后出队的状态只需用1s
            //最终用时反而会少
            if(!vis[nx][ny][nt%4]){
                vis[nx][ny][nt%4]=1;
                Q.push(State(nx,ny,nt));
            }
            //当前位置(tp.x,tp.y)和要走到位置(nx,ny)会被监控监控到,选择在当前位置躲在箱子内1s.
            if(flag && !vis[tp.x][tp.y][(tp.t+1)%4]){
                vis[tp.x][tp.y][(tp.t+1)%4]=1;
                Q.push(State(tp.x,tp.y,tp.t+1));
            }
        }
    }
    return -1;
}

int main(){
    int cas=0,T,sx,sy;
    pos['N']=0;//N对应的方向是S 对应dir下标0
    pos['E']=1;//N对应的方向是W 对应dir下标1
    pos['S']=2;//N对应的方向是N 对应dir下标2
    pos['W']=3;//N对应的方向是E 对应dir下标3
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'M')
                    sx=i,sy=j;
            }
        }
        printf("Case #%d: %d\n",cas,bfs(sx,sy));
    }
    return 0;
}

/*
//ac 452ms bfs
//摄像机反方向用pos三维数组记录各个方向能被监控到的时间
//方式2:pos三维数组记录pos[x][y][t%4]=0/1表示(x,y)位置在时间t下是否能被周围监控器监控到.
//预处理出'N'、'E'、'S'、'W'监控器在各个方向下在时间取模t%4下是否能被监控pos[x+/-1][y+/-1][0..3].
#include<cstdio>
#include<queue>
#include<cstring>
#define N 510
using namespace std;

//pos[x][y][t%4]=0/1表示(x,y)位置在时间t下是否能被周围监控器监控到.
int n,dir[4][2]={{1,0},{0,-1},{-1,0},{0,1}},pos[N][N][4],vis[N][N][4];
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>n || mp[x][y] == '#')
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    priority_queue<State> Q;
    vis[sx][sy][0]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny,nt,flag;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.x][tp.y] == 'T')
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny))
                continue;
            flag=0;
            //判断当前位置和即将要走位置在当前时刻tp.t是否被监控监控到
            if(pos[tp.x][tp.y][tp.t%4] || pos[nx][ny][tp.t%4]){
                nt=tp.t+3;
                flag=1;
            }
            else
                nt=tp.t+1;
            if(!vis[nx][ny][nt%4]){
                vis[nx][ny][nt%4]=1;
                Q.push(State(nx,ny,nt));
            }
            if(flag && !vis[tp.x][tp.y][(tp.t+1)%4]){
                vis[tp.x][tp.y][(tp.t+1)%4]=1;
                Q.push(State(tp.x,tp.y,tp.t+1));
            }
        }
    }
    return -1;
}

int main(){
    int cas=0,T,sx,sy;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(vis,0,sizeof(vis));
        memset(pos,0,sizeof(pos));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'M')
                    sx=i,sy=j;
                //监控方向初始监控方向为北
                else if(mp[i][j] == 'N'){
                    //(i,j)当前位置任何时刻都能被监控到
                    pos[i][j][0]=pos[i][j][1]=pos[i][j][2]=pos[i][j][3]=1;
                    if(!check(i-1,j))//当前位置(i,j)的正上方(i-1,j)在时刻0会被监控到
                        pos[i-1][j][0]=1;
                    if(!check(i,j+1))//当前位置(i,j)的右方(i,j+1)在时刻1会被监控到
                        pos[i][j+1][1]=1;
                    if(!check(i+1,j))//当前位置(i,j)的正下方(i+1,j)在时刻2会被监控到
                        pos[i+1][j][2]=1;
                    if(!check(i,j-1))//当前位置(i,j)的左方(i,j-1)在时刻3会被监控到
                        pos[i][j-1][3]=1;
                }
                else if(mp[i][j] == 'E'){
                    pos[i][j][0]=pos[i][j][1]=pos[i][j][2]=pos[i][j][3]=1;
                    if(!check(i,j+1))
                        pos[i][j+1][0]=1;
                    if(!check(i+1,j))
                        pos[i+1][j][1]=1;
                    if(!check(i,j-1))
                        pos[i][j-1][2]=1;
                    if(!check(i-1,j))
                        pos[i-1][j][3]=1;
                }
                else if(mp[i][j] == 'S'){
                    pos[i][j][0]=pos[i][j][1]=pos[i][j][2]=pos[i][j][3]=1;
                    if(!check(i+1,j))
                        pos[i+1][j][0]=1;
                    if(!check(i,j-1))
                        pos[i][j-1][1]=1;
                    if(!check(i-1,j))
                        pos[i-1][j][2]=1;
                    if(!check(i,j+1))
                        pos[i][j+1][3]=1;
                }
                else if(mp[i][j] == 'W'){
                    pos[i][j][0]=pos[i][j][1]=pos[i][j][2]=pos[i][j][3]=1;
                    if(!check(i,j-1))
                        pos[i][j-1][0]=1;
                    if(!check(i-1,j))
                        pos[i-1][j][1]=1;
                    if(!check(i,j+1))
                        pos[i][j+1][2]=1;
                    if(!check(i+1,j))
                        pos[i+1][j][3]=1;
                }
            }
        }
        printf("Case #%d: %d\n",cas,bfs(sx,sy));
    }
    return 0;
}
*/
