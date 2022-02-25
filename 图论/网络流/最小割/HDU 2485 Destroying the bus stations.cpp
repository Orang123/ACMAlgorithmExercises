#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 5000
#define INF 0x3f3f3f3f
using namespace std;
//ac 46ms dinic floyd+拆点+最小割
/*
题意:起点1到终点n,有一些单向的边,每条边的时间消耗为1,
破坏中间的一些点,问你摧毁多少个点能让人在k时间内无法到达.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2485
思路:可以用floyd先求出从1到n的最短路,对于从1到n花费时间小于等于k的
建边容量INF,现在问最少删除多少点才能使得这些最短路都断开,可以拆点,i入点,i+n出点,
两点间建容量为1的边,那么现在问题就转化为分离源和汇至少要删多少边,而这些边恰好就是拆点,
,问题就由删点转化为了删边,转化为了求解最小割的问题,那么最小割=最大流.
*/
int n,m,k,st,ed,cnt,head[N],dis[N],vis[N],mp[N][N],a[M],b[M];
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(){
    int sum=0;
    while(bfs(st))
        sum+=dfs(st,INF);
    return sum;
}

void floyd(){
    for(int t=1;t<=n;t++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j]>mp[i][t]+mp[t][j])
                    mp[i][j]=mp[i][t]+mp[t][j];
            }
        }
    }
}

void init(){
    cnt=0;
    st=1,ed=n*2;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i == j) mp[i][j]=0;
            else mp[i][j]=INF;
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            mp[u][v]=1;
            a[i]=u,b[i]=v;
        }
        floyd();
        for(int i=2;i<n;i++)
            addEdge(i,i+n,1);
        addEdge(1,1+n,INF);
        addEdge(n,n+n,INF);
        for(int i=1;i<=m;i++){
            if(mp[1][a[i]]+1+mp[b[i]][n]<=k)//a[i]->b[i] 还需时间1
                addEdge(a[i]+n,b[i],INF);
        }
        printf("%d\n",max_flow());
    }
    return 0;
}

/*
//ac 31ms EK算法 费用流
//这里费用等效于最短路的权值之所以拆点入点和出点间的费用为0,
//是因为拆点间并不存在真实的路径权值,而只有实际的边权才能累加权值和,
//而每条实际的边权容量为INF,费用为1(每条边需要单位时间1通过),而每次搜索到
//一条通过时间小于等于k的增广路增加的残余容量恰好就是拆点间的某个容量1,
//我们可以将其中的某个点删去,使得这条路以及从这条路分支出来的路都使得不能从1走到n.
//之所以spfa搜索增广路退出循环的条件是当前增广路费用权值和>k,是因为后面搜索到的增广路
//权值和只会越来越大,肯定都是大于k的,因此不再考虑直接退出循环.
//1和n拆点间容量无穷,因为可能会有多条从1到达n的最短路
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 5000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<1];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    //若当前增广路最短路大于k,后面搜索的增广路最短路也一定大于k,只会越来越大,
    //因为容量在不断减少,可供选择的边也会越少,而spfa搜索的一定是当前费用和最小的增广路,后面只会越来越大
    return dis[ed]<=k;
}

int mcmf(){
    int sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];//每次增广路的最小残余容量一定是某个拆点间的剩余容量,等效于删除某个点来使得1到n不连通
    }
    return sum;
}

void init(){
    cnt=0;
    st=1,ed=n;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v;
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=2;i<n;i++)
            addEdge(i,i+n,1,0);
        addEdge(1,1+n,INF,0);//1和n拆点间容量无穷,因为可能会有多条从1到达n的最短路
        addEdge(n,n+n,INF,0);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            addEdge(u+n,v,1,1);
        }
        printf("%d\n",mcmf());
    }
    return 0;
}
*/

/*
//ac 873ms 迭代加深搜索 暂时不理解
//题目中要使达到要求要去掉边的条数最少，要求是1到N的距离要大于K，
//那么一定要求取1到N之间的最短路，然后再去掉最短路径中的一个点，
//导致最短路径变长，然后重新求取最短路，做同样的操作，直到最短路径大于K，
//在这个思路中，我们唯一不确定的就是每次去掉的点的具体标号和一共要去掉点的个数，
//我们可以枚举深度，逐步加深，去掉的点我们可以枚举最短路径上的点，递归地进行深度
//优先搜索，查探能不能找到可行解，只要能找到可行解，那么当前深度就是最小深度，
//因为比它小的深度均找不到解
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#define MAX 57

using namespace std;
bool inqueue[MAX];
bool okay[MAX];
int dis[MAX];
int pre[MAX];
int n,m,k;

struct
{
    int v , next;
}e[MAX*MAX<<2];

int head[MAX];
int cc;

void add ( int u , int v )
{
    e[cc].next = head[u];
    e[cc].v = v;
    head[u] = cc++;
}

void spfa ( int u )
{
    memset ( inqueue , 0 , sizeof ( inqueue) );
    memset ( dis , 0x3f , sizeof ( dis ) );
    inqueue[u] = true;
    queue<int> q;
    dis[u] = 0;
    q.push ( u );
    while ( !q.empty())
    {
        int temp = q.front();
        q.pop ();
        inqueue[u] = false;
        for ( int i = head[temp] ; i != -1 ; i = e[i].next )
        {
            int v = e[i].v;
            if ( inqueue[v]||okay[v] ) continue;
            if ( dis[v] > dis[temp] + 1 )
            {
                dis[v] = dis[temp] + 1;
                inqueue[v] = true;
                q.push ( v );
                pre[v] = temp;
            }
        }
    }
}

bool flag = false;
int path[MAX][MAX];

void dfs ( int size )
{
    spfa( 1 );
    if ( dis[n] > k )
    {
        flag = true;
        return;
    }
    if ( size == 0 ) return;
    int cnt = 0;
    for ( int i = n ; i != 1 ; i = pre[i] )
        path[size][cnt++] = i;
    for ( int i = 1 ; i < cnt ; i++ )
    {
        int index = path[size][i];
        if ( okay[index] ) continue;
        okay[index] = true;
        dfs ( size - 1 );
        okay[index] = false;
    }
}


int main ( )
{
    int u,v;
    while ( ~scanf ( "%d%d%d" , &n , &m , &k ), n+m+k )
    {
        cc = 0;
        memset ( head , -1  , sizeof ( head ) );
        for ( int i = 0 ; i < m ; i++ )
        {
            scanf ( "%d%d" , &u ,&v );
            add ( u , v );
        }
        flag = false;
        for ( int i = 0 ; i < n ; i++ )
        {
            dfs ( i );
            if ( flag )
            {
                printf ( "%d\n" , i );
                break;
            }
        }
    }
    return 0;
}
*/
