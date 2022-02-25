/*
题意:摘自网上
根据输入的n*m字符矩阵，分别找到girl和cat字符串的数量。
n,m<=1000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5706
思路:dfs
*/
//ac 421ms dfs回溯
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

char str1[10]="girl",str2[10]="cat";
int n,m,dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}},cnt1,cnt;
char mp[N][N];

void dfs(int x,int y,char *str,int k){
    int nx,ny;
    if(mp[x][y] == str[k]){
        if(str[k+1] == '\0'){
            cnt++;
            return;
        }
        for(int i=0;i<4;i++){
            nx=x+dir[i][0];
            ny=y+dir[i][1];
            if(nx<1 || nx>n || ny<1 || ny>m)
                continue;
            dfs(nx,ny,str,k+1);
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp[i][j] == 'g')
                    dfs(i,j,str1,0);
            }
        }
        cnt1=cnt;
        cnt=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp[i][j] == 'c')
                    dfs(i,j,str2,0);
            }
        }
        printf("%d %d\n",cnt1,cnt);
    }
    return 0;
}
