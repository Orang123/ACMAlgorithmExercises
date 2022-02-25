#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 200
#define M 10000
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:n个站点,每个站点有默认连接的站点不需要转动扳手,想要连接到其它站点
需要转动扳手,现在要从a站点到达b站点,问最少转动的扳手次数,输入的一个连接站点
是默认连接的站点.
链接:http://poj.org/problem?id=1847
思路:spfa,默然站点权0,其它站点权1.
*/
int n,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof dis);
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
    int v,a,b,k;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++){
        scanf("%d",&k);
        for(int j=1;j<=k;j++){
            scanf("%d",&v);
            if(j==1)
                addEdge(i,v,0);
            else
                addEdge(i,v,1);
        }
    }
    spfa(a);
    if(dis[b] == INF) printf("-1");
    else printf("%d",dis[b]);
    return 0;
}
