#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//ac 1.24s EK算法求解最小费用最大流 mcmf
/*
相关概念:
1.费用流:
给定一个网络G=(V,E),每条边除了有容量限制c(u,v),还有一个单位流量的费用w(u,v).
当(u,v)的流量为f(u,v)时,需要花费f(u,v)*w(u,v).
w也满足斜对称性,即w(u,v)=-w(u,v).
则该网络中总花费最小的最大流称为最小费用最大流,即在最大化f(s,v)(源点s发出流综合)
的前提下最小化f(u,v)*w(u,v).
2.最小费用最大流:
每条边除了要流经流量外,还有一个费用,代表单位流量流过这条边的开销.
我们要在求出最大流的同时,要求花费的费用最小.
*/

/*
题意:给出一个包含n个点和m条边的有向图(下面称其为网络)G=(V,E),
该网络上所有点分别编号为1~n,所有边分别编号为1~m,其中该网络的源点为s,
汇点为t,网络上的每条边(u,v)都有一个流量限制c(u,v)和单位流量的费用w(u,v).
现在要求出在该网络流量最大的前提下,使得水流经过的费用c(u,v)*w(u,v)最小化,
分出输出对应的最大流和最小费用.
链接:https://www.luogu.com.cn/problem/P3381
思路:EK算法求解最小费用最大流模板,mcmf.
*/

struct node{
    int to,next,c,w;
}edge[M<<1];
int head[N],incf[N],pre[N],cnt,dis[N],n,m,vis[N];
int max_flow,min_cost;

void addEdge(int from,int to,int c,int w){
    edge[cnt].to=to;
    edge[cnt].c=c;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s,int t){
    for(int i=1;i<=n;i++)//memset(dis,0x3f,sizeof(dis)) dis[s]=0也是正确的
        dis[i]=i==s?0:INF;//将源点dis[s]设置为0,其余点dis设置为INF,方便更新规划最小费用
    pre[t]=-1;//设置汇点的标记为-1,用来判断此次是否搜索到了新的增广路
    incf[s]=INF;//方便比较更新增广路中的最小残余流量
    vis[s]=1;//初试源点 首先入队
}

/*
因为反向弧的存在,每条边有可能费用为负数,即负权边,这里采用spfa,而不能直接用Dijkstra,
因为最短路问题Dijkstra贪心是建立在边权都为正的情况,这里既有正又有负就会出错.
若要用Dijkstra则需要引入势函数h[i]将边权费用拉成正数才能保证结果的正确性.
实际上就是在搜索增广路的同时搜索费用权最短路,要保证其到达汇点所花费的费用总和最小
*/
int spfa(int s,int t){
    queue<int> Q;
    init(s,t);//初始化
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            /*
            该边既要满足残余容量>0,也要满足从源点到达v点所花费的费用能再次变得更小,
            dis[v]>dis[u]+edge[i].w 这里原则上对于负权边反向弧是能够再次从v点又回到u点的,
            但是这里是>号没有=号,dis[u]=dis[v]+edge[i].w(是能够成立的).
            因为有dis[v]>dis[u]+edge[i].w可保证不会遍历已遍历过的点,这里可以不用pre[v]==-1判断.
            */
            if(edge[i].c>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;//记录增广路v点所在的边的下标
                incf[v]=min(incf[u],edge[i].c);//不断记录求解本次增广路中的最小残余容量
                dis[v]=dis[u]+edge[i].w;//更新从源点到达v点所花费的最小费用
                if(!vis[v]){//若v点还未入队,则从新入队
                    Q.push(v);
                    vis[v]=1;
                }
                //这里不能到达汇点t就直接结束,因为spfa先到达某个点的路径费用综合不一定是最小的,会出错
                //这里实际确定的增广路长度也不一定是最短的,spfa计算的路径权值和(费用)最小
                //if(v == t){ return incf[t];
            }
        }
    }
    return pre[t];//pre[t]==-1 则代表本次搜索任意一条s到t的路径中都至少含有一条残余流量为0的边,即不存在增广路
}
//mcmf(min cost max flow 最小费用最大流)
void mcmf(int s,int t){
    while(spfa(s,t)!=-1){//不存在增广路时返回-1就结束
        for(int i=t;i!=s;i=edge[pre[i]^1].to){
            edge[pre[i]].c-=incf[t];//正向边残余容量减少
            edge[pre[i]^1].c+=incf[t];//反向边残余容量增加
            /*
            可以这样在每一条增广路得到每条边上对每条边所花费的流量*单位流量费用求和
            但洛谷里这里有优化,直接一个一个求 大数据样例会超时,实际数学表达式:
            edge[pre[i]].w*incf[t]+edge[pre[j]].w*incf[t]+...+edge[pre[t]].w*incf[t],
            可以提取公因式incf[t],incf[t]*(edge[pre[i]].w+edge[pre[j]].w+...edge[pre[t]].w)
            而(edge[pre[i]].w+edge[pre[j]].w+...edge[pre[t]].w)每条边上所花费的费用之和,
            实际就是spfa求出的从s源点到达汇点t最小费用权值和,可用dis[t]代替实际就是incf[t]*dis[t].
            */
            //min_cost+=incf[t]*edge[pre[i]].w;//一条边一条边累加流量*费用会TLE,加法会耗时.
        }
        max_flow+=incf[t];//累加最大流
        min_cost+=incf[t]*dis[t];//一次性计算 最小费用
    }
}

