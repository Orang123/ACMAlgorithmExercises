#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;
//思维建边
/*
题意:n个点,m条权值为w的双向边,现在要从1点到达n点,
有k次机会通过一条花费为其本身一半的边,求最小花费.
链接:https://www.luogu.com.cn/problem/P4822
思路:经典分层图最短路.
*/

int n,m,k,cnt,head[N*51],vis[N*51],dis[N*51];

struct Node{
    int to,next,w;
}edge[(M*2*51)<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    priority_queue<pair<int,int> >Q;
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
    int u,v,w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        for(int i=0;i<=k;i++){
            addEdge(u+n*i,v+n*i,w);
            addEdge(v+n*i,u+n*i,w);
            if(i){
                addEdge(u+(i-1)*n,v+i*n,w>>1);
                addEdge(v+(i-1)*n,u+i*n,w>>1);
            }
        }
    }
    Dijkstra(1);
    for(int i=1;i<=k;i++)
        ans=min(ans,dis[n+n*i]);
    printf("%d",ans);
    return 0;
}

/*
//状态转移
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,cnt,head[N],vis[N][51],dis[N][51];

struct state{
    int v,dis,cnt;
    state(int v=0,int dis=0,int cnt=0):v(v),dis(dis),cnt(cnt){}
    bool operator <(const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
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
            if(cnt<k && dis[v][cnt+1]>dis[u][cnt]+edge[i].w/2){
                dis[v][cnt+1]=dis[u][cnt]+edge[i].w/2;
                Q.push(state(v,dis[v][cnt+1],cnt+1));
            }
        }
    }
}

int main(){
    int u,v,w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    Dijkstra(1);
    for(int i=1;i<=k;i++)
        ans=min(ans,dis[n][i]);
    printf("%d",ans);
    return 0;
}
*/
