#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//取反最短路,反向建边,链式前向星实现
/*
题意:n个农场,每个农场有一头奶牛,农场之间有m条单向道路,
现在要在s农场参加聚会,每头奶牛都需要到达s,然后聚会结束后要再次
返回原地,但因为道路是单向边,一来一回的路径可能是不同的.求每头
奶牛一来一回所需要的最大距离.
链接:http://poj.org/problem?id=3268
思路:s点返回n个奶牛所在地的距离可以从s点跑一遍正向边的最短路求出,
但对于每个奶牛从原所在地n到达s点的距离可以通过反向建边,再跑一遍
从s点出发的最短路,因为现在是反向建边如果s->n是最短,那对于原图,n->s
也会是最短.这个通过建立超级源点,连向每个点,只能求出某个奶牛到达s点的
最短距离,无法求出所有奶牛的.
*/

int n,m,s,cnt1,cnt2,head1[N],head2[N],vis[N],dis1[N],dis2[N];
struct Node{
    int to,next,w;
}edge1[M],edge2[M];

void addEdge1(int from,int to,int w){
    edge1[cnt1]=(Node){to,head1[from],w};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to,int w){
    edge2[cnt2]=(Node){to,head2[from],w};
    head2[from]=cnt2++;
}

void init(int s,int *dis){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s,int *dis,int *head,Node *edge){
    init(s,dis);
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
    int u,v,w,ans=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d%d",&n,&m,&s);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge1(u,v,w);
        addEdge2(v,u,w);
    }
    spfa(s,dis1,head1,edge1);
    spfa(s,dis2,head2,edge2);
    for(int i=1;i<=n;i++)
        ans=max(ans,dis1[i]+dis2[i]);
    printf("%d",ans);
    return 0;
}

/*
//邻接矩阵实现
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,s,mp[N][N],vis[N],dis1[N],dis2[N];

void init(int s,int *dis){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s,int *dis){
    init(s,dis);
    queue <int>Q;
    vis[s]=1;
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int v=1;v<=n;v++){
            if(!mp[u][v]) continue;
            if(dis[v]>dis[u]+mp[u][v]){
                dis[v]=dis[u]+mp[u][v];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,w,ans=0;
    scanf("%d%d%d",&n,&m,&s);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        mp[u][v]=w;
    }
    spfa(s,dis1);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
            swap(mp[i][j],mp[j][i]);
    }
    spfa(s,dis2);
    for(int i=1;i<=n;i++)
        ans=max(ans,dis1[i]+dis2[i]);
    printf("%d",ans);
    return 0;
}
*/


