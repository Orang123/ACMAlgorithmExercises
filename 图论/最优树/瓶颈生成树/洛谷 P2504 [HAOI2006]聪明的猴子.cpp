#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1200
#define INF 0x3f3f3f3f
using namespace std;
//因为是完全图所以用prim,ac 112ms
/*
题意:n棵树有坐标,有m个猴子,每个猴子有最大跳跃距离,
现在问最多有多少个猴子能在n棵树中的任意两棵树之间跳跃.
链接:https://www.luogu.com.cn/problem/P2504
思路:就是n个点的完全图,要想让更多猴子能在n棵树间自由跳跃,
那就要n棵树间的相互连通的树之间的距离最大值尽可能小,
显然就是求瓶颈生成树中的最大边,可以用mst求出,
再判断有多少个猴子跳跃距离大于等于最大边权.
*/

int a[N],bx[N],by[N],maxLen,head[N],cnt,dis[N],vis[N];
struct Node{
    int to,next,w;
}edge[N*N];
/*
有很少条边或弧的图称为稀疏图，反之称为稠密图。
这里稀疏和稠密是模糊的概念，都是相对而言的。目前为止还没有给出一个量化的定义。
比方说一个有100个顶点、200条边的图，与100个顶点组成的完全图相比，他的边很少，也就是所谓的稀疏了。
用n 表示图中顶点数目，用e表示图中边或弧的数目
稀疏图： e < nlogn
稠密图:  e >nlogn
Prim算法适合稠密图，Kruskal算法适合稀疏图，可以使用prim和kruskal两种方法。
因为Kruskal是从边去考虑的,对于一个图而言若边数远远大于点数,那么Kruskal的对边排序和遍历每一个边复杂度显然偏大,
这时如果采用prim算法从点数去考虑则复杂度会降低很多,这一点在完全图问题上prim算法效率极高
在图论的数学领域，完全图是一个简单的无向图，其中每对不同的顶点之间都恰连有一条边相连。
n个端点的完全图有n个端点以及n(n − 1) / 2条边，以Kn表示。
*/
void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    memset(dis,INF,sizeof(dis));
    dis[0]=0;//这里因为记录最大边权时 第一次会用到dis[0]为了避免一直记录这个INF,所以初始化为0
}
/*
这里prim的思想就是 每次都取距离当前最小树集合各个点距离最近的那个点并入最小树集合,
并且用这个点从新扩展更新 别的点距离最小树集合的距离,若比之前的距离还小则更新,一直重复,
直到并入了所有的结点,构建最小树完成,所构建的最小树边权和自然是最小的,同样是贪心
*/
void prim(int n){//O((n+m)log n) 感觉是O(nlogn+m)
    priority_queue <pair<int,int> >Q;
    init();
    Q.push(make_pair(dis[0],0));//构建最小树默认从编号为0的这棵树开始,这里的距离dis[0]其实用不上
    int u,v,num=0;
    while(!Q.empty()){//每次循环都有一个点并入最小树集合,总共有n个点 循环n次
        u=Q.top().second;//这里弹出的u是 距离当前最小树集合中点距离最小的点,将其并入最小树集合
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;//已经并入最小树的点需要标记
        num++;
        maxLen=max(maxLen,dis[u]);//记录最小树中最大的边权 这里可以记录最优树的权值之和 即最小权
        if(num == n) break;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && dis[v]>edge[i].w){// !vis[v]判断 必须是和原先最小树集合中的连相互不连通的点,否则会构成回路,导致错误建树
                dis[v]=edge[i].w;//更新 从最小树集合到达v点的距离,取最小的,之前也许dis[v]也已经设置过,但是连接v点的边权并不是最小的
                Q.push(make_pair(-dis[v],v));//将v点扩展入堆
            }
        }
    }
}

int main(){
    int m,n;
    memset(head,-1,sizeof(head));
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",a+i);
        a[i]*=a[i];
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d %d",&bx[i],&by[i]);
    int k=0,w;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){//这里显然是按照完全图去建边的,边数远远大于点数，所以prim算法效率会更高
            w=(bx[j]-bx[i])*(bx[j]-bx[i])+(by[j]-by[i])*(by[j]-by[i]);
            addEdge(i,j,w);//prim采用Dijkstra的思想,因此需要构造无向图,双向边
            addEdge(j,i,w);
        }
    }
    prim(n);
    int ans=0;
    for(int i=0;i<m;i++){
        if(a[i]>=maxLen)
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}

/*
//kruskal ac 764ms
#include<cstdio>
#include<algorithm>
#define N 1200
using namespace std;

//这些猴子非常聪明，它们通过目测就可以准确地判断出自己能否跳到对面的树上。
//猴子的最大跳跃距离,统计有多少个猴子可以在这个地区露出水面的所有树冠上觅食。
//那么只要猴子的最大跳跃距离大于 树与树之间最大距离,则可以从任意2棵树之间跳跃,
//其实这题目生成树 权值和最小的思想并不很强,更多地只是在考察 实际问题转化为理论模型
//的抽象建模能力

//洛谷网友soul_maker理解:
//MST具有的一个性质：“MST的最大边权是这个图所有生成树的最大边权中最小的。
//”对于一只猴子，它能否跳到每棵树上，取决于它跳跃的生成树的最大边权是否会超过它的跳跃限度，
//而MST可以做到“最大边权最小”，如果某只猴子按照MST来跳跃，就可以尽量的把跳跃的最大边权控制到最小，
//这样就很好的划分出来了。

int a[N],bx[N],by[N],fa[N],maxLen;
struct Node{
    int x,y,w;
    bool operator < (const Node &s)const{
        return w<s.w;
    }
}edge[N*N/2];

void init(int n){
    for(int i=0;i<n;i++)
        fa[i]=i;
}

int Find(int x){
    if(fa[x]!=x)
        return fa[x]=Find(fa[x]);
    else
        return x;
}

bool Union(int x,int y){
    int a=Find(x);
    int b=Find(y);
    if(a!=b){
        fa[a]=b;
        return true;
    }
    else return false;
}

void kruskal(int k,int n){
    int cnt=0;
    init(n);
    for(int i=0;i<k;i++){
        if(Union(edge[i].x,edge[i].y)){//O(MlogN) 这个应该是需要数学的推导才能证明出来
            maxLen=edge[i].w;
            cnt++;
            if(cnt == n-1){
                maxLen=edge[i].w;
                return;
            }
        }
    }
}

int main(){
    int m,n;
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",a+i);
        a[i]*=a[i];
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d %d",&bx[i],&by[i]);
    int k=0;
    for(int i=0;i<n;i++){
        //j从i+1开始,因为一条连边(无向边)它会记录这2个顶点,没必要重复记录这2个相同的顶点,并查集的无向图
        //图论的模型思想并不很强,主要是集合的并集思想,有别于无向图前向星构建双向边那种形式
        for(int j=i+1;j<n;j++){
            edge[k].x=i;
            edge[k].y=j;
            edge[k++].w=(bx[j]-bx[i])*(bx[j]-bx[i])+(by[j]-by[i])*(by[j]-by[i]);
        }
    }
    sort(edge,edge+k);//O(MlogM)
    kruskal(k,n);//kruskal综合复杂度为O(MlogM) 复杂度主要在于边数
    int ans=0;
    for(int i=0;i<m;i++){
        if(a[i]>=maxLen)//猴子的最大跳跃距离大于 树与树之间最大距离,则可以从任意2棵树之间跳跃,树是连通无回路的
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}

*/
