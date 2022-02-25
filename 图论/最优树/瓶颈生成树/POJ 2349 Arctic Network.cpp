#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 550
#define M 130000
using namespace std;
//kruskal 172ms 对于本题prim算法更适合
/*
题意:n个前哨站要两两之间可通过卫星或无线电进行通信,
分别放置卫星的2个前哨站通信可不考虑位置距离,用无线电通信产生
成本为两个前哨站间的距离D,整体收发器的功率和最大的D值
相关,D值越高,成本越大,现在要构造n个前哨站两两互通的通信网,
问最小成本是多少.
链接:http://poj.org/problem?id=2349
思路:最小瓶颈树,最大边权为所有生成树中最大边权的最小值,mst一定是最小瓶颈树,
而最小瓶颈树不一定是mst.
求解最小生成树中的最大边权,因为放置卫星的前哨站间通信,
可不考虑成本,所以贪心选择生成树中边权最大的边的端点放置卫星,这样成本最低.
eg:s个卫星放置在s个端点上,会有s-1条边边权为0,所以kruskal加边时,加到n-1-(s-1)
=n-s条边时,剩下的s-1条边也就是s个点可将s个卫星放置在这些端点上,边权就为0,那么
最大边权就是加的第n-s条边.
*/

int s,n,m,fa[N];

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

struct Point{
    int x,y;
}point[N];

double getDis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

double kruskal(){
    init();
    int x,y,cnt=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            cnt++;
            if(cnt == n-s)
                return edge[i].w;
        }
    }
}

int main(){
    int T;
    double w;
    scanf("%d",&T);
    while(T--){
        m=0;
        scanf("%d%d",&s,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                edge[++m]=Edge(i,j,w);
            }
        }
        printf("%.2f\n",kruskal());
    }
    return 0;
}
/*
//V<=500 E<=130000
//E>Vlog(V) 为稠密图 稠密图更适合prim
//prim 125ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#define N 550
#define M 130000
#define INF 1e18
using namespace std;

int s,n,cnt,head[N],vis[N];
double dis[N],a[N];

struct Edge{
    int to,next;
    double w;
}edge[M<<1];

struct Point{
    int x,y;
}point[N];

double getDis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void addEdge(int from,int to,double w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
}

void prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        num++;
        //将加入mst中的边放入a数组中排序,因为每次弹出边权的距离mst中集合的点的边权大小是无序的
        if(num!=1) a[num]=dis[u];
        if(num == n) return;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T;
    double w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&s,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                addEdge(i,j,w);
                addEdge(j,i,w);
            }
        }
        prim(1);
        sort(a+2,a+n+1,less<double>());
        printf("%.2f\n",a[n-s+1]);
    }
    return 0;
}
*/
