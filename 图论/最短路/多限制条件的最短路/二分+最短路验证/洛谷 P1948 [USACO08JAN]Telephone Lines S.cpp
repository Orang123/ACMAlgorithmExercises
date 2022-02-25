//最大值最小化
//思考：为什么可以这样概括呢？因为题意中的答案要最小，我们贪心肯定要使k次免费的资格用完，
//那么最划算的方案肯定是拿最长的k条路使之免费，然后付第k+1长路的长度的钱。。。这样的贪心思路显然是正确的。

//思路：我们首先二分第k+1长的路的长度(即答案)，边界值l显然是0、r是1000000(题目中说边最长为1000000)，
//然后关键是如何判断正确性。我们考虑简化问题，对于长度小于二分出的答案的线段，因为不需要付价钱，
//所以可以将其权值看作是0;同理，大于二分的值的路径，我们将长度看作1(意味着我需要使用1次免费的资格)。
//so，我们跑一遍spfa，看到了n点的最短路的长度，如果大于k，则不行，缩小r范围继续二分;如果小于，则有可能更小，缩小l范围继续二分。
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
/*
题意:n个点,m条权值为w的双向边,现在要从1点到达n点,
有k次免费通过边的机会,求1到达n点所有路径中边权最大边的最小值.
链接:https://www.luogu.com.cn/problem/P1948
思路:二分+最短路
*/

int n,m,k,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s,int cost){
    priority_queue<pair<int,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v,w;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].w>cost) w=1;
            else w=0;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return dis[n]<=k;
}

int main(){
    int u,v,w,l=0,r=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        r=max(r,w);
    }
    while(l<=r){
        int mid=(l+r)/2;
        if(Dijkstra(1,mid)) r=mid-1;//若是最小值最大化 这里是l=mid+1
        else l=mid+1;//若是最小值最大化 这里是r=mid-1
    }
    if(dis[n]!=INF) printf("%d",l);//若是最小值最大化 这里是r
    else printf("-1\n");
    return 0;
}
/*
//最小值最大化
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,k,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s,int cost){
    priority_queue<pair<int,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v,w;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].w>cost) w=1;
            else w=0;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return dis[n]<=k;
}

int main(){
    int u,v,w,l=0,r=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        r=max(r,w);
    }
    while(l<=r){
        int mid=(l+r)/2;
        if(Dijkstra(1,mid)) l=mid+1;
        else r=mid-1;
    }
    if(dis[n]!=INF) printf("%d",r);
    else printf("-1\n");
    return 0;
}
*/

/*
//分层图最短路
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,k,cnt,head[N*1000],vis[N*1000];
ll dis[N*1000];

struct Node{
    int to,next;
    ll w;
}edge[(M*2*1000)<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //当前路径中边的最大值若比之前到达v点路径中的最大值小就松弛入队
            if(dis[v]>max(dis[u],edge[i].w)){
                dis[v]=max(dis[u],edge[i].w);
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int u,v;
    ll w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        for(int i=0;i<=k;i++){
            addEdge(u+n*i,v+n*i,w);
            addEdge(v+n*i,u+n*i,w);
            if(i){
                addEdge(u+(i-1)*n,v+i*n,0);
                addEdge(v+(i-1)*n,u+i*n,0);
            }
        }
    }
    Dijkstra(1);
    for(int i=0;i<=k;i++)
        ans=min(ans,dis[n+n*i]);
    if(ans!=INF) printf("%lld",ans);
    else printf("-1");
    return 0;
}
*/
