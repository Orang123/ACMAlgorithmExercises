#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 250 //构造i+n点 构造割边等效割点需要2*N的空间开销
#define M 1500//建双向边 (600+100)*2,电脑之间互相可达
#define INF 0x3f3f3f3f
using namespace std;
//ac 25ms dinic 最小割=最大流 拆点构造入点出点,将删点转化为删入点到出点的删边问题
/*
题意:农夫约翰的奶牛们喜欢通过电邮保持联系,于是她们建立了一个奶牛电脑网络,
以便互相交流.这些机器用如下的方式发送电邮:如果存在一个由c台电脑组成的序列
a1,a2,...,ac,且a1与a2相连,a2与a3相连,等等.那么电脑a1和ac就可以互发电邮.
很不幸,有时候奶牛会不小心踩到电脑上,农夫约翰的车也可能碾过电脑,这台倒霉的
电脑就会坏掉.这意味着这台电脑不能再发送电邮了,于是与这台电脑相关的连接也就
不可用了.有两头奶牛就想:如果我们两个不能互发电邮,至少需要坏掉多少台电脑呢?
请编写一个程序为她们计算这个最小值.
两头奶牛使用的电脑编号为c1、c2.
以如下网络为例:1-3-2
这张图画的是有2条连接的3台电脑.我们想要在电脑1和2之间传送信息.电脑1与3,
2与3直接连通.如果电脑3坏了,电脑1与2便不能互发信息了.
释义:一张n个点网络图,求至少删除多少个点才能使网络中的源点和汇点不连通.

链接:https://www.luogu.com.cn/problem/P1345
思路:可以将一个点i拆成两个点i(入点)、i+n(出点),i与i+n之间建双向边,
容量为1(因为每个点只能删除一次),其余点x联想i建x-i的双向边,容量为INF;
i点连向其余点x,建i+n-x的双向边,容量为INF.这样问题转化为了分离源点到汇点
至少需要割去几条边,显然是最小割问题,而最小割=最大流.而实际最小割中边的数目
和实际最少删除点的个数是等价的,因为删去的边的容量都是1,这样就将求删点的最少
数目转化成了删边的最少数目.
注意:初始源点要从c1+n(c1源点的出点)开始,因为c1-c1+n其实容量只有1,这样结果永远为1,
答案错误.

注意:
1.u到v的电脑是双向通信的,双向通信的有向边分为 u+n->v和 v+n->u这两条边的起始容量是INF,
但其反向弧v->u+n和u->v+n起始容量是0,否则结果会出错.
2.此题无法从tarjan割点的角度考虑,因为tarjan只能判断出多少个割点,无法求解出影响源点和汇点间
连通性的具体最少的割点数目.而且这类题目一般是不存在割点的,就是无法删除一个点使得原图不连通,
所以要用最大流最小割做.
*/

struct node{
    int to,next,f;
}edge[M<<1];//建双向边
int head[N],cnt,vis[N],d[N];

void addEdge(int from,int to,int f){
    edge[cnt]=(node){to,head[from],f};
    head[from]=cnt++;
    edge[cnt]=(node){from,head[to],0};//反向弧起始容量为0
    head[to]=cnt++;
}

void init(int s){
    memset(d,-1,sizeof(d));//源点设置0,其余点设置-1,判断用dis[v]==-1,可避免使用!dis[v]使得源点再次入队
    d[s]=0;
}

bool bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].f>0 && d[v]==-1){
                d[v]=d[u]+1;
                if(v == t) return true;
                Q.push(v);
            }
        }
    }
    return false;
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int v,incf,res=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(edge[i].f>0 && d[v]==d[u]+1){
            incf=dfs(v,t,min(flow,edge[i].f));
            if(incf>0){
                edge[i].f-=incf;
                edge[i^1].f+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0) return res;
        }
    }
    if(res == 0) d[u]=-1;
    return res;
}

int maxFlow(int s,int t){
    int sum=0;
    while(bfs(s,t))
        sum+=dfs(s,t,INF);
    return sum;
}

