#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;
//ac 16ms
/*
题意:一个电话网络,如果某个电话机出现故障,除了故障所在地无法到达外,
还可能导致其他一些地方无法连接,那么这些地方就是关键,
现在要求出电话网络中这样关键地方的数目.
释义:求解无向图中割点的数目.
链接:http://poj.org/problem?id=1144
思路:tarjan求解无向图割点数目.
*/

int n,dfn[N],low[N],num,cnt,head[N],id,rt,vis[N],ans;
struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v,son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            if(u == rt)
                son++;
            low[u]=min(low[u],low[v]);
            if(u != rt && dfn[u]<=low[v])
                vis[u]=1;
            else if(u == rt && son>=2)
                vis[u]=1;
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v;
    while(scanf("%d",&n) && n){
        ans=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(head,-1,sizeof head);
        memset(vis,0,sizeof vis);
        while(scanf("%d",&u) && u){
            while(getchar()!='\n'){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                rt=i;
                dfs(i,-1);
            }
        }
        for(int i=1;i<=n;i++){
            if(vis[i])
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
