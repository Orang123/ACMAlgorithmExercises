#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 42000
#define M 4004000//这题目的数据范围和题目描述不符,实际地上界达到了百万,2百万即可,按照题目描述,卡死10W感觉就可
#define INF 0x3f3f3f3f
using namespace std;
//ac 545ms dinic 最小割=最大流 数据较大,EK算法会TLE.

/*割相关的概念
对于每条路径，切去最小的那条边，以达到路径断裂且代价最小，也就是多选一。
对于一个网络流图G=(V,E),其割的定义为一种点的划分方式:将所有的点划分为S和T=V-S
两个集合,其中源点s属于S,汇点t属于T。
割的容量:我们定义割(S,T)的容量c(S,T)表示所有从S到T的边的容量之和
最小割:最小割是求得一个割(S,T)使得割的容量c(S,T)最小。
网络N的一个割即是分离源和汇的弧之集合。
最大流-最小割定理:最大流=最小割,我理解的是最大流在求解每条增广路所增加的流刚好
是这条增广路径上最小的残余容量,而最小的残余容量累加起来刚好和最小割的容量,可以这么类比,
但最大流增广路的选取的最小残余容量和最小割中的割边没有一点关系,更多的是数值上相等。

割边数量
只需要将每条边的容量变为1,然后重新跑网络流即可.
*/

/*
题意:小M在MC里开辟了两块巨大的耕地A和B(你可以认为容量是无穷),
现在小P有n中作物的种子,每种作物的种子有1个(就是可以种一棵作物)(用1...n编号).
现在第i种作物种植在A中种植可以获得ai的收益,在B中种植可以获得bi的收益,
而且现在还有这么一种神奇的现象,就是某些作物共同种在一块耕地中可以获得额外的收益,
小M找到了规则中共有m种作物组合,第i个组合中的作物共同种在A中可以获得c1i的额外收益,
共同总在B中可以获得c2i的额外收益.小M很快的算出了种植的最大收益,但是他想要考考你,
你能回答他这个问题么?
链接:https://www.luogu.com.cn/problem/P1361
思路:
二者选其一问题模型
题目的意思就是由n种作物只能种在A地或B地里,即当选择种在A地里就不能种在B地里
我们可以构建图论模型来表达这个关系,即将A、B两地当做源点(s)和汇点(t),作物i种在A地里
那么从s连一条指向i点的有向边,产生的收益就为边的残余容量,作物种在B地里,那么从i点连一条
指向汇点(t)的有向边,该边的残余容量同样为产生的收益,除此以外某种作物组合如果同时种在A地或
B地会产生额外的收益。现在问如何种植使得获得的收益最大,首先这是一个矛盾的问题,因为作物只能
选择种在A地或B地一种方式,反应到图论网络的问题就是i点所连接到源点和汇点的边只能选择一条
(即:二者选其一),而且要尽可能选择残余流量最大的那些边集,那么实际我们就需要删除那些流量较小
的边集组合,来达到分离源点和汇点连接的作用,那么显然这是一个最小割的问题,根据最大流-最小割定理
(最大流=最小割)我们可以转化为求网络最大流去做。现在会产生额外的问题,就是额外收益,我们可以考虑
构建一个虚点x,用来表示都种在A地或B地的一个作物(i、j)组合,从源点(s)连一条有向边指向x点,边容量为
其产生的额外收益,同时从x点向组合中的每个点都连有向边,流量为INF,然后再构建一个虚点y同样表示i和j作物
同时种在B地的组合,将组合中的作物i、j都连有向边向y,流量为INF,然后y点再向汇点(t)连一条有向边,残余流量
为作物i、j同时钟在B中所产生额外收益.
注意:额外收益的组合如果选在了A地,那B地的连边必然都不能选,因为需要满足割分离源和汇.
显然问题本身也满足割的定义.

分析额外收益:根据最小割,如果x与s的这条边存在,那必然组合中的点与汇点(t)的连边都得切断,而且y点与汇点相连的边也得切断,
至于为什么要这么切只是我们从题目的主观概念上来想的,我们再从最小割的角度上想一想,首先i、j两点与汇点(t)的边都已经切断,
而现在从s->x->i->y->t和s->x->j->y->t都能到达汇点t,因为我们搜构建的x->i,i->y流为INF(无穷大),自然最小割割边不会选择这条,
而且即使选择这条边,那么j点与x、y相连的边也得切掉,我们可以选择只切掉y点与汇点相连的边,这样才是"最小"割。
实际关于s->i->t,s->j->t割边是怎么切的,也是根据最小割的割边容量总和最小去切的,只有当实际所切除割边后剩余下来的边是最大收益时,
最小割才是最小的。就是说可能也不是主观的那样min(c(s->i),c(i->t))取在作物种在A地或B地(局部)收益较小的那个座位割边,而是
从割边集合中边的流量总和最小(全局)来考虑的。但求解最大流的过程和最小割没有关联(最大流的最小残余容量和最小割的割边可能没有关联),
只是在数值上最大流等于最小割.
*/

