#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 100100
using namespace std;
typedef long long ll;
//ac 78ms
/*
题意:求最多添加多少边能使得原图仍旧不是强连通图,
非强连通图所能添加最多边数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4635
思路:https://blog.csdn.net/qq_34374664/article/details/78055357 参考博客
正面不好考虑,可以从反面考虑,先将原图tarjan求出SCC,
记录各个SCC中点的个数再缩点,求出各个点的出度入度,
考虑一个出度为0或入度为0的SCC 点个数x,将其余缩点(SCC)看成一个整体(点个数y),
将整个图分为2部分,现在将这两部分都当做完全图,则边数分别为x*(x-1),
y*(y-1),这样这2部分之间还没有连边,实际他们最多能连的边数是一个集合中的
每一个点都和另一个集合中所有点所连成的单向边,这样就能保证2部分不会构成一个
SCC,那么最大 连边根据乘法原理为x*y,所以最多边数的非强连通图总边数为
x*(x-1)+y*(y-1)+x*y再去除本身就有的边数m,则最多能加的边数为x*(x-1)+y*(y-1)+x*y-m
当然这里需要计算每个出度入度为0的SCC分为两部分最多能加的边数,乘法原理的最大值因为两
乘法因子的大小不定,只要记录最大值即可.

当然可以从反面考虑,直接将整张图看做完全图,那么只要将其分成2部分,
去除2部分间的最大单向连边数和本身存在的边数m,也是最大能添加的边数即:n*(n-1)-x*y-m
可以想象非强连通图的SCC的个数越少所能添加的边数越多,而非强连通图SCC个数至少为2,
也就是为2个SCC的时候,所能添加的边数是最多的.

为什么考虑出度入度为0的点SCC,感觉如果选择的是比的出入度不为0的SCC,结果只会偏小,不会偏大啊,
有点疑惑.
*/

int n,m,dfn[N],low[N],in[N],num,cnt,head[N],id,block[N],inde[N],outde[N],amout[N];
stack<int> s;
struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            amout[id]++;
            block[v]=id;
        }while(v!=u);
    }
}

int main(){
    int T,u,v,cas=0;
    ll ans;
    scanf("%d",&T);
    while(T--){
        cas++;
        ans=cnt=num=id=0;
        memset(dfn,0,sizeof dfn);
        memset(head,-1,sizeof head);
        memset(amout,0,sizeof amout);
        memset(inde,0,sizeof inde);
        memset(outde,0,sizeof outde);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        if(id == 1){//只有一个SCC,本身就是SCG(强连通图)
            printf("Case %d: -1\n",cas);
            continue;
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u] != block[v]){
                inde[block[v]]++;
                outde[block[u]]++;
            }
        }
        ll x,y;
        for(int i=1;i<=id;i++){
            if(!inde[i] || !outde[i]){
                x=amout[i],y=n-x;
                ans=max(ans,x*(x-1)+y*(y-1)+x*y-m);
                //当x*y最小的时候值最大,而x和y差距最大的时候才是乘积最小的,
                //所以也可以直接找SCC中点数最小的,只计算一次就可打的最大添加边数
                //ans=max(ans,n*(n-1)-x*y-m);
            }
        }
        printf("Case %d: %lld\n",cas,ans);
    }
    return 0;
}