int main(){
    int n,m,c1,c2,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    scanf("%d%d",&c1,&c2);
    for(int i=1;i<=n;i++)
        //i点为别的点连边进入的点,i+n点为i点连边连出去的点 其实容量设置为1,因为1个点只能删除1次
        //反向弧出点到入点i+n到i起始容量为0
        addEdge(i,i+n,1);
    while(m--){
        scanf("%d%d",&u,&v);
        /*
        其余点和点之间的连别是双向连通的,而且流要设置为INF,
        因为实际割掉的是i与i+n之间流为1的边,等效于割掉i点,
        根据最小割而不会割掉其余点之间连边流为INF的连边.
        */
        //u-v是互通的,即u的出点可达v的入点,v的出点也可达u的入点 并且起始容量都是INF
        //其反向弧容量是0
        addEdge(u+n,v,INF);//u到v正向弧起始容量为INF 反向弧v->u+n起始容量为0
        addEdge(v+n,u,INF);//v到u正向弧起始容量为INF 反向弧u->v+n起始容量为0
    }
    /*
    这里不能删掉源点c1与c1+n之间的连边,这会导致删掉c1这个点,那就直接与c2分割了,割点数为1,
    初始源点要从c1+n(c1源点的出点)开始.
    答案错误,源点遍历要从c1+n源点连出去的边开始
    */
    printf("%d",maxFlow(c1+n,c2));//求解i与i+n之间的割边 最小割即:最小割点 等效于最大流
    return 0;
}

/*
//ac 25ms dinic 当前弧优化 拆点
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 250
#define M 1500
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,next,f;
}edge[M<<1];
int n,m,head[N],cnt,vis[N],d[N],cur[N];

void addEdge(int from,int to,int f){
    edge[cnt]=(node){to,head[from],f};
    head[from]=cnt++;
    edge[cnt]=(node){from,head[to],0};
    head[to]=cnt++;
}

void init(int s){
    memset(d,-1,sizeof(d));//源点设置0,其余点设置-1,判断用dis[v]==-1,可避免使用!dis[v]使得源点再次入队
    d[s]=0;
}

bool bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].f>0 && d[v]==-1){
                d[v]=d[u]+1;
                if(v == t) return true;
                Q.push(v);
            }
        }
    }
    return false;
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int v,incf,res=0;
    for(int i=cur[u];i!=-1;i=edge[i].next){
    	cur[u]=i;
        v=edge[i].to;
        if(edge[i].f>0 && d[v]==d[u]+1){
            incf=dfs(v,t,min(flow,edge[i].f));
            if(incf>0){
                edge[i].f-=incf;
                edge[i^1].f+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0) return res;
        }
    }
    if(res == 0) d[u]=-1;
    return res;
}

int maxFlow(int s,int t){
    int sum=0;
    while(bfs(s,t)){
    	for(int i=1;i<=2*n;i++)
    		cur[i]=head[i];
		sum+=dfs(s,t,INF);
	}
    return sum;
}

int main(){
    int c1,c2,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    scanf("%d%d",&c1,&c2);
    for(int i=1;i<=n;i++)
        addEdge(i,i+n,1);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u+n,v,INF);//流设置为1  求解最小割容量值即为割边数量
        addEdge(v+n,u,INF);
    }
    printf("%d",maxFlow(c1+n,c2));//求解割边个数 根据最大流-最小割定理,转化为求解最大流
    return 0;
}
*/

/*
//ac 23ms EK算法 bfs搜索增广路
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 250
#define M 1500
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],pre[N],incf[N],sum;
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
}

void init(int s){
    memset(pre,-1,sizeof(pre));
    incf[s]=INF;
}

int bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        if(u == t) return 1;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && pre[v] == -1){
                incf[v]=min(incf[u],edge[i].cf);
                pre[v]=i;
                Q.push(v);
            }
        }
    }
    return 0;
}

int max_flow(int s,int t){
    int ans=0,v;
    while(bfs(s,t)){
        v=t;
        while(v!=s){
            edge[pre[v]].cf-=incf[t];
            edge[pre[v]^1].cf+=incf[t];
            v=edge[pre[v]^1].to;
        }
        ans+=incf[t];
    }
    return ans;
}

int main(){
    int c1,c2,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    scanf("%d%d",&c1,&c2);
    for(int i=1;i<=n;i++){
        addEdge(i,i+n,1);//入点到出点 容量为1(每个点只能删除1次)
        addEdge(i+n,i,0);//反向弧出点到入点 容量为0
    }
    while(m--){
        scanf("%d%d",&u,&v);
        //u-v是互通的,即u的出点可达v的入点,v的出点也可达u的入点 并且起始容量都是INF
        //其反向弧容量是0
        addEdge(u+n,v,INF);//u到v 起始容量INF
        addEdge(v,u+n,0);//反向弧v->u+n起始容量为0
        addEdge(v+n,u,INF);//v到u 起始容量INF
        addEdge(u,v+n,0);//反向弧u->v+n起始容量为0
    }
    printf("%d",max_flow(c1+n,c2));//求解割边个数 根据最大流-最小割定理,转化为求解最大流
    return 0;
}
*/
