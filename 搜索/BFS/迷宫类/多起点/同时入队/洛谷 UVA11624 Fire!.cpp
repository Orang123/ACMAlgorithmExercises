/*
题意:r*c个格子构成的迷宫,'#'代表墙,'.'代表可通行格子,'F'代表着火点,'J'代表Joe的初始位置,
'F'着火点每分钟向上下左右4个方向的格子蔓延,Joe每分钟也可向上下左右4个方向的可通行没着火
的格子行走,现在求出Joe走出迷宫需要的最少时间.注意格子中初始的着火点可能有多处.
1<=r,c<=1000.
链接:https://www.luogu.com.cn/problem/UVA11624
思路:2次bfs搜索.第一次bfs是对初始着火点进行扩展,求出每个'.'(x,y)开始着火需要的最少时间f[x][y].
第二次bfs是对Joe初始位置进行搜索扩展,扩展入队条件是当格子(nx,ny)是'.'且当前行走的时间小于(nx,ny)
着火需要的最少时间.

注意:此题同样不能用dfs深搜,因为深度搜索无法保证深度优先遍历的状态点用时是最少的,但又会将走过的状态
标记,而后续遍历策略 又不能走之前之前遍历的点,这样就会wa.
*/
//ac 310ms 2次bfs 1次扩展着火点状态,1次扩展Joe行走的状态
//时间复杂度O(rc)=10^6 最多能扩展的状态是迷宫的所有网格个数
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int r,c,f[N][N],vis[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct State{
    int x,y,m;
    State(int x=0,int y=0,int m=0):x(x),y(y),m(m){}
};
queue<State> Q;

void bfs1(){
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=r && ny>=1 && ny<=c && mp[nx][ny]!='#' && f[nx][ny] == INF){
                //这个状态赋值要放在for内部,不能放在pop出队之前,否则如果初始着火点的状态扩展可能是别的初始着火点,那么别的初始着火点本身时间是0,就会被赋值为别的值
                f[nx][ny]=tp.m+1;//bfs先搜索到的状态一定是最小的时间
                Q.push(State(nx,ny,tp.m+1));
            }
        }
    }
}

int bfs2(int sx,int sy){
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x<1 || tp.x>r || tp.y<1 || tp.y>c)
            return tp.m;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(!vis[nx][ny] && mp[nx][ny]!='#' && tp.m+1<f[nx][ny]){
                vis[nx][ny]=1;
                Q.push(State(nx,ny,tp.m+1));
            }
        }
    }
    return -1;
}

int main(){
    int T,sx,sy,ans;
    scanf("%d",&T);
    while(T--){
        memset(mp,'.',sizeof(mp));
        memset(f,0x3f,sizeof(f));
        scanf("%d%d",&r,&c);
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'F'){
                    f[i][j]=0;//初始着火点 本身就是着火点的 需要时间为0
                    Q.push(State(i,j,0));//可能含有多个着火点 要全部入队
                }
                else if(mp[i][j] == 'J'){
                    sx=i;
                    sy=j;
                }
            }
        }
        bfs1();
        memset(vis,0,sizeof(vis));
        ans=bfs2(sx,sy);
        while(!Q.empty()) Q.pop();
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("IMPOSSIBLE\n");
    }
    return 0;
}

/*
//ac 220ms 单次bfs
//实际可以将所有初始着火点和Joe一同入队,将着火点和Joe同时扩展,着火点要先入队,
//对于着火点扩展过的状态,因为着火点和Joe是按照队列同时刻扩展的,时间上也是同时刻的,
//着火点扩展过的状态要设置为'#',Joe肯定是不能走的,同样Joe扩展过的状态Joe肯定也不能再走到这个状态点,设置为'#'
//因为时间上肯定不是最少的.
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int r,c,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct State{
    int x,y,m,flag;
    State(int x=0,int y=0,int m=0,int flag=0):x(x),y(y),m(m),flag(flag){}
};
queue<State> Q;

int bfs(int sx,int sy){
    mp[sx][sy]='#';
    Q.push(State(sx,sy,0,1));//Joe最后入队
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x<1 || tp.x>r || tp.y<1 || tp.y>c)
            return tp.m;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            //着火点扩展过的状态 设置为'#' 着火点不能扩展到迷宫之外
            if(!tp.flag && nx>=1 && nx<=r && ny>=1 && ny<=c && mp[nx][ny]!='#'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,0,0));
            }
            //Joe 走过的状态 要设置为'#' 因为不可能比当前用时更短 可以扩展到迷宫之外无需判断边界
            else if(tp.flag && mp[nx][ny]!='#'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.m+1,1));
            }
        }
    }
    return -1;
}

int main(){
    int T,sx,sy,ans;
    scanf("%d",&T);
    while(T--){
        memset(mp,'.',sizeof(mp));
        scanf("%d%d",&r,&c);
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'F'){
                    mp[i][j]='#';//初始着火点 直接设置为'#'不能再走
                    Q.push(State(i,j,0,0));
                }
                else if(mp[i][j] == 'J'){
                    sx=i;
                    sy=j;
                }
            }
        }
        //所有着火点F和Joe同时入队,Joe最后入队
        ans=bfs(sx,sy);
        while(!Q.empty()) Q.pop();
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("IMPOSSIBLE\n");
    }
    return 0;
}
*/

/*
1<=r,c<=1000 普通的dfs和迭代加深dfs都会TLE 迭代加深的剪枝要枚举走向4个方向出迷宫的时间都大于给定的时间则返回,剪枝效率并不高
*/
