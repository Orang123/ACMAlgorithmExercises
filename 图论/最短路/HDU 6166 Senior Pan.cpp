#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//Dijkstra 3338ms
/*
题意:n个节点的有向连通图,m条有向边,现在选出k个点,求出这k个点对间的
最短距离.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=6166
思路:
已知求解两个集合间的最短距离做法是,将其中一个集合所有元素入堆,并且设置各个点的dis为0,
这样跑一边最短路,比较另一个集合所有点的dis,求出最小值就是两集合间的最短距离.
现在考虑将这k个点分为两个集合,尝试用两个集合间的最短距离来求出这k个点间的最短距离.
那么问题是如何将这k个点分割成两个集合,使得任意两点都可以分别被分割开,使得任意两点间
距离都可以被考虑进去,这里可以考虑根据每个点编号的二进制位,根据二进制每一位是否有无,将
k个点分割成两个集合,这样做的合理性在于因为任意两个十进制数其二进制位至少有一位是不同的,
所以枚举每一位二进制的有无,对于任意两点来说,他们都能保证被分割到不同的集合.
这样我们枚举二进制位因为N<=10^5,可以枚举到第16位二进制位,因为2^17=130000,所以枚举到第16位
即可.

2019 ICPC 南昌 Fire-Fighting Hero
这题是之前做过求解k个点到其余所有点间的最大距离,那个做法是将这k个点用一个超级源点连接,边权为0,从超级源点出发,
跑一遍最短路,比较各个点的dis,求出最大值即可,可这个做法只能用来求解k个点到其余所有点的最小距离,无法求解
指定的k个点间的最小距离,因为这k个点的dis永远为0,要去求解指定k个点的最短路还是需要将k个点划分成2个集合的.
*/

int n,m,cnt,k,head[N],vis[N],a[N],b[N],t;
ll dis[N];
priority_queue<pair<ll,int> >Q;

struct Node{
    int to,next;
    ll w;
}edge[N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    t=0;
    memset(vis,0,sizeof(vis));
    memset(b,0,sizeof(b));
    memset(dis,0x3f,sizeof(dis));
    while(!Q.empty()) Q.pop();
}

ll Dijkstra(){
    int u,v,num=0;
    ll ans=INF;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        if(b[u]){
            num++;
            ans=min(ans,dis[u]);
            if(num == t) return ans;
        }
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return ans;
}

int main(){
    int T,u,v,cas=0;
    ll w,ans;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        ans=INF;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<=16;i++){//枚举二进制位的每一位,当2^i>n时,只能被分割成一个集合,但这不影响问题的求解,ans返回的值是INF
            init();
            for(int j=1;j<=k;j++){
                if(a[j] & (1<<i)){//若a[j]点编号二进制位第i+1位是1,则将这样的点都初试化到一个集合里并入堆
                    dis[a[j]]=0;//设置其初试距离为0,方便更新到另一个点的距离
                    Q.push(make_pair(0,a[j]));
                }
                else{//若a[j]点编号二进制位第i+1位不是1,则将这样的点都作为目标点放入另一个集合中
                    b[a[j]]=1;
                    t++;
                }
            }
            ans=min(ans,Dijkstra());//求解从集合1到集合2的所有点对的最短距离
            init();
            for(int j=1;j<=k;j++){
                if(a[j] & (1<<i)){
                    b[a[j]]=1;
                    t++;
                }
                else{
                    dis[a[j]]=0;
                    Q.push(make_pair(0,a[j]));
                }
            }
            ans=min(ans,Dijkstra());//因为是单向边,所以再求解一次集合2到集合1的所有点对的最短距离,综合比较求出k个点间的最短距离
        }
        printf("Case #%d: %lld\n",cas,ans);
    }
    return 0;
}

/*
//spfa 2558ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,k,head[N],vis[N],a[N],b[N];
ll dis[N];
queue<int> Q;

struct Node{
    int to,next;
    ll w;
}edge[N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    memset(vis,0,sizeof(vis));
    memset(b,0,sizeof(b));
    memset(dis,0x3f,sizeof(dis));
}

ll spfa(){
    int u,v;
    ll ans=INF;
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
    for(int i=1;i<=k;i++){
        if(b[a[i]])
            ans=min(ans,dis[a[i]]);
    }
    return ans;
}

int main(){
    int T,u,v,cas=0;
    ll w,ans;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        ans=INF;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<=16;i++){
            init();
            for(int j=1;j<=k;j++){
                if(a[j] & (1<<i)){
                    dis[a[j]]=0;
                    vis[a[j]]=1;
                    Q.push(a[j]);
                }
                else
                    b[a[j]]=1;
            }
            ans=min(ans,spfa());
            init();
            for(int j=1;j<=k;j++){
                if(a[j] & (1<<i))
                    b[a[j]]=1;
                else{
                    dis[a[j]]=0;
                    vis[a[j]]=1;
                    Q.push(a[j]);
                }
            }
            ans=min(ans,spfa());
        }
        printf("Case #%d: %lld\n",cas,ans);
    }
    return 0;
}
*/

