#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 50
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:n个点,只能尝试删除编号为2~n-1中的一个点,尽可能使
1点不可达n点,如果不能使其不可达,求其最短路的最大值.
(希望刘老板花更多的钱,问至少准备多少钱).
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5137
思路:因为N<=30,所以暴力枚举删除2~n-1中的一个点跑最短路,记录最大值.
*/

int n,m,cnt,head[N],vis[N],dis[N],sign[N];
struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
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
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(sign[v]) continue;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int u,v,w,ans;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        //枚举删除2~n-1 某一个点
        for(int i=2;i<n;i++){
            sign[i]=1;
            Dijkstra(1);
            sign[i]=0;
            ans=max(ans,dis[n]);
            if(ans==INF) break;
        }
        if(ans!=INF) printf("%d\n",ans);
        else printf("Inf\n");
    }
    return 0;
}
