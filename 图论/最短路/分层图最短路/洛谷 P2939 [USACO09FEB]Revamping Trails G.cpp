#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//思维建边
/*
题意:约翰一共有N个牧场.由M条布满尘埃的小径连接。小径可以双向通行。
每天早上约翰从牧场1出发到牧场N去给奶牛检查身体。
通过每条小径都需要消耗一定的时间。约翰打算升级其中K条小径，使之成为高速公路。
在高速公路上的通行几乎是瞬间完成的，所以高速公路的通行时间为0。
请帮助约翰决定对哪些小径进行升级，使他每天从1号牧场到第N号牧场所花的时间最短。
链接:https://www.luogu.com.cn/problem/P2939
思路:经典分层图最短路
*/

int n,m,k,cnt,head[N*21],vis[N*21];
ll dis[N*21];

struct Node{
    int to,next;
    ll w;
}edge[(M*2*21)<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int u,v;
    ll w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        for(int i=0;i<=k;i++){
            addEdge(u+n*i,v+n*i,w);
            addEdge(v+n*i,u+n*i,w);
            if(i){
                addEdge(u+(i-1)*n,v+i*n,0);
                addEdge(v+(i-1)*n,u+i*n,0);
            }
        }
    }
    Dijkstra(1);
    for(int i=1;i<=k;i++)
        ans=min(ans,dis[n+n*i]);
    printf("%lld",ans);
    return 0;
}

/*
//状态枚举 dis二维数组做法
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,k,cnt,head[N],vis[N][21];
ll dis[N][21];

struct state{
    int v,cnt;
    ll dis;
    state(int v=0,ll dis=0,int cnt=0):v(v),dis(dis),cnt(cnt){}
    bool operator <(const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<=k;i++)
        dis[s][i]=0;
}

void Dijkstra(int s){
    priority_queue<state>Q;
    init(s);
    Q.push(state(s,0,0));
    state tmp;
    int u,v,cnt;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,cnt=tmp.cnt;
        Q.pop();
        if(vis[u][cnt]) continue;
        vis[u][cnt]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v][cnt]>dis[u][cnt]+edge[i].w){
                dis[v][cnt]=dis[u][cnt]+edge[i].w;
                Q.push(state(v,dis[v][cnt],cnt));
            }
            if(cnt<k && dis[v][cnt+1]>dis[u][cnt]){
                dis[v][cnt+1]=dis[u][cnt];
                Q.push(state(v,dis[v][cnt+1],cnt+1));
            }
        }
    }
}

int main(){
    int u,v;
    ll w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    Dijkstra(1);
    for(int i=1;i<=k;i++)
        ans=min(ans,dis[n][i]);
    printf("%lld",ans);
    return 0;
}
*/
