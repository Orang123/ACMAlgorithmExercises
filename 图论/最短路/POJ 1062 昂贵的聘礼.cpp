#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
//此题wa  不明白原因
/*
题意:http://poj.org/problem?id=1062  中文题意
链接:http://poj.org/problem?id=1062
思路:每个物品的本身的价格w,可以通过超级源点(0)到这个物品编号建
一条权值为w的边mp[0][i]=w,一个物品t兑换另一个物品的需要的价钱v,
可通过构建mp[t][i]=v的边.但需注意兑换时的等级要求,必须先枚举某个物品的
等级最低,然后把等级低于它的和等级比他高之差超过m的滤除掉,再开始最短路,
dis[1]比较最小值即为答案.
*/

int n,m,cnt,mp[N][N],vis[N],dis[N],rnk[N];

void init(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int v=1;v<=n;v++){
            if(!mp[u][v]) continue;
            if(dis[v]>dis[u]+mp[u][v]){
                dis[v]=dis[u]+mp[u][v];
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return dis[1];
}

int main(){
    int w,ans=INF,num,t,v;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w,&rnk[i],&num);
        mp[0][i]=w;
        while(num--){
            scanf("%d%d",&t,&v);
            mp[t][i]=v;
        }
    }
    for(int i=1;i<=n;i++){
        vis[0]=0;
        for(int j=1;j<=n;j++){
            if(rnk[j]>=rnk[i] && rnk[j]<=rnk[i]+m)
                vis[j]=0;
            else
                vis[j]=1;
        }
        ans=min(ans,Dijkstra(0));
    }
    printf("%d",ans);
    return 0;
}

/*
ac
//https://blog.csdn.net/just_sort/article/details/49591481
//此题的关键在于等级限制的处理，最好的办法是采用枚举，即假设酋长等级为5，等级限制为2，那么需要枚举等级从3~5,4~6,5~7
//然后就是dij了，至于为什么要用dij，看个人喜好，毕竟这里等级处理要对vis数组进行标记
//处理了等级问题，就可以枚举等级数组，n倍dij跑完本题了，nlogn0ms搞定
//以下为具体代码
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define inf 0x3fffffff
int maze[110][110];
int dis[110],degree[110],val[110],vis[110];
int m,n;
void init()
{
    memset(dis,inf,sizeof(dis));
    for(int i=1;i<=n;i++)
       for(int j=1;j<=n;j++)
          maze[i][j]=inf;
}

int dij()
{
    for(int i=1;i<=n;i++)
        dis[i]=val[i];
    for(int i=1;i<=n;i++)
    {
        int minn=inf,mark=inf;
        for(int j=1;j<=n;j++)
        {
            if(!vis[j]&&dis[j]<minn)
            {
                minn=dis[j];
                mark=j;
            }
        }
        if(minn==inf)break;
        vis[mark]=true;
        for(int j=1;j<=n;j++)
        {
            if(!vis[j]&&dis[j]>dis[mark]+maze[mark][j])
            {
                dis[j]=dis[mark]+maze[mark][j];
            }
        }
    }
    return dis[1];
}
int main()
{
    while(~scanf("%d%d",&m,&n))
    {
        init();
        int x,a,b,tmp;
        int ans=inf;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&val[i],&degree[i],&x);
            while(x--)
            {
                scanf("%d%d",&a,&b);
                maze[a][i]=b;
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(degree[j]>=degree[i]&&degree[j]<=degree[i]+m)
                {
                    vis[j]=false;
                }
                else
                {
                    vis[j]=true;
                }
            }
            tmp=dij();
            ans=min(ans,tmp);
        }
        cout<<ans<<endl;
    }
    return 0;
}

*/
/*
ac
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
//https://blog.csdn.net/SongBai1997/article/details/83216252
using namespace std;

const int N=105;
const int INF=0x3f3f3f3f;
int dist[N];
int rank[N];//每个物品的等级
int g[N][N];
bool vis[N];

struct Node{
	int u,w;
	//Node(){}
	Node(int u,int w):u(u),w(w){}
	bool operator<(const Node &a)const
	{
		return w>a.w;
	}
};

int n,m;
void dijkstra(int l,int h)//只考虑结点等级在[l,h]中的结点
{
	memset(dist,INF,sizeof(dist));
	memset(vis,false,sizeof(vis));
	dist[0]=0;
	priority_queue<Node>q;
	q.push(Node(0,0));
	while(!q.empty()){
		Node f=q.top();
		q.pop();
		int u=f.u;
		if(!vis[u]){
			vis[u]=true;
			for(int i=1;i<=n;i++)
			  if(!vis[i]&&g[u][i]!=INF&&l<=rank[i]&&rank[i]<=h&&dist[i]>dist[u]+g[u][i]){
			  		dist[i]=dist[u]+g[u][i];
			  		q.push(Node(i,dist[i]));
			  }
		}
	}
}

int main()
{
	scanf("%d%d",&m,&n);
	int p,l,x,t,v;
	memset(g,INF,sizeof(g));
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&p,&l,&x);
		rank[i]=l;
		g[0][i]=p;//直接花钱买
		while(x--){
			scanf("%d%d",&t,&v);
			g[t][i]=v;
		}
	}
	int ans=INF;
	for(int i=rank[1]-m;i<=rank[1];i++){
	    dijkstra(i,i+m);
		ans=min(ans,dist[1]);
	}
	printf("%d\n",ans);
	return 0;
}
*/


