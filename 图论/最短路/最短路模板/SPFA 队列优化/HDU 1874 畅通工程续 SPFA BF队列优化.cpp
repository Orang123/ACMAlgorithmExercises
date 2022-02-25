#include<cstdio>
#include<queue>
#include<cstring>
#define N 2010
#define INF 0x3f3f3f3f
using namespace std;
//无法求解正权图的最长路和负权图的最短路问题
/*
题意:n个城市,m条边 求解s->t的最短距离.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1874
思路:最短路裸题.
*/

struct node{
    int to,w,next;
}edge[N];
int n,m,cnt,dis[N],head[N],num[N],vis[N];

/*
相比BF算法很多松弛操作dis[u]实际还没有松弛,即本身还是INF,这时这个松弛是没有意义的,很多时候我们并不需要那么多无用的松弛操作
很显然,只有上一次被松弛的结点,所连接的边的端点,才有可能引起下一次的松弛操作。
那么我们用队列来维护“哪些结点可能会引起松弛操作”,就能只访问必要的边了.
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
/*
最坏时间复杂度 达到BF算法的上界O(VE) 感觉这个其实不管松弛入队顺序怎样 几乎每个点的所有边都会考虑能否松弛,
只是是否可以更新dis[v] 有必要再次赋值的时间开销而已 即较为费时的地方是刚开始入队列松弛的点,边权和并不是最小的,后续松弛后边权和会持续变小 这里就会重复再次对dis[v]赋值
时间开销应该是主要在这了,spfa比较好的一点 对于点如果已经在队列 则不会重复入队,这点相比Dijkstra的堆优化,因为容器中数据不可变,更新后的dis[v]无论怎样都需再次插入堆中,
但总的而言Dijkstra由于采用了贪心的策略,每次都取各个顶点单源路径权值和最小的点作为松弛点去更新,在这样每步局部贪心策略下,能较快达到一个全局最优的结果,即:能在
较早时刻规划好最短路,实际有效的弹出堆顶次数只有n次,剩下的点都是权值和较大被更新过的,可忽略,而重复插入后权值较大的某些点 会根据已经弹出点所做的标记,直接忽略遍历它的边,
这样几乎不会产生什么时间开销,总的而言spfa大多数时候发挥的很好,但在某些强数据下只有正权条件下,还是提倡使用Dijkstra
*/
//这里队列中总共入队的结点个数 无法确定,但总的而言是比BF算法效率要高 不过最好的时间界比Dijkstra还快,就是总共入队的元素就是n个的时候这样时间界 O(V+E) 最坏的情形入队的元素可能远远大于n,时间复杂度取决于建图建边的顺序 不太好分析时间
bool spfa(int s){
    queue<int> Q;
    int u,v;
    init(s);
    Q.push(s);
    vis[s]=1;
    while(!Q.empty()){//每个点很可能会重复入队很多次
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            /*
            对于v有可能是父节点的情况,无需设置访问标记,因为v假如是父节点,
            也无法继续松弛,因为其路径权值和这样只会越来越大.
            */
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                num[v]++;
                /*
                若v点入队超过n-1次则说明除了其余n-2个点出发更新到达v的权和减少,
                自己这个点出发已经走了2圈,也就是死循环了,说明图中含负环(环权值之和为负数,每走一圈,权值都在减少)
                */
                if(num[v] >= n) return false;//这里应该是>=n 很多人写的是 >n 不解
                if(!vis[v]){//若本身还在队列中,则不用重复入队列,只更新dis[v]即可
                    Q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    return true;
}

int main(){
    int s,t,a,b,x;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(head,-1,sizeof(head));
        memset(dis,0,sizeof(dis));
        memset(num,0,sizeof(num));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&a,&b,&x);
            addEdge(a,b,x);
            addEdge(b,a,x);
        }
        scanf("%d%d",&s,&t);
        if(spfa(s)){
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

/*
洛谷P2850 判负环 dfs版本,只要某个点被访问两次 则说明含有负环 感觉对于spfa来说 dfs bfs求取最短路 区别不大,
只是dfs判断负环的效率会更高点,因为bfs即使有负环而本身第一条路径就是最短的时,也会刻意把整张图跑n圈才能判断出来.

如果新扩展的这个点之前已经扩展过了，就说明一条路中存在了两次这个点
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
struct CZP
{
	int next,to,dis;
}a[1000001];
int n,m,h[100001],b[100001],flag,t,top,dis[100001],w;
void cun(int from,int to,int dis)
{
	a[++top].next=h[from];
	a[top].to=to;
	a[top].dis=dis;
	h[from]=top;
}
void pd(int x)
{
	if (flag)
	return ;
	b[x]=1;
	int k=h[x];
	while (k!=-1)
	{
		if (dis[a[k].to]>dis[x]+a[k].dis)
		{
			dis[a[k].to]=dis[x]+a[k].dis;
			if (b[a[k].to])
			{
				flag=1;
				return ;
			}
			else
			pd(a[k].to);
		}
		k=a[k].next;
		}
	b[x]=0;
}   //这里使用了dfs的求负权环操作
int main()
{
	scanf("%d",&t);
	for (int k=1;k<=t;k++)
	{
		flag=0;
	    scanf("%d%d%d",&n,&m,&w);
		for (int i=0;i<=n;i++)
		h[i]=-1;
		for (int i=1;i<=m;i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			cun(x,y,z);
			cun(y,x,z);
			}     //小路为双向边！
		for (int i=1;i<=w;i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			cun(x,y,-z);
		}   //虫洞改为负权值
		memset(b,0,sizeof(b));
		for (int i=1;i<=n;i++)
		cun(0,i,0);  //建立超级源点0
		for (int i=1;i<=n;i++)
		dis[i]=100000000;
		dis[0]=0;
		b[0]=1;
		pd(0);
		if (flag==1)
		printf("YES\n");
		else
		printf("NO\n");
	}
	return 0;
}
*/
