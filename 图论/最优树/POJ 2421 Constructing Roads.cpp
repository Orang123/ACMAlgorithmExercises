#include<cstdio>
#include<algorithm>
#define N 110
#define M 5000//边数按完全图取上限
using namespace std;
//kruskal 32ms
/*
题意:n个村庄,会给出村庄间道路的邻接矩阵,数值为道路的长度,
会有一些道路已经被建好,现在要求使得村庄相互连通的道路总长最小.
链接:http://poj.org/problem?id=2421
思路:最小树裸题,对于已经建好的道路,权值为0.
*/
int n,mp[N][N],fa[N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M<<1];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,sum=0,cnt=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    int a,b,q;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mp[i][j]);
            if(j>i)//只构建一条无向边
                edge[++m]=Edge(i,j,mp[i][j]);
        }
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&a,&b);
        edge[++m]=Edge(a,b,0);//已经建好的道路,权值为0
    }
    printf("%d",kruskal());
    return 0;
}

/*
//prim 47ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,q,mp[N][N],vis[N],dis[N];

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,sum=0,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        sum+=dis[u];
        num++;
        if(num == n) return sum;
        vis[u]=1;
        for(int v=1;v<=n;v++){
            if(!vis[v] && mp[u][v]<dis[v]){
                dis[v]=mp[u][v];
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return sum;
}

int main(){
    int a,b;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mp[i][j]);
        }
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&a,&b);
        mp[a][b]=mp[b][a]=0;
    }
    printf("%d",prim(1));
    return 0;
}
*/
