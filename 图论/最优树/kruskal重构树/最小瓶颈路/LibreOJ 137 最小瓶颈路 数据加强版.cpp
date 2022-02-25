#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 75000
#define M 100100
#define MOD 1000000007
using namespace std;
//kruskal�ع���+RMQ-st�� ac 2573ms
//��������RMQ-st����Kruskal�ع��� ֱ��O(1)��������Ȩ
/*
kruskal�ع�����ظ���:
����Kruskal��С����ӱ�ʱ,ÿһ�μӱ߻�ϲ���������,
���ǿ����½�һ����,��ȨΪ����ߵı�Ȩ,
ͬʱ���������ϵĸ��ڵ�ֱ���Ϊ�½��������Ӻ��Ҷ���.
Ȼ�����ǽ��������ϸ��ڵ㶼ָ���½���,���½���ϲ���һ������,���½�����Ϊ��.
���ѷ���,�ڽ���n-1��֮�����ǵõ���һ��ǡ��n��Ҷ�ӽڵ�(ԭ�ȵ�n����)�Ķ�����,
ͬʱÿ����Ҷ�ӽڵ�(n-1��,�е�Ȩ)ǡ������������.������ͽ�kruskal�ع���.���
��������������������.���Է���Խ�����������еĸ��ڵ�,��Ӧ�ĵ�ȨԽ��
(������С������,���������,�򿿽����ڵ�ĵ�ȨԽС),��ı��ҲԽ��,
��Ӧ�����������ȨҲ��Խ��.ʵ�ʹ���ʱ�ȹ�������ӽڵ������ι�������׽ڵ�.
��kruskal�ع�����������Ҷ�ӽڵ��lca�ĵ�Ȩ����ԭ��С���������������·���ϵ�����Ȩ,
��������������Ļ�,��Ȩ��ԭ������������������·���ϵ���С��Ȩ.
*/

/*
����:����һ������n���ڵ��m���ߵ�������ͨͼ,û���Ի�,�������ر�,ÿ������һ��Ȩֵw.
��������ǻش�q��ѯ��,ÿ��ѯ�ʰ�������������s��t��ʾ�����յ�,
Ҫ��Ѱ�Ҵ�s��t��һ��·��,ʹ��·����Ȩֵ����һ����Ȩֵ��С.
����100%������,n<=70000,m<=100000,q<=10000000,w<=1000000007
�������������ߵ�,����ѹ��������:����4������,ÿ��ѯ�ʵ������º�������u��v:
int A,B,C,P;
inline int rnd(){return A=(A*B+C)%P;}
ÿ��ѯ��ʱ�ĵ��÷���Ϊ:u=rnd()%n+1,v=rnd()%n+1;
�����һ��һ������,��ʾ����ѯ�ʵĴ�֮��ģ10^9+7��ֵ��
����:https://loj.ac/problem/137
˼·:���������Сƿ��·�е�����Ȩ,���ǵ�ͨ�����mst�����Сƿ��·.���ر�,����ʽǰ����.
��Ϊn<=70000,prim+dp������maxLen[N][N]��������ô��,��k<=10^7,�����lca,���Ӷ�klog(N),
1sҲ��TLE.��ô���ǿ�����st���O(1)��ѯ������,��lcaת��ΪRMQ st����,�������ֻ������
������������֮��������������(lca)�ı��,�޷�����·���ϵ�����Ȩ,��ô���ǿ�����kruskal
ʱ����kruskal�ع���,�������չ�����Ķ������ķ�Ҷ�ӽڵ��ϵĵ�Ȩ����ԭ����������������Ȩ.
����·���ϵı�Ȩ��������,��ת��Ϊֻ�����������������lca��ŵ�Ȩ������,��ô�Ϳ�ֱ��ͨ��lcaת��Ϊ
RMQ-st����ʵ��.��֮���Բ���RMQ ����dp����st��ʱ���ձ����㷨,dfsʱȥ����һЩmax��������ȥ����·�����ֵ,
����Ϊ�������lca�����Ѿ���һ����������ת��ΪRMQ st��������,Ҳ����˵��RMQʱ�Ѿ���ȫ����������(dfs)�����������,
��Ϊ����ʹ�е�ĸ����ʱ��,�޷���������͵�֮���Ȩ�ĸ���,�Ӷ�Ҳ�޷����ñ��max��������ȥ��������Ȩ.
*/

