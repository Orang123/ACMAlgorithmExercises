/*
题意:m×n的迷宫,‘S’表示小狗的起点,‘D'表示小狗要走到的终点,'.'表示空地可以走,
‘X’表示墙不能走,‘1’～‘9’代表当前地炸药的数量,往上下左右走一步花费1秒钟,走到
带有炸药的地方可以一次性将炸药全部带走,无需额外花费时间,炸一面墙需多花1秒钟,
问小狗从S走到D最少需要多上时间.
2<=n,m<=8.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2128
思路:bfs.只是要注意走到每个格子可以拿走这个格子上的炸药使得这个格子变为
正常的空地,而这个当前这个状态再往回走时这个地方就是空地没有炸药了,因为之前
已经拿过了,但是对于之前出队扩展的别的状态该地仍旧是有炸药的.以及走到'X'墙可
以用一个炸药多花费1秒钟将其引爆使其变成空地可以正常通行,等之后再回到这个地方时,
就已经是空地了,这样对于bfs入队的状态再回到该点时,无需消耗炸药就可以直接通过这块空地,
综上所述每个状态对应的当前的迷宫的格子状态是不同的.因此需要将mp[N][N]放入bfs要扩展的
转态State中.因为遇到'X'需要花费2s才能到达该点,而遇到空地只需花费1s,因此队列层序遍历
扩展同阶段的状态对于不同方向、方案,花费的时间并不一样,有可能先入队的遇到的全是'X',实际
花费时间较长,而后入队的一直在走空地'.',因此要用优先队列priority_queue 按照每个状态所用时
最少的先出队.

注意:
而对于迷宫中位置(x,y) 避免其重复遍历导致bfs重复入队相同的状态导致MLE.
但是实际对于每个位置重复遍历时,可能携带的炸药数量并不同,并不单方面按照
当前携带炸弹数量比位置(x,y)之前到达时携带炸弹数量多来判断是否可以入队扩展状态,
因为每个状态的对应的迷宫状态是不同的,需要走到'D'实际要炸毁的墙'X'的数目也是不同
的,即使当前携带的炸药数较少,但是实际当前状态对应的迷宫到达'D'地的墙'X'也少,实际
花费的时间可能较少,而之前状态虽然携带的炸药多,但之前状态对应的迷宫中的墙'X'也较多,
有可能炸药数不够炸毁所有需要通过的'X',导致不能到达'D'地,或者可能需要炸毁的'X'墙较多,
实际到达'D'地需要花费的时间也较多.
因此对于迷宫中每个点(x,y)的状态 并不能单方面根据携带炸药数判断重复走过的就不能再走,
而是对于重复位置的状态也让其入队扩展状态,只是为了避免bfs MLE,要设置每个位置 携带的炸药数
的状态最多能入队的次数的上限,这里HDU的数据较弱,实际设置为5,即:vis[x][y][tp.num]<=5即可,
不影响实际结果,为了保险也可以设置地较大一点 50、100都可以.
*/
/*
//几组数据
input
6 5
S.XX1
X.1X1
XX.X.
XXXXX
XXXXX
XXXDX
2 6
S.1XXD
1..XXX
4 4
S1X1
XXXX
XXDX
XXXX
6 2
S1
..
1X
XX
XX
DX

output
17
9
8
9
*/
//ac 0ms bfs
//时间复杂度>=N*N*M=64*576=36864
#include<cstdio>
#include<queue>
#include<cstring>
#define N 10
#define M 600
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][M];
struct State{
    int x,y,s,num;
    char mp[N][N];
    bool operator < (const State &x)const{
        return s>x.s;//因为走到'X'和走到'.'花费时间不同 所以优先队列 按照时间最少出队
    }
};

