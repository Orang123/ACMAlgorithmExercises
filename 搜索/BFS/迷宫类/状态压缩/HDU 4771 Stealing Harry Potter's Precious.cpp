/*
题意:一个n*m的房间矩阵,哈利叔叔从'@'出发,只能走上下左右4个方向,
'.'可以走,‘#’是墙,有k个宝贝放置在格子上,并且给出放置k个宝贝的
格子坐标,求出哈利叔叔最少要走多少步可以把k个宝贝取完拿完,如果无
法拿完k个宝贝输出-1.
0<n,m<=100.0<k<=4.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4771
思路:要求拿到所有宝贝的最少步数,很明显bfs层序遍历队列先进先出,每一个
状态的扩展,每个方案平行增加的步长都是1,每个状态所走的路径每步都是按
最优层序遍历向四周去走的,因此最先出队达到取完k个宝贝时,所用的步数就是最少的,
bfs是贪心按照每步都走最短的路径进行状态转移的,
只是这里对于取完一个格子上的宝贝,可能需要往回走到之前走过的格子,只是
再次走到之前走过的格子时身上持有宝贝数量不同,因此是不同的状态,所以对于
每个格子(x,y)的状态应该是当前格子上所持有宝贝的集合组合情况,这样才能保
证状态标记的有效性 使得能够重复往回走到之前走过的格子.对于取到宝贝集合
组合情况,可以用二进制位来表示,列如k个宝贝可以用k个0/1二进制位表示,0代表
当前位的宝贝还没取到,1代表当前位的宝贝取到了,那么所有宝贝持有的可能情况
的2进制位可以用0~(1<<k)-1的10进制数值表示,所以vis数组需要开成 vis[N][N][1<<4].
最小的0是所有位都是0,代表一个宝贝还没取,(1<<k)-1代表所有位都是1,k个宝贝都取到了.

注意:
1.此题数据k个宝贝都是放置在不同的格子上的,如果多个宝贝可以放置在同一格子上,
那么在状态压缩时要将当前格子上的所有宝贝都压缩进去.
2.不能用dfs搜索+状态压缩,因为深度搜索不能保证先搜索到的vis[x][y][sta]的步数
是最小的,如果直接标记会导致后续较少步数的状态取到的宝贝组合情况vis[x][y][sta]
已经被之前较多步数 提前标记,这样较小步数的状态就不能得到继续扩展,不能继续走下去,
从而最后的最小步数就是错误的.
*/
//ac 0ms bfs+状态压缩 在for循环内部入队之前判断状态是否已标记.
//时间复杂度和空间复杂度都是O(n*m*2^k) 每个节点最多有16个状态0~2^4-1,所有可以扩展的状态最多有n*m*(2^k) 100*100*16=160000=1.6*10^5
//实际复杂度肯定要比O(n*m*2^k)要小,因为只要状态达到2^k-1就会结束.
//k个宝贝都放置在不同的格子上 judge里找到哪个宝贝直接返回
//注意对于(nx,ny)上有宝贝的状态 实际状态判断vis可以判断 之前的状态未取到该(nx,ny)宝贝的状态即:!vis[nx][ny][tp.sta],
//但状态标记仍旧需要标记取到该点宝贝的状态即:vis[nx][ny][tp.sta|1<<val]=1,但这种做法 对于vis[nx][ny][tp.sta]是没有标记的,也就是如果还有其它较长路径 和之前状态一样会重复入队.
//也可以判断vis[nx][ny][tp.sta|1<<val]到达该点取到该点宝贝的状态
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
using namespace std;

int n,m,k,vis[N][N][1<<4],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct Goods{
    int x,y;
}gds[4];
struct State{
    int x,y,step,sta;
    State(int x=0,int y=0,int step=0,int sta=0):x(x),y(y),step(step),sta(sta){}
};

//查找当前格子(x,y)上放置的是哪个宝贝,第i个宝贝对应的二进制位是1<<(i-1)
int judge(int x,int y){
    for(int i=1;i<=k;i++){
        if(x == gds[i].x && y == gds[i].y)
            return i-1;//找到就返回
    }
    return -1;//当前格子没有放置宝贝
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,0,0));
    vis[sx][sy][0]=1;
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.sta == (1<<k)-1)
            return tp.step;
        Q.pop();
        for(int i=0;i<4;i++){
            int nx=tp.x+dir[i][0];
            int ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]!='#'){
                int val,sta;
                val=judge(nx,ny);
                //注意不能用tp.sta + 1<<val 因为加法会导致同一格子的宝贝重复取,
                //而按位或如果已经取过当前格子宝贝,那么按位或|后转态还是tp.sta并未得到新状态 不会重复入队
                if(val != -1)
                    sta=tp.sta | 1<<val;
                else//当前格子没有放置宝贝
                    sta=tp.sta;
                if(!vis[nx][ny][sta]){
                    vis[nx][ny][sta]=1;//标记当前状态
                    Q.push(State(nx,ny,tp.step+1,sta));
                }
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){//记录出发点 //此题的数据出发点 是不包含宝贝的,不然初始状态的sta 也应该判断一下
                    sx=i;
                    sy=j;
                }
            }
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d",&gds[i].x,&gds[i].y);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}

