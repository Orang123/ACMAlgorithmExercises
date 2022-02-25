#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
int head[N],fa[N][20],lg[N],dep[N],cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

void dfs(int u,int fath){
    dep[u]=dep[fath]+1;
    fa[u][0]=fath;
    for(int i=1;i<=lg[dep[u]];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)
            dfs(v,u);
    }
}

int lca(int x,int y){
    if(dep[x]<dep[y])
        swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]];
    if(x == y) return x;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int dis(int x,int y){
    int z=lca(x,y);
    return dep[x]+dep[y]-2*dep[z];
}

/*
这类利用lca性质而不是只求取lca的题目最好用在线算法,而不要使用tarjan(离线做法),
离线做法一次就把所有lca求出来了,但是最后还得再分步 计算出需要的结果
判断树中两条路径是否会有交点,首先两条路径交叉的这种情况不算,
因为树每一个结点只有一个父亲结点,树是没有回路的,这违背了树的定义.
假设两条路径a到b和c到d,lca(a,b)=x,lca(c,d)=y,那么它们有交点的情况是
x在c到d的路径上或y在a到b的路径上,即就是该点(一条路径的lca)到路径(另一条)两端点的距离和等于两端点的距离
求解距离 可通过求解出lca 那么d=dep[x]+dep[y]-2*dep[lca(x,y)]
*/
bool judge(int a,int b,int c,int d){
    int e=lca(a,b),f=lca(c,d);
    /*
    这里分别判断两条路径上的lca距离另一条路径的两端点的距离之和是否等于另一条路径的长度 若相等则有交点
    优化一点可以选择LCA深度大的节点，判断它是否在另外两个节点构成的路径 若刚好在只用判断一次就结束
    这里是||直接分为两种情况,一种不行再考虑另一种
    */
    if(dis(e,c)+dis(e,d) == dis(c,d) || dis(f,a)+dis(f,b) == dis(a,b))
        return true;
    else return false;
}

int main(){
    int n,q,u,v,a,b,c,d;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&q);
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    dep[0]=-1;
    dfs(1,0);//本题因为不是单纯求lca(x,y)的编号,只是求是否有无交点,所以根节点的选取不同并不影响判断 一条路径的lca是否在另一条路径上,因此root可以是任意结点
    while(q--){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        if(judge(a,b,c,d)) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
