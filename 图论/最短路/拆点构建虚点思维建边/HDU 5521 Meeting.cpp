#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000100
#define INF 1e15//0x3f/7f 应该不行,因为w权和可能比0x3f/7f还大
using namespace std;
typedef long long ll;

/*
题意:n个点的无向连通图,有一些点的集合,每个集合中的任意两点都连通
且距离都相同,有2个人,一个人在1点，一个人在n点,现在问相约在哪些点,
需要走的距离最短,并输出最短距离(一个人先走到约定点,会停下等另一个人到达).
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5521
思路:关键是如何建边,如果集合内两两之间都建边,因为n<=10^5,基本会MLE,时间也会TLE.
因此可以在集合i外引入一个虚点i+n,将集合中的每个点和i+n建一条长为w的双向边,这样
在最终的求解结果将ans最短距离除以2即是答案.
*/

ll n,m,cnt,dis1[N<<1],dis2[N<<1],vis[N<<1],ans;//数组大小也可以设成题目要求的N+M
int head[N<<1];
struct Node{
    int to,next;
    ll w;
}edge[N<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s,ll *dis){
    for(int i=1;i<N*2;i++)
        dis[i]=(i==s?0:INF);
}

void Dijkstra(int s,ll *dis){
    priority_queue<pair<int,int> > Q;
    init(s,dis);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,t,cas=0;
    ll w;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        ans=INF;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        scanf("%lld%lld",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%lld%d",&w,&t);
            while(t--){
                scanf("%d",&v);
                addEdge(v,i+n,w);//引入虚点i+n,和集合中每个点建边长度为w,双向边
                addEdge(i+n,v,w);
            }
        }
        Dijkstra(1,dis1);
        memset(vis,0,sizeof(vis));
        Dijkstra(n,dis2);
        for(int i=1;i<=n;i++)
            ans=min(ans,max(dis1[i],dis2[i]));
        if(ans == INF){
            printf("Case #%d: Evil John\n",cas);
            continue;
        }
        int flag=0;
        if(ans!=INF){
            printf("Case #%d: %lld\n",cas,ans/2);
            for(int i=1;i<=n;i++){
                if(max(dis1[i],dis2[i]) == ans && !flag){
                    printf("%d",i);
                    flag=1;
                }
                else if(max(dis1[i],dis2[i]) == ans && flag)
                    printf(" %d",i);
            }
            printf("\n");
        }
    }
    return 0;
}

/*
也可以在引入虚点建双向边时,一边长度为0,一边长度为w,这样最终的最短距离ans直接输出即可
两边权各为w/2,若w不为偶数 会出错.
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000100
#define INF 0x7f7f7f7f//0x3f 应该不行,因为w权和可能比0x3f还大
using namespace std;
typedef long long ll;

ll n,m,cnt,dis1[N<<1],dis2[N<<1],vis[N<<1],ans;
int head[N<<1];
struct Node{
    int to,next;
    ll w;
}edge[N<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s,ll *dis){
    for(int i=1;i<N*2;i++)
        dis[i]=(i==s?0:INF);
}

void Dijkstra(int s,ll *dis){
    priority_queue<pair<int,int> > Q;
    init(s,dis);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,t,cas=0;
    ll w;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        ans=INF;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        scanf("%lld%lld",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%lld%d",&w,&t);
            while(t--){
                scanf("%d",&v);
                addEdge(v,i+n,0);
                addEdge(i+n,v,w);
            }
        }
        Dijkstra(1,dis1);
        memset(vis,0,sizeof(vis));
        Dijkstra(n,dis2);
        for(int i=1;i<=n;i++)
            ans=min(ans,max(dis1[i],dis2[i]));
        if(ans == INF){
            printf("Case #%d: Evil John\n",cas);
            continue;
        }
        int flag=0;
        if(ans!=INF){
            printf("Case #%d: %lld\n",cas,ans);
            for(int i=1;i<=n;i++){
                if(max(dis1[i],dis2[i]) == ans && !flag){
                    printf("%d",i);
                    flag=1;
                }
                else if(max(dis1[i],dis2[i]) == ans && flag)
                    printf(" %d",i);
            }
            printf("\n");
        }
    }
    return 0;
}

*/

