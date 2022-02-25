#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000100
#define M 2000100
#define INF 0x3f3f3f3f
#define MOD 100003
using namespace std;

/*
题意:求解从1到达其余每个点的最短路个数.
链接:https://www.luogu.com.cn/problem/P1144s
思路:设置num[x]表示到达节点x的最短路个数,dis[v]更新时,num[v]=num[u],
当发现最短路此时刻权值和相同时,num[v]+=num[u].

因为这题权值恒定为1,所以也可用朴素的bfs做,但是对于无向图 边权为w的不定值,
最短路做法是具有普适性,此时朴素的bfs就不能应用,因为权值不恒定,先搜到的也
不一定是最短路.
*/

int n,m,cnt,head[N],vis[N],num[N],dis[N];
struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void bfs(int s){
    init(s);
    queue <int>Q;
    num[s]=vis[s]=1;//起始点代表一条路径
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //如果还没遍历到,那么当前遍历到的距离就是最短的,因为这里边权都为1,bfs第一次遍历到的一定是最短的
            if(!vis[v]){
                vis[v]=1;
                dis[v]=dis[u]+1;
                Q.push(v);
            }
            //当找到最短路或者和最短路距离相等时 就累加最短路个数
            if(dis[v] == dis[u]+1)
                num[v]=(num[v]+num[u])%MOD;
        }
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    bfs(1);
    for(int i=1;i<=n;i++)
        printf("%d\n",num[i]);
    return 0;
}
/*
//Dijkstra做法
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000100
#define M 2000100
#define INF 0x3f3f3f3f
#define MOD 100003
using namespace std;
//Dijkstra 最短路做法
int n,m,cnt,head[N],vis[N],num[N],dis[N];
struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void Dijkstra(int s){
    init(s);
    priority_queue <pair<int,int> >Q;
    num[s]=1;//起始点代表一条路径
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
                num[v]=num[u];//最短路径发生变化,根据前驱节点的路径条数更新v节点路径条数
                Q.push(make_pair(-dis[v],v));
            }
            else if(dis[v]==dis[u]+edge[i].w)
                num[v]=(num[v]+num[u])%MOD;//当相等时,v节点路径条数就要加上u前驱节点路径条数
        }
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v,1);
        addEdge(v,u,1);
    }
    Dijkstra(1);
    for(int i=1;i<=n;i++)
        printf("%d\n",num[i]);
    return 0;
}
*/


