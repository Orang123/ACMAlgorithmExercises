/*
题意:l层,每层长宽分别是r、c的三维网格l*r*c,'#'表示不能行走的单元格,
'.'表示空单元格可以行走.初始位置为'S',目的地位'E',在每层可以向东南西北
4个方向的相邻格子移动,并且可以从当前位置的当前层k向上一层k+1或下一层k-1移动,
位置(x,y)不变.这6个方向的移动每次需要花费1分钟,问从'S'到达'E'最少需要多少分钟.
l,r,c<=30
链接:http://poj.org/problem?id=2251
思路:三个维度的网格,对应的有6个方向东南西北、上下.
因此dir[6][3]={{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}.
{0,-1,0}表示在同一层从(x,y)移动到(x-1,y)
{1,0,0}表示在第k层的(x,y)移动到第k+1层的(x,y)
*/
//ac 32ms bfs
//时间复杂度O(l*r*c)=30^3=2700
#include<cstdio>
#include<queue>
#include<cstring>
#define N 35
#define INF 0x3f3f3f3f
using namespace std;

int l,r,c,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N][N];
struct State{
    int k,x,y,s;
    State(int k=0,int x=0,int y=0,int s=0):k(k),x(x),y(y),s(s){}
};

int bfs(int sk,int sx,int sy,int ek,int ex,int ey){
    queue<State> Q;
    mp[sk][sx][sy]='#';
    Q.push(State(sk,sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.k == ek && tp.x == ex && tp.y == ey)
            return tp.s;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=r && ny>=1 && ny<=c && mp[tp.k][nx][ny]!='#'){
                mp[tp.k][nx][ny]='#';
                Q.push(State(tp.k,nx,ny,tp.s+1));
            }
        }
        if(tp.k<l && mp[tp.k+1][tp.x][tp.y]!='#'){
            mp[tp.k+1][tp.x][tp.y]='#';
            Q.push(State(tp.k+1,tp.x,tp.y,tp.s+1));
        }
        if(tp.k>1 && mp[tp.k-1][tp.x][tp.y]!='#'){
            mp[tp.k-1][tp.x][tp.y]='#';
            Q.push(State(tp.k-1,tp.x,tp.y,tp.s+1));
        }
    }
    return -1;
}

int main(){
    int sf,sx,sy,ef,ex,ey,ans;
    while(scanf("%d%d%d",&l,&r,&c) && l+r+c){
        for(int k=1;k<=l;k++){
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    scanf(" %c",&mp[k][i][j]);
                    if(mp[k][i][j] == 'S'){
                        sf=k;
                        sx=i,sy=j;
                    }
                    else if(mp[k][i][j] == 'E'){
                        ef=k;
                        ex=i,ey=j;
                    }
                }
            }
        }
        ans=bfs(sf,sx,sy,ef,ex,ey);
        if(ans!=-1)
            printf("Escaped in %d minute(s).\n",ans);
        else
            printf("Trapped!\n");
    }
    return 0;
}

/*
//ac 32ms bfs 用dir[6][3]表示6个方向分别是北、南、西、东、上、下
//dir[6][3]={{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}
//时间复杂度O(l*r*c)=30^3=2700
#include<cstdio>
#include<queue>
#include<cstring>
#define N 35
#define INF 0x3f3f3f3f
using namespace std;

int l,r,c,dir[6][3]={{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}};
char mp[N][N][N];
struct State{
    int k,x,y,s;
    State(int k=0,int x=0,int y=0,int s=0):k(k),x(x),y(y),s(s){}
};

int bfs(int sk,int sx,int sy){
    queue<State> Q;
    mp[sk][sx][sy]='#';
    Q.push(State(sk,sx,sy,0));
    State tp;
    int nk,nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<6;i++){
            nk=tp.k+dir[i][0];
            nx=tp.x+dir[i][1];
            ny=tp.y+dir[i][2];
            if(nk>=1 && nk<=l && nx>=1 && nx<=r && ny>=1 && ny<=c && mp[nk][nx][ny]!='#'){
                if(mp[nk][nx][ny] == 'E')
                    return tp.s+1;
                mp[nk][nx][ny]='#';
                Q.push(State(nk,nx,ny,tp.s+1));
            }
        }
    }
    return -1;
}

int main(){
    int sf,sx,sy,ans;
    while(scanf("%d%d%d",&l,&r,&c) && l+r+c){
        for(int k=1;k<=l;k++){
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    scanf(" %c",&mp[k][i][j]);
                    if(mp[k][i][j] == 'S'){
                        sf=k;
                        sx=i,sy=j;
                    }
                }
            }
        }
        ans=bfs(sf,sx,sy);
        if(ans!=-1)
            printf("Escaped in %d minute(s).\n",ans);
        else
            printf("Trapped!\n");
    }
    return 0;
}
*/

