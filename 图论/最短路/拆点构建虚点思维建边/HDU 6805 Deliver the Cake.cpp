#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 200100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//这个代码 莫名wa掉不知什么原因
/*
题意:n个村庄,村庄之间存在双向道路,现在要将一块蛋糕从s点送到t点,
并且村庄分为3种,第一种村庄左村只能左手托着蛋糕,
第二种村庄右村只能右手托着蛋糕,第三种村庄中村既能左手托着也能
右手托着,已知把一块蛋糕从左手放到右手或从右手放到左手,
需要花费x,现在问把蛋糕从s点提到t点需要的最少花费.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=6805
思路:对于左手村和右手村之间的道路的权值是清楚的就是道路权值加上还手的代价,
可对于中村和左中右村的是否需要换手是不清楚的,因为不清楚中村人托蛋糕的状态到底
是左手还是右手,所以对于中村的情况就需要拆点,拆为2个状态,左和右,这样中村就拆为2个点,
对于中村x,x表示要求左手托蛋糕,x+n表示要求右手托蛋糕.
然后针对起点和终点有可能也为中村,那么还可以设置一个超级源点(0)和汇点(2n+1)
将起点和终点的所有情况统筹进去,最后跑最短路求取dis[2n+1]即可.
*/

int n,m,cnt,head[N<<1],vis[N<<1];
ll dis[N<<1];
char str[N];

struct Node{
    int to,next;
    ll w;
}edge[M<<3];

void addEdge1(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

void addEdge2(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    dis[0]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> > Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(u == 2*n+1) return;
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
    int T,u,v,s,t;
    ll w,x;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d%lld",&n,&m,&s,&t,&x);
        init();
        scanf("%s",str+1);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            //分析两个端点 左右手的情况,来考虑是否在边权的基础上加入换手的代价x
            if(str[u] == 'L'){
                if(str[v] == 'L')
                    addEdge1(u,v,w);//u->v 无需换手 只有边权
                else if(str[v] == 'R')
                    addEdge1(u,v,w+x);//u->v 到达v点后要从左手换到右手 代价为w+x
                else{//对于中村 枚举2种可能性,左和右,这两种代价会对后面点的连边产生影响,不同的状态最终的最短路可能不同
                    addEdge1(u,v,w);//左->左 代价w
                    addEdge1(u,v+n,w+x);//左->右 代价w+x
                }
            }
            else if(str[u] == 'R'){
                if(str[v] == 'L')
                    addEdge1(u,v,w+x);
                else if(str[v] == 'R')
                    addEdge1(u,v,w);
                else{
                    addEdge1(u,v,w+x);
                    addEdge1(u,v+n,w);
                }
            }
            else{//对于u点为中村,那就需要考虑 u点 当前的2种状态 左和右去连接v点
                if(str[v] == 'L'){
                    addEdge1(u,v,w);//左左 w
                    addEdge1(u+n,v,w+x);//左右 w+x
                }
                if(str[v] == 'R'){
                    addEdge1(u,v,w+x);
                    addEdge1(u+n,v,w);
                }
                else{//中村->中村 2x2 4种可能连接
                    addEdge1(u,v,w);
                    addEdge1(u,v+n,w+x);
                    addEdge1(u+n,v,w+x);
                    addEdge1(u+n,v+n,w);
                }
            }
        }
        //超级源点连向起点
        if(str[s] == 'L' || str[s] == 'R')//起点不是中村 只有一种状态
            addEdge2(0,s,0);
        else{//起点是中村 有2种状态
            addEdge2(0,s,0);
            addEdge2(0,s+n,0);
        }

        if(str[t] == 'L' || str[t] == 'R')
            addEdge2(t,2*n+1,0);
        else{
            addEdge2(t,2*n+1,0);
            addEdge2(t+n,2*n+1,0);
        }
        Dijkstra(0);
        printf("%lld\n",dis[2*n+1]);
    }
    return 0;
}

