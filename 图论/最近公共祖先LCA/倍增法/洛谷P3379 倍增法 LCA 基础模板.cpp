#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 500100

/*
这里的倍增实际就是对深度进行倍增,不用让结点一步一步向上跳,而是依据2的倍率 从大往小跳,
缩短了向上跳的总次数,来优化时间，这里是构造了fa[i][k]这种i结点向上第2^k个祖先的数据结构来实现倍增的跳跃
*/
/*
fa[i][k]表示结点i的上面第2^k次方的祖先是哪个结点
dep[i]表示结点i的深度
*/
int head[N],fa[N][21],dep[N],n,m,s,cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

//O(log(dep[u1])+log(dep[u2])+...+log(dep[un]))=O(log(dep[u1]*dep[u2]*...*dep[un])) 预处理时间复杂度好像化简为O(NlogN)
void dfs(int u,int fath){
    fa[u][0]=fath;//u的第2^0次方的祖先结点,即其父亲结点为fath
    dep[u]=dep[fath]+1;//结点深度+1
    for(int i=1;(1<<i)<=dep[u];i++)//根据当前所处的深度构造其第2^log2(dep[u])个祖先 O(log(N))
        /*
        u结点的第2^i次方的祖先结点可以理解为 先从u结点走到其第2^(i-1)次方的祖先结点,
        再从这个祖先结点往上走2^(i-1)次方个祖先结点就是fa[u][i],就相等于2^i=2^(i-1)+2^(i-1)=2*2(i-1)=2^i
        先从计算往上较小的祖先结点,再计算往上较大的祖先节点,依次递推
        */
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)//不能再回到其父节点
            dfs(v,u);
    }
}

//lca(Least Common Ancestors) O(log(dep)) dep为(x、y)中深度最深结点与lca之间深度之差 最坏时间复杂度O(logN)
int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);//永远将x结点作为深度较深的那个结点
    /*
    将x的深度向上跳到和y深度一致,不过是从大往小跳如果大的跳不过去，
    再把它调小。这是因为从小开始跳，可能会出现“悔棋”的现象。
    这里最终x是一定可以跳到和y相同的深度的,因为倍增正是应用了任意一个
    10进制数都可以表示为2进制的方式这个准则，这里x与y的深度之差正是这个
    10进制数，它是可以以2进制的形式表示出来的。列如5(101)=4(100)+1(1) 8(1000)等.
    至于为什么要从大往小跳:
    eg:
    1.乌鸦喝水的过程，就是乌鸦先把体积大的（这里就是i值）放进水杯里，
    再逐渐减小放入物品的体积直到把水杯的水升上来，而不是先填沙子这种小颗粒的东西。
    这就是为什么i值要从大到小。
    2.拿5为例，从小向大跳，5≠1+2+4,所以我们还要回溯一步，然后才能得出5=1+4,而从大向小跳，
    直接可以得出5=4+1。这也可以拿二进制为例,5(101),从高位向低位填很简,如果填了这位之后比原数大了,那我就不填.
    3.若从小开始跳,得从2^0次方开始,但实际x、y距离只差可能是个偶数,这里还用不到1去构造,这样结果就会出错,需要反悔
    */
    /*
    2^20次方是10^6 也就是最大深度10^6而此题最多只有50W个结点深度最深是50W,
    因此枚举的上界2^20次方是够用的(所以fa[N][21]二维要设21下标最大才能取到20)
    这里枚举的步长是以2的倍率依次减半递减的,步长的选择是连续的,
    但是对于一开始x与y深度差为5时,实际选取的步长为2^2、2^0,中间枚举的2^1次方是多余的可能性,
    而lg数组预处理优化解决了这个问题,对于多余的步长可以直接跳过,优化循环的时间复杂度
    */
    for(int i=20;i>=0;i--){//这里步长的选择并不是根据x与y的实时差值去选择的,而是暴力枚举每一种可能性 其实20可以用 log N/log 2来替代 N为点的个数
        //if(dep[x]-(1<<i)>=dep[y])
        /*
        当x向上跳到深度比y仍旧大时,将x跳到当前选定的深度,再继续向上跳 不过向上所跳深度是原先一半越来越小,
        如果x向上跳的深度比y小,则选取更小的步长，将向上跳的步长变为原来一半.实际就是暴力分解这个x与y10进制深度之差,将其以2进制因子的形式组合出来,
        而10进制数是一定可以表示成2进制数的,因此x是一定可以跳跃到与y同深度的
        */
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    }
    if(x == y) return x;//如果之前深度较小的y刚好是x的祖先,那么此时的x结点就为x、y结点的lca
    /*
    将处于同一深度的x、y同时向上跳,也是先向上跳步数较大的祖先,如果不相等,就更新x、y为当前祖先节点,之后步数减小为其一半
    也是从大到小跳,一是这样跳跃最终所跳的总次数会减少,二是不会出错,若从小的2^0次方开始跳可能会出错,因为他们的lca距离他们
    的距离可能是个偶数
    */
    for(int i =20;i>=0;i--){//此处2^20次方同理枚举向上跳深度最大上界
        /*
        eg:1.若最后一次2^0次方父亲结点相等,最终返回fa[x][0]
           2.若2^1次方相等,2^0次方不相等,x、y更新到其父亲结点,但之前的2^1次方相等,所以最终还是返回fa[x][0].
           3.若2^2次方相等,2^1次方不相等,x、y更新到其父亲结点,2^0次方不相等,x、y更新到其父亲结点,但之前的2^2次方相等,所以最终还是返回fa[x][0]
        */
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];//x、y只需再向上跳一步即它们的父亲结点就是x与y的lca
}

