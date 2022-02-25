/*
题意:r*c的网格,'Y'是起点,'C'是终点,'*'代表收费站,每次路过花费cost,
'#'为不能通过,'P'是传送站可以免费到达图上其它点任意一个P,
为从起点走到终点最少花费.
0<r*c<=5000.cost<=10000.
'P'的数量不超过图中所有点数目的10%.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4308
思路:bfs,只是因为只有遇到'*'才会收费,遇到'P'可以免费传送到网格中
任意一个'P',因此先入队的状态花费不一定是较小的,有可能后入队遇到'P'
的花费更小,所以要用优先队列.
*/
//ac 31ms bfs
//复杂度O(r*c)=5000
#include<cstdio>
#include<queue>
#include<cstring>
#define N 5100
using namespace std;

int r,c,cost,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct State{
    int x,y,c;
    State(int x=0,int y=0,int c=0):x(x),y(y),c(c){}
    bool operator <(const State &a)const{
        return c>a.c;
    }
};
vector<pair<int,int>> V;

int bfs(int sx,int sy){
    priority_queue<State> Q;
    mp[sx][sy]='#';
    Q.push(State(sx,sy,0));
    int nx,ny;
    State tp;
    while(!Q.empty()){
        tp=Q.top();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx<1 || nx>r || ny<1 || ny>c)
                continue;
            if(mp[nx][ny] == '*'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.c+cost));
            }
            else if(mp[nx][ny] == 'P'){
                for(pair<int,int> & p : V){
                    if(mp[p.first][p.second] == 'P'){
                        mp[p.first][p.second]='#';
                        Q.push(State(p.first,p.second,tp.c));
                    }
                }
            }
            else if(mp[nx][ny] == 'C')
                return tp.c;
        }
    }
    return -1;
}

int main(){
    int sx,sy,ans;
    while(scanf("%d%d%d",&r,&c,&cost)!=EOF){
        V.clear();
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'Y'){
                    sx=i;
                    sy=j;
                }
                else if(mp[i][j] == 'P')
                    V.push_back(make_pair(i,j));
            }
        }
        ans=bfs(sx,sy);
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("Damn teoy!\n");
    }
    return 0;
}
