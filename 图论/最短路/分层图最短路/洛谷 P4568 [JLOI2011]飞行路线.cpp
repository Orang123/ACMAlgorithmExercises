#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//分层图思维建边做法 498ms 是对边状态的拆分,一种花费w走,一种花费0走
/*
题意:n个点,m条权值为w的双向边,现在要从s点到达t点,
有k次免费通过边的机会,求最小花费.
链接:https://www.luogu.com.cn/problem/P4568
思路:经典分层图最短路.
*/

/*
分层图概念:
对于图中的每个结点u,可以把它拆成k+1个节点, 0<=j<=k,
分别表示当使用j次免费通行权限后到达u号节点的状态。
*/

int n,m,k,s,t,cnt,head[N*11],vis[N*11],dis[N*11];
/*
0~k层每层都有M条双向边,层与层之间对于i层原图存在的一条双向边,
都存在2条有向边与i+1层相连那么相当于每层就有2M条无向边,
总共(k+1)层(k<=10),所以共有(M*2*11)<<1条边.
*/
struct Node{
    int to,next,w;
}edge[(M*2*11)<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}
//O(mklog(nk))
void Dijkstra(int s){
    priority_queue<pair<int,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int u,v,w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    scanf("%d%d",&s,&t);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        /*
        将图分成k+1层即0~k 第0层就是原图节点,编号为u的点在第i层的编号为u+i*n,
        每一层都有同样的n个点,m条边,权值也相同.层与层之间的连边,只能由较低层指向较高层.
        */
        for(int i=0;i<=k;i++){
            //第i层 u->v边权为w的双向边
            addEdge(u+n*i,v+n*i,w);
            addEdge(v+n*i,u+n*i,w);
            if(i){//i不为第0层时,连接上一层到下一层之间边权为0的连边.
                //将第i-1层的u点连向i层v点边权为0,代表使用第i次免费机会,从i-1层u点可直接到达i层v点
                addEdge(u+(i-1)*n,v+i*n,0);
                //将第i-1层的v点连向i层u点边权为0,代表使用第i次免费机会,从i-1层v点可直接到达i层u点
                addEdge(v+(i-1)*n,u+i*n,0);
            }
        }
    }
    Dijkstra(s);
    /*
    首先对于m>k时
    因为对于从s到t所有路径而言,并不是所有路径边数都大于等于k,即存在边数小于k的路径,
    这样s到t所有边都使用免费机会,k还有剩余,最优解就在k层以前,花费为0.因此要比较0~k层t点
    的最小值作为最小花费.
    但是当m<k时,从s到达t的所有路径边数肯定小于等于k,此时s到达t的任意路径花费都为0.
    可以直接输出最小花费,而不必建分层图跑最短路.
    */
    for(int i=0;i<=k;i++)
        ans=min(ans,dis[t+n*i]);
    printf("%d",ans);
    return 0;
}

/*
//这种做法是从状态枚举转移 dp的角度dis数组扩展一个维度来表示分层图的,
//建边和点数还是原图而得空间开销 391ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;

//dis[i][j]代表到达i点用了j次免费机会的最小花费,即i点在第j层图中
//vis[i][j]代表到达i点用了j次免费机会的状态点是否已计算确定过
int head[N],vis[N][11],cnt,dis[N][11],n,k;

struct node{
    int to,next,w;
}edge[M<<1];

struct state{
    int v,w,nowCnt;//w为到达v点使用nowCnt花费的最小费用
    state(){}
    state(int v,int w,int nowCnt):v(v),w(w),nowCnt(nowCnt){}
    bool operator < (const state &x)const{//重载运算符构建小根堆
        return w>x.w;
    }
};

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    //注意初始化对于起点免费次数(0~k)次的状态都要置0
    //这样可以避免s点的 1~k次免费次数状态点被走出去的点反向走回来的更新,会导致枚举很多无意义的状态点
    for(int i=0;i<=k;i++)
        dis[s][i]=0;
}
//复杂度主要在每个点枚举 使用还是不使用免费机会这两个状态,会扩展出很多状态点
//这些入队的状态点个数可能还是要k层图所有的结点个数少
void Dijkstra(int s){
    priority_queue<state> Q;
    init(s);
    Q.push(state(s,0,0));
    int u,v,nowCnt;
    while(!Q.empty()){
        state tmp=Q.top();//弹出当前花费最小的点 去松弛其它结点的花费
        u=tmp.v,nowCnt=tmp.nowCnt;
        Q.pop();
        //这种状态若之前已经弹出堆,计算确定过,之前那个肯定花费最小,因为所有边都是正权边,
        if(vis[u][nowCnt]) continue;
        vis[u][nowCnt]=1;
        //到达v点枚举2个状态点,一种使用免费机会,一种不使用,每次弹堆只取费用最小的点 去松弛其它点
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //这里有可能前面几次都使用免费机会刚好替换掉费用较大的边,那这种状态就是较优的,反之则不是
            //当前使用免费机会次数少于k次 还可以尝试使用一次免费机会
            if(nowCnt<k && dis[v][nowCnt+1]>dis[u][nowCnt]){
                dis[v][nowCnt+1]=dis[u][nowCnt];//花费为之前的到达u点的花费
                Q.push(state(v,dis[v][nowCnt+1],nowCnt+1));//入堆
            }
            //若不使用免费机会则不判断是否到达使用免费次数上限,只判断当前免费次数下费用是否能更少
            //这里若实际花费走过的边花费刚好是较小的,把后续的航班花费较大的边用免费机会替代,则这种状态是较优的,反之则不是
            if(dis[v][nowCnt]>dis[u][nowCnt]+edge[i].w){
                dis[v][nowCnt]=dis[u][nowCnt]+edge[i].w;//更新费用
                Q.push(state(v,dis[v][nowCnt],nowCnt));//入堆
            }
        }
    }
}

int main(){
    int m,s,t,a,b,c,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    scanf("%d%d",&s,&t);
    while(m--){
        scanf("%d%d%d",&a,&b,&c);
        addEdge(a,b,c);//构建正权无向图
        addEdge(b,a,c);
    }
    Dijkstra(s);
    //统计到达t终点 在各个i(0~k)次数下最小的花费
    //因为并不是所有路径的边数都大于k
    for(int i=0;i<=k;i++)
        ans=min(ans,dis[t][i]);
    printf("%d",ans);
    return 0;
}
*/
