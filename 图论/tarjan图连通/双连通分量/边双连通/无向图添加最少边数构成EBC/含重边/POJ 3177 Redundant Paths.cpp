#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;
//ac 0ms tarjan类比求解scc来求解ebc
/*
题意:一个无向图(含重边),最少要添加几条边才能使得图中没有割边,成为边双连通图.
同一对字段之间可能已经有多个路径(含重边).
链接:http://poj.org/problem?id=3177
思路:tarjan类比求解scc求解ebc.只不过对于重边也要能使其回到父亲节点,
进而更新low[u]=min(low[u],dfn[v]).
含重边的做法同样适用不含重边的做法,建议不管含不含重边,都按含重边的做法对待.
*/

int n,m,dfn[N],low[N],in[N],num,cnt,head[N],block[N],ebc_cnt,de[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}
//因为是无向图,如果图本身是连通的,那么一次dfs就能分离出所有ebc,而后续dfn次序较小的在分离ebc时,
//如果有连向已分离出的ebc的点的重边,那么low值本身就比已分离点dfn小,不加in判定也不会出问题,如果本身没有重边,
//那么就根本不会在访问到已分离出ebc的点.所以可以不设置in判断是否在栈中.
//如果原图不连通,那么一个连通分量ebc分离完,在分离另一个连通分量的ebc也不会遍历到之前已经分出ebc中的点.
//所以dfs对于dfn[v]!=0,是不需要判断in[v]在栈中,但是对于有重边的情况在逻辑上觉得还是应该加上in[v]的判断
//(当然不加in判定结果也是对的,因为low值本身就比已分离的ebc的dfn小),没有重边是可以完全不加的
void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,i);//这里记录的是父亲节点那条连边的编号
            low[u]=min(low[u],low[v]);
        }
        else if(in[v] && (i^1)!=fa)//i^1是其反向边只要不是之前父亲节点那条边就可以,因为对于有重边这里需要将父亲和子节点看做一个ebc
            low[u]=min(low[u],dfn[v]);//这里low[u]=min(low[u],low[v])也是可以的
    }
    if(dfn[u] == low[u]){//dfn和low相等时,说明没有回边回到时间戳更早的节点,开始弹栈 构成一个EBC
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=ebc_cnt;//设置当前点所属的ebc的编号
        }while(v!=u);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    //此题其实保证了原图是连通的 直接dfs(1,-1)
    dfs(1,-1);
    for(int i=0;i<cnt;i+=2){//因为是双向边+2,两端点度都+1
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            de[block[u]]++;
            de[block[v]]++;
        }
    }
    for(int i=1;i<=ebc_cnt;i++){
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);//对于原图单链的情况,只需添加一条首位相接的边即可成为边双连通图.
    return 0;
}
/*
含有重边1-2 有两条,这个不知为什么tarjan+并查集这种做法不判重边,
这个样例输出2,实际只需添加1条边,但是POJ却能通过.
input
4 4
1 2
1 2
1 3
1 4
output
1
*/
/*
//ac 0ms tarjan求解割边i^1!=father考虑重边构成的ebc+并查集构造ebc
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;

int n,m,fa[N],dfn[N],low[N],num,cnt,cut_num,head[N],ebc_cnt,de[N];

struct Edge{
    int to,next;
    Edge(int to=0,int next=0):to(to),next(next){}
}edge[M<<1],cut_edge[M];

void addEdge(int from,int to){
    edge[cnt]=Edge(to,head[from]);
    head[from]=cnt++;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int u,int father){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])//记录割边,满足dfn[u]<low[v]
                cut_edge[++cut_num]=Edge(u,v);
            else
                fa[find(u)]=find(v);//这里u和v未合并之前必然是不同集合,因为tarjan 这里点都是未遍历的.
        }
        else if((i^1)!=father)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    for(int i=1;i<=cut_num;i++){
        u=cut_edge[i].to;
        v=cut_edge[i].next;
        de[find(u)]++;//这里就不考虑并查集祖先节点的编号,没有去求解ebc的个数,最后暴力n个点的度都判一遍
        de[find(v)]++;
    }
    for(int i=1;i<=n;i++){//暴力每个点都判,因为不知道具体每个ebc集合祖先根节点的编号
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);
    return 0;
}
*/


/*
//ac 16ms tarjan求解割边bridge[u][v]过滤判重边+并查集构造ebc
//这个不用bridge[u][v]记录边数,不判重边,POJ不知为何也过了,但上面这组数据,它的输出应该是1,而这个做法输出2,就好奇怪
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;

int n,m,fa[N],dfn[N],low[N],num,cnt,cut_num,head[N],ebc_cnt,de[N],bridge[N][N];

struct Edge{
    int to,next;
    Edge(int to=0,int next=0):to(to),next(next){}
}edge[M<<1],cut_edge[M];

void addEdge(int from,int to){
    edge[cnt]=Edge(to,head[from]);
    head[from]=cnt++;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int u,int father){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v] && bridge[u][v] == 1)//记录割边,满足dfn[u]<low[v]还得满足没有重边,即边数bridge[u][v]=1
                cut_edge[++cut_num]=Edge(u,v);
            else
                fa[find(u)]=find(v);//这里u和v未合并之前必然是不同集合,因为tarjan 这里点都是未遍历的.
        }
        else if(v!=father)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
        bridge[u][v]++;
        bridge[v][u]++;
    }
    dfs(1,-1);
    for(int i=1;i<=cut_num;i++){
        u=cut_edge[i].to;
        v=cut_edge[i].next;
        de[find(u)]++;//这里就不考虑并查集祖先节点的编号,没有去求解ebc的个数,最后暴力n个点的度都判一遍
        de[find(v)]++;
    }
    for(int i=1;i<=n;i++){//暴力每个点都判,因为不知道具体每个ebc集合祖先根节点的编号
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);
    return 0;
}
*/
