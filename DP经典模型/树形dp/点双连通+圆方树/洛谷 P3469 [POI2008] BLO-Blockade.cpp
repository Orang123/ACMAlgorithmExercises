#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
//ac 284ms tarjan求解pbc构造圆方树求解
/*
题意:给定一张无向图,求每个点被删除之后有多少个有序点对
(x,y)(x!=y,1<=x,y<=n)不连通.
链接:https://www.luogu.com.cn/problem/P3469
思路:如果删除的点u不是割点,则只有删除的u和其余点不连通.
如果删除的点u是割点,则除了该点和其余所有点不连通外,删除割点u
所分离出的各个子连通分支中的点对也是不连通的.
圆方树中删除某个圆点后其本身所在祖父节点的分支是显而易见的,
每个子树分支都会作为一个连通子集被分割.
可以tarjan求解pbc构造圆方树,这样应用树形dp统计每个节点u的子树
中圆点的个数siz[u].若删除叶子节点u(不是割点)则只计算u点和其余点
构成的点对2*(n-1),若删除度大于1的圆点u(割点),除了计算u点和其余点
构成的不连通点对外,以这个点为根的各个分支之间都会产生不连通的点对,
ans+=2*siz[u]*siz[v]+(num-siz[u]-1)*siz[u].
因为点对起点终点可以颠倒各算1次,所以要乘2.
*/

int n,m,head[N],cnt;
int dfn[N],low[N],clock,num,pbc_cnt,vis[N<<1];

ll son[N<<1],ans[N];
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}


void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    num++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            s.push(v);
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                int tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    G[pbc_cnt].push_back(tmp);//构造圆方树
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                vis[pbc_cnt]=1;//标记方点
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void dfs(int u,int fa){
    for(int v : G[u]){
        if(v == fa) continue;
        dfs(v,u);
        if(!vis[u])//删除的点只能是实际存在的圆点 这里不考虑u点
            ans[u]+=2*son[u]*son[v];
        son[u]+=son[v];
    }
    if(!vis[u]){
        ans[u]+=2*son[u]*(num-son[u]-1);//祖父节点中的圆点和u子树中的圆点会构成不连通的点对(不考虑u点)
        ans[u]+=2*(num-1);//u点和剩余所有圆点构成的不连通点对
    }
    son[u]+=u<=n?1:0;//只记录圆方树中的圆点,这里在dfs回溯算时先不考虑u点
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    int n2=n<<1;
    for(int i=1;i<n2;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            num=0;//记录将要构造的圆方树中圆点的个数.
            tarjan(i,-1);
            dfs(i,-1);
        }
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}

/*
//ac 201ms 类似圆方树那种计算点对的方式,只不过现在是用tarjan求解割点时计算
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,head[N],cnt;
int dfn[N],low[N],clock;

ll son[N],ans[N];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}


void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    son[u]=1;
    ll sum=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            tarjan(v,u);
            son[u]+=son[v];//son[u]代表u所连接的tarjan还没访问的点的个数,也就是所有树边所连接的点的个数
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                ans[u]+=2*sum*son[v];//当前合并的不连通u分支(不包括u点)与当前不连通v子分支构成的不连通点对
                //注意这里sum只计算 u作为割点分量的不连通v分支的点个数,u作为割点并不是所有v分支都要作为子不连通分支,
                //有可能v分支和u是属于同一个pbc的,这时v分支是和祖父节点作为祖父不连通分支去计算的
                sum+=son[v];//son[v]分支计算过后,还要和后面的v分支计算不连通点对,所以累加到sum里
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    ans[u]+=2*(n-1);//u点和剩余点所构成的不连通点对
    ans[u]+=2*sum*(n-sum-1);//u作为割点分割的祖父不连通分支(不包括u点)与所有分割出的v子不连通分支构成的不连通点对
}

void init(){
    clock=cnt=0;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,-1);
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
*/

/*
//ac 202ms tarjan求解割点 子不连通块与其余所有不连通块构成的不连通点对
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,head[N],cnt;
int dfn[N],low[N],clock;

ll son[N],ans[N];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}


void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    son[u]=1;
    ll sum=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            tarjan(v,u);
            son[u]+=son[v];
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                //当前这个分支和其余分支以及祖父分支(不包括u点)构成的不连通点对
                //这里无需乘2,在这个过程每个son[v]分支除了计算自己外,还会把别的分支再计算端点颠倒的一次
                //所有分支都计算完后,除过祖父分支只计算了一次外,其余被分割连通块都计算了2次.
                ans[u]+=son[v]*(n-son[v]-1);
                sum+=son[v];
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    ans[u]+=2*(n-1);//u点分割后与剩余点所构成的不连通点对
    ans[u]+=sum*(n-sum-1);//删除u点后,祖父分支与其余连通块所构成端点颠倒的连通对
}

void init(){
    clock=cnt=0;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,-1);
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
*/
