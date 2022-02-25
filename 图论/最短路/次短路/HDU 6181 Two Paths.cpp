#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

/*
题意:求1->n的次短路
链接:http://acm.hdu.edu.cn/showproblem.php?pid=6181
思路:次短路模板
*/

int n,m,cnt,head[N],vis[N][2];
ll dis[N][2];

struct state{
    int v,flag;
    ll dis;
    state(ll dis=0,int v=0,int flag=0):dis(dis),v(v),flag(flag){}
    bool operator < (const state &x)const{
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
    dis[s][0]=0;
}

ll Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(0,s,0));
    int u,v,flag;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,flag=tmp.flag;
        Q.pop();
        if(u == n && flag) return dis[u][flag];
        if(vis[u][flag]) continue;
        vis[u][flag]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v][0]>tmp.dis+edge[i].w){
                if(dis[v][0]!=INF){
                    dis[v][1]=dis[v][0];
                    Q.push(state(dis[v][1],v,1));
                }
                dis[v][0]=tmp.dis+edge[i].w;
                Q.push(state(dis[v][0],v,0));
            }
            else if(dis[v][1]>tmp.dis+edge[i].w){
                dis[v][1]=tmp.dis+edge[i].w;
                Q.push(state(dis[v][1],v,1));
            }
        }
    }
    return -1;
}

int main(){
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        printf("%lld\n",Dijkstra(1));
    }
    return 0;
}

/*
//Dijkstra 436ms 自己改写网上的版本
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N];
ll dis1[N],dis2[N];

struct state{
    int v;
    ll dis;
    state(ll dis=0,int v=0):dis(dis),v(v){}
    bool operator < (const state &x)const{
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
    memset(dis1,0x3f,sizeof(dis1));
    memset(dis2,0x3f,sizeof(dis2));
    //dis2[s]次短路不能设置成0,因为次短路是根据和最短路比较得出的,若初始化为0,对于直链则次短路永远都是0,不可能再更新了
    dis1[s]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(0,s));
    int u,v;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v;
        Q.pop();
        if(tmp.dis>dis2[u]) continue;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis1[v]>tmp.dis+edge[i].w){
                if(dis1[v]!=INF){
                    dis2[v]=dis1[v];
                    Q.push(state(dis2[v],v));
                }
                dis1[v]=tmp.dis+edge[i].w;
                Q.push(state(dis1[v],v));
            }
            else if(dis2[v]>tmp.dis+edge[i].w){
                dis2[v]=tmp.dis+edge[i].w;
                Q.push(state(dis2[v],v));
            }
        }
    }
}

int main(){
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(1);
        printf("%lld\n",dis2[n]);
    }
    return 0;
}
*/

/*
spfa 312ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N];
ll dis1[N],dis2[N];
struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    dis1[s]=0;
}

void spfa(int s){
    queue <int>Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis1[v]>dis1[u]+edge[i].w){
                dis2[v]=dis1[v];
                dis1[v]=dis1[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
            if(dis2[v]>dis2[u]+edge[i].w){
                dis2[v]=dis2[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
            if(dis2[v]>dis1[u]+edge[i].w && dis1[u]+edge[i].w>dis1[v]){
                dis2[v]=dis1[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init(1);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        spfa(1);
        printf("%lld\n",dis2[n]);
    }
    return 0;
}
*/
