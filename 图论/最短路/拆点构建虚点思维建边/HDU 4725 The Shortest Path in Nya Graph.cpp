#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//Dijkstra 421ms
/*
题意:n个节点构成的图,每个节点都处于一个层次,处于相邻的层次之间的
点可以相互访问代价为c,如x层能以代价c访问x+1层中的元素,x+1层同样能
以代价c访问x层中的元素.求从1到n的最小代价。
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4725
思路:对于相邻层之间元素可以相互访问,肯定不能两两元素暴力建边,
可以把每层(x)拆成2个点,一个入点f+2*n,一个出点f+n,
入点连向该层的所有元素,该层的所有元素连向出点,边权为0.
对于x层访问x+1层元素 x+n->(x+1)+2*n x层出点连向x+1层入点
对于x+1层访问x层元素 x+1+n->x+2*n x+1层出点连向x层入点
以上都死单向边.双向边会导致,每层的元素相互之间访问代价为0.
*/

int n,m,cnt,head[3*N],vis[3*N];
ll dis[3*N],c;
struct Node{
    int to,next;
    ll w;
}edge[6*N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        //若n点已经弹出堆 则,dis[n]已经是最小(Dijkstra是贪心弹出当前堆中最小的距离),可以不用再更新了,即结束
        if(u == n) return;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,f,cas=0;
    ll w;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d%lld",&n,&m,&c);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&f);
            addEdge(i,f+n,0);//i连向出点f+n
            addEdge(f+2*n,i,0);//入点f+2*n连向i
        }
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        /*
        实际层数可能会有断层,或者根本达不到n层,
        虽然也将出点和入点相连了,但这本身对求解问题
        是没有什么帮助的,也不影响问题的求解.
        */
        for(int i=1;i<n;i++){
            addEdge(i+n,i+1+2*n,c);//i层出点连向i+1层入点
            addEdge(i+1+n,i+2*n,c);//i+1层出点连向i层入点
        }
        Dijkstra(1);
        if(dis[n] == INF) dis[n] =-1;
        printf("Case #%d: %lld\n",cas,dis[n]);
    }
    return 0;
}

/*
x层的入点和出点还可表示成 2*x-1+n,2*x+n
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[3*N],vis[3*N];
ll dis[3*N],c;
struct Node{
    int to,next;
    ll w;
}edge[6*N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(u == n) return;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,f,cas=0;
    ll w;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d%lld",&n,&m,&c);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&f);
            addEdge(i,2*f+n,0);
            addEdge(2*f-1+n,i,0);
        }
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        for(int i=1;i<n;i++){
            addEdge(2*i+n,2*(i+1)-1+n,c);
            addEdge(2*(i+1)+n,2*i-1+n,c);
        }
        Dijkstra(1);
        if(dis[n] == INF) dis[n] =-1;
        printf("Case #%d: %lld\n",cas,dis[n]);
    }
    return 0;
}

*/
/*
spfa 889ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[3*N],vis[3*N];
ll dis[3*N],c;
struct Node{
    int to,next;
    ll w;
}edge[6*N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
}

void spfa(int s){
    queue <int>Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int T,u,v,f,cas=0;
    ll w;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d%lld",&n,&m,&c);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&f);
            addEdge(i,f+n,0);
            addEdge(f+2*n,i,0);
        }
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        for(int i=1;i<n;i++){
            addEdge(i+n,i+1+2*n,c);
            addEdge(i+1+n,i+2*n,c);
        }
        spfa(1);
        if(dis[n] == INF) dis[n] =-1;
        printf("Case #%d: %lld\n",cas,dis[n]);
    }
    return 0;
}
*/

/*
另一种做法x层出点和x+1层入点共用一个点的做法,比较节约空间,也没有构建没有的断层的边集.
https://blog.csdn.net/zcmartin2014214283/article/details/52775288
#include <iostream>
#include <string.h>
#include <queue>
#include <stdio.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=200005;//这块一定是200000，因为点数增加了一倍
const int maxm=800010;
struct Edge
{
    int to,next,w;
} edge[maxm];
int tot;
int head[maxn];
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w)
{
    edge[tot].to=v;
    edge[tot].w=w;
    edge[tot].next=head[u];
    head[u]=tot++;
}
int d[maxn*2];
bool vis[maxn*2];
struct node
{
    int u,w;
    node(int u,int d):u(u),w(d) {}
};
bool operator < (node a,node b)
{
    return a.w > b.w;
}
void  dijk(int s,int n)
{
    memset(vis,0,sizeof(vis));
    priority_queue<node> que;
    for(int i=0; i<=n; i++) d[i]=INF;
    d[s]=0;
    que.push(node(s,0));
    while(!que.empty())
    {
        node tmp = que.top();
        que.pop();
        int u=tmp.u;
        if(vis[u]) continue;
        vis[u]=true;
        for(int e=head[u]; e!=-1; e=edge[e].next)
        {
            int v=edge[e].to,w=edge[e].w;
            if(vis[v]) continue;
            if(d[u]+w<d[v])
            {
                d[v]=d[u]+w;
                que.push(node(v,d[v]));
            }
        }
    }
}
int a[maxn*2];
int main()
{
    //ios::sync_with_stdio(false);
    int T,n,m,t,u,v,w;
    int cases=1;
    scanf("%d",&T);
    //cin>>T;
    while(T--)
    {
        init();
        memset(a,0,sizeof(a));
        memset(d,0,sizeof(d));
        memset(vis,0,sizeof(vis));
        //cin>>n>>m>>t;
        scanf("%d%d%d",&n,&m,&t);
        int val;
        for(int i=1;i<=n;i++)
            {
                //cin>>val;
                scanf("%d",&val);
                a[i]=val;//a[i]//表示i的层数是val
                vis[val]=1;//这是用来标记这个层是否曾经出现过
            }
            for(int i=1;i<=n;i++)
            {
                if(a[i]==1)//如果是第一层，则只能连到下一层
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]+1]&&a[i]<n)//注意这里一定是a[i]+1，因为要表示的是这层的下一层
                // 如果写成了a[i+1]的话表示的则是i的下一个点的那一层，这样是不对的，只能相邻的层建边
                        addedge(i,a[i]+n+1,t);
                }
                else if(a[i]==n)//如果是第n层，则只能连到上一层
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]-1]&&a[i]>1)
                        addedge(i,a[i]+n-1,t);
                }
                else
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]+1]&&a[i]<n)
                        addedge(i,a[i]+n+1,t);
                      if(vis[a[i]-1]&&a[i]>1)
                        addedge(i,a[i]+n-1,t);
                }
            }
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            //cin>>u>>v>>w;
            addedge(u,v,w);
            addedge(v,u,w);
        }
        dijk(1,n*2);
        if(d[n]==INF)
            d[n]=-1;
       // cout<<"Case #"<<cases++<<": ";
        //cout<<d[n]<<endl;
        printf("Case #");
        printf("%d",cases++);
        printf(": ");
        printf("%d\n",d[n]);

    }
    return 0;
}


*/
