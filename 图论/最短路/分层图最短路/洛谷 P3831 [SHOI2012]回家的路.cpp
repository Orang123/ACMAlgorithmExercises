#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f
using namespace std;
//思维建边方式 403ms
//状态转移方式因为只有2层,可以横向纵向线路分别建在两个图里,Dijk时枚举切换线路即可
/*
题意:n*n的网格图,横向或纵向走一条边花费2,由横向转向纵向
或由纵向转向横向花费1,但这样的站点只有m个,给出起点和终点,
问从起点到终点最少花费多少时间.
链接:https://www.luogu.com.cn/problem/P3831
思路:首先n<=20000,n*n个点中实际有用的点就是那m个可供站内换乘的点,
只需构建m个点间的连边即可,但是实际对于当前走的状态需要区分横向和纵向,
这样对于站内换乘点在切换方向时就要多花1分钟,所以可以建2层图,一层存放
横向走的边,另一层存放纵向走的边,对于每个点构造两层之间对应点交互的双向边.
输入和n无关
*/
//建立k=1的双层图
int n,m,cnt,head[N<<1],dis[N<<1],vis[N<<1];

struct Pos{
    //因为排序会打乱原有的编号,因此要将实现确定好的点的编号记录下来,这样 纵向建边的点才能和横向建边的点对应起来
    int x,y,id;
}pos[N];

bool cmpx(Pos a,Pos b){
    if(a.x!=b.x) return a.x<b.x;
    else return a.y<b.y;
}

bool cmpy(Pos a,Pos b){
    if(a.y!=b.y) return a.y<b.y;
    else return a.x<b.x;
}
//横向N条边 纵向N条边 2层之间每个点一条边,共N条边 又因为双向边,所以3N*2
struct Node{
    int to,next,w;
}edge[N*3*2];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s){
    priority_queue<pair<int,int> > Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        //最终对于终点m+2 既有可能从横向到达也有可能纵向到达,但先出队的一定是最小花费
        if(u == m+2 || u == m+2+m+2) return dis[u];
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
    return -1;//不可达终点
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);//输入和n无关
    //m+1 m+2个点是起点和终点
    for(int i=1;i<=m+2;i++){
        scanf("%d%d",&pos[i].x,&pos[i].y);
        pos[i].id=i;
    }
    //按照横向线路优先排序
    sort(pos+1,pos+1+m+2,cmpx);
    for(int i=1;i<m+2;i++){
        if(pos[i].x == pos[i+1].x){//在同一横线上,相邻两个站点构造边
            //0层图编号id
            addEdge(pos[i].id,pos[i+1].id,(pos[i+1].y-pos[i].y)*2);
            addEdge(pos[i+1].id,pos[i].id,(pos[i+1].y-pos[i].y)*2);
        }
    }
    //按照纵向线路优先排序
    sort(pos+1,pos+1+m+2,cmpy);
    for(int i=1;i<m+2;i++){
        if(pos[i].y == pos[i+1].y){//在同一纵线上,相邻两个站点构造边
            //1层图编号为id+(m+2)
            addEdge(pos[i].id+m+2,pos[i+1].id+m+2,(pos[i+1].x-pos[i].x)*2);
            addEdge(pos[i+1].id+m+2,pos[i].id+m+2,(pos[i+1].x-pos[i].x)*2);
        }
    }
    /*
    与一般分层图不同的是,这里两层之间的边为双向边,因为对于同一个点
    既能从横向切换到纵向,也能从纵向切换到横向.
    */
    for(int i=1;i<=m;i++){
        addEdge(i,i+m+2,1);
        addEdge(i+m+2,i,1);
    }
    //对于起点 既可以先走横向也可以先走纵向
    addEdge(m+1,m+1+m+2,0);
    printf("%d",Dijkstra(m+1));
    return 0;
}

/*
//分层图最短路 dp做法 355ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f
using namespace std;
//dis[u][0]代表从u开始走横向线路
//dis[u][1]代表从u开始走纵向线路
int n,m,cnt[2],head[N][2],dis[N][2],vis[N][2];

struct state{
    int v,dis,sign;
    state(int v=0,int dis=0,int sign=0):v(v),dis(dis),sign(sign){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Pos{
    int x,y,id;
}pos[N];

bool cmpx(Pos a,Pos b){
    if(a.x!=b.x) return a.x<b.x;
    else return a.y<b.y;
}

bool cmpy(Pos a,Pos b){
    if(a.y!=b.y) return a.y<b.y;
    else return a.x<b.x;
}
//edge[cnt][0] 存放横向边
//edge[cnt][1] 存放纵向边
struct Node{
    int to,next,w;
}edge[N<<1][2];

void addEdge(int from,int to,int w,int k){
    edge[cnt[k]][k]=(Node){to,head[from][k],w};
    head[from][k]=cnt[k]++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s][0]=dis[s][1]=0;
}

int Dijkstra(int s){
    priority_queue<state> Q;
    init(s);
    Q.push(state(s,0,0));//起点开始 枚举横向、纵向2种线路走法
    Q.push(state(s,0,1));
    int u,v,k;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,k=tmp.sign;
        if(u == m+2) return dis[u][k];
        Q.pop();
        if(vis[u][k]) continue;
        vis[u][k]=1;
        //k=0 代表更新横向站点 k=1代表更新纵向站点
        for(int i=head[u][k];i!=-1;i=edge[i][k].next){
            v=edge[i][k].to;
            if(dis[v][k]>dis[u][k]+edge[i][k].w){
                dis[v][k]=dis[u][k]+edge[i][k].w;//考虑横向/纵向线路更新
                Q.push(state(v,dis[v][k],k));
                //这里一定要判断是否符合松弛的条件 花费更小,否则会wa
                if(dis[v][k^1]>dis[v][k]+1){//考虑相反线路k异或1更新,在原先横向/纵向线路到达该点要再+1
                    dis[v][k^1]=dis[v][k]+1;
                    Q.push(state(v,dis[v][k^1],k^1));
                }
            }
        }
    }
    return -1;
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m+2;i++){
        scanf("%d%d",&pos[i].x,&pos[i].y);
        pos[i].id=i;
    }
    sort(pos+1,pos+1+m+2,cmpx);
    for(int i=1;i<m+2;i++){
        if(pos[i].x == pos[i+1].x){
            addEdge(pos[i].id,pos[i+1].id,(pos[i+1].y-pos[i].y)*2,0);
            addEdge(pos[i+1].id,pos[i].id,(pos[i+1].y-pos[i].y)*2,0);
        }
    }
    sort(pos+1,pos+1+m+2,cmpy);
    for(int i=1;i<m+2;i++){
        if(pos[i].y == pos[i+1].y){
            addEdge(pos[i].id,pos[i+1].id,(pos[i+1].x-pos[i].x)*2,1);
            addEdge(pos[i+1].id,pos[i].id,(pos[i+1].x-pos[i].x)*2,1);
        }
    }
    printf("%d",Dijkstra(m+1));
    return 0;
}
*/

