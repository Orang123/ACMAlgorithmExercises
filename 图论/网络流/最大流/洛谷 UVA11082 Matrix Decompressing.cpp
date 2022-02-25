#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 50
#define M 2500
#define INF 0x3f3f3f3f
using namespace std;
//wa 我的矩阵输出和答案大不同和网上的也不同,但最大流的值是对的,不知何原因
//这个做法 具体原理还有待证明,暂时只是知道这个做法能做对
/*
题意:知道矩阵的前i行之和,和前j列之和(任意i和j都可以).求这个矩阵.
每个格子中的元素必须在1~20之间,矩阵大小上限20*20.
链接:https://www.luogu.com.cn/problem/UVA11082
思路:参照博客:https://www.cnblogs.com/xiaochaoqun/p/7190016.html
通过前i行的和以及前j列的和,获得每一行的和以及每一列的和.
把每一行看做一个节点,每一列看做一个节点.建立一个源点到达每一行.
建立一个汇点,每一列到达汇点.每一行到达每一列.由于数据范围是[1,20],
流可以说0.所以为了方便处理,所有容量-1.最后结果+1.那么源点到第i行的
容量为r[i]-列数.(每一行有列数个数)第j列到汇点的容量为c[j]-行数,
第i行到第j列的容量都为19(20-1).为什么要这样做呢,因为网络流里面是
可能存在0流的,所以我们把下界减一,那么答案就不会有漏.每一行都经过
每一列组成,所以这样建立连接.如果源点到每一个行节点都是满载,每一个
列节点到汇点都是满载.那么有解,解为:第i行第j列的元素为第i行的节点到
第j列的节点的流+1.
*/
int cas,n,m,r[N],c[N],st,ed,cnt,head[N],dis[N];
struct Edge{
    int from,to,next,cf,flow;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){from,to,head[from],cf,0};
    head[from]=cnt++;
    edge[cnt]=(Edge){to,from,head[to],0,0};
    head[to]=cnt++;
}

int bfs(int s,int ed){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int ed,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,ed,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i].flow+=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

void max_flow(int st,int ed){
    while(bfs(st,ed))
        dfs(st,ed,INF);
}

void init(){
    cas++;
    cnt=0;
    st=0,ed=n+m+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++)
            scanf("%d",&r[i]);
        for(int i=1;i<=m;i++)
            scanf("%d",&c[i]);
        for(int i=n;i>=1;i--){
            r[i]=r[i]-r[i-1];
            addEdge(st,i,r[i]-m);//源点->每一行,容量为第i行权值和-m
        }
        for(int i=m;i>=1;i--){
            c[i]=c[i]-c[i-1];
            addEdge(i+n,ed,c[i]-n);//每一列->汇点,容量为第i列权值和-n
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                addEdge(i,j+n,19);//第i行->第j列 容量为19
        }
        max_flow(st,ed);
        printf("Matrix %d\n",cas);
        for(int i=(n+m)*2;i<cnt;i+=2){//前(n+m)*2是和源点和汇点连接的边,之后才是行和列的连边
            if(edge[i].to-n == m) printf("%d\n",edge[i].flow+1);
            else printf("%d ",edge[i].flow+1);
        }
    }
    return 0;
}

/*
//摘自博客:https://www.cnblogs.com/xiaochaoqun/p/7190016.html
//ac 0ms EK算法
#include<iostream>
#include<cstring>
#include<vector>
#include<map>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long LL;
const int N = 110;
int r[N], c[N];
struct Edge{
    int from, to, cap, flow;
    Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};
struct EdmondsKarp
{
    int n, m;
    vector<Edge> edges;
    vector<int> G[N];
    int p[N];
    int a[N];
    int ans[N][N];

    void init(int n)
    {
        for(int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int cap){
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int Maxflow(int s,int t)
    {
        int flow = 0;
        for(;;){
            memset(a, 0, sizeof a);
            queue<int>Q;
            Q.push(s);
            a[s] = INF;
            while(!Q.empty()){
                int x = Q.front(); Q.pop();
                for(int i = 0; i < G[x].size(); i++){
                    Edge& e = edges[G[x][i]];
                    if(!a[e.to]&&e.cap>e.flow){
                        p[e.to] = G[x][i];
                        a[e.to] = min(a[x],e.cap-e.flow);
                        Q.push(e.to);
                    }
                }
                if(a[t]) break;
            }
            if(!a[t]) break;
            for(int u = t; u != s; u = edges[p[u]].from){
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }

    void getMatrix()
    {
        int r = 0, c = 0;
        for(int i = 2*(n+m); i < edges.size(); i+=2){
            if(c==m) {
                r++, c = 0;
            }
            ans[r][c] = edges[i].flow;
            c++;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(j==m-1) printf("%d\n",ans[i][j]+1);
                else printf("%d ",ans[i][j]+1);
            }
        }
    }
};

int main()
{
    int n, m, T;
    scanf("%d",&T);
    for(int cas = 1; cas <= T; cas++){
        scanf("%d%d",&n,&m);
        for(int i = 0; i < n; i++) scanf("%d",&r[i]);
        for(int i = 0; i < m; i++) scanf("%d",&c[i]);
        for(int i = n-1; i > 0; i--) r[i] = r[i]-r[i-1];
        for(int i = m-1; i > 0; i--) c[i] = c[i]-c[i-1];
        int s, t;
        s = 0, t = n+m+1;
        EdmondsKarp ek;
        ek.init(t);
        ///s -> r
        for(int i = 0; i < n; i++) ek.AddEdge(s,i+1,r[i]-m);
        ///c -> t
        for(int i = 0; i < m; i++) ek.AddEdge(n+i+1,t,c[i]-n);
        ///r -> c
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                ek.AddEdge(i+1,n+j+1,19);
            }
        }
        int flow = ek.Maxflow(s,t);
        printf("Matrix %d\n",cas);
        ek.n = n, ek.m = m;
        ek.getMatrix();
    }
    return 0;
}
*/
