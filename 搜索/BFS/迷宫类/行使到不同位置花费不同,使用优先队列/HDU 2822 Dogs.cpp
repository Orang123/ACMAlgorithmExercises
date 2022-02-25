/*
����:��һֻС��Ҫȥ����һֻС��,������ֻС�������궼֪��,
m*n�ĵ�ͼ����������Ԫ��,'X'��ʾ����,'.'��ʾ�յ�,
���С����������'X',�����ڸ���,����������ǿյ�'.',
���С������Ŀ���ʱ������Ҫ�ڵ���С������.
1<=m,n<=1000.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4198
˼·:�����ߵ�'X'��'.'����ʱ��ֱ�Ϊ0��1,ʹ����ͨ�Ķ���
�ȳ��ӵĻ���ʱ�䲻һ�������ٵ�,���Գ�����Ҫ���յ�ǰ����
ʱ�����ٵ�״̬�ȳ���,���ʹ�����ȶ���priority_queue<State> Q;
����״̬����ʱ�����ٵ��ȳ���.
*/
//ac 670ms bfs
//ʱ�临�Ӷ�O(m*n)=10^6
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1100
using namespace std;

int m,n,d,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ex,ey;
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int bfs(int sx,int sy){
    priority_queue<State> Q;
    mp[sx][sy]='#';
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.top();
        if(tp.x == ex && tp.y == ey)
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(mp[nx][ny] == '.'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+1));
            }
            else if(mp[nx][ny] == 'X'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t));
            }
        }
    }
    return tp.t;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&m,&n) && m+n){
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        scanf("%d%d",&sx,&sy);
        scanf("%d%d",&ex,&ey);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
