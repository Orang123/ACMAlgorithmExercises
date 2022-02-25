#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5500
#define M 200100
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:https://www.luogu.com.cn/problem/P2483
链接:https://www.luogu.com.cn/problem/P2483
思路:A*启发式搜索.
*/

int n,head1[N],head2[N],vis[N],cnt,ans,tot[N];
double e,dis[N];
/*
要使用A*算法,必须包含开放列表、关闭列表、估价函数(f),现在所写的A*
只是侧重于估价函数f=g+h,模拟了它的反向最短路搜索,和正向A*搜索,未涉及
开放列表和关闭列表,并不算真正意义上的A*算法
*/
/*
分别构建正向边和反向边,因为A*算法维护估价函数f时,没有(dis[v]>dis[u]+w)等判断条件是直接入堆更新估价函数f的
如果正向边和反向边都放置在一个edge里,会导致A*搜索时从子节点又会遍历回到父节点,父节点重复入堆,这样会导致
若是原先这条路径整体的路径权值较小,长度也较小,其它分支的路径较长到达终点较晚,那么这条路径可能会被重复作为多次到达终点的路径计算,
那么总费用E会被提前消耗,若前面分支整体总花费就较小会导致计算的ans结果偏大.
*/
struct Node{
    int to,next;
    double w;
}edge1[M],edge2[M];

struct Data{
    int u;
    double f,g;
    Data(int u,double f,double g):u(u),f(f),g(g){}
    bool operator < (const Data &a)const{
        //f相等时,貌似可以按g去比较
        return f>a.f;//A*搜索以维护估价函数f作为优先出堆依据,f较小的,则越是接近终点,整体花费较小,每次都尽可能取f较小的,那么就能在E有限地条件下,才会有尽可能多的路径到达终点
    }
};

void addEdge(int from,int to,double w){
    edge1[cnt].to=to;
    edge1[cnt].w=w;
    edge1[cnt].next=head1[from];
    head1[from]=cnt;
    edge2[cnt].to=from;
    edge2[cnt].w=w;
    edge2[cnt].next=head2[to];
    head2[to]=cnt++;
}

void init(int s){
    for(int i=1;i<=n;i++)
        dis[i]=s==i?0:INF;//这里INF赋值不能用memset,会出错
}

