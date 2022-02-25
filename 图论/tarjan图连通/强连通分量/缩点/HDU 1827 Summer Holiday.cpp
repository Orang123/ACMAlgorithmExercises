#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 1100
#define M 2100
using namespace std;
//ac 187ms
/*
题意:n个联系人,每个人可能有其它人的联系方式,现在Wiskey有事情需要
通知所有人,已知它通知每个人的电话费用,Wiskey不必每个人都通知,通知到
的人可以去通知别的人,问Wiskey最少要通知几人,以及最少花费的电话费.
注意:联系方式是单向的.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1827
思路:求解tarjan缩点求解scc中的最小权值累加和.

拓展:如果联系方式是单向的,也可以用并查集做,但无论联系方式单向还是双向
tarjan求解scc缩点的做法都是可行的.这类问题如果能用并查集做,一般也一定是
能用tarjan求解scc来做.并且tarjan效率要较高些.
*/

int n,m,dfn[N],low[N],val[N],clock,cnt,block[N],cost[N],id,head[N],inde[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            cost[id]=min(cost[id],val[v]);
        }while(v!=u);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(cost,0x3f,sizeof(cost));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])
                inde[block[v]]++;
        }
        int ans=0,sum=0;
        for(int i=1;i<=id;i++){
            if(!inde[i]){
                ans++;
                sum+=cost[i];
            }
        }
        printf("%d %d\n",ans,sum);
    }
    return 0;
}