/*
//ac 15ms bfs+状态压缩 在for循环内部入队之前判断状态是否已标记
//加强版 一个房间可能放多个宝物 在状态压缩时要将当前格子上的所有宝贝都压缩进去.
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
using namespace std;

int n,m,k,vis[N][N][1<<4],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct Goods{
    int x,y;
}gds[4];
struct State{
    int x,y,step,sta;
    State(int x=0,int y=0,int step=0,int sta=0):x(x),y(y),step(step),sta(sta){}
};

int judge(int x,int y){
    int val=0;
    for(int i=1;i<=k;i++){
        if(x == gds[i].x && y == gds[i].y)
            val|=1<<(i-1);//要将当前格子上的所有宝贝对应的二进制位1都取到
    }
    return val;
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,0,0));
    vis[sx][sy][0]=1;
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.sta == (1<<k)-1)
            return tp.step;
        Q.pop();
        for(int i=0;i<4;i++){
            int nx=tp.x+dir[i][0];
            int ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]!='#'){
                int sta;
                sta=tp.sta | judge(nx,ny);
                if(!vis[nx][ny][sta]){
                    vis[nx][ny][sta]=1;
                    Q.push(State(nx,ny,tp.step+1,sta));
                }
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d",&gds[i].x,&gds[i].y);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
*/

/*
//ac 0ms bfs+状态压缩 在for循环外部出队之后判断状态是否已标记.
//k个宝贝都放置在不同的格子上 judge里找到哪个宝贝直接返回
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
using namespace std;

int n,m,k,vis[N][N][1<<4],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct Goods{
    int x,y;
}gds[4];
struct State{
    int x,y,step,sta;
    State(int x=0,int y=0,int step=0,int sta=0):x(x),y(y),step(step),sta(sta){}
};

int judge(int x,int y){
    for(int i=1;i<=k;i++){
        if(x == gds[i].x && y == gds[i].y)
            return i-1;
    }
    return -1;
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,0,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        if(tp.sta == (1<<k)-1)
            return tp.step;
        if(vis[tp.x][tp.y][tp.sta])//注意需放置在pop之后,否则当前tp会一直不出队,死循环
            continue;
        vis[tp.x][tp.y][tp.sta]=1;
        for(int i=0;i<4;i++){
            int nx=tp.x+dir[i][0];
            int ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]!='#'){
                int val,sta;
                val=judge(nx,ny);
                if(val != -1)
                    sta=tp.sta | 1<<val;
                else
                    sta=tp.sta;
                Q.push(State(nx,ny,tp.step+1,sta));
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d",&gds[i].x,&gds[i].y);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
*/

/*
//TLE dfs+二进制状态压缩 枚举出所有走到目的点的方案的时间求最小值
//复杂度O(4^(n*m*2^k))因为要把所有的取到k个宝贝的步数都枚举出来 比较求解最小步数,要遍历所有情况
//dp[x][y][sta]代表到达(x,y)时当前所携带的宝贝状态为sta时在之前的遍历中最少需要的步数 用来剪枝,如果当前步数不能比之前步数更小 则返回
//dfs搜索+dp记录最小步数剪枝的原因:因为深度搜索不能保证先搜索到的dp[x][y][sta]的步数
//是最小的,如果直接标记为1判重会导致后续较少步数的状态取到的宝贝组合情况dp[x][y][sta]
//已经被之前较多步数 提前标记,这样较小步数的状态就不能得到继续扩展,不能继续走下去,
//从而最后的最小步数就是错误的.因此需要枚举出所有走到目的点的方案的时间求最小值

//因为此题并没有明确的单目的地,所以无法使用一个目的地的迭代加深搜索的曼哈顿距离剪枝

//直接dp[x][y][sta]=1判重会错 数据 来自HDU Discuss模块
//4 4
//#@##
//..#.
//#.##
//....
//4
//2 1
//2 2
//4 3
//4 4
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

//dp[x][y][sta]代表到达(x,y)时当前所携带的宝贝状态为sta时在之前的遍历中最少需要的步数 用来剪枝,如果当前步数不能比之前步数更小 则返回
int n,m,k,dp[N][N][1<<4],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ans;
//val[i]代表第i个宝贝选取所代表的二进制位1对应的十进制数值
//mp[x][y]=val 代表当前格子(x,y)上放置的背包组合情况,一个格子可能放置多个宝贝 所以mp[x][y]是累加
int val[5]={0,1,2,4,8},mp[N][N];

void dfs(int x,int y,int step,int sta){
    //如果当前到达(x,y)点的取到的宝贝状态需要的步数不能比之前遍历的步数更小 则返回
    //因为当前已经不能更优,后续的遍历肯定也不会比之前遍历更优 无意义的搜索
    if(step>=dp[x][y][sta])
        return;
    dp[x][y][sta]=step;
    if(sta == (1<<k)-1){
        ans=min(ans,step);
        return;
    }
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]>=0)
            //注意不能用tp.sta + 1<<val 因为加法会导致同一格子的宝贝重复取,
            //而按位或如果已经取过当前格子宝贝,那么按位或|后转态还是tp.sta并未得到新状态 不会重复入队
            dfs(nx,ny,step+1,sta|mp[nx][ny]);
    }
}

int main(){
    int sx,sy,x,y;
    char c;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&c);
                if(c != '#'){
                    mp[i][j]=0;
                    if(c == '@'){
                        sx=i;
                        sy=j;
                    }
                }
                else
                    mp[i][j]=-1;
            }
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++){
            scanf("%d%d",&x,&y);
            //宝贝不能放置在'#'墙上,否则也会使得mp[x][y]原先的-1累加变成正数 导致之后的搜索状态扩展出错.
            if(mp[x][y]>=0)
                //mp[x][y]=val 代表当前格子(x,y)上放置的背包组合情况,一个格子可能放置多个宝贝 所以mp[x][y]是累加
                mp[x][y]+=val[i];
        }
        dfs(sx,sy,0,mp[sx][sy]);//有可能初始位置'@'本身就放置有宝贝,不过HDU的数据 比较弱 初始位置并未放置宝贝
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("-1\n");
    }
    return 0;
}
*/

