#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
typedef long long ll;

/*
题意:给定一棵无根树,假设它有n个节点,节点编号从1到n,
求1-n这n个节点,到其他n-1个节点的距离之和.
链接:http://www.51nod.com/Challenge/Problem.html#problemId=1405
思路:siz[u]代表以u节点为根的子树的所有节点个数
若存在v是u的儿子,假设已知dp[u],那么有siz[v]个节点到v点的距离比到u点的距离少了1,
有n-siz[v]个节点到v节点的距离比到u节点的距离多1.所以dp[v]=dp[u]-siz[v]+n-siz[v]
*/

ll dp[N],head[N],dep[N],siz[N],cnt,n;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

//计算siz[u] dp[1] 固定1节点为根求dp[1]
void dfs1(int u,int fa){
    siz[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dep[v]=dep[u]+1;
        dp[1]+=dep[v];//到整棵树根节点的距离为其余所有节点的深度之和
        dfs1(v,u);
        siz[u]+=siz[v];
    }
}
//由1节点向子节点转移,父节点再分别向子节点转移
void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dp[v]=dp[u]-siz[v]+n-siz[v];
        dfs2(v,u);
    }
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
    dfs1(1,-1);
    dfs2(1,-1);
    for(int i=1;i<=n;i++)
        printf("%lld\n",dp[i]);
    return 0;
}
