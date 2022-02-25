/*
题意:摘自网上
从迷宫的S处出发，每次可以往东、南、西、北4个方向之一前进。
如果前方有墙壁，游戏者可以把墙壁往前推一格。如果有两堵或者
多堵连续的墙，则不能推动。另外，游戏者也不能推动游戏区域边
界上的墙。用最少的步数走出迷宫（边界处没有墙的地方就是出口）。
迷宫总是有4行6列，多解时任意输出一个移动序列即可。
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1325
思路:这题实际只有4*6行,这个数据直接dfs都不会炸.
这个问题(x,y)位置的状态涉及到墙的状态,因此不能直接用vis[x][y]二维数组
判重,需要用三维vis[x][y][mp[x][y]]判重.
但是可以考虑用IDA*,对于(x,y)位置重复访问的问题,可以直接用迭代的
深度去剪枝,避免死循环,剪枝是基于曼哈顿距离的剪枝,判断当前位置
距离最近的出口最少走的步数,如果当前步数加上最少要走的步数大于
当前迭代的深度,就剪枝.
遍历对于当前(x,y)所走方向有i墙,即将走到位置(nx,ny)在该方向i无墙的情况,
要更新(x,y)位置在i方向无墙,(nx,ny)在i方向有墙,(nx+dir[i][0],ny+dir[i][1]),
位置相对应的i的反方向会有墙,即如果(nx,ny)有东墙,nx+dir[i][0],ny+dir[i][1])
自然就会有西墙,可以用按位异或实现墙的状态的更新.
*/
//ac 50ms IDA*-曼哈顿距离剪枝
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};//WNES 1248
int mp[N][N],rec[4]={2,3,0,1};
vector<pair<int,int> > endPoints;//出口点的集合
char path[N*N],str[5]="WNES";

int judge(int x,int y){
    if(x>=1 && x<=4 && y>=1 && y<=6)
        return 1;
    return 0;
}

int check(int x,int y){
    return x<1 || x>4 || y<1 || y>6;
}

int dis(int x,int y){
    int d=INF;
    for(pair<int,int> &tp : endPoints)
        d=min(d,abs(x-tp.first)+abs(y-tp.second));
    return d;
}

int dfs(int x,int y,int d,int dep){
    if(d == dep)
        return check(x,y);
    if(d+dis(x,y) > dep)
        return 0;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(mp[x][y] & 1<<i){//(x,y)在i方向有墙
            if((mp[nx][ny] & 1<<i))
                continue;
            if((i==0 && y==1) || (i==1 && x==1) || (i==2 && y==6) || (i==3 && x==4))
                continue;
            mp[x][y]^=1<<i;//当前(x,y)位置要取消i方向的墙
            mp[nx][ny]^=1<<i;//(nx,ny)所走到的方向要增加i方向的墙
            if(judge(nx+dir[i][0],ny+dir[i][1]))//(nx,ny)i方向紧邻的位置(nx+dir[i][0],ny+dir[i][1])在i的反方向rec[i]也会有墙
                mp[nx+dir[i][0]][ny+dir[i][1]]^=1<<rec[i];
            path[d]=str[i];
            if(dfs(nx,ny,d+1,dep))
                return 1;
            mp[x][y]^=1<<i;
            mp[nx][ny]^=1<<i;
            if(judge(nx+dir[i][0],ny+dir[i][1]))
                mp[nx+dir[i][0]][ny+dir[i][1]]^=1<<rec[i];
        }
        else{//在i方向无墙
            path[d]=str[i];
            if(dfs(nx,ny,d+1,dep))
                return 1;
        }
    }
    return 0;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&sy,&sx) && sx+sy){
        endPoints.clear();
        for(int i=1;i<=4;i++){
            for(int j=1;j<=6;j++){
                scanf("%d",&mp[i][j]);
                if(i == 1 && !(mp[i][j] & 2))
                    endPoints.push_back(make_pair(i,j));
                else if(i == 4 && !(mp[i][j] & 8))
                    endPoints.push_back(make_pair(i,j));
                else if(j == 1 && !(mp[i][j] & 1))
                    endPoints.push_back(make_pair(i,j));
                else if(j == 6 && !(mp[i][j] & 4))
                    endPoints.push_back(make_pair(i,j));
            }
        }
        for(int i=1;;i++){
            if(dfs(sx,sy,0,i)){
                for(int j=0;j<i;j++)
                    printf("%c",path[j]);
                printf("\n");
                break;
            }
        }
    }
    return 0;
}