/*
//ac 31ms bfs求出出发点'@'和放置宝贝的格子任意两点间最短距离的邻接矩阵p[i][j]+dfs枚举全排列 从出发点出发取k个宝贝的顺序序列(全排列)
//k<=4,全排列复杂度4!
//因此，可以先将起点和k个点构造一个图，图之间的权重为两点之间的最短路径距离，这个距离可以使用bfs求得。
//在构造出这个图之后，可以使用dfs进行一个遍历，求从起点出发，经过所有k个点的最小路径的长度。
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

int n,m,sx,sy,k,res;
char graph[105][105];
bool vis[105][105];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

struct Node{
    int x,y;
}node[10];

struct node1{
    int x,y,step;
};
int p[10][10];

int bfs(int from,int to){
    memset(vis,0,sizeof(vis));
    queue<node1> q;
    node1 cur,next;
    cur.x = node[from].x;
    cur.y = node[from].y;
    cur.step = 0;
    q.push(cur);
    vis[cur.x][cur.y] = 1;
    while(!q.empty()){
        cur = q.front();
        q.pop();
        if(cur.x==node[to].x && cur.y==node[to].y){
            return cur.step;
        }
        for(int i=0;i<4;i++){
            int xx = cur.x+dx[i];
            int yy = cur.y+dy[i];
            if(xx>=1 && xx<=n && yy>=1 && yy<=m && graph[xx][yy]!='#' && !vis[xx][yy]){
                vis[xx][yy] = 1;
                next.x = xx;
                next.y = yy;
                next.step = cur.step+1;
                q.push(next);
            }
        }
    }
    return -1;
}

//枚举全排列 k<=4 O(k!)=O(4!) 因此复杂度可接受
void dfs(int f[],int pre,int cost,int cnt){
    if(cnt==k){
        if(cost<res){
            res = cost;
        }
        return ;
    }
    for(int i=1;i<=k;i++){
        if(f[i]==0){
            f[i] = 1;
            //枚举第cnt个次序要取的宝贝是第i个宝贝
            dfs(f,i,cost+p[pre][i],cnt+1);
            f[i] = 0;
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&m)){
        if(n==0 && m==0) break;
        memset(vis,false,sizeof(vis));
        memset(graph,'#',sizeof(graph));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&graph[i][j]);
                if(graph[i][j]=='@'){
                    sx = i;
                    sy = j;  //记录起点
                }
            }
        }
        node[0].x = sx;
        node[0].y = sy;
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d",&node[i].x,&node[i].y);
        memset(p,-1,sizeof(p));
        bool flag = 0;
        for(int i=0;i<=k;i++){   //枚举任意必须要经过的两点间的最短路径，用bfs求出来
            p[i][i] = 0;
            for(int j=0;j<=k;j++){
                if(p[i][j]==-1 && flag==0){
                    p[i][j] = p[j][i] = bfs(i,j);
                    if(p[i][j]==-1){
                        flag = 1;
                        break;
                    }
                }
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        int f[10];
        memset(f,0,sizeof(f));
        res = INT_MAX;
        dfs(f,0,0,0);
        printf("%d\n",res);
    }
    return 0;
}
*/
