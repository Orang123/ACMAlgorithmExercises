#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:n个点的图,求距离s点最短距离为l的点或边上的点
有多少个.
链接:https://codeforces.ml/problemset/problem/144/D
思路:距离s的点直接跑最短路即可,对于边的处理可以考虑
对于边的两端点u,v,如果dis[u]<l dis[u]+w>l ,则说明这条边上
存在一个点离s距离为l.
*/

int n,m,l,cnt,head[N],dis[N],vis[N];
struct Node{
    int from,to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){from,to,head[from],w};
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
    int u,v,w,s,sum=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    scanf("%d",&l);
    spfa(s);
    for(int i=1;i<=n;i++)
        if(dis[i]==l) sum++;
    for(int i=0;i<cnt;i+=2){//因为u->v v->u会重复算,所以+2刚好跳过反向边
        u=edge[i].from;
        v=edge[i].to;
        w=edge[i].w;
        /*
        因为dis[u]<l && dis[u]+w>l
        考虑靠近u的端点dis[u]+边上某一点x上边权刚好等于l,
        dis[v]+w-(l-dis[u])>l表示对于dis[v],u->v上x靠近v点的另一半里
        存在一点y,对dis[v]有贡献,这表明x y不重合,但这里增加的是x点,
        因为并不清楚dis[v]和l的关系,下个判断就是考虑dis[v]
        */
        if(dis[u]<l && dis[u]+w>l && dis[v]+w-(l-dis[u])>l)//实际就是dis[u]+dis[v]+w>2*l
            sum++;
        if(dis[v]<l && dis[v]+w>l && dis[u]+w-(l-dis[v])>l)//同理
            sum++;
        //u->v边上的一点对于dis[u] dis[v]的贡献刚好满足l,这个两个点刚好重合,所以只算一个点
        if(dis[u]<l && dis[v]<l && dis[u]+dis[v]+w==2*l)
            sum++;
    }
    printf("%d",sum);
    return 0;
}
