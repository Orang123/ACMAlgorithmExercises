#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
using namespace std;

/*
题意:一棵树求删除哪些个节点后,可使得剩余子树最大节点数不超过总节点数的一半.
链接:http://poj.org/problem?id=2378
思路:还是经典找重心的思路,只不过需要用dp[u]标记删除u点后剩余的子树中最大的节点数目是否不超过n/2.
*/

int dp[N],head[N],cnt,n,siz[N];
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
    if(maxSiz<=n/2) dp[u]=1;
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
        if(dp[i])
            printf("%d\n",i);
    }
    return 0;
}
