#include<cstdio>
#include<algorithm>
#define N 120
#define M 1100
#define Mod 31011
using namespace std;
//dfs搜索+并查集 ac 29ms
/*
题意:n个点,m条边的无向图,求解最小生成树的个数.
如果两颗最小生成树中至少有一条边不同,则这两个最小生成树就是不同的.
链接:https://www.luogu.com.cn/problem/P4208
定理:"一张图的所有最小生成树中权值相等的边的个数一定相同".
证明:3+7=4+6=10不可能有3、7和4、6这两种边组合方案,在生成mst时,会贪心选3+4=7,不会选较大的边权3+7或4+6这样.
思路:对于未加入mst的边u-v,将其加入后,判断树上u-v这段路径中有多少条边和未加入
的边权值相等,那么对于这mst这一段可能的形状就有多少种.最后用乘法原理累乘出所有段
的答案即可.这里的做法具体是先把相同边权放置在一个区间数组里,然后计算mst在这个相同
边权的区间内要加多少边,之后我们dfs爆搜对每一个相等边权的数组,搜索选择本身mst加入这个
数组相等边权的数目cnt,这里枚举出可能的cnt条相等边权,sum计数,之后乘法原理再和ans累乘,
接着统计下一个相等边权的区间.
洛谷网友fighter:
为什么不能对dfs中使用的并查集进行路径压缩？我认为是因为在dfs过程中搜索完后需要还原，
以保证搜索的正确性，而这种还原要保证并查集的结构完整地被还原，如果进行路径压缩，
那么当前的根节点，在dfs后可能已经不是根节点，原先他的子节点经过路径压缩后，
都指向了当前“级别”更高的根节点，这时候如果要还原并查集的结构就会十分困难。
因为你只能暂时将"级别"更高的根节点还原,而之前的子节点因为路径压缩,它仍旧指向了已经被
还原的的"级别"更高的根节点,而后面若还有边是子节点和"级别"更高的根节点在子节点还没回溯
还原之前有连边,则会因为祖先节点一样,而无法连边,这就影响会加边的结果,导致计算错误.

*/

int fa[N],sum;

struct Node{
    int u,v,w;
    bool operator < (const Node &x)const{
        return w<x.w;
    }
}edge[M];

struct section{
    int l,r,num;//l表示 权值相等的边的下标的左端点,r表示右端点,num表示在mst中这样权值相等的边的数量
}sec[M];

void init(int n){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:find(fa[x]);
}

/*
dfs求解的本质思想:其实就是考虑原先 mst里 某段路径 未加入的边 是否有和当前路径中的边权相同,
加入后 构成了环，然后顺次删掉原先那条边。这样就是一个新的mst.
*/
//本dfs应用的性质L在无向连通图中 所有的最小生成树中权值相等的边数量是相同的

void dfs(int x,int now,int cnt){
    int a,b;
    if(now == sec[x].r+1){//若权值相等的边 枚举到了 右端点即 结束
        if(cnt == sec[x].num)//判断权值相等的边是否和初始化时的mst相同,若相同则此时选择的权值相同的边就构成了 新的mst
            sum++;
        return;
    }
    a=find(edge[now].u);
    b=find(edge[now].v);
    if(a!=b){//若当前边 能加入mst
        fa[a]=b;
        dfs(x,now+1,cnt+1);//下一条边的下标now+1,构成的相同权值的边数目cnt+1
        /*
        回溯时,考虑不加入这条边,尝试加入其它权值相等的边 ,最终的数目是否能达到初始时的mst权值相等的边的数目
        同时要将之前连通起来的2个集合分开恢复到未加入这条边时的图的结构.
        注意find函数里绝对不能有路径压缩,若有路径压缩会导致,
        因为在 后续find 再加边时,这个a的儿子 它可能会成为新的b的儿子
        此时就算fa[a]=a,fa[b]=b也只是能 改变当初根节点的 指向,儿子结点指向 会因为后续加入的新b结点路径压缩而指向b,
        这会影响后面加边时连通关系的判定,导致没有完全恢复到之前的连通状态.
        eg:考虑边集1-2,1-3,1-4,1-5,1-6,3-5所构造的并查集若不压缩则是fa[1]=2,fa[2]=3,fa[3]=4,fa[4]=5,fa[5]=6,3-5的边因为构成回路不能加进来,
        但是如果路径压缩后并查集的构造fa[1]=fa[2]=fa[3]==fa[4]=5,fa[5]=6,如果此时回溯不选择1-5,1-6这条边连接,那么并查集还原只能
        还原fa[4]=4,fa[5]=5,fa[6]=6,但是fa[1]=fa[2]=fa[3]=5,仍然都指向5,对于3-5这条边,因为fa[3]=fa[5]=5,导致不能加入3-5这条边,
        但这条边并没有构成环,只是因为路径压缩,导致子节点指向更高级别的父节点,导致还原时,在没有回溯到子节点时,其fa的指向并没有
        还原,如果有子节点和之前断开的级别高的父节点有连边则会无法连接.
        1->2->3路径压缩完就变成1->3、2->3,本来1是2的儿子，现在1变成3的儿子了,而在恢复时也只能使得fa[2]=2,而fa[1]已经等于3了,
        这样就没有恢复到原先未加入这条边时的连通状态
        */
        fa[a]=a,fa[b]=b;
    }
    dfs(x,now+1,cnt);//考虑不加入这条边,尝试加入其它权值相等的边
}

