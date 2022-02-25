#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//Dijkstra 657ms
/*
题意:n个节点的图,每个点都有点权,点与点之间有边权,现在要建立一棵树使得花费最小,
树的一条边的花费定义为:一条边的权*边所在子树所有端点点权的和,
整棵树的花费为所有边的花费,1节点恒为根节点,现在要求取建造整棵树的最小花费.
链接:http://poj.org/problem?id=3013
思路:首先分析样例2:
求花费的组成:
sum=4*40+3*50+2*60+3*(20+40+50+60)+2*30+1*(10+20+30+40+50+60)
=10*1+20*(1+3)+30*(2+1)+40*(4+1+3)+50*(3+1+3)+60*(1+2+3)
=10+80+90+320+350+360
=1210
可以发现:sum=10*1+20*(1+3)+30*(2+1)+40*(4+1+3)+50*(3+1+3)+60*(1+2+3)
这不就是每个点的最短路*该点点权的累加和吗.
实际上最小总花费=每条边(u,v)*v的子树中各结点的点权
                =(提取公因式(相同点权))每个点的点权*从根节点到该点的每条边的边权累加和
                =每个点*该点到根结点的最短路
虽然原图给出的是连通图,并不直接是一棵树,这里实际不用考虑构建一棵生成树,
因为即使构造出了最小树,这里只能得到边权和最小,但影响费用的因素不光是边权,
是边权和点权的乘积,并且最小树可能不唯一,但是不同的最小树构建费用 根据边权乘子树点权和,
可能即使都是最小树,费用也不一样,因为树的形态具体的边权和点的关系，也会影响费用.
而根据边的子树中的点权和乘以边权,实际这个问题就是求解最短路*点权就是最小费用

*/

int n,m,cnt,head[N],vis[N];
ll dis[N],val[N],sum;

struct Node{
    int to,next;
    ll w;
}edge[N<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<ll,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
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
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%lld",&val[i]);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(1);
        int flag=0;
        for(int i=2;i<=n;i++){
            if(dis[i]==INF){//若不连通,则结束输出No Answer
                flag=1;
                break;
            }
            sum+=dis[i]*val[i];
        }
        if(flag)
            printf("No Answer\n");
        else
            printf("%lld\n",sum);
    }
    return 0;
}

/*
spfa 657ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N];
ll dis[N],val[N],sum;

struct Node{
    int to,next;
    ll w;
}edge[N<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void spfa(int s){
    init(s);
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
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%lld",&val[i]);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        spfa(1);
        int flag=0;
        for(int i=2;i<=n;i++){
            if(dis[i]==INF){
                flag=1;
                break;
            }
            sum+=dis[i]*val[i];
        }
        if(flag)
            printf("No Answer\n");
        else
            printf("%lld\n",sum);
    }
    return 0;
}

*/