/*
计算从终点到达其余点的最短路径,作为h(x),为从当前状态到达目标状态的最佳路径的估计代价(dis记录)。
spfa和Dijkstra都可以 dij快一点
*/
void Dijkstra(int s){//NlogN
    priority_queue <pair<double,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        /*
        这里是在反向边图从终点开始遍历计算到达其余点的最短路径
        其实这里即使是在双向边的无向图里遍历结果也是不会出错的,
        因为都是正权,而且有dis[v]>dis[u]+edge2[i].w的判定,只是
        采用反向边可以避免访问回到父节点的点,能提高效率,但是A*搜索
        是一定要在正向边里遍历的
        */
        for(int i=head2[u];i!=-1;i=edge2[i].next){
            v=edge2[i].to;
            if(dis[v]>dis[u]+edge2[i].w){//这里的判断条件只能计算最短路 无法计算第k短路
                dis[v]=dis[u]+edge2[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

/*void spfa(int s){
    queue<int> Q;
    init(s);
    Q.push(s);
    vis[s]=1;
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head2[u];i!=-1;i=edge2[i].next){
            v=edge2[i].to;
            if(dis[v]>dis[u]+edge2[i].w){
                dis[v]=dis[u]+edge2[i].w;
                if(!vis[v]){
                    Q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}*/

/*
A*搜索为启发式搜索,就是通过f=g+h,g与h之间的平衡来判定到底哪个点可能距离终点较近的,
g相同的情况下选择h较小的,h相同的条件下选择g较小的,综合下来就是实际可能距离终点较近的点
这个有相关的数学证明,我们不必深究
估价函数f(x)=g(x)+h(x)
其中g(x)为从初始状态到达当前状态的实际代价,h(x)为从当前状态到达目标状态的最佳路径的估计代价。
每次取出f(x)最优的状态x,扩展其所有子状态,可以用优先队列来维护这个值。
在求解k短路问题时，令h(x)为从当前结点到达终点t的最短路径长度(从终点t到其余点的单源最短路径),
g(x)为从初始状态走到当前状态实际走过的路径长度
*/

/*
g(x)与h(x)对f(x)的影响
1.如果h(x)<g(x)估计值小于实际值，这种情况下，搜索的点数多，搜索范围大，效率低。但能得到最优解。
2.如果h(x)=g(x),估计值等于实际值，那么搜索将严格沿着最短路径进行， 此时的搜索效率是最高的。
3.如果h(x)>g(x),估计值大于实际值,搜索的点数少，搜索范围小，效率高，但不能保证得到最优解。
*/
void Astar(int s,int t,int k){//当图的形态是一个n元环(有环的条件下效率偏低吧)的时候,该算法最坏是O(KNlogN)的 每个由s到达t的路径都是最坏NlogN,k条就是kNlogN
    priority_queue <Data> Q;
    Q.push(Data(s,dis[s],0));
    while(!Q.empty()){
        Data u=Q.top();//启发式搜索f值较优的情况,也就是距离终点最近的点去扩展其余点
        Q.pop();
        /*
        在没有总费用限制的条件下,如果原图中含有环,那么A*搜索是一个死循环会一直重复搜索下去,
        若原图中没有环,则在没有连边结点搜索时会结束循环
        */
        if(u.u == t){//从起点走到终点t
            e-=u.g;//总费用要减去当前从起点走到终点t所花费的实际费用
            if(e<0) return;//若e<0说明之前剩余的费用 不够支出本次到达终点的路径的费用,因为之后出队的f函数只会大于等于当前的,所以剩余费用都不够,结束
            ans++;//第ans条到达终点t的最短路
            continue;//到达终点后,再用终点去扩展别的点都是无意义的,再去扩展只会导致f增大,题意也说明这次转化过程到达后就应结束而不应重复成环又再次访问
        }
        /*
        这里的剪枝优化是对于前面的路径分支所消耗e所剩无几,在这里通过判断路径前面某个点作为第k短路被贡献了几次,
        因为最多只能贡献(e/dis[1])次,即最多只有第e/dis[1]短路,若这个点的贡献次数大于k,则在这个点的贡献下不可能再有第k+1短路,
        就不对这个点进行扩展,这里就可以避免剩余没有意义的点扩展入队,剪枝以优化时间,这里++tot[u.u]大于k并不代表之前经过u.u已经
        有k条路径到达终点了,也许有,只是说明它之前入队了k次,但是后续它扩展的点入队后是否在f较优条件下是否到达终点未知,也许其它f
        更短的路径先到达了,但这个路径却没经过u.u,也就是u.u扩展的点可能还在堆中未扩展到终点,但也许之后它能到达终点,
        我们只需要确定的是它不能贡献超过k次,因为整个图从s到t的总花费e只够支付k条路径,对于搜索的结束还是以后续扩展e-u.g<0来决定
        */
        if(++tot[u.u]>k) continue;
        Data v=Data(0,0,0);
        for(int i=head1[u.u];i!=-1;i=edge1[i].next){//这里没有额外扩展的判断条件, 因为要计算第k短路,并不是Dijkstra和spfa那样只能统计最短的路径,如果先统计了最短的,那后续第二短和第三短都无法统计了,因此无法采用Dijkstra和spfa取做 尽可能更新f函数入队,选择可能更优的f函数
            v.u=edge1[i].to;
            v.g=u.g+edge1[i].w;//到达当前v点实际走过的路径花费为之前u的花费加上u->v的花费
            v.f=v.g+dis[v.u];//估价函数f=g+h(dis)
            Q.push(v);
        }
    }
}

//题意就是求在总费用E下 最多能通过有几条路径到达终点
int main(){
    int m,u,v;
    double w;
    memset(head1,-1,sizeof(head1));//cnt边集数组下标可从0开始记录 用-1判断是否为空
    memset(head2,-1,sizeof(head2));
    scanf("%d%d%lf",&n,&m,&e);//数据集11MLE 这里特判 n==5000&&m==9997&&e==10000000 的内存空间限制应用可持久化可并堆解决
    while(m--){
        scanf("%d%d%lf",&u,&v,&w);
        addEdge(u,v,w);
    }
    Dijkstra(n);//遍历反向边统计h(x)
    //spfa(n);
    Astar(1,n,(int)e/dis[1]);//遍历正向边更新g(x) f(x) (int)e/dis[1]代表在e的总花费最多能有几条路径到达终点  是取从起点到终点第1短路作为标准e除它得出的一个上界(最多的数目)
    printf("%d",ans);//输出完成的方式数
    return 0;
}
