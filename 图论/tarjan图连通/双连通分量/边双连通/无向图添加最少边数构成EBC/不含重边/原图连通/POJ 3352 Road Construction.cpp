#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;
//ac 类比tarjan求解SCC做法 16ms
/*
相关概念:
无向图因为都是双向边,所以不区分出度入度,统一只计算点的度.
1.边双连通图:若一个无向图中的去掉任意一条边,都不会改变此图的连通性,
即不存在割边/桥,则称作边双连通图(Edge Biconnected Graph-EBG).
2.边双连通分量:一个无向图中的每一个极大边双连通子图称作此无向图的边双连通分量(Edge Biconnected Component-EBC).
3.边双连通分量可以只有一个点.
4.边双连通分量就是求解无向图中的含点数极大的环,就是求解无向图中各个可能的最大环,即:极大相并连和极大相交叉的环,
但是和欧拉回路没关系,欧拉回路是指经过图中所有边一次还能回到起点,这个是要经过图中的所有边,它侧重的是所有边,而不是极大点数的子环.

性质定理:
1.割边/桥的两个端点必定分别属于原图的两个边双连通分量(ebc),一旦删除了桥,
这两个边双连通分量必定断开,原图就不连通了.但是如果在两个本身没有直接连边的ebc
之间再添加一条边,本身连接这两个ebc的桥就不再是桥了,因为删掉原先的桥,这两个ebc间还有边,
2个ebc间仍连通,原图仍旧是连通的.那么使得原图成为EBG的最少添边必然是在各个度为1的ebc间(缩点树-叶子节点)添加.
2.因为无向图(若不连通,各个连通子图同理)各个边双连通分量(EBC)中的点都不会有重复,
所以无向图中按照EBC缩点剩下的连边都是割边,即删除任一条边都会导致原图不连通,
所以缩点所得到必然是一棵无向树(或多棵无向树即森林).
对比点双连通分量因为同一点可作为各个PBC中的点,所以PBC问题一般不讨论缩点.
3.对于一棵无向树,我们要使得其变成边双连通图,需要添加的边数 == (树中度数为1的点的个数+1)/2.
树中度数为1的点实际就是叶子节点.要保证连通性就必须有度,度已为1,不能再有边连接,显然叶子节点.
这个添加的边一定是加在叶子节点间,而且要想最少,最后可能个别叶子节点间刚好没有边,这样就是最少加边数.
4.在一个边双连通图(EBG)中任意两点间都至少有两条路径.对于无向图按照ebc缩点后的树加最少边成为EBG,
这个EBG任意两点间只有2条路径,这时加边数就是最少的.
5.是边双连通分量并不一定是点双连通分量,是点双连通分量一定是边双连通分量(因为删除任意点自然包括了删除任意边).
6.无向图ebc缩点后所形成的无向树的树边都是原无向图中的桥,所以原图中桥的个数就等于树的边数=ebc_cnt-1

注意:
1.这里树中度数为1的点的个数如果为偶数,那么偶数+1为奇数,除2除不尽,不需处理,本身这个结果就是
向下取整的,列如1-2,1-3,1-4,1-5,4个叶子节点"2,3,4,5",选择在叶子节点间添加2条边,就可使其变成边双连通图.
而实际度为1的节点个数为4,(4+1)/2=5/2=2 int除法本身就是向下取整的,结果也正确.
这个最少加边数画一画就能理解,证明暂时不知.
2.是边双连通图一定是强连通图,是强连通图不一定是边双连通图(SCC中删除一条边,虽然点并没有被分割,
但因为是有向边,删掉后有些点之间并不可达).
*/

