#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;
//Dijkstra 266ms
//这种求解路径中边权最小值最大化问题别用spfa,因为spfa无法保证重复遍历前驱节点的问题,因为松弛本身就是不确定的
/*
虽然Dijkstra无法求解正权图最长路,但是这个题目是求解边权的最小值最大化,
假如1->2->3 边权2、5 1->3 边权4 那么开始1节点扩展时,2 、4边权入队,根据贪心4先出队,
3节点标记,这里为什么忽略了2->3的边权5呢,因为是求取路径中最小值,一开始2就比4小,后续的最小值只会<=2,
当到达3点时,最大值还是4,因此3节点第一次标记后,记录的就是最大边权,不可再被松弛.这是和最长路边权和
不同的地方.同样对于路径边权最大值最小化问题,Dijkstra同样适用.
*/
/*
题意:求从1到n的路径中边权最小的最大值是多少.
链接:http://poj.org/problem?id=1797
思路:最短路,修改下松弛条件.dis[v]<min(dis[u],edge[i].w)
*/

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
/*
//kruskal 最大树做法 266ms
#include<cstdio>
#include<algorithm>
#define N 1100
#define M 500100
using namespace std;

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
*/

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
二分解法
*/
