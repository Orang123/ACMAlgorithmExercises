/*
题意:公主被关在一个两层的迷宫里,迷宫的入口是S(1,1,0),公主的位置用'P'表示,
时空传输机用'#'表示,墙用'*'表示,平地用'.'表示.骑士们一进入时空传输机就会
被转到另一层的相对位置,但如果被转到的位置是墙的话,那骑士们就会被撞死.骑士
们在一层中只能前后左右移动,每移动一格花1时刻.层间的移动只能通过时空传输机,
且不需要任何时间.如果骑士们能够在T时刻能找到公主就输出“YES”,否则输出“NO”.
1<=n,m<=10.
注意:摘自杭电Discuss模块
1.碰到'#'传送们必传送到另一层,没有第二种选择,不能选择在同层上下左右扩展.
2.两边都是传送门时,或者一边是传送门一边是墙时,这两种情况是死路.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2102
思路:bfs,因为传送门不需要花费时间,因此采用优先队列.
*/
//ac 0ms bfs
//复杂度O(n*m*2)=200
#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#define N 11
using namespace std;

//前4个方向是在同一层上下左右移动,后2个方向是在层间上下移动.
//因为要判断走过的是否是'#'传送门选择是否可以在层间移动,所以无法用mp原图里对一走过的点做标记,只能用vis做标记.
int n,m,t,dir[6][3]={{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,1},{0,0,-1}},vis[N][N][2];
char mp[N][N][2];
struct State{
    int x,y,z,t;
    State(int x=0,int y=0,int z=0,int t=0):x(x),y(y),z(z),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int bfs(){
    priority_queue<State> Q;
    vis[1][1][0]=1;
    Q.push(State(1,1,0,0));
    int nx,ny,nz;
    State tp;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.x][tp.y][tp.z] == 'P'){
            if(tp.t<=t)
                return 1;
            else
                return 0;
        }
        Q.pop();
        for(int i=0;i<6;i++){
            //不是传送门 无法在层间移动 只能在前4个方向移动
            if(mp[tp.x][tp.y][tp.z]!='#' && i>=4)
                continue;
            //是传送门 只能在层间移动 只能在后2个方向移动
            if(mp[tp.x][tp.y][tp.z] == '#' && i<4)
                continue;
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            nz=tp.z+dir[i][2];
            if(nx<1 || nx>n || ny<1 || ny>m || nz<0 || nz>1 || mp[nx][ny][nz] == '*' || vis[nx][ny][nz])
                continue;
            //'#'传送门 传到传送门是无意义 只能再穿回来
            if(mp[tp.x][tp.y][tp.z] == '#' && mp[nx][ny][nz] == '#')
                continue;
            if(i<4){
                vis[nx][ny][nz]=1;
                Q.push(State(nx,ny,nz,tp.t+1));
            }
            else{
                vis[nx][ny][nz]=1;
                Q.push(State(nx,ny,nz,tp.t));
            }
        }
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d%d",&n,&m,&t);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf(" %c",&mp[i][j][0]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf(" %c",&mp[i][j][1]);
        }
        if(bfs())
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

/*
//ac 15ms dfs
//数据较弱 实际复杂度可达 5^(10*10*2)=6^200
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char str[15][15][15];
int temp[15][15][15];
int n,m,t,sign;
int xx[]={1,0,-1,0};
int yy[]={0,-1,0,1};
void dfs(int x,int y,int z,int sum){
   int i;
   if(x<0||x>=m||y<0||y>=n||z<0||z>1||sign==1)      //出界或已找到就不搜索
   return;
   if(sum>t)                                        //超过时间就不搜索
   return;
   if(str[x][y][z]=='P'){                           //找到之后标记
   sign=1;
   return;
   }
   if(temp[x][y][z]==1||str[x][y][z]=='*')          //这条路已经走过或者是墙就不搜索
   return;
   if(str[x][y][z]=='#'){
   if(str[x][y][1-z]!='#')                          //当是传送门时并另一端不是墙时搜索
   dfs(x,y,1-z,sum);
   return;                                          //这个一定要回溯，否者假如两边都是
   }                                                //传送门的话就会死循环
   temp[x][y][z]=1;
   for(i=0;i<4;i++)
   dfs(x+xx[i],y+yy[i],z,sum+1);
   temp[x][y][z]=0;
}
int main(){
    int cur,i,j,k;
    scanf("%d",&cur);
    while(cur--){
        scanf("%d%d%d",&m,&n,&t);
        getchar();
        for(i=0;i<2;i++)
        for(j=0;j<m;j++)
        for(k=0;k<n;k++)
        cin>>str[j][k][i];
        memset(temp,0,sizeof(temp));
        sign=0;
        dfs(0,0,0,0);
        if(sign)
        puts("YES");
        else
        puts("NO");
    }
    return 0;
}
*/
