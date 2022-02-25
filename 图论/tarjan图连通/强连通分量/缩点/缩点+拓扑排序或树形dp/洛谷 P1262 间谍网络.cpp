#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 3100
#define M 8500
#define INF 0x3f3f3f3f
using namespace std;
//洛谷P1262 间谍网络
//ac 61ms tarjan缩点+拓扑序
//后面第二种排除不能贿赂间谍做法更优一些
//同FZU 1719 Spy Network 但是FZU的测试数据有点问题
/*
题意:n个间谍之间有m条关系,a->b,代表间谍a掌握了b的所有证据,依次类推,
如果a->b,b->c,c->d,那么只需要掌握间谍a的证据,即可同时掌握b、c、d的
证据,现在有p个间谍可以收贿赂,每个间谍的贿赂钱不同,现在问如果要掌握
所有间谍的证据,最少需要多少钱,如果不能掌握间谍的所有证据,则输出
不能掌控证据的间谍的最小编号.
链接:https://www.luogu.com.cn/problem/P1262 or http://acm.fzu.edu.cn/problem.php?pid=1719
思路:可以tarjan求解scc并求出scc中可贿赂的最小花费,缩点构造DAG,
在DAG上拓扑序求解,当当前出队的节点scc中所有点都不能接受贿赂时,
那么这个scc内所有点的证据都是不能掌握的并且将连接点入度减1,如果连接点入度为0了,再入队,
如果scc内有点能接受贿赂,那么就加上这个scc内最小花费,对连接点并不做入队,并且后面路径也
不用再管了,它们因为入度永远不会为0,也不会入队.这样即可求解出最小花费和所有不能掌握证据
的间谍.
*/
int n,m,p,dfn[N],low[N],id,clk,cnt,block[N],head[N],cost[N],inde[N],ans;
stack<int> s;

struct SCC{
    int id,cost;
    SCC(int id=0,int cost=0):id(id),cost(cost){}
    bool operator < (const SCC &x)const{
        return cost<x.cost;
    }
};
vector<SCC> scc[N];
vector <int> G[N],seq;//seq是不能掌握证据的间谍编号


struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clk;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            scc[id].push_back(SCC(v,cost[v]));
            block[v]=id;
        }while(v!=u);
        sort(scc[id].begin(),scc[id].end());//按照花费从小到大排序 不能收贿赂的间谍本身就是INF
    }
}

void topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i])
            Q.push(i);
    }
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        if(scc[u].front().cost == INF){//如果最小花费 都不收贿赂 那这个SCC就全都不收贿赂 加入seq
            for(SCC &tmp : scc[u])
                seq.push_back(tmp.id);
        }
        else{
            ans+=scc[u].front().cost;
            continue;//u点的证据已经掌握,那么u之后的证据自然就全都掌握,就不必继续入队了.
        }
        for(int &v : G[u]){
            //如果u点不能掌控证据,则需考虑v点
            //按照入度是否为0决定是否入队,如果入度为0了,说明前面的节点没有一个证据是能掌握的,
            //那自然v点的证据就只能考虑v中的间谍是否能收贿赂了来掌握了
            if(!--inde[v])
                Q.push(v);
        }
    }
}

void init(){
    ans=id=clk=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(cost,0x3f,sizeof(cost));
    memset(inde,0,sizeof(inde));
    memset(dfn,0,sizeof(dfn));
    seq.clear();
    for(int i=1;i<=n;i++){
        G[i].clear();
        scc[i].clear();
    }
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    scanf("%d",&p);
    while(p--){
        scanf("%d%d",&u,&v);
        cost[u]=v;
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            inde[block[v]]++;
            G[block[u]].push_back(block[v]);
        }
    }
    topSort();
    if(!seq.size()){
        printf("YES\n");
        printf("%d\n",ans);
    }
    else{
        sort(seq.begin(),seq.end());
        printf("NO\n");
        printf("%d\n",seq.front());
    }
    return 0;
}

