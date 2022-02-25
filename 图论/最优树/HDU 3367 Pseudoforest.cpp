#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
typedef long long ll;
//296ms kruskal
/*
此题prim算法的思想和题意不符,因为对于输入为一个连通集时,
prim求出的永远也只是一个连通集,而kruskal 求出的可能是多个连通集,结果可能不同,
而题目要求为伪森林(pseudoforest),显然要求在求解过程中会有分裂,因此prim不符合
题意.
*/
/*
题意:n个点的图(伪森林),要求求取所有连通子集的最大权值和,
每个连通子集最多有一个环.给出的图不是完全图,也不一定连通.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3367
思路:kruskal,在求解最大生成树的基础上,对于一条边两端点不在同一连通集的
情况,只要两个连通集不都有环就可以连接,否则连接起来会产生2个环和题意不符,
对于一条边两端点在同一连通集的,这个连通集不能有环,否则也会产生2个环.fa数组
除了记录祖先,还有有个数组记录连通集环的个数.
*/

int n,m;

struct Fa{
    int ptr;
    int cnt;
}fa[N];

struct Edge{
    int u,v;
    ll w;
    bool operator < (const Edge &x)const{
        return w>x.w;
    }
}edge[M];

void init(){
    sort(edge+1,edge+1+m);
    for(int i=0;i<n;i++){
        fa[i].ptr=i;
        fa[i].cnt=0;
    }
}

int find(int x){
    return fa[x].ptr==x?x:fa[x].ptr=find(fa[x].ptr);
}

ll kruskal(){
    init();
    int x,y;
    ll sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y && fa[x].cnt+fa[y].cnt<2){//不在同一连通集 环的个数和要小于2
            if(fa[x].cnt>fa[y].cnt)
                swap(x,y);
            fa[x].ptr=y;//x指向y,更新祖先中的cnt环的个数为1
            sum+=edge[i].w;
        }
        else if(x == y && fa[x].cnt+fa[y].cnt == 0){//在同一连通集 本身不能有环,加边后会产生一个环
            fa[y].cnt=1;//更新祖先cnt环的个数为1
            sum+=edge[i].w;
        }
    }
    return sum;
}

int main(){
    int u,v;
    ll w;
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d%d%lld",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("%lld\n",kruskal());
    }
    return 0;
}

/*
//wa prim不符合题意
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N];
ll sum;

struct Edge{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void prim(int s){
    priority_queue<pair<ll,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,num=0,flag=0;
    pair<ll,int> tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.second;
        Q.pop();
        if(vis[u]){
            //如果这个点已被加入集合,如果原先集合还没有环,则加入这条较大的边产生一个环
            if(!flag){
                sum+=tmp.first;
                flag=1;
            }
            continue;
        }
        vis[u]=1;
        num++;
        sum+=tmp.first;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v])
                Q.push(make_pair(edge[i].w,v));
        }
    }
}

int main(){
    int u,v;
    ll w;
    while(scanf("%d%d",&n,&m) && n+m){
        cnt=sum=0;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        for(int i=0;i<n;i++)//原图可能不是连通图,有多个连通子集
            if(!vis[i])
                prim(i);
        printf("%lld\n",sum);
    }
    return 0;
}
*/