int bfs(State node){
    priority_queue<State> Q;
    vis[node.x][node.y][node.num]++;
    Q.push(node);
    State tp,next;
    while(!Q.empty()){
        tp=Q.top();
        Q.pop();
        for(int i=0;i<4;i++){
            next.x=tp.x+dir[i][0];
            next.y=tp.y+dir[i][1];
            //(x,y)携带炸弹数num vis[x][y][num]的入队次数不能超过5次,为了降低bfs重复状态入队的次数
            //实际每个点 携带炸弹数即使相同或不同状态所对应的迷宫状态中'X'的数目也是不同的,因此不能简单对(x,y)携带的炸弹数进行判重
            //而是尽可能让其入队 但限制最大入队次数 可以设置高点 50、100等.
            if(next.x<1 || next.x>n || next.y<1 || next.y>m || vis[next.x][next.y][tp.num]>5)
                continue;
            if(tp.mp[next.x][next.y] == '.'){
                next.num=tp.num;
                vis[next.x][next.y][next.num]++;
                next.s=tp.s+1;
                memcpy(next.mp,tp.mp,sizeof(tp.mp));
                Q.push(next);
            }
            else if(tp.mp[next.x][next.y]>='1' && tp.mp[next.x][next.y]<='9'){
                next.num=tp.num+tp.mp[next.x][next.y]-'0';//实际增加的炸药数为tp.mp[next.x][next.y]-'0'
                vis[next.x][next.y][next.num]++;
                next.s=tp.s+1;
                memcpy(next.mp,tp.mp,sizeof(tp.mp));
                next.mp[next.x][next.y]='.';//取完炸药后 就会变成'.'
                Q.push(next);
            }
            else if(tp.mp[next.x][next.y] == 'X' && tp.num>=1){//要炸毁'X' 至少需要一个炸药
                next.num=tp.num-1;
                vis[next.x][next.y][next.num]++;
                next.s=tp.s+2;//爆照需要1s,走到'X'还需要1s 共2s
                memcpy(next.mp,tp.mp,sizeof(tp.mp));
                next.mp[next.x][next.y]='.';//爆炸之后 'X'就会变成'.'
                Q.push(next);
            }
            else if(tp.mp[next.x][next.y] == 'D')//到达'D'点 需花费tp.s+1
                return tp.s+1;
        }
    }
    return -1;
}

int main(){
    State node;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&node.mp[i][j]);
                if(node.mp[i][j] == 'S'){
                    node.x=i;
                    node.y=j;
                    node.num=0;
                    node.s=0;
                    node.mp[i][j]='.';//这里一定要'S'初始位置设置为'.',因为'S'点可能再次走过时携带的炸弹数目不同
                }
            }
        }
        printf("%d\n",bfs(node));
    }
    return 0;
}

/*
//ac 15ms IDA* 曼哈顿距离剪枝+炸弹最大携带数目剪枝
//dp[x][y]表示(x,y)点之前走过状态能携带的最多的炸弹数目
//这个做法其实也是有点问题的,dp[x][y]记录的炸弹数目只能更大的时候才会扩展,
//但实际携带炸弹数目不同时,网格的状态也不同了,墙的数目也是不同的,只能说数据较水.
//正解应该只是IDA*+曼哈顿距离剪枝,只有一个剪枝,但是这个做法复杂度太大,会TLE.
//参考博客:https://blog.csdn.net/Force_CHL/article/details/76855997
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define M 600
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},dp[N][N],ex,ey,flag;
char mp[N][N];

//s为走到当前(x,y)花费的时间 tot为从起点'S'到达终点'D' 规定要花费的时间
int dfs(int x,int y,int num,int s,int tot){
    //剪枝1:如果当前行走方案 携带的炸弹数目不能比之前更多 就返回
    if(dp[x][y]>=num)
        return 0;
    dp[x][y]=num;
    if(s == tot)
        return mp[x][y] == 'D';
    if(s>tot)//注意因为 炸毁墙要2s,所以有可能时间会刚好跳过tot,这就会导致 到达D状态 被错误记录炸弹数目,导致后面较小的 时间 会被错误剪枝,答案错误
        return 0;
    //剪枝2:曼哈顿距离剪枝 如果当前位置不考虑后续路径中'X'按照最短路径直接能走到'D'点还需要花费的时间已经超过规定的时间tot-s 就返回
    //(ex,ey)为'D'点坐标
    //if(s+abs(ex-x)+abs(ey-y)>tot)//不加这个曼哈顿剪枝 也能15ms ac
    	//return 0;
    int nx,ny,q;
    char tp;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        tp=mp[nx][ny];
        if(nx<1 || nx>n || ny<1 || ny>m)
            continue;
        if(mp[nx][ny] == '.' || mp[nx][ny] == 'D' || mp[nx][ny] == 'S'){
            q=dp[nx][ny];
            if(dfs(nx,ny,num,s+1,tot))
                return 1;
            dp[nx][ny]=q;//回溯后dp值要重新赋值
        }
        else if(mp[nx][ny]>='1' && mp[nx][ny]<='9'){
            int p=mp[nx][ny]-'0';
            mp[nx][ny]='.';
            q=dp[nx][ny];
            if(dfs(nx,ny,num+p,s+1,tot))
                return 1;
            dp[nx][ny]=q;
            mp[nx][ny]=tp;
        }
        else if(mp[nx][ny] == 'X' && num>=1){
            mp[nx][ny]='.';
            q=dp[nx][ny];
            if(dfs(nx,ny,num-1,s+2,tot))
                return 1;
            dp[nx][ny]=q;
            mp[nx][ny]=tp;
        }
    }
    return 0;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S'){
                    sx=i;
                    sy=j;
                    mp[i][j]='.';//这里一定要'S'初始位置设置为'.',因为'S'点再次走过时携带的炸弹数目不同
                }
                else if(mp[i][j] == 'D'){
                    ex=i;
                    ey=j;
                }
            }
        }
        //升序迭代加深搜索,枚举搜索从'S'出发到达'D'点最多花费的时间i
        //根据当前位置(x,y)到达'D'点的剩余时间进行剪枝 如果超过规定时间i 则返回
        for(int i=1;i<=40;i++){//这里上界是随机取的,实际应尽可能取的大一些,主要能搜索出满足条件的i即可
            flag=0;
            memset(dp,-1,sizeof(dp));
            if(dfs(sx,sy,0,0,i)){//因为i升序,第一个满足条件的i即是最短时间
                flag=1;
                printf("%d\n",i);
                break;
            }
        }
        if(!flag)
            printf("-1\n");
    }
    return 0;
}
*/

