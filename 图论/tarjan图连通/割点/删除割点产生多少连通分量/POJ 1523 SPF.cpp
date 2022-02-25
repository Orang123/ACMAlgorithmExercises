#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define M 500100
using namespace std;
//ac 0ms
/*
题意:无向图中,求删除每个割点后所产生的连通分量数.
链接:http://poj.org/problem?id=1523
思路:tarjan求解无向图割点,记得结果还要+1.
*/

int n,dfn[N],low[N],num,head[N],cnt,ans[N],rt;
struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            if(u == rt)
                son++;
            low[u]=min(low[u],low[v]);
            if(u!=rt && dfn[u]<=low[v])
                ans[u]++;
            //这里记录根节点作为割点所产生的的连通分量一定要在for里面,因为每个分支都得计算
            else if(u == rt && son>=2)
                ans[u]++;
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,cas=0;
    while(scanf("%d",&u) && u){
        cas++;
        num=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(ans,0,sizeof ans);
        scanf("%d",&v);
        addEdge(u,v);
        addEdge(v,u);
        n=max(n,max(u,v));
        while(scanf("%d",&u) && u){
            scanf("%d",&v);
            n=max(n,max(u,v));
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=1;i<=n;i++){
            rt=i;
            dfs(i,-1);
        }
        printf("Network #%d\n",cas);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(ans[i]){
                //除过根节点其余节点切除后fa->u左端的还有一个连通分量
                //根节点本身是少记录了一个分支的连通分量,所以所有结果都得+1.
                printf("  SPF node %d leaves %d subnets\n",i,ans[i]+1);
                flag=1;
            }
        }
        if(!flag) printf("  No SPF nodes\n");
        printf("\n");
        n=0;
    }
    return 0;
}
