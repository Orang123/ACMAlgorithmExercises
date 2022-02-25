#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 21000
#define INF 1e15//0x3f 应该不行,因为w权和可能比0x3f还大
using namespace std;
typedef long long ll;

/*
题意:n个城市,有两类道路,第一类道路是单个城市之间的双向道路,
第二类道路是城市群之间的道路,一个城市群的所有城市可通过第二类道路和
另一个城市群众的所有道路相通,问从城市s到城市t的最短距离是多少.
链接:https://nanti.jisuanke.com/t/A1244
思路:第二类道路的建边显然不可能将两个城市群中的所有城市两两建边,这样会MLE,
也会TLE,因此可以对于每个城市群拆点构造出一个出点(由城市群中所有城市连向)
和一个入点(连向城市群中所有的城市),边权都为0,对于两个城市群中的第二类道路,
可通过一个城市群的出点到另一个城市群的入点建边实现互通.
*/

int n,m,cnt,head[N<<2],vis[N<<2];//每个城市群还有2个虚点(3N) 因此上限N<<2
ll dis[N<<2];
struct Node{
    int to,next;
    ll w;
}edge[N<<3];//边数上限设大点

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    for(int i=1;i<(n<<2);i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s){
    queue <int>Q;
    init(s);
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,s,t,num,m0;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&num);
        while(num--){
            scanf("%d",&v);
            addEdge(v,i+n,0);//每个城市到出点建边
            addEdge(i+n+m,v,0);//入点到每个城市建边 边权都为0
        }
    }
    scanf("%d",&m0);
    while(m0--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    scanf("%d",&m0);
    while(m0--){
        scanf("%d%d%lld",&u,&v,&w);//这里建议入点编号用u+2*n,v+n+m和u+n有可能会重
        addEdge(u+n,v+n+m,w);//城市群u的出点向城市群v的入点建边
        addEdge(v+n,u+n+m,w);//城市群v的出点向城市群u的入点建边 这样就实现两个城市群之间两两互通
    }
    scanf("%d%d",&s,&t);
    spfa(s);
    if(dis[t]!=INF)
        printf("%lld\n",dis[t]);
    else
        printf("-1\n");
    return 0;
}

/*
Dijkstra做法
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 21000
#define INF 1e15//0x3f 应该不行,因为w权和可能比0x3f还大
using namespace std;
typedef long long ll;

int n,m,cnt,head[N<<2],vis[N<<2];
ll dis[N<<2];
struct Node{
    int to,next;
    ll w;
}edge[N<<3];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    for(int i=1;i<(n<<2);i++)
        dis[i]=(i==s?0:INF);
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
    int u,v,s,t,num;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&num);
        while(num--){
            scanf("%d",&v);
            addEdge(v,i+n,0);
            addEdge(i+2*n,v,0);
        }
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u+n,v+2*n,w);
        addEdge(v+n,u+2*n,w);
    }
    scanf("%d%d",&s,&t);
    Dijkstra(s);
    if(dis[t]!=INF)
        printf("%lld\n",dis[t]);
    else
        printf("-1\n");
    return 0;
}
*/
