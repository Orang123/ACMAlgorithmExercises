/*
题意:摘自网上
一个城堡分成了m*n个块，然后给出了每个块一个数字，这个数字代表门的情况，
如果这个块西面有门，那么1就要加到这个数字中。如果这个块北面有门，那么2
就要加到这个数字中。如果这个块东面有门，那么4就要加到这个数字中。如果这
个块南面有门，那么8就加到这个数字中。输出城堡的房间数、城堡中最大房间所包括的方块数。
n,m<=50.
链接:http://poj.org/problem?id=1164
思路:方向按照西、北、东、南初始好,每次判断(mp[x][y] & 1<<i),如果
为1 说明这个方向不可走.
*/
//ac 0ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
using namespace std;

int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int n,m,mp[N][N],vis[N][N],cnt,ans,sum;

void dfs(int x,int y){
    int nx,ny;
    vis[x][y]=1;
    sum++;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>n || ny<1 || ny>m || vis[nx][ny] || (mp[x][y] & 1<<i))
            continue;
        dfs(nx,ny);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum=0;
            if(!vis[i][j]){
                cnt++;
                dfs(i,j);
                ans=max(ans,sum);
            }
        }
    }
    printf("%d\n",cnt);
    printf("%d",ans);
    return 0;
}
