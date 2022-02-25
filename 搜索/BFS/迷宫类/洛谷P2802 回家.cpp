/*
题意:小 H 在一个划分成了 n*m 个方格的长方形封锁线上。 每次他能向上下左右四个方向移动一格
（当然小 H 不可以静止不动）， 但不能离开封锁线，否则就被打死了。 刚开始时他有满血 6 点，
每移动一格他要消耗 1 点血量。一旦小 H 的 血量降到 0， 他将死去。 他可以沿路通过拾取鼠标
（什么鬼。。。）来补满血量。只要他走到有鼠标的格子，他不需要任何时间即可拾取。格子上的鼠标
可以瞬间补满，所以每次经过这个格子都有鼠标。就算到了某个有鼠标的格子才死去， 他也不能通过
拾取鼠标补满 HP。 即使在家门口死去， 他也不能算完成任务回到家中。
地图上有 5 种格子：
数字 0： 障碍物。
数字 1： 空地， 小 H 可以自由行走。
数字 2： 小 H 出发点， 也是一片空地。
数字 3： 小 H 的家。
数字 4： 有鼠标在上面的空地。
小 H 能否安全回家？如果能， 最短需要多长时间呢？
n,m<10
链接:https://www.luogu.com.cn/problem/P2802
思路:bfs.
*/
//ac 36ms bfs
//vis[x][y][hp]=0/1表示在(x,y)点生命值为hp的情况是否走过
#include<cstdio>
#include<queue>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,mp[N][N],vis[N][N][7];

struct State{
    int x,y,hp,t;
    State(int x=0,int y=0,int hp=0,int t=0):x(x),y(y),hp(hp),t(t){}
};

int check(int x,int y,int hp){
    if(x>=1 && x<=n && y>=1 &&y<=m && mp[x][y])
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,6,0));
    vis[sx][sy][6]=1;
    State tp;
    int nx,ny,np;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        if(!tp.hp)
            continue;
        if(mp[tp.x][tp.y] == 3)
            return tp.t;
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny,tp.hp-1)){
                if(mp[nx][ny] == 4 && tp.hp-1)
                    np=6;
                else
                    np=tp.hp-1;
                if(!vis[nx][ny][np]){
                    vis[nx][ny][np]=1;
                    Q.push(State(nx,ny,np,tp.t+1));
                }
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&mp[i][j]);
            if(mp[i][j] == 2) sx=i,sy=j;
        }
    }
    printf("%d",bfs(sx,sy));
    return 0;
}

/*
//ac 41ms bfs
//vis[x][y]=hp表示走到(x,y)点最大的生命值为hp
#include<cstdio>
#include<queue>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,mp[N][N],vis[N][N];

struct State{
    int x,y,hp,t;
    State(int x=0,int y=0,int hp=0,int t=0):x(x),y(y),hp(hp),t(t){}
};

int check(int x,int y,int hp){
    if(x>=1 && x<=n && y>=1 &&y<=m && mp[x][y])
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,6,0));
    State tp;
    int nx,ny,np;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        if(!tp.hp)
            continue;
        if(mp[tp.x][tp.y] == 3)
            return tp.t;
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny,tp.hp-1)){
                if(mp[nx][ny] == 4 && tp.hp-1)
                    np=6;
                else
                    np=tp.hp-1;
                //如果当前走到(nx,ny)点的生命值不能比之前更大,则不入队,因为时间每次只增加1,之
				//前的时间就是最短的,现在的时间只会大于等于之前的,如果生命值不能比之前的大 就不必再扩展
                if(np>vis[nx][ny]){
                    vis[nx][ny]=np;
                    Q.push(State(nx,ny,np,tp.t+1));
                }
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&mp[i][j]);
            if(mp[i][j] == 2) sx=i,sy=j;
        }
    }
    printf("%d",bfs(sx,sy));
    return 0;
}
*/

/*
//ac dfs
//因为数据量比较少,不做标记,只用hp为0作为结束条件
#include<cstdio>
int n,m,map0[11][11],ans=200;
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int judge(int x,int y){
    if(x>=1 && x<=n && y>=1 &&y<=m && map0[x][y]) return 1;
    else return 0;
}

void dfs(int x,int y,int hp,int k){
    if(k>=ans) return;
    if(map0[x][y] == 4 && hp) hp=6;
    if(!hp) return;
    if(map0[x][y] == 3){
        if(k<ans) ans=k;
        return;
    }
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(judge(x0,y0))
            dfs(x0,y0,hp-1,k+1);
    }
}

int main(){
    int x,y;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&map0[i][j]);
            if(map0[i][j] == 2) x=i,y=j;
        }
    }
    dfs(x,y,6,0);
    if(ans!=200)
        printf("%d\n",ans);
    else
        printf("-1\n");
    return 0;
}
*/

/*
//ac dfs
//vis[x][y][hp]=0/1表示在(x,y)点生命值为hp的情况是否走过
#include<cstdio>
int n,m,map0[11][11],vis[11][11][7],ans=200;
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int judge(int x,int y,int hp){
    if(x>=1 && x<=n && y>=1 &&y<=m && map0[x][y] && !vis[x][y][hp]) return 1;
    else return 0;
}

void dfs(int x,int y,int hp,int k){
    if(k>m*n || k>ans) return;
    if(map0[x][y] == 4 && hp) hp=6;
    if(!hp) return;
    if(map0[x][y] == 3){
        if(k<ans)
            ans=k;
        return;
    }
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(judge(x0,y0,hp-1)){
            vis[x0][y0][hp-1]=1;
            dfs(x0,y0,hp-1,k+1);
            vis[x0][y0][hp-1]=0;
        }
    }
}

int main(){
    int x,y;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&map0[i][j]);
            if(map0[i][j] == 2) x=i,y=j;
        }
    }
    vis[x][y][6]=1;
    dfs(x,y,6,0);
    if(ans!=200)
        printf("%d\n",ans);
    else
        printf("-1\n");
    return 0;
}
*/
