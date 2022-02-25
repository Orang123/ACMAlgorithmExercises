#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 105
using namespace std;
//共6种做法 最后一种+kruskal+lca还没做
//暴力跑n-1次kurskal判断法 ac 16ms
/*
题意:判断最小生成树是否唯一.
链接:http://poj.org/problem?id=1679
思路:因为n<=100,可以先跑一次kurskal求出mst权值和,再尝试删掉原mst
中的每一条边,跑kruskal判断是否权值和和之前一样,如果有一样的,则mst
不唯一,如果全都不一样,那么mst是唯一的.时间复杂度O(nmlogm)
*/

struct node{
    int x,y,price;
    bool operator < (const node &a)const{
        return price<a.price;
    }
}edge[N*N];
int vertex[N],n,m;
bool visit[N*N/2];//注意这里是判断删掉的哪条边,数组大小应开N*N,而不是判断点 数组大小开大N,这样会数组越界异常,poj这个题目的re不会报,会报wa

void init(){
    for(int i=1;i<=n;i++){
        vertex[i]=i;
    }
}
int find0(int x){
    if(vertex[x]!=x)
        return vertex[x]=find0(vertex[x]);
    return x;
}
bool unionSet(int x,int y){
    int x0=find0(x);
    int y0=find0(y);
    if(x0!=y0){
        vertex[x0]=y0;
        return true;
    }
    else
        return false;
}
int kruskal(){
    int sum=0,cnt=0;
    init();
    for(int i=0;i<m;i++){
        if(unionSet(edge[i].x,edge[i].y)){
            visit[i]=true;
            sum+=edge[i].price;
            cnt++;
            if(cnt == n-1) return sum;
        }
    }
    return sum;//这里因为 有可能m=0或含有边权为0的边,实际最小树权和为0,但是输出不能输出-1,所以当构不成生成树时也统一输出其权和0
}

int subEdge(int num){
    int sum=0,cnt=0;
    init();
    for(int i=0;i<m;i++){
        if(i!=num&&unionSet(edge[i].x,edge[i].y)){//避开之前最小树编号为num的边看还能不能构成权和一样的最小树
            sum+=edge[i].price;
            cnt++;
            if(cnt == n-1) return sum;
        }
    }
    return -1;
}

int main(){
    int t,sum,ans;
    int flag;
    scanf("%d",&t);
    while(t--){
        memset(visit,false,sizeof(visit));
        flag=0;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++)
            scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].price);
        sort(edge,edge+m);
        sum=kruskal();
        /*
        这个不存在那种 前面边非常小，后面边非常大的这种情形构成的不唯一最小树,
        因为若存在前面更小的边,那第一次的最小树一定会将这些边包含进去的,
        所以还是得考虑有没有和原先最小树哪条边权一样的边看是否能构成树.
        */
        for(int i=0;i<m;i++){
            if(visit[i]){//试着尝试删除原先最小树中每一条边,看其余边能够构成权和相同的最小树
                ans=subEdge(i);
                if(ans==sum){
                    flag=1;
                    break;
                }
            }
        }
        if(flag)
            printf("Not Unique!\n");
        else
            printf("%d\n",sum);
    }
    return 0;
}