int main(){
    int x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        /*
        构造无向树,因为输入的s根节点是任意的,不一定是一开始就入度为0的那个点,有可能是中间某个点,
        但它本身是作为入度被连向的边的端点，因此要构造双向边,才能遍历以这个点为根节点的所有结点.
        */
        addEdge(x,y);
    }
    dfs(s,0);//这里默认根节点的祖先结点是0结点，实际没有意义，只是因为当深度为2时,会计算其上面的第2^1的祖先节点这是会用到0结点
    while(m--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));//计算x、y结点的lca
    }
    return 0;
}
/*
求取lca时 x与y深度之差通过,将10进制转化为二进制 对比每一位哪个是1，从较小的1开始向上跳
注意这里是从小向大跳,所以一定是要验证所跳的这一步,对应的深度转化为二进制以后 是否还有这一位的1,
因为不验证 原先若是个偶数,直接跳1,最终就会出错,最终所枚举出的二进制1是一定不等于这个10进制数的.
#include <bits/stdc++.h>
using namespace std;
#define P pair<int, int>
const int MAXN = 500000 + 5;
int N, M, S;
int head[MAXN], cnt;
vector<P> ask;
int fa[MAXN][20], depth[MAXN];
struct Edge{
	int to, dis, next;
}edge[MAXN << 1];
void add_edge(int u, int v, int dis) {
	edge[++cnt].to = v;
	edge[cnt].dis = 0;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
void init() {
	cnt = 1;
	memset(head, 0, sizeof(head));
	memset(depth, 0 , sizeof(depth));
	memset(fa, 0, sizeof(fa));
	ask.clear();
}
//更新每个节点的深度, 在搜索过程中
void DFS (int now, int pre) {
	depth[now] = depth[pre] + 1;
	fa[now][0] = pre;
	for (int i = 1; (1 << i) <= depth[now]; ++i) {
		fa[now][i] = fa[fa[now][i - 1]][i - 1];
	}
	for(int i = head[now]; i; i = edge[i].next) {
		if(edge[i].to != pre) {
			DFS(edge[i].to, now);
		}
	}
}
int LCA(int a, int b) {
	//让 a 处于更低的深度
	if (depth[a] < depth[b]) swap(a, b);
	//然后让 a 向上爬，爬到与b相同深度
	//这里a与b的深度之差 是将10进制数看成二进制数 通过(1<<i) & dep 按位与操作判断2进制位上哪一位是1(去组装这个二进制数),
	//来向上跳跃到哪个祖先,从低位判断,从较近的祖先开始跳,因为一个10进制数是一定能表示成2进制的形式的 从小到大跳 是否效率低点 有待考证
	//注意这里是从小向大跳,所以一定是要验证所跳的这一步,对应的深度转化为二进制以后 是否还有这一位的1,因为不验证 原先若是个偶数,直接跳1,最终就会出错,最终所枚举出的二进制1是一定不等于这个10进制数的
	int dep = depth[a] - depth[b];
	for (int i = 0; (1 << i) <= dep; ++i) {
		if ((1 << i) & dep) {
			a = fa[a][i];
		}
	}
	//如果 b 爬到与 a 同一深度时 a == b 则直接返回该节点(该节点就是a b的LCA)
	if(a == b) return a;
	//否者 a b 同时向上倍增  从最远的开始试
	for (int i = log2(depth[a]); i >= 0; --i) {
			//如果父亲不同就向上跳， 如果父亲相同就减小距离再比较，直到不相同在跳。
		if (fa[a][i] != fa[b][i]) {
			a = fa[a][i];
			b = fa[b][i];
		}
	}
	return fa[a][0];
	//跳到最后 a 和 b 距离最近的LCA只差一步 所以返回 dp[a][0] 即可
}
int main() {
	scanf("%d%d%d", &N, &M, &S);
	init();
	int x, y;
	for (int i = 1; i < N; ++i) {
		scanf("%d%d", &x, &y);
		add_edge(x, y, 0);
		add_edge(y, x, 0);
	}
	for (int i = 1; i <= M; ++i) {
		scanf("%d%d", &x, &y);
		ask.push_back(make_pair(x, y));
	}
	DFS(S, 0);
	for(int i = 0; i < ask.size(); ++i) {
		int ans = LCA(ask[i].first, ask[i].second);
		printf("%d\n", ans);
	}
	return 0;
}
*/
/*深度上界log换底公式计算法 t=log(n)/log(2);
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 500100
int head[N],fa[N][21],dep[N],n,m,s,cnt,t;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

void dfs(int u,int fath){
    fa[u][0]=fath;
    dep[u]=dep[fath]+1;
    for(int i=1;(1<<i)<=dep[u];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)
            dfs(v,u);
    }
}

int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=t;i>=0;i--){
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    }
    if(x == y) return x;
    for(int i =t;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int main(){
    int x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    t=log(n)/log(2);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    dfs(s,0);
    while(m--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}
*/
