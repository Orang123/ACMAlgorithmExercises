#include<cstdio>
#include<algorithm>
#define N 110
#define M 6000
using namespace std;
//Kruskal 克鲁斯卡尔算法 从边考虑
/*
题意:要在n个村庄铺路,输入会给出n个村庄连的n(n-1)/2条距离(完全图),
现在求村庄铺路的最小长度.
注:这题是一定会连通的,因为是完全图.一般对于不连通的情况题目会给出输出说明.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1233
思路:最小树模板题.
*/

int n,m,fa[N];

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            sum+=edge[i].w;
            cnt++;
            //在这里直接return 会出错,n=1时并不会进入这个循环,没有路要铺,返回的是0
            if(cnt == n-1) break;
        }
    }
    //对于1个点0条边的情况 cnt=0=n-1 其实是连通的但不会进入循环,所以判断不连通一定要在循环外围判断cnt!=n-1,不能再循环里设置flag
    //一般除非题目对不连通的情况输出有要求,
    //才在cnt==n-1时设置标记,其余情况即使不连通,还是输出最小权值和
    return sum;
}

int main(){
    while(scanf("%d",&n)&&n){
        m=n*(n-1)/2;
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("%d\n",kruskal());
    }
    return 0;
}
/*
//prim 普里姆算法 从点考虑
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 6000
using namespace std;
//minimum spanning tree(最小生成树)
int n,m,head[N],cnt,dis[N],vis[N];

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
    dis[s]=0;//这里要初始化 因为出堆后sum+=dis[u]
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
        sum+=dis[u];
        num++;
        if(num == n) return sum;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //这里有可能后续扩展到的点边权更小一些,导致先前加入mst的点边权是较大的,因此要更新dis
            //这里会更新导致重复加入mst,sum结果就偏大,所以加入mst一定要判断必须为mst之外的点
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    //mst中的点数达不到n,说明原图不连通,此题是完全图所以不会有这种情况
    //如果只要求输出最小费用,对于不连通的情况,prim需要对每个连通分量都跑一次,用vis做判断
    return -1;
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)&&n){
        cnt=0;
        memset(head,-1,sizeof(head));
        m=n*(n-1)/2;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        printf("%d\n",prim(1));
    }
    return 0;
}

*/
