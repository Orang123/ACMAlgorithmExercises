#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
//dfs求树的直径
/*
题意:一个n个节点的无向树,每条边都有权值,两个人从s节点出发，
这两个人分头遍历这棵树，最后要将所有的树边都遍历完,遍历一条边的花费为树边权的值,
这两个人不要求最后回到出发点,求这两人遍历完这棵树边的最小花费.
链接:http://poj.org/problem?id=1849
思路:一个人遍历一条路径到叶子节点时,要再去遍历别的路径就一定要往回走,那么所有走过的路径里,
只有最后走的路径只走了一次,其它路径都走了2次,要求最小花费,只要树中最长的路径走一次,其它路径走两次,
这样花费就是最少的,之所以最终走一遍的路径是直径是因为这两个人是从同一出发点出发走不同路径的,要想花费最小,
那么2个人所走次数算下来,刚好直径只走了一遍时,才是最小花费.而且真实所走情况可能是,第一个人走过的,第二个人又会过来走,
然后对于直径刚好还是只走了一次,所以最终除了直径路径外其他路径都走了2遍,所以最小花费就是sum*2-直径权
相关题解示意:https://blog.csdn.net/Dilly__dally/article/details/82229776
*/

int cnt,n,s,head[N],dis[N],sum,st,ans;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    if(ans<dis[u]){
        ans=dis[u];
        st=u;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=dis[u]+edge[i].w;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&s);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        sum+=w;
    }
    ans=-1;
    dfs(1,-1);
    dis[st]=0;
    dfs(st,-1);
    printf("%d",sum*2-ans);
    return 0;
}

/*
bfs求树的直径
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 100010
using namespace std;

int cnt,n,s,head[N],dis[N],sum,ans,vis[N];

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void bfs(){
    queue <int>Q;
    Q.push(s);
    while(!Q.empty()){
        int u=Q.front();
        vis[u]=1;
        if(dis[u]>ans){
            ans=dis[u];
            s=u;
        }
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(vis[v]) continue;
            dis[v]=dis[u]+edge[i].w;
            Q.push(v);
        }
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&s);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        sum+=w;
    }
    ans=-1;
    bfs();
    dis[s]=0;
    memset(vis,0,sizeof(vis));
    bfs();
    printf("%d",sum*2-ans);
    return 0;
}
*/
