/*
����:n*m������,1����վ̨,���ÿ��(x,y)���Ӿ��������վ̨1
����̾���,������е����1����̾���õ��洢����.
1<=n,m<=182.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2645
˼·:
����1:��ÿ����(x,y)Ϊ�����һ��bfs,��һ������1վ̨ʱ����,
��¼��̾���res[x][y]=tp.d;
����2:�����е�1�����,�����������λ�õ���̾���
res[nx][ny]=tp.d+1;
*/
//ac 452ms bfs ���е�(x,y)��Ϊ��㿪ʼbfs,�����һ�������1��ͽ���
//ʱ�临�Ӷ�O(n*m*n*m)
#include<cstdio>
#include<queue>
#include<cstring>
#define N 200
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N],res[N][N];
char mp[N][N];
struct State{
    int x,y,d;
    State(int x=0,int y=0,int d=0):x(x),y(y),d(d){}
};

void bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == '1'){
            res[sx][sy]=tp.d;
            break;
        }
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && !vis[nx][ny]){
                vis[nx][ny]=1;
                Q.push(State(nx,ny,tp.d+1));
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                memset(vis,0,sizeof(vis));
                bfs(i,j);
                printf("%d",res[i][j]);
                if(j!=m)
                    printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}

/*
//ac 31ms �����е�1���,�����������λ�õ���̾���
//ʱ�临�Ӷ�O(n*m)
#include<cstdio>
#include<queue>
#include<cstring>
#define N 200
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},res[N][N];
char mp[N][N];
struct State{
    int x,y,d;
    State(int x=0,int y=0,int d=0):x(x),y(y),d(d){}
};
queue<State> Q;

void bfs(){
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && res[nx][ny] == -1){//res[nx][ny] == -1 �����ǻ�δ�������,�Ѿ�����ĵ� �Ѿ�����̾�����
                res[nx][ny]=tp.d+1;
                Q.push(State(nx,ny,tp.d+1));
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
    	memset(res,-1,sizeof(res));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
            	if(mp[i][j] == '1'){
            		res[i][j]=0;//1�� ���������1�����Լ�����,�����̾���Ϊ0
            		Q.push(State(i,j,0));
				}
			}
        }
        bfs();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                printf("%d",res[i][j]);
                if(j!=m)
                    printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}
*/
