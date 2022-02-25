#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 550
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;
//分层图最短路 思维建边做法
/*
题意:机场有N个车站,分两种线路,经济线和商业线,商业线较快,
但只能乘坐一站,现在问要从s站到达e站,找到一条最短的路线.
链接:https://www.luogu.com.cn/problem/UVA11374
思路:分层图最短路,k恒为1的特殊情形,可以将商业线看成0层与1层连接线路,有权.
*/

int n,m,k,s,e,y,cnt,head[N<<1],dis[N<<1],vis[N<<1],pre[N<<1];
struct Node{
    int to,next,w;
}edge[(M*2*2)<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> > Q;
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
                pre[v]=u;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

void print(int x){
    //第一个小于n编号的点即0层图和1层图连接的边处于0层图点就是商业线转折点
    if(x<n && !y) y=x;
    if(x == s){
        printf("%d",s);
        return;
    }
    print(pre[x]);
    printf(" %d",(x-1)%n+1);//输出时要取模避免输出大于n的1层图中的编号
}

int main(){
    int u,v,w,cas=0;
    while(scanf("%d%d%d",&n,&s,&e)!=EOF){
        if(cas++) printf("\n");//两个样例之间有换行,但题目没说,不懂
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);//o层图
            addEdge(v,u,w);
            addEdge(u+n,v+n,w);//1层图
            addEdge(v+n,u+n,w);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v+n,w);//连接0层与1层的有向边作为商业线
            addEdge(v,u+n,w);
        }
        Dijkstra(s);
        int flag=0;
        y=0;
        if(dis[e+n]<dis[e])
            flag=1;
        print(e+flag*n);
        if(flag) printf("\n%d\n",y);
        else printf("\nTicket Not Used\n");
        printf("%d\n",dis[e+n*flag]);
    }
    return 0;
}


/*
//分层图最短路 dp做法
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 550
#define M 2100
#define INF 0x3f3f3f3f
using namespace std;
//dis[v][0]代表到达v点没有乘坐商业线
//dis[v][1]代表到达v点已经乘坐了商业线
int n,m,k,s,e,z,cnt,head[N],dis[N][2],vis[N][2],preu[N][2],precnt[N][2];

struct state{
    int v,dis,cnt;
    state(){}
    state(int v,int dis,int cnt):v(v),dis(dis),cnt(cnt){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next,w,sign;
}edge[M<<1];

void addEdge(int from,int to,int w,int sign){
    edge[cnt]=(Node){to,head[from],w,sign};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s][0]=dis[s][1]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(s,0,0));
    state tmp;
    int u,v,nowCnt;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,nowCnt=tmp.cnt;
        Q.pop();
        if(u == e) return;
        if(vis[u][nowCnt]) continue;
        vis[u][nowCnt]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!edge[i].sign){//若该边是经济线 判断是否权值和更小
                if(dis[v][nowCnt]>dis[u][nowCnt]+edge[i].w){
                    dis[v][nowCnt]=dis[u][nowCnt]+edge[i].w;
                    preu[v][nowCnt]=u;//记录到达v使用商业线nowCnt次的前驱节点u
                    precnt[v][nowCnt]=nowCnt;//记录到达v使用商业线nowCnt次的前驱节点u使用商业线次数nowCnt
                    Q.push(state(v,dis[v][nowCnt],nowCnt));
                }
            }
            else{
                if(!nowCnt){//若该边是商业线线 首先判断之前有没有走过商业线 再判断是否权值和更小
                    if(dis[v][nowCnt^1]>dis[u][nowCnt]+edge[i].w){
                        dis[v][nowCnt^1]=dis[u][nowCnt]+edge[i].w;
                        preu[v][nowCnt^1]=u;//记录到达v使用商业线1次的前驱节点u
                        precnt[v][nowCnt^1]=nowCnt;//记录到达v使用商业线1次的前驱节点u没有使用商业线
                        Q.push(state(v,dis[v][nowCnt^1],nowCnt^1));
                    }
                }
            }
        }
    }
}

void print(int x,int y){
    if(!y&&!z) z=x;//第一个没有商业线的前驱即是使用商业线的转折点,z只记录一次
    if(x == s){
        printf("%d",x);
        return;
    }
    print(preu[x][y],precnt[x][y]);
    printf(" %d",x);
}

int main(){
    int u,v,w,cas=0;
    while(scanf("%d%d%d",&n,&s,&e)!=EOF){
        if(cas++) printf("\n");//两个样例之间有换行,但题目没说,不懂
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w,0);//0代表经济线
            addEdge(v,u,w,0);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w,1);//1代表商业线
            addEdge(v,u,w,1);
        }
        Dijkstra(s);
        int flag=0;
        z=0;
        if(dis[e][0]>dis[e][1])
            flag=1;//代表使用商业线最快
        print(e,flag);
        if(flag) printf("\n%d\n",z);
        else printf("\nTicket Not Used\n");
        printf("%d\n",dis[e][flag]);
    }
    return 0;
}
*/

/*
枚举拆分最短路做法 ac
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 550
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;
//此题spfa Dijkstra都能过 并不卡spfa,V、E其实都很小.

//思路:因为商业线只能乘坐一站,对于经济线可以分别从s,e开始跑两遍
//最短路,枚举每一条商业线u->v 构造dis1[u]+w+dis2[v] 是否比dis1[e]更
//优.


int n,m,k,s,e,cnt,head[N],dis1[N],dis2[N],vis[N],pre1[N],pre2[N];
struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s,int *dis){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
}

void Dijkstra(int s,int *dis,int *pre){
    init(s,dis);
    priority_queue<pair<int,int> > Q;
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
                pre[v]=u;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

void print1(int v){
    if(v == s){
        printf("%d",v);
        return;
    }
    print1(pre1[v]);
    printf(" %d",v);
}

void print2(int v){
    if(v == e){
        printf(" %d",v);
        return;
    }
    printf(" %d",v);
    print2(pre2[v]);
}

int main(){
    int u,v,w,ans,st,ed,cas=0;
    while(scanf("%d%d%d",&n,&s,&e)!=EOF){
        if(cas++) printf("\n");//两个样例之间有换行,但题目没说,不懂
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(s,dis1,pre1);
        Dijkstra(e,dis2,pre2);
        ans=dis1[e];
        scanf("%d",&k);
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            //枚举每一条商业线 分正反 u->v v->u两个方向
            if(dis1[u]+w+dis2[v]<ans){
                st=u;
                ed=v;
                ans=dis1[u]+w+dis2[v];
            }
            if(dis1[v]+w+dis2[u]<ans){
                st=v;
                ed=u;
                ans=dis1[v]+w+dis2[u];
            }
        }
        if(ans!=dis1[e]){
            print1(st);
            print2(ed);
            printf("\n%d\n",st);//这个地方的\n必须放在st前面 不能放在print里 否则会wa,不懂
        }
        else{
            print1(e);
            printf("\nTicket Not Used\n");//\n 同上
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
