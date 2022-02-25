/*
题意:n*m的网格.
oibh被突来的洪水淹没了>.<还好oibh总部有在某些重要的地方起一些围墙，
用*号表示，而一个封闭的*号区域洪水是进不去的……现在给出oibh的围墙建设图，
问oibh总部没被淹到的重要区域（由"0"表示）有多少。
n,m<=500.
链接:https://www.luogu.com.cn/problem/P1506
思路:
解法1:
dfs,n*m网格的行列范围设置为[1,n],[1,m].可以在网格外围设置0行,n+1行,
0列,m+1列表示洪水,从(0,0)开始dfs,将'o'全部淹没设置为'*',最后统计剩下的'0'
的个数,便是没被淹没的'0'的个数.

解法2:
可以枚举每个'O',dfs搜索'O'相连的'O'的块的个数,如果能够搜索走出迷宫边界,
则这些'O'的块就会被洪水淹没需要标记,如果不会走出迷宫边界,就不会被洪水淹没,
则累加此次搜索的'O'块的'O'的个数.
*/
//ac 47ms n*m迷宫外加一圈表示洪水
#include<cstdio>
#define N 510

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,sum;
char mp[N][N];

void dfs(int x,int y){
    mp[x][y]='*';
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<0 || nx>n+1 || ny<0 || ny>m+1 || mp[nx][ny] == '*')
            continue;
        dfs(nx,ny);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf(" %c",&mp[i][j]);
    }
    dfs(0,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j] == '0')
                sum++;
        }
    }
    printf("%d\n",sum);
    return 0;
}

/*
//ac 52ms
//可以枚举每个'O',dfs搜索'O'相连的'O'的块的个数,如果能够搜索走出迷宫边界,
//则这些'O'的块就会被洪水淹没需要标记,如果不会走出迷宫边界,就不会被洪水淹没,
//则累加此次搜索的'O'块的'O'的个数.
#include<cstdio>
#define N 510

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,ans,cnt,flag;
char mp[N][N];

void dfs(int x,int y){
	if(x<1 || x>n || y<1 || y>m){
		flag=0;
		return;
	}
    mp[x][y]='*';
    cnt++;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(mp[nx][ny] == '*')
            continue;
        dfs(nx,ny);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf(" %c",&mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j] == '0'){
            	cnt=0;
            	flag=1;
            	dfs(i,j);
            	if(flag)
            		ans+=cnt;
			}
        }
    }
    printf("%d\n",ans);
    return 0;
}
*/
