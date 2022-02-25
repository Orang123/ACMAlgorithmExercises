#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 210
#define M 40100
#define INF 0x3f3f3f3f
using namespace std;
//ac 218ms Ek算法 有向环覆盖 拆点
//还可通过KM算法,边权取反求最小权匹配
/*
摘自网上
题意:给你一个N个点M条边的带权有向图,现在要你求这样一个值:
该有向图中的所有顶点正好被1个或多个不相交的有向环覆盖.
这个值就是所有这些有向环的权值和.要求该值越小越好.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1853
思路:有向环的最小覆盖问题,首先考虑该图中所有顶点正好被1个
或多个不相交的环覆盖的话,就意味着图中的每个顶点出度和入度均为1,
那么对于每个顶点就可以把它拆成两个点,来模拟出度和入度,源点就相当
于总出度,汇点就相当于总入度,那么如果最大流等于顶点数目,那么就可
以说明刚好被1个或多个不相交环覆盖,那么最小费用就是答案了.
i表示点i的出度,i+n表示点i的入度,源点0,汇点2*n+1,源点向每个出度点连
容量为1,费用为0的边,每个点的出度i+n向汇点连容量为1,费用为0的边.
每条有向边u->v,连u到v+n,容量为1,费用为w的边.
*/
int n,m,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
struct Edge{
    int to,next,cf,w;
}edge[M];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
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
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
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

int mcmf(){
    int sum=0,cost=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
    return sum == n?cost:-1;
}

void init(){
    cnt=0;
    st=0,ed=n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            addEdge(st,i,1,0);
            addEdge(i+n,ed,1,0);
        }
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v+n,1,w);
        }
        printf("%d\n",mcmf());
    }
    return 0;
}

/*
摘自博客:https://blog.csdn.net/qq_21057881/article/details/50677187
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 1e9
using namespace std;
const int maxn=100+10;

struct Max_Match
{
    int n,W[maxn][maxn];
    int Lx[maxn],Ly[maxn];
    bool S[maxn],T[maxn];
    int left[maxn];

    bool match(int i)
    {
        S[i]=true;
        for(int j=1;j<=n;j++)if(Lx[i]+Ly[j]==W[i][j] && !T[j])
        {
            T[j]=true;
            if(left[j]==-1 || match(left[j]))
            {
                left[j]=i;
                return true;
            }
        }
        return false;
    }

    void update()
    {
        int a=1<<30;
        for(int i=1;i<=n;i++)if(S[i])
        for(int j=1;j<=n;j++)if(!T[j])
            a=min(a, Lx[i]+Ly[j]-W[i][j]);
        for(int i=1;i<=n;i++)
        {
            if(S[i]) Lx[i] -=a;
            if(T[i]) Ly[i] +=a;
        }
    }

    int solve(int n)
    {
        this->n=n;
        memset(left,-1,sizeof(left));
        for(int i=1;i<=n;i++)
        {
            Lx[i]=Ly[i]=0;
            for(int j=1;j<=n;j++) Lx[i]=max(Lx[i], W[i][j]);
        }
        for(int i=1;i<=n;i++)
        {
            while(true)
            {
                for(int j=1;j<=n;j++) S[j]=T[j]=false;
                if(match(i)) break;
                else update();
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            if(W[left[i]][i]==-INF) return -1; //找不到
            ans += W[left[i]][i];
        }
        return -ans;//注意这里返回的是负值
    }
}KM;

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            KM.W[i][j]=-INF;
        while(m--)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            KM.W[u][v]=max(KM.W[u][v],-w);//可能存在重边
        }
        printf("%d\n",KM.solve(n));
    }
    return 0;
}
*/
