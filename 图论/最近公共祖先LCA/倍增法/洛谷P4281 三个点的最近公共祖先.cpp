#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500100
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
    int n,m,a,b,x,y,z,xyz;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&a,&b);
        addEdge(a,b);
    }
    dep[0]=-1;
    dfs(1,0);
    while(m--){
        scanf("%d%d%d",&x,&y,&z);
        //这题采用离线tarjan就很麻烦,因为每个回答要用到三组lca,最后分步处理较麻烦
        int xy=lca(x,y);
        int yz=lca(y,z);
        int xz=lca(x,z);
        /*
        其实题目让求的,准确来讲并不是三个点的lca,
        而是距离三个点最近的那个点，使得三个点距离该点
        距离总和最小，集合花费最低的点.
        但是这个问题可以转化为lca来求.
        这个三个点的lca,必然会有两组的lca是相同的,
        那么距离三个点的最近的点就必然是两组之外不同的那组2个点的lca
        */
        if(xy == yz) xyz=xz;
        else if(xy == xz) xyz=yz;
        else if(yz == xz) xyz=xy;
        printf("%d %d\n",xyz,dis(x,xyz)+dis(y,xyz)+dis(z,xyz));//求解三个点分别距离该集合点的距离之和
        /*
        也可以差分利用深度和lca深度之间的关系,先求出三个点的深度之和再把重合无用lca深度距离剔除掉.
        */
        //printf("%d %d\n",xyz,dep[x]+dep[y]+dep[z]-dep[xy]-dep[yz]-dep[xz]);
    }
    return 0;
}