/*
//ac 10ms bfs+vis三维状态标记
//vis[x][y][mp[x][y]]=1表示(x,y)位置墙的状态为mp[x][y]已经遍历过
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define N 10
#define M 16
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};//WNES 1248
int mp[N][N],rec[4]={2,3,0,1},vis[N][N][M];
vector<pair<int,int> > endPoints;
char str[5]="WNES";

struct State{
    int mp[N][N],x,y,d;
    char path[N*N];
    int vis[N][N][M];
};

int judge(int x,int y){
    if(x>=1 && x<=4 && y>=1 && y<=6)
        return 1;
    return 0;
}

int check(int x,int y){
    return x<1 || x>4 || y<1 || y>6;
}

void bfs(int sx,int sy){
    queue<State> Q;
    State tp,next;
    memset(tp.vis,0,sizeof(tp.vis));
    tp.vis[sx][sy][mp[sx][sy]]=1;
    tp.x=sx,tp.y=sy;
    memcpy(tp.mp,mp,sizeof(mp));
    tp.d=0;
    Q.push(tp);
    while(!Q.empty()){
        tp=Q.front();
        if(check(tp.x,tp.y)){
            for(int i=0;i<tp.d;i++)
                printf("%c",tp.path[i]);
            printf("\n");
            break;
        }
        Q.pop();
        for(int i=0;i<4;i++){
            next.x=tp.x+dir[i][0];
            next.y=tp.y+dir[i][1];
            if(tp.mp[tp.x][tp.y] & 1<<i){
                if(tp.mp[next.x][next.y] & 1<<i)
                    continue;
                if((i==0 && tp.y==1) || (i==1 && tp.x==1) || (i==2 && tp.y==6) || (i==3 && tp.x==4))
                    continue;
                    memcpy(next.path,tp.path,sizeof(tp.path));
                    memcpy(next.mp,tp.mp,sizeof(tp.mp));
                    next.mp[tp.x][tp.y]^=1<<i;
                    next.mp[next.x][next.y]^=1<<i;
                    if(judge(next.x+dir[i][0],next.y+dir[i][1]))
                        next.mp[next.x+dir[i][0]][next.y+dir[i][1]]^=1<<rec[i];
            }
            else{
                memcpy(next.path,tp.path,sizeof(tp.path));
                memcpy(next.mp,tp.mp,sizeof(tp.mp));
            }
            if(!tp.vis[next.x][next.y][next.mp[next.x][next.y]]){
                next.path[tp.d]=str[i];
                next.d=tp.d+1;
                memcpy(next.vis,tp.vis,sizeof(tp.vis));
                next.vis[next.x][next.y][next.mp[next.x][next.y]]=1;
                Q.push(next);
            }
        }
    }
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&sy,&sx) && sx+sy){
        endPoints.clear();
        for(int i=1;i<=4;i++){
            for(int j=1;j<=6;j++)
                scanf("%d",&mp[i][j]);
        }
        bfs(sx,sy);
    }
    return 0;
}
*/

/*
//ac 0ms dfs+曼哈顿距离剪枝
//vis[x][y][mp[x][y]]=1表示(x,y)位置墙的状态为mp[x][y]已经遍历过
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 10
#define M 16
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};//WNES 1248
int mp[N][N],vis[N][N][M],rec[4]={2,3,0,1},ans;
vector<pair<int,int> > endPoints;
char path[N*N],res[N*N],str[5]="WNES";

int judge(int x,int y){
    if(x>=1 && x<=4 && y>=1 && y<=6)
        return 1;
    return 0;
}

int check(int x,int y){
    return x<1 || x>4 || y<1 || y>6;
}

int dis(int x,int y){
    int d=INF;
    for(pair<int,int> &tp : endPoints)
        d=min(d,abs(x-tp.first)+abs(y-tp.second));
    return d;
}

void dfs(int x,int y,int d){
	if(check(x,y)){
		if(d<ans){
			ans=d;
			memcpy(res,path,sizeof(path));
		}
		return;
	}
    if(d+dis(x,y) > ans)//没这个剪枝 也是3000ms
        return;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(mp[x][y] & 1<<i){
            if((mp[nx][ny] & 1<<i))
                continue;
            if((i==0 && y==1) || (i==1 && x==1) || (i==2 && y==6) || (i==3 && x==4))
                continue;
            if(!vis[nx][ny][mp[nx][ny]^1<<i]){
            	mp[x][y]^=1<<i;
            	mp[nx][ny]^=1<<i;
            	if(judge(nx+dir[i][0],ny+dir[i][1]))
                	mp[nx+dir[i][0]][ny+dir[i][1]]^=1<<rec[i];
           	 	path[d]=str[i];
            	vis[nx][ny][mp[nx][ny]]=1;
            	dfs(nx,ny,d+1);
            	vis[nx][ny][mp[nx][ny]]=0;
            	mp[x][y]^=1<<i;
            	mp[nx][ny]^=1<<i;
            	if(judge(nx+dir[i][0],ny+dir[i][1]))
                	mp[nx+dir[i][0]][ny+dir[i][1]]^=1<<rec[i];
			}
        }
        else if(!vis[nx][ny][mp[nx][ny]]){
            vis[nx][ny][mp[nx][ny]]=1;
            path[d]=str[i];
            dfs(nx,ny,d+1);
            vis[nx][ny][mp[nx][ny]]=0;
        }
    }
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&sy,&sx) && sx+sy){
        endPoints.clear();
        ans=INF;
        for(int i=1;i<=4;i++){
            for(int j=1;j<=6;j++){
                scanf("%d",&mp[i][j]);
                if(i == 1 && !(mp[i][j] & 2))
                    endPoints.push_back(make_pair(i,j));
                else if(i == 4 && !(mp[i][j] & 8))
                    endPoints.push_back(make_pair(i,j));
                else if(j == 1 && !(mp[i][j] & 1))
                    endPoints.push_back(make_pair(i,j));
                else if(j == 6 && !(mp[i][j] & 4))
                    endPoints.push_back(make_pair(i,j));
            }
        }
        vis[sx][sy][mp[sx][sy]]=1;
        dfs(sx,sy,0);
        vis[sx][sy][mp[sx][sy]]=0;
        for(int j=0;j<ans;j++)
            printf("%c",res[j]);
        printf("\n");
    }
    return 0;
}
*/