/*
//ac 0 ms 676K 第二快的做法
//加边成环,再减边,恢复生成树,如果所减边等于所加边,则mst不唯一.
//prim+dp统计出生成树上所有路径上的最大边权,判断没加入生成树的边两端点上的mst中的最大边权是否和该边权相等,
//如果相等,则说明生成树不唯一.如果未加入的边没有一条和树上路径最大边权相等,则生成树是唯一的.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define N 105
#define M 10005
#define INF 0x3f3f3f3f
using namespace std;
bool vis[N],used[N][N];
//pre[i] 记录i结点的前驱结点,maxLen[i][j]记录mst中路径i到j之间边的最大权值,这也是非mst中的边会和其权值相等的可能情况
int cnt,head[N],dis[N],pre[N],maxLen[N][N],sum,seq[N];
struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

int getCost(int u,int v){
    for(int i=head[u];i!=-1;i=edge[i].next){
        if(edge[i].to == v) return edge[i].w;
    }
    return -1;
}

void init(){
    sum=cnt=0;
    memset(vis,false,sizeof(vis));
    memset(used,false,sizeof(used));
    memset(maxLen,0,sizeof(maxLen));//maxLen[v][v]自己到自己,更新一条边路径时要用到,要初始化为0
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));//个别时候memset INF 会出错
    memset(pre,0,sizeof(pre));//要初始化第一个加入的点的pre[s]=s
}
//核心思想就是考虑不在mst中的边哪些可能的权值会和在mst中的边相等
void prim(int n){
    priority_queue<pair<int,int> > Q;
    dis[1]=0;//最小权第一次源点累加时,还没有边.应该为0
    Q.push(make_pair(dis[1],1));
    int u,v,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        used[pre[u]][u]=used[u][pre[u]]=true;//标记这条无向条边已经加入mst(Minimum Spanning Tree)中
        sum+=dis[u];//累加mst权值和
        //从已经加入mst中的点,枚举每一个点i,记录从i到u路径中边的最大权值,注意i到u之间可能有很多点,
        //不一定是直接连接的,seq[i]=u时,路径为i到i的自环无意义,无需记录,若记录则maxLen[u][u]会有值,不为0,
        //那么在下次加入新边时,seq[i]=pre[u],maxLen[seq[i]][u]=max(maxLen[pre[u]][pre[u]],dis[u])
        //本身这个值肯定是dis[u],但有可能就取成了maxLen[pre[u]][pre[u]],会导致后续的结果出错的,
        //当然此题的数据较弱,刚好每次都较大的都是dis[u],所以也水过了
        for(int i=1;i<=num;i++)
            //比较seq[i]到pre[u]路径中的最大权值与新加入的边pre[u]到u的权值,取最大值
            //maxLen[seq[i]][pre[u]]之前是肯定记录过的,至于为什么取最大值,当在最小生
            //成树某条路径中加入一条边时，必会构成回路，加入的这条边一定是大于等于该路径上
            //权值最大的边,不然这条边一开始就是最小生成树里的边了.例如说i到u的路径
            //我们所取的不是最大边,则在构造mst加入点时,实际中是不可能遗留这条较小的边的,
            //因为这样选择的较大边则mst的权和一定不是最小的,mst每次所取的都是距离当前mst
            //集合点距离最近的点,那这个较小的边也会被提前合并,而不会遗留在先添加较大边的后面。
            //所以非mst中的边一定是大于等于mst中路径中最大权值边的。所以我们只是在确定非mst中边
            //的值可能会和mst某个路径中的那条边权值相同,当刚好相同时则可以替换,这样mst便不唯一.

            //当seq[i]=pre[u]时,虽然maxLen[pre[u]][u]是作为加入mst内的边,不会作为非mst边去比较权值是否
            //相等可替代,但这里还要记录其值因为后续加边在记录maxLen的是否会用到maxLen[seq[i]][pre[u]]的值去比较
            maxLen[seq[i]][u]=maxLen[u][seq[i]]=max(maxLen[seq[i]][pre[u]],dis[u]);//之所以也记录反向边maxLen[u][i]是为了到时比较的时候有可能会先手判断u->i这条边,那么可以较早判断出来唯一性
        num++;
        seq[num]=u;//将已经加入的点存入 seq数组 在maxLen[seq[i]][u] dp完成,再加入u点,因为不能改变maxLen[u][u]的值
        if(num == n) break;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && dis[v]>edge[i].w){
                dis[v]=edge[i].w;
                pre[v]=u;//记录当前加入距离mst集合中距离最小的点的前驱节点,方便更新maxLen
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int t,n,m,u,v,w;
    scanf("%d",&t);
    while(t--){
        init();
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
        }
        prim(n);
        bool flag=false;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int val=getCost(i,j);
                if(!used[i][j] && val!=-1 && val == maxLen[i][j]){//判断未加入mst中的边 是否可能和原先mst中的某条边相等,若相等,则可替换,mst就不唯一
                    flag=true;
                    break;
                }
            }
            if(flag) break;
        }
        if(flag) printf("Not Unique!\n");
        else printf("%d\n",sum);
    }
    return 0;
}

*/

