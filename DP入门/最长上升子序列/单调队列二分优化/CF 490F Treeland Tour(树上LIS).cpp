#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6500
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:一棵n个节点的树,每个节点都有点权,相同的节点不能重复遍历,
求遍历节点点权上升的最大长度.
链接:https://codeforces.ml/problemset/problem/490/F
思路:因为n<=6000,所以O(n^2)肯定超时,可以采取二分优化的LIS(nlogn)
这个因为是在树上,线性序列是未知的,所以也无法应用O(n^2)的dp做法求解LIS,
O(n^2)dp做法必须是在序列已知的情况下才能应用的.此题也只能用LIS的二分队列优化做法.
*/

int n,head[N],cnt,a[N],b[N],ans;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    /*
    每次遍历到新节点时找到原先b中第一个不小于a[u]的位置,若a[u]本身就是最大的位置,
    则a[u]就会加入b队列末尾,否则替换b中这个位置值,这样原先最大的值会变小,
    这样就有利于后面节点更多地加入b队列末尾,序列长度就会更长.
    */
    int pos=lower_bound(b+1,b+n+1,a[u])-b;
    ans=max(ans,pos);//记录序列最大长度
    int tmp=b[pos];
    b[pos]=a[u];//更新b中pos位置的值
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
    }
    //回溯时b数组原先的值要还原,因为下个节点是在另外分支父节点的位置必须还是原来的
    b[pos]=tmp;
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        /*
        因为这里我们省略了b数组插入过程,所以利用lower_bound(返回不小于a[u]的位置)
        返回的pos来使得序列中更大值赋值给队列末尾,因此b数组每个位置初始值都是INF(无穷大),
        这样较大的值就会插入到当前队列末尾.如果不设置INF,lower_bound遇到较大值的查询就无法返回
        队列末尾的位置.就无法赋值
        */
        memset(b,INF,sizeof(b));
        dfs(i,-1);
    }
    printf("%d",ans);
    return 0;
}

/*
线段树优化版
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0'||c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c&&c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
template < class T >
void getMax(T&a,const T&b){if(a<b) a=b;}
template < class T >
void getMin(T&a,const T&b){if(b<a) a=b;}

const int MaxN = 6005;
struct Edge{
	int to, nxt;
	Edge(int T=0,int N=0){
		to = T, nxt = N;
	}
} edge[MaxN<<1];
int head[MaxN], cntEdge;
void addEdge(int a,int b){
	edge[cntEdge] = Edge(b,head[a]);
	head[a] = cntEdge ++;
	edge[cntEdge] = Edge(a,head[b]);
	head[b] = cntEdge ++;
}

template < class T , int normal >
class L_S{ // LIS or LDS
	int g[MaxN], n; T cmp;
public:
	void clear(){ n = 0; }
	int query(int x){
		int L = 0, R = n;
		while(L < R)
			if(cmp(g[(L+R+1)/2],x))
				L = (L+R+1)>>1;
			else R = (L+R+1)/2-1;
		return L+1;
	}
	void modify(int id,int x){
		while(n < id)
			g[++ n] = normal;
		if(cmp(x,g[id]))
			g[id] = x; // 请自行保证有序
	}
};

int son[MaxN], siz[MaxN];
void build(int x,int pre){
	siz[x] = 1, son[x] = 0;
	for(int i=head[x]; ~i; i=edge[i].nxt)
		if(edge[i].to != pre){
			build(edge[i].to,x);
			if(siz[edge[i].to] > siz[son[x]])
				son[x] = edge[i].to;
			siz[x] += siz[edge[i].to];
		}
}

const int infty = (1<<30)-1;
int a[MaxN], n, ans, up[MaxN], down[MaxN];
L_S< less<int>,infty > LIS;
L_S< greater<int>,-infty > LDS;
void modify(int x,int pre){
	LIS.modify(up[x],a[x]);
	LDS.modify(down[x],a[x]);
	for(int i=head[x]; ~i; i=edge[i].nxt)
		if(edge[i].to != pre)
			modify(edge[i].to,x);
}
void updata(int rt,int x,int pre){
	for(int i=head[x]; ~i; i=edge[i].nxt)
		if(edge[i].to != pre)
			updata(rt,edge[i].to,x);
	getMax(ans,LIS.query(a[x])+down[x]-1);
	if(a[x] > a[rt])
		getMax(ans,LIS.query(a[rt])+down[x]);
	getMax(ans,LDS.query(a[x])+up[x]-1);
	if(a[x] < a[rt])
		getMax(ans,LDS.query(a[rt])+up[x]);
}
void dfs(int x,int pre,bool f){
	for(int i=head[x]; ~i; i=edge[i].nxt)
		if(edge[i].to != pre)
		if(edge[i].to != son[x])
			dfs(edge[i].to,x,0);
	if(son[x]) dfs(son[x],x,1);
	for(int i=head[x]; ~i; i=edge[i].nxt)
		if(edge[i].to != pre)
		if(edge[i].to != son[x]){
			updata(x,edge[i].to,x);
			modify(edge[i].to,x);
		}
	up[x] = LIS.query(a[x]);
	down[x] = LDS.query(a[x]);
	if(!f) LIS.clear(), LDS.clear();
	else{
		LIS.modify(up[x],a[x]);
		LDS.modify(down[x],a[x]);
	}
}

int main(){
	n = readint();
	for(int i=1; i<=n; ++i){
		head[i] = -1;
		a[i] = readint();
	}
	for(int i=1; i<n; ++i)
		addEdge(readint(),readint());
	dfs(1,-1,1);
	for(int i=1; i<=n; ++i)
		getMax(ans,max(up[i],down[i]));
	printf("%d\n",ans);
	return 0;
}

*/
/*
这种自己写的入队做法很容易出错,还是直接初始化INF,二分查找最大值返回队末位置好实现.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6500
#define INF 0x3f3f3f3f
using namespace std;

int n,head[N],cnt,a[N],b[N],ans;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int num){
    int pos,flag=1;
    if(b[num-1]<a[u]){
        b[num]=a[u];
        ans=max(ans,num);
        printf("a[%d]=%d num=%d\n",u,a[u],num);
    }
    else{
        pos=lower_bound(b+1,b+num-1,a[u])-b;
        flag=0;
    }
    int tmp;
    if(!flag){
        tmp=b[pos];
        b[pos]=a[u];
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u,num+1);
    }
    if(!flag)
        b[pos]=tmp;
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        memset(b,0,sizeof(b));
        //b[0]=INF;
        dfs(i,-1,1);
    }
    printf("%d",ans);
    return 0;
}

*/
