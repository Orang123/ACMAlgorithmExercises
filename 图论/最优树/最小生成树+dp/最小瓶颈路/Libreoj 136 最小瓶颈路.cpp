#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//prim+dp ac 95ms
/*
相关定义:
最小瓶颈路:无向图G中x到y的最小瓶颈路是这样的一类简单路径,
满足这条路径上的最大的边权在所有x到y的简单路径中是最小的.
性质:
x到y的最小瓶颈路上的最大边权等于最小生成树上x到y路径上的最大边权.
虽然最小生成树不唯一,但是每种最小生成树x到y路径的最大边权相同且为最小值,
因为所有的最小生成树权值相等的边的个数是相等的.
也就是说,每种最小生成树上的x到y的路径均为最小瓶颈路.
*/

/*
题意:给定一个包含n个节点和m条边的图,每条边有一个权值.
你的任务是回答k个询问,每个询问包含两个正整数s和t表示起点和终点,
要求寻找从s到t的一条路径,使得路径上权值最大的一条边权值最小.
对于100%的数据,n<=1000,m<=100000,k<=1000,w<=10000000
链接:https://loj.ac/problem/136
思路:就是求解最小瓶颈路上的最大边权,可以转化为求解mst计算出mst上路径的最大边权.
因为k询问<=1000,用数组maxLen将结果保存起来.
因为n<=1000,maxLen[N][N]不会MLE,可以采用prim+dp计算出mst上路径的最大边权或者
kruskal+树形dp计算maxLen.但是当n达到10000时,maxLen这么开数组可能会卡MLE,这时需要用
lca倍增求解树上任意两点间最大边权.
*/

int n,m,k,head[N],cnt,dis[N],vis[N],used[N][N],maxLen[N][N],seq[N],sum;

struct state{
    int u,v,dis;
    state(int u=0,int v=0,int dis=0):u(u),v(v),dis(dis){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Edge{
    int from,to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof vis);
    memset(used,0,sizeof used);
    memset(dis,0x3f,sizeof dis);
    dis[s]=0;
    memset(maxLen,0,sizeof maxLen);
}

void prim(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(s,s,0));
    int u,v,num=0;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        Q.pop();
        u=tmp.v;
        if(vis[u]) continue;
        vis[u]=1;
        used[tmp.u][u]=used[u][tmp.u]=1;
        sum+=dis[u];
        for(int i=1;i<=num;i++)
            maxLen[seq[i]][u]=maxLen[u][seq[i]]=max(maxLen[seq[i]][tmp.u],dis[u]);
        seq[++num]=u;
        if(num == n) break;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(state(u,v,dis[v]));
            }
        }
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof head);
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    prim(1);
    while(k--){
        scanf("%d%d",&u,&v);
        if(!maxLen[u][v]) maxLen[u][v]=-1;
        printf("%d\n",maxLen[u][v]);
    }
    return 0;
}

/*
//lca倍增求解树上任意两点间最大边权 ac 43ms
#include <bits/stdc++.h>
#define maxn 2000005
using namespace std;
int n, m, tot, S, T, lnk[maxn], fa[maxn], Q, nxt[maxn], son[maxn], w[maxn];
struct lc {
    int x, y, z;
    bool operator<(const lc b) const { return z < b.z; }
} e[maxn];
inline int read() {
    int ret = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0') ret = ret * 10 + ch - '0', ch = getchar();
    return ret * f;
}
inline int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
inline void add(int x, int y, int z) {
    nxt[++tot] = lnk[x];
    lnk[x] = tot;
    son[tot] = y;
    w[tot] = z;
}
namespace Tree {
int dep[maxn], fa[maxn][25], dis[maxn][25];
void dfs(int x) {
    dep[x] = dep[fa[x][0]] + 1;
    for (int i = 1; i <= 20; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1], dis[x][i] = max(dis[fa[x][i - 1]][i - 1], dis[x][i - 1]);
    for (int i = lnk[x]; i; i = nxt[i])
        if (son[i] != fa[x][0])
            dis[son[i]][0] = w[i], fa[son[i]][0] = x, dfs(son[i]);
}
int LCA(int x, int y) {
    int Mx = 0;
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[fa[x][i]] >= dep[y])
            Mx = max(Mx, dis[x][i]), x = fa[x][i];
    if (x == y)
        return Mx;
    for (int i = 20; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
            Mx = max(Mx, max(dis[x][i], dis[y][i])), x = fa[x][i], y = fa[y][i];
    return max(Mx, max(dis[x][0], dis[y][0]));
}
}  // namespace Tree
int main() {
    n = read(), m = read(), Q = read();
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) e[i].x = read(), e[i].y = read(), e[i].z = read();
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= m; i++) {
        int fx = getfa(e[i].x), fy = getfa(e[i].y);
        if (fx == fy)
            continue;
        fa[fx] = fy;
        add(e[i].x, e[i].y, e[i].z), add(e[i].y, e[i].x, e[i].z);
    }
    for (int i = 1; i <= n; i++)
        if (!Tree::dep[i])
            Tree::dfs(i);
    while (Q--) {
        S = read(), T = read();
        printf("%d\n", getfa(S) != getfa(T) ? -1 : Tree::LCA(S, T));
    }
    return 0;
}
*/
