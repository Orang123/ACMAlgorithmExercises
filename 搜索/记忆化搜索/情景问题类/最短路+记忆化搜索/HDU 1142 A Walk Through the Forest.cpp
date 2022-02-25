/*
题意:摘自网上
求从起点1到终点2的满足条件的路径条数，
条件是该条路径上的所有边AB都要满足A到终点的
最短路大于B到终点的最短路。
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1142
思路:可以先求出点2出发的最短路.在搜索从1出发的路径时,
对于多分支的交叉点,公共路径很明显是重叠子问题,所以需要记忆化
搜索.
dp[v]表示2到v合法路径的条数
*/
//ac 78ms 最短路(Dijkstra)+记忆化搜索
//dp[v]表示2到v合法路径的条数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dp[N],mp[N][N],vis[N],dis[N];

void Dijkstra(int s){
    dis[s]=0;
    int mind,u;
    for(int i=1;i<=n;i++){
        mind=INF;
        for(int j=1;j<=n;j++){
            if(!vis[j] && dis[j]<mind){
                mind=dis[j];
                u=j;
            }
        }
        vis[u]=1;
        for(int v=1;v<=n;v++){
            if(dis[v]>dis[u]+mp[u][v])
                dis[v]=dis[u]+mp[u][v];
        }
    }
}

int dfs(int u){
    if(dp[u]!=-1)
        return dp[u];
    if(u == 2)//到达终点返回1
        return dp[u]=1;
    dp[u]=0;
    for(int v=1;v<=n;v++){
        if(mp[u][v] == INF || dis[u]<=dis[v])
            continue;
        dp[u]+=dfs(v);
    }
    return dp[u];
}

int main(){
    int u,v,w;
    while(scanf("%d",&n) && n){
        scanf("%d",&m);
        memset(vis,0,sizeof(vis));
        memset(mp,0x3f,sizeof(mp));
        memset(dis,0x3f,sizeof(dis));
        memset(dp,-1,sizeof(dp));//0也是合法值,因此初始化为-1
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            mp[u][v]=mp[v][u]=w;
        }
        Dijkstra(2);
        printf("%d\n",dfs(1));
    }
    return 0;
}

/*
//ac 31ms 最短路(spfa)+记忆化搜索
//dp[v]表示2到v合法路径的条数
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],dp[N],vis[N],dis[N];
struct Edge{
	int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
	edge[cnt]=(Edge){to,head[from],w};
	head[from]=cnt++;
}

void spfa(int s){
	queue<int> Q;
	dis[s]=0;
	vis[s]=1;
	Q.push(s);
	int u,v;
	while(!Q.empty()){
		u=Q.front();
		Q.pop();
		vis[u]=0;
		for(int i=head[u];i!=-1;i=edge[i].next){
			v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].w){
				dis[v]=dis[u]+edge[i].w;
				if(!vis[v]){
					vis[v]=1;
					Q.push(v);
				}
			}
		}
	}
}

int dfs(int u){
    if(dp[u]!=-1)
        return dp[u];
    if(u == 2)
        return dp[u]=1;
    dp[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
    	int v=edge[i].to;
    	if(dis[u]<=dis[v])
    		continue;
    	dp[u]+=dfs(v);
	}
    return dp[u];
}

int main(){
    int u,v,w;
    while(scanf("%d",&n) && n){
        scanf("%d",&m);
        cnt=0;
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        memset(dis,0x3f,sizeof(dis));
        memset(dp,-1,sizeof(dp));
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        spfa(2);
        printf("%d\n",dfs(1));
    }
    return 0;
}
*/
