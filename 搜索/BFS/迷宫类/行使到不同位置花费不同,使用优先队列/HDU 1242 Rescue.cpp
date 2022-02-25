/*
题意:一个公主被抓,公主有个朋友,在图上'a'代表公主'r'代表公主的朋友,
'#'代表墙,'.'代表路,'x'代表守卫,打败守卫花费2秒,其它1秒,现在问你那
个朋友能最快解救公主需要多少秒,如果不能解救输出"Poor ANGEL has to stay in the prison all his life."
注意:实际题目公主只有一个朋友,如果有多个朋友,需要考虑将多个朋友同时入队,
计算最少到达每个位置的最少时间,每个位置同样只会到达一次.
n,m<=200.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1242
思路:bfs,走路'.'需要1s,打败首位2s,因此用优先队列.
*/
//ac 93ms bfs
#include<cstdio>
#include<queue>
#include<cstring>
#define N 210
using namespace std;

int n,m,d,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
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
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx<1 || nx>n || ny<1 || ny>m || mp[nx][ny] == '#')
                continue;
            if(mp[nx][ny] == '.'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+1));
            }
            else if(mp[nx][ny] == 'x'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+2));
            }
            else if(mp[nx][ny] == 'a')
                return tp.t+1;
        }
    }
    return -1;
}

int main(){
    int sx,sy,ans;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'r')
                    sx=i,sy=j;
            }
        }
        ans=bfs(sx,sy);
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("Poor ANGEL has to stay in the prison all his life.\n");
    }
    return 0;
}
