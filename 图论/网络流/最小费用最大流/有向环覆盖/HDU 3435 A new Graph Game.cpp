#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 2100
#define M 14000
#define INF 0x3f3f3f3f
using namespace std;
//TLE 费用流 此题链式前向星莫名超时 vector能ac
/*
题意:n个点,m条边的无向图,每条边都有权值,现在可
以删掉任意数量的边,使得原图变成一些分离的连通子图,
每个连通子图刚好构成一个哈密顿回路,不能是几个相交
的环,因为相交环除了起点外交点访问次数大于2(不构成哈密顿回路),
一个连通子图恰好构成一个简单环.现在要求出所有可能
情况的连通子图构成的所有哈密顿回路边权之和的最小值,
如果原图无法通过删边分离出各个哈密顿回路子图,输出NO.
释义:就是问用1个或多个不相交的有向环覆盖无向图中所有点,求这些环的最少边权和.
注意:
1.原无向图存在重边.(mp存图需要记录最小边权)
2.对于u-v这条边,已经构成了哈密顿回路,
先从u到v,再从v到u,每个点都只经过1次,恰好回到u点,u点访问2次.
3.每个回路至少要有2个点.
4.输入无自环,实际有自环也不会影响二分匹配的结果,X集合i点到Y集合i点构成一个匹配,不会死循环.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3435
思路:同HDU 1853,费用流建边无需考虑重边.KM算法若采用邻接矩阵存边,
要考虑重边取最小的.
*/


int cas,n,m,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<1];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

void mcmf(){
    int sum=0,cost=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
    printf("Case %d: ",cas);
    if(sum == n) printf("%d\n",cost);
    else printf("NO\n");
}

void init(){
    cas++;
    cnt=0;
    st=0,ed=n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++){
            addEdge(st,i,1,0);
            addEdge(i+n,ed,1,0);
        }
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v+n,1,w);
            addEdge(v,u+n,1,w);
        }
        mcmf();
    }
    return 0;
}

/*
//摘自博客:https://blog.csdn.net/qq_21057881/article/details/50651715
//ac 2792ms 费用流
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#define INF 1e9
using namespace std;
const int maxn=2500;
int T,cas=1;
struct Edge
{
    int from,to,cap,flow,cost;
    Edge(){}
    Edge(int f,int t,int c,int fl,int co):from(f),to(t),cap(c),flow(fl),cost(co){}
};

struct MCMF
{
    int n,m,s,t;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool inq[maxn];     //是否在队列
    int d[maxn];        //Bellman_ford单源最短路径
    int p[maxn];        //p[i]表从s到i的最小费用路径上的最后一条弧编号
    int a[maxn];        //a[i]表示从s到i的最小残量

    //初始化
    void init(int n,int s,int t)
    {
        this->n=n, this->s=s, this->t=t;
        edges.clear();
        for(int i=0;i<n;++i) G[i].clear();
    }

    //添加一条有向边
    void AddEdge(int from,int to,int cap,int cost)
    {
        edges.push_back(Edge(from,to,cap,0,cost));
        edges.push_back(Edge(to,from,0,0,-cost));
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    //求一次增广路
    bool BellmanFord(int &flow, int &cost)
    {
        for(int i=0;i<n;++i) d[i]=INF;
        memset(inq,0,sizeof(inq));
        d[s]=0, a[s]=INF, inq[s]=true, p[s]=0;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty())
        {
            int u=Q.front(); Q.pop();
            inq[u]=false;
            for(int i=0;i<G[u].size();++i)
            {
                Edge &e=edges[G[u][i]];
                if(e.cap>e.flow && d[e.to]>d[u]+e.cost)
                {
                    d[e.to]= d[u]+e.cost;
                    p[e.to]=G[u][i];
                    a[e.to]= min(a[u],e.cap-e.flow);
                    if(!inq[e.to]){ Q.push(e.to); inq[e.to]=true; }
                }
            }
        }
        if(d[t]==INF) return false;
        flow +=a[t];
        cost +=a[t]*d[t];
        int u=t;
        while(u!=s)
        {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -=a[t];
            u = edges[p[u]].from;
        }
        return true;
    }

    //求出最小费用最大流
    int Min_cost(int num)
    {
        int flow=0,cost=0;
        while(BellmanFord(flow,cost));
        return num==flow?cost:-1;
    }
}mc;

int d[maxn][maxn];

int main()
{
	int n,m;
	scanf("%d",&T);
    while (T--)
	{
        scanf("%d%d",&n,&m);
        mc.init(n*2+2,0,n*2+1);
		memset(d,0,sizeof(d));
		for (int i=1;i<=n;i++)
		{
			mc.AddEdge(0,i,1,0);
			mc.AddEdge(n+i,n*2+1,1,0);
		}
		for (int i = 1;i<=m;i++)
		{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			if (d[u][v] > w || !d[u][v])
			{
				d[u][v]=w;
				d[v][u]=w;
			}
		}
		for (int i = 1;i<=n;i++)
			for (int j = i+1;j<=n;j++)
				if (d[i][j]!=0)
				{
					mc.AddEdge(i,j+n,1,d[i][j]);
                    mc.AddEdge(j,i+n,1,d[i][j]);
				}

		int ans = mc.Min_cost(n);
		if (ans == -1)
			printf("Case %d: NO\n",cas++);
		else
		    printf("Case %d: %d\n",cas++,ans);
	}
}
*/

/*
//ac 1107ms 最优匹配 slack数组松弛优化 dfs匈牙利不考虑实际不存在的边
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],slack[N],d,ans;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(mp[u][v] == -INF || visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

void KM(){
    for(int i=1;i<=n;i++){
        lx[i]=-INF;//初始化为负无穷,因为边权为负值
        ly[i]=0;
        for(int j=1;j<=n;j++){
            if(mp[i][j]!=INF)
                lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            //如果存在某个点找不到Y集合的配对点,则说明这个点度为2,
            //要么是度为1本身不存在回路,要么是存在交叉环度>=3的情况
            if(d == INF) return;
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    //说明存在完美匹配,即能分割出各个哈密顿回路的连通子图
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
}

void init(){
    ans=0;
    cas++;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            mp[i][j]=-INF;//-INF无法memset这样赋值最终结果并不等于-INF,因为每字节并不是0x3f
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//u即可作发出边的点,也可作连入边的点,v点同理
            if(-mp[u][v]>w)//要判断当前已存边边权是否比输入边权大,若大则更新
                mp[u][v]=mp[v][u]=-w;//KM求最大匹配边权和,因此存负值
        }
        KM();
        if(!ans) printf("Case %d: NO\n",cas);
        else printf("Case %d: %d\n",cas,-ans);
    }
    return 0;
}
*/
