#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
//两次深搜
/*
题意:求解一颗树上两端点最远的距离,即树的直径
链接:http://poj.org/problem?id=2631
思路:两次dfs,第一次dfs求解出从根节点u出发所能走到的单源最长距离,并且记录这个最长距离的终点v.
第二次dfs求解出从终点v开始的单源最长距离,这个最长距离即是树的直径.
树的直径定义:也称树的最长链，定义为一棵树上最远的两个节点的路径，即树上一条不重复经过某一条边的最长的路径
树的直径证明:https://blog.csdn.net/forever_dreams/article/details/81051578
floyd时间和空间上都严重超标,首先O(N^3) 而N=10^4,空间上数组也最大开10^6,而现在空间开销为10^4*10^4=10^8
*/

int cnt,n,head[N],dis[N],ans,st;
//int pre[N];记录树的直径的具体路径

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//O(V+E) bfs也行
void dfs(int u,int fa){
    if(dis[u]>ans){
        ans=dis[u];
        st=u;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=dis[u]+edge[i].w;
        //pre[v]=u;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    while(scanf("%d%d%d",&u,&v,&w)!=EOF){
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    ans=-1;
    dfs(1,-1);
    dis[st]=0;//再从第一次单源最长路径的终点开始搜索,因此初始值为0
    memset(pre,-1,sizeof(pre));
    dfs(st,-1);
    printf("%d",ans);
    /*
    while(st!=-1){
        printf("%d ",st);
        st=pre[st];
    }
    */
    return 0;
}

/*
//树形dp求解  求解具体路径比较麻烦 因为直径是两条路径构成,最大路径和次大路径拼接而成的
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
//dp[u][0]代表子树中叶子节点距离u节点的最大距离
//dp[u][1]代表子树中叶子节点距离u节点的次大距离
int cnt,n,head[N],dp[N][2],ans,st;

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
        //更新最大距离
        if(dp[u][0]<dp[v][0]+edge[i].w){
            dp[u][1]=dp[u][0];//先前的最大距离会变成次大距离
            dp[u][0]=dp[v][0]+edge[i].w;
        }
        else if(dp[u][1]<dp[v][0]+edge[i].w)//考虑更新次大距离
            dp[u][1]=dp[v][0]+edge[i].w;
    }
    //最长的路径就是不同子树距离u点的最大距离与次大距离之和,而各个父节点的这个距离之和的最大值就是树的直径
    //这里不必考虑父节点向上的反向距离,因为随着父节点不断回溯,向上的反向距离就会变成子树距离父节点的距离
    ans=max(ans,dp[u][0]+dp[u][1]);
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    while(scanf("%d%d%d",&u,&v,&w)!=EOF){
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    ans=-1;
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/

/*
另一种树形dp 不知为何wa
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
//dp[u]代表子树中叶子节点距离u节点最远距离
int cnt,n,head[N],dp[N],ans,st;

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
        //考虑当前dp[u](距离u节点的最大距离)与其它子树分支的最大距离之和 各个父节点的这个和的最大值就是树的直径
        //dp[v]+edge[i].w有可能比dp[u]还大,此时dp[u]就变为次大距离,也就是次大距离+最大距离
        ans=max(ans,dp[u]+dp[v]+edge[i].w);
        //更新子树中叶子节点距离u节点的最大距离
        dp[u]=max(dp[u],dp[v]+edge[i].w);
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    while(scanf("%d%d%d",&u,&v,&w)!=EOF){
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    ans=-1;
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/
