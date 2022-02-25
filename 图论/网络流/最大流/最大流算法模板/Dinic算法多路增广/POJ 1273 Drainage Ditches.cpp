#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;
int cnt,n,m,head[N],d[N];
//ac 0ms Dinic多路增广求解最大流 链式前向星存边
/*
相关概念:
1.Dinic算法:时间复杂度O(V^2*E)
Dinic算法是网络流最大流的优化算法之一,先BFS对原图进行分层,
设源点的层数为0,那么一个点的层数便是它离源点的最近距离,然后用DFS求增广路.
时间复杂度是O(V^2*E)(需要严格地证明),相比EK的O(V*E^2)还是快得多了,因为边数要远远多于顶点数.
Dinic算法最多被分为n个阶段,每个阶段包括建层次网络和寻找增广路两部分.Dinic算法的思想是分阶段地在层次网络中增广.
它与最短增广路算法(EK)不同之处是;最短增广路每个阶段执行完一次BFS增广后(每次只会增广一条路径),要重新启动BFS从
源点st开始寻找另一条增广路;而在Dinic算法中,每次BFS过程就可以实现多次增广,即BFS构建层次网络,DFS完成多路增广,
层次网络指的是多条长度相同的增广路,而且是在本次BFS中最短的增广路,参考点是第一次到达汇点的那条路径的长度,
之后到达汇点的增广路长度需与其一致.
Dinic在稀疏图上效率和EK算法相当,但在稠密图上效率要比EK算法高很多.
说明:在求解二分图最大匹配问题时,Dinic算法的时间复杂度是O(sqrt(V)*E).

2.Dinic 算法有两个优化：
(1).多路增广:每次找到一条增广路的时候,如果残余流量没有用完怎么办呢?我们可以利用残余部分流量,
再找出一条增广路.这样就可以在一次DFS中找出多条增广路,大大提高了算法的效率.
在应用了当前弧优化的前提下,对于每个点,我们维护下一条可以增广的边,而当前弧最多变化E次,
从而单轮增广的最坏时间复杂度为O(VE),最多只需V-1轮增广即可得到最大流.
(2).当前弧优化:如果一条边已经被增广过,那么它就没有可能被增广第二次.那么,我们下一次进行增广的时候,
就可以不必再走那些已经被增广过的边.
当前弧优化参考博客:https://www.cnblogs.com/floatiy/p/9457809.html
https://www.cnblogs.com/ticmis/p/13211009.html#_label3_0_3_2
https://oi-wiki.org/graph/flow/max-flow/  OI-Wiki
每次增广一条路后可以看做“榨干”了这条路,既然榨干了就没有再增广的可能了.但如果每次都扫描这些“枯萎的”边是很浪费时间的.
那我们就记录一下“榨取”到那条边了,然后下一次直接从这条边开始增广,就可以节省大量的时间.这就是当前弧优化
实现方式:先把链式前向星的head数组复制一份，存进cur数组,然后在cur数组中每次记录“榨取”到哪条边了.
当前弧优化存在问题:
//cur记录的边下标为当前i,因为i之前的边所构成的增广路可能存在残余容量为0的边,没必要再去增广了
//但这里如果是u的前驱节点路径里的残余容量较小,那么u点后如果有很多分支,可能这些分支的残余容量并不为0(没有被榨干),
//会使得cur数组只记录最后一个分支,这样若还有别的增广路访问u点,此时之前那些分支就无法分流,
//这次dfs就没能遍历之前bfs划分出的层次的增广路(最短相同长度的增广路),但这并不影响结果的正确性,本次dfs遗漏掉的增广路
//会在下次bfs时再次被划分出来,就是可能会多bfs几次,但这个当前弧优化对于大多数u点后分支残余容量为0的情况还是有很大的优化的,综合来看优化还是很高.
*/

/*
题意:m个池塘,n条水渠,每条水渠水的流向只能是一个方向,
每条水渠有个水流的速率,求水渠中从1点流向m点(溪流)的水
流的最大速率.
释义:m个点,n条有向边的网络,每条边有一定容量,求解1到m的最大流.
注意:输入会有重复边,即1->2 20 1->2 30,这样1->2实际容量为30,
因此要累加容量.
链接:http://poj.org/problem?id=1273
思路:Dinic算法求解最大流模板.
*/

struct node{
    int to,next,c;
}net[N<<1];//这里题目中说明了 最多有N(210)条水管,因为在构建网络时需要初始化反向弧,所以总共需要的最大边数为2*N

void addEdge(int x,int y,int c){
    net[cnt].to=y;
    net[cnt].c+=c;
    net[cnt].next=head[x];
    head[x]=cnt++;
}