/*
//TLE dfs
//时间复杂度O(6^(30*30*30))
#include<cstdio>
#include<queue>
#include<cstring>
#define N 35
#define INF 0x3f3f3f3f
using namespace std;

int l,r,c,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},dp[N][N][N],ans;
int ek,ex,ey;
char mp[N][N][N];

void dfs(int k,int x,int y,int s){
    if(s>=dp[k][x][y])
        return;
    dp[k][x][y]=s;
    if(k == ek && x == ex && y == ey){
        ans=min(ans,s);
        return;
    }
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=r && ny>=1 && ny<=c && mp[k][nx][ny]!='#')
            dfs(k,nx,ny,s+1);
    }
    if(k<l && mp[k+1][x][y]!='#')
        dfs(k+1,x,y,s+1);
    if(k>1 && mp[k-1][x][y]!='#')
        dfs(k-1,x,y,s+1);
}

int main(){
    int sf,sx,sy;
    while(scanf("%d%d%d",&l,&r,&c) && l+r+c){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        for(int k=1;k<=l;k++){
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    scanf(" %c",&mp[k][i][j]);
                    if(mp[k][i][j] == 'S'){
                        sf=k;
                        sx=i,sy=j;
                    }
                    else if(mp[k][i][j] == 'E'){
                        ek=k;
                        ex=i,ey=j;
                    }
                }
            }
        }
        dfs(sf,sx,sy,0);
        if(ans!=INF)
            printf("Escaped in %d minute(s).\n",ans);
        else
            printf("Trapped!\n");
    }
    return 0;
}
*/

/*
//TLE 迭代加深搜索dfs+曼哈顿距离剪枝
//复杂度O(6^(30*30*30))
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 35
#define INF 0x3f3f3f3f
using namespace std;

int l,r,c,dir[6][3]={{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}},dp[N][N][N];
int ek,ex,ey;
char mp[N][N][N];

int dfs(int k,int x,int y,int s,int tot){
    //剪枝1:如果到达当前层(x,y)位置所用时不能比之前记录的用时更少就不必搜索,当前已经不能更优,后续更不可能更优了.
    if(s>=dp[k][x][y])
        return 0;
    dp[k][x][y]=s;
    //剪枝2:曼哈顿距离剪枝 如果和目标点在同一层 当前时间s+剩下最短曼哈顿距离需要的时间还比规定的时间大 则返回
    if(k == ek && abs(ex-x)+abs(ey-y)>tot-s)
        return 0;
    if(k == ek && x == ex && y == ey)
        return 1;
    int nk,nx,ny;
    for(int i=0;i<6;i++){
        nk=k+dir[i][0];
        nx=x+dir[i][1];
        ny=y+dir[i][2];
        if(nk>=1 && nk<=l && nx>=1 && nx<=r && ny>=1 && ny<=c && mp[nk][nx][ny]!='#'){
            if(dfs(nk,nx,ny,s+1,tot))
                return 1;
        }
    }
    return 0;
}

int main(){
    int sf,sx,sy;
    while(scanf("%d%d%d",&l,&r,&c) && l+r+c){
        for(int k=1;k<=l;k++){
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    scanf(" %c",&mp[k][i][j]);
                    if(mp[k][i][j] == 'S'){
                        sf=k;
                        sx=i,sy=j;
                    }
                    else if(mp[k][i][j] == 'E'){
                        ek=k;
                        ex=i,ey=j;
                    }
                }
            }
        }
        int flag=0;
        for(int i=1;i<=100;i++){//时间上限为30+30+30,从第1层走到30层需要30-1,从(1,1)走到(30,30)需要30-1+30-1
            memset(dp,0x3f,sizeof(dp));
            if(dfs(sf,sx,sy,0,i)){
                flag=1;
                printf("Escaped in %d minute(s).\n",i);
                break;
            }
        }
        if(!flag)
            printf("Trapped!\n");
    }
    return 0;
}
*/
