#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
//树形dp
/*
题意:一棵树形结构的城市,一个商人要卖一本书,该书在每个城市的价格都不同,商人可以在一座城市买入,
在另一座城市以高价卖出,求商人能赚取的最大差价.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=6201
思路:dp[u][0]代表在u点或其子树节点卖出该书,dp[u][1]代表在u或其子树节点买入该书.
则最大差价ans=max(dp[u][0]+dp[u][1])
*/
int dp[N][2],head[N],val[N],cnt,ans=0;
struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dp[u][0]=val[u];
    dp[u][1]=-val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //如果u结点既不是买入地也不是卖出地,那么dp[u][0]+dp[u][1]一定小于之前的子节点dp[v][0]+dp[v][1]
        dp[u][0]=max(dp[u][0],dp[v][0]-edge[i].w);//选择u节点和之前的子节点中卖的价钱最高的卖再减去所走过的路程u->v这段路程
        dp[u][1]=max(dp[u][1],dp[v][1]-edge[i].w);//选择u节点和之前子节点买的价钱加上所走路程最小的作为买书的城市
    }
    ans=max(ans,dp[u][0]+dp[u][1]);//求取最大差价
}

int main(){
    int T,n,u,v,w;
    scanf("%d",&T);
    while(T--){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        dfs(1,-1);
        printf("%d\n",ans);
    }
    return 0;
}

/*
拆点+最长路(spfa)
因为我们不知道从哪点出发到哪点终止。因此虚拟一个起点，一个终点，
起点连接所有的节点，权值为−v[i]，代表买入的代价。
所有节点再连向终点，权值为v[i]，代表卖出的收益。
每条边的权值置为负，代表走这条路需要花费代价。
跑一次最长路即可。
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF -0x3f3f3f3f
using namespace std;
typedef long long ll;

//ac 577ms  树形dp为499ms
int n,cnt,head[N],vis[N],val[N];
ll dis[N];
struct Node{
    int to,next;
    ll w;
}edge[N<<2];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));
    dis[0]=0;
}

void spfa(int s){
    queue <int>Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]<dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            addEdge(0,i,-val[i]);//0点作为入点,0->i代表在i点买书,边权为负
            addEdge(i,n+1,val[i]);//n+1点作为出点,i->n+1代表在i点卖书,边权为正
        }
        for(int i=1;i<n;i++){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,-w);
            addEdge(v,u,-w);
        }
        spfa(0);
        printf("%lld\n",dis[n+1]);
    }
    return 0;
}

*/


