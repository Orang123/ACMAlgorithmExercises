/*
����:һ��n*n��������,�ʹ�����������һ��ָ�����ߵ�����һ��ָ����������Ҫ���ٲ�.
����һ����t��ʾ����������T��
ÿ����������������,��һ��n�������̴�СΪn*n,�ڶ��б�ʾ��������,�����б�ʾ�յ�����
ÿһ�������չ���������ʿ���߷���,�����ٵĲ���������ߵ��յ�.
4<=n<=300.
����:http://poj.org/problem?id=1915
˼·:bfs.�������� ����8���߷�.
���dir[8][2]={{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}}.
��Ϊn<=300,dfs��TLE �ʱ���O(8^(300*300)) 1sʱ�� TLE.
*/
//ac 141ms bfs
//ʱ�临�Ӷ�O(n*n)=300*300=90000
#include<cstdio>
#include<queue>
#include<cstring>
#define N 310
using namespace std;

int n,dir[8][2]={{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}},vis[N][N],ex,ey;
struct State{
    int x,y,s;
    State(int x=0,int y=0,int s=0):x(x),y(y),s(s){}
};

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x == ex && tp.y == ey)
            break;
        Q.pop();
        for(int i=0;i<8;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=0 && nx<n && ny>=0 && ny<n && !vis[nx][ny]){
                vis[nx][ny]=1;
                Q.push(State(nx,ny,tp.s+1));
            }
        }
    }
    return tp.s;
}

int main(){
    int T,sx,sy;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        scanf("%d%d",&sx,&sy);
        scanf("%d%d",&ex,&ey);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}

/*
��Ϊn<=300.
�ʱ���O(8^(300*300)) 1sʱ�� TLE
ֱ��dfs�ᳬʱ

��Ϊ�������������߷� �����ǳ���������4�������ߵ�,����޷�Ӧ�õ�������dfs�������پ����֦
*/
