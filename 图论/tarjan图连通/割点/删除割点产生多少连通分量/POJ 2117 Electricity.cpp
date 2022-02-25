#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
//ac 532ms
/*
题意:一个发电厂网络,为了对其进行评估,我们假设可能发生的最坏事件
是发电厂的一个连接点发生故障,这可能导致网络分裂成几个部分.现在
应该确定在删除其中一个连接点(不计算删除的连接点本身)后网络可能
包含的最大未连接部分的数量.
释义:
对于无向图,求删除一个割点后所能产生的最多的连通分量是多少.
链接:http://poj.org/problem?id=2117
思路:暴力统计删除每个割点后所产生的最大连通分量,对于每个点作为父亲的分支,
如果删除这个点能使得这个分支与它不连通,则分离的连通分量加1.
*/

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int root;
int ans;

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){//O(E) E为边
    dfn[u]=low[u]=++num;
    int v,son=0,conn=0;//conn这里统计的是u节点之后子树所产生的连通分量,结果应该还需要加上u点之前没分离的连通分量个数为1.
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            son++;
            low[u]=min(low[u],low[v]);
            if(u != root && dfn[u]<=low[v])
                conn++;//同一个点每被一个分支作为一次割点,则删除这个点,都会新增加一个连通分量
            //这里不能放在for外面,因为删掉根节点与根节点相连的所有分支都会成为一个连通分量,所以对于每个分支都要conn++
            //如果只是判断该点是否是割点,是可以放在for循环外面的
            //这里son==1,只有一个分支是不记录的,但是当son>=2时,所记录的连通分量实际少记录了一个,所以最后所有结果都得+1
            else if(u == root && son>=2)
                conn++;//同上
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    ans=max(ans,conn);//求取各个点作为割点所能增加的最大连通数
}

int main(){
    int n,m,a,b;
    while(scanf("%d%d",&n,&m) && n||m){
        if(m==0){//若0条边,则有n个连通分量,减少一个点,连通分量为(n-1)个
            printf("%d\n",n-1);
            continue;
        }
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        ans=num=cnt=0;
        while(m--){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            addEdge(b,a);
        }
        int res=0;
        for(int i=0;i<n;i++){
            if(!dfn[i]){
                res++;
                root=i;
                dfs(i,-1);
            }
        }
        //对于割点是根节点的情况,ans实际少记录了一个分支,
        //因为只有son>=2时才开始计数,而只有一个分支时不是割点,但是res恰好补了一个分离的分支
        printf("%d\n",res+ans);//res是原图中的连通分量数,ans为删除一个割点后新增加的连通分量数
    }
    return 0;
}

/*
//另一种求解删除割点后剩余连通分量的写法
//ac 516ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int root;
int ans;

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){//O(E) E为边
    dfn[u]=low[u]=++num;
    int conn=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v])
                conn++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(fa < 0) conn--;
    ans=max(ans,conn);//求取各个点作为割点所能增加的最大连通数
}

int main(){
    int n,m,a,b;
    while(scanf("%d%d",&n,&m) && n||m){
        if(m==0){//若0条边,则有n个连通分量,减少一个点,连通分量为(n-1)个
            printf("%d\n",n-1);
            continue;
        }
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        ans=num=cnt=0;
        while(m--){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            addEdge(b,a);
        }
        int res=0;
        for(int i=0;i<n;i++){
            if(!dfn[i]){
                res++;
                root=i;
                dfs(i,-1);
            }
        }
        //对于割点是根节点的情况,ans实际少记录了一个分支,
        //因为只有son>=2时才开始计数,而只有一个分支时不是割点,但是res恰好补了一个分离的分支
        printf("%d\n",res+ans);//res是原图中的连通分量数,ans为删除一个割点后新增加的连通分量数
    }
    return 0;
}
*/
