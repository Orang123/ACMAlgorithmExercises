#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 500100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
//ac 912ms tarjan缩点构造DAG+spfa最长路
//如果spfa被卡TLE的话,可以考虑拓扑序dp求解路径最大点权和
/*
题意:有向图,n个路口每个路口上设置有ATM机,m条单向道路,
每个ATM机都能取到一定金额的钱,有p个酒吧分布在n个路口上,
每个路口只有一个酒吧,并且不是每个路口都有酒吧,现在一个小偷
要从s点出发,到各个点去抢劫,并且最终他要在一家酒吧庆祝.
每个路口和道路都可多次经过,但只能取一次钱.
链接:https://www.luogu.com.cn/problem/P3627
思路:tarjan缩点构造DAG,spfa计算到达各个酒吧最大点权和.
*/

int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],vis[N],val[N],cost[N],dis[N],bar[N],sccbar[N];
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            if(bar[v]) sccbar[id]=1;//如果v点设置有酒吧,那么其scc内就标记有酒吧
            cost[id]+=val[v];
        }while(v!=u);
    }
}

void spfa(int s){
    queue<int> Q;
    vis[s]=1;
    dis[s]=cost[s];
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int &v : G[u]){
            if(dis[v]<dis[u]+cost[v]){
                dis[v]=dis[u]+cost[v];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,ans=0,s,p;//注意ans要初始化为0,有可能没有酒吧,所以抢劫现金为0
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    scanf("%d%d",&s,&p);
    while(p--){
        scanf("%d",&u);
        bar[u]=1;
    }
    tarjan(s);//只求解s点能到达点的SCC即可
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(!block[u]) continue;//缩点只针对s点能到达的点,所以必须是s点能到达的点的SCC
        if(block[u]!=block[v])//构造DAG
            G[block[u]].push_back(block[v]);
    }
    spfa(block[s]);
    for(int i=1;i<=id;i++){
        if(sccbar[i])//DAG上终点必须有酒吧,若没有一个scc有酒吧,则默认初始值为0
            ans=max(ans,dis[i]);
    }
    printf("%d",ans);
    return 0;
}

/*
//如果spfa被卡超时的话,可以采用DAG上拓扑序求解最大点权和
//ac 943ms tarjan缩点构建s点出发可能到达点的scc+拓扑序求解最大点权和路径
//注意拓扑序要用的DAG只能是从s点出发可达的,不然会影响结果.如果tarjan将整张图构建成DAG,如果初始化不把入度为0都入队,
//会导致个别点入度永远都不能为0,如果将所有入度为0的点都入队会导致不是从s点出发的路径也被算进去,导致结果错误.
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 500100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],val[N],cost[N],dis[N],bar[N],sccbar[N],inde[N];
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            if(bar[v]) sccbar[id]=1;
            cost[id]+=val[v];
        }while(v!=u);
    }
}

void topSort(int s){
    queue<int> Q;
    //当前的拓扑图,s点的入度一定是为0的,因为只构造了以s出发到达的点的DAG,
    //而其余的点的入度只能来源于s或s遍历到的点
    dis[s]=cost[s];
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int &v : G[u]){
            dis[v]=max(dis[v],dis[u]+cost[v]);
            //只有当入度为0时,这时就考虑到了所有从s出发到达v点的路径,只记录最大的dis[v]点权和,
            //这时再让v点入队,开始从v点出发遍历剩下的点
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int u,v,ans=0,s,p;//注意ans要初始化为0,有可能没有酒吧,所以抢劫现金为0
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    scanf("%d%d",&s,&p);
    while(p--){
        scanf("%d",&u);
        bar[u]=1;
    }
    //因为是从s出发,所以只需要求出s能遍历到的scc,实际因为用了topSort要求解s出发路径上最大点权和,
    //为了避免其余s遍历不到的点 在topSort时影响s路径上点入度减为0,也只能求解s能遍历到的scc.
    tarjan(s);
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        //u点遍历到了,v点必然也能遍历到.
        //但u点没遍历到,v点也有可能遍历到,这时如果将这条边构造进DAG,
        //那么topSort时block[v]的入度永远也不能减为0,因为block[s]遍历不到block[u],结果就会出错
        //所以加进DAG的边一定要保证u点是从s出发能遍历到的
        if(!dfn[u]) continue;//这里判断!block[u]也是可以的
        if(block[u]!=block[v]){//构造DAG
            G[block[u]].push_back(block[v]);
            inde[block[v]]++;
        }
    }
    topSort(block[s]);//直接从block[s]出发拓扑
    for(int i=1;i<=id;i++){
        if(sccbar[i])
            ans=max(ans,dis[i]);
    }
    printf("%d",ans);
    return 0;
}
*/
