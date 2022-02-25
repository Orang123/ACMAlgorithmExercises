#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
int head[N],fa[N][20],lg[N],dep[N],cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

void dfs(int u,int fath){
    dep[u]=dep[fath]+1;
    fa[u][0]=fath;
    for(int i=1;i<=lg[dep[u]];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)
            dfs(v,u);
    }
}

int lca(int x,int y){
    if(dep[x]<dep[y])
        swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]];
    if(x == y) return x;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int dis(int x,int y){
    int z=lca(x,y);
    return dep[x]+dep[y]-2*dep[z];
}

int main(){
    int n,q,u,v,a,b;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    dep[0]=-1;
    dfs(1,0);
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&a,&b);
        printf("%d\n",dis(a,b));
    }
    return 0;
}
