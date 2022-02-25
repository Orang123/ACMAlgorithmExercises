#include<cstdio>
#include<queue>
#include<cmath>
#include<algorithm>
#include<cstring>
#define N 110
#define M 11000
#define eps 1e-9
#define INF 1e18
using namespace std;
//ac 873ms EK算法 最小概率费用流 log2以2为底做法
/*
题意:图上有n个点,每个点上有a个人,b个面包,面包不够吃得去其他地方,
存在m条有向路径,每条路都有一个人数上限.路径之间铺了电线,每当有人
通过时都会有pi的概率碰到它,但是第一个通过的人一定不会碰到,求所有人
都获取到食物而碰到电线的最小概率。
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5988
思路:费用流,但是费用流是加法,最小概率显然要用乘法原理,可以取其对数
log2(ab)=log2(a)+log2(b),对每个点多出的人和源点建边,每个点多出的失物和
汇点建边,容量为多出数量,费用为0,其余电线建2条边,一条容量为1,费用为0,一条
容量cf-1,费用为pi.
*/
int n,m,cnt,head[N],st,ed,incf[N],pre[N],vis[N];
double dis[N];
struct Edge{
    int to,next,cf;
    double w;
}edge[M<<1];

void addEdge(int from,int to,int cf,double w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    for(int i=st;i<=ed;i++)
        dis[i]=i==s?0:INF;
    incf[s]=0x3f3f3f3f;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w+eps){
                pre[v]=i;
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

double mcmf(){
    double sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed]*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int T,s,b,u,v,cf;
    double w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&s,&b);
            s-=b;
            if(s>0)
                addEdge(st,i,s,0);
            if(s<0)
                addEdge(i,ed,-s,0);
        }
        while(m--){
            scanf("%d%d%d%lf",&u,&v,&cf,&w);
            if(cf>0)//第一个人不会碰到电线
                addEdge(u,v,1,0);
            if(cf-1>0)//剩下的人会碰到
                addEdge(u,v,cf-1,-log2(1-w));
        }
        printf("%.2f\n",1-pow(2,-mcmf()));
    }
    return 0;
}

/*
//ac 858ms EK算法 最小概率费用流 log以10为底做法
#include<cstdio>
#include<queue>
#include<cmath>
#include<algorithm>
#include<cstring>
#define N 110
#define M 11000
#define eps 1e-9
#define INF 1e18
using namespace std;
int n,m,cnt,head[N],st,ed,incf[N],pre[N],vis[N];
double dis[N];
struct Edge{
    int to,next,cf;
    double w;
}edge[M<<1];

void addEdge(int from,int to,int cf,double w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    for(int i=st;i<=ed;i++)
        dis[i]=i==s?0:INF;
    incf[s]=0x3f3f3f3f;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w+eps){
                pre[v]=i;
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

double mcmf(){
    double sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed]*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int T,s,b,u,v,cf;
    double w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&s,&b);
            s-=b;
            if(s>0)
                addEdge(st,i,s,0);
            if(s<0)
                addEdge(i,ed,-s,0);
        }
        while(m--){
            scanf("%d%d%d%lf",&u,&v,&cf,&w);
            if(cf>0)
                addEdge(u,v,1,0);
            if(cf-1>0)
                addEdge(u,v,cf-1,-log(1-w));
        }
        printf("%.2f\n",1-exp(-mcmf()));
    }
    return 0;
}
*/
