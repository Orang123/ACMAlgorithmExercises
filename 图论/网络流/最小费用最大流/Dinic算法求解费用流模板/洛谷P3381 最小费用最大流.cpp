#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//ac 1.24s dinic求解费用流
//因为dfs多路增广对访问点作标记原因,所以本身就替代了当前弧优化,实际效果差不多.因此无需当前弧优化.
/*
题意:给出一个包含n个点和m条边的有向图(下面称其为网络)G=(V,E),
该网络上所有点分别编号为1~n,所有边分别编号为1~m,其中该网络的源点为s,
汇点为t,网络上的每条边(u,v)都有一个流量限制c(u,v)和单位流量的费用w(u,v).
现在要求出在该网络流量最大的前提下,使得水流经过的费用c(u,v)*w(u,v)最小化,
分出输出对应的最大流和最小费用.
链接:https://www.luogu.com.cn/problem/P3381
思路:Dinic算法求解最小费用最大流模板,mcmf.
*/
struct node{
    int to,next,c,w;
}edge[M<<1];
int head[N],cnt,dis[N],n,m,vis[N];
int max_flow,min_cost;
void addEdge(int from,int to,int c,int w){
    edge[cnt].to=to;
    edge[cnt].c=c;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s,int t){
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
    memset(vis,0,sizeof(vis));//这里因为上一次dfs统计多路增广路 最大流费用时,标记过vis[i]=1,重新赋值为0以便下次spfa
    vis[s]=1;//源点s先入队
}

//spfa遍历搜索最短费用相同的增广路,将这些增广路划分到同一层次,
//方便dfs时计算这些增广路的费用流,但是不一定所有增广路都能遍历到,因为dfs时采用了vis标记.
bool spfa(int s,int t){
    queue<int> Q;
    init(s,t);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            /*
            这里原则上对于负权边反向弧是能够 再次从v点又回到u点的,但是这里是>号没有=号,
            因此也不会使得u点再次入队,只是dis[u]=dis[v]+edge[i].w(是能够成立的),
            dfs时会成立,因此在dfs设置了!vis[u].
            */
            if(edge[i].c>0 && dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    Q.push(v);
                    vis[v]=1;
                }
                // if(v==t) return true //spfa直接就确定第一次到达的增广路,费用和不见得最小,会出错wrong
            }
        }
    }
    return (dis[t]!=INF);//若dis[t]为INF说明没有增广路
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int res=0,v,incf;
    /*
    已访问过的父节点需要标记,不可在儿子访问反向弧时回到父节点,会出错.
    这个标记本身就替代了当前弧优化,已访问过的增广路分支节点因为被标记,
    就不可再访问.所以不必再使用cur数组在dfs里更新头结点记录的下标.所以
    做标记法也会出现当前弧优化出现的那个问题,详情在最大流Dinic算法模板
    里有过记录.
    */
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        /*
        这里dis[v] == dis[u]+edge[i].w,如果不设置!vis[v]会导致这条增广路的v结点,
        可以通过累加反向弧的负权值费用会回到之前的父节点u导致构成死循环;
        或者能够成功到达汇点t,在退栈回溯时,v->u这条错误的边的残余容量和反向弧的
        残余容量会被更新+-incf,但因为正向边反向边各走了1次,所以+-incf刚好抵消,
        实际v-u的正向边和反向边残余容量没有变化.所以不设置!vis[v]的判定只会导致死循环.
        vis标记同样会出现当前弧优化的那个问题.
        */
        if(!vis[v] && edge[i].c>0 && dis[v] == dis[u]+edge[i].w){
            incf=dfs(v,t,min(flow,edge[i].c));
            if(incf>0){
                edge[i].c-=incf;
                edge[i^1].c+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0)
                return res;
        }
    }
    /*
    不能vis[u]=0
    这里不能通过回溯时取消vis标记来使得其余增广路访问之前增广路访问过的分支
    (可能残余容量没用完),这样会使得满足dis[v] == dis[u]+edge[i].w的分支路径,
    但这个v点之前的增广路访问过,现在再次访问因为取消了前驱节点的标记,会访问v
    的前驱节点u,这样正向边和反向边会再次更新和之前增广路更新的抵消掉,也就是之前增广路
    上边的残余容量在这次增广并没有变化,但是实际最大流已经计算过了,可残余容量没有变化,
    这样就会在下次bfs分层后dfs增广路总的结果最大流就会出错.
    */
    //vis[u]=0;//不能这样取消标记 会出错
    /*
    这里无需像dinic那样炸点优化本次并不打算计算的那些较大费用流的可能增广路,
    因为对于已访问过的点已经标记过vis[u]=1了,已访问过的点本身就是不会再访问的.
    */
    //if(res == 0) dis[u]=INF;//无需这个操作,vis[v]标记本身就能保证已访问过的增广路的点不再访问
    return res;
}

void mcmf(int s,int t){
    int flow;
    while(spfa(s,t)){
        flow=dfs(s,t,INF);//一次dfs统计计算多条增广路的最大流,
        max_flow+=flow;
        /*
        这里最小费用总合也是通过两次 提取公因式 简化计算得到,
        第一次提取公因式incf将费用总合化简为 dis[t],第二次提取
        公因式dis[t]将多条增广路的最大流和化简为flow.
        */
        min_cost+=flow*dis[t];
    }
}

int main(){
    int s,t,u,v,c,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        scanf("%d%d%d%d",&u,&v,&c,&w);
        addEdge(u,v,c,w);
        addEdge(v,u,0,-w);
    }
    mcmf(s,t);
    printf("%d %d",max_flow,min_cost);
    return 0;
}

/*
//ac 695ms Dinic算法 Dijkstra划分层次网络 因为有负权费用,
//需要用势函数h[i]将边权费用拉成正数才能保证结果的正确性
//不过不太理解势函数h[i]的操作
////这个势函数是采用了 Johnson算法顶标的三角不等式的思路 http://hoblovski.is-programmer.com/posts/52364.html
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;

struct node{
    int to,next,c,w;
}edge[M<<1];
int head[N],cnt,dis[N],n,m,vis[N],h[N];
int max_flow,min_cost;
void addEdge(int from,int to,int c,int w){
    edge[cnt].to=to;
    edge[cnt].c=c;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s,int t){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    memset(vis,0,sizeof(vis));
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
                dis[v]=dis[u]+edge[i].w+h[u]-h[v];
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return dis[t]!=INF;
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int res=0,v,incf;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!vis[v] && edge[i].c>0 && dis[v] == dis[u]+edge[i].w+h[u]-h[v]){
            incf=dfs(v,t,min(flow,edge[i].c));
            if(incf>0){
                edge[i].c-=incf;
                edge[i^1].c+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0)
                return res;
        }
    }
    return res;
}

void mcmf(int s,int t){
    int flow;
    while(Dijkstra(s,t)){
        flow=dfs(s,t,INF);//一次dfs统计计算多条增广路的最大流,
        for(int i=1;i<=n;i++)
            h[i]+=dis[i];
        max_flow+=flow;
        min_cost+=flow*h[t];//这里源点到汇点的费用和要用h[t],而不是dis[t],否则费用流结果会出错
    }
}

int main(){
    int s,t,u,v,c,w;
    memset(head,-1,sizeof(head));
    memset(h,0,sizeof(h));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        scanf("%d%d%d%d",&u,&v,&c,&w);
        addEdge(u,v,c,w);
        addEdge(v,u,0,-w);
    }
    mcmf(s,t);
    printf("%d %d",max_flow,min_cost);
    return 0;
}
*/

/*
zkw费用流暂未了解
*/
