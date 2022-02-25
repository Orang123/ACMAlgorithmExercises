#include<cstdio>
#include<queue>
#include<cstring>
#define N 2010
#define INF 0x3f3f3f3f
using namespace std;
/*
题意:n个城市,m条边 求解s->t的最短距离.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1874
思路:最短路裸题.
*/

struct node{
    int to,w,next;
}edge[N];
int n,m,cnt,dis[N],head[N],vis[N];
/* bool operator < (const node &x)const 重载优先队列,小根堆
    {
     return dist>x.dist;
    }
*/
/*
Dijsktra 无法处理负权 负环的问题,因为每次都取的是最小的权值和的点,而且只会取一次,就算弹出先前已经弹出堆的点,
也不会进行松弛操作,不存在每个点会访问2次及其以上,因此根本就不会形成访问的一个回路的问题,自然也就无法根据入队
采取这个点松弛的次数>=n来判定存在负环的问题,就是说即使全是负权,这个while循环也只会 循环n次 vis[u]都是1 剩余的点虽然也小,但算法本身每个点只会取一次,因此无法重复访问形成回路
*/
void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s){
    for(int i=0;i<n;i++)
        dis[i]=(i==s?0:INF);
}
//O(MlogN+M)~=O(MlogN) Dijkstra,spfa无法求解负权图的最短路问题,因为无法避免回到走过的前驱节点,往回走
void Dijkstra(int s){
    priority_queue<pair<int,int> > Q;//默认是大根堆
    int u,v;
    init(s);
    Q.push(make_pair(0,s));//pair first 为路径权和 second 为终点
    //这里循环的次数其实就是朴素Dijkstra 点的个数,因为每次都只取出一个最短的路径点,总共取n次就恰好能完成所有顶点的最短路更新
    while(!Q.empty()){
        /*
        //每次都弹出堆顶路径权较小的点去松弛其余点,总共弹n次,这样能较早地规划更新出所有点的最短路
        每次最坏时间复杂度O(logN) 还有一个优化是后续松弛的点往往dis[v]比之前的大这样也不用
        再次赋值更新,因为每一步都取的是权值和最小的点去松弛的.
        */
        u=Q.top().second;
        Q.pop();
        /*
        主要的优化就体现在这里,因为while有效的循环只会循环n次,
        剩余的点的vis[u]其实之前都已弹出堆,剩余的这些是之前较大的路径权和,
        已没有松弛的必要.
        */
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){//这里累加的for次数刚好为图中边的总个数 M
            v=edge[i].to;
            /*
            这里因为是最短路 本身是没有负权的,都是正权所以 无需判定!vis[v],
            不过如果真的有负权也可加上,这样可能不会导致dis[v]被更新,
            也不会插入堆中.
            */
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
            //这里不考虑之前v点是否在堆中,因为priority_queue Q中保存的dis[v]是不会更新的,
            //所以只要dis[v]有更新都重新插入堆中
                Q.push(make_pair(-dis[v],v));//这里权值和取负数,大顶堆的堆顶元素实际便是最小的 O(logN)入队
            }
        }
    }
}
/*
注意Dijkstra无法求解正权图中的最长路
2点原因:无向图 前驱节点无限入队更新,另一点即使是有向图,因为贪心的原因,结果也不正确.
eg:1->2->3 1->3 对于1->2权2 2->3权3 1->3权4,那么由1点开始遍历时,
将2、3点入队后,因为权值和2,4,根据贪心求取当前集合中最长权和,
3点出队,并且3点不可再被访问入队,但实际1->2->3的权值和5才是最大的,
显然结果错误.造成这样错误的原因主要在于 最短路 Dijkstra是建立在bfs层序遍历的基础上的,
在边数越少权值和较小的点先松弛时,其权值和一定就是最小的,但是如果对于求取最长路,
在边数越少权值和较大的点先松弛时,其权值和确不一定就是最大的了,但Dij会vis做出队标记,
使得后松弛的原先边数较多的较大权值和能正常入队,但是出队时,无法再度去松弛其余点,
因为先前出队已被标记,导致后续点dis值结果错误.
不过对于负权边的最长路Dijkstra还是能通用的,实际这仍旧是求解最短路.

//对于spfa而言无法求解正权图的最长路问题,因为它无法避免回到前驱节点,往回走,
//因为先松弛的本身就不一定是最优的,所以对于一般情况,即使一个节点已经出队如有更优的松弛就会再次入队,
//但如果往回走走过的前驱节点就会重复走,这是不可避免的问题,但是负权图的最长路spfa是能求解的.
void Dijkstra(){
    priority_queue<pair<int,int> > Q;//默认是大根堆
    int u,v;
    memset(dis,0,sizeof(dis));
    Q.push(make_pair(0,s));
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //只适用负权图最长路
            if(dis[v]<dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(dis[v],v));
            }
        }
    }
}
*/

int main(){
    int s,t,a,b,x;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(head,-1,sizeof(head));
        memset(dis,0,sizeof(dis));
        memset(vis,0,sizeof(vis));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&a,&b,&x);
            addEdge(a,b,x);
            addEdge(b,a,x);
        }
        scanf("%d%d",&s,&t);
        Dijkstra(s);
        if(dis[t]!=INF)
            printf("%d\n",dis[t]);
        else
            printf("-1\n");
    }
    return 0;
}
