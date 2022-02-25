/*
题意:幻象迷宫可以认为是无限大的，不过它由若干个N*M的矩阵重复组成。
矩阵中有的地方是道路，用'.'表示；有的地方是墙，用'#'表示。
LHX和WD所在的位置用'S'表示。也就是对于迷宫中的一个点(x,y)，
如果(x mod n,y mod m)是'.'或者'S'，那么这个地方是道路；
如果(x mod n,y mod m)是'#'，那么这个地方是墙。
LHX和WD可以向上下左右四个方向移动，当然不能移动到墙上。
请你告诉LHX和WD，它们能否走出幻象迷宫（如果它们能走到距离起点无限远处，
就认为能走出去）。如果不能的话，LHX就只好启动城堡的毁灭程序了……
当然不到万不得已，他不想这么做。。。
题意推荐看洛谷网友GNAQ的图解。
n,m<=1500.
链接:https://www.luogu.com.cn/problem/P1363
思路:dfs.这个题,题意刚开始一直看不懂,比较怪吧.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1600
using namespace std;
char map0[N][N];
/*
vis[x][y][0]代表这个矩阵中某个点是否被遍历过,
vis[x][y][1]代表所遍历的矩阵中(x,y)这个点的在真正遍历的那个矩阵的横坐标
vis[x][y][2]代表所遍历的矩阵中(x,y)这个点的在真正遍历的那个矩阵的纵坐标
*/
int n,m,vis[N][N][3];
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int dfs(int x,int y,int x0,int y0){
    /*
    当该点被遍历过,并且和之前实际记录的点坐标不同,
    则说明这个点分别在两个不同的矩阵被遍历到了,
    则说明可以走距离起点无限远
    */
    if(vis[x][y][0] && (vis[x][y][1]!=x0 || vis[x][y][2]!=y0))
        return 1;
    vis[x][y][0]=1,vis[x][y][1]=x0,vis[x][y][2]=y0;//记录遍历到该点的实际坐标
    int x1,y1,x2,y2;
    for(int i=0;i<4;i++){
        //+n +m是因为 从一个矩阵的第一行向上走,是走到上面矩阵的最后一行,
        //列同理 从第一列走到左面矩阵的最后一列
        //取余是对从最后一列走到右面矩阵第一列,最后一行走到下面矩阵第一行.
        x1=(x+dir[i][0]+n)%n;//x1 y1是当前这个样例中的矩阵的该点的等效点的坐标都是正值
        y1=(y+dir[i][1]+m)%m;
        x2=x0+dir[i][0];//x2 y2记录的永远是每个矩阵的实际坐标
        y2=y0+dir[i][1];
        if(map0[x1][y1]!='#'&& (!vis[x1][y1][0] || vis[x1][y1][1]!=x2 || vis[x1][y1][2]!=y2))//这个点被遍历过 但是 实际坐标不同也可以遍历,或者没遍历过但实际坐标不同
            if(dfs(x1,y1,x2,y2)) return 1;
    }
    return 0;
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(vis,0,sizeof(vis));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                scanf(" %c",&map0[i][j]);
                if(map0[i][j] == 'S') x=i,y=j;
            }
        }
        if(dfs(x,y,x,y)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