/*
//TLE IDA*+曼哈顿距离剪枝
//这是真正意义上的正解,但因为只是根据每次的深度去剪枝,没有采用位置的标记数组,会有重复的遍历 不可避免.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define M 600
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ex,ey,flag;
char mp[N][N];

//s为走到当前(x,y)花费的时间 tot为从起点'S'到达终点'D' 规定要花费的时间
int dfs(int x,int y,int num,int s,int tot){
    //剪枝2:曼哈顿距离剪枝 如果当前位置不考虑后续路径中'X'按照最短路径直接能走到'D'点还需要花费的时间已经超过规定的时间tot-s 就返回
    //(ex,ey)为'D'点坐标
    if(s == tot)
        return mp[x][y] == 'D';
    if(s+abs(ex-x)+abs(ey-y)>tot)
        return 0;
    if(s>tot)
        return 0;
    int nx,ny;
    char tp;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        tp=mp[nx][ny];
        if(nx<1 || nx>n || ny<1 || ny>m)
            continue;
        if(mp[nx][ny] == '.' || mp[nx][ny] == 'D' || mp[nx][ny] == 'S'){
            if(dfs(nx,ny,num,s+1,tot))
                return 1;
        }
        else if(mp[nx][ny]>='1' && mp[nx][ny]<='9'){
            int p=mp[nx][ny]-'0';
            mp[nx][ny]='.';
            if(dfs(nx,ny,num+p,s+1,tot))
                return 1;
            mp[nx][ny]=tp;
        }
        else if(mp[nx][ny] == 'X' && num>=1){
            mp[nx][ny]='.';
            if(dfs(nx,ny,num-1,s+2,tot))
                return 1;
            mp[nx][ny]=tp;
        }
    }
    return 0;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S'){
                    sx=i;
                    sy=j;
                    mp[i][j]='.';//这里一定要'S'初始位置设置为'.',因为'S'点再次走过时携带的炸弹数目不同
                }
                else if(mp[i][j] == 'D'){
                    ex=i;
                    ey=j;
                }
            }
        }
        //升序迭代加深搜索,枚举搜索从'S'出发到达'D'点最多花费的时间i
        //根据当前位置(x,y)到达'D'点的剩余时间进行剪枝 如果超过规定时间i 则返回
        for(int i=1;i<=40;i++){//这里上界是随机取的,实际应尽可能取的大一些,主要能搜索出满足条件的i即可
            flag=0;
            if(dfs(sx,sy,0,0,i)){//因为i升序,第一个满足条件的i即是最短时间
                flag=1;
                printf("%d\n",i);
                break;
            }
        }
        if(!flag)
            printf("-1\n");
    }
    return 0;
}
*/

