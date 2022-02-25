/*
����:m*n������,��@����ʾ�;�,��*����ʾ����,��֪'@'�;�֮���������ҡ����ڶԽ���
8������ĺ������;����໥��ͨ��,�ʹ��ж��ٸ���������ͨ�;�.
1<=m,n<=100.
ͬPOJ 1979 Oil Deposits��ͬһ����
����:http://acm.hdu.edu.cn/showproblem.php?pid=1241 or http://poj.org/problem?id=1562
˼·:bfs��dfs���Ǵ�ÿ��'@'��ʼ��8�����������'@'��,�������ĵ㶼���ó�'#',�����ٱ���,
��ͳ���ܹ������˼���bfs��dfs,�����ʵ�ʶ�����ͨ��֧�;�����.
*/
//ac bfs 31ms
//ʱ�临�Ӷ�O(m*n)=10^4 ÿ����(x,y)ֻ�����һ��
#include<cstdio>
#include<queue>
#include<cstring>
#define N 110
using namespace std;

//dir[8][2]�����������ҡ��ڶԽ�����˸�����
int m,n,dir[8][2]={{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}},cnt;
char mp[N][N];
struct State{
    int x,y;
    State(int x=0,int y=0):x(x),y(y){}
};

void bfs(int sx,int sy){
    queue<State> Q;
    mp[sx][sy]='*';
    Q.push(State(sx,sy));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<8;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=m && ny>=1 && ny<=n && mp[nx][ny] == '@'){
                mp[nx][ny]='*';
                Q.push(State(nx,ny));
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&m,&n) && m+n){
        cnt=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j] == '@'){
                    cnt++;
                    bfs(i,j);
                }
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}

/*
//ac 32ms dfs
//ʱ�临�Ӷ�O(m*n)=10^4 ÿ����(x,y)ֻ�����һ��
#include<cstdio>
#include<queue>
#include<cstring>
#define N 110
using namespace std;

int m,n,dir[8][2]={{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}},cnt;
char mp[N][N];

void dfs(int x,int y){
	int nx,ny;
	for(int i=0;i<8;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=m && ny>=1 && ny<=n && mp[nx][ny] == '@'){
            mp[nx][ny]='*';
            dfs(nx,ny);
        }
    }
}

int main(){
    while(scanf("%d%d",&m,&n) && m+n){
        cnt=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j] == '@'){
                    cnt++;
                    mp[i][j]='*';
                    dfs(i,j);
                }
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}
*/
