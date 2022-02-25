#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 500
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//ac 282ms 拆点+floyd+二分枚举最大时间+最大流验证
//同POJ 2112
//用二分图多重匹配,多对多拆点,会拆出很多一个一个的点,很麻烦
/*
题意摘自网上
题意:有n块地,每块地初始有a头牛和一个能容纳b头牛的牛棚,
有m条带权边,表示走过这条边需要的时间,问最少需要多少时间
能让所有的牛在进入棚子(n头牛同时行动).
链接:http://poj.org/problem?id=2391
思路:最少需要多少时间,就是实际移动所需时间最长的牛花费的时间,
现在要求这个最大时间最小化,显然最大值最小化问题二分枚举最大时间,
最大流验证,同POJ 2112,不同的是这里每个点初始有牛,还有一个能容纳牛的
最大数量的牛棚,所以可将点i拆点为,i和i+n,i表示初始时牛的个数,i+n表示
每个点牛棚能容纳的牛的上限.源点0,汇点2*n+1,源点向每个点i建边,容量为
初始牛的个数,每个点i+n向汇点建容量为容纳牛最大上限的边,再建i->j+n,容量
为初始i点牛数量,表示i点的牛要移动到j点的牛棚,这样不断二分最大时间,跑最大
流验证是否最大流等于所有初始牛的数量,标明是否所有牛都移动到了牛棚.

注意:此题如果用匈牙利多重匹配来解,因为每个点初始也有多只牛,是一个多对多的问题,
如果用拆点,需要拆成一个一个的点(代表一个初始的牛),这样做法很繁琐.
*/
int n,m,st,ed,cnt,head[N],dis[N],vis[N],a[N],b[N],sum;
ll mp[N][N];
struct Edge{
    int to,next,cf;
}edge[N*N];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(ll mid){
    int ans=0;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){//这个点本身初始奶牛,也可以到本身这个点的牛棚 即mp[i][i]=0也是可以的
        addEdge(st,i,a[i]);
        addEdge(i+n,ed,b[i]);
        for(int j=1;j<=n;j++){
            if(mp[i][j] != INF && mp[i][j]<=mid)
                addEdge(i,j+n,a[i]);
        }
    }
    while(bfs(st))
        ans+=dfs(st,0x3f3f3f3f);
    return ans == sum;
}

void floyd(){
    for(int t=1;t<=n;t++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j]>mp[i][t]+mp[t][j])
                    mp[i][j]=mp[i][t]+mp[t][j];
            }
        }
    }
}

void init(){
    st=0,ed=n*2+1;
    sum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            mp[i][j]=i==j?0:INF;
    }
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
        sum+=a[i];
    }
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        mp[u][v]=mp[v][u]=min(mp[u][v],w);//双向边
    }
    floyd();
    ll l=0,r=0,mid;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
            r=max(r,mp[i][j]);//求出最大距离的初始上界
    }
    if(!max_flow(r)){//若最大距离都不能使所有奶牛都移动到牛棚,则无解
        printf("-1");
        return 0;
    }
    while(l<r){
        mid=(l+r)/2;
        if(max_flow(mid))
            r=mid;
        else
            l=mid+1;
    }
    printf("%lld",r);
    return 0;
}
