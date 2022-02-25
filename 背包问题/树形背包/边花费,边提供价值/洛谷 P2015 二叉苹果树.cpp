/*
题意:有一棵苹果树,如果树枝有分叉,一定是分2叉（就是说没有只有1个儿子的结点）
这棵树共有N个结点（叶子点或者树枝分叉点），编号为1-N,树根编号一定是1。
我们用一根树枝两端连接的结点的编号来描述一根树枝的位置。现在这颗树枝条太多了，
需要剪枝。但是一些树枝上长有苹果。给定需要保留的树枝数量q，求出最多能留住多少苹果。
n<=100,q<=100,w<=30000.
链接:https://www.luogu.com.cn/problem/P2015
思路:树上背包.
dp[i][j]表示以i为根节点的子树恰好保留j个树枝能留下的最多的苹果树.

注意:
dp[i][j]=k表示以i为根的子树在得到苹果数为j个时需要的最少的树枝.
这种表示法会TLE MLE 以边权为背包容量 空间太大,N*M=100*3*10^6=3*10^8
dp转移代码在最后一部分.
*/
//ac 45ms
//dp[i][j]表示以i为根节点的子树恰好保留j个树枝能留下的最多的苹果树.
//dp[u][j]=max(dp[u][j],dp[u][j-k-1]+dp[v][k]+edge[i].w);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int cnt,head[N],n,q,siz[N],dp[N][M];

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    siz[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        siz[u]+=siz[v]+1;
        int m=siz[u]<q?siz[u]:q;
        for(int j=m;j>=1;j--){
            //j-k-1<=siz[u]-siz[v]的dp[u][j-k-1]才是合法的 之前u遍历的边数最多为siz[u]-siz[v]
            //for(int k=min(j-1,siz[v]);k>=0 && j-k-1<=siz[u]-siz[v];k--)//ac
                //dp[u][j]=max(dp[u][j],dp[u][j-k-1]+dp[v][k]+edge[i].w);
            for(int k=max(0,j-1-siz[u]+siz[v]);k<=min(j-1,siz[v]);k++)//ac
                dp[u][j]=max(dp[u][j],dp[u][j-k-1]+dp[v][k]+edge[i].w);
        }
    }
}

int main(){
    int u,v,w;
    cnt=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    memset(dp,0,sizeof(dp));
    dfs(1,-1);
    printf("%d",dp[1][q]);
    return 0;
}

/*
//ac 39ms
//dp[i][j]表示以i为根节点的子树恰好保留j个树枝能留下的最多的苹果树.
//dp[u][j+k+1]=max(dp[u][j+k+1],dp[u][j]+dp[v][k]+edge[i].w);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int cnt,head[N],n,q,siz[N],dp[N][M];

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    siz[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //for(int j=q-1;j>=0;j--){
            //for(int k=0;k+j+1<=q;k++)
                //dp[u][j+k+1]=max(dp[u][j+k+1],dp[u][j]+dp[v][k]+edge[i].w);
        //}
        for(int j=min(siz[u],q-1);j>=0;j--){
            for(int k=0;k<=siz[v] && j+k+1<=q;k++)
                dp[u][j+k+1]=max(dp[u][j+k+1],dp[u][j]+dp[v][k]+edge[i].w);
        }
        siz[u]+=siz[v]+1;
    }
}

int main(){
    int u,v,w;
    cnt=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    memset(dp,0,sizeof(dp));
    dfs(1,-1);
    printf("%d",dp[1][q]);
    return 0;
}
*/

/*
//ac 43ms
//dp[i][j]表示以i为根节点的子树恰好保留j个树枝能留下的最多的苹果树.
//dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k-1]+edge[i].w);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int cnt,head[N],n,q,dp[N][M];

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=q;j>=1;j--){
            for(int k=1;k<=j;k++)
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k-1]+edge[i].w);
        }
    }
}

int main(){
    int u,v,w;
    cnt=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    memset(dp,0,sizeof(dp));
    dfs(1,-1);
    printf("%d",dp[1][q]);
    return 0;
}
*/

/*
//TLE MLE 以边权为背包容量 空间太大,N*M=100*3*10^6=3*10^8
//dp[i][j]表示以i为根的子树在得到苹果数为j个时需要的最少的树枝.
//dp[u][j]=min(dp[u][j],dp[u][j-k-w]+dp[v][k]+1);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 30000
#define INF 0x3f3f3f3f
using namespace std;

int cnt,head[N],n,q,dp[N][M],sum;

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dp[u][0]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        int w=edge[i].w;
        if(v == fa) continue;
        dfs(v,u);
        sum+=w;
        for(int j=sum;j>=w;j--){
            for(int k=0;k<=j-w;k++)
                dp[u][j]=min(dp[u][j],dp[u][j-k-w]+dp[v][k]+1);
        }
    }
}

int main(){
    int u,v,w;
    cnt=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    memset(dp,0x3f,sizeof(dp));
    dfs(1,-1);
    for(int i=sum;i>=0;i--){
        if(dp[1][i]<=q){
            printf("%d",i);
            break;
        }
    }
    return 0;
}
*/
