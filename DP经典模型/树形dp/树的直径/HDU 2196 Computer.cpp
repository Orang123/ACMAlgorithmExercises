#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
using namespace std;

/*
题意:求解一棵树上各个节点距离其它节点的最远距离
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2196
思路:树上某个节点距离其它节点最远的点一定不会比距离树的直径的两个端点还远,因此
先求解树的直径,在求解其余点距离树直径两端点的距离,求取距离两端点的最大值作为结果.
也有树形dp求解最大/次大距离以及反向最大距离的做法
*/
int cnt,n,head[N],dis1[N],dis2[N],ans,st;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    if(dis1[u]>ans){
        st=u;
        ans=dis1[u];
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis1[v]=dis1[u]+edge[i].w;
        dfs(v,u);
    }
}

int main(){
    int v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=2;i<=n;i++){
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
            addEdge(v,i,w);
        }
        ans=-1;
        dfs(1,-1);
        dis1[st]=0;
        ans=-1;
        dfs(st,-1);
        for(int i=1;i<=n;i++) dis2[i]=dis1[i];//dis2记录距离直径第一次求出的端点的距离
        dis1[st]=0;
        dfs(st,-1);//dis1记录距离直径第二次求出的端点的距离
        for(int i=1;i<=n;i++)
            printf("%d\n",max(dis1[i],dis2[i]));//输出直径两端点距离的最大值
    }
    return 0;
}

/*
//只用一个dis数组 记录距离两端点的最大值
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
using namespace std;


int cnt,n,head[N],dis[N],ans,st;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//sum代表从st点出发现在所走的权值和
void dfs(int u,int fa,int sum){
    if(sum>ans){
        st=u;
        ans=sum;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=max(dis[v],sum+edge[i].w);//dis[v]取距离直径两端点的最大距离
        dfs(v,u,sum+edge[i].w);
    }
}

int main(){
    int v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(dis,0,sizeof(dis));
        memset(head,-1,sizeof(head));
        for(int i=2;i<=n;i++){
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
            addEdge(v,i,w);
        }
        ans=-1;
        dfs(1,-1,0);
        ans=-1;//避免直径权值和没有之前大,而记录不到直径的另一端点
        dfs(st,-1,0);
        dfs(st,-1,0);
        for(int i=1;i<=n;i++)
            printf("%d\n",dis[i]);
    }
    return 0;
}
*/
