/*
题意:摘自网上
共有28张骨牌,给出一些7*8的矩阵，每两个相邻的数字可以表示一个骨牌，
一种骨牌只能用一次，问说骨牌有多少种摆法。
链接:https://www.luogu.com.cn/problem/UVA211
思路:在配对骨牌时,考虑横或竖两种方式配对,并且7*8矩阵一种序号的骨牌
只能出现一次,dfs回溯.
*/
//ac 50ms dfs回溯
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
using namespace std;

int dir[2][2]={{0,1},{1,0}};
int cas,mp[N][N],g[N][N],vis[N][N],val[30],ans;

void print(int (*a)[N]){
    for(int i=1;i<=7;i++){
        for(int j=1;j<=8;j++)
            printf("%4d",a[i][j]);
        printf("\n");
    }
    printf("\n");
}

void dfs(int x,int y){
    if(y == 9){
        x++;
        y=1;
    }
    if(x == 8){//(x,y)之前的位置一定全部放置完了骨牌,因此无需剪枝
        ans++;
        print(vis);
        return;
    }
    if(vis[x][y])
        dfs(x,y+1);
    else{
        int nx,ny,k;
        for(int i=0;i<2;i++){
            nx=x+dir[i][0];
            ny=y+dir[i][1];
            k=g[mp[x][y]][mp[nx][ny]];
            if(nx>7 || ny>8 || vis[nx][ny] || val[k])
                continue;
            vis[x][y]=vis[nx][ny]=k;
            val[k]=1;
            dfs(x,y+1);
            vis[x][y]=vis[nx][ny]=0;
            val[k]=0;
        }
    }
}

int main(){
    int cnt=0;
    for(int i=0;i<=6;i++){
        for(int j=i;j<=6;j++)
            g[i][j]=g[j][i]=++cnt;//骨牌的 pip和bone的映射关系 注意在配对时 不考虑前后i,j的顺序
    }
    while(scanf("%d",&mp[1][1])!=EOF){
        cas++;
        ans=0;
        memset(vis,0,sizeof(vis));
        memset(val,0,sizeof(val));
        for(int i=1;i<=7;i++){
            for(int j=1;j<=8;j++){
                if(i+j == 2) continue;
                scanf("%d",&mp[i][j]);
            }
        }
        if(cas!=1)
            printf("\n\n\n");
        printf("Layout #%d:\n\n",cas);
        print(mp);
        printf("Maps resulting from layout #%d are:\n\n",cas);
        dfs(1,1);
        printf("There are %d solution(s) for layout #%d.\n",ans,cas);
    }
    return 0;
}