//可搜索出多条长度相等的最短增广路 每次都搜索最短,
//会使得最终整体增广路的总边数最少,提高搜索效率
bool bfs(int s,int t){//构建层次网络(指的是相同长度的增广路构成的网络),层数就是最短增广路长度
    int u,v;
    queue<int> Q;
    //源点设置0,其余点设置-1,判断用dis[v]==-1,可避免使用!dis[v]使得源点再次入队
    memset(d,-1,sizeof(d));
    d[s]=0;//初始化起点长度为0,也避免重复访问 判断d[v]==-1
    Q.push(s);
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=net[i].next){
            v=net[i].to;
            /*
            该边必须是可行流,即残余容量大于0
            该点之前必须未被访问增广(d[v]==-1),对于某条路径上的较短路就可能已经先行更新了d[v],
            而对于这条路径上较长的增广路访问时,d[v]已不为-1
            */
            if(net[i].c>0 && d[v]==-1){
                //对于相同路径长度的增广路而言这里是通用的,因为可能d[v]只赋值了一次,
                //但是他们各个d[u]值都是一样的,因此在dfs时d[v]==d[u]+1仍旧是成立的
                d[v]=d[u]+1;
                //对于其它长度和本次第一次遍历到的这条增广路相同的增广路
                //不必再遍历了,因为d[v]已经等于d[u]加1了,不必重复遍历了,
                //最短长度是第一次遍历到汇点的增广路的长度,其余还没出队的点无需遍历,
                //若增广路长度是相同的,dfs时d[v]=d[u]+1.
                if(v == t) return true;
                Q.push(v);
            }
        }
    }
    //如果return false说明所遍历的所有路径里含有残余流量为0的边,
    //导致无法搜索到达汇点,不存在增广路
    return false;
}

//搜索增广路,累加残余容量作为最大流
//每次找增广路的时候,都只找比当前点层数多1的点进行增广(这样就可以确保我们找到的增广路是最短的).
int dfs(int u,int flow){
    if(u==m)
        return flow;
    int v,res=0,incf;
    for(int i=head[u];i!=-1;i=net[i].next){
        v=net[i].to;
        //对于反向弧,无需标记vis 避免其又返回u点dfs,因为有d[v]==d[u]+1限制
        if(d[v]==d[u]+1 && net[i].c>0){//多路增广
            incf=dfs(v,min(net[i].c,flow));//求出当前点为首的后续路径之中最小的残余容量
            if(incf>0){//incf 残余容量大于0代表搜索到增广路
                /*
                flow表示之前的前驱结点的边里面的最小残余容量.flow减去各个分支所能分走的最大流量
                这里最大流量指的是各个路径最小的残余容量.
                */
                flow-=incf;
                net[i].c-=incf;//正向边残余容量减少
                net[i^1].c+=incf;//反向边残余容量增加
                //res累加后面各个分支路径的最小残余容量,
                //返回结果给前面路径中结果作为所有路径分支总和的最小残余容量.
                res+=incf;
            }
            if(flow==0)//表示当前边的残余容量已为0,结束dfs 没有增广路可寻
                return res;
        }
    }
    /*
    剪枝 炸点优化 res==0表示
    对于d[v]!=d[u]+1是指那些在BFS时未能构建在当前层次的较长增广路(就是本次dfs并不打算作为增广路统计最大流的路径)
    在回溯时这个点以及之前的那些点也都被置为-1,为了避免从其余分支的点(与其长度相同的路径汇总到当前这个较长路的点上)
    也再次访问到这个并不是作为这次要更新的增广路而浪费时间.还有那些存在残余容量为0的路径,也需要标记d[u]=-1,这样就
    不会重复遍历这些存在残余容量为0的路径.
    */
    if(res==0)//不加这个剪枝,也能过,这个是当前弧优化的另一种方式.
        d[u]=-1;
    //把后面路径包括所有分支的最小残余流量累加作为新的总最小残余流量返回前面节点,
    //依次更新前面路径中边的残余容量,继续累加残余容量为最大流.
    return res;
}

//Dinic 时间复杂度O(V^2*E)
int maxFlow(){
    int sum=0;
    while(bfs(1,m)){
        //dfs源点返回的是各个分支上的最小残余容量总和,
        //就是多条增广路上各个最小的残余容量,也就是最多能流过的流量
        sum+=dfs(1,INF);//初始残余容量设置为INF,方便记录增广路中最小残余容量
    }
    return sum;
}

