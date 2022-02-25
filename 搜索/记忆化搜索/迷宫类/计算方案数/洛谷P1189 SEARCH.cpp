/*
题意:r*c的网格,'.'表示可以通过,'X'表示不能通行,汽车
的起始位置用'*'表示.汽车可以向上下左右4个方向行驶,
现在给出n个汽车行驶的方向指令串,汽车在每个指定方向
行驶的距离不限,必须将n个指令都行驶完才行,现在要求出
汽车最终能够停下来的可能位置,用'*'标记.
说明:结果中的'*'号不能有汽车的初始位置.
链接:https://www.luogu.com.cn/problem/P1189
思路:dfs记忆化搜索.状态标记用vis[x][y][k]=0/1,表示在点(x,y)
已经执行到第k个指令串是否已经搜索过.
*/
//ac 73ms 记忆化搜索
#include<cstdio>
#include<cstring>
using namespace std;
char map0[52][52];
char a[1010][10];
bool vis[52][52][1010];//记忆化搜索 剪枝
int r,c,n,dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//上 右 下 左

int judgeDir(int i){
    if(a[i][0] == 'N') return 0;
    else if(a[i][0] == 'E') return 1;
    else if(a[i][0] == 'S') return 2;
    else return 3;
}

int judge(int x,int y){
    if(x>=1 && x<=r && y>=1 && y<=c) return 1;
    else return 0;
}

void dfs(int x,int y,int k){
    if(vis[x][y][k]) return;
    vis[x][y][k]=true;
    if(k == n+1){
        map0[x][y]='*';
        return;
    }
    int i=judgeDir(k);
    while(judge(x,y)){
        x+=dir[i][0];//在这个方向继续走
        y+=dir[i][1];
        if(map0[x][y] == 'X')
            return;
        dfs(x,y,k+1);
    }
}

int main(){
    int x,y;
    scanf("%d%d",&r,&c);
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            scanf(" %c",&map0[i][j]);
            if(map0[i][j] == '*'){
                map0[i][j]='.';
                x=i,y=j;
            }
        }
    }
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",a[i]);
    dfs(x,y,1);
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++)
            printf("%c",map0[i][j]);
        printf("\n");
    }
    return 0;
}
/*
BFS版本
#include <cstdio>
#include <queue>
using namespace std;
int n, m, k;
const int N = 55;
char a[N][N];
bool vis[N][N][1005];
const char w[] = {'N', 'S', 'W', 'E'};
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
struct node {
	int x;
	int y;
	int deep;
} ;
queue <node> q;
int l = 1, r;
int main () {
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++)
		scanf ("%s", a[i] + 1);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			if (a[i][j] == '*') {
				a[i][j] = '.';
				q.push((node){i, j, 1});
			}
		}
	}
	char last = 'X';
	scanf ("%d", &k);
	for (int dep = 1; dep <= k; dep ++) {
		char s[100];
		scanf ("%s", s + 1);
		if (s[1] == last) continue;
		last = s[1];
		for (int i = 0; i < 4; i ++) {
			if (w[i] == s[1]) {
				while (!q.empty() && q.front().deep == dep) {
					node t = q.front();
					q.pop();
					int nx = t.x, ny = t.y;
					while (1) {
						nx += dx[i];
						ny += dy[i];
						if (nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == 'X') {
							break;
						}
						if (vis[nx][ny][t.deep + 1]) break;
						vis[nx][ny][t.deep + 1] = 1;
						q.push((node){nx, ny, t.deep + 1});
					}
				}
			}
		}
	}
	while (!q.empty()) {
		a[q.front().x][q.front().y] = '*';
		q.pop();
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			printf ("%c", a[i][j]);
		}
		putchar ('\n');
	}
}
*/

/*
模拟暴力
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int r,c,n,map[60][60],ans[60][60];
char st[60][60],str[1000];
bool vis[60][60];
//vis数组是用来记录，当次search（）中ans[][]为1点，是上次serch()得来的ans[][]，
//还是由上次search()得来的ans[][]由这次search()移动得来的;
int dx[5]={0,-1,0,1,0},dy[5]={0,0,1,0,-1};
//方向，我是左上角为原点，向下为x的正方向，想又为y的正方向；
void search(int direct)
{
    memset(vis,0,sizeof(vis));//新的一 轮，就要重新开始
    for(int i=1;i<=r;i++)
    for(int j=1;j<=c;j++)
    {
        if(ans[i][j] && !vis[i][j])
        {
            int ddx=i+dx[direct],ddy=j+dy[direct];
            ans[i][j]=0;//它一移动原来的位置就不在有可能在有；
            while(map[ddx][ddy])//将其能到的点全标记；
            {
                ans[ddx][ddy]=1;
                vis[ddx][ddy]=true;
                ddx=ddx+dx[direct];ddy=ddy+dy[direct];
            }
        }
    }
}
int main()
{
    scanf("%d %d",&r,&c);
    for(int i=1;i<=r;i++)
    {
        scanf("%s",st[i]+1);
        for(int j=1;j<=c;j++)
        {
            if(st[i][j]=='*') map[i][j]=1,ans[i][j]=1;
            //最开始的位置，就是还没移动时的可能的位置；
            else if(st[i][j]=='.') map[i][j]=1;
            else map[i][j]=0;
        }
    }
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        if(str[0]=='N') search(1);//向上
        if(str[0]=='E') search(2);//向右
        if(str[0]=='S') search(3);//向下
        if(str[0]=='W') search(4);//向左
    }
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            if(ans[i][j]) printf("*");
            else
            {
                if(st[i][j]=='*') printf(".");
                else printf("%c",st[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}
*/
