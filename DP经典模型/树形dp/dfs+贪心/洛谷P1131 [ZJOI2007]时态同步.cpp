#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500010
using namespace std;
typedef long long ll;
//dfs+贪心
/*
题意:一颗n个节点的树,根节点为s,每条边都有权值,
现在要求至少需要在原先边权基础上增加多少权值才能
使得从根节点(s)出发到达每个叶子节点的权值和都一样.
链接:https://www.luogu.com.cn/problem/P1131
思路:要求增加的权值和最少,那么增加权值应该从底向上考虑,尽可能使得子树权值和都相同,
整体调整父节点以上的边权,调整越靠根节点的树枝调整的代价越少。所以可先求出每个父节点u中子树权值和最大,
然后其它子树与这个最大权值作差并累加,这样u节点的每棵子树权值和就都是一样的了,
下次调整时只需要整体调整u节点以上的边权,它的子树边权和就都会增加,这样增加的权值才是最小的.
*/
//dis[u]表示叶子节点到u节点最大边权和
int cnt,n,head[N],dis[N];
ll ans;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //求出叶子节点到u节点最大边权和
        dis[u]=max(dis[u],dis[v]+edge[i].w);
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //对于其余子树小于最大边权和需要增加边权,作差
        ans+=dis[u]-dis[v]-edge[i].w;
    }
}

int main(){
    int n,s,u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&s);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dfs(s,-1);
    printf("%lld",ans);
    return 0;
}
