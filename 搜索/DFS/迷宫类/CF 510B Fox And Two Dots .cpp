/*
题意:在mp迷宫是否能找相同颜色所构成的环.
链接:https://codeforces.ml/problemset/problem/510/B
思路:dfs.枚举每个点的颜色,看是否会回到之前访问过的点,
注意对于上一步刚走过的点,不能往回走,可以记录前驱节点或
上一次所走的方向,只要不走上次方向的反方向就好.
*/
//ac
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,vis[60][60];
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char mp[60][60];

int dfs(int x,int y,char col,int fx,int fy){
    vis[x][y]=1;
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(x0<1 || x0>n || y0<1 || y0>m) continue;
        if(x0 == fx && y0 == fy) continue;//不能回到之前得到父亲格子,因为这样并不是一个环,最小的环是2x2,个数是4,和父亲相等个数是2
        if(mp[x0][y0] != col) continue;//dfs按照相同的颜色去搜索
        if(vis[x0][y0]) return 1;//若颜色相同并且回到了之前访问过的点,则说明构成了一个相同颜色的环
        if(dfs(x0,y0,col,x,y)) return 1;
    }
    return 0;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> mp[i][j];
        }
    }
    int flag=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!vis[i][j]){//枚举每一个点的颜色
                if(dfs(i,j,mp[i][j],-1,-1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag) break;
    }
    if(flag) printf("Yes");
    else printf("No");
    return 0;
}

/*
//ac 30ms 记录上一步的方向,不能走反方向
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,vis[60][60];
int dir[4][2]={{1,0},{0,-1},{0,1},{-1,0}};//S W E N
char mp[60][60];

int dfs(int x,int y,char col,int d){
    vis[x][y]=1;
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(x0<1 || x0>n || y0<1 || y0>m || i+d == 3) continue;//i+d == 3是互为反方向
        if(mp[x0][y0] != col) continue;//dfs按照相同的颜色去搜索
        if(vis[x0][y0]) return 1;//若颜色相同并且回到了之前访问过的点,则说明构成了一个相同颜色的环
        if(dfs(x0,y0,col,i)) return 1;
    }
    return 0;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> mp[i][j];
        }
    }
    int flag=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!vis[i][j]){//枚举每一个点的颜色
                if(dfs(i,j,mp[i][j],-1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag) break;
    }
    if(flag) printf("Yes");
    else printf("No");
    return 0;
}
*/