/*
//ac 1887ms 标准做法 判断地图(x,y)不同炸药数量时 地图状态的不同
//设置 vector<State>vist[8][8][560]; //走到地图每个位置得到不同炸药数量的地图状态有没有存在过
//从S到D，所经过的每个位置得到的炸药数量可能不等，就算得到的炸药数量相等，
//但每个到达当前位置时的地图的状态不同。所以我们不仅必须判断在每个位置得到的炸药数是否存在过，
//而且还要判断得到的这些炸药数在相同情况下不同地图的状态。
#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
using namespace std;

struct State
{
    short state[8];//地图每行压缩的状态，
};
struct node
{
    int x,y; //当前走到的位置
    int time,explosiveNumb; //走过的时间，得到的炸药数量
    State s;  //走过后的地图状态
    friend bool operator<(const node &a,const node &b) //优先队列以时间最小的顺序取
    {
        return a.time>b.time;
    }
};

int n,m;
char map[10][10];
vector<State>vist[8][8][560]; //走到地图每个位置得到不同炸药数量的地图状态有没有存在过

void init()
{
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        for(int k=0; k<559; k++)
        vist[i][j][k].clear();
}
bool judge(int x,int y,int numb,short state[])
{
    int length=vist[x][y][numb].size();
    for(int i = 0; i < length ;i++)
    {
        int j;
        for(j = 0; j<n ; j++)
            if(vist[x][y][numb][i].state[j]!=state[j])
            break;
        if(j==n) //当前将要走的state[]地图状态，不必再加入队列（即己经存在过）
            return false;
    }
    //当前将要走的地图状态没存在过，需加入队列
    return true;
}
int bfs(int sx,int sy)
{
    int dir[4][2]={0,1,0,-1,1,0,-1,0};
    priority_queue<node>q;
    node p,tp;

    init();
    p.x=sx;
    p.y=sy;
    p.time=0;
    p.explosiveNumb=0;
    for(int i=0;i<n;i++)
    {
        p.s.state[i]=0;
        //压缩每行地图的状态，位置是 1 表示不存在任何东西
        for(int j=0;j<m;j++)
            if(map[i][j]=='.')
        p.s.state[i]|=(1<<j);
    }

    vist[sx][sy][0].push_back(p.s);
    q.push(p);
    while(!q.empty())
    {
        p=q.top();
        q.pop();
        for(int e=0;e<4;e++)
        {
            tp=p;
            tp.x+=dir[e][0];
            tp.y+=dir[e][1];
            tp.time++;
            if(tp.x>=0&&tp.x<n&&tp.y>=0&&tp.y<m)
            {
                if(!(tp.s.state[tp.x]&(1<<tp.y))&&map[tp.x][tp.y]=='X'&&!tp.explosiveNumb) //表示将要走的位置是现在还没炸的墙，并且身上没有炸药
                    continue ;
                if(!(tp.s.state[tp.x]&(1<<tp.y))&&map[tp.x][tp.y]>'0'&&map[tp.x][tp.y]<='9') //表示将要走的位置是没有取走的炸药
                {
                    tp.explosiveNumb+=map[tp.x][tp.y]-'0';
                    tp.s.state[tp.x]|=1<<tp.y; //取走后变成 "."
                }
                else if(!(tp.s.state[tp.x]&(1<<tp.y))&&map[tp.x][tp.y]=='X'&&tp.explosiveNumb)  //表示将要走的位置是现在还没炸的墙，身上有炸药
                {
                    tp.explosiveNumb--;
                    tp.s.state[tp.x]|=1<<tp.y; //炸完后变成 "."
                    tp.time++;
                }
                else if(map[tp.x][tp.y]=='D')
                    return tp.time;
                if(judge(tp.x,tp.y,tp.explosiveNumb,tp.s.state)) //判断走到当前位置的炸药数量与地图状态是否没有存在过？为真没存在过，否则为存在过
                vist[tp.x][tp.y][tp.explosiveNumb].push_back(tp.s),q.push(tp);
            }
        }
    }
    return -1;
}
int main()
{
    int sx,sy;
    while(scanf("%d%d",&n,&m)>0)
    {
        if(n==0&&m==0)
            break;
        for(int i=0;i<n;i++)
            scanf("%s",map[i]);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
            if(map[i][j]=='S')
            sx=i,sy=j;
        printf("%d\n",bfs(sx,sy));
    }
}
*/