int main(){
    int n,m,a,b,c,cnt=0,cnt0=0,ans=1;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    sort(edge+1,edge+1+m);
    init(n);
    for(int i=1;i<=m;i++){
        /*这里若判断i 和i+1 边下标从0开始 结果就会wa不知为何*/
        if(edge[i].w!=edge[i-1].w){//如果相邻边 的权值不相等,就说明 此时的i对应的边权是新的较大的边权
            sec[cnt].r=i-1;//记录之前相等边权的右端点的下标
            sec[++cnt].l=i;//记录新的相等边权的左端点为此时的边i下标
        }
        a=find(edge[i].u);
        b=find(edge[i].v);
        if(a!=b){//构造mst不断加边
            fa[a]=b;
            sec[cnt].num++;//在mst中这种边权的个数+1
            cnt0++;
            //if(cnt0 == n-1) break;这里不能提前结束,因为有可能提前退出循环 其余权值相等的边就没有被记录进去
        }
    }
    sec[cnt].r=m;//循环结束时,最后一种边权的右端点为下标m
    if(cnt0 != n-1){//若不存在mst,则输出0
        printf("0\n");
        return 0;
    }
    init(n);
    for(int i=1;i<=cnt;i++){//枚举每一个 权值相等的边
        sum=0;//初始化这个权值相等的边的所能构成mst的不同种类个数
        dfs(i,sec[i].l,0);
        ans=(ans*sum)%Mod;
        for(int j=sec[i].l;j<=sec[i].r;j++){
            a=find(edge[j].u);
            b=find(edge[j].v);
            if(a!=b)
                fa[a]=b;
        }
    }
    printf("%d\n",ans);
    return 0;
}
/*
//基尔霍夫矩阵(矩阵树定理) 高斯消元做法 ac 27ms
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N=101,M=1001,MOD=31011;

//原图，边权离散化并按相等边权存储
struct e
{
    int x,y,v;
} tp[M],mst[M];
vector<e> edge[M];
int cmp(e a,e b)
{
    return a.v<b.v;
}

bool is[M];

//并查集
int bcj[N],bel[N];
void init(int a)
{
	for(int i=1;i<=a;i++) bcj[i]=i;
}
int rt(int a)
{
    if(bcj[a]==a) return a;
    return bcj[a]=rt(bcj[a]);
}
bool uni(int a,int b)
{
    int p=rt(a),q=rt(b);
    if(p==q) return true;
    bcj[p]=q;
    return false;
}

//三个矩阵 度数、邻接、基尔霍夫
int n,deg[N][N],g[N][N],mat[N][N];

int treecnt()//生成树计数，辗转相除高斯消元
{
    int i,j,k,ans=1;
    for(i=1;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            while(mat[j][i])
            {
                int div=mat[i][i]/mat[j][i];
                for(k=i;k<n;k++) mat[i][k]=(mat[i][k]-1ll*mat[j][k]*div%MOD+MOD)%MOD;
                swap(mat[i],mat[j]);
                ans*=-1;
            }
            if(mat[i][i]==0) return 0;
        }
        ans=1ll*ans*mat[i][i]%MOD;
    }
    return (ans+MOD)%MOD;
}

int main()
{
    int a,b,i,j,k,tl=0,tmp=0,cnt=0;
    scanf("%d%d",&a,&b);
    init(a);
    for(i=0;i<b;i++) scanf("%d%d%d",&tp[i].x,&tp[i].y,&tp[i].v);
    sort(tp,tp+b,cmp);

    //kruskal
    for(i=0;i<b;i++)
    {
        if(tp[i].v!=tmp) tl++,tmp=tp[i].v;
        edge[tl].push_back(tp[i]);
        if(uni(tp[i].x,tp[i].y)) continue;
        is[tl]=1,mst[cnt]=tp[i],mst[cnt++].v=tl;
    }
    if(cnt!=a-1)
    {
        printf("0");
        return 0;
    }

    //统计答案
    int ans=1;
    for(i=1;i<=tl;i++)
    {
        //如果最小生成树中没有用到此边权
        if(!is[i]) continue;

		init(a);
        int siz=edge[i].size();
		n=0;

		//将生成树上的边全部连上并缩点
		for(j=0;j<cnt;j++)
		{
			if(mst[j].v==i) continue;
			uni(mst[j].x,mst[j].y);
		}
		for(j=1;j<=a;j++)
		{
			if(bcj[j]==j) bel[j]=++n;
		}
		for(j=1;j<=a;j++) bel[j]=bel[rt(j)];

        //将原图中此边权的边全部连上
        for(j=0;j<siz;j++)
        {
            int bx=bel[edge[i][j].x],by=bel[edge[i][j].y];
            deg[bx][bx]++,deg[by][by]++;
            g[bx][by]++,g[by][bx]++;
        }

        for(j=1;j<=n;j++)
            for(k=1;k<=n;k++)
                mat[j][k]=deg[j][k]-g[j][k];
        ans=ans*treecnt()%MOD;

        //删除连上的边
        for(j=0;j<siz;j++)
        {
            int bx=bel[edge[i][j].x],by=bel[edge[i][j].y];
            deg[bx][bx]--,deg[by][by]--;
            g[bx][by]--,g[by][bx]--;
        }
    }
    printf("%d",ans);
    return 0;
}
*/

