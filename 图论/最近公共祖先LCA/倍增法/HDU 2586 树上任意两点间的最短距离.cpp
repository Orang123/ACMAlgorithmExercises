#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 40100
int head[N],fa[N][21],cost[N][21],dep[N],lg[N],n,m,cnt;//cost[i][k]���� ��i�ڵ���������ϵ�2^k�η������ȵľ���
struct Node{
    int to,next,w;
}edge[N<<1];
/*
d(u,v)=dep[u]-lca(u,v)+dep[v]-lca(u,v)=dep[u]+dep[v]-2*lca(u,v)
u��v����ĳ��ȵ���u��v�����֮�ͼ�ȥu��v��lca��2��
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
        cost[u][i]=cost[fa[u][i-1]][i-1]+cost[u][i-1];//�ȼ���u����2^(i-1)�η�����(j)�ľ���,�ټ���j�����2^(i-1)�η����ȵľ��� ����ۼ�
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath){
            cost[v][0]=edge[i].w;//v���丸��֮��ľ���Ϊedge[i].w
            dfs(v,u);
        }
    }
}

int lca(int x, int y){
    int ans=0;
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]){
        ans+=cost[x][lg[dep[x]-dep[y]]-1];//�ۼӵ�ǰ����������Ծ���������֮��ľ���
        x=fa[x][lg[dep[x]-dep[y]]-1];
    }
    if(x == y) return ans;
    for(int i =lg[dep[x]]-1;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            ans+=cost[x][i];//ͬʱ�ۼ�x��y������Ծ��������ȵľ���
            ans+=cost[y][i];
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    ans+=cost[x][0];//���ǵ�lca�ľ��벢δ�ۼ�
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
