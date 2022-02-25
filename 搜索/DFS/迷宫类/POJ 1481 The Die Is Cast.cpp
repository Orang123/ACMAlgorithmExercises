/*
题意:摘自网上
w*h的网格,由 * . X组成，其中每块由*和X组成的部分是独立的一个面，
每个面上由X来组成数字表示，求这个图上每个面的数字是多少，并从小到大排序。
w,h<=50.
链接:http://poj.org/problem?id=1481
思路:可以对每个'*'开始dfs1的遍历,在dfs1找到'X'时,再对X相连的情况
进行dfs2,每进入一次dfs2都使得当前模块不连通得到'X'块的数量+1.
*/
//ac 0ms dfs回溯
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
using namespace std;

int w,h,dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}},sum[N*N],cnt;
char mp[N][N];

void dfs2(int x,int y){
    mp[x][y]='*';
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>h || ny<1 || ny>w)
            continue;
        if(mp[nx][ny] == 'X')
            dfs2(nx,ny);
    }
}

void dfs1(int x,int y){
    mp[x][y]='.';
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>h || ny<1 || ny>w)
            continue;
        //注意这里要先判断'X',因为Xdfs2遍历完后,会使得mp[nx][ny]变成'*',方便直接进行dfs1 否则X会使得'*'被分割,使得cnt数目偏大
        if(mp[nx][ny] == 'X'){
            sum[cnt]++;//当前'*'构成的块中不连通的'X'构成的块 数目加1
            dfs2(nx,ny);
        }
        if(mp[nx][ny] == '*')//'*'的dfs1放在 'X'的dfs2后
            dfs1(nx,ny);
    }
}

int main(){
    int cas=0;
    while(scanf("%d%d",&w,&h) && w+h){
        cnt=0;
        cas++;
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                if(mp[i][j] == '*'){
                    cnt++;
                    dfs1(i,j);
                }
            }
        }
        sort(sum+1,sum+1+cnt);
        printf("Throw %d\n",cas);
        for(int i=1;i<=cnt;i++){
            if(i == 1)
                printf("%d",sum[i]);
            else
                printf(" %d",sum[i]);
        }
        printf("\n\n");
    }
    return 0;
}
