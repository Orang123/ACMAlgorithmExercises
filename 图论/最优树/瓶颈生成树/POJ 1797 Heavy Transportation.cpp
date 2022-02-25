#include<cstdio>
#include<algorithm>
#define N 1100
#define M 500100
using namespace std;
//kruskal最大树 266ms

/*
题意:求从1到n的路径中边权最小的最大值是多少.
链接:http://poj.org/problem?id=1797
思路:kruskal最大生成树,当fa[1]==fa[n]时,当前所连边即为1->n路径上的最大
允许重量.因为边是按照从大到小排序的,当添加的边使得,1和n合并为一个连通集
时,这条边是当前树上从1到达n最小的边,而对于树任意两点之间的路径是唯一的,
而原图中还未加入的边(包含会造成回路的边)为更小的边,即使在1->n的路径上,
对于同一个终点取最小值中的最大值,所取到的仍旧是当前这条边权.
*/

int n,m,fa[N],sum;

struct Edge{
    int u,v,w;
    bool operator <(const Edge &x)const{
        return w>x.w;
    }
}edge[M];

void init(){
    sort(edge+1,edge+1+m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(){
    init();
    int x,y;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            /*
            当添加的边使得1 n连通起来时,那么这条边就在1到达n的路径上,并且是当前所有边权中最小的,
            而后续加边只会更小,所有1->n路径上的最小边的最大值自然就是当前边权.
            */
            if(find(1) == find(n)) return edge[i].w;
        }
    }
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("Scenario #%d:\n",cas);
        printf("%d\n\n",kruskal());
    }
    return 0;
}

/*
//prim ac 313ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,mp[N][N],dis[N],vis[N];

void init(){
    memset(vis,0,sizeof(vis));
    memset(dis,0,sizeof(dis));
}

int prim(int s){
    init();
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,ans=INF;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        if(u!=s)
            //因为prim每次加点是加距离mst中的点的权值最大的点加的,后面加入的边权不一定是最小的,有可能后面加的边反而更大一些
            //所以要求取已加入边权利最小的边就是1到n路径上最小值中最大的边权,
            ans=min(ans,dis[u]);
        //未加入mst中的边即使有从1到n的路径边,也是较小的边,我们是取最小边的最大值
        if(u == n) break;//只要n点和1点连通了,就没必要考虑后面的点,没意义,和1到n的路径边没关系了,为避免ans错误记录,就得提前结束
        for(int v=1;v<=n;v++){
            if(mp[u][v] == -1) continue;//没有边
            if(!vis[v] && mp[u][v]>dis[v]){
                dis[v]=mp[u][v];
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return ans;
}

int main(){
    int T,cas=0,u,v,w;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(mp,-1,sizeof(mp));//不一定是完全图
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            mp[u][v]=mp[v][u]=w;
        }
        printf("Scenario #%d:\n",cas);
        printf("%d\n\n",prim(1));
    }
    return 0;
}
*/

/*
//Dijkstra 266ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],dis[N],vis[N];
struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0,sizeof(dis));//这里Dijkstra Q.top
    dis[s]=INF;
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(dis[s],s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;//这里Dijkstra Q.top 每次都弹出的是最大值当前路径中边权最长的终止点
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //当前到达v点路径中的边权最小值如果比之前路径到达v点的最小值还大就入队
            //这里v点一定是未遍历的,否则有可能会使得v节点的前驱节点重复入队 导致dis[u]最大值计算出错
            if(!vis[v] && dis[v]<min(dis[u],edge[i].w)){
                dis[v]=min(dis[u],edge[i].w);
                Q.push(make_pair(dis[v],v));
            }
        }
    }
}

int main(){
    int u,v,w,T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(1);
        printf("Scenario #%d:\n",cas);
        printf("%d\n\n",dis[n]);
    }
    return 0;
}
*/