/*
题意:n个旅游景点,m条道路,现在有施工单位正在某些道路施工,
可能会导致游客不能从两景点间通过,现在问至少再修建多少条
新道路才能使得施工单位在道路施工不影响游客在任意两景点游览.
释义:一个无向图(无重边并且一定连通),最少要添加几条边才能使得图中没有割边.
给你一个连通的无向图,最少在该图中添加几条边,能使得该图变成边双连通图.
最少添加几条边才能使得图中任意两点之间至少有两条路径.
此题原图保证一定是连通的.
链接:http://poj.org/problem?id=3352
思路:可以类比tarjan求解SCC的做法,需要注意的是对于已经遍历过的点除了判断
是否在栈中,还不能是当前节点的前驱节点.最后只要判断dfn[u] == low[u]依次出栈.
求解出EBC后缩点计算每个点的度,统计出度为1的点的个数ans,结果就为(ans+1)/2.
含重边的做法同样适用不含重边的做法,建议不管含不含重边,都按含重边的做法对待.

这里网上有一种错误做法,是跑一遍无向图的tarjan求出每个点的low值,最后根据,如果两个点
的low值相同则它们在同一边双连通分量里(EBC),这里如果EBC中只有一个环是没问题的,但是对于
本身有2个环的EBC,因为low[u]值再有回边时记录的是dfn[v]的值(即使记录low[v],因为dfs深度优先,
这个v点的low可能还并没有更新),导致两个环中low值不一样,而错误将2个环分开,各自作为一个EBC.
*/

int n,m,dfn[N],low[N],num,cnt,head[N],block[N],ebc_cnt,de[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}
//因为是无向图,如果图本身是连通的,那么一次dfs就能分离出所有ebc,而后续dfn次序较小的在分离ebc时,
//如果有连向已分离出的ebc的点的重边时,那么low值本身就比已分离点dfn小,也不会出问题,如果本身没有重边,
//那么就根本不会在访问到已分离出ebc的点.所以可以不设置in判断是否在栈中.
//如果原图不连通,那么一个连通分量ebc分离完,在分离另一个连通分量的ebc也不会遍历到之前已经分出ebc中的点.
//所以dfs对于dfn[v]!=0,是不需要判断in[v]在栈中,但是对于有重边的情况在逻辑上觉得还是应该加上in[v]的判断
//(当然不加结果也是对的,因为low值本身就比已分离的ebc的dfn小),没有重边是可以完全不加的
void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
        }
        else if(v!=fa)//不能是前驱节点,因为这样会导致 u-v这样的单边图单独成一个EBC,但实际并不是EBC,实际u、v各成一个EBC
            low[u]=min(low[u],dfn[v]);//这里low[u]=min(low[u],low[v])也是可以的
    }
    if(dfn[u] == low[u]){//dfn和low相等时,说明没有回边回到时间戳更早的节点,开始弹栈 构成一个EBC
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
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
    //此题其实保证了原图是连通的 直接dfs(1,-1),事实上这种做法也只适用原图连通的情况
    //对于原图不连通的情况还需考虑度为0被孤立的点,ans要加2.
    dfs(1,-1);
    //对原图连通且本身就是EBG的情况无需 特判因为本身也没有度为1的点.原图不连通还是要特判的 因为要考虑度为0的情况
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
//ac tarjan求解割边+并查集 32ms
//因为原无向图各个割边所连接一定是2个独立出来的边双连通分量(ebc),
//所以可以把除割点外的边上的点用并查集合并为一个集合,这些独立出的集合就是各个ebc,
//缩点后的点的度的计算可以用之前的割边来计算,每个割边两端点de[find(u)]度都加+1
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
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
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])//记录割边 用来缩点计算缩点后的树上点的度
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
//ac tarjan求解割边+并查集 32ms 这里将并查集祖先节点 再存入pos[find(u)]=++ebc_cnt,可以计算ebc的数目,给每个ebc编号
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;
//ac 32ms
int n,m,fa[N],dfn[N],low[N],num,cnt,cut_num,head[N],ebc_cnt,de[N],pos[N];

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
            if(dfn[u]<low[v])
                cut_edge[++cut_num]=Edge(u,v);
            else
                fa[find(u)]=find(v);
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
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++){
        int x=find(i);
        if(!pos[x]) pos[x]=++ebc_cnt;
    }
    for(int i=1;i<=cut_num;i++){
        u=cut_edge[i].to;
        v=cut_edge[i].next;
        de[pos[find(u)]]++;
        de[pos[find(v)]]++;
    }
    for(int i=1;i<=ebc_cnt;i++){//只判断ebc的数目
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);
    return 0;
}
*/

