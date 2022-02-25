#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
//ac 148ms
/*
题意:给定一个n个点m条边有向图,每个点有一个权值,
求一条路径,使路径经过的点权值之和最大.你只需要求出这个权值和.
允许多次经过一条边或者一个点,但是,重复经过的点,权值只计算一次.
权值没有负值.
链接:https://www.luogu.com.cn/problem/P3387
思路:因为点可重复经过,权值只计算一次,所以可考虑scc缩点作为一个整体权值考虑.
可以dfs dp遍历子路径最大权值和累加到父节点,
但是原图中有环,可以通过tarjan缩点将图转换成DAG,
再在DAG上进行树形dp记录各个SCC中最大的权值和.
*/

/*
树形dp之前要缩点原因:
(并不是为了通过缩点来达到缩小dp点的个数来缩短时间复杂度,
因为这样也避免不了tarjan缩点本身O(V+E)的时间)
对于图
1->2->3->1,1->4->5
因为原图中有环1->2->3->1,直接dp的话,对于遍历到1-2->3
3->1 再回到1点时,虽然1点也遍历过了,但是为了能遍历1->4->5更多路径的点权和
显然对于重复遍历的点还是要继续遍历下去,但是这样当回到1点时,
1->2->3这个原先遍历过的环也无法避免它又会遍历,然后不断这样无限递归,dfs不能结束.
如果先缩点成有向无环图(DAG),这样对于像1->2->3->1
这样的环的点权和会缩成一个点(x)的点权和,这样就会图就会变成x->4->5,
这样就能满足题目要求"允许多次经过一条边或者一个点,重复经过的点,权值只计算一次."
既能遍历完1->2->3->1这样的环不进入死递归,还能回到1点将1->4->5这一条路径遍历到.
如果1还连接着1->6->7这样的单链,则dp时对于遍历完缩点x,在x->4->5 x->6->7会选择,
权值和较大的去遍历,因为4->5 6-7遍历时都没有回边再去遍历别的路径,这能选择一条路径.
事实上就是通过缩点对于强连通分量构成的环我们直接当成了一个独立的点(点权是环中所有节点点权和),
这样就不必通过再回到遍历过的初始点 去遍历别的路径,因为这样无法避免原先遍历过的环,
而缩点消除了环的影响,直接将原图变成了单链,通过遍历缩点一次性遍历完了环中所有点,
紧接着就可以遍历别的分支的点.
*/

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int val[N],sum[N];
stack<int> s;
bool in[N];
int block[N],id;
int a[M],b[M];
int dis[N];//dis[u]代表以u节点为父亲的子路径中单向路径最大的权值和

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){//O(N+E)
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=true;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++id;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            sum[id]+=val[v];
            s.pop();
        }while(v != u);
    }
}

void dp(int u){//O(n) n缩点的个数
    dis[u]=sum[u];
    int v,maxWe=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        //深度优先遍历子树路径 先统计子树的路径权值最大和,如果这个分支访问过直接比较dp[v]的结果和之前是否一样
        //循环里先dp过的点有可能是单向链中间的点v,后遍历的是单向链前面的点u,当从u再遍历到v时直接累加v点后链的点权值和就好
        //可以理解为记忆化搜索.
        if(!dis[v]) dp(v);
        maxWe=max(maxWe,dis[v]);//选择权值和较大的子树作为路径
    }
    dis[u]+=maxWe;//将子树权值和累加到父亲结点上
}

int main(){
    int n,m;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a[i],&b[i]);
        addEdge(a[i],b[i]);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    memset(head,-1,sizeof(head));
    cnt=0;
    for(int i=1;i<=m;i++){
        if(block[a[i]] != block[b[i]])//两个结点对应的强连通分量编号不同,则可认为是两个缩点之间有连接
            addEdge(block[a[i]],block[b[i]]);//缩点重新构图,所构成的图没有SCC,即有向无环图(DAG),这是进行树形dp的先决条件
    }
    int ans=0;
    for(int i=1;i<=id;i++){//缩点有可能仍旧不是连通的,个别缩点是孤立的,因此要对每个还没遍历到的点进行dp
        if(!dis[i]){
            dp(i);
            ans=max(ans,dis[i]);
        }
    }
    printf("%d\n",ans);
    return 0;
}

/*
//不考虑在DAG上应用最短路算法,因为没有指定起点,该题起点可以是任意的.
//ac 102ms
//当然对于有向无环图DAG有特定算法能够遍历整张图的所有路径,
//可以考虑拓扑排序,从所有入度为0的点开始遍历,这样只需一次就能
//将这张图的所有路径遍历完毕.在这个遍历路径的过程中进行dp.
//dis[u]代表以u节点为终点的可到达的单向路径中最大的权值和
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int val[N],sum[N];
stack<int> s;
bool in[N];
int block[N],id;
int a[M],b[M];
int dis[N],inde[N],ans;

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){//O(N+E)
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=true;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++id;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            sum[id]+=val[v];
            s.pop();
        }while(v != u);
    }
}

void topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i]){
            dis[i]=sum[i];
            Q.push(i);
        }
    }
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        ans=max(ans,dis[u]);
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            dis[v]=max(dis[v],dis[u]+sum[v]);
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int n,m;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a[i],&b[i]);
        addEdge(a[i],b[i]);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    memset(head,-1,sizeof(head));
    cnt=0;
    for(int i=1;i<=m;i++){
        if(block[a[i]] != block[b[i]]){//两个结点对应的强连通分量编号不同,则可认为是两个缩点之间有连接
            addEdge(block[a[i]],block[b[i]]);//缩点重新构图,所构成的图没有回边,不会构成环,即有向无环图(DAG),这是进行树形dp的先决条件
            inde[block[b[i]]]++;
        }
    }
    topSort();//初始将所有入度为0的点加入,就能将DAG中所有路径遍历完毕
    printf("%d\n",ans);
    return 0;
}
*/
