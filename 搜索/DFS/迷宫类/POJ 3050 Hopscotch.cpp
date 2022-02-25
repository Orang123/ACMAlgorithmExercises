/*
题意:摘自网上
给定一个5*5的地图，每个格子上有一个数字。从一个格子出发（上下左右4个方向），
走5步将数字连起来可以构造出一个6位数。问该地图可以构造出多少个不同的6位数。
链接:http://poj.org/problem?id=3050
思路:开一个大小为10^6的val数组记录,6位数的数值是否已经搜索过,注意相同的格子
是可以重复走的,只用步数做限制条件.
*/
//ac 32ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6
#define M 1000000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int mp[N][N],val[M],ans;

void dfs(int x,int y,int sum,int cnt){
    sum=sum*10+mp[x][y];
    if(cnt == 5){
        if(!val[sum]){
            val[sum]=1;
            ans++;
        }
        return;
    }
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>5 || ny<1 || ny>5)
            continue;
        dfs(nx,ny,sum,cnt+1);
    }
}

int main(){
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++)
            scanf("%d",&mp[i][j]);
    }
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++)
            dfs(i,j,0,0);
    }
    printf("%d",ans);
    return 0;
}
