#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20100
#define M 100100
using namespace std;
//ac 114ms
/*
相关概念:
割点:是针对无向图而言,没有单向连通,强连通的概念,对于一个无向图,如
果把一个点删除后这个图的极大连通分量数增加了,那么这个点就是这个图的割点(又称割顶).
连通分量:无向图G的极大连通子图称为G的连通分量(Connected Component).

重边不会影响求解割点的问题,因为即使有重边,割点只要删除点与点相连的所有边都会断开,
有无重边并不会影响割点的判断.也不会影响点双连通的问题.
*/

/*
题意:给出一个n个点,m条边的无向图,求图的割点.
链接:https://www.luogu.com.cn/problem/P3388
思路:tarjan求解无向图中的割点.
*/

struct node{
    int to,next;
}edge[M<<1];//无向图有双向边 因此M*2
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int root;//每次dfs时的第一个结点 即:root根节点
bool cut[N];//判断是否割点

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){//O(E) E为边
    dfn[u]=low[u]=++num;
    int v,son=0;//son代表根节点的子树 只在判断root时生效
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){//如果是分支的尾节点,则这个节点肯定不是割点,也不会进入这个if
            dfs(v,u);
            if(u == root)//or fa == -1
                son++;//每次root结点每访问一个未访问的点时 子树个数++,因为是无向图,有些点可能会被之前的子树访问过
            low[u]=min(low[u],low[v]);//若v能回到较早次序的结点那么u也可以回到
            /*
            当u不是根节点时,只要它有一个子节点所能回到的次序大于等于它的访问编号,
            说明不通过u结点,v无法回到u之前的结点,说明u是割点,
            这里当dfn[u]<low[v]时,v只能回到u之后遍历的节点,那么删除u必然使得u v之间的节点与u断开.
            当dfn[u]==low[v]时,这就说明v点能回到u点,那么删除u点,也必然使得u v之间的节点与u断开.
            也就是说若v能回到u,那么u v 之间的节点x都不是割点,因为low[x]=dfn[u],对于x的父亲dfn[fa]>low[x]
            这里若不判断u==root,若是root结点,其只有一个子树,也会满足这个条件,但此时删除根节点,
            因为只有一棵子树,root节点后单链仍然是连通的.
            */
            if(u != root && dfn[u]<=low[v])//这里某个子树分支 不是割点,但是对另一个子树会是割点
                cut[u]=true;//不宜在这里统计割点的数目,因为u结点有可能会是 多棵子树的割点
            /*
            当u为根节点且其有2棵子树时,说明之前先访问的第一棵子树并没有遍历到第二棵子树的节点,
            所以2棵子树是以root结点作为媒介连接的,删除这个点才会导致2棵子树不连通.
            这里不能放在for外面,因为删掉根节点与根节点相连的所有分支都会成为一个连通分量,
            所以对于每个分支都要计算器++,如果只是判断该点是否是割点,是可以放在for循环外面的.
            这里son==1,只有一个分支是不记录的,但是当son>=2时,所记录的连通分量实际少记录了一个,
            所以最后所有结果都得+1.
            */
            else if(u == root && son>=2)
                cut[u]=true;
        }
        /*
        这里对于u点连向已遍历过的父亲节点fa,虽然构成了环循环,但是删掉父亲节点fa后,
        仍然会使得u与fa分离,所以对于u的连边,若v是父亲节点,则不需要更新low[u],回溯时,
        dfn[u]<low[v]直接判断u父亲节点为割点就好.当然去掉if(v!=fa),因为if(!dfn[v])的判定里,
        low[u]=min(low[u],low[v]),low[v]<=dfn[v],结果也不会错.
        */
        else if(v!=fa)
        /*
        这里不能是low[u]=min(low[u],low[v]),因为当low[u]为low[v]时,
        low[v]是会比dfn[v]小的,那么当回溯到v点,判断v点是割点时,
        是用dfn[u]<=low[v],而这时,low[v]就会比dfn[u]小,因为
        low[u]=min(low[u],dfn[v]),low[u]取了较小的low[u],但是判断时,
        是用dfn[u]判断的,此时dfn[u]可能是比low[v]小于等于的,但是因为
        当时low[u]取了low[v]会导致dfn[u]>low[v]会出错.
        */
            low[u]=min(low[u],dfn[v]);
    }
}
/*
//另一种求解删除割点后剩余连通分量的写法
void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            dfs(v,u,k);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v])
                cut[u]++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(fa < 0) cut[u]--;
}
*/

int main(){
    int n,m,a,b;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&a,&b);
        addEdge(a,b);//构建无向图,双向边,才能满足连通性
        addEdge(b,a);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){//原图不一定是连通图,可能是分散的,因此得对未遍历的每个点进行dfs
            root=i;//根节点为第一个访问的i结点
            dfs(i,-1);//第一次访问root时 不存在父亲结点的概念 设为-1
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(cut[i])
            ans++;//统计割点的个数
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        if(cut[i])
            printf("%d ",i);//输出割点的编号
    printf("\n");
    return 0;
}