int main(){
    int s,t,u,v,c,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        scanf("%d%d%d%d",&u,&v,&c,&w);//c为容量 w为通过单位流量需要的费用
        addEdge(u,v,c,w);
        addEdge(v,u,0,-w);//反向弧当增广路的选择不是最优时提供反悔的机会 初试流为0,费用为负权
    }
    mcmf(s,t);
    printf("%d %d",max_flow,min_cost);
    return 0;
}

/*
//ac 555ms EK算法 Dijkstra划分层次网络 因为有负权费用,
//需要用势函数h[i]将边权费用拉成正数才能保证结果的正确性
//不过不太理解势函数h[i]的操作
//这个势函数是采用了 Johnson算法顶标的三角不等式的思路 http://hoblovski.is-programmer.com/posts/52364.html
//参考博客:https://www.cnblogs.com/zbwmqlw/archive/2011/01/01/1923694.html
//https://www.luogu.com.cn/problem/solution/P3381?page=1 //洛谷P3381 题解
//https://blog.csdn.net/weixin_43741224/article/details/98970032
//https://www.cnblogs.com/zwfymqz/p/8543329.html
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//h[i]会一直累加,这个做法如果边权本身很大,需要开long long
int head[N],incf[N],pre[N],cnt,dis[N],n,m,h[N];
int max_flow,min_cost;
struct node{
    int to,next,c,w;
}edge[M<<1];

void addEdge(int from,int to,int c,int w){
    edge[cnt].to=to;
    edge[cnt].c=c;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s,int t){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;//起始费用为0
    pre[t]=-1;//汇点前驱标记-1
    incf[s]=INF;//源点最小残余容量标记INF
}

int Dijkstra(int s,int t){
    priority_queue<pair<int,int> ,vector<pair<int,int>>,greater<pair<int,int>> >Q;//这里是小根堆 也可用pair 大根堆存负值
    init(s,t);//初始化
    Q.push(make_pair(dis[s],s));
    int u,v;
    pair<int,int> tp;
    while(!Q.empty()){
        tp=Q.top();
        u=tp.second;
        Q.pop();
        //这里不能像最短路那样用vis标记,用vis标记,如果再判断u == t就会tle 搞不懂啥原因
        if(dis[u]<tp.first) continue;//当之前更新的dis[u]费用已经比当前弹出堆的费用小则不必更新
        if(u == t) break;//Dijkstra已经弹出的最小费用一定是最优的不必再更新,结束
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].c>0 && dis[v]>dis[u]+edge[i].w+h[u]-h[v]){//h[u]-h[v]不理解
                pre[v]=i;
                incf[v]=min(incf[u],edge[i].c);
                dis[v]=dis[u]+edge[i].w+h[u]-h[v];
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return pre[t];
}

void mcmf(int s,int t){
    while(Dijkstra(s,t)!=-1){
        for(int i=t;i!=s;i=edge[pre[i]^1].to){
            edge[pre[i]].c-=incf[t];
            edge[pre[i]^1].c+=incf[t];
        }
	//需要在每次Dijkstra求层次网络前累加结果
        for(int i=1;i<=n;i++)//h[i]会一直累加,这个做法如果边权本身很大,需要开long long
            h[i]+=dis[i];//也可h[i]=min(h[i]+dis[i],INF); 这里不理解
        max_flow+=incf[t];
        min_cost+=incf[t]*h[t];//这里源点到汇点的费用和要用h[t],而不是dis[t],否则费用流结果会出错
    }
}

int main(){
    int s,t,u,v,c,w;
    memset(head,-1,sizeof(head));
    memset(h,0,sizeof(h));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        scanf("%d%d%d%d",&u,&v,&c,&w);//c为容量 w为通过单位流量需要的费用
        addEdge(u,v,c,w);
        addEdge(v,u,0,-w);
    }
    mcmf(s,t);
    printf("%d %d",max_flow,min_cost);
    return 0;
}
*/

/*
zkw费用流 暂未了解
*/
