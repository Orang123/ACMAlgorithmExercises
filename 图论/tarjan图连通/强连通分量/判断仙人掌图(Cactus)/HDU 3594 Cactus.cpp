#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 20100
using namespace std;
//ac 78ms
//虽然这题 ac了,但听说是因为数据水,正解还有待考证,后面有时间看看那个Cactus的PDF讲解
//不过用这个办法 hdu 3594 UVA 10510这2题都ac了
/*
题意:判断一个图是否是仙人掌(Cactus)图.仙人掌图为有向图.
仙人掌图满足两个条件:
1.所有的边都在环上.
2.所有的边都只属于1个环.
释义:是否是强连通图,scc个数是否为1.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3594
思路:条件1只要满足scc的个数为1即可,条件2可以在tarjan求解scc
时,记录每个节点的前驱节点,当遇到回边重复访问v点时,就将当前点不断回跳到
之前的祖先节点直到返回到v时结束,这个跳跃过程不断累加没个点出现次数,
如果某个点出现了2次就说明这哥点所连的边 至少出现在了2个环上,就可以结束,
说明不是仙人掌图.
*/

int n,head[N],cnt;
int dfn[N],low[N],in[N],clock,id,block[N],pre[N],num[N],flag;
stack<int> s;

struct Edge{
    int to,next;
}edge[N*N/2];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            pre[v]=u;
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v]){
            low[u]=min(low[u],dfn[v]);
            int tmp=u;
            //遇到回边v点已访问时,向祖先节点往回跳跃 直到再次回到v点,注意这里v点是不能num[v]++的,否则如果是两个环紧贴会错判不是Cactus
            while(tmp!=v){
                num[tmp]++;//记录祖先链上 每个点出现次数
                if(num[tmp]>1){//当大于1时
                    flag=1;
                    return;
                }
                tmp=pre[tmp];
            }
        }
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=id;
        }while(v!=u);
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        flag=id=clock=cnt=0;
        memset(head,-1,sizeof(head));
        //这里不能赋值-1 否则会导致数组小标出现-1,虽然答案也正确 但是程序逻辑是有误的
        memset(pre,0,sizeof(pre));
        memset(num,0,sizeof(num));
        memset(dfn,0,sizeof(dfn));
        scanf("%d",&n);
        while(scanf("%d%d",&u,&v) && u+v)
            addEdge(u,v);
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i);
        }
        if(id>1 || flag) printf("NO\n");//当scc个数大于1或某条边属于至少2个环时,说明不是仙人掌图.
        else printf("YES\n");
    }
    return 0;
}
/*
//输入样例
input
2
5
0 1
1 2
2 0
2 3
3 4
4 2
0 0

5
0 1
1 2
2 3
3 4
3 1
4 0
0 0

4
0 1
1 2
2 3
3 1
3 0
0 0

output
YES
NO
NO
*/

/*
//另一种判断仙人掌图的办法
//https://www.cnblogs.com/AOQNRMGYXLMV/p/5353502.html
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

const int maxn = 10000 + 10;

int n, m;
vector<int> G[maxn];

stack<int> S;
int dfs_clock, pre[maxn], low[maxn];
int scc_cnt, sccno[maxn];

void dfs(int u) {
	pre[u] = low[u] = ++dfs_clock;
	S.push(u);
	for(int v : G[u]) {
		if(!pre[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(!sccno[v]) low[u] = min(low[u], pre[v]);
	}
	if(low[u] == pre[u]) {
		scc_cnt++;
		for(;;) {
			int x = S.top(); S.pop();
			sccno[x] = scc_cnt;
			if(x == u) break;
		}
	}
}

//Tarjan算法求强连通分量
void find_scc() {
	dfs_clock = scc_cnt = 0;
	memset(pre, 0, sizeof(pre));
	memset(sccno, 0, sizeof(sccno));
	for(int i = 0; i < n; i++) if(!pre[i])
		dfs(i);
}

//第二遍DFS保证是仙人掌图

//color[u]为0表示还没有访问，为1表示正在访问，为2表示已经访问完毕
int color[maxn];

bool dfs2(int u, int minBack) {    //minBack表示反向边能指向的最小的DFS序
	color[u] = 1;
	int backs = 0;//反向边的个数，至多只能有一个
	for(int v : G[u]) if(color[v] == 1) {    //找到一条反向边
		backs++;
		if(backs > 1) return false;
		if(pre[v] < minBack) return false;    //反向边指向的节点的DFS序小于最小值
	}
	if(backs) minBack = pre[u];
	for(int v : G[u]) {
		if(color[v] == 2) return false;    //前向边或交叉边
		if(color[v] == 0)    //树边
			if(!dfs2(v, minBack)) return false;;
	}
	color[u] = 2;
	return true;
}

int main()
{
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++) G[i].clear();
		while(m--) {
			int u, v; scanf("%d%d", &u, &v);
			G[u].push_back(v);
		}

		find_scc();
		if(scc_cnt > 1) { puts("NO"); continue; }

		memset(color, 0, sizeof(color));
		if(!dfs2(0, 0)) puts("NO");
		else puts("YES");
	}

	return 0;

}
*/

