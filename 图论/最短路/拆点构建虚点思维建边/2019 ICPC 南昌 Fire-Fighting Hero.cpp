#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1000100
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:n个地区,设有k个消防点,有m条双向道路,还有一个消防英雄
在s地区,现在要求出消防英雄到达其它地区最短路的最大值,和k个
消防队分别到达其它(实际就是k个点之外的点)路径最短路的最大值,
两者最大值进行比较,消防英雄要除以c,输出原先较小的最大值.
链接:https://nanti.jisuanke.com/t/41349
思路:消防英雄到其余点的最短路很好求,但消防队分别到其余点的最短路属于一个
多源点的最短路问题,如果暴力求解则需要跑k次最短路或floyed O(N^3),可以建立
一个超级源点(0)到k个消防队所在的点构建一条单向边,这样以超级源点0作为起点
跑一遍最短路,比较每个点的dis,求出最大值即是k个消防队到其余地点最短路的最大值.
这个做法看上去从超级源点出发也考虑了每个消防队作为入点,但在跑的过程中,dijkstra
是贪心算法,如果先行更新的是较短的dis,对于相同点的dis,较大的边权和可能就不会被考虑,
所以总体来讲,实际所遍历的边数是比暴力跑k次最短路要小的,因此时间也较优.
*/

int n,m,s,k,c,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M];

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
    init(s);
    priority_queue<pair<int,int> >Q;
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
    int T,u,v,w,ans1,ans2;
    scanf("%d",&T);
    while(T--){
        ans1=ans2=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d%d%d%d",&n,&m,&s,&k,&c);
        for(int i=1;i<=k;i++){
            scanf("%d",&v);
            addEdge(0,v,0);//超级源点连向k个消防队所在点
        }
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(s);
        for(int i=1;i<=n;i++)
            ans1=max(ans1,dis[i]);
        //事实上求解的是从0(超级源点)开始最短路,各个消防队的dis本身也是为0的,实际上就是求解各个消防队到其余点的最短路的最大距离
        Dijkstra(0);
        for(int i=1;i<=n;i++)
            ans2=max(ans2,dis[i]);
        if(ans1<=ans2*c)
            printf("%d\n",ans1);
        else
            printf("%d\n",ans2);
    }
    return 0;
}
