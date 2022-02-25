#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 100100
#define M 200100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
//ac 876ms 开O2 tarjan求解pbc构造圆方树+树形dp求解所有路径点权和
/*
题意:n个点m条边无向图,问有多少对三元组(s,c,f)(s,c,f互不相同)
使得存在一条简单路径从s出发,经过c到达f.
链接:https://www.luogu.com.cn/problem/P4630
思路:关于pbc(点双)有这样2条性质:
1.pbc中任意两点(s,f)之间的路径必然有一条简单路径会经过该pbc中另外一点c.
2.由1可推出对于圆方树上任意两圆点s,f之间的路径上不同的中间的点个数等于
s到f经过的pbc中所有点的并集的大小,即s到f经过的pbc中任意一点都可作为s和f路径上的中间点.
这个首先pbc保证了pbc内任意两点之间的连通性,而s到f路径上途经的pbc,那么pbc
中任意一点都可作为中间点连接.
这2条性质的证明可以参考博客:https://www.cnblogs.com/PinkRabbit/p/10446473.html

那么现在给圆方树附上点权,方点的点权为对应pbc中点的个数,圆点的点权为-1.
这样会发现圆方树上任意两圆点之间路径的总数为路径上点权和,这里需要注意
对于圆-方-圆这样实际只有2个圆点的路径,其权值累加和刚好是0,这里之所以将
圆点点权设置为-1,是因为圆方树上点的连接情况一定是圆-方-圆-方-圆这样连接,
又因为同一点可以同时贡献给多个pbc,那么路径上2个相隔的方点对中间圆点的个数
会重复累加一次,而树上任一路劲上中间点的度都是2,意味着计算时只可能同时为
两个相邻方点贡献,只有将圆点点权设置为-1,才能抵消掉重复贡献的个数,而对于
s到f路径上两端点的圆点,实际并不是因为重复贡献而设置-1,是因为计算路径个数
时,是按照两端点固定下来,通过计算中间圆点的个数来计算路径个数的,所以两端点
s、f并不贡献其次数,所以点权设置为-1刚好将相邻方点的多余的点权减掉.
这里再进一步思考,实际我们需要计算的就是圆方树中路径圆点个数大于2的所有不同路径
的点权和(圆点+方点),那么实际可以单步考虑每个点(圆点+方点)贡献给了多少条端点为2圆点的路径,
也就是实际该点的点权贡献了多少次,这可以通过树形dp来求解.还有一道统计边权对所有路径贡献次数
的树形dp的题目HDU 5723 Abandoned country.

总的来说就是通过固定s,f两端点后将求解实际能选取的中间点c的个数转化成求解s-f路径点权和问题.
*/
int n,m,head[N],cnt;
int dfn[N],low[N],clock,num,pbc_cnt;//pbc_cnt代表
//siz[u]记录的是圆方树中u节点子树包括u圆点的个数,只有圆点是实际存在的点.
//val记录圆方树中每个点的点权 圆点为-1,方点为对应pbc中点个数,方点的度就是对应pbc中点的个数
ll ans,val[N<<1],siz[N<<1];
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
                    //siz也可以用方点作为u点外节点的父亲计算其个数,退出do-while后u再作为方点的父亲
                    tmp=s.top();
                    s.pop();
                    val[pbc_cnt]++;
                    G[pbc_cnt].push_back(tmp);//构造圆方树
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                val[pbc_cnt]+=2;//val初始值为-1 所以加u后还得再加1
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

//O(V+E)=O(2n+2n-1)~=O(n)
void dfs(int u,int fa){
    siz[u]=u<=n?1:0;//只记录圆点个数,只有圆点是实际存在的点,否则会重复计算贡献的路径个数
    for(int v : G[u]){
        if(v == fa) continue;
        dfs(v,u);
        /*
        之前统计的u中子树圆点与当前v子树中圆点分别作为(s,f)路径两端点s、f,
        乘法原理 乘积代表能构成的所有不同路径的个数,也就是val[u]应该贡献给计算出路径的总次数.
        如果当u为圆点时,v必然是方点,而方点不会是叶子节点,所以siz[v]必然>=1,这样结果圆-方-圆也是有意义的.
        乘2是因为,s与f可以颠倒也就是(s,c,f)(f,c,s),每条路径都有2种表达形式.
        这也是和计算边权对两边点构成路径贡献次数不同的地方.
        */
        ans+=2*val[u]*siz[u]*siz[v];
        siz[u]+=siz[v];//先乘法原理计算再累加siz
    }
    //对于圆方树祖父节点中的圆点还能与u中子树中的圆点构成新的(s,f)路径
    //祖父节点中圆点的个数为num-siz[u],num为当前连通块中的实际节点数也就是当前圆方树中圆点总个数.
    ans+=2*val[u]*siz[u]*(num-siz[u]);
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;
    memset(head,-1,sizeof(head));
    memset(val,-1,sizeof(val));//初始化圆方树点权为-1
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
    for(int i=1;i<=n;i++){//原图可能不连通,所有圆方树可能构成森林
        if(!dfn[i]){
            num=0;
            tarjan(i,-1);
            dfs(i,-1);
        }
    }
    printf("%lld",ans);
    return 0;
}
