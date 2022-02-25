#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//最大值最小化
/*
题意:n个城市,m条双向公路,每条道路都需要消耗一定血量,
每个城市经过时,都需要付一定费用,你有一个初始血量,求从
1到n的路径所付出的费用最大值里的最小值是多少.
链接:https://www.luogu.com.cn/problem/P1462
思路:二分费用,最短路验证在初始血量允许下是否能到达n点.
*/

int n,m,cnt,head[N],vis[N],a[N],c[N];
ll dis[N],b;

struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s,int cost){
    init(s);
    priority_queue<pair<ll,int> > Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        if(u == n) break;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(a[v]>cost) continue;//如果比二分的费用高则不行
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    if(dis[n]<=b) return 1;
    else return 0;
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%lld",&n,&m,&b);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        c[i]=a[i];
    }
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    if(!Dijkstra(1,INF)){
        printf("AFK\n");
        return 0;
    }
    sort(c+1,c+n+1);//二分每个城市费用,城市费用得是有序的
    int l=1,r=n;
    while(l<=r){
        int mid=(l+r)/2;
        //说明能到达n点,说明二分的费用偏高,再变小点
        //Dijk返回1,到底增大还是减小,看最值的第二个因此是要求最大还是最小
        //这里最大值最小化,第二个最是最小化,所以缩小右边界,变小,反之增大左边界
        if(Dijkstra(1,c[mid])) r=mid-1;//若是最小值最大化这里是l=mid+1
        //说明不能到达n点,说明二分的费用偏小,再变大点
        else l=mid+1;//若是最小值最大化这里是r=mid-1
    }
    printf("%d",c[l]);
    return 0;
}
/*
//与之对应的最小值最大化
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N],a[N],c[N];
ll dis[N],b;

struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s,int cost){
    init(s);
    priority_queue<pair<ll,int> > Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        if(u == n) break;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(a[v]>cost) continue;//如果比二分的费用高则不行
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    if(dis[n]<=b) return 1;
    else return 0;
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%lld",&n,&m,&b);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        c[i]=a[i];
    }
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    if(!Dijkstra(1,INF)){
        printf("AFK\n");
        return 0;
    }
    sort(c+1,c+n+1);//二分每个城市费用,城市费用得是有序的
    int l=1,r=n;
    while(l<=r){
        int mid=(l+r)/2;
        //说明能到达n点,说明二分的费用偏高,再变大点
        if(Dijkstra(1,c[mid])) l=mid+1;
        //说明不能到达n点,说明二分的费用偏小,再变小点
        else r=mid-1;
    }
    printf("%d",c[l]);
    return 0;
}
*/
