#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2100
#define M 10010
using namespace std;
//kruskal 32ms
/*
题意:n个农场,贝西要去所有农场,农场间有m条双向道路,
贝西行走时需要补充水量,每条道路的每单位长度需要1盎司水,
到达每个农场后,贝西都可以将水袋补充满,现在求贝西最少需要
携带多大容量的水袋才不至于累到在半路.
链接:http://poj.org/problem?id=2395
思路:求解生成树中的最大边权,即最小瓶颈树,可通过构造mst求得最大边权.
*/

struct Node{
    int u,v,w;
    bool operator <(const Node &x)const{
        return w<x.w;
    }
}edge[M];

int fa[N];

void init(int n){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(int n,int m){
    int x,y,cnt=0;
    for(int i=0;i<m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x != y){
            fa[x]=y;
            cnt++;
            if(cnt == n-1)
                return edge[i].w;
        }
    }
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    sort(edge,edge+m);
    printf("%d\n",kruskal(n,m));
    return 0;
}

/*
//prim 63ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 2100
#define M 10010
using namespace std;

int n,m,cnt,head[N],vis[N],dis[N],ans;

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
    ans=dis[s]=0;
}

int prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        ans=max(ans,dis[u]);
        num++;
        if(num == n) return ans;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return ans;
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    printf("%d",prim(1));
    return 0;
}
*/
