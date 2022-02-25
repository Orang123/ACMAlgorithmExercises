#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500100
using namespace std;
/*
https://www.cnblogs.com/ivanovcraft/p/9019090.html
树链剖分 可分为 重链剖分、长链剖分、Link/cut Tree 的剖分(也叫“实链剖分”),一般情况下,树链剖分指重链剖分.
重链剖分可以将树上的任意一条路径划分成不超过O(logN)条连续的链,链(本身得是轻链)上所有点的LCA为重链的一个头顶端点.
重链剖分还能保证划分出的每条链上的节点DFS序连续.

log N条重链这里应该是需要相关的数学方法去证明的,从代码来看不太好分析.

重儿子(重子节点):父亲节点的所有儿子中子树结点数目最多(size最大)的结点;
轻儿子(轻子节点):父亲节点中除了重儿子以外的儿子;
重边:父亲结点和重儿子连成的边;
轻边:父亲节点和轻儿子连成的边;
重链:由多条重边连接而成的路径;
轻链:由多条轻边连接而成的路径;
*/
/*
fa[x]表示节点x在树上的父亲.
dep[x]表示节点x在树上的深度.
siz[x]表示节点x及其子树的节点总个数.
son[x]表示节点x的重儿子.
top[x]表示节点x所在重链的顶部节点(深度最小).
dfn[x]表示节点x的DFS序,也是其在线段树中的编号.dfn[u]=++num,代表第一次遍历u结点的下标编号是num
rnk[x]表示 DFS 序所对应的节点编号，有rnk[dfn[x]]=x.
*/
int head[N],fa[N],dep[N],dfn[N],rnk[N],top[N],son[N],siz[N],cnt,num;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

//遍历这棵树,计算每个结点的深度、父节点以及重儿子还有每个节点构成的子树的总节点个数.
void dfs1(int u){
    siz[u]=1;//这个节点本身还要计算进去
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u]){
            dep[v]=dep[u]+1;
            fa[v]=u;
            dfs1(v);
            /*
            经过一条轻边时，所在子树的大小至少会除以二,因为经过轻节点必然是存在重节点,
            而重节点siz个数大于轻节点,而此时儿子的个数至少2个,所以重节点一定大于
            父节点siz的二分之一,那么轻节点siz一定小于父节点siz的二分之一.
            */
            siz[u]+=siz[v];//累加子节点所构成的子树节点个数来计算父节点所构成子树总结点个数
            if(siz[v]>siz[son[u]])//记录子节点中子树节点个数最多的子节点作为父节点的重儿子
                son[u]=v;
        }
    }
}

//遍历这棵树,记录遍历时的dfs序和重链的顶部节点
void dfs2(int u,int k){
    dfn[u]=++num;
    rnk[num]=u;
    top[u]=k;
    if(!son[u])//如果没有重儿子说明该点为叶子节点,结束
        return;
    //父节点和它的重儿子处于同一条重链,所以重儿子所在重链的顶端点还是k
    dfs2(son[u],k);//优先遍历重儿子和重边,最后重链的DFS序就会是连续的
    //再遍历轻节点和轻边
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u] && v!=son[u])//避开父节点和重儿子
            dfs2(v,v);//轻链的顶端点就是从这个点开始的重链的顶端点,top[v]=v,也就是轻节点本身
    }
}

/*
利用重链的top顶端节点来向上跳跃求解lca,这样也可以减少最终跳跃的总步数,
相比较线性跳跃一次只跳一层深度还是要快,但是相比数据量较大时的倍增跳跃还是要慢一些.
*/
int lca(int x,int y){
    while(top[x]!=top[y]){//不断向上跳重链,当跳到同一条重链上时结束
        if(dep[top[x]]>dep[top[y]])//向上跳重链时需要先跳所在重链顶端深度较大的那个,而不是重链顶端深度较小的那个,否则不是"最近的"公共祖先
            x=fa[top[x]];
        else
            y=fa[top[y]];
    }
    return dep[x]<dep[y]?x:y;//比较最终同一重链上的2节点,深度较小的那个是lca
}

int main(){
    int n,m,s,u,v;
    scanf("%d%d%d",&n,&m,&s);
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    dfs1(s);//s为根节点
    dfs2(s,s);//s为遍历的初始根节点,且其实第一条重链的顶部结点,因此k=s.
    while(m--){
        scanf("%d%d",&u,&v);
        printf("%d\n",lca(u,v));
    }
    return 0;
}
