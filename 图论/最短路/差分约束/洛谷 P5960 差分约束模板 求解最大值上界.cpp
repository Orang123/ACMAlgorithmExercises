#include<cstdio>
#include<cstring>
#include<queue>
#define N 5100
#define INF 0x3f3f3f3f
using namespace std;
//求解最大值上界
/*
题意:https://www.luogu.com.cn/problem/P5960
链接:https://www.luogu.com.cn/problem/P5960
思路:差分约束系统模板
*/

/*
Dijkstra无法处理含有负权边的情况,Bellman-Ford可以
对于不等式 x1-x0<=2 转换为x1<=x0+2 看看成x0->x1之间有一条长度为2的有向边 这里是根据最短路的松弛函数类比过来的
对于三角不等式(1)B-A<=c,(2)C-B<=a,(3)C-A<=b 现将三者建成三个点的图 问题转化成了 A->B(w=c) B->c(w=a) A->C(w=b)
(1)+(2)可得C-A<=c+a 其实现在问题转换为了求解
C-A<=c+a,C-A<=b这两个不等式的解 根据不等式同小取小的原则C-A<=min(c+a,b) 现在的问题刚好变成了求解
这个图中从源点A到终点C的最短路问题,但是对于原不等式而言我们依旧求取的是其最小的上界，因此仍旧是求取最大值。
实际上上面的问题也可以完全建立成反向边 即(1)A-B>=-c (2)C-B>=-a (3)A-C>=-b (2)+(3)可得:A-B>=-a-b,所求解的问题
根据不等式同大取大的原则转变成max(-c,-a-b),图论中的问题转变成了 求解从源点B到终点A的最长路问题
差分约束属于线性规划问题,感觉有点像高中数学里的线性规划求取目标函数的临界值问题。
对于此题而言我们最终要求的是xi的符合条件的一组值,即我们可以加入一个超级源点,将问题转化为求取从超级源点到各个点的最短路问题
总之:差分约束问题可以转化为最短路或最长路问题，所以两种转化也就形成了两种不同的连边方法,两种方法求出的解是不同的,一种x<=0 另一种x>=0
1.连边后求最短路
将xj-xi<=k变形为xj<=xi+k,即从i到j连一条边权为k的边,加入超级源点后求最短路,得到xi<=0,因此x有最大值
2.连边后求最长路
将xj-xi<=k变形为xi>=xj+(-k),即从j到i连一条边权为-k的边,加入超级源点后求最长路,得到xi>=0,因此x有最小值
注意:1.对于原图中存在负环,因为求解的是最短路,则会一直沿着负环走,最短路就会越来越小最后趋于-OO
对于不等式集而言,化简后的式子 为求取x<=0 x>=5这样没有交集的情况,即不等式无解。
2.对于原图不连通,则可认为最大值无限大,有无数组解满足条件
3.对于xi-xj=c可转化成xi-xj<=c xi-xj>=c 需要建两条边
*/

struct node{
    int to,w,next;
}edge[N<<1];
//vis判断是否入队 num记录入队次数 dis[i]表示超级源点到i的最短路
int cnt,vis[N],num[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[0]=0;//超级源点到自身距离为0
    for(int i=1;i<=n;i++)
        dis[i]=INF;//因为求最短路 所以超级源点初始化到其余各定点的值要设置正无穷,第一次松弛边时会得到更新
}
//Shortest Path Faster Algorithm (SPFA)(西南交大 段凡丁 不过BF提出更早) 即: Bellman-Ford的队列优化,时间复杂度最坏 O(VE) 即每一次出队每个点都会对其余所有点的边进行松弛
bool SPFA(int u){
    init();
    queue<int> Q;
    int v;
    Q.push(u);//超级源点并没有被松弛,超级源点不会被松弛,其它点没有边连向超级源点
    vis[u]=1;
    while(!Q.empty()){//O(V)
        u=Q.front();
        vis[u]=0;//出队 标记为0
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){//O(E)
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){//s->v可松弛为s->u->v 更新
                dis[v]=dis[u]+edge[i].w;
                num[v]++;//v点入队次数加1
                /*
                判断是否存在负环,(这里算上超级源点有n+1个点)理论上每个点最多只可被除自己外n个点构成的路径松弛,
                当第n+1个路径开始对这个点松弛时这个路径一定构成了负环,因为它一定和之前的n个路径中的其中一条重复了,
                这里再度松弛就是因为环的权值和为负数才导致其松弛值越来越小
                */
                if(num[v] >= n+1) return false;//这里有可能第二次访问就已经是负环了,但还是为重复访问n次才会达到判定条件,也有可能第二次入队是因为别的结点构成的路径松弛并不构成负环
                if(!vis[v]){//如果已经入队就无需重复入队,只有松弛过的点没有再队列中，才需入队下次出队后用来松弛其它点更新最短路
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return true;
}
int main(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(v,u,w);
    }
    for(int i=1;i<=n;i++)//加入超级源点 构建顺序任意可以放在原图构建边之前构建
        addEdge(0,i,0);
    if(SPFA(0)){
        for(int i=1;i<=n;i++)
            printf("%d ",dis[i]);//求解出的解为 0 -2 0 对于输入案例里的输出 5 3 5其实这两个是等价的,对于不等式在不等式两端加上同样的值不等式仍成立,这里加5 0,-2,0就转变成了5,3,5
    }
    else//存在负环无解
        printf("NO");
    return 0;
}

/*
//最小值 最长路做法 构建反向负权边 求解最长路问题,对于正权边无法求解最长路,负权边可以s
#include<cstdio>
#include<cstring>
#include<queue>
#define N 5100
#define INF -0x3f3f3f3f
using namespace std;

struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],num[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[0]=0;
    for(int i=1;i<=n;i++)
        dis[i]=INF;//这里初始化为无穷小,因为要求最长路,超级源点松弛后就可更新
}

bool SPFA(int u){
    init();
    queue<int> Q;
    int v;
    Q.push(u);
    vis[u]=1;
    num[u]++;
    while(!Q.empty()){
        u=Q.front();
        vis[u]=0;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]<dis[u]+edge[i].w){//松弛判定 最长路
                dis[v]=dis[u]+edge[i].w;
                num[v]++;
                if(num[v] >= n+1) return false;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return true;
}
int main(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,-w);
    }
    for(int i=1;i<=n;i++)
        addEdge(0,i,0);
    if(SPFA(0)){
        for(int i=1;i<=n;i++)
            printf("%d ",dis[i]);// 0 0 2 和最短路的解不同这里>=0
    }
    else
        printf("NO");
    return 0;
}
*/
