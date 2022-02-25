#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//spfa做法
/*
题意:求解从1节点出发到达n节点的次短路,注意次短路一定严格大于最短路.
链接:http://poj.org/problem?id=3255
思路:spfa,dis1求解最短路,dis2求解次短路,每次松弛节点时,同时更新最短路和次短路.
分三种情况：
1.若该点最短路+下一条边比到下个点的最短路短，则更新下个点的最短路，同时更新次短路为原最短路
2.若该点次短路+下一条边比到下个点的次短路短，则更新下个点的次短路
3.若该点最短路+下一条边比到下个点的最短路长同时比下个点的次短路短，则更新下个点的次短路
这里之所以要分三种情况,单独if判定是因为spfa入队永远记录的是一个点,而Dijkstra 点和距离是同时入队的,
这个距离本身就包含了最短路和次短路的可能性,因此if else if2个判定就够.
*/

int n,m,cnt,head[N],vis[N];
ll dis1[N],dis2[N];
struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    //dis2[s]次短路不能设置成0,因为次短路是根据和最短路比较得出的,若初始化为0,对于直链则次短路永远都是0,不可能再更新了
    dis1[s]=0;
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
            //情况1 更新最短路
            if(dis1[v]>dis1[u]+edge[i].w){
                dis2[v]=dis1[v];
                dis1[v]=dis1[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
            //情况2 次短路更新次短路 因为有可能到达v点最短路只有一条,那么次短路只能由到达v点较大的次短路更新
            if(dis2[v]>dis2[u]+edge[i].w){
                dis2[v]=dis2[u]+edge[i].w;
                /*
                这里次短路更新后的结果同样也要作为新的路径去更新后面节点的次短路,
                所以如果v点之前已经弹出过队列,还要将其入队.
                因为后面节点的次短路不一定都能通过前面节点的最短路获得更新(对于没有其它分支,
                单独链时最开始第一个次短路是通过前面的最短路更新的),前面的次短路也有可能会
                更新后面节点的次短路.
                */
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
            //情况3 最短路(比当前最短路大,比当前次短路小)更新次短路
            if(dis2[v]>dis1[u]+edge[i].w && dis1[u]+edge[i].w>dis1[v]){
                dis2[v]=dis1[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init(1);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    spfa(1);
    printf("%lld\n",dis2[n]);
    return 0;
}

/*
//Dijkstra 最简洁最易理解做法
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],vis[N][2],dis[N][2];

struct state{
    int v,dis,flag;
    state(int dis=0,int v=0,int flag=0):dis(dis),v(v),flag(flag){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

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
    dis[s][0]=0;
}

int Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(0,s,0));
    int u,v,flag;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,flag=tmp.flag;
        Q.pop();
        if(u == n && flag) return dis[u][flag];
        if(vis[u][flag]) continue;
        vis[u][flag]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v][0]>tmp.dis+edge[i].w){
                if(dis[v][0]!=INF){
                    dis[v][1]=dis[v][0];
                    Q.push(state(dis[v][1],v,1));
                }
                dis[v][0]=tmp.dis+edge[i].w;
                Q.push(state(dis[v][0],v,0));
            }
            else if(dis[v][1]>tmp.dis+edge[i].w){
                dis[v][1]=tmp.dis+edge[i].w;
                Q.push(state(dis[v][1],v,1));
            }
        }
    }
    return -1;
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    printf("%d",Dijkstra(1));
    return 0;
}
*/

/*
//Dijkstra  推荐自己的做法 思路比网上统一思路要更清晰一点 不混淆
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N];
ll dis1[N],dis2[N];
struct Node{
    int to,next;
    ll w;
}edge[M<<1];
struct state{
    ll dis;
    int v;
    state(ll dis=0,int v=0):dis(dis),v(v){}
    bool operator <(const state &x)const{
        return dis>x.dis;
    }
};

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    //dis2[s]次短路不能设置成0,因为次短路是根据和最短路比较得出的,若初始化为0,对于直链则次短路永远都是0,不可能再更新了
    dis1[s]=0;
}

void Dijkstra(int s){
    priority_queue <state>Q;
    Q.push(state(0,s));
    int u,v;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v;
        Q.pop();
        //当到达u点的次短路已经不可能更小时,就不必再去松弛了
        //这里有可能本身不存在次短路,会刻意往回走重复的边松弛出新的次短路来,刻意构造出来的
        if(tmp.dis>dis2[u]) continue;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //这里tmp.dis+edge[i].w代表堆中维护的当前较小的路径值,有可能是之前节点最短路也有可能是次短路
            //若tmp.dis+edge[i].w是最短路,则在更新最短路的之前,会先将之前的最短路更新为新的次短路,也可能直接用来更新次短路
            //若tmp.dis+edge[i].w是次短路,则只能更新后续节点的次短路
            //情况1 更新最短路
            if(dis1[v]>tmp.dis+edge[i].w){
                if(dis1[v]!=INF){
                    dis2[v]=dis1[v];//先将之前的最短路更新为新的次短路,再更新当前新的最短路
                    Q.push(state(dis2[v],v));
                }
                dis1[v]=tmp.dis+edge[i].w;
                Q.push(state(dis1[v],v));
            }
            //情况2 次短路或最短路更新次短路
            //这个tmp.dis+edge[i].w有可能本身就是次短路,也有可能本身就是最短路但是比dis1[v]大,但却比dis2[v]小
            else if(dis2[v]>tmp.dis+edge[i].w){
                dis2[v]=tmp.dis+edge[i].w;
                Q.push(state(dis2[v],v));//将次短路压入堆中,可能更新后面节点的次短路
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init(1);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    Dijkstra(1);
    printf("%lld\n",dis2[n]);
    return 0;
}
*/

/*
//Dijkstra求解次短路 网上统一版本 更新次短路那里很容易混淆不推荐
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N];
ll dis1[N],dis2[N];
struct Node{
    int to,next;
    ll w;
}edge[M<<1];
struct state{
    ll dis;
    int v;
    state(ll dis=0,int v=0):dis(dis),v(v){}
    bool operator <(const state &x)const{
        return dis>x.dis;
    }
};

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    dis1[s]=0;
}

void Dijkstra(int s){
    priority_queue <state>Q;
    Q.push(state(0,s));
    int u,v;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v;
        Q.pop();
        //当到达u点的次短路已经不可能更小时,就不必再去松弛了
        //这里有可能本身不存在次短路,会刻意往回走重复的边松弛出新的次短路来,刻意构造出来的
        //对于tmp.dis=dis2[u]的情况 eg:1->2 2往回走刚更新1的次短路,这时tmp.dis==dis2[1]还需要用这个次短路去更新2的次短路
        if(tmp.dis>dis2[u]) continue;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //这里d代表堆中维护的当前较小的路径值,有可能是之前节点最短路也有可能是次短路
            //若d是最短路,则既能更新最短路,也能更新次短路
            //若d是次短路,则只能更新后续节点的次短路
            ll d=tmp.dis+edge[i].w;
            //情况1 更新最短路 同时交换d与原先最短路
            if(dis1[v]>d){
                swap(dis1[v],d);
                Q.push(state(dis1[v],v));
            }
            //情况2 次短路或最短路更新次短路
            //这个d有可能本身就是次短路,也有可能是原先的被替换的最短路,也有可能本身就是最短路但是没有dis1[v]小
            if(dis2[v]>d && d>dis1[v]){
                dis2[v]=d;
                Q.push(state(dis2[v],v));//将次短路压入堆中,可能更新后面节点的次短路
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init(1);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    Dijkstra(1);
    printf("%lld\n",dis2[n]);
    return 0;
}
*/

/*
暴力解法 枚举路径的可能组成情况 效率要低一些 跑两遍最短路(一遍1开始,一遍n开始)
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N];
ll dis1[N],dis2[N],ans=INF;
struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    dis1[1]=0;
    dis2[n]=0;
}

void spfa(int s,ll *dis){
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

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    spfa(1,dis1);//计算1->v的最短路dis1
    spfa(n,dis2);//计算n->v的最短路dis2
    for(int u=1;u<=n;u++){//枚举每个点作为中间分割边的起点,实际就是枚举其余路径 选择比最短路大比其余路径尽可能小的值
        //也不能只枚举dis1[u]+dis2[u],不枚举分割边,这样对于1->2这样的路径次短路就不存在了.
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;//枚举另一个分割点
            //1->n的路径组成情况 dis1[1->u]+d[u->v]+dis2[v->n]
            //对于1->2这种单链的情况,当u=2时 有2->1这条反向边的存在,所以sum=dis1[1->2]+d[2->1]+dis2[2->1]=3,刚好是次短路长度为3，最短路是1->2长度为1
            ll sum=dis1[u]+edge[i].w+dis2[v];
            if(sum>dis1[n] && sum<ans)//只要比最短路小,比之前记录的次短路大,就更新
                ans=sum;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
*/

/*
A*搜索解法 https://blog.csdn.net/algzjh/article/details/77542212 还没看
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
typedef long long LL;
const LL INF=1e18;
const int MAXN=1e5+5;
int head[MAXN],head1[MAXN];
LL dis[MAXN];
bool vis[MAXN];
int n,m,tot,st,en,k;

struct Edge
{
    int u,v,nxt,nxt1;
    LL c;
    Edge(){}
    Edge(int _u,int _v,LL _c):u(_u),v(_v),c(_c){}
}e[MAXN*2];

struct qnode
{
    int v;
    LL c;
    qnode(){}
    qnode(int _v,LL _c):v(_v),c(_c){}
    bool operator < (const qnode& rhs) const
    {
        return c+dis[v]>rhs.c+dis[rhs.v];
    }
};

void addedge(int u,int v,LL c)
{
    e[tot]=Edge(u,v,c);
    e[tot].nxt=head[u];head[u]=tot;
    e[tot].nxt1=head1[v];head1[v]=tot++;
}

void dij(int src)
{
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) dis[i]=INF;
    dis[src]=0;
    priority_queue<qnode> que;
    que.push(qnode(src,0));
    while(!que.empty())
    {
        qnode pre=que.top(); que.pop();
        if(vis[pre.v]) continue;
        vis[pre.v]=true;
        for(int i=head1[pre.v];i!=-1;i=e[i].nxt1)
        {
            if(dis[e[i].u]>dis[pre.v]+e[i].c)
            {
                dis[e[i].u]=dis[pre.v]+e[i].c;
                que.push(qnode(e[i].u,0));
            }
        }
    }
}

LL a_star(int src)
{
    priority_queue<qnode> que;
    que.push(qnode(src,0));
    k--;
    while(!que.empty())
    {
        qnode pre=que.top();que.pop();
        if(pre.v==en)
        {
            if(k) k--;
            else return pre.c;
        }
        for(int i=head[pre.v];i!=-1;i=e[i].nxt)
            que.push(qnode(e[i].v,pre.c+e[i].c));
    }
    return -1;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        memset(head1,-1,sizeof(head1));
        tot=0;
        for(int i=0;i<m;i++)
        {
            int u,v;LL c;
            scanf("%d%d%lld",&u,&v,&c);
            addedge(u,v,c);
            addedge(v,u,c);
        }
        st=1,en=n;k=2;
        dij(en);
        if(st==en) k++;
        printf("%lld\n",a_star(st));
    }
    return 0;
}
*/

