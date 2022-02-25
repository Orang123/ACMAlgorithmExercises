#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;

//Dijkstra 180ms
/*
题意:n个点,m条双向边,每条边长度和花费,现在要求从st到ed,要求长度最短,如果
长度相同,要求花费最少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3790
思路:多限制条件的最短路,Dijkstra 先判断长度,长度相等再判断花费.
*/

int n,m,k,st,ed,cnt,head[N],vis[N];

struct Dis{
    int w,cost;
}dis[N];

struct Node{
    int to,next,w,cost;
}edge[M<<1];

struct state{
    int u,w,cost;
    state(int u=0,int w=0,int cost=0):u(u),w(w),cost(cost){}
    bool operator <(const state &x)const{
        if(w == x.w) return cost>x.cost;
        else return w>x.w;
    }
};

void addEdge(int from,int to,int w,int cost){
    edge[cnt]=(Node){to,head[from],w,cost};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s].w=dis[s].cost=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(s,0,0));
    state tmp;
    int u,v;
    while(!Q.empty()){
        tmp=Q.top();
        if(u == ed) return;
        u=tmp.u;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v].w>dis[u].w+edge[i].w){
                dis[v].w=dis[u].w+edge[i].w;
                dis[v].cost=dis[u].cost+edge[i].cost;
                Q.push(state(v,dis[v].w,dis[v].cost));
            }
            //若长度相等,如果花费更少也入堆
            else if(dis[v].w==dis[u].w+edge[i].w && dis[v].cost>dis[u].cost+edge[i].cost){
                dis[v].cost=dis[u].cost+edge[i].cost;
                Q.push(state(v,dis[v].w,dis[v].cost));
            }
        }
    }

}

int main(){
    int u,v,w,cost;
    while(scanf("%d%d",&n,&m) && n+m){
        cnt=0;
        memset(head,-1,sizeof(head));
        while(m--){
            scanf("%d%d%d%d",&u,&v,&w,&cost);
            addEdge(u,v,w,cost);
            addEdge(v,u,w,cost);
        }
        scanf("%d%d",&st,&ed);
        Dijkstra(st);
        printf("%d %d\n",dis[ed].w,dis[ed].cost);
    }
    return 0;
}

/*
spfa 170ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,st,ed,cnt,head[N],vis[N];

struct Dis{
    int w,cost;
}dis[N];

struct Node{
    int to,next,w,cost;
}edge[M<<1];

void addEdge(int from,int to,int w,int cost){
    edge[cnt]=(Node){to,head[from],w,cost};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s].w=dis[s].cost=0;
}

void spfa(int s){
    init(s);
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v].w>dis[u].w+edge[i].w){
                dis[v].w=dis[u].w+edge[i].w;
                dis[v].cost=dis[u].cost+edge[i].cost;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
            else if(dis[v].w==dis[u].w+edge[i].w && dis[v].cost>dis[u].cost+edge[i].cost){
                dis[v].cost=dis[u].cost+edge[i].cost;
                Q.push(v);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }

}

int main(){
    int u,v,w,cost;
    while(scanf("%d%d",&n,&m) && n+m){
        cnt=0;
        memset(head,-1,sizeof(head));
        while(m--){
            scanf("%d%d%d%d",&u,&v,&w,&cost);
            addEdge(u,v,w,cost);
            addEdge(v,u,w,cost);
        }
        scanf("%d%d",&st,&ed);
        spfa(st);
        printf("%d %d\n",dis[ed].w,dis[ed].cost);
    }
    return 0;
}
*/
