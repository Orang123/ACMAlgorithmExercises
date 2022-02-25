/*
����:����һ����ά���飺
int maze[5][5] = {

	0, 1, 0, 0, 0,

	0, 1, 0, 1, 0,

	0, 0, 0, 0, 0,

	0, 1, 1, 1, 0,

	0, 0, 0, 1, 0,

};
����ʾһ���Թ�,���е�1��ʾǽ��,0��ʾ�����ߵ�·,ֻ�ܺ����߻�������,
����б����,Ҫ�������ҳ������Ͻǵ����½ǵ����·��.���·���ϵĵ������.
����:http://poj.org/problem?id=3984
˼·:bfs ��4��������չ״̬,��¼һ��State(x,y)�Ķ�ά����pre[N][N],��¼
���·�����ӵ���һ�����ӵ�State.��:pre[nx][ny]=tp(State);
*/
//ac 16ms bfs
#include<cstdio>
#include<queue>
#include<cstring>
#define N 5
using namespace std;

int mp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
struct State{
    int x,y;
    State(int x=0,int y=0):x(x),y(y){}
}pre[N][N];

void bfs(){
    queue<State> Q;
    mp[0][0]=1;
    Q.push(State(0,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x == 4 && tp.y == 4)
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=0 && nx<=4 && ny>=0 && ny<=4 && !mp[nx][ny]){
                mp[nx][ny]=1;//ֻ��һ��bfs ֱ���޸�mp[nx][ny]=1 �����߼���,�����ٿ�vis[N][N]���鵥�������
                pre[nx][ny]=tp;
                Q.push(State(nx,ny));
            }
        }
    }
}

void print(int x,int y){
    if(!x && !y)
        printf("(0, 0)\n");
    else{
        print(pre[x][y].x,pre[x][y].y);
        printf("(%d, %d)\n",x,y);
    }
}

int main(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            scanf("%d",&mp[i][j]);
    }
    bfs();
    print(4,4);
    return 0;
}

/*
//ac 0ms dfs ��ͨ��dfs�Ѿ���ac,�Ͳ��ؿ��ǵ������������������پ����֦��
//��Ϊdfs���б�����(4,4)��·������һ������̵�,����Ҫ��¼���µ���ÿ����(x,y)����̾������.
//dp[x][y]��ʾ�ߵ�(x,y)��ʱ������̾���.
//��֦: ����ǰ���߷��� ���þ��벻�ܱ�֮ǰ�ߵ�(nx,ny)������Сʱ�Ͳ��� ��������ȥ.
//ʱ�临�Ӷ�(4^25) ÿ�����Ӷ�����������������4�������� �ܹ�25������ ����ʵ�����ڵĵ��ǲ����ظ������ߵ�,���ʵ�ʸ��Ӷȱ��������ҪС���
#include<cstdio>
#include<queue>
#include<cstring>
#define N 5
using namespace std;

int mp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},dp[N][N];
struct State{
    int x,y;
    State(int x=0,int y=0):x(x),y(y){}
}pre[N][N];

void dfs(int x,int y,int s){
    if(x == 4 && y == 4)
        return;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        //��֦: ����ǰ���߷��� ���þ��벻�ܱ�֮ǰ�ߵ�(nx,ny)������Сʱ�Ͳ��� ��������ȥ.
        if(nx>=0 && nx<=4 && ny>=0 && ny<=4 && !mp[nx][ny] && s+1<dp[nx][ny]){
            dp[nx][ny]=s+1;
            pre[nx][ny]=State(x,y);
            dfs(nx,ny,s+1);
        }
    }
}

void print(int x,int y){
    if(!x && !y)
        printf("(0, 0)\n");
    else{
        print(pre[x][y].x,pre[x][y].y);
        printf("(%d, %d)\n",x,y);
    }
}

int main(){
    memset(dp,0x3f,sizeof(dp));
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            scanf("%d",&mp[i][j]);
    }
    dp[0][0]=0;
    dfs(0,0,0);
    print(4,4);
    return 0;
}
*/