/*
这里记录相同权值的边区间若判断i 和i+1 边下标从0开始 结果就会wa不知为何
#include<cstdio>
#include<algorithm>
#define N 120
#define M 1100
#define Mod 31011
using namespace std;
int fa[N],sum;

struct Node{
    int u,v,w;
    bool operator < (const Node &x)const{
        return w<x.w;
    }
}edge[M];

struct section{
    int l,r,num;
}sec[M];

void init(int n){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:find(fa[x]);
}

void dfs(int x,int now,int cnt){
    int a,b;
    if(now == sec[x].r+1){
        if(cnt == sec[x].num)
            sum++;
        return;
    }
    a=find(edge[now].u);
    b=find(edge[now].v);
    if(a!=b){
        fa[a]=b;
        dfs(x,now+1,cnt+1);
        fa[a]=a,fa[b]=b;
    }
    dfs(x,now+1,cnt);
}

int main(){
    int n,m,a,b,cnt=0,cnt0=0,ans=1;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    sort(edge,edge+m);
    init(n);
    for(int i=0;i<m-1;i++){
        if(edge[i].w!=edge[i+1].w){
            sec[cnt].r=i;
            sec[++cnt].l=i+1;
        }
        a=find(edge[i].u);
        b=find(edge[i].v);
        if(a!=b){
            fa[a]=b;
            sec[cnt].num++;
            cnt0++;
            //if(cnt0 == n-1) break;
        }
    }
    sec[cnt].r=m-1;
    if(cnt0 != n-1){
        printf("0\n");
        return 0;
    }
    init(n);
    for(int i=0;i<=cnt;i++){
        sum=0;
        dfs(i,sec[i].l,0);
        ans=(ans*sum)%Mod;
        for(int j=sec[i].l;j<=sec[i].r;j++){
            a=find(edge[j].u);
            b=find(edge[j].v);
            if(a!=b)
                fa[a]=b;
        }
    }
    printf("%d\n",ans);
    return 0;
}

*/
