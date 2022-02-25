//贪心kruskal 31ms ac
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
#define M 20010
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:给定一个包含n个节点和m条边的无向图,每条边有一个权值.
要求寻找从s到t的一条路径,使得路径上权值最大的一条边权值最小.
输出这个权值.单个样例只需输出一次结果.
链接:https://www.luogu.com.cn/problem/P1396
思路:因为单个样例只有一个询问,只需输出一次结果,所以可以不采用
prim+dp(每次询问o(1)输出)或lca倍增(每次询问log(n)输出)之类更高效的做法.
3种思路.
1.贪心kruskal最小树 当st的集合和ed集合连通时,当前加入的边权就为最大的边权的最小值.
2.Dijkstra修改松弛条件max(dis[u],edge[i].w)<dis[v]
3.二分边权最大值,bfs验证是否可从st到达ed.
*/

int n,m,fa[N];

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(int st,int ed){
    init();
    int x,y;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y)
            fa[x]=y;
        if(find(st) == find(ed)){
            printf("%d",edge[i].w);
            break;
        }
    }
}

int main(){
    int st,ed;
    scanf("%d%d%d%d",&n,&m,&st,&ed);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    kruskal(st,ed);
    return 0;
}

/*
//Dijkstra 41ms ac
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10010
#define M 20010
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],st,ed,vis[N],dis[N];

struct Edge{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    dis[s]=0;
}

int Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(dis[s],s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        if(u == ed) break;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && max(dis[u],edge[i].w)<dis[v]){
                dis[v]=max(dis[u],edge[i].w);
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return dis[ed];
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof head);
    scanf("%d%d%d%d",&n,&m,&st,&ed);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    printf("%d",Dijkstra(st));
    return 0;
}
*/

/*
//最大值最小化 二分bfs验证 46ms ac
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10010
#define M 20010
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],st,ed,vis[N];

struct Edge{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof vis);
}

int bfs(int s,int w){
    init(s);
    queue<int> Q;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        if(u == ed) break;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<w){
                vis[v]=1;
                Q.push(v);
            }
        }
    }
    return vis[ed];
}

int main(){
    int u,v,w,l=0,r=0;
    memset(head,-1,sizeof head);
    scanf("%d%d%d%d",&n,&m,&st,&ed);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        r=max(r,w);
    }
    while(l<r){//O(log(maxw)n) w<=10^4 n<=10^4 log(maxw)<=14
        int mid=(l+r+1)/2;
        if(bfs(st,mid)) r=mid-1;
        else l=mid;
    }
    printf("%d",l);
    return 0;
}
*/

/*
//最大值最小化 二分dfs验证 35ms ac
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10010
#define M 20010
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],st,ed,vis[N];

struct Edge{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof vis);
}

int dfs(int u,int w){
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v] || edge[i].w>=w) continue;
        if(v == ed) return 1;
        if(dfs(v,w)) return 1;
    }
    return 0;
}

int main(){
    int u,v,w,l=0,r=0;
    memset(head,-1,sizeof head);
    scanf("%d%d%d%d",&n,&m,&st,&ed);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        r=max(r,w);
    }
    while(l<r){
        memset(vis,0,sizeof(vis));
        int mid=(l+r+1)/2;
        if(dfs(st,mid)) r=mid-1;
        else l=mid;
    }
    printf("%d",l);
    return 0;
}
*/
