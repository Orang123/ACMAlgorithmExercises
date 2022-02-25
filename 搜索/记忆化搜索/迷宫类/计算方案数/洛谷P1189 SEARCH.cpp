/*
����:r*c������,'.'��ʾ����ͨ��,'X'��ʾ����ͨ��,����
����ʼλ����'*'��ʾ.������������������4��������ʻ,
���ڸ���n��������ʻ�ķ���ָ�,������ÿ��ָ������
��ʻ�ľ��벻��,���뽫n��ָ���ʻ�����,����Ҫ���
���������ܹ�ͣ�����Ŀ���λ��,��'*'���.
˵��:����е�'*'�Ų����������ĳ�ʼλ��.
����:https://www.luogu.com.cn/problem/P1189
˼·:dfs���仯����.״̬�����vis[x][y][k]=0/1,��ʾ�ڵ�(x,y)
�Ѿ�ִ�е���k��ָ��Ƿ��Ѿ�������.
*/
//ac 73ms ���仯����
#include<cstdio>
#include<cstring>
using namespace std;
char map0[52][52];
char a[1010][10];
bool vis[52][52][1010];//���仯���� ��֦
int r,c,n,dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//�� �� �� ��

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
        x+=dir[i][0];//��������������
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
BFS�汾
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
ģ�Ⱪ��
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int r,c,n,map[60][60],ans[60][60];
char st[60][60],str[1000];
bool vis[60][60];
//vis������������¼������search������ans[][]Ϊ1�㣬���ϴ�serch()������ans[][]��
//�������ϴ�search()������ans[][]�����search()�ƶ�������;
int dx[5]={0,-1,0,1,0},dy[5]={0,0,1,0,-1};
//�����������Ͻ�Ϊԭ�㣬����Ϊx������������Ϊy��������
void search(int direct)
{
    memset(vis,0,sizeof(vis));//�µ�һ �֣���Ҫ���¿�ʼ
    for(int i=1;i<=r;i++)
    for(int j=1;j<=c;j++)
    {
        if(ans[i][j] && !vis[i][j])
        {
            int ddx=i+dx[direct],ddy=j+dy[direct];
            ans[i][j]=0;//��һ�ƶ�ԭ����λ�þͲ����п������У�
            while(map[ddx][ddy])//�����ܵ��ĵ�ȫ��ǣ�
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
            //�ʼ��λ�ã����ǻ�û�ƶ�ʱ�Ŀ��ܵ�λ�ã�
            else if(st[i][j]=='.') map[i][j]=1;
            else map[i][j]=0;
        }
    }
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        if(str[0]=='N') search(1);//����
        if(str[0]=='E') search(2);//����
        if(str[0]=='S') search(3);//����
        if(str[0]=='W') search(4);//����
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
