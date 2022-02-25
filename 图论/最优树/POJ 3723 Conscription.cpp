#include<cstdio>
#include<algorithm>
#define N 21000
#define M 51000
using namespace std;
//kruskal 329ms

/*
题意:n个女孩m个男孩,现在要征兵,每个人10000元入伍费,
已知男孩和女孩间存在着关系权重d,在一个人已经入伍的条件下,
另一个人入伍的费用为10000-d元,求最少的征兵费用.
链接:http://poj.org/problem?id=3723
思路:首先每个人只能入伍一次费用只能算一次,那么在这个最终的关系网中显然不能有回路,
因为有回路一个人就会入伍多次,那么其实就是求解最大的连通分量边权和.给出的关系不一定
是一个连通集,可能是多个连通分量.所以用kruskal容易些,prim一次只能计算一个连通分量的
最大边权和.这样最终的最小花费就是 10000*(n+m)-sum(max).
*/
int n,m,r,fa[N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w>x.w;
    }
}edge[M];

void init(){
    for(int i=0;i<n+m;i++)
        fa[i]=i;
    sort(edge+1,edge+1+r);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,sum=0,cnt=0;
    for(int i=1;i<=r;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n+m-1) break;
        }
    }
    return sum;
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&r);
        for(int i=1;i<=r;i++){
            scanf("%d%d%d",&u,&v,&w);
            edge[i]=Edge(u,v+n,w);//v+n 表示男生的编号不能和女生编号重合
        }
        printf("%d\n",10000*(n+m)-kruskal());
    }
    return 0;
}
/*
//prim 422ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 21000
#define M 51000
using namespace std;

int n,m,r,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(dis,0,sizeof(dis));
    dis[s]=0;
}

int prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,sum=0,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        sum+=dis[u];
        num++;
        if(num == n+m) return sum;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w>dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return sum;
}

int main(){
    int T,u,v,w,sum;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        scanf("%d%d%d",&n,&m,&r);
        while(r--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v+n,w);
            addEdge(v+n,u,w);
        }
        //原图可能并不连通,但是要把所有连通分量中的最大权值和求出来,需要多次prim,对vis做标记
        for(int i=0;i<n+m;i++){
            if(!vis[i])
                sum+=prim(i);
        }
        printf("%d\n",10000*(n+m)-sum);
    }
    return 0;
}
*/
