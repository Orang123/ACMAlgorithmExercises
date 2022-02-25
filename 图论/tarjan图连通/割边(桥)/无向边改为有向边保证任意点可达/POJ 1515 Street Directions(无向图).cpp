#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define M 1000100
using namespace std;
//ac 172ms
/*
题意:将无向图中的边改为有向边,使得有向图中任意两点之间仍旧
连通相互可达,对于单向边只输出其方向边的两端点,对于必须是双向的
边同时输出其正反两方向的端点.原图保证连通.
链接:http://poj.org/problem?id=1515
思路:显然,只有原图不在环里的边才必须是双向的,那么就是桥.
剩下的单向边实际结果是不唯一的,就按照tarjan dfs序标记一个方向就好,
因为只是将原先的2个方向只保留其中一个方向,并不是删掉某条边.
所以就是tarjan求桥.
*/
int n,m,dfn[N],low[N],clock,cnt,head[N],cas;

struct Edge{
    int from,to,next,flag;
}edge[M];

void addEdge(int from,int to,int flag){
    edge[cnt]=(Edge){from,to,head[from],flag};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(edge[i].flag!=-1) continue;//如果不为-1 说明这个边的方向之前已经确定过
        edge[i].flag=1;//标记当前方式为要保留的有向边反向
        edge[i^1].flag=0;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                edge[i^1].flag=1;//对于割边 那么正反2个方向都要保留,edge[i]之前已经标记过了.
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    cas++;
    clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v,-1);//-1代表这条边的方向还未确定
            addEdge(v,u,-1);
        }
        dfs(1,-1);//原图保证是连通的.
        printf("%d\n\n",cas);
        for(int i=0;i<cnt;i++){
            if(edge[i].flag)
                printf("%d %d\n",edge[i].from,edge[i].to);
        }
        printf("#\n");
    }
    return 0;
}
