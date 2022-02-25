#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 200100
using namespace std;
//ac 670ms
/*
题意:n台计算机之间由m条链路链接使其直接或间接连接起来,
这样数据才能通过链路在任意两个计算机间转换,切除某些链路会导致,
计算机间的数据无法转换,把这样的链路叫做网桥,现在有q条新的链接要加入网络,
输出每添加一条新的链接后网桥的数目.
释义:就是问n个点m条边的无向图中,每添加一条边后的所剩的割边的数目.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2460
思路:tarjan求解割边.再在dfs中记录每个节点的前驱节点,在添加一条新边时,
通过前驱节点向前遍历u、v与lca(u,v)构成的环中计算过的割边,将其减掉,
直到dfn[u]==dfn[v]时,也就是u==v时,结束.类似与倍增求解lca的那个过程.
和标准树上倍增lca不同的是,树上倍增lca是会先跳到同一高度,然后再同时跳到lca;
而这里向上跳u和v是不会同时向上跳的,如果跳两次必定是一个节点先跳到lca(u,v),
另一个节点再跳到lca,也有可能v和u在同一分支,那么dfn较大的,
只需一次性跳到dfn较小的另一个节点即可.
*/

int dfn[N],low[N],num,head[N],cnt,pre[N],n,m,ans,vis[N];
struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            pre[v]=u;//记录有环无向图中v的前驱节点,因为这里dfs每个节点也只会遍历一次,
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v]){
                ans++;//割边数+1
                vis[v]=1;//标记以v点为端点的边是割边.因为要求解环中的边,需要向上跳遍历环中的边,所以标记edge[i]边的下标i无法求解该问题
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);//也可以是low[u]=min(low[u],low[v])
    }
}

void lca(int u,int v){
    //这里固定dfn[u]>dfn[v],这样刚好第一个循环调整u的前驱如果dfn[u]<dfn[v]时,
    //再接着循环调整v的前驱使得dfn[v]==dfn[u],避免需要调整两次时,第一个循环不满足,
    //只调整第二个循环,并没有使得u==v到达lca(u,v)
    if(dfn[u]<dfn[v]) swap(u,v);
    /*
    dfn[u]>dfn[v]时,说明u节点是在遍历完了v节点回溯到u和v的lca后,才开始遍历u节点所在的分支的节点,
    那么在u和v节点的lca(u,v)=x,在x-u这段路径中的所有节点y的dfn[y]都是大于dfn[v]的,
    因为tarjan求解割边是dfs深度优先遍历的.所以最终如果v点和u本身不在一个分支,那么u
    一定会跳到lca(u,v)才停止,然后下个循环v再向上跳到lca(u,v),和标准树上倍增lca不同
    的是,树上倍增lca是会先跳到同一高度,然后再同时跳到lca;而这里向上跳u和v是不会同时
    向上跳的,如果跳两次必定是一个节点先跳到lca(u,v),另一个节点再跳到lca,也有可能v和
    u在同一分支,那么dfn较大的,只需一次性跳到dfn较小的另一个节点即可.
    */
    while(dfn[u]>dfn[v]){
        if(vis[u]){
            ans--;
            vis[u]=0;
        }
        u=pre[u];
    }
    while(dfn[v]>dfn[u]){
        if(vis[v]){
            ans--;
            vis[v]=0;
        }
        v=pre[v];
    }
}

int main(){
    int u,v,q,cas=0;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        ans=num=cnt=0;
        memset(dfn,0,sizeof(dfn));
        memset(vis,0,sizeof vis);
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        scanf("%d",&q);
        printf("Case %d:\n",cas);
        while(q--){
            scanf("%d%d",&u,&v);
            lca(u,v);
            printf("%d\n",ans);
        }
        printf("\n");
    }
    return 0;
}
