#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 1000100
using namespace std;
typedef long long ll;
//kruskal 1752ms
/*
题意:n个点,m条边,求解mst,以及所构建的mst上任意两点间距离的最小的数学期望.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5723
思路:关键是任意两点间距离的最小的数学期望,要想最小,必然还是需要构建出最小生成树,
数学期望=(树上所有路径的距离和)/(完全图中所有边数),树上所有路径的距离和可通过
计算每条边在所有路径贡献的次数求得,即:边权*边左侧所有端点个数*边右侧所有端点个数.
那么边左右两侧的个数显然可通过树形dp求得,在dp时顺带计算所有路径距离和.
*/
//son[u]表示以u为根节点的所有儿子个数+1(自己)
int m,fa[N],cnt,head[N];
ll n,ans,son[N];

struct Node{
    int to,next;
    ll w;
}node[N<<1];

struct Edge{
    int u,v;
    ll w;
    Edge(int u=0,int v=0,ll w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void addEdge(int from,int to,ll w){
    node[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

ll kruskal(){
    init();
    int x,y,num=0;
    ll sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            num++;
            sum+=edge[i].w;
            addEdge(edge[i].u,edge[i].v,edge[i].w);
            addEdge(edge[i].v,edge[i].u,edge[i].w);
            if(num == n-1) break;
        }
    }
    return sum;
}

void dfs(int u,int fa){
    son[u]=1;
    for(int i=head[u];i!=-1;i=node[i].next){
        int v=node[i].to;
        if(v == fa) continue;
        dfs(v,u);
        son[u]+=son[v];
        //每条边在所有路径中贡献的次数等于这条边的两个端点两侧`顶点数目的乘积
        //那么这条边贡献的权值和就为边权*son[v]*(n-son[v])
        ans+=node[i].w*son[v]*(n-son[v]);
    }
}

int main(){
    int T;
    ll sum;
    scanf("%d",&T);
    while(T--){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%lld%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%lld",&edge[i].u,&edge[i].v,&edge[i].w);
        sum=kruskal();
        dfs(1,-1);
        printf("%lld %.2f\n",sum,(double)ans/(n*(n-1)/2));
    }
    return 0;
}
