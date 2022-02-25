#include<cstdio>
#include<cstring>
#define N 500100
int head[N],askHead[N],cnt1,cnt2,fa[N],vis[N],ans[N],visq[N];//ans用来存储lca的结果 visq判断询问关系lca是否被计算
struct Node{
    int to,next;
}edge[N<<1];
struct Ask{
    int num,to,next;
}ask[N<<1];//ask 用来构造 询问lca的边集关系
/*
tarjan离线算法,离线是指在一次遍历中把所有的lca询问一次性解决
时间复杂度为O(n+m),n为所有点的个数,m为所有lca询问的边集个数
*/
/*
这里只是借用了并查集的路径压缩思想,和并查集的集合并思想没什么关联,
在find路径压缩时去记录x与y结点最近的那个由x转折到访问y结点路径的祖先结点
*/
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);//在find时,路径压缩,使得下一次查找O(1)时间内 返回其lca结点
}

void addEdge(int from,int to){
    edge[cnt1]=(Node){to,head[from]};
    head[from]=cnt1++;
    edge[cnt1]=(Node){from,head[to]};
    head[to]=cnt1++;
}

void addAsk(int num,int from,int to){
    ask[cnt2]=(Ask){num,to,askHead[from]};
    askHead[from]=cnt2++;
    ask[cnt2]=(Ask){num,from,askHead[to]};
    askHead[to]=cnt2++;
}

void init(int n){
    memset(head,-1,sizeof(head));
    memset(askHead,-1,sizeof(askHead));
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

//O(n+m)
void dfs(int u){
    int v;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){//访问所有u子节点v
        v=edge[i].to;
        if(!vis[v]){
            dfs(v);
            fa[v]=u;//v点访问完后,回溯时 使得其fa结点指向父亲结点,这样在求解lca,调用find时 会不断向上跳到其lca转折结点,最终记录其祖先结点
        }
    }
    for(int i=askHead[u];i!=-1;i=ask[i].next){//访问所有和u有询问关系的v
        v=ask[i].to;
        /*
        如果查询边集中v结点已被访问过,并且这个lca询问对应的下标是没被解决的,那么lca(u,v)=find(v),
        1.这里若u、v是分布在lca的两边时,v结点find时会连续向上跳到由v结点发生转折进而去访问u结点的最近转折点,
        也就是lca(u,v),这里不会重复计算find,因为第一次访问u结点时,v是还没被访问,第二次访问v时才会计算find lca,
        而作为树(连通无回路)是不会再次访问u结点的,因此不会重复计算lca;
        2.如果v结点本身就是u结点的lca,那么这时v结点必然还没有回溯,也就是fa[v]=v,那么find(v)就等于v,即lca(u,v)=v;
        但是当回溯到v结点时,以v结点作为询问关系中的起始点时,这里lca(u,v)会被重复计算一次，为了避免重复的find操作,
        因此设置visq用来记录询问关系是否被解决避免重复find
        */
        if(vis[v] && !visq[ask[i].num]){
            ans[ask[i].num]=find(v);
            visq[ask[i].num]=1;//这里lca询问边集只会被计算一次,不会重复计算
        }
    }
}

int main(){
    int n,m,s,x,y;
    scanf("%d%d%d",&n,&m,&s);
    init(n);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    for(int i=0;i<m;i++){
        scanf("%d%d",&x,&y);
        /*
        构造双向边,因为实际dfs时所访问到lca(x,y)关系中的x点时,y点可能还没有访问,这时如果只有x指向y的边,那么就无法计算lca(x,y)
        因此询问边集也需要构造一条从y指向x的边,等访问到y时,x刚好访问过,这是去计算lca(x,y)
        */
        addAsk(i,x,y);
    }
    dfs(s);
    for(int i=0;i<m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
