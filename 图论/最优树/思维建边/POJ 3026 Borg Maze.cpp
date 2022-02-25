#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 55
#define M 11000//迷宫中最多100个外星人 那么完全图有4950条边,但是这里在建边时,去重边太麻烦,即a->b b->a建了2条,没太大影响 因此4950*2<11000 避免数组越界
using namespace std;
//63ms kruskal
/*
题意:外星人分布在迷宫的'A'处,博格人从'S'处出发,
向四周同化外星人,一个外星人被同化后,就能去同化其它外星人,
求所有外星人被同化后走过的最小距离.
题意剖析:
n*m的迷宫,只能走' ','#'不能走,求从字母'S'出发
将所有的'A'连接起来使得'S'与所有'A'连通要走的最少距离.
链接:http://poj.org/problem?id=3026
思路:这个问题和从s点出发没有关系,就是求解'S'与所有的'A'构成
的mst,那就是如何建边的问题,因为迷宫中有'#'不能直接通过坐标差
来建边权,所以要从所有的'A'与'S'进行bfs与其它'A'与'S'建边,构造
一个'S'与'A'的完全图.之后再跑kruskal即可求得最小距离.
*/
//fa[N<<1] 迷宫最多有100个外星人,构建的图最多100个点
int n,m,id,fa[N<<1],mp2[N][N],mp3[N][N],cnt,vis[N][N];
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char mp1[N][N];

struct Node{
    int x,y,dis;
    Node(int x=0,int y=0,int dis=0):x(x),y(y),dis(dis){}
};

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void bfs(int x,int y){
    queue<Node> Q;
    vis[x][y]=1;
    Q.push(Node(x,y,0));
    Node node;
    int x0,y0;
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        //到达 'A'或'S' 就建边
        if(node.dis && mp2[node.x][node.y])//这里每条边会建两边,因此数组要开2倍
            edge[++cnt]=Edge(mp2[x][y],mp2[node.x][node.y],node.dis);
        for(int i=0;i<4;i++){
            x0=node.x+dir[i][0];
            y0=node.y+dir[i][1];
            if(x0<1 || x0>n || y0<1 || y0>m) continue;
            if(vis[x0][y0] || mp1[x0][y0] == '#') continue;
            vis[x0][y0]=1;//这里标记一定要设置在入队这里,如果设置在pop后面会导致相同的坐标入队2次,无意义会增加复杂度
            Q.push(Node(x0,y0,node.dis+1));
        }
    }
}

void init(){
    //id 是'S' 'A'的总个数
    for(int i=1;i<=id;i++)
        fa[i]=i;
    sort(edge+1,edge+1+cnt);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,num=0,sum=0;
    for(int i=1;i<=cnt;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            num++;
            sum+=edge[i].w;
            if(num == id-1) break;
        }
    }
    return sum;
}

int main(){
    int T;
    char str[55];
    scanf("%d",&T);
    while(T--){
        id=cnt=0;
        memset(mp2,0,sizeof(mp2));
        scanf("%d%d",&m,&n);
        gets(str);//输入数据 莫名有多余的' '空格,正常情况getchar()读取到上一行的‘\n'即可
        for(int i=1;i<=n;i++){
            gets(mp1[i]+1);
            for(int j=1;j<=m;j++){
                if(mp1[i][j] == 'S' || mp1[i][j] == 'A')
                    mp2[i][j]=++id;//设置'S' 'A'点的编号
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp2[i][j]){//从每个'S' 'A'开始构建边
                    memset(vis,0,sizeof(vis));
                    bfs(i,j);
                }
            }
        }
        printf("%d\n",kruskal());
    }
    return 0;
}
/*
//附上一组数据
1
50 50
##################################################
#AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#S                                              A#
##################################################

*/
