#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
int head[N],fa[N][20],dep[N],lg[N],cnt,minw[N][20],ver[N],vis[N];//minw[i][j]表示i节点到其2^j级祖先之间的最小边权
/*
货车装最重的货物，那么就必须货车走的路载重要尽可能大
这里对于两个城市之间的道路肯定是尽可能选择载重较大的道路(贪心),
那么可重构原图为一颗最大生成树,当然原图有可能并不连通,可能需要重构多棵最大生成树,
结果可能是森林.
那么要求火车从x城市运送到y城市所能运送最重的货物,自然而然是从x结点到y结点道路载重最小的权,即求解
x结点到y结点最小的边权.这里可以借用求解lcafa数组倍增建模的方式,那我们可以换一种思路：倍增求出u,v两点的lca,设其为t。
那么u到v的最小边权就是u到t的最小边权 和 v到t的最小边权取min.
建一个数组minw(Minimum Weight)，其中minw[i][j]表示i节点到其2^j级祖先之间的最小边权。
*/
struct Node1{
    int u,v,w;
    bool operator <(const Node1 &a)const{
        return w>a.w;
    }
}edge1[M];

struct Node2{
    int to,next,w;
}edge2[N<<1];

void init(int n){
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        ver[i]=i;
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
}

void addEdge(int from,int to,int w){
    edge2[cnt]=(Node2){to,head[from],w};
    head[from]=cnt++;
    edge2[cnt]=(Node2){from,head[to],w};
    head[to]=cnt++;
}

int find(int x){
    return ver[x]==x?x:(ver[x]=find(ver[x]));
}

//kruskal构建最大生成树 在保证城市道路连通的基础上,载重尽可能大(贪心) 采用kruskal主要是编程复杂度低,十分快捷.
void Kruskal(int n,int m){
    int x,y,num=0;
    for(int i=0;i<m;i++){
        x=find(edge1[i].u);
        y=find(edge1[i].v);
        if(x != y){
            ver[x]=y;
            addEdge(edge1[i].u,edge1[i].v,edge1[i].w);
            num++;
            /*
            这里若原图是连通的,则边数等于点数-1时已经构成树,此时可尽早地结束循环,提高效率.
            若为森林则实际的边数为点数减去森林中树的个数,num<n-1,并不会影响最终的森林.
            */
            if(num == n-1) return;
        }
    }
}

void dfs(int u){
    vis[u]=1;
    for(int i=1,k;i<=lg[dep[u]];i++){
        k=fa[u][i-1];
        fa[u][i]=fa[k][i-1];
        minw[u][i]=min(minw[u][i-1],minw[k][i-1]);//记录从u节点到u以上第2^i次方祖先之间边的最小权值
    }
    for(int i=head[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            dep[v]=dep[u]+1;//v结点深度加1
            fa[v][0]=u;//记录v结点的父亲为u结点
            minw[v][0]=edge2[i].w;//记录u到v节点之前边的权值
            dfs(v);
        }
    }
}

/*
这里其实是借用了求取lca倍增的这个思想,
在倍增的过程中顺带构建了(区间偶数长度的)minw(路径最小边权).
在求货车最大载重时,其实是将x结点到y结点的lca求出来,将原先的路径分成了
偶数长度已经记录过minw[i][j]的路径,这样就可以借助minw去比较x结点和y结点分别到lca的最小边权
*/
int lca(int x,int y){
    int ans=INF;
    if(dep[x]<dep[y]) swap(x,y);
    int i;
    while(dep[x]>dep[y]){
        i=lg[dep[x]-dep[y]];
        ans=min(ans,minw[x][i]);//在x结点向上跳的过程中记录其所经过路径的边最小权值
        x=fa[x][i];
    }
    if(x == y)
        return ans;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            ans=min(ans,min(minw[x][i],minw[y][i]));//在x、y结点同时向上跳时记录,x和y结点到其各自祖先结点路径上的最小边权
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return min(ans,min(minw[x][0],minw[y][0]));//在求取最终的x、y结点到其父亲(lca)的最小边权
}

int main(){
    int n,m,x,y,q;
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge1[i].u,&edge1[i].v,&edge1[i].w);
    sort(edge1,edge1+m);
    Kruskal(n,m);
    for(int i=1;i<=n;i++){//原图不一定连通,最终结果可能是森林
        if(!vis[i])
            dfs(i);//这里以哪个结点作为根节点开始遍历 并不会影响路径最小权值的计算
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&x,&y);
        if(find(x) == find(y))//若x结点和y结点 本身不连通则无法到达
            printf("%d\n",lca(x,y));
        else printf("-1\n");
    }
    return 0;
}
