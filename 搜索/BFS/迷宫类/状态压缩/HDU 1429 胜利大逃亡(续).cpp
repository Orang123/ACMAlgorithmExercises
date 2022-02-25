/*
题意:Ignatius再次被魔王抓走了(搞不懂他咋这么讨魔王喜欢)这次魔王汲取了上次的教训,
把Ignatius关在一个n*m的地牢里,并在地牢的某些地方安装了带锁的门,钥匙藏在地牢另外的某些地方.
刚开始Ignatius被关在(sx,sy)的位置,离开地牢的门在(ex,ey)的位置.Ignatius每分钟只能从一个坐标
走到相邻四个坐标中的其中一个.魔王每t分钟回地牢视察一次,若发现Ignatius不在原位置便把他拎回去.
经过若干次的尝试,Ignatius已画出整个地牢的地图.现在请你帮他计算能否再次成功逃亡.只要在魔王下次
视察之前走到出口就算离开地牢,如果魔王回来的时候刚好走到出口或还未到出口都算逃亡失败.
. 代表路
* 代表墙
@ 代表Ignatius的起始位置
^ 代表地牢的出口
A-J 代表带锁的门,对应的钥匙分别为a-j
a-j 代表钥匙，对应的门分别为A-J
2<=n,m<=20.t>0.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1429
思路:状态压缩bfs,对多有a~j 10个钥匙,用10个二进制位1来表示 对应的10进制数值 为0~(2^10-1).
因此状态标记数组为vis[N][N][1<<10].
*/
//ac 343ms bfs a~j的状态判断为!vis[nx][ny][tp.sta|1<<(ch-'a')],之前的状态要获得当前的钥匙再在(nx,ny)的位置上判断钥匙的状态是否出现过
//vis判断标记放在所有分支内
//时间复杂度O(20*20*1024)=4*10^6
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

//a~j最多10个钥匙 用10个二进制位1来表示 对应的10进制数值 为0~(2^10-1)
int n,m,t,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][1<<10];
char mp[N][N];
struct State{
    int x,y,m,sta;
    State(int x=0,int y=0,int m=0,int sta=0):x(x),y(y),m(m),sta(sta){}
};

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy][0]=1;
    Q.push(State(sx,sy,0,0));
    State tp;
    int nx,ny,ch;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == '^'){
            if(tp.m<t)
                return tp.m;
            else
                return -1;
        }
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx<1 || nx>n || ny<1 || ny>m)
                continue;
            ch=mp[nx][ny];
            if(ch == '*')
                continue;
            if(ch>='a' && ch<='j' && !vis[nx][ny][tp.sta|1<<(ch-'a')]){
                vis[nx][ny][tp.sta|1<<(ch-'a')]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta|1<<(ch-'a')));
            }
            else if(ch>='A' && ch<='J' && (tp.sta & 1<<(ch-'A')) && !vis[nx][ny][tp.sta]){
                vis[nx][ny][tp.sta]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta));
            }
            //注意这里一定要加上(ch == '.' || ch == '@' || ch == '^')的判断 否则,前面不满足的钥匙的条件但 !vis[nx][ny][tp.sta]满足的条件就会错误入队 这里debug了好久
            else if((ch == '.' || ch == '@' || ch == '^') && !vis[nx][ny][tp.sta]){
                vis[nx][ny][tp.sta]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta));
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d%d",&n,&m,&t)!=EOF){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}

/*
//ac 296ms bfs  a~j的状态判断为!vis[nx][ny][tp.sta] 即:到达(nx,ny)的状态判断并不算入(nx,ny)上的钥匙
//vis判断统一放在 所有分支之前
//这种判断标记做法 实际复杂度是偏大的,因为如果是(nx.ny)是a~j则并未对vis[nx][ny][tp.sta]标记
//如果还有别的较长路径 到达该点和之前状态一样会重复入队
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

int n,m,t,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][1<<10];
char mp[N][N];
struct State{
    int x,y,m,sta;
    State(int x=0,int y=0,int m=0,int sta=0):x(x),y(y),m(m),sta(sta){}
};

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy][0]=1;
    Q.push(State(sx,sy,0,0));
    State tp;
    int nx,ny,ch;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == '^'){
            if(tp.m<t)
                return tp.m;
            else
                return -1;
        }
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            //对于(nx,ny)有a~j钥匙的情况 实际只需判断 之前的状态为未获得该位置钥匙时的状态是否出现过即可
            //这种判断标记做法 实际复杂度是偏大的,因为如果是(nx.ny)是a~j则并未对vis[nx][ny][tp.sta]标记
            //如果还有别的较长路径 到达该点和之前状态一样会重复入队
            if(nx<1 || nx>n || ny<1 || ny>m || vis[nx][ny][tp.sta])
                continue;
            ch=mp[nx][ny];
            if(ch == '*')
                continue;
            if(ch>='a' && ch<='j'){
                vis[nx][ny][tp.sta|1<<(ch-'a')]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta|1<<(ch-'a')));
            }
            else if(ch>='A' && ch<='J' && (tp.sta & 1<<(ch-'A'))){
                vis[nx][ny][tp.sta]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta));
            }
            else if(ch == '.' || ch == '@' || ch == '^'){
                vis[nx][ny][tp.sta]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta));
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d%d",&n,&m,&t)!=EOF){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
*/
