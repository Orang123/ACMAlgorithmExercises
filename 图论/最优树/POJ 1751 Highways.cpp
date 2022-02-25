#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 1000
#define M 510000//因为n个点构造完全图需要的点数为n*(n-1)/2=500000 再加上已经建造好的道路1000
#define INF 1e18
using namespace std;
//kruskal 594ms 此题稠密图 prim较快 157ms
/*
题意:n个城镇,现在要修建公路网,公路费用与公路长度
成正比,使得所有城镇互通,现在已经修建好了m条公路,
问还需要修建哪些城镇间的道路,才能使得n个城镇互通
的费用最小,输出每条公路的两端点编号.
链接:http://poj.org/problem?id=1751
思路:已修建好的城镇,边权为0,输出时不输出边权为0的边.
*/

int n,cnt,m,fa[N];

struct Point{
    int x,y;
}point[N];

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

double getDis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+cnt);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,num=0;
    for(int i=1;i<=cnt;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            if(edge[i].w) printf("%d %d\n",edge[i].u,edge[i].v);
            num++;
            if(num == n-1) break;
        }
    }
}

int main(){
    int u,v;
    double w;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&point[i].x,&point[i].y);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
            edge[++cnt]=Edge(i,j,w);
        }
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        edge[++cnt]=Edge(u,v,0);
    }
    kruskal();
    return 0;
}

/*
//prim 157ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#define N 1000
#define M 510000//因为n个点构造完全图需要的点数为n*(n-1)/2=500000 再加上已经建造好的道路1000
#define INF 1e18
using namespace std;

int n,m,vis[N];
double mp[N][N],dis[N];

struct state{
    int u,v;
    double w;
    state(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const state &x)const{
    //这里用dis[v]<dis[x.v]会出错,这样不同端点u,相同点v,边权会更新为一样,优先队列出队时,导致输出的边的端点出错,但总费用不会出错.
        return w>x.w;
    }
};

struct Point{
    int x,y;
}point[N];

double getDis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
}

void prim(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(s,s,0));
    int u,num=0;
    state tmp;
    double sum=0;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        num++;
        sum+=dis[u];
        if(dis[u]) printf("%d %d\n",tmp.u,tmp.v);
        if(num == n) return;
        for(int v=1;v<=n;v++){
            if(!vis[v] && mp[u][v]<dis[v]){
                dis[v]=mp[u][v];
                Q.push(state(u,v,dis[v]));
            }
        }
    }
}

int main(){
    int u,v;
    double w;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&point[i].x,&point[i].y);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
            mp[i][j]=mp[j][i]=w;
        }
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        mp[u][v]=mp[v][u]=0;
    }
    prim(1);
    return 0;
}
*/
