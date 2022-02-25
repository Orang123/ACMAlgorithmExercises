#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define N 50100
using namespace std;

/*
题意:一颗树求解出删除某个节点后,剩余最大的子树节点数目要最小,
求删除的这样的点都有哪些.
链接:http://poj.org/problem?id=3107
思路:还是经典找重心的思路,只不过需要用dp[u]记录删除u点后剩余的子树中最大的节点数目.
*/

int dp[N],head[N],cnt,n,ans=INF,siz[N];
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    siz[u]=1;
    int maxSiz=-1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        maxSiz=max(maxSiz,siz[v]);
    }
    maxSiz=max(maxSiz,n-siz[u]);
    dp[u]=maxSiz;
    ans=min(ans,maxSiz);
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++){
        if(dp[i] == ans)
            printf("%d ",i);
    }
    printf("\n");
    return 0;
}