/*
暴力建边已ac
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 200100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N<<1],vis[N<<1],state[N<<1];
ll dis[N<<1],x;
char str[N];

struct Node{
    int to,next;
    ll w;
}edge[M<<4];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

void Dijkstra(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=2*n;i++)
        dis[i]=INF;
    priority_queue<pair<ll,int> > Q;
    dis[s]=0;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            ll ok=state[u]==state[v]?0:1;//状态不一致 说明左右手不一致,则要加上换手的代价
            if(dis[v]>dis[u]+edge[i].w+ok*x){
                dis[v]=dis[u]+edge[i].w+ok*x;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,s,t;
    ll w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d%lld",&n,&m,&s,&t,&x);
        init();
        scanf("%s",str+1);
        for(int i=1;i<=n;i++){
            if(str[i] == 'L') state[i]=0,state[i+n]=0;
            else if(str[i] == 'R') state[i]=state[i+n]=1;
            else state[i]=0,state[i+n]=1;
        }
        //这种做法不区分每个点是不是中村,都统一按照2个状态处理 所以每条边都对应4个状态组合
        //实际对于不是中村的节点,这不会对问题的求解有影响,可能会影响一点时间效率,但答案不变.
        //对于只能左手的点,自然两个点的state都是0,若v是右手则这种组合显示不是较优的,但总存在较的组合比曾更优
        while(m--){//暴力建边
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(u,v+n,w);
            addEdge(u+n,v,w);
            addEdge(u+n,v+n,w);
        }
        if(str[s] == 'L' || str[s] == 'R'){//若起点只有一种状态 则跑一边s出发的最短路即可
            Dijkstra(s);
            printf("%lld\n",min(dis[t],dis[t+n]));
        }
        else{//若起点是中村,则跑两次 s,s+n的最短路取最小值,终点的情况 不去管具体它是否是中村 都在dis[t] dis[t+n]中取较小值即可结果是正确的
            ll ans;
            Dijkstra(s);
            ans=min(dis[t],dis[t+n]);
            Dijkstra(s+n);
            ans=min(ans,min(dis[t],dis[t+n]));
            printf("%lld\n",ans);
        }
    }
    return 0;
}

*/

/*
博客地址:https://blog.csdn.net/leoxe/article/details/107704404
这个代码是ac的,但是我的思路和它一样,为什么wa
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define inf 0x3f3f3f3f3f3f3f3f
const int maxn = 2e5 + 70;
const int maxm = 2e6 + 7;
// 优化查找最近点的优先队列
struct qnode {
    int u;
    LL w;
    qnode(int _u = 0, LL _w = 0) : u(_u), w(_w) {}
    bool operator < (const qnode& b) const {
        return w > b.w;
    }
};
// 储存边以及权值
struct Edge {
    int v;
    LL w;
    Edge(int _v = 0, LL _w = 0) : v(_v), w(_w) {}
};
char str[maxn];
struct Dijstra {
    LL dis[maxn];
    int  n, m, S, T;
    int start, end;
    LL cc;
    bool vis[maxn];
    vector<Edge> G[maxn];
    priority_queue<qnode> pq;
    // 初始化
    void init() {
        while(!pq.empty()) {pq.pop();}
        for(int i = 0; i <= n * 2 + 1; ++ i) {
            vis[i] = false;
            dis[i] = inf;
            G[i].clear();
        }
    }
    // 加边
    void add_edge(int u, int v, LL w) {
        G[u].push_back(Edge(v, w));
        G[v].push_back(Edge(u, w));
    }
    // 读入
    void read_data() {
        scanf("%d %d %d %d %lld", &n, &m, &S, &T, &cc);
        scanf("%s", str+1);
        start = 0;
        end = n * 2 + 1;
        init();
        if(str[S] == 'L') {
            add_edge(start, S, 0);
        } else if(str[S] == 'R') {
            add_edge(start, S + n, 0);
        } else {
            add_edge(start, S, 0);
            add_edge(start, S + n, 0);
        }
        if(str[T] == 'L') {
            add_edge(end, T, 0);
        } else if(str[T] == 'R') {
            add_edge(end, T + n, 0);
        } else {
            add_edge(end, T, 0);
            add_edge(end, T + n, 0);
        }
        while(m --) {
            int u, v;
            LL w;
            scanf("%d %d %lld", &u, &v, &w);
            if(str[u] == 'L') {
                if(str[v] == 'L') {
                    add_edge(u, v, w);
                } else if(str[v] == 'R') {
                    add_edge(u, v + n, w + cc);
                } else {
                    add_edge(u, v, w);
                    add_edge(u, v + n, w + cc);
                }
            } else if(str[u] == 'R') {
                if(str[v] == 'L') {
                    add_edge(u + n, v, w + cc);
                } else if(str[v] == 'R') {
                    add_edge(u + n, v + n, w);
                } else {
                    add_edge(u + n, v, w + cc);
                    add_edge(u + n, v + n, w);
                }
            } else {
                if(str[v] == 'L') {
                    add_edge(u, v, w);
                    add_edge(u + n, v, w + cc);
                } else if(str[v] == 'R') {
                    add_edge(u, v + n, w + cc);
                    add_edge(u + n, v + n, w);
                } else {
                    add_edge(u, v, w);
                    add_edge(u, v + n, w + cc);
                    add_edge(u + n, v, w + cc);
                    add_edge(u + n, v + n, w);
                }
            }
        }
    }

    void dijstra(int st) {
        S = st;
        dis[st] = 0;
        pq.push(qnode(st, 0));
        qnode tmp;
        while(!pq.empty()) {
            tmp = pq.top();
            pq.pop();
            int u = tmp.u;
            if(vis[u]) {
                continue;
            }
            vis[u] = true;
            int sz = G[u].size();
            for(int i = 0; i < sz; ++ i) {
                int v = G[u][i].v;
                LL w = G[u][i].w;
                if(!vis[v] && dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    pq.push(qnode(v, dis[v]));
                }
            }
        }
        printf("%lld\n", dis[end]);
    }
}res;
void Solve(int& kase) {
    int p;
    scanf("%d",&p);
    while(p--){
        res.read_data();
        res.dijstra(0);
    }
}
int main(){
    int k=1;
    Solve(k);
    return 0;
}
*/

