#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 40100
int head[N],fa[N][21],cost[N][21],dep[N],lg[N],n,m,cnt;//cost[i][k]代表 从i节点距离其向上第2^k次方个祖先的距离
struct Node{
    int to,next,w;
}edge[N<<1];
/*
d(u,v)=dep[u]-lca(u,v)+dep[v]-lca(u,v)=dep[u]+dep[v]-2*lca(u,v)
u与v结点间的长度等于u与v的深度之和减去u与v的lca的2倍
*/
void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

void dfs(int u,int fath){
    fa[u][0]=fath;
    dep[u]=dep[fath]+1;
    for(int i=1;i<=lg[dep[u]]-1;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
        cost[u][i]=cost[fa[u][i-1]][i-1]+cost[u][i-1];//先计算u到第2^(i-1)次方祖先(j)的距离,再计算j到其第2^(i-1)次方祖先的距离 最后累加
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath){
            cost[v][0]=edge[i].w;//v到其父亲之间的距离为edge[i].w
            dfs(v,u);
        }
    }
}

int lca(int x, int y){
    int ans=0;
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]){
        ans+=cost[x][lg[dep[x]-dep[y]]-1];//累加当前所能向上跳跃的最大祖先之间的距离
        x=fa[x][lg[dep[x]-dep[y]]-1];
    }
    if(x == y) return ans;
    for(int i =lg[dep[x]]-1;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            ans+=cost[x][i];//同时累加x、y向上跳跃到最大祖先的距离
            ans+=cost[y][i];
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    ans+=cost[x][0];//他们到lca的距离并未累加
    ans+=cost[y][0];
    return ans;
}

int main(){
    int x,y,w,T;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n-1;i++){
            scanf("%d%d%d",&x,&y,&w);
            addEdge(x,y,w);
        }
        for(int i=1;i<=n;i++)
            lg[i]=lg[i-1]+(1<<lg[i-1] == i);
        dfs(1,0);
        while(m--){
            scanf("%d%d",&x,&y);
            printf("%d\n",lca(x,y));
        }
    }
    return 0;
}
