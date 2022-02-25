#include<cstdio>
#include<cstring>
#define N 2010
#define INF 0x3f3f3f3f

/*
题意:n个城市,m条边 求解s->t的最短距离.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1874
思路:最短路裸题.
*/

struct node{
    int from,to,w;
}edge[N];
int n,m,cnt,dis[N];

/*
Bellman-Ford(贝尔曼-福特)算法 一种基于松弛(relax)操作的最短路算法。
松弛可理解为将一条直线在某个点拉伸,来使其变成2段线,2段线的权值之和要远小于本来的直线
支持负权.能找到某个结点出发到所有结点的最短路，或者报告某些最短路不存在.
*/

void addEdge(int from,int to,int w){
    edge[cnt].from=from;
    edge[cnt].to=to;
    edge[cnt].w=w;
    cnt++;
}
void init(int s){
    for(int i=0;i<n;i++)
        dis[i]=(i==s?0:INF);
}
//最坏时间复杂度O(VE)
bool Bellman_Ford(int s){
    init(s);
    int u,v,ok;
    /*
    由于一次松弛操作会使最短路的边数至少+1,而最短路的边数最多为n-1(连通无回路的一条笔直的树考虑,边数为点数-1).
    所以最多执行n-1次松弛操作，即最多循环n-1次.
    在更新松弛最长的最短路时,在每一次的循环中较短的最短路也在被松弛更新
    */
    for(int i=1;i<n;i++){
        ok=0;
        /*
        尽可能多地考虑每一条边是否可以松弛,这里和实际构建边集的顺序有关,
        越好的序列可能在前期越早地能求出每个点的最短路,即每次循环松弛的边越多,
        它的cnt序列刚好满足前面松弛的点dis更新后,cnt靠后的边的dis[u]刚好就是之前更新
        好的dis[v]这种情况是最为理想的情况,最坏的情况及是每次只更新松弛一条边,这条边刚好
        是最靠后的边依次往前推更新,刚好循环完n-1次
        */
        for(int j=0;j<cnt;j++){
            u=edge[j].from;
            v=edge[j].to;
            /*
            BF算法很多松弛操作dis[u]实际还没有松弛,即本身还是INF,这时这个松弛时没有意义的,这也是BF算法的缺陷,spfa正是在此点上改进
            */
            if(dis[v]>dis[u]+edge[j].w){//dis[v]存在更短的路径,以u中介点,dis[u]+u->v
                dis[v]=dis[u]+edge[j].w;
                ok=1;//有边可松弛的标记
            }
        }
        if(!ok)//若此次循环,没有一条边可以松弛代表源点到所有点的最短路已经求出 此题只是求解最短路问题,只有正权,没有负权,不存在负环的说法
            return true;//退出程序
    }
    //代表刚好进行暴力进行了n-1次松弛更新,此时验证是否存在负环
    for(int j=0;j<cnt;j++){
        u=edge[j].from;
        v=edge[j].to;
        if(dis[v]>dis[u]+edge[j].w)//若仍旧还存在边可松弛更新,说明某条边一定重复性地松弛,说明存在负环,越松弛越小,无线循环,某个点不一定被松弛n次,但是某个边一定是被重复松弛了>=2次
            return false;
    }
    return true;
}

int main(){
    int s,t,a,b,x;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dis,0,sizeof(dis));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&a,&b,&x);
            addEdge(a,b,x);
            addEdge(b,a,x);
        }
        scanf("%d%d",&s,&t);
        if(Bellman_Ford(s)){
            if(dis[t]!=INF)
                printf("%d\n",dis[t]);
            else
                printf("-1\n");
        }
        else
            printf("原图含有负环,不存在最短路\n");
    }
    return 0;
}
