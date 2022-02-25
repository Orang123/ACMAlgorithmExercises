#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 300100
using namespace std;
/*
严格次小生成树就是边权之和严格大于（不能等于,也就是添加的边权一定大于mst路径上最大边权）,
但是又是满足该条件的生成树里边权之、和最小的树.
比如说某图的最小生成树的边权和为88，还有其他的几个生成树的边权和分别为88、88、90、100、103、111,
那么边权和为90的生成树就是该图的严格次小生成树，而另外另一棵边权和为88的生成树就是该图的非严格次小生成树
（此时这棵树的边权和 与 mst的边权和相等了）.
在非严格次小生成树中,新添加的边的边权一定不小于最大值（否则就不是最小生成树）,
当mst路径上最大边权等于添加的边权时,这时新形成的mst的边权和和之前的mst相同就属于非严格次小生成树(反正不是严格次小生成树),
因此，对于严格次小生成树来说,不仅要求环上的最大值，还要求环上的次大值，
这样在出现最大值等于边权时可以用次大值更新答案，保证答案正确性.
max1w[x][i],max2w[x][i] 分别表示x点向上走2^i层路径中边权的最大值、x点向上走2^i层路径中边权的次大值.
*/
int head[N],fa[N][20],dep[N],lg[N],max1w[N][20],max2w[N][20],ver[N],vis[N],cnt;
long long sum,ans=1e18;
struct Node1{
    int u,v,w,vis;
    bool operator <(const Node1 &x)const{
        return w<x.w;
    }
}edge1[M];
struct Node2{
    int to,next,w;
}edge2[N<<1];

void init(int n){
    memset(head,-1,sizeof(head));
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)
        ver[i]=i;
}

int find(int x){
    return ver[x]==x?x:(ver[x]=find(ver[x]));
}

void addEdge(int from,int to,int w){
    edge2[cnt]=(Node2){to,head[from],w};
    head[from]=cnt++;
    edge2[cnt]=(Node2){from,head[to],w};
    head[to]=cnt++;
}

void kruskal(int n,int m){
    int num=0,x,y;
    for(int i=0;i<m;i++){
        x=find(edge1[i].u);
        y=find(edge1[i].v);
        if(x != y){
            ver[x]=y;
            edge1[i].vis=1;//标记这条边已被加入mst中
            sum+=edge1[i].w;
            addEdge(edge1[i].u,edge1[i].v,edge1[i].w);//重新构造mst用来dfs
            num++;
            if(num == n-1) return;
        }
    }
}

void dfs(int u){
    vis[u]=1;
    for(int i=1,k;i<=lg[dep[u]];i++){
        k=fa[u][i-1];//k为u点向上第2^(i-1)方个祖先结点的编号
        fa[u][i]=fa[k][i-1];
        max1w[u][i]=max(max1w[u][i-1],max1w[k][i-1]);//统计u点到其向上第2^i次方个祖先结点路径上面边权的最大值
        max2w[u][i]=max(max2w[u][i-1],max2w[k][i-1]);//统计u点到其向上第2^i次方个祖先结点路径上面边权的次大值
        /*
        若u点向上的2个长度为2^(i-1)次方区间路径内的边权的最大值不相等,
        那么maxw1[u][i]边权的次大值取其2区间内最大值的较小者,
        再和之前本身计算出的次小者取较大值为max2[u][i]的边权次大值.
        之所以还要和本身已经计算出的max2[u][i]次大值比较是因为
        max1w[u][i-1]与max1w[k][i-1]较小者有可能比之前计算出的max2[u][i]次大值还要小,
        因此我们要取次大值,就要再比较.比如较小值取得是max1w[k][i-1],而之前次大值所取的是max2w[u][i-1],
        这个max2w[u][i-1]是有可能比max1w[k][i-1]还要大的.
        */
        if(max1w[u][i-1] != max1w[k][i-1])
            max2w[u][i]=max(max2w[u][i],min(max1w[u][i-1],max1w[k][i-1]));
        /*
        若u点向上的2个长度为2^(i-1)次方区间路径内的边权的最大值相等,那么次小值就只能考虑max2w[u][i-1],max2w[k][i-1]中较大者,
        这样才可以避免当枚举不在mst的边权刚好等于路径中边权较大值时所选的边权次大值和最大值相等,这样才能构造出严格次小生成树,
        其权值和要小于mst的.
        */
    }
    for(int i=head[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            dep[v]=dep[u]+1;
            fa[v][0]=u;
            max1w[v][0]=edge2[i].w;//这里不能初始化max2w[v][0],因为在求取max2w[v][1]=(max2w[v][0],max2w[k][0])所求出的是最大边权,而不是次大边权
            dfs(v);
        }
    }
}

