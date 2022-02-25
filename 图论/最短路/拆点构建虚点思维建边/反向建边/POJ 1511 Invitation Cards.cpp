#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

/*
题意:求解1节点到n个节点来回的最短距离和.单向边.
链接:http://poj.org/problem?id=1511
思路:反向建边两次最短路.
*/

int n,m,cnt1,cnt2,head1[N],head2[N],vis[N];
ll dis1[N],dis2[N],ans;
struct Node{
    int to,next;
    ll w;
}edge1[N],edge2[N];

void addEdge1(int from,int to,ll w){
    edge1[cnt1]=(Node){to,head1[from],w};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to,int w){
    edge2[cnt2]=(Node){to,head2[from],w};
    head2[from]=cnt2++;
}

void init(int s,ll *dis){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void Dijkstra(int s,ll *dis,int *head,Node *edge){
    init(s,dis);
    priority_queue<pair<ll,int> >Q;
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
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        ans=cnt1=cnt2=0;
        memset(head1,-1,sizeof(head1));
        memset(head2,-1,sizeof(head2));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge1(u,v,w);
            addEdge2(v,u,w);
        }
        Dijkstra(1,dis1,head1,edge1);
        Dijkstra(1,dis2,head2,edge2);
        for(int i=2;i<=n;i++)
            ans+=dis1[i]+dis2[i];
        printf("%lld\n",ans);
    }
    return 0;
}
