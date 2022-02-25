/*
����:w*h������,��#����ʾ�췽��,��.����ʾ�ڷ���,ĳ�˳�ʼλ���ڡ�@'����ڿ�,
���������������ĸ�������,��ֻ���ߺڿ�,�ʴ����(�ڿ�)�����ߵĺڿ�ĸ������ж��٣�
w,h<=20.
ͬPOJ 1979 Red and Black��ͬһ����
����:http://acm.hdu.edu.cn/showproblem.php?pid=1312 or http://poj.org/problem?id=1979
˼·:bfs��dfs���ĸ������������'#'��,�������ĵ㶼���ó�'#',�����ٱ���,��ͳ�������.
*/
//ac bfs 15ms
//���Ӷ�O(w*h)=400
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

int w,h,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},cnt;
char mp[N][N];
struct State{
    int x,y;
    State(int x=0,int y=0):x(x),y(y){}
};

void bfs(int sx,int sy){
    queue<State> Q;
    mp[sx][sy]='#';
    Q.push(State(sx,sy));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=h && ny>=1 && ny<=w && mp[nx][ny] != '#'){
                cnt++;
                mp[nx][ny]='#';
                Q.push(State(nx,ny));
            }
        }
    }
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&w,&h) && w+h){
        cnt=1;
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        bfs(sx,sy);
        printf("%d\n",cnt);
    }
    return 0;
}

/*
//ac 15ms dfs
//ʱ�临�Ӷ�O(w*h)=400
#include<cstdio>
#include<cstring>
#define N 25
using namespace std;

int w,h,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},cnt;
char mp[N][N];

void dfs(int x,int y){
	if(mp[x][y] == '#')
		return;
	mp[x][y]='#';
	cnt++;
	int nx,ny;
	for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=h && ny>=1 && ny<=w && mp[nx][ny] != '#')
            dfs(nx,ny);
    }
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&w,&h) && w+h){
        cnt=0;
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        dfs(sx,sy);
        printf("%d\n",cnt);
    }
    return 0;
}
*/