/*
自己写的还是wa
和https://blog.csdn.net/leoxe/article/details/107704404一样为什么wa???
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 200100
#define M 4001000
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N<<1],vis[N<<1];
ll dis[N<<1];
char str[N];

struct Node{
    int to,next;
    ll w;
}edge[M];

void addEdge1(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

void addEdge2(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof vis);
    for(int i=0;i<=2*n+1;i++)
        dis[i]=INF;
    //memset(dis,0x3f,sizeof dis);
    dis[0]=0;
}

    priority_queue<pair<ll,int> > Q;
void Dijkstra(int s){
    while(!Q.empty()) Q.pop();
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        //if(vis[2*n+1]) return;
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
    int T,u,v,s,t;
    ll w,x;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d%lld",&n,&m,&s,&t,&x);
        init();
        scanf("%s",str+1);
        if(str[s] == 'L')
            addEdge1(0,s,0);
        else if(str[s] == 'R')
            addEdge1(0,s+n,0);
        else{
            addEdge1(0,s,0);
            addEdge1(0,s+n,0);
        }

        if(str[t] == 'L')
            addEdge1(2*n+1,t,0);
        else if(str[t] == 'R')
            addEdge1(2*n+1,t+n,0);
        else{
            addEdge1(2*n+1,t,0);
            addEdge1(2*n+1,t+n,0);
        }
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            if(str[u] == 'L'){
                if(str[v] == 'L')
                    addEdge1(u,v,w);
                else if(str[v] == 'R')
                    addEdge1(u,v+n,w+x);
                else{
                    addEdge1(u,v,w);
                    addEdge1(u,v+n,w+x);
                }
            }
            else if(str[u] == 'R'){
                if(str[v] == 'L')
                    addEdge1(u+n,v,w+x);
                else if(str[v] == 'R')
                    addEdge1(u+n,v+n,w);
                else{
                    addEdge1(u+n,v,w+x);
                    addEdge1(u+n,v+n,w);
                }
            }
            else{
                if(str[v] == 'L'){
                    addEdge1(u,v,w);
                    addEdge1(u+n,v,w+x);
                }
                if(str[v] == 'R'){
                    addEdge1(u,v+n,w+x);
                    addEdge1(u+n,v+n,w);
                }
                else{
                    addEdge1(u,v,w);
                    addEdge1(u,v+n,w+x);
                    addEdge1(u+n,v,w+x);
                    addEdge1(u+n,v+n,w);
                }
            }
        }
        Dijkstra(0);
        printf("%lld\n",dis[2*n+1]);
    }
    return 0;
}
*/
