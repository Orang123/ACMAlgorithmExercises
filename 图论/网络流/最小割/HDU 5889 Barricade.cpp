#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#define N 1100
#define M 10010
#define INF 0x3f3f3f3f
using namespace std;
//ac 15ms 最短路+最小割
//同HDU 3416
/*
//题意摘自网上
题意:有n个点m条边,每条边的长度相同,我们可以默认为1,
构成一个无向图:现在起点为1,终点为n,从起点到终点有很多路可走,
现在已知每次走的都是最短路径;现在要设置障碍,已知在每条边上设置
障碍的代价wi,为了让从起点到达终点一定能看到至少一个障碍求建立障碍的最小代价;
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3416
思路:同HDU3416,先求出最短路,根据最短路构建网络流,容量为最短路上障碍的代价,
现在要求的就是分离起点和终点的各个路障的最小代价,显然是最小割,而最小割的等于
最大流,求解最大流即可.
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
            if(dis[v]>dis[u]+1){
                dis[v]=dis[u]+1;
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
    st=1,ed=n;
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
            G[u].push_back(make_pair(v,w));//建边是双向边
            G[v].push_back(make_pair(u,w));
        }
        Dijkstra(st);
        for(int u=1;u<=n;u++){
            for(pair<int,int> &e : G[u]){
                int v=e.first;
                if(dis[v] == dis[u]+1)//直接判断 不必再反向建图 dis1[u]+w+dis2[v] == dis1[v]
                    addEdge(u,v,e.second);
            }
        }
        printf("%d\n",max_flow(st,ed));
    }
    return 0;
}
