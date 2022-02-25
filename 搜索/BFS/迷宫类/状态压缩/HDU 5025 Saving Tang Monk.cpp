/*
//2014 ACM/ICPC Asia Regional Guangzhou Online
//题意摘自网上
题意:孙悟空救师傅,一个n*n的网格,'K'表示孙悟空,'T'表示唐僧,
'#'表示墙,'.'表示路,数字'1'~'9'表示钥匙,'S'表示蛇怪.
孙悟空可以上下左右移动,每移动一格花费1分钟时间,如果遇到蛇怪,
打死蛇怪另外花费1分钟,最多有5个蛇怪,孙悟空要集齐m种钥匙才能救出师傅,
但是取钥匙有一个规则,只有取到前i种钥匙,才能取第i+1种钥匙,孙悟空除了墙
以外,任何位置都可以到达,唐僧的位置也可以去,但是钥匙没有集齐即使到了'T'点
也无法救出唐僧,求救出唐僧的最少时间,如救不出输出"impossible".
0<=n<=100.0<=m<=9.
注意:每种钥匙i,可能在多个位置有存放.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5025
思路:因为杀死蛇会多花1分钟,所以使用优先队列按照用时最少出队.
有因为钥匙实际在取的时候必须按照顺序取,那么就不必状态压缩,
假如要取第i种钥匙,可以在状态标记里判断当前取到钥匙的数量是否达到了i-1.
对于有蛇怪的位置,如果之前消灭了蛇,那么再次走过的时候就不必再多花1分钟去
消灭,也就是说需要判断每个蛇的位置是否之前消灭过 来决定花费时间是1还是2,
那么蛇需要状态压缩,在输入处理时将蛇'S'重新处理为'A'、'B'、'C'、'D'、'E',
最多有5条蛇.
*/
//ac 343ms bfs优先队列+四维数组状态压缩
#include<cstdio>
#include<queue>
#include<cstring>
#define N 110
using namespace std;

//最多5条蛇,最大可能数值为2^5-1=31.
//vis[x][y][key][sk]=0/1 表示(x,y)位置下携带钥匙数量为前key种,消灭蛇的组合情况为sk的状态是否出现过.
int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][10][32];
char mp[N][N];
struct State{
    int x,y,key,sk,t;
    State(int x=0,int y=0,int key=0,int sk=0,int t=0):x(x),y(y),key(key),sk(sk),t(t){}
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
    vis[sx][sy][0][0]=1;
    Q.push(State(sx,sy,0,0,0));
    State tp;
    int nx,ny;
    char ch;
    while(!Q.empty()){
        tp=Q.top();
        //到达'T'点,并且携带钥匙数量达到m 返回当前所用的最少时间
        if(mp[tp.x][tp.y] == 'T' && tp.key == m)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny))
                continue;
            ch=mp[nx][ny];
            //'.' 'T' 'K' 根据实际携带钥匙和消灭蛇的组合不同 可以再次重复经过
            if((ch == '.' || ch == 'T' || ch == 'K') && !vis[nx][ny][tp.key][tp.sk]){
                vis[nx][ny][tp.key][tp.sk]=1;
                Q.push(State(nx,ny,tp.key,tp.sk,tp.t+1));
            }
            //遇到蛇怪,判断是否已经消灭过该点的蛇
            else if(ch>='A' && ch<='E' && !vis[nx][ny][tp.key][tp.sk]){
                vis[nx][ny][tp.key][tp.sk]=1;
                if(tp.sk & 1<<(ch-'A')){//已经消灭过该点的蛇,再次到达时 用时1
                    vis[nx][ny][tp.key][tp.sk]=1;
                    Q.push(State(nx,ny,tp.key,tp.sk,tp.t+1));
                }
                else{//还未消灭该点的蛇,到达时 用时2
                    vis[nx][ny][tp.key][tp.sk|1<<(ch-'A')]=1;//将该点蛇的状态压入
                    Q.push(State(nx,ny,tp.key,tp.sk|1<<(ch-'A'),tp.t+2));
                }
            }
            //遇到钥匙
            else if(ch>='1' && ch<='9' && !vis[nx][ny][tp.key][tp.sk]){
                int nk;
                vis[nx][ny][tp.key][tp.sk]=1;//标记到达该点时 还未获取钥匙时的状态,避免重复多余的状态再次入队
                if(tp.key == ch-'1')//判断前面是否凑齐了 前ch-'1'种钥匙,如果凑齐了,那么当前位置第ch种钥匙便可携带
                    nk=tp.key+1;//钥匙数+1
                else//否则若携带钥匙数比ch-'1'小或大于等于ch,携带钥匙数量不变是原来的状态.
                    nk=tp.key;
                vis[nx][ny][nk][tp.sk]=1;//这里新钥匙下的状态一定是为入队过的,因为vis[nx][ny][tp.key][tp.sk]=0
                Q.push(State(nx,ny,nk,tp.sk,tp.t+1));
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy,ans,k;
    while(scanf("%d%d",&n,&m) && n+m){
        k=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'K')
                    sx=i,sy=j;
                else if(mp[i][j] == 'S'){//将蛇的位置重新设置为'A'、'B'、'C'、'D'、'E',需要状态压缩判断不同状态走到该点时的用时为1还是2
                    mp[i][j]='A'+k;
                    k++;
                }
            }
        }
        ans=bfs(sx,sy);
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("impossible\n");
    }
    return 0;
}

