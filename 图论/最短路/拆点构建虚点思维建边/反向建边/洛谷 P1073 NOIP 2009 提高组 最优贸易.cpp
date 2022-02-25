#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 500100
#define INF -0x3f3f3f3f
using namespace std;
//分层图最短路
//下面第二种方法是反向建边
/*
题意:n个城市,m条道路,一种商品在每个城市的价格都不同,
现在从1出发,选择在某个城市买入,某个城市卖出,使得差价
最大,以赚取最大利润,并且能回到n点,求最大差价,城市之间
道路行走没有花费.
链接:https://www.luogu.com.cn/problem/P1073
思路:这个买卖过程可以分为三个阶段
1.从1出发选择在某个城市买入 第0层
2.之后在选择在某个城市卖出  第1层
3.卖出后要回到n点           第2层
很明显可以构建一个3层的分层图最长路.
其中第0层到第1层间的连边代表在某点买入,边权为负.
第1层到第2层间的连边代表在某点卖出,边权为正.其余边权都为0.
这样通过构建分层图就可将点权转化为边权进而转化为一个最短路模型去解决.
*/

int n,m,cnt,head[N*3],vis[N*3],dis[N*3];
//三层图 边数按全是双向边算 (M*3)<<1+层间买卖有向边2*N
struct Node{
    int to,next,w;
}edge[((M*3)<<1)+N*2];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,-0x3f,sizeof(dis));
    dis[s]=0;
}
//注意Dijkstra因为贪心思维,不可求解最长度问题
void spfa(int s){
    queue<int> Q;
    init(s);
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]<dis[u]+edge[i].w){
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
    int u,v,z;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&z);
        addEdge(i,i+n,-z);//第0层到第1层连边,代表在i点买入
        addEdge(i+n,i+2*n,z);//第1层到第2层连边,代表在i点卖出
    }
    while(m--){
        scanf("%d%d%d",&u,&v,&z);
        addEdge(u,v,0);//三层图间的道路边权都为0
        addEdge(u+n,v+n,0);
        addEdge(u+2*n,v+2*n,0);
        if(z == 2){//z==2 构建双向边
            addEdge(v,u,0);
            addEdge(v+n,u+n,0);
            addEdge(v+2*n,u+2*n,0);
        }
    }
    spfa(1);//计算从1到3*n节点的最长路 3*n节点代表在第2层买卖完成后回到n节点
    if(dis[3*n]!=INF) printf("%d",dis[3*n]);
    else printf("0");
    return 0;
}

/*
//构建反向边 分别从1、n开始跑2次spfa,记录路径最小点权和最大点权
//取dis2[i]-dis1[i]最大值
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt1,cnt2,head1[N],head2[N],vis[N],dis1[N],dis2[N],val[N];

struct Node{
    int to,next;
}edge1[M<<1],edge2[M<<1];

void addEdge1(int from,int to){
    edge1[cnt1]=(Node){to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node){to,head2[from]};
    head2[from]=cnt2++;
}
//计算1到v点路径上的最小点权 实际就是买入的点能到达当前v点 对于双向边而言有可能会重复遍历,
//再次回到前驱节点 更新最小值 列如样例的4节点 实际遍历是1->4->5->4,4点被更新了两次
void spfa1(int s){
    memset(vis,0,sizeof(vis));
    memset(dis1,0x3f,sizeof(dis1));
    dis1[s]=val[s];
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head1[u];i!=-1;i=edge1[i].next){
            v=edge1[i].to;
            if(dis1[v]>min(dis1[u],val[v])){
                dis1[v]=min(dis1[u],val[v]);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}
//计算n到v点路径上的最大点权 实际就是v点能到达卖出的点(最大值)
//实际对于样例 5点会重复更新两次 即5->4->5
void spfa2(int s){
    memset(vis,0,sizeof(vis));
    memset(dis2,-0x3f,sizeof(dis2));
    dis2[s]=val[s];
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head2[u];i!=-1;i=edge2[i].next){
            v=edge2[i].to;
            if(dis2[v]<max(dis2[u],val[v])){
                dis2[v]=max(dis2[u],val[v]);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,z,ans=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    while(m--){
        scanf("%d%d%d",&u,&v,&z);
        addEdge1(u,v);
        //构建反向边 若从n能到i,那么对于正向边而言就一定能从i到n,这样在最大差价基础上才能保证能到达n点
        addEdge2(v,u);
        if(z == 2){
            addEdge1(v,u);
            addEdge2(u,v);
        }
    }
    spfa1(1);
    spfa2(n);
    for(int i=1;i<=n;i++)
        ans=max(ans,dis2[i]-dis1[i]);
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 建图dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define N 51000
#define M 500100
using namespace std;

int n,m,head[N],cnt,ans,val[N],pric[N],mi[N];
struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

//minv 要作为临时变量传入,若是全局变量,记录的某个最小值,
//在下一次回溯到另一条路径时,原先这个最小值和新的路径可能并不是相通的.
//这种树形dp的做法是比较暴力的,感觉实际效率并不高,数据加强一些就会TLE

void dfs(int u,int fa,int minv){
    int flag=1,tmp;
    minv=min(minv,val[u]);
    //mi数组记录访问能够访问到该点的所有路径中的价值的最小值,
    //作用是剪枝 避免重复遍历,当之前的路径存在双向边,
    //并且有最小价值能访问到深度遍历到另一条路径时,会先沿着这条路径回来把另一条路径深度遍历完,
    //这条路径的各个点mi记录下这个最小值,这样最开始第一次访问这个分叉点回溯再去访问这另一条路径时就不必重复访问,
    //因为mi[i]数组已经记录了之前的最小值,虽然这时的minx还是最先开始的较大值,因此不满足mi[u]>minv.
    if(mi[u]>minv){//这条路径该点访问过的最小值是否比当前遍历到这个点的最小值大,若大则更新
        mi[u]=minv;
        flag=0;
    }
    tmp=max(pric[fa],val[u]-minv);//记录最大差价
    if(tmp>pric[u]){//判断是否比之前的差价更大
        pric[u]=tmp;
        flag=0;
    }
    if(flag) return;//两种情况满足任意一种 可继续遍历,否则结束.
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v,u,minv);
    }
}

int main(){
    int u,v,z;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) mi[i]=INF;
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&z);
        addEdge(u,v);
        if(z == 2) addEdge(v,u);
    }
    dfs(1,0,INF);//这里得从1开始,因为从别的点开始 可能会导致,单向边无法遍历到前面满足情况的:先遍历价值小的再遍历价值大的情况.
    printf("%d\n",pric[n]);
    return 0;
}
*/

/*
//还有记忆化搜索的做法,不过不太好理解
//也有tarjan做法 不过不太好理解,也有点没必要强行用tarjan去做
*/