/*
//这个做法是最快的 ac 0ms
//直接在prim每次加入距离集合mst中距离最短的点v时,就判断已经在mst中的点
//u(不能是v本身连接的前驱节点)还有没有到v未加入mst的边权和当前加入的边相等,
//如果有,则说明mst不唯一,如果全部都没有,则说明mst是唯一的.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define N 105
#define M 10005
#define INF 0x3f3f3f3f
using namespace std;
bool vis[N],used[N][N],flag;
int map0[N][N],dis[N],pre[N],sum,seq[N];

void init(){
    sum=0;
    flag=false;
    memset(map0,INF,sizeof(map0));
    memset(vis,false,sizeof(vis));
    memset(used,false,sizeof(used));
    memset(dis,INF,sizeof(dis));//个别时候memset INF 会出错
    memset(pre,0,sizeof(pre));
}

void prim(int n){
    priority_queue<pair<int,int> > Q;
    dis[1]=0;//最小权第一次源点累加时,还没有边.应该为0
    Q.push(make_pair(dis[1],1));
    int u,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        used[pre[u]][u]=used[u][pre[u]]=true;
        sum+=dis[u];
        for(int i=1;i<=num;i++){
            //每加入一条边,就判断当前的mst集合内其余的点除过pre[u]外,能否有一条连向u点权值与当前边权值相同的边,若有,mst不唯一,输入数据保证图是连通的
            if(seq[i]!=pre[u] && map0[seq[i]][u]==dis[u]){
                flag=1;
                return;//存在 立即结束
            }
        }
        seq[++num]=u;
        if(num == n) break;
        for(int i=1;i<=n;i++){
            if(!vis[i] && dis[i]>map0[u][i]){
                dis[i]=map0[u][i];
                pre[i]=u;
                Q.push(make_pair(-dis[i],i));
            }
        }
    }
}

int main(){
    int t,n,m,u,v,w;
    scanf("%d",&t);
    while(t--){
        init();
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            map0[u][v]=map0[v][u]=w;
        }
        prim(n);
        if(flag) printf("Not Unique!\n");
        else printf("%d\n",sum);
    }
    return 0;
}
*/

