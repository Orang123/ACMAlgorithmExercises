#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#define N 1100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//ac 156ms 最短路+网络路
//同HDU 5889
/*
题意:有n个城市,m条边,a到b耗费为w,为单向边.
要求从s到t的最短路径有多少条,每一条边只能走一次.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3416
思路:实际就是求解在每条边只能走一次的条件下,有几条从s到达t的最短路,
注意不能用统计最短路数量的那个加法原理的做法,这个做法每条边可以使用
多次.先求出最短路,再根据最短路dis[v]==dis[u]+w满足时,构建网络,每条边
的容量为1,求最大流就是最短路数目.
这个并不需要反向建图跑两次最短路,直接判断dis[v] == dis[u]+w,不必再反向建图
dis1[u]+w+dis2[v] == dis1[v].
*/
int n,m,st,ed,cnt,head[N],dis[N],vis[N];
vector<pair<int,int> > G[N];
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

void Dijkstra(int s){
    priority_queue<pair<int,int> > Q;
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    Q.push(make_pair(-dis[s],s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(pair<int,int> &e : G[u]){
            v=e.first;
            if(dis[v]>dis[u]+e.second){
                dis[v]=dis[u]+e.second;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int bfs(int s,int ed){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int ed,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,ed,min(flow,edge[i].cf));
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
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(int st,int ed){
    int sum=0;
    while(bfs(st,ed))
        sum+=dfs(st,ed,INF);
    return sum;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int u,v,w,T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            G[u].push_back(make_pair(v,w));//建边是单向边
        }
        scanf("%d%d",&st,&ed);
        Dijkstra(st);
        for(int u=1;u<=n;u++){
            for(pair<int,int> &e : G[u]){
                int v=e.first;
                if(dis[v] == dis[u]+e.second)//直接判断 不必再反向建图 dis1[u]+w+dis2[v] == dis1[v]
                    addEdge(u,v,1);
            }
        }
        printf("%d\n",max_flow(st,ed));
    }
    return 0;
}