/*
//https://www.cnblogs.com/cenariusxz/p/4814504.html
//首先，tarjan可以判强连通分量是否只有一个。然后对于所有边是否仅在一个环内，
//我的做法是，当一个点在 tarjan 的 dfs 中，引出下一条边，如果这条边指向了
//一个时间轴上比它大的点，那么该点一定是 dfs 树中它的后继节点，在之前必定有
//一条这两点之间的路径，那么这两点之间就已经有两条路径了，而从后继节点一定能返回到
//祖先节点而形成环（强连通），所以返回祖先节点的路径一定与两点间的两条路径形成两个环，
//就不符合仙人掌图了。而如果这条边指向了一个时间轴上比它小的点，那么或者那个点
//是这个圈的访问祖先，或者那个点是其他圈中的点，那么这一段一定都在一个圈上，
//那就不断遍历回祖先将点的访问数+1。最后再判断是否每个点的访问数小于等于1就行了。
#include<stdio.h>
#include<string.h>
#include<stack>
#include<queue>
using namespace std;

const int maxn=2e4+5;
const int maxm=5e4+5;

int head[maxn],point[maxm],nxt[maxm],size;
int n,t,scccnt;
int stx[maxn],low[maxn],scc[maxn];
int fa[maxn];
int vis[maxn];
stack<int>S;
bool f;

void init(){
    memset(head,-1,sizeof(head));
    size=0;
    f=1;
    memset(vis,0,sizeof(vis));
    memset(fa,-1,sizeof(fa));
}

void add(int a,int b){
    point[size]=b;
    nxt[size]=head[a];
    head[a]=size++;
}

void dfs(int s,int pre){
    fa[s]=pre;
    stx[s]=low[s]=++t;
    S.push(s);
    for(int i=head[s];~i;i=nxt[i]){
        int j=point[i];
        if(!stx[j]){
            dfs(j,s);
            low[s]=min(low[s],low[j]);
        }
        else if(!scc[j]){
            if(stx[j]<stx[s]){
                int k=s;
                while(k!=j&&k!=-1){
                    vis[k]++;
                    k=fa[k];
                }
            }
            else f=0;
            low[s]=min(low[s],stx[j]);
        }
    }
    if(low[s]==stx[s]){
        scccnt++;
        while(1){
            int u=S.top();S.pop();
            scc[u]=scccnt;
            if(s==u)break;
        }
    }
}

void setscc(){
    memset(stx,0,sizeof(stx));
    memset(scc,0,sizeof(scc));
    t=scccnt=0;
    for(int i=0;i<n;++i)if(!stx[i])dfs(i,-1);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int m;
        scanf("%d",&n);
        init();
        int a,b;
        while(scanf("%d%d",&a,&b)&&a+b){
            add(a,b);
        }
        setscc();
        for(int i=0;i<n;++i)if(vis[i]>1)f=0;
        if(scccnt>1||!f)printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
*/
