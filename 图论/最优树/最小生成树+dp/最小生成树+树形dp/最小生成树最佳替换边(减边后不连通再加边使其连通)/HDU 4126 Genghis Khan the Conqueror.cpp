#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3100
#define M 9000100
#define INF 0x3f3f3f3f
using namespace std;
//kruskal 1154ms ac
/*
题意:n个点,m条边,求解mst,有q次询问,每次询问会把原先边替换为权值较大的边,
问q次询问替换后的mst权值和的平均值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4126
思路:q<=10000,显然跑q次kruskal,这样肯定会TLE.
对于每次询问,都是将a，b之间的边增加到c,会出现两种情况:
1.如果边权增加的那条边原先就不在最小生成树中,那么这时候的最小生成树的值不变
2.如果该边在原最小生成树中,那么这时候将增加的边从原最小生成树中去掉,
这时候生成树就被分成了两个各自连通的部分,可以证明的是,
这时候的最小生成树一定是将这两部分联通起来的最小的那条边.
先kruskal构造出生成树的图,再dp求解dp[i][j].这样就只需要跑一次kruskal.
dp[i][j]表示去掉最小生成树中的边(i,j)分成两个连通部分后,将他们再次连接起来的最小的那条边长.
http://www.mamicode.com/info-detail-410392.html 分析摘自这篇文章
*/
//询问判断是否是mst边 用pre[u]!=v pre[v]!=u会wa,不懂
//https://blog.csdn.net/qq_36889101/article/details/88789284 这个pre判断前驱是ac的
int mp[N][N],n,m,q,fa[N],sum,head[N],cnt,dp[N][N],vis[N][N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

struct Node{
    int to,next;
}node[N<<1];

void addEdge(int from,int to){
    node[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void init(){
    sort(edge+1,edge+1+m);
    for(int i=0;i<n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,num=0,a,b;
    for(int i=1;i<=m;i++){
        a=edge[i].u,b=edge[i].v;
        x=find(a),y=find(b);
        if(x!=y){
            fa[x]=y;
            num++;
            sum+=edge[i].w;
            vis[a][b]=vis[b][a]=1;//标记u->v v->u这条边为生成树中的边
            addEdge(a,b);//构造mst的图,进行dp
            addEdge(b,a);
            if(num == n-1) break;
        }
    }
}

int dfs(int u,int fa,int rt){
    int res=INF;
    for(int i=head[u];i!=-1;i=node[i].next){
        int v=node[i].to;
        if(v == fa) continue;
        int tmp=dfs(v,u,rt);//tmp代表v的子树中rt和其所有节点(包括v)连边中最小的
        res=min(res,tmp);//res代表u的所有子树中rt和其所有节点(包括u)连边中最小的
        /*
        dp[u][v] 是断开u->v的连边,那么被分开的另一个连通集是v的子树,所以要使得分开的v的子树连通集再次连接,
        rt要和v及其子节点连边才能使得mst再次连通.不能和u的其余子节点的子树连边,这样即使连边当前v节点的子树
        仍然是分离的.
        */
        dp[u][v]=dp[v][u]=min(dp[u][v],tmp);
    }
    //当u的父节点为rt时,dp[rt][u]更新时不能取mp[rt][u],因为rt->u这条边已经是切断的,不能再取
    //其余情况res需和rt->u这条边权去比较求最小
    if(rt!=fa) res=min(res,mp[rt][u]);
    return res;
}

int main(){
    int u,v,w;
    double ans;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=cnt=sum=0;
        memset(head,-1,sizeof head);
        memset(vis,0,sizeof vis);
        memset(mp,0x3f,sizeof mp);//给出的边不一定构成完全图,所以要初始化.
        memset(dp,0x3f,sizeof dp);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            edge[i]=Edge(u,v,w);
            mp[u][v]=mp[v][u]=w;
        }
        kruskal();
        //以每个点作为根节点和被分割的另一个连通集连边,更新更小的dp[u][v]
        for(int i=0;i<n;i++)//O(n^2)
            dfs(i,-1,i);
        scanf("%d",&q);
        for(int i=1;i<=q;i++){
            scanf("%d%d%d",&u,&v,&w);
            //u->v不在mst中,本次的权值和就是初始mst的权值和
            if(!vis[u][v] && !vis[v][u]) ans+=sum;
            else ans+=(sum-mp[u][v]+min(w,dp[u][v]));
        }
        printf("%.4f\n",ans/q);//
    }
    return 0;
}