/*
//ac 46ms bfs+三维数组状压
//摘自博客:https://blog.csdn.net/yuanjunlai141/article/details/50954656
#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
using namespace std;
const int maxn=115;
char map[maxn][maxn];
struct Point
{
    int x,y;
}d;
struct PT
{
    int x,y,t,snake,key;
    PT()
    {
        ;
    }
    PT(int xx,int yy,int tt,int s,int k)
    {
        x=xx,y=yy,t=tt,snake=s,key=k;
    }
    friend bool operator<(const PT a,const PT b)
    {
        return a.t>b.t;
    }
};
int n,Key;
int dx[4]= {0,-1,0,1};
int dy[4]= {-1,0,1,0};
bool vis[maxn][maxn][15];
int dis[maxn][maxn][15];
int Snake[maxn][maxn];
bool check(int x,int y)
{
    if(x<0||x>=n||y<0||y>=n||map[x][y]=='#')
        return false;
     return true;
}
priority_queue<PT>que;
int bfs(Point start)
{
    int nx,ny;
    memset(vis,false,sizeof(vis));
    nx=start.x,ny=start.y;
    while(!que.empty())
    {
        que.pop();
    }
    vis[nx][ny][0]=true;
    que.push(PT(nx,ny,0,0,0));
    while(!que.empty())
    {
        PT now;
        now=que.top();
        que.pop();
        if(map[now.x][now.y]=='T'&&now.key==Key)  ///钥匙凑齐并且找到唐僧
            return now.t;
        for(int i=0; i<4; i++)
        {
            nx=now.x+dx[i];
            ny=now.y+dy[i];
            bool flag=check(nx,ny);
            if(!flag||vis[nx][ny][now.key])
                continue;
             if(now.key+1+'0'==map[nx][ny])///刚好是下一个要找的钥匙
            {
                    vis[nx][ny][now.key+1]=true;
                    que.push(PT(nx,ny,now.t+1,now.snake,now.key+1));
            }
            else if(map[nx][ny]=='S')///遇到蛇
            {
                if(!(now.snake&(1<<Snake[nx][ny])))///没杀过这条蛇
                {
                    vis[nx][ny][now.key]=true;
                    que.push(PT(nx,ny,now.t+2,now.snake|(1<<Snake[nx][ny]),now.key));
                }
                else
                {
                    vis[nx][ny][now.key]=true;
                    que.push(PT(nx,ny,now.t+1,now.snake,now.key));
                }
            }
            else///其他所有情况都包括....
            {
                vis[nx][ny][now.key]=true;
                que.push(PT(nx,ny,now.t+1,now.snake,now.key));
            }

        }

    }
    return -1;
}
int main()
{
    int tot;
    while(cin>>n>>Key)
    {
        if(n==0)
            break;
        tot=0;
        for(int i=0; i<n; i++)
        {
            cin>>map[i];
            for(int j=0; j<n; j++)
            {
                if(map[i][j]=='K')
                {
                    d.x=i,d.y=j;
                }
                if(map[i][j]=='S')
                {
                    Snake[i][j]=tot++;
                }
            }
        }
        int ans=bfs(d);
        if(ans==-1)
            cout<<"impossible"<<endl;
        else
            cout<<ans<<endl;
    }
    return 0;
}
*/
