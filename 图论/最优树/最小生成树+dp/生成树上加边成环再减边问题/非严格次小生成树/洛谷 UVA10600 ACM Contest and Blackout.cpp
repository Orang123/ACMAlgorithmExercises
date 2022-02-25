#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5500
#define INF 0x3f3f3f3f
using namespace std;
//prim+dp 0ms
/*
题意:学校间存在联系,每个联系存在一定费用,
求取将所有学校联系起来的的最小费用的2种方案.
链接:https://www.luogu.com.cn/problem/UVA10600
非严格次小生成树:求得的次小树边权和大于等于最小树的边权和,并且在其余所有生成树中边权和是最小的.
严格次小生成树:求得的次小树边权和严格大于最小树的边权和,并且在其余所有生成树中边权和是最小的.
区别仅仅是:"大于等于"和"大于".
思路:分别求取最小生成树和非严格次小生成树的权值和.
可以prim+dp或kruskal+树形dp或 prim/kruskal+lca(倍增)
*/

int n,m,head[N],cnt,dis[N],vis[N],used[N][N],maxLen[N][N],seq[N],sum;

struct state{
    int u,v,dis;
    state(int u=0,int v=0,int dis=0):u(u),v(v),dis(dis){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Edge{
    int from,to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof vis);
    memset(used,0,sizeof used);
    memset(dis,0x3f,sizeof dis);
    dis[s]=0;
    memset(maxLen,0,sizeof maxLen);
}

void prim(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(s,s,0));
    int u,v,num=0;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        Q.pop();
        u=tmp.v;
        if(vis[u]) continue;
        vis[u]=1;
        used[tmp.u][u]=used[u][tmp.u]=1;
        sum+=dis[u];
        for(int i=1;i<=num;i++)
            maxLen[seq[i]][u]=maxLen[u][seq[i]]=max(maxLen[seq[i]][tmp.u],dis[u]);
        seq[++num]=u;
        if(num == n) break;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(state(u,v,dis[v]));
            }
        }
    }
}

int main(){
    int T,u,v,w,ans;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        ans=INF;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        prim(1);
        for(int i=0;i<cnt;i+=2){
            u=edge[i].from;
            v=edge[i].to;
            if(!used[u][v])
                ans=min(ans,sum-maxLen[u][v]+edge[i].w);
        }
        printf("%d %d\n",sum,ans);
    }
    return 0;
}

/*
//kruskal+树形dp(O(n)) ac
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5500
#define INF 0x3f3f3f3f
using namespace std;
//dp[u][v] 代表树上u到v路径上的最大边权
int n,m,fa[N],used[N][N],cnt,head[N],sum,dp[N][N],seq[N],num;

struct Node{
    int to,next,w;
}node[N<<1];

void addEdge(int from,int to,int w){
    node[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    memset(used,0,sizeof used);
    memset(dp,0,sizeof dp);
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,num0=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            addEdge(edge[i].u,edge[i].v,edge[i].w);
            addEdge(edge[i].v,edge[i].u,edge[i].w);
            used[edge[i].u][edge[i].v]=used[edge[i].v][edge[i].u]=1;
            sum+=edge[i].w;
            num0++;
            if(num0 == n-1) break;
        }
    }
}

void dfs(int u,int fa){
    seq[++num]=u;//每遍历一个点就将其放入seq数组中,方便dp
    for(int i=head[u];i!=-1;i=node[i].next){
        int v=node[i].to;
        if(v == fa) continue;
        for(int j=1;j<=num;j++)//求解之前遍历过的点到当前点路径上的最大边权
            dp[seq[j]][v]=dp[v][seq[j]]=max(dp[seq[j]][u],node[i].w);//比较之前点到前驱和当前边权的最大值
        dfs(v,u);
    }
}

int main(){
    int T,u,v,ans;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        ans=INF;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        kruskal();
        num=0;
        dfs(1,-1);//O(n)
        for(int i=1;i<=m;i++){
            u=edge[i].u;
            v=edge[i].v;
            if(!used[u][v])
                ans=min(ans,sum-dp[u][v]+edge[i].w);
        }
        printf("%d %d\n",sum,ans);
    }
    return 0;
}
*/

/*
//kruskal+树形dp(O(n^2)) ac
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5500
#define INF 0x3f3f3f3f
using namespace std;

int n,m,fa[N],used[N][N],cnt,head[N],sum,dp[N][N];

struct Node{
    int to,next,w;
}node[N<<1];

void addEdge(int from,int to,int w){
    node[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    memset(used,0,sizeof used);
    memset(dp,0,sizeof dp);
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,num=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            addEdge(edge[i].u,edge[i].v,edge[i].w);
            addEdge(edge[i].v,edge[i].u,edge[i].w);
            used[edge[i].u][edge[i].v]=used[edge[i].v][edge[i].u]=1;
            sum+=edge[i].w;
            num++;
            if(num == n-1) break;
        }
    }
}

void dfs(int rt,int u,int fa){
    for(int i=head[u];i!=-1;i=node[i].next){
        int v=node[i].to;
        if(v == fa) continue;
        dp[rt][v]=dp[v][rt]=max(dp[rt][u],node[i].w);//比较rt到父节点和父节点u到v即当前边权 取最大
        dfs(rt,v,u);
    }
}

int main(){
    int T,u,v,ans;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        ans=INF;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        kruskal();
        for(int i=1;i<=n;i++)//o(n^2) 以每个点作为根节点去遍历到其它点的路径上的最大边权
            dfs(i,i,-1);
        for(int i=1;i<=m;i++){
            u=edge[i].u;
            v=edge[i].v;
            if(!used[u][v])
                ans=min(ans,sum-dp[u][v]+edge[i].w);
        }
        printf("%d %d\n",sum,ans);
    }
    return 0;
}
*/

/*
kruskal/prim+lca(倍增求解树上任意两点间边最大权值)
*/
