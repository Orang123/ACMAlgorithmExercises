#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 1100
#define M 6500
using namespace std;
//ac 344ms tarjan缩点+拓扑排序
//还可缩点构造DAG+最小路径覆盖 在最后面
/*
题意:一个有向图,是否对于任意两点u,v都存在u到v或v到u的一条路径.
链接:http://poj.org/problem?id=2762
思路:注意是存在任意两点u到v或v到u的路径,满足任意一个方向即可,
那么可以先tarjan+缩点构成DAG,只要满足DAG是一条单链即入度为0的点的
个数和出度为0的点个个数都只有一个,若入度为0有2个,则两个入度为0的互不可达,出度同理,
而且要是单链不能有分支,如果有分支2个分支上的点就是互不可达的.判断
分支可以用拓扑排序判断当前队列中的点的个数是否大于1来实现或者也可以采取dfs判断
父亲节点的分支个数,当大于1时就说明有分支.

拓展:如果题目问的是u->v和v->u双向可达的路径,那么只需判断原图是否为SCG(强连通图),
scc个数为1即可.
*/

int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id,inde[N];
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        //可以不设置in判断是否在栈中,直接用block[v]是否被划分到scc,若还没被划分则还在栈中,否则一经出栈划分出scc,需要每次初始化block为0
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

int topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i])
            Q.push(i);
    }
    int u,v;
    while(!Q.empty()){
        if(Q.size()>1) return 0;//如果>1 说明有分支
        u=Q.front();
        Q.pop();
        for(int i=0;i<G[u].size();i++){//POJ 不支持C++11的写法
            v=G[u][i];
            if(!--inde[v])
                Q.push(v);
        }
    }
    //本身就是DAG,不存在闭合回路,无需判断点的个数是否达到了scc的个数. 网上有部分代码 多余判断
    return 1;
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        clock=id=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(block,0,sizeof(block));
        memset(inde,0,sizeof(inde));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            G[i].clear();
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
        if(topSort()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

/*
//ac 344ms
//tarjan缩点+dfs搜索DAG上每一点的分支个数,若大于1则说明分支上的两点互不可达.
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 1100
#define M 6500
using namespace std;

int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id,inde[N],vis[N];
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
        if(!dfn[v]){
            tarjan(v);
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
            block[v]=id;
        }while(v!=u);
    }
}

//不标记 u点 是因为DAG上没有闭合回路,永远不会有返祖边
int dfs(int u){
    int son=0;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!vis[v]){//标记是否被访问,DAG上会有前向边,但子树中的节点已经dfs深度优先访问过
            vis[v]=1;
            son++;
            if(son>1) return 0;//u点儿子数大于1 说明子路径中有分支 返回0,直接退出dfs 退栈.
            if(!dfs(v)) return 0;
        }
    }
    return 1;//没有分支
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        clock=id=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(block,0,sizeof(block));
        memset(vis,0,sizeof(vis));
        memset(inde,0,sizeof(inde));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            G[i].clear();
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                inde[block[v]]++;
                G[block[u]].push_back(block[v]);
            }
        }
        int ans=0;
        for(int i=1;i<=id;i++){
            if(!inde[i]){
                ans++;
                u=i;
            }
        }
        if(ans == 1){//先判断入度为0的 点个数 刚好为1,则从该点开始dfs,否则输出No
            if(dfs(u)) printf("Yes\n");
            else printf("No\n");
        }
        else
            printf("No\n");
    }
    return 0;
}
*/

/*
//ac 344ms tarjan缩点+DAG上最小路径覆盖 最小路径覆盖=顶点数-最大匹配
//若只有一条直链即:最小路径覆盖数为1,则输出Yes,否则输出No
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#define N 1100
#define M 6500
using namespace std;

int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id,vis[N],link[N],ans;
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        //可以不设置in判断是否在栈中,直接用block[v]是否被划分到scc,若还没被划分则还在栈中,否则一经出栈划分出scc,需要每次初始化block为0
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

int hungary(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || hungary(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=clock=id=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(link,0,sizeof(link));
        memset(block,0,sizeof(block));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            G[i].clear();
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])
                G[block[u]].push_back(block[v]);
        }
        for(int i=1;i<=id;i++){
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        if(id-ans == 1) printf("Yes\n");//最小路径覆盖=顶点数-最大匹配
        else printf("No\n");
    }
    return 0;
}
*/
