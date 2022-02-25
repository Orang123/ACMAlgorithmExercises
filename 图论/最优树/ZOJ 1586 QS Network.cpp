#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#define N 1100
#define M 500100
using namespace std;
//kruskal 70ms 此题为稠密图 prim会快些
/*
题意:n个点构成的网络,点与点之间需要适配器和电缆连接,
每条电缆两端的端点都需要贡献一个适配器,需要考虑电缆
和适配器的价钱,问网络连通的最低费用.
连接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365085
思路:构建边时再加上两端点的点权,kruskal
//在kruskal 加边时 edge[i].w+val[edge[i].u]+val[edge[i].v] 为何会wa?
*/

int n,m,fa[N],val[N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
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

int kruskal(){
    init();
    int x,y,cnt=0,sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;//edge[i].w+val[edge[i].u]+val[edge[i].v] 为何会wa?
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    int T,w;
    scanf("%d",&T);
    while(T--){
        m=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&w);
                if(j>i)
                    edge[++m]=Edge(i,j,w+val[i]+val[j]);
            }
        }
        printf("%d\n",kruskal());
    }
    return 0;
}

/*
//prim 50ms E>Vlog(V) 此题为稠密图 prim会快些
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 500100
#define INF 1e18
using namespace std;

int s,n,cnt,head[N],vis[N],dis[N],val[N];

struct Edge{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
}

int prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,num=0,sum=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        sum+=dis[u];
        num++;
        if(num == n) return sum;
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
    int T,w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&w);
                if(j>i){
                    addEdge(i,j,w+val[i]+val[j]);
                    addEdge(j,i,w+val[i]+val[j]);
                }
            }
        }
        printf("%d\n",prim(1));
    }
    return 0;
}
*/
