#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define M 300100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

/*
题意:n个城市,1为首都,m条道路相连,还有k条火车线路
直接和首都直通,现在问最多可以关闭多少条火车线路,
使得每个城市到首都的最短距离不受到影响.
链接:https://codeforces.ml/problemset/problem/449/B
思路:可以将m条道路和k条火车线路,共同建边,因为每个
城市到首都的最短路,中间边可能会用到火车线路,然后用类似
统计最短路个数的办法统计首都到达每个城市有多少条最短路,
只不过这里感觉可能是为了避免个数太大导致溢出,每次只加1,
实际原先道路网最短路只要存在一条即可,对删除的k条火车线路结果
没有影响,有可能同1城市到达首都的火车线路有多条,距离也有可能相同.
*/

int n,m,k,cnt,head[N],vis[N],a[N],num[N],ans;
ll dis[N],b[N];
struct Node{
    int to,next;
    ll w;
}edge[(M<<1)+N];

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
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(dis[s],s));
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
                num[v]=1;//标准做法是num[v]=num[u] 这样会比实际个数少一些 但不影响答案,直接统计可能会结果溢出
                Q.push(make_pair(-dis[v],v));
            }
            else if(dis[v]==dis[u]+edge[i].w)
                //但这样不影响结果,因为实际只需知道除过k条火车线路,原道路网能提供一条最短路即可
                num[v]++;//标准做法是num[v]+=num[u]
        }
    }
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    for(int i=1;i<=k;i++){
        scanf("%d%lld",&a[i],&b[i]);
        addEdge(1,a[i],b[i]);
    }
    Dijkstra(1);
    for(int i=1;i<=k;i++){
        u=a[i];
        if(b[i]>dis[u])//火车线比最短路大 直接加1
            ans++;
        //若火车线和最短路相等 并且剩余图中包括当前这条火车线仍有2条最短路,因为要保证图中最少还有一条最短路
        else if(b[i] == dis[u] && num[u]>1){
            ans++;
            num[u]--;//剩余最短路个数减一
        }
    }
    printf("%d",ans);
    return 0;
}
