#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 75000
#define M 100100
#define MOD 1000000007
using namespace std;
//kruskal重构树+RMQ-st表 ac 2573ms
/*
kruskal重构树相关概念:
在跑Kruskal从小到大加边时,每一次加边会合并两个集合,
我们可以新建一个点,点权为加入边的边权,
同时将两个集合的根节点分别设为新建点的左儿子和右儿子.
然后我们将两个集合根节点都指向新建点,和新建点合并成一个集合,将新建点设为根.
不难发现,在进行n-1轮之后我们得到了一棵恰有n个叶子节点(原先的n个点)的二叉树,
同时每个非叶子节点(n-1个,有点权)恰好有两个儿子.这棵树就叫kruskal重构树.这棵
二叉树并不是满二叉树.可以发现越靠近二叉树中的根节点,对应的点权越大,点的编号也越大,
对应的两点点最大边权也就越大.实际构造时先构造出儿子节点再依次构造出父亲节点.
*/

/*
题意:给定一个包含n个节点和m条边的无向连通图,没有自环,可能有重边,每条边有一个权值w.
你的任务是回答q个询问,每个询问包含两个正整数s和t表示起点和终点,
要求寻找从s到t的一条路径,使得路径上权值最大的一条边权值最小.
对于100%的数据,n<=70000,m<=100000,q<=10000000,w<=1000000007
输入数据是在线的,输入压缩方法是:读入4个整数,每次询问调用以下函数生成u和v:
int A,B,C,P;
inline int rnd(){return A=(A*B+C)%P;}
每次询问时的调用方法为:u=rnd()%n+1,v=rnd()%n+1;
输出共一行一个整数,表示所有询问的答案之和模10^9+7的值。
链接:https://loj.ac/problem/137
思路:还是求解最小瓶颈路中的最大边权,还是得通过求解mst求解最小瓶颈路.有重边,用链式前向星.
因为n<=70000,prim+dp的做法maxLen[N][N]开不了这么大,而k<=10^7,如果用lca,复杂度klog(N),
1s也会TLE.那么我们可以用st表的O(1)查询的优势,将lca转化为RMQ st表解决,但是这个只能求解出
树上任意两点之间的最近公共祖先(lca)的编号,无法求解出路径上的最大边权,那么我们可以在kruskal
时构造kruskal重构树,这样最终构造出的二叉树的非叶子节点上的点权就是原先任意两点间的最大边权.
这样路径上的边权最大的问题,就转化为只是求解树上任意两点lca编号点权的问题,那么就可直接通过lca转化为
RMQ-st表来实现.而之所以不在RMQ 区间dp计算st表时仿照倍增算法,dfs时去设置一些max辅助数组去计算路径最大值,
是因为首先这个lca问题已经从一个树上问题转化为RMQ st表问题了,也就是说在RMQ时已经完全脱离了树上(dfs)的这个概念了,
因为当即使有点的概念的时候,无法关联到点和点之间边权的概念,从而也无法设置别的max辅助数组去计算最大边权.
*/

/*
kruskal重构树所新构造的点个数因为mst中边的个数(n-1),所以重构mst中点的个数n+n-1=2*n-1,
而且对应将lca问题转为RMQ问题,需要构造的深度遍历访问序列总长度应为点数的二倍即2*(2*n-1)-1
也就是4*n,即dfn,st,lg数组长度都为N<<2.
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
    int num=n,x,y;//num要从n开始,因为新加入的点编号从n+1开始 val[num]
    for(int i=0;i<m;i++){//因为是按照边权从小到大顺序加边的,所以最终的kurskal重构树越靠近根节点的新建点的点权越大
        x=find(edge1[i].u);
        y=find(edge1[i].v);
        if(x!=y){
            num++;
            fa[x]=fa[y]=num;//将x、y两个集合的根节点分别设为新建点的左儿子和右儿子,将新建点设为根,将三个集合合并为一个集合
            val[num]=edge1[i].w;//记录这条边的权
            addEdge(x,num);//原先的x、y结点的根节点分别作为新建点的左右儿子
            addEdge(y,num);
            /*
            记录原先x结点到y结点之间的边权, 再不断构造新建点时,实际树的深度也在被不断抬高(对应的边权也是不断增大的),
            不断地靠近最终的根节点,因此两点之间的最大边权就会越来越大
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
        //最小生成树上两个点之间的简单路径上边权最大值=Kruskal重构树上两点之间的LCA点的权值.
        ans=(ans+val[lca(dfn[u],dfn[v])])%MOD;
    }
    printf("%d\n",ans);
    return 0;
}
