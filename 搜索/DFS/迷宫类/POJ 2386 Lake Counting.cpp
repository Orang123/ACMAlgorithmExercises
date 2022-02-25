/*
题意:n*m的网格,'W'表示水,'.'表示旱地,
可以连接8个方向,问有几块独立的水域.
n,m<=100.
链接:http://poj.org/problem?id=2386
思路:dfs
*/
//ac 32ms
#include<stdio.h>
#define max_size 101
#define For(i,n) for(int i=0;i<n;i++)
char map[max_size][max_size];
int dir[8][2]= {{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,-1},{1,0},{1,1}};
void DFS(int i,int j)
{
    if(map[i][j]=='.') return;
    map[i][j]='.';
    For(k,8) DFS(i+dir[k][0],j+dir[k][1]);
}
int main()
{
    int n,m,sum;
    For(i,max_size)
    map[0][i]=map[i][0]='.';
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        getchar();
        sum=0;
        for(int i=1; i<=n+1; i++)
            map[i][m+1]='.';
        for(int i=1; i<=m+1; i++)
            map[n+1][i]='.';
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                scanf(" %c",map[i]+j);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if(map[i][j]=='W')
                {
                    DFS(i,j);
                    sum++;
                }
        printf("%d\n",sum);
    }
    return 0;
}
