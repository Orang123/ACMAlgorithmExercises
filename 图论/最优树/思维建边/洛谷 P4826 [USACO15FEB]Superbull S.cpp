#include<cstdio>
#include<algorithm>
#define N 2100
#define M 2000000
using namespace std;
typedef long long ll;
//kruskal ac 2.98s
/*
题意:n个人两两进行比赛,每次会淘汰1人,每场比赛的得分是2个人
id的异或值,问如何比赛使所有比赛总得分最大.
链接:https://www.luogu.com.cn/problem/P4826
思路:总共会进行n-1场比赛,而每个人和别人的比赛可以看成,
这个人和另外的人有连边,每次比赛只有胜者会接着比赛,这可以
看成对于a-b如果b胜利,那么接下来的连边由b去连如果a胜利,接下来
连边由a去连,所以最终n-1场比赛连边所构成的一定是一棵树,那么现在
问题转化成了在完全图中求解最大生成书的问题.每个人可和其它任意人
进行比赛,因此是完全图,此图为稠密图prim会快些.
*/

int n,m,fa[N],a[N];

struct Edge{
    int u,v;
    ll w;
    Edge(int u=0,int v=0,ll w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w>x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

ll kruskal(){
    init();
    int x,y,cnt=0;
    ll sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){//边权为人id的异或值
            edge[++m]=Edge(i,j,a[i]^a[j]);
        }
    }
    printf("%lld",kruskal());
    return 0;
}

/*
//prim 573ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 2100
using namespace std;
typedef long long ll;

int n,m,a[N],dis[N],vis[N],mp[N][N];

void init(){
    memset(vis,0,sizeof vis);
    memset(dis,0,sizeof dis);
}

ll prim(int s){
    init();
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,num=0;
    ll sum=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        num++;
        sum+=dis[u];
        if(num == n) break;
        for(int v=1;v<=n;v++){
            if(!vis[v] && mp[u][v]>dis[v]){
                dis[v]=mp[u][v];
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return sum;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j)
                mp[i][j]=a[i]^a[j];
        }
    }
    printf("%lld",prim(1));
    return 0;
}
*/
