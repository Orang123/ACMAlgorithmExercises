#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 500100
using namespace std;
//ac kruskal 50ms prim实现较为繁琐标记点集,第一次还得把其余点距离已标记点集更新再跑prim
//此题枚举子网子集也可以采用爆搜枚举
/*
题意:网络上有n个点(1<=N<=1000),每个点有对应坐标,你的任务是让所有n个点连通,
为此,你可以新建一些边,费用等于两个端点的欧几里得距离的平方.
另外还有q(0<=q<=8)个子网,可以购买,如果你购买了第i个子网,
该子网中的所有结点将变得相互连通,第i个子网的花费为cost[i].
求使所有点连通的最小花费.
链接:https://www.luogu.com.cn/problem/UVA1151
思路:虽然子网可以使得子网内的点都连通,但需要开销cost[i],
也就是说购买子网不一定比直接构建点与点之间连接连边的总体费用低,
那么就无法贪心求解,需要枚举不购买子网以及购买具体哪些子网组合的所有方案,
对于子网的可能组合方案 因为q<=8,所以可以采用二进制位来表示组合,即1<<q-1代表
所有方案的个数.先选取子网,将fa[N]中可能的边连接集合合并,再跑kruskal,比较记录
最小花费.
这里有个小优化:枚举子网组合方案可以在第一次求解mst得出的边集的基础上枚举,
因为即使枚举子网,根据kruskal,加边时还是会选取边权较小加边,那么除了子网已经
连通的点外,在接下来求解mst时所加的边依然是n-1条边内剩下的边,而不会考虑本身排在n-1条
边后的边.
此题不同的是 对于免费边并没有明确指出,而是给出一个集合互通的总体代价.这就需要
枚举出所有情况从而求解出最小的花费,无法从某个角度贪心选取.
*/

int n,m,q,t,fa[N],cost[8],cnt;
vector<int> G[8];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge1[M],edge2[N];

struct Point{
    int x,y;
}point[N];

int getDis(int x1,int y1,int x2,int y2){
    return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}

void init(){
    cnt=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int Union(int a,int b){
    int x=find(a);
    int y=find(b);
    if(x!=y){
        fa[x]=y;
        return 1;
    }
    return 0;
}

int kruskal(int sum){
    for(int i=1;i<=t;i++){
        if(Union(edge2[i].u,edge2[i].v)){
            sum+=edge2[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    int T,u,ans;
    scanf("%d",&T);
    while(T--){
        for(int i=0;i<8;i++)
            G[i].clear();
        scanf("%d%d",&n,&q);
        for(int i=0;i<q;i++){//输入子网
            scanf("%d%d",&m,&cost[i]);
            while(m--){
                scanf("%d",&u);
                G[i].push_back(u);
            }
        }
        m=0;
        for(int i=1;i<=n;i++)//输入点坐标
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){//构建完全图的边集
            for(int j=i+1;j<=n;j++){
                int w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                edge1[++m]=Edge(i,j,w);
            }
        }
        ans=t=0;
        init();
        sort(edge1+1,edge1+1+m);
        for(int i=1;i<=m;i++){//先选择不加入任何子网 求解一次mst,并记录下n-1边
            if(Union(edge1[i].u,edge1[i].v)){
                cnt++;
                ans+=edge1[i].w;
                edge2[++t]=edge1[i];//将mst的边记录到edge2中
                if(cnt == n-1) break;
            }
        }
        //在edge2 n-1条边基础上枚举子网的方案 eg:01010110 代表选择编号为2、3、5、7个子网
        for(int s=1;s<(1<<q);s++){//s代表每个子网选择与否,从1开始,不能一个也不选,总共有8个子网,(1<<8-1) 内的数二进制位代表了 8个子网的状态(选与不选)
            init();
            int sum=0;
            for(int i=0;i<q;i++){
                //也可(s>>i) & 1判断
                if(s&(1<<i)){//s& 1<<i代表编号为i的子网状态为选择 就将子网i内的点加入并查集
                    sum+=cost[i];
                    for(int j=1;j<G[i].size();j++)//这里也同样要判定不能构成回路,因为不同子网会有交集,构成回路 find会死循环
                        if(Union(G[i][0],G[i][j]))//从子网中第二个点开始 都选择和第一个连接,这样find可缩小查询的步长,达到路径压缩的目的
                            cnt++;//这个子网中构造的mst中的边+1
                }
            }
            ans=min(ans,kruskal(sum));
        }
        printf("%d\n",ans);
        if(T) printf("\n");//不同样例输出之间留有空行,最后一个样例后没有空行
    }
    return 0;
}

/*
//dfs爆搜枚举子集+kruskal ac 50ms
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 500100
using namespace std;

int n,m,q,t,fa[N],cost[8],cnt,seq[8],ans;
vector<int> G[8];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge1[M],edge2[N];

struct Point{
    int x,y;
}point[N];

int getDis(int x1,int y1,int x2,int y2){
    return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}

void init(){
    cnt=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int Union(int a,int b){
    int x=find(a);
    int y=find(b);
    if(x!=y){
        fa[x]=y;
        return 1;
    }
    return 0;
}

int kruskal(int sum){
    for(int i=1;i<=t;i++){
        if(Union(edge2[i].u,edge2[i].v)){
            sum+=edge2[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

void dfs(int st,int num,int res){
    if(q-st<res-num) return;//剪枝 当剩下的数小于还需要选取的个数时 结束
    if(num == res){
        int sum=0;
        init();
        for(int i=1;i<=res;i++){
            int j=seq[i];
            sum+=cost[j];
            for(int j=seq[i],k=1;k<G[j].size();k++){
                if(Union(G[j][0],G[j][k]))
                    cnt++;
            }
        }
        ans=min(ans,kruskal(sum));
        return;
    }
    //if(st>=q) return;
    seq[num+1]=st;
    dfs(st+1,num+1,res);
    dfs(st+1,num,res);
}

int main(){
    int T,u;
    scanf("%d",&T);
    while(T--){
        for(int i=0;i<8;i++)
            G[i].clear();
        scanf("%d%d",&n,&q);
        for(int i=0;i<q;i++){//输入子网
            scanf("%d%d",&m,&cost[i]);
            while(m--){
                scanf("%d",&u);
                G[i].push_back(u);
            }
        }
        m=0;
        for(int i=1;i<=n;i++)//输入点坐标
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){//构建完全图的边集
            for(int j=i+1;j<=n;j++){
                int w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                edge1[++m]=Edge(i,j,w);
            }
        }
        ans=t=0;
        init();
        sort(edge1+1,edge1+1+m);
        for(int i=1;i<=m;i++){//先选择不加入任何子网 求解一次mst,并记录下n-1边
            if(Union(edge1[i].u,edge1[i].v)){
                cnt++;
                ans+=edge1[i].w;
                edge2[++t]=edge1[i];//将mst的边记录到edge2中
                if(cnt == n-1) break;
            }
        }
        for(int i=1;i<=q;i++)
            dfs(0,0,i);
        printf("%d\n",ans);
        if(T) printf("\n");//不同样例输出之间留有空行,最后一个样例后没有空行
    }
    return 0;
}
*/
