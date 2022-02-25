#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5500
#define INF 0x3f3f3f3f
using namespace std;
//prim+dp 10ms

/*
题意:求解最小生成树和非严格次小生成树,如果不连通,输出"No way",
如果不存在非严格次小生成树输出"No second way",如果存在输出非严格
次小生成树的权值和.
链接:https://www.luogu.com.cn/problem/UVA10462
思路:因为有重边,不能用used[N][N]判断是否加入mst了,直接在edge[M<<1]中加入flag标记
是否加入mst,prim时需要用边集编号的异或来同时标记正向边和反向边.之后就是prim+dp记录路径最大
边权,求解非严格次小树.
*/

int n,m,head[N],cnt,dis[N],vis[N],maxLen[N][N],seq[N],sum;

struct state{
    int u,v,dis,id;
    state(int u=0,int v=0,int dis=0,int id=0):u(u),v(v),dis(dis),id(id){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Edge{
    int from,to,next,w,flag;
}edge[M<<1];

void addEdge(int from,int to,int w,int flag){
    edge[cnt]=(Edge){from,to,head[from],w,flag};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    dis[s]=0;
    memset(maxLen,0,sizeof maxLen);
}

int prim(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(s,s,0,0));
    int u,v,num=0;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        Q.pop();
        u=tmp.v;
        if(vis[u]) continue;
        vis[u]=1;
        if(u!=s)
            //标记正向边和反向边加入mst,如果只标记一条边,判断时反向边也会错判成未加入mst的导致结果错误
            edge[tmp.id].flag=edge[tmp.id^1].flag=1;
        sum+=dis[u];
        for(int i=1;i<=num;i++)
            maxLen[seq[i]][u]=maxLen[u][seq[i]]=max(maxLen[seq[i]][tmp.u],dis[u]);
        seq[++num]=u;
        if(num == n) return 1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(state(u,v,dis[v],i));
            }
        }
    }
    return 0;
}

int main(){
    int T,u,v,w,ans,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=cnt=0;
        ans=INF;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w,0);
            addEdge(v,u,w,0);
        }
        if(!prim(1)){
            printf("Case #%d : No way\n",cas);
            continue;
        }
        for(int i=0;i<cnt;i+=2){
            u=edge[i].from;
            v=edge[i].to;
            if(!edge[i].flag)//如果该边未加入mst,则加入该边成环后 去除换上最大边权,记录权值和最小值
                ans=min(ans,sum-maxLen[u][v]+edge[i].w);
        }
        if(ans == INF)  printf("Case #%d : No second way\n",cas);
        else printf("Case #%d : %d\n",cas,ans);
    }
    return 0;
}

/*
//kruskal+树形dp(O(n)) ac 10ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5500
#define INF 0x3f3f3f3f
using namespace std;
//dp[u][v] 代表树上u到v路径上的最大边权
int n,m,fa[N],cnt,head[N],sum,dp[N][N],seq[N],num;

struct Node{
    int to,next,w;
}node[N<<1];

void addEdge(int from,int to,int w){
    node[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

struct Edge{
    int u,v,w,flag;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    memset(dp,0,sizeof dp);
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,num0=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            addEdge(edge[i].u,edge[i].v,edge[i].w);
            addEdge(edge[i].v,edge[i].u,edge[i].w);
            edge[i].flag=1;
            sum+=edge[i].w;
            num0++;
            if(num0 == n-1) break;
        }
    }
    if(num0 == n-1) return 1;
    else return 0;
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
    int T,u,v,ans,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=cnt=0;
        ans=INF;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
            edge[i].flag=0;
        }
        if(!kruskal()){
            printf("Case #%d : No way\n",cas);
            continue;
        }
        num=0;
        dfs(1,-1);//O(n)
        for(int i=1;i<=m;i++){
            u=edge[i].u;
            v=edge[i].v;
            if(!edge[i].flag)
                ans=min(ans,sum-dp[u][v]+edge[i].w);
        }
        if(ans == INF)  printf("Case #%d : No second way\n",cas);
        else printf("Case #%d : %d\n",cas,ans);
    }
    return 0;
}
*/

/*
kruskal/prim+lca(倍增求解树上任意两点间边最大权值)
*/
