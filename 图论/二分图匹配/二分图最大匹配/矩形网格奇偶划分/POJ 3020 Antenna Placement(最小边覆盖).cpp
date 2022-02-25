#include<cstdio>
#include<cstring>
#define N 500
using namespace std;
//ac 0ms 二分图奇偶集合划分 mp记录点奇偶点编号
/*
二分图性质定理:
边覆盖:若图G的每个顶点都与L中至少一条边关联,则称L是G的边覆盖.
若边覆盖L的任何真子集都不是G的边覆盖,则称L是G的极小边覆盖.
G的含边数最少的边覆盖称为G的最小边覆盖,其所含边的数目称为G的边覆盖数.
通俗地讲 最小边覆盖:实质是个边集,这个集合里的边能覆盖所有的点,最小边覆盖是
满足这个要求的所有边集中边数最少的一个.
二分图中最小边覆盖=顶点数-最大匹配数.
*/

/*
题意:一个n*m的网格,由'*'和'o'组成,'*'代表城市,'o‘代表空地,
现在要在城市'*'和空地'o'间放置基站,一个基站最多同时覆盖4周相邻的
一个位置,即信号只能同时覆盖连续的一个1*2或2*1位置,现在问至少要在
'*'或'o'间放置多少个基站才能使得所有的'*'城市信号得以被覆盖.
注意:在一个点放置基站它的信号最多也只能覆盖2个位置,即只能在4周方向一个位置覆盖.
链接:http://poj.org/problem?id=3020
思路:区别于最大匹配,因为最大匹配数有可能个别点并没有纳入匹配中的点集,
现在这个问题求解的是至少几条边才能使得所有的'*'才能被覆盖,因此就是求解
所有的'*'构成的二分图中的最小边覆盖.
而二分图中最小边覆盖=顶点数-最大匹配数
*/
int head[N],cnt;
int n,m,mp[50][12],odd,even,vis[N],link[N],num,ans;
struct Edge{
    int to,next;
}edge[N*4];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=odd=even=num=cnt=0;
    memset(link,0,sizeof(link));
    memset(head,-1,sizeof(head));
}
int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == '*'){
                    if((i+j) & 1) mp[i][j]=++odd;
                    else mp[i][j]=++even;
                    num++;
                }
                else
                    mp[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!((i+j) & 1)) continue;
                if(j<n && mp[i][j+1])
                    addEdge(mp[i][j],mp[i][j+1]);
                if(i<n && mp[i+1][j])
                    addEdge(mp[i][j],mp[i+1][j]);
                if(j>1 && mp[i][j-1])
                    addEdge(mp[i][j],mp[i][j-1]);
                if(i>1 && mp[i-1][j])
                    addEdge(mp[i][j],mp[i-1][j]);
            }
        }
        for(int i=1;i<=odd;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",num-ans);//输出最小边覆盖
    }
    return 0;
}

/*
//ac 0ms 奇偶集合用两个node数组记录坐标,非mp记录网格
#include<cstdio>
#include<cstring>
#include<vector>
#define N 500
using namespace std;
int n,m,odd,even,vis[N],link[N],ans;
vector<int> G[N];
struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

int check(int i,int j){
    if(node1[i].x == node2[j].x && node1[i].y == node2[j].y+1) return 1;
    if(node1[i].x == node2[j].x && node1[i].y == node2[j].y-1) return 1;
    if(node1[i].x == node2[j].x+1 && node1[i].y == node2[j].y) return 1;
    if(node1[i].x == node2[j].x-1 && node1[i].y == node2[j].y) return 1;
    return 0;
}

void init(){
    ans=odd=even=0;
    memset(link,0,sizeof(link));
    for(int i=1;i<N;i++) G[i].clear();
}

int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == '*'){
                    if((i+j) & 1) node1[++odd]=Node(i,j);
                    else node2[++even]=Node(i,j);
                }
            }
        }
        for(int i=1;i<=odd;i++){
            for(int j=1;j<=even;j++){
                if(check(i,j))
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=odd;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",odd+even-ans);
    }
    return 0;
}
*/
