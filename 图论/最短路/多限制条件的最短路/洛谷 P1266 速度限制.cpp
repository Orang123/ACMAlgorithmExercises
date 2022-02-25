#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 150
#define M 25000
#define INF 1e18
using namespace std;
//分层图最短路 dp状态转移
/*
题意:n个城市(编号0~n-1),m条单向道路,每个道路有长度和一定限速,
限速为0时,需要按照当前速度继续前行,现在求从0点开始到达D
点,所花费的最少时间,其中初始速度为70.
链接:https://www.luogu.com.cn/problem/P1266
思路:通过每个道路的时间为道路长度/最高限速,但是当限速为0时,
通过这条道路的时间就取决于到达该点的初始速度,那么对于到达点v
所花费的时间而言,不能单方面的以时间来判别,因为到达该点的时间少,
但是初始速度太小,通过当前道路所花费的时间就会越大,而即使到达v点
花费时间较多,但是初始速度较大,通过当前道路所花费时间就越少,这样当
这条道路本身长度很大时,可能最终到达v点本身花费时间较多,初始速度较大
的情况到达终点D花费总时间较少,就是说对于限速为0的边,不同的初始速度,
会影响后续的边权,那么就需要在原先时间花费上再添加一个速度因素,
所以分层图最短路,这样dis[i][j]代表以速度j到达i点的时间花费.
实际就相当于按照速度分层建立的图.但是因为速度V<=500,
直接构建分层图的空间、时间代价太大(实际也不太好建立),
所以只考虑状态转移dp的办法.
*/

int n,m,t,cnt,head[N],vis[N][510],preu[N][510],prev[N][510];
double dis[N][510];

struct state{
    int u,v;
    double dis;
    state(int u=0,int v=0,double dis=0):u(u),v(v),dis(dis){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next,v;
    double l;
}edge[M];

void addEdge(int from,int to,int v,double l){
    edge[cnt]=(Node){to,head[from],v,l};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    //浮点数不能用memset 0x3f赋值初始化 会出错
    for(int i=0;i<n;i++){
        for(int j=1;j<510;j++)
            dis[i][j]=i==s?0:INF;
    }
}

void Dijkstra(int s){
    priority_queue<state> Q;
    init(s);
    Q.push(state(s,70,0));
    int u,v,nowV,edgeV;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.u,nowV=tmp.v;//nowV为到达前驱节点u的初始速度
        Q.pop();
        if(vis[u][nowV]) continue;
        vis[u][nowV]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //如果当前道路速度限制不为0,通过该道路的速度就为道路限速
            //如果当前道路速度限制为0,通过该道路的速度就为初始到达u点的速度
            edgeV=edge[i].v?edge[i].v:nowV;
            if(dis[v][edgeV]>dis[u][nowV]+edge[i].l/edgeV){
                dis[v][edgeV]=dis[u][nowV]+edge[i].l/edgeV;
                preu[v][edgeV]=u;//记录以速度edfeV到达v点的前驱节点.
                prev[v][edgeV]=nowV;//记录以速度edfeV到达v点的前驱节点的初始速度
                Q.push(state(v,edgeV,dis[v][edgeV]));
            }
        }
    }
}

void print(int x,int v){
    if(!x){
        printf("0");
        return;
    }
    print(preu[x][v],prev[x][v]);
    printf(" %d",x);
}

int main(){
    int x,y,v;
    double l,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&t);
    while(m--){
        scanf("%d%d%d%lf",&x,&y,&v,&l);
        addEdge(x,y,v,l);
    }
    Dijkstra(0);
    for(int i=1;i<510;i++){//比较求出到达终点最小花费以及速度
        if(ans>dis[t][i]){
            v=i;
            ans=dis[t][i];
        }
    }
    print(t,v);//输出路径
    return 0;
}