/*
//ac 16ms
//kruskal+构造生成树+暴力n次树形dp(由父节点向子节点转移)求解所有路径上的最大边权
//因为要求解所有路径所以需要以每个点为根节点遍历,更新到达所有点路径上最大边权,
//之后还是判断未加入mst中的边是否有和加入mst中路径(回路)上的最大边权相等,如有则不唯一,否则唯一.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 105
#define INF 0x3f3f3f3f
using namespace std;
//G[i][j] 用来记录从点i到点j的路径之间最大的边权值 其实也可以用链式前向星替代,这样空间复杂度低一些,题目并不是完全图,用邻接矩阵有点没必要
struct Node{
    int x,y,w;
    bool operator < (const Node &x)const{
        return w<x.w;
    }
}edge[N*N/2];

void init(){
    memset(used,0,sizeof(used));
    memset(G,0x3f,sizeof(G));//这里memset是赋值1字节也就是8位,所以每一字节赋值0x3f,最后G[i][j]的值就是0x3f3f3f3f
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}


//自己写的 dp求解树上根节点到所有点的最大边权 maxLen[rt][v] n次dfs求解以每个点i作为根节点的dp
//状态转移是从父节点向子节点转移,因为路径是不断加边边长的.
//void dfs(int rt,int u,int fa){//O(n^2)
    //for(int i=head[u];i!=-1;i=edge[i].next){
        //int v=edge[i].to;
        //if(v == fa) continue;
        //maxLen[rt][v]=max(maxLen[rt][u],edge[i].w);
        //dfs(rt,v,u);
    //}
//}

//void dfs(int u,int fa){//O(n) dp求解
    //seq[++num]=u;//每遍历一个点就将其放入seq数组中,方便dp
    //for(int i=head[u];i!=-1;i=node[i].next){
        //int v=node[i].to;
        //if(v == fa) continue;
        //for(int j=1;j<=num;j++)//求解之前遍历过的点到当前点路径上的最大边权
            //dp[seq[j]][v]=dp[v][seq[j]]=max(dp[seq[j]][u],node[i].w);//比较之前点到前驱和当前边权的最大值
        //dfs(v,u);
    //}
//}


void dfs(int u,int v, int w){
    vis[v]=1,G[u][v]=w;//记录v点已访问,u到v的路径边上的最大权值
    for(int i=1;i<=n;i++)
        if(!vis[i] && G[v][i]!=INF) dfs(u,i,max(w,G[v][i]));//u的起始点 是一直不变的,i是每次路径遍历的下一个端点
        //大体上就是在mst中找到一条边能否构成回路,若能构成回路 并且这条边和mst中边权相同则mst不唯一,
        //至于这里为什么要记录mst路径上的最大边权,那是因为假如i->j这条构成回路,那么i->j的权值绝对只能
        //大于等于mst中i到j路径上的最大边权,因为如果i->j这条边比最大权值小,那么根据Kruskal每次都取边权
        //最小的边,现在的mst就不是最小生成树了,而是i->j这条边应该纳入mst中
}

int main(){
    int t,u,v,ans;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=0;i<m;i++)
            scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].w);
        sort(edge,edge+m);
        ans=0;
        for(int i=0;i<m;i++){
            u=find(edge[i].x);
            v=find(edge[i].y);
            if(u!=v){
                fa[v]=u;
                ans+=edge[i].w;
                G[edge[i].x][edge[i].y]=G[edge[i].y][edge[i].x]=edge[i].w;//在G 邻接矩阵里初始化某条加入mst中的两端点的权值
                used[i]=1;//记录加入mst中的边
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            dfs(i,i,0);//记录从每个点出发的mst中的路径的边的最大权值
        }
        int flag=0;
        for(int i=0;i<m;i++)
            //若非mst中的边使得mst构成x到y路径上的回路并且边权等于
            //edge[i].x到edge[i].y 路径上的最大边权,则mst不唯一
            if(!used[i] && edge[i].w == G[edge[i].x][edge[i].y]){
                flag=1;
                break;
            }
        if(flag) printf("Not Unique!\n");
        else printf("%d\n",ans);
    }
    return 0;
}

*/

/*
//Oi-wiki做法,此做法暂时还没搞懂 空间(380K)和时间(0ms)都是最优的
//对于 Kruskal 算法，只要计算为当前权值的边可以放几条，实际放了几条，
//如果这两个值不一样，那么就说明这几条边与之前的边产生了一个环
//（这个环中至少有两条当前权值的边，否则根据并查集，这条边是不能放的），
//即最小生成树不唯一。
#include <algorithm>
#include <cstdio>
using namespace std;
struct Edge {
  int x, y, z;
};
int f[100001];
Edge a[100001];
int cmp(const Edge& a, const Edge& b) { return a.z < b.z; }
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) f[i] = i;
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
    sort(a + 1, a + m + 1, cmp);
    int num = 0, ans = 0, tail = 0, sum1 = 0, sum2 = 0;
    bool flag = 1;
    for (int i = 1; i <= m + 1; i++) {
      if (i > tail) {
        if (sum1 != sum2) {
          flag = 0;
          break;
        }
        sum1 = 0;
        for (int j = i; j <= m + 1; j++) {
          if (a[j].z != a[i].z) {
            tail = j - 1;
            break;
          }
          if (find(a[j].x) != find(a[j].y)) ++sum1;
        }
        sum2 = 0;
      }
      if (i > m) break;
      int x = find(a[i].x);
      int y = find(a[i].y);
      if (x != y && num != n - 1) {
        sum2++;
        num++;
        f[x] = f[y];
        ans += a[i].z;
      }
    }
    if (flag)
      printf("%d\n", ans);
    else
      printf("Not Unique!\n");
  }
  return 0;
}
*/

/*
当然判断唯一可以试着用lca倍增去判断 构成环的边权是否等于mst路径上的最大边权,
若等于则说明mst不唯一,否则mst是唯一的.
*/
