#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define N 100100
#define M 1000100
using namespace std;
typedef long long ll;
//prim ac 1.02s
/*
题意:n个点,m条边有权值,每个点有个高度,一个人初始在1点,
若想从u到达v,则u的高度必须不小于v的高度,现在问这个人
在1点最多能到达的点数,以及所经过的所有点所花费的最小权值和,
注意这个人可以免费回退到经过的点,即不需要花费.
链接:https://www.luogu.com.cn/problem/P2573
思路:就是求解有向图中的最小生成树.我们采用prim算法,但是prim算法的正确性
需要建立在无向图中,对于有向图它贪心的正确性无法保证,但是题目给出了u->v,
h[u]>=h[v],我们需要修改prim算法每次从未加入点选择距离已加入点距离最近的点
放入已加入点集合中,这一条件,因为现在是有向图,新加入的点可能是高度较低的点,
对于一些还未加入的点如果是高度较高的点,在统计距离已加入点距离最近点的时候,高度较大的点无法
考虑到(即使边权较小),导致贪心的正确性无法保证,如果一直按照距离最近加入点,最终权值和可能并不是最小的.所以
我们首先按照未加入的点如果高度不同,按照高度递减的顺序出队,这样就能保证每条有向边的权值在终点相同
时都能同时考虑,因为我们是按照高度递减出队,后面出队的是高度较低的,那么也不存在后续的点会和前面已加入集合
的点有连边,正确性就得意保证.对于高度相同,则必然是双向边,就按常规的距离递增出队.
*/

int n,m,cnt,head[N],vis[N],h[N],num;
ll dis[N],sum;

struct Edge{
    int to,next;
    ll w;
}edge[M<<1];

struct state{
    int v;
    ll dis;
    state(int v=0,ll dis=0):v(v),dis(dis){}
    bool operator < (const state &x)const{
        //高度不同时,按照高度递减出队,这样在出队时对同一终点才能考虑更多有向边
        if(h[v]!=h[x.v]) return h[v]<h[x.v];
        return dis>x.dis;//高度相同则都是双向边,就按常规的距离递增出队
    }
};


void addEdge(int from,int to,ll w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void prim(int s){
    init(s);
    priority_queue<state>Q;
    Q.push(state(s,0));
    int u,v;
    state tmp;
    while(!Q.empty()){
        u=Q.top().v;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        num++;
        sum+=dis[u];
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(state(v,dis[v]));
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        if(h[u] >= h[v])
            addEdge(u,v,w);
        if(h[u]<=h[v])
            addEdge(v,u,w);
    }
    prim(1);
    printf("%d %lld",num,sum);
    return 0;
}

/*

//kruskal ac 1.20s
//先用bfs统计最多能访问的点,所有能访问的边存入新的边集
//对新边集如果高度不同按照高度递减排序,否则按权值升序排序,再对新的边集kruskal求解mst即可
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 1000100
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],fa[N],h[N],vis[N],num;
ll sum;

struct Edge{
    int u,v;
    ll w;
    Edge(int u=0,int v=0,ll w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        //高度不同时,先按高度排,才能保证kruskal合并时,边的有向性得到保证,因为直接按边权排,会出现高度低的点到达高度高的点的边
        //而高度较低的点永远也无法连向高度较高的点,这样也保证了贪心的正确性.
        if(h[v]!=h[x.v]) return h[v]>h[x.v];
        else return w<x.w;//高度相同时,对于同一点而言选择边权较小的连接
    }
}edge[M];

struct Node{
    int to,next;
    ll w;
}node[M<<1];

void addEdge(int from,int to,ll w){
    node[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,cnt=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == num-1) break;
        }
    }
}

void bfs(int s){
    queue<int> Q;
    Q.push(s);
    vis[s]=1;
    num++;
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=node[i].next){
            v=node[i].to;
            edge[++m]=Edge(u,v,node[i].w);
            if(!vis[v]){
                vis[v]=1;
                num++;
                Q.push(v);
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        if(h[u]>=h[v]) addEdge(u,v,w);
        if(h[u]<=h[v]) addEdge(v,u,w);
    }
    m=0;
    bfs(1);
    kruskal();
    printf("%d %lld",num,sum);
    return 0;
}

*/
