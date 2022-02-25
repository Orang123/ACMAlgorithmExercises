/*
����:h*w�ĺ����ͼ,'.'����ˮ,'@'������,'#'����½��,'S'���������ĳ�ʼλ��.
������ֻ��ˮƽ��ֱ��4��������ʹ,��ʹ������'.'ˮ����Ҫ����1����,����ʹ��
'@'��,��������ʱ���ӳ���Ҫd���Ӳ���ͨ��.����ʱ��Ϊd+1.����Ҫ���뺣��,
��ʹ����ͼ֮��Ĺ���,������Ҫ����ʱ��.
3<=h,w<=500.0<=d<=50.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4198
˼·:������ʹ��'.'��'@'����ʱ�䲻ͬ,ʹ����ͨ�Ķ���
�ȳ��ӵĻ���ʱ�䲻һ�������ٵ����Գ�����Ҫ���յ�ǰ
����ʱ�����ٵ�״̬�ȳ���,���ʹ�����ȶ���
priority_queue<State> Q;����״̬����ʱ�����ٵ��ȳ���.
*/
//ac 234ms bfs �ڵ�ͼ�����,����tp.t,��Ҫ��ʼ����ͼ�ⶼ��'.'�ɵ����.
//ʱ�临�Ӷ�O(h*w)=500^2=250000
#include<cstdio>
#include<queue>
#include<cstring>
#define N 510
using namespace std;

int h,w,d,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
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
        if(tp.x<1 || tp.x>h || tp.y<1 || tp.y>w)
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(mp[nx][ny] == '.'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+1));
            }
            else if(mp[nx][ny] == '@'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+1+d));
            }
        }
    }
    return tp.t;
}

int main(){
    int T,sx,sy;
    scanf("%d",&T);
    while(T--){
        memset(mp,'.',sizeof(mp));
        scanf("%d%d%d",&h,&w,&d);
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S')
                    sx=i,sy=j;
            }
        }
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}

/*
//ac 234ms bfs �ڵ�ͼ�߽��������tp.t+1
#include<cstdio>
#include<queue>
#include<cstring>
#define N 510
using namespace std;

int h,w,d,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
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
        if(tp.x==1 || tp.x==h || tp.y==1 || tp.y==w)
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(mp[nx][ny] == '.'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+1));
            }
            else if(mp[nx][ny] == '@'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+1+d));
            }
        }
    }
    return tp.t+1;
}

int main(){
    int T,sx,sy;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&h,&w,&d);
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S')
                    sx=i,sy=j;
            }
        }
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
*/

/*
dfs O(4^(500*500))��TLE
*/
