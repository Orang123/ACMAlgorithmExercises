/*
题意:h*w的海域地图,'.'代表水,'@'代表桥,'#'代表陆地,'S'代表海盗船的初始位置.
海盗船只能水平或垂直朝4个方向行使,行使到四周'.'水域需要花费1分钟,而行使到
'@'桥,由于桥有时间延迟需要d分钟才能通行.即总时间为d+1.海盗要脱离海域,
行使到地图之外的公海,最少需要多少时间.
3<=h,w<=500.0<=d<=50.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4198
思路:由于行使到'.'和'@'花费时间不同,使用普通的队列
先出队的花费时间不一定是最少的所以出队需要按照当前
花费时间最少的状态先出队,因此使用优先队列
priority_queue<State> Q;按照状态花费时间最少的先出队.
*/
//ac 234ms bfs 在地图外结束,返回tp.t,需要初始化地图外都是'.'可到达的.
//时间复杂度O(h*w)=500^2=250000
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
//ac 234ms bfs 在地图边界结束返回tp.t+1
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
dfs O(4^(500*500))会TLE
*/
