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
��ض���:
��Сƿ��·:����ͼG��x��y����Сƿ��·��������һ���·��,
��������·���ϵ����ı�Ȩ������x��y�ļ�·��������С��.
����:
x��y����Сƿ��·�ϵ�����Ȩ������С��������x��y·���ϵ�����Ȩ.
��Ȼ��С��������Ψһ,����ÿ����С������x��y·��������Ȩ��ͬ��Ϊ��Сֵ,
��Ϊ���е���С������Ȩֵ��ȵıߵĸ�������ȵ�.
Ҳ����˵,ÿ����С�������ϵ�x��y��·����Ϊ��Сƿ��·.
*/

/*
����:����һ������n���ڵ��m���ߵ�ͼ,ÿ������һ��Ȩֵ.
��������ǻش�k��ѯ��,ÿ��ѯ�ʰ�������������s��t��ʾ�����յ�,
Ҫ��Ѱ�Ҵ�s��t��һ��·��,ʹ��·����Ȩֵ����һ����Ȩֵ��С.
����100%������,n<=1000,m<=100000,k<=1000,w<=10000000
����:https://loj.ac/problem/136
˼·:���������Сƿ��·�ϵ�����Ȩ,����ת��Ϊ���mst�����mst��·��������Ȩ.
��Ϊkѯ��<=1000,������maxLen�������������.
��Ϊn<=1000,maxLen[N][N]����MLE,���Բ���prim+dp�����mst��·��������Ȩ����
kruskal+����dp����maxLen.���ǵ�n�ﵽ10000ʱ,maxLen��ô��������ܻῨMLE,��ʱ��Ҫ��
lca������������������������Ȩ.
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
//lca������������������������Ȩ ac 43ms
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
