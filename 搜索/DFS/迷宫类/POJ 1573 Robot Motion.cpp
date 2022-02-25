/*
����:ժ������
��һ��N*M�����򣬻����˴ӵ�һ�еĵڼ��н��룬������ȫ����'N' , 'S' , 'W' , 'E' ��
�ߵ�ĳ�������ʱ��ֻ�ܰ��ո�����ָ���ķ��������һ��������������ܷ��߳���Ƭ����
�����ܣ����뿪ʼ��Ȧ�Ĳ�����Ȧ�Ĵ�С��
n,m<=10.
����:http://poj.org/problem?id=1573
˼·:dfs,ֻ�����ߵķ������͵�ǰλ�õ�mp[x][y]����һ��.
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