/*
kruskal�ع������¹���ĵ������Ϊmst�бߵĸ���(n-1),�����ع�mst�е�ĸ���n+n-1=2*n-1,
���Ҷ�Ӧ��lca����תΪRMQ����,��Ҫ�������ȱ������������ܳ���ӦΪ�����Ķ�����2*(2*n-1)-1
Ҳ����4*n,��dfn,st,lg���鳤�ȶ�ΪN<<2.
*/
int head[N<<1],dfn[N<<2],st[N<<2][20],dep[N<<1],lg[N<<2],fa[N<<1],cnt,val[N<<1],num,vis[N<<1];
int A,B,C,P;
struct Node1{
    int u,v,w;
    bool operator < (const Node1 &x)const{
        return w<x.w;
    }
}edge1[M];
struct Node2{
    int to,next;
}edge2[N<<2];

inline int rnd(){
    return A=(A*B+C)%P;
}

void addEdge(int from,int to){
    edge2[cnt]=(Node2){to,head[from]};
    head[from]=cnt++;
    edge2[cnt]=(Node2){from,head[to]};
    head[to]=cnt++;
}

void init(int n){
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        fa[i]=i;
    lg[0]=-1;
    n*=2;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

void kruskal(int n,int m){
    int num=n,x,y;//numҪ��n��ʼ,��Ϊ�¼���ĵ��Ŵ�n+1��ʼ val[num]
    for(int i=0;i<m;i++){//��Ϊ�ǰ��ձ�Ȩ��С����˳��ӱߵ�,�������յ�kurskal�ع���Խ�������ڵ���½���ĵ�ȨԽ��
        x=find(edge1[i].u);
        y=find(edge1[i].v);
        if(x!=y){
            num++;
            fa[x]=fa[y]=num;//��x��y�������ϵĸ��ڵ�ֱ���Ϊ�½��������Ӻ��Ҷ���,���½�����Ϊ��,���������Ϻϲ�Ϊһ������
            val[num]=edge1[i].w;//��¼�����ߵ�Ȩ
            addEdge(x,num);//ԭ�ȵ�x��y���ĸ��ڵ�ֱ���Ϊ�½�������Ҷ���
            addEdge(y,num);
            /*
            ��¼ԭ��x��㵽y���֮��ı�Ȩ, �ٲ��Ϲ����½���ʱ,ʵ���������Ҳ�ڱ�����̧��(��Ӧ�ı�ȨҲ�ǲ��������),
            ���ϵؿ������յĸ��ڵ�,�������֮�������Ȩ�ͻ�Խ��Խ��
            */
            if(num - n == n-1) return;
        }
    }
}

void dfs(int u){
    vis[u]=1;
    dfn[u]=++num;
    st[num][0]=u;
    for(int i=head[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            dep[v]=dep[u]+1;
            dfs(v);
            st[++num][0]=u;
        }
    }
}

void RMQ(){
    int a,b;
    for(int i=1;i<=lg[num];i++){
        for(int j=1;j+(1<<i)-1<=num;j++){
            a=st[j][i-1];
            b=st[j+(1<<i-1)][i-1];
            if(dep[a]<dep[b])
                st[j][i]=a;
            else
                st[j][i]=b;
        }
    }
}

int lca(int x,int y){
    int k,a,b;
    if(x>y) swap(x,y);
    k=lg[y-x+1];
    a=st[x][k];
    b=st[y-(1<<k)+1][k];
    if(dep[a]<dep[b]) return a;
    else return b;
}

int main(){
    int n,m,q,u,v,ans=0;
    scanf("%d%d",&n,&m);
    init(2*n);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge1[i].u,&edge1[i].v,&edge1[i].w);
    sort(edge1,edge1+m);
    kruskal(n,m);
    dfs(2*n-1);
    RMQ();
    scanf("%d",&q);
    scanf("%d%d%d%d",&A,&B,&C,&P);
    while(q--){
        u=rnd()%n+1,v=rnd()%n+1;
        //��С��������������֮��ļ�·���ϱ�Ȩ���ֵ=Kruskal�ع���������֮���LCA���Ȩֵ.
        ans=(ans+val[lca(dfn[u],dfn[v])])%MOD;
    }
    printf("%d\n",ans);
    return 0;
}

