#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 330
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

/*
题意:n个赛点的构成的赛道(单向),每个赛道有个开放时间和关闭时间,
赛车只能在开放时间内一次性通过赛道,通过每个赛道的时间不同,
求从s赛点到t赛点需要的最短时间.
链接:https://www.luogu.com.cn/problem/UVA12661
思路:因为有每个赛道有开放时间a和关闭时间b,可以用当前所用时间对(a+b)
取模,这样就知道在经过了这么几轮时间后,当前赛车所要通过的赛道处于开放
和关闭的什么时间点,分两种情况判断,一种当前时间+通过赛道时间<=开放时间,
则此次通过赛道的时间就是通过(赛道的时间),若当前时间+通过赛道时间>开放时间,
则赛车通过赛道的时间(开放时间-当前时间+关闭时间(这些是需要等待时间)+通过赛道的时间).
赛车只能一次性地通过赛道.
*/

int n,m,cnt,head[N],vis[N];
ll dis[N];

struct Node{
    int to,next;
    ll a,b,w;
}edge[M];

void addEdge(int from,int to,ll a,ll b,ll w){
    edge[cnt]=(Node){to,head[from],a,b,w};
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
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            ll t=dis[u]%(edge[i].a+edge[i].b);
            ll w;
            //当前时间+通过赛道时间<=开放时间
            if(t+edge[i].w<=edge[i].a)
                w=edge[i].w;//时间就是通过赛道的时间
            else//当前时间+通过赛道时间>开放时间
            //时间就是开放时间-当前时间+关闭时间(这些是需要等待时间)+通过赛道的时间
                w=edge[i].w+(edge[i].a-t)+edge[i].b;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int s,t,u,v,cas=0;
    ll a,b,w;
    while(scanf("%d%d%d%d",&n,&m,&s,&t)!=EOF){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        while(m--){
            scanf("%d%d%lld%lld%lld",&u,&v,&a,&b,&w);
            if(w<=a)//当通过赛道的时间比开放时间还长时,这条边就不可用,不建边,否则会wa
                addEdge(u,v,a,b,w);
        }
        spfa(s);
        printf("Case %d: %lld\n",cas,dis[t]);
    }
    return 0;
}
