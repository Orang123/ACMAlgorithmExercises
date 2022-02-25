#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 200100
#define INF 0x3f3f3f3f
using namespace std;
//反向建边
/*
题意:n个数,每个数i都可以跳到i+a[i],i-a[i]两个位置,
现在要求出对于每个数从奇数跳到偶数和从偶数跳到奇数需要的最小步数.
链接:https://codeforces.ml/problemset/problem/1272/E
思路:如果考虑正向建边,即i->i+a[i],i->i-a[i],这样在求最短路时,
假如对于a[i]是偶数要求偶数(i)到奇数,那么要跑一遍起点为i的最短路,
对于每个终点为奇数的长度都需要比较求出最短距离,对于其它每个点都得再跑一边最短路,
这样会TLE spfa最坏可达 o(n^3),Dijkstra也超过O(n^2),而n<=2*10^5.
所以考虑反向建边,即:i+a[i]->i i-a[i]->i,设置两个超级源点 0,n+1.分别指向所有的偶点和奇点.权为0.
两次最短路起点分别为0,n+1.这样对于每个点i理论上作为的是终点,但实际因为我们是反向建边，
所以 它仍旧是作为起点 跑到奇偶性质相反的点的最短路,这样只需整体跑一次最短路即可.
*/

int n,cnt,head[N],a[N],vis[N],dis1[N],dis2[N];

struct Node{
    int to,next,w;
}edge[N*3];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s,int *dis){
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n+1;i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s,int *dis){
    init(s,dis);
    queue<int> Q;
    Q.push(s);
    vis[s]=1;
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
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i]&1) addEdge(n+1,i,0);
        else addEdge(0,i,0);
        if(i+a[i]<=n) addEdge(i+a[i],i,1);
        if(i-a[i]>=1) addEdge(i-a[i],i,1);
    }
    spfa(0,dis1);
    spfa(n+1,dis2);
    for(int i=1;i<=n;i++){
        if(a[i]&1){//a[i]是奇数
            /*
            考虑从偶数点跑到i的最短路径,实际是反向建边,对于从i(奇数)到偶数点也是最短可达成立的.
            因为i才是起点,如果按照0,n+1超级源点正向建边 这里只能表示从偶数到奇数,而具体哪个偶数是不知道的,
            因为我们是从0点开始跑的,而且因为是正向边 实际这个i这个点也不一定就是最短的
            */
            if(dis1[i]!=INF) printf("%d ",dis1[i]);
            else printf("-1 ");
        }
        else{//a[i]偶数同理
            if(dis2[i]!=INF) printf("%d ",dis2[i]);
            else printf("-1 ");
        }
    }
    return 0;
}