/*
//RMQ-st�� ֱ��o(1)��������Ȩ,û�й���kruskal�ع��������� ac 2681ms
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, x, y) for (int i = (x); i < (y); ++i)
#define REP(i, x, y) for (int i = (x); i <= (y); ++i)
#define PB push_back
#define MP make_pair
#define PH push
#define fst first
#define snd second
typedef long long ll;
typedef unsigned long long ull;
typedef double lf;
typedef long double Lf;
typedef pair<int, int> pii;

const int maxm = 2e5 + 5;
const int maxn = 2e5 + 5;
const int logn = 20;
const int INF = 1e9 + 7;

int n, m, q, ans = 0;
int a[maxn];
int A, B, C, P;

class Edge {
public:
    int u, v, w;
    Edge() {}
    inline Edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}
    inline bool operator<(const Edge &oth) const { return w < oth.w; }
} ed[maxm];

class Dsu {
public:
    int fa[maxn], rk[maxn];
    inline void init() {
        FOR(i, 0, maxn) fa[i] = i, rk[i] = 1;
        return;
    }
    inline int find(int u) { return (u == fa[u] ? u : find(fa[u])); }
    inline void merge(int u, int v, int w) {
        u = find(u), v = find(v);
        if (u == v)
            return;
        fa[u] = fa[v] = n;
        a[n++] = w;
        return;
    }
} dsu;

namespace Tree {
int tl;
int que[maxn << 1], eul[maxn];
int mn[maxn << 1][logn], lg[maxn << 1];
vector<int> g[maxn];

inline void dfs(int u) {
    eul[u] = tl;
    que[tl++] = u;
    FOR(i, 0, g[u].size()) {
        int v = g[u][i];
        dfs(v);
        que[tl++] = u;
    }
    return;
}

inline void build() {
    FOR(i, 0, n) if (dsu.fa[i] != i) g[dsu.fa[i]].PB(i);
    dfs(n - 1);

    FOR(i, 0, tl)
    mn[i][0] = a[que[i]];
    FOR(j, 1, logn)
    FOR(i, 0, tl) mn[i][j] = max(mn[i][j - 1], (i + (1 << j - 1) < tl) ? mn[i + (1 << j - 1)][j - 1] : INF);

    lg[1] = 0;
    REP(i, 2, tl)
    lg[i] = lg[i - 1] + ((1 << lg[i - 1] + 1) <= i);
    return;
}

inline int query(int u, int v) {
    u = eul[u], v = eul[v];
    if (u > v)
        swap(u, v);
    int k = lg[v - u + 1];
    return max(mn[u][k], mn[v - (1 << k) + 1][k]);
}
}  // namespace Tree

inline int rnd() { return A = (A * B + C) % P; }

int main() {
    scanf("%d%d", &n, &m);
    int pn = n;
    FOR(i, 0, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u;
        --v;
        ed[i] = Edge(u, v, w);
    }

    dsu.init();
    sort(ed, ed + m);
    FOR(i, 0, m)
    dsu.merge(ed[i].u, ed[i].v, ed[i].w);

    Tree::build();

    scanf("%d", &q);
    scanf("%d%d%d%d", &A, &B, &C, &P);
    FOR(i, 0, q) {
        int u = rnd() % pn, v = rnd() % pn;
        (ans += Tree::query(u, v)) %= INF;
    }

    printf("%d\n", ans);
    return 0;
}
*/
