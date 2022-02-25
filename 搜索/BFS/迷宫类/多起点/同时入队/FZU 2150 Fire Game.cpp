/*
题意:n*m的草地,'#'代表草,'.'代表空地,2个小孩同时点燃2个草地(不花费时间),
每一块着火地都可以在下一秒烧向上下左右四块草地'#',空地'.'是不能扩张的.
问你最少花多少时间可以烧掉所有草地,如果烧不掉就输出-1.
数据保证至少有一个草地.
1<=n,m<=10.
链接:https://vjudge.net/problem/FZU-2150
思路:可以枚举所有草地的两个草地作为起点开始bfs,求出烧完所有草地的最短时间,
记录比较每次bfs的时间最小值作为答案,注意如果草地个数不超过2,则无需花费时间
让火向四中蔓延,直接刚开始点燃1或2个草地即可无需花费时间.
*/
//ac FZU外网不能进入,无法测评,应该是没问题的 bfs
//复杂度O(n*m*n*m*n*m)=10^6
#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#define N 15
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N],cnt;
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
};
vector<pair<int,int>> node;
queue<State> Q;

int bfs(){
    State tp;
    int nx,ny,siz=2;//初始已经点燃2个草地了
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny] =='#' && !vis[nx][ny]){
                vis[nx][ny]=1;
                siz++;
                if(siz == cnt)//所有草地已被点燃,输出最短时间tp.t+1
                    return tp.t+1;
                Q.push(State(nx,ny,tp.t+1));
            }
        }
    }
    return -1;
}

int main(){
    int T,cas=0,t,ans;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        cas++;
        node.clear();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '#'){
                    cnt++;//记录草地个数
                    node.push_back(make_pair(i,j));
                }
            }
        }
        if(cnt<=2){
            printf("Case %d: 0\n",cas);
            continue;
        }
        ans=INF;
        //枚举 初始点燃的2个草地组合 复杂度O(100*100)
        for(int i=0;i<node.size();i++){
            for(int j=i+1;j<node.size();j++){
                while(!Q.empty()) Q.pop();
                memset(vis,0,sizeof(vis));
                vis[node[i].first][node[i].second]=1;
                vis[node[j].first][node[j].second]=1;
                Q.push(State(node[i].first,node[i].second,0));
                Q.push(State(node[j].first,node[j].second,0));
                t=bfs();//O(100)
                if(t!=-1)
                    ans=min(ans,t);
            }
        }
        if(ans!=INF)
            printf("Case %d: %d\n",cas,ans);
        else
            printf("Case %d: -1\n",cas);
    }
    return 0;
}
