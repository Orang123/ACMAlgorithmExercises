#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 10010
#define INF 0x3f3f3f3f
using namespace std;
//ac 16ms EK算法 最小费用流 源点->1->n->汇点
//不知为何此题 源点设置1,汇点设置n,就会出错.
/*
题意:给你一个无向图,让你求一条最小的路径从1到N再回到1.边不能重复走.
求所走的最短距离是多少.
链接:http://poj.org/problem?id=2135
思路:不能用正反跑两次最短路,因为首先这样可能会导致虽然第一次正着走
距离最短,但第二次可能不通,或某条边权选的过大,就是结果不一定就是最小
的,正确性得不到保证.所以可以考虑费用流,源点0,汇点n+1,源点向1点连容量
为2,费用为0的无向边,注意因为是无向图,建2条边.因为要从1走到n,再从n走到1,
走两次所以容量为2,而这个反向走的过程转化为网络流可以变为走两次正向的1到n.
n点向汇点连容量为2,费用为0的无向边.其余边u-v,也是建容量为1,费用为w的两条无向边.
跑费用流即可得到答案.
*/
int n,m,cnt,head[N],st,ed,incf[N],pre[N],dis[N],vis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<2];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

int mcmf(){
    int sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed]*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    init();
    addEdge(st,1,2,0);
    addEdge(n,ed,2,0);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,1,w);//因为是无向图,所以建两条边
        addEdge(v,u,1,w);
    }
    printf("%d",mcmf());
    return 0;
}

/*
//ac 16ms dinic 最小费用流 源点->1->n->汇点
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 10010
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],st,ed,dis[N],vis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<2];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    memset(vis,0,sizeof(vis));
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return dis[ed]!=INF;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v] && edge[i].cf>0 && dis[v] == dis[u]+edge[i].w){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
        }
    }
    return res;
}

int mcmf(){
    int sum=0,incf;
    while(spfa(st)){
        incf=dfs(st,INF);
        sum+=incf*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    init();
    addEdge(st,1,2,0);
    addEdge(n,ed,2,0);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,1,w);//因为是无向图,所以建两条边
        addEdge(v,u,1,w);
    }
    printf("%d",mcmf());
    return 0;
}
*/