int main(){
    int x,y,cap;
    /*
    题目样例里总共构建了三次层次网络,第一次是1->4(20),第二次是1->2->4(20),第三次是1->2->3->4(10) 20+20+10=50
    */
    while(scanf("%d %d",&n,&m)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        memset(net,0,sizeof(net));//有重复边,容量需要累加,因此c要初始化为0
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&x,&y,&cap);
            addEdge(x,y,cap);//从cnt=0下标开始存边 每存一条正向边与他紧邻的cnt+1下标就存一条反向边 且参与容量初始化为0
            addEdge(y,x,0);
        }
        printf("%d\n",maxFlow());
    }
    return 0;
}

/*
//ac 0ms Dinic多路增广求解最大流 链式前向星存边 cur数组 当前弧优化
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;
int cnt,n,m,head[N],d[N],cur[N];

struct node{
    int to,next,c;
}net[N<<1];//这里题目中说明了 最多有N(210)条水管,因为在构建网络时需要初始化反向弧,所以总共需要的最大边数为2*N

void addEdge(int x,int y,int c){
    net[cnt].to=y;
    net[cnt].c+=c;
    net[cnt].next=head[x];
    head[x]=cnt++;
}

//可搜索出多条长度相等的最短增广路 每次都搜索最短,
//会使得最终整体增广路的总边数最少,提高搜索效率
bool bfs(int s,int t){//构建层次网络(指的是相同长度的增广路构成的网络),层数就是最短增广路长度
    int u,v;
    queue<int> Q;
    //源点设置0,其余点设置-1,判断用dis[v]==-1,可避免使用!dis[v]使得源点再次入队
    memset(d,-1,sizeof(d));
    d[s]=0;//初始化起点长度为0,也避免重复访问 判断d[v]==-1
    Q.push(s);
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=net[i].next){
            v=net[i].to;
            if(net[i].c>0 && d[v]==-1){
                d[v]=d[u]+1;
                if(v == t) return true;
                Q.push(v);
            }
        }
    }
    //如果return false说明所遍历的所有路径里含有残余流量为0的边,
    //导致无法搜索到达汇点,不存在增广路
    return false;
}

//搜索增广路,累加残余容量作为最大流
//每次找增广路的时候,都只找比当前点层数多1的点进行增广(这样就可以确保我们找到的增广路是最短的).
int dfs(int u,int flow){
    if(u==m)
        return flow;
    int v,res=0,incf;
    for(int i=cur[u];i!=-1;i=net[i].next){
        //cur记录的边下标为当前i,因为i之前的边所构成的增广路可能存在残余容量为0的边,没必要再去增广了
        //但这里如果是u的前驱节点路径里的残余容量较小,那么u点后如果有很多分支,可能这些分支的残余容量并不为0(没有被榨干),
        //会使得cur数组只记录最后一个分支,这样若还有别的增广路访问u点,此时之前那些分支就无法分流,
        //这次dfs就没能遍历之前bfs划分出的层次的增广路(最短相同长度的增广路),但这并不影响结果的正确性,本次dfs遗漏掉的增广路
        //会在下次bfs时再次被划分出来,就是可能会多bfs几次,但这个当前弧优化对于大多数u点后分支残余容量为0的情况还是有很大的优化的,综合来看优化还是很高.
        cur[u]=i;
        v=net[i].to;
        //对于反向弧,无需标记vis 避免其又返回u点dfs,因为有d[v]==d[u]+1限制
        if(d[v]==d[u]+1 && net[i].c>0){//多路增广
            incf=dfs(v,min(net[i].c,flow));//求出当前点为首的后续路径之中最小的残余容量
            if(incf>0){//incf 残余容量大于0代表搜索到增广路
                flow-=incf;
                net[i].c-=incf;
                net[i^1].c+=incf;
                res+=incf;
            }
            if(flow==0)//表示当前边的残余容量已为0,结束dfs 没有增广路可寻
                return res;
        }
    }
    if(res==0)
        d[u]=-1;
    return res;
}

//Dinic 时间复杂度O(V^2*E)
int maxFlow(){
    int sum=0;
    while(bfs(1,m)){
        for(int i=1;i<=m;i++)//每次dfs需要重新初始化cur数组为head数组
            cur[i]=head[i];
        sum+=dfs(1,INF);
    }
    return sum;
}

int main(){
    int x,y,cap;
    while(scanf("%d %d",&n,&m)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        memset(net,0,sizeof(net));//有重复边,容量需要累加,因此c要初始化为0
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&x,&y,&cap);
            addEdge(x,y,cap);//从cnt=0下标开始存边 每存一条正向边与他紧邻的cnt+1下标就存一条反向边 且参与容量初始化为0
            addEdge(y,x,0);
        }
        printf("%d\n",maxFlow());
    }
    return 0;
}
*/
