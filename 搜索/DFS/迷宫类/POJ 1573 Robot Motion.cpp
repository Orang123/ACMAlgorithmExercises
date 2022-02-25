/*
题意:摘自网上
有一个N*M的区域，机器人从第一行的第几列进入，该区域全部由'N' , 'S' , 'W' , 'E' ，
走到某个区域的时候只能按照该区域指定的方向进行下一步，问你机器人能否走出该片区域，
若不能，输入开始绕圈的步数和圈的大小。
n,m<=10.
链接:http://poj.org/problem?id=1573
思路:dfs,只是所走的方向必须和当前位置的mp[x][y]方向一致.
*/
//ac 0ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

char str[4]={'W','N','E','S'},mp[N][N];
int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int n,m,col,vis[N][N],step[N][N];

int dfs(int x,int y){
    vis[x][y]=1;
    int nx,ny;
    for(int i=0;i<4;i++){
        if(mp[x][y] != str[i])
            continue;
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>n || ny<1 || ny>m){
            printf("%d step(s) to exit\n",step[x][y]+1);
            return 1;
        }
        if(vis[nx][ny]){
            printf("%d step(s) before a loop of %d step(s)\n",step[nx][ny],step[x][y]+1-step[nx][ny]);
            return 1;
        }
        step[nx][ny]=step[x][y]+1;
        if(dfs(nx,ny))
            return 1;
    }
    return 0;
}

int main(){
    while(scanf("%d%d%d",&n,&m,&col) && n+m+col){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf(" %c",&mp[i][j]);
        }
        step[1][col]=0;
        dfs(1,col);
    }
    return 0;
}
