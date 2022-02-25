#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1010
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:n个点,m条单向边,求从s到t的最短路数目和
比最短路长度多1的次短路数目之和,如果次短路长度不满足
比最短路多1,就输出最短路数目.
链接:http://poj.org/problem?id=3463
思路:最短路计数+次短路,不同的是对于次短路的更新,
有可能来源于最短路也有可能来源于次短路,因此在入队时
需要设置一个最短路和次短路的标志,这样在更新次短路个数时,
就知道继承原先最短路个数还是次短路个数.
*/
//dis[v][0]代表到达v点最短路长度 num[v][0]代表到达v点最短路个数
//dis[v][1]代表到达v点次短路长度 num[v][1]代表到达v点次短路个数
//vis[v][0]代表到达v点最短路是否已计算
//vis[v][1]代表到达v点次短路是否已计算

int n,m,cnt,st,ed,head[N],vis[N][2],dis[N][2],num[N][2];

struct state{
    int v,dis,flag;//flag标记是最短路还是次短路
    state(int dis=0,int v=0,int flag=0):dis(dis),v(v),flag(flag){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(num,0,sizeof(num));
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s][0]=0;
    num[s][0]=1;//次短路个数不用初始化,刚开始次短路个数一定是由较长的最短路更新的
}

int Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(0,s,0));
    int u,v,flag;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,flag=tmp.flag;
        Q.pop();
        if(u == ed && flag) break;
        if(vis[u][flag]) continue;//如果到达u点的flag路计算过,当前的就不是最优的,不必计算
        vis[u][flag]=1;//到达v点最/次短路已被计算 做上标记
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //更新最短路
            if(dis[v][0]>tmp.dis+edge[i].w){
                //若原先最短路已被更新,则将之前的最短路变为新的次短路,这里是为了避免次短路无意义的入队
                if(dis[v][0]!=INF){
                    dis[v][1]=dis[v][0];
                    num[v][1]=num[v][0];
                    Q.push(state(dis[v][1],v,1));
                }
                dis[v][0]=tmp.dis+edge[i].w;
                num[v][0]=num[u][0];
                Q.push(state(dis[v][0],v,0));
            }
            else if(dis[v][0]==tmp.dis+edge[i].w)
                num[v][0]+=num[u][0];//累加最短路个数
            else if(dis[v][1]>tmp.dis+edge[i].w){//更新次短路 tmp.dis+edge[i].w有可能是最短路也有可能次短路
                dis[v][1]=tmp.dis+edge[i].w;
                num[v][1]=num[u][flag];//次短路个数更新由具体之前入队设置的标志决定,0是最短路,1是次短路
                Q.push(state(dis[v][1],v,1));
            }
            else if(dis[v][1]==tmp.dis+edge[i].w)
                num[v][1]+=num[u][flag];//累加次短路个数 有可能最短路也有可能次短路 由flag决定
        }
    }
    if(dis[ed][0]+1 == dis[ed][1])
        return num[ed][0]+num[ed][1];
    else
        return num[ed][0];
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);//根据图示可知是单向边
        }
        scanf("%d%d",&st,&ed);
        printf("%d\n",Dijkstra(st));
    }
    return 0;
}