/*
洛谷网友理解:
S向每个点建边，容量为种在A的收益，每个点向T建边，容量为种在B的收益，对于每一个点，
我们必然要割掉连向S或T的一条且仅一条边。对于割之后的图，S集的点均选择了种在A，
T集的点均选择了种在B。那对于共同种在A地有额外收益的点怎么办呢？，我们新建一个点x，S向x连边，
容量为收益，x向所有需要共同种在A的点连边，容量为inf，则如果这些点有一个点没有割掉向T的连边，
我们势必要割掉收益这条边。如果收益这条边没被割掉，则说明他所需要的点最后都割了向T的连边，
也就是都在S集中，也就是都种在了A，符合题意。对于共同种在B的有额外收益的也同理，
新建一个点x，x向T连边，容量为收益，所有需要共同种在B的点向x连边，容量为inf。则最后答案就是总收益-最小割。
*/
struct node{
    int to,next,f;
}edge[M];
int head[N],cnt,vis[N],d[N];

void addEdge(int from,int to,int f){
    edge[cnt].to=to;
    edge[cnt].f=f;
    edge[cnt].next=head[from];
    head[from]=cnt++;
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
    int n,a,b,s,t,m,k,c1,c2,h,ans=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    s=n+1,t=n+2;//源点编号n+1 汇点编号n+2
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        ans+=a;
        addEdge(s,i,a);//i作物种在A地 s连向i的有向边
        addEdge(i,s,0);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b);
        ans+=b;
        addEdge(i,t,b);//i作物种在B地 i连向t的有向边
        addEdge(t,i,0);
    }
    scanf("%d",&m);//m种组合 作物 编号 都种在A地从(n+2)+1开始编号 都种在B地从(n+2+m)+1开始编号
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&k,&c1,&c2);//该组合包含k个作物
        ans+=c1+c2;
        addEdge(s,n+2+i,c1);//n+2+i种组合作物都种在A地 获得的额外收益C1
        addEdge(n+2+i,s,0);
        addEdge(n+2+m+i,t,c2);//n+2+m+i种组合作物都种在B地 获得的额外收益C2
        addEdge(t,n+2+m+i,0);
        while(k--){
            scanf("%d",&h);
            addEdge(n+2+i,h,INF);//组合虚点X点 向组合中的每一个作物点连边
            addEdge(h,n+2+i,0);
            addEdge(h,n+2+m+i,INF);//组合内的每一个作物点向 组合虚点Y点连边
            addEdge(n+2+m+i,h,0);
        }
    }
    printf("%d\n",ans-maxFlow(s,t));//求出最小割,将这些矛盾的割边删除,剩下的就是最大收益,即:总收益和-最大流
    return 0;
}

/*
//ac 437ms dinic 当前弧优化
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 42000
#define M 4004000
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
struct node{
    int to,next,f;
}edge[M];
int head[N],cnt,vis[N],d[N],cur[N];

void addEdge(int from,int to,int f){
    edge[cnt].to=to;
    edge[cnt].f=f;
    edge[cnt].next=head[from];
    head[from]=cnt++;
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
        cur[u]=i;//当前弧优化
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
        for(int i=1;i<=2*n+m+2;i++)
            cur[i]=head[i];
        sum+=dfs(s,t,INF);
    }
    return sum;
}

int main(){
    int a,b,s,t,k,c1,c2,h,ans=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        ans+=a;
        addEdge(s,i,a);
        addEdge(i,s,0);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b);
        ans+=b;
        addEdge(i,t,b);
        addEdge(t,i,0);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&k,&c1,&c2);
        ans+=c1+c2;
        addEdge(s,n+2+i,c1);
        addEdge(n+2+i,s,0);
        addEdge(n+2+m+i,t,c2);
        addEdge(t,n+2+m+i,0);
        while(k--){
            scanf("%d",&h);
            addEdge(n+2+i,h,INF);
            addEdge(h,n+2+i,0);
            addEdge(h,n+2+m+i,INF);
            addEdge(n+2+m+i,h,0);
        }
    }
    printf("%d\n",ans-maxFlow(s,t));
    return 0;
}
*/

/*
//EK 算法TLE O(V*E^2) E<=4*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 3100
#define M 4000100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],pre[N],incf[N],sum;
struct Edge{
    int to,next,cf;
}edge[M];

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
    int a,b,c1,c2,k,v;
    cnt=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        sum+=a;
        addEdge(0,i,a);
        addEdge(i,0,0);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b);
        sum+=b;
        addEdge(i,n+1,b);
        addEdge(n+1,i,0);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&k,&c1,&c2);
        sum+=c1+c2;
        addEdge(0,n+1+i,c1);
        addEdge(n+1+i,0,0);
        addEdge(n+1+m+i,n+1,c2);
        addEdge(n+1,n+1+m+i,0);
        while(k--){
            scanf("%d",&v);
            addEdge(n+1+i,v,INF);
            addEdge(v,n+1+i,0);
            addEdge(v,n+1+m+i,INF);
            addEdge(n+1+m+i,v,0);
        }
    }
    printf("%d",sum-max_flow(0,n+1));
    return 0;
}
*/