/*
//洛谷P1262 间谍网络
//ac 54ms tarjan排除不能贿赂间谍求解scc计算入度为0点的最小花费
//洛谷网友Danny_boodman解析
//2种情况:
//一是有的罪犯既不能贿赂他也没有罪犯能揭发他,那么此题无解,我们在遍历时打上标记,
//然后从小到大枚举,只要遇见没有标记的就输出然后退出即可.
//二是所有的罪犯都能直接或间接地被能贿赂的罪犯揭发.很明显,也有两种情况,一是没有环,
//那么资金就是贿赂那个没有入度的罪犯,二是有环,那么资金就是那个环里罪犯所需资金最小的.
//我们想,如果我们把环里的罪犯缩成一个点,那么全都是前者的情况了.

//这个做法是在一开始的时候tarjan就不处理不能贿赂的间谍,只对能接受贿赂的间谍开始tarjan遍历,
//如果遍历的点没能遍历到那些不能接受贿赂的间谍,那么不接受贿赂我的间谍的证据自然就无法掌握,也就是dfn[i] == 0.
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 3100
#define M 8500
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p,dfn[N],low[N],id,clk,cnt,block[N],head[N],cost[N],min_cost[N],inde[N],ans;
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clk;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            min_cost[id]=min(min_cost[id],cost[v]);
            block[v]=id;
        }while(v!=u);
    }
}

void init(){
    ans=id=clk=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(cost,0x3f,sizeof(cost));
    memset(min_cost,0x3f,sizeof(min_cost));
    memset(inde,0,sizeof(inde));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    init();
    scanf("%d",&n);
    scanf("%d",&p);
    while(p--){
        scanf("%d%d",&u,&v);
        cost[u]=v;
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i] && cost[i]!=INF)//只对能接受贿赂的间谍开始遍历
            dfs(i);
    }
    for(int i=1;i<=n;i++){//按点的编号升序遍历
        //如果存在哪个点没有被tarjan遍历过,说明这个不能贿赂的间谍的证据也没有被其它间谍掌握,自然其证据不能掌握
        if(!dfn[i]){
            printf("NO\n");
            printf("%d\n",i);
            return 0;
        }
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v])
            inde[block[v]]++;
    }
    //最终遍历到的scc缩点后一定都是能掌握到证据的间谍,那么只需加上入度为0的点scc中需要花费最小的间谍即可
    for(int i=1;i<=id;i++){
        if(!inde[i])
            ans+=min_cost[i];
    }
    printf("YES\n");
    printf("%d\n",ans);
    return 0;
}
*/

/*
//FZU 1719 Spy Network http://acm.fzu.edu.cn/problem.php?pid=1719
//ac 78ms tarjan缩点+拓扑序
//但是 FZU 1719 排除不能贿赂间谍的tarjan那种简单做法会wa 不懂.
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 3100
#define M 8500
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p,dfn[N],low[N],id,clk,cnt,block[N],head[N],cost[N],inde[N],ans;
stack<int> s;

struct SCC{
    int id,cost;
    SCC(int id=0,int cost=0):id(id),cost(cost){}
    bool operator < (const SCC &x)const{
        return cost<x.cost;
    }
};
vector<SCC> scc[N];
vector <int> G[N],seq;//seq是不能掌握证据的间谍编号


struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clk;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            scc[id].push_back(SCC(v,cost[v]));
            block[v]=id;
        }while(v!=u);
        sort(scc[id].begin(),scc[id].end());//按照花费从小到大排序 不能收贿赂的间谍本身就是INF
    }
}

void topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i])
            Q.push(i);
    }
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        if(scc[u].front().cost == INF){//如果最小花费 都不收贿赂 那这个SCC就全都不收贿赂 加入seq
            for(int i=0;i<scc[u].size();i++)
                seq.push_back(scc[u][i].id);
        }
        else{
            ans+=scc[u].front().cost;
            continue;//u点的证据已经掌握,那么u之后的证据自然就全都掌握,就不必继续入队了.
        }
        for(int i=0;i<G[u].size();i++){
            int v=G[u][i];
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        ans=id=clk=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(cost,0x3f,sizeof(cost));
        memset(inde,0,sizeof(inde));
        memset(dfn,0,sizeof(dfn));
        seq.clear();
        for(int i=1;i<=n;i++){
            G[i].clear();
            scc[i].clear();
        }
        scanf("%d",&p);
        while(p--){
            scanf("%d%d",&u,&v);
            cost[u]=v;
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                inde[block[v]]++;
                G[block[u]].push_back(block[v]);
            }
        }
        topSort();
        if(!seq.size()){
            printf("YES\n");
            printf("%d\n",ans);
        }
        else{
            sort(seq.begin(),seq.end());
            printf("NO\n");
            printf("%d\n",seq.front());
        }
    }
    return 0;
}
*/
