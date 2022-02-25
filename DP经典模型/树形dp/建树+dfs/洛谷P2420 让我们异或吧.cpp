/*
题意:给出一颗树，它很高兴自己有N个结点。树的每条边上有一个权值。
我们要进行M次询问，对于每次询问，我们想知道某两点之间的路径上
所有边权的异或值。
1<=n,m<=10^5.
链接:https://www.luogu.com.cn/problem/P2420
思路:树形dp.
dp[u]表示从根节点到u的边权的异或值.
这样任意两点(u,v)的边权的异或值就为dp[u]^dp[v]
u和v的lca,根节点到lca的部分会相互抵消.
*/
//ac 317ms 树形dp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 100100
using namespace std;
int n,m,cnt,head[N],ans[N];
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
        if(v!=fa){
            ans[v]=ans[u]^edge[i].w;
            dfs(v,u);
        }
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dfs(1,0);
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        printf("%d\n",ans[u]^ans[v]);//ans[u]^ans[lca]^ans[v]^ans[lca]=ans[u]^ans[v]  重复异或的lca到根节点的那段路径本身会抵消掉.
    }
    return 0;
}

/*
//ac 573ms lca树上倍增
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 100100
using namespace std;
int n,m,fa[N][20],dep[N],lg[N],cnt,head[N],ans[N][20];
struct Node{
    int to,next,w;
}edge[N<<1];

void init(int n){
    memset(head,-1,sizeof(head));
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
}

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u){
    for(int i=1;i<=lg[dep[u]];i++){
        int j=fa[u][i-1];
        fa[u][i]=fa[j][i-1];
        ans[u][i]=ans[u][i-1] ^ ans[j][i-1];
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u][0]){
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            ans[v][0]=edge[i].w;
            dfs(v);
        }
    }
}

int lca(int x,int y){
    int res=0,tmp;
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]){
        tmp=lg[dep[x]-dep[y]];
        res^=ans[x][tmp];
        x=fa[x][tmp];
    }
    if(x == y)
        return res;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            res^=ans[x][i]^ans[y][i];
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    res^=ans[x][0]^ans[y][0];
    return res;
}

int main(){
    int u,v,w;
    scanf("%d",&n);
    init(n);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dfs(1);
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        printf("%d\n",lca(u,v));
    }
    return 0;
}
*/