//利用lca倍增的过程 求取x到y路径上的最大边权或次大边权 w为未加入mst中的边权
int lca(int x,int y,int w){
    int k,res=-1;
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]){
        k=lg[dep[x]-dep[y]];
        /*
        若w和最大边权不等,那么这里w一定大于最大边权,那么就选择未加入mst中的边权去替换最大边权,替换后的边权和也大于之前mst的边权和
        如果w和最大边权相等,则为了避免替换后的边权和之前mst的边权和一样,这里选择w去替换max2边权次大值,
        这里w也一定是大于max2次大值的,同样最终的替换后的边权和也大于之前mst的边权和.
        */
        res=max(res,max1w[x][k]!=w?max1w[x][k]:max2w[x][k]);
        x=fa[x][k];
    }
    if(x == y) return res;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i] != fa[y][i]){
            res=max(res,max1w[x][i]!=w?max1w[x][i]:max2w[x][i]);//这里需要同时比对x与y结点同时向上跳的两条路径中的边权最大值
            res=max(res,max1w[y][i]!=w?max1w[y][i]:max2w[y][i]);
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    res=max(res,max1w[x][0]!=w?max1w[x][0]:max2w[x][0]);//最后比较x于y结点到其父亲结点(lca)边权
    res=max(res,max1w[y][0]!=w?max1w[y][0]:max2w[y][0]);
    return res;
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge1[i].u,&edge1[i].v,&edge1[i].w);
    sort(edge1,edge1+m);
    kruskal(n,m);
    dfs(1);
    for(int i=0;i<m;i++){
        if(!edge1[i].vis){
            int res=lca(edge1[i].u,edge1[i].v,edge1[i].w);//先求出lca,再利用求解lca倍增的过程求解x到y路径上边权的最大值
            /*
            将edge1[i].u到edge1[i].v这条边权加入mst中会产生环,这样同时删去
            mst中edge1[i].u到edge1[i].v中路径边权的最大值就构成了严格次小生成树
            之所以要替换路径上的边权最大值是因为,mst Kruskal每次加入的边一定是最小的,
            这条为选入mst中的边权一定大于等于路径上的最大边权的,否则当前求出的就不是mst了,
            mst在构造时不应该把这条未加入mst中的边权加入mst中吗
            */
            ans=min(ans,sum-res+edge1[i].w);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
/*
将求取x到y路径上的最大边权分成了2步求解,先求解出其lca(x,y),
再去分别求解x到lca(x,y)和y到lca(x,y)的最大边权最后再做比较,
没有必要这么做,直接在第一次求取lca的过程里就把x到y的最大边权求解出来.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 300100
using namespace std;
int head[N],fa[N][20],dep[N],lg[N],max1w[N][20],max2w[N][20],ver[N],vis[N],cnt;
long long sum,ans=1e18;
struct Node1{
    int u,v,w,vis;
    bool operator <(const Node1 &x)const{
        return w<x.w;
    }
}edge1[M];
struct Node2{
    int to,next,w;
}edge2[N<<1];

void init(int n){
    memset(head,-1,sizeof(head));
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)
        ver[i]=i;
}

int find(int x){
    return ver[x]==x?x:(ver[x]=find(ver[x]));
}

void addEdge(int from,int to,int w){
    edge2[cnt]=(Node2){to,head[from],w};
    head[from]=cnt++;
    edge2[cnt]=(Node2){from,head[to],w};
    head[to]=cnt++;
}

void kruskal(int n,int m){
    int num=0,x,y;
    for(int i=0;i<m;i++){
        x=find(edge1[i].u);
        y=find(edge1[i].v);
        if(x != y){
            ver[x]=y;
            edge1[i].vis=1;
            sum+=edge1[i].w;
            addEdge(edge1[i].u,edge1[i].v,edge1[i].w);
            num++;
            if(num == n-1) return;
        }
    }
}

void dfs(int u){
    vis[u]=1;
    for(int i=1,k;i<=lg[dep[u]];i++){
        k=fa[u][i-1];
        fa[u][i]=fa[k][i-1];
        max1w[u][i]=max(max1w[u][i-1],max1w[k][i-1]);
        max2w[u][i]=max(max2w[u][i-1],max2w[k][i-1]);
        if(max1w[u][i-1] != max1w[k][i-1])
            max2w[u][i]=max(max2w[u][i],min(max1w[u][i-1],max1w[k][i-1]));
    }
    for(int i=head[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            dep[v]=dep[u]+1;
            fa[v][0]=u;
            max1w[v][0]=edge2[i].w;
            dfs(v);
        }
    }
}

int lca(int x,int y){
    int k;
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]){
        k=lg[dep[x]-dep[y]];
        x=fa[x][k];
    }
    if(x == y) return x;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i] != fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int getMaxw(int x,int y,int w){
    int res=-1,k;
    while(dep[x]>dep[y]){
        k=lg[dep[x]-dep[y]];
        res=max(res,max1w[x][k]!=w?max1w[x][k]:max2w[x][k]);
        x=fa[x][k];
    }
    return res;

}

int main(){
    int n,m,x,y,res,maxu,maxv;
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge1[i].u,&edge1[i].v,&edge1[i].w);
    sort(edge1,edge1+m);
    kruskal(n,m);
    dfs(1);
    for(int i=0;i<m;i++){
        if(!edge1[i].vis){
            res=lca(edge1[i].u,edge1[i].v);
            maxu=getMaxw(edge1[i].u,res,edge1[i].w);
            maxv=getMaxw(edge1[i].v,res,edge1[i].w);
            ans=min(ans,sum-max(maxu,maxv)+edge1[i].w);
        }
    }
    printf("%lld\n",ans);
    return 0;
}*/
