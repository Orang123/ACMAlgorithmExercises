#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 10100
using namespace std;
//ac 0ms
/*
题意:判断仙人掌图
链接:https://www.luogu.com.cn/problem/UVA10510
思路:tarjan求解scc,scc个数必须为1,判断回边点出现次数,大于2时不是Cactus.
*/

int n,m,head[N],cnt;
int dfn[N],low[N],in[N],clock,id,block[N],pre[N],num[N],flag;
stack<int> s;

struct Edge{
    int to,next;
}edge[N];

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
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
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
//ac 20ms
// * UVA 10510 - Cactus
// * Main idea: First check the graph is a single strongly connected
// *            component. Then draw the DFS tree - if the graph has
// *            any cross/forward edge, then it's not a cactus. If there
// *            exists a node who has more than one children with a back
// *            edge to the ancestor of the node, then the graph is not a
// *            cactus.
// *
//这份代码没有考虑只能有一条反向边的限制，但也能在UVA上AC
#include <iostream>
#include<cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
vector<int> edge[10005];
int dfsnum[10005];
int scc[10005];
int st[10005];
int low[10005];
int color[10005];
int num_scc;
int num;
int n, m;
int stack_sz;

// strongly connected component - hacked to be like a DP
int SCC(int x) {
  if (dfsnum[x] == -1) low[x] = dfsnum[x] = num++;
  else return low[x];

  st[stack_sz++] = x;
  for (int i = 0; i < (int)edge[x].size(); ++i)
    if (scc[edge[x][i]] == -1) low[x] = min(low[x], SCC(edge[x][i]));
  if (low[x] == dfsnum[x])  {
    while (scc[x] != num_scc)
      scc[st[--stack_sz]] = num_scc;
    ++num_scc;
  }
  return low[x];
}

// dfs to find any cross/forward edge and "bad" back edge.
// return true iff graph is a cactus
bool dfs(int x, int minBackEdge) {
  color[x] = 1;
  bool hasBackEdge = false;
  // check whether I have a back Edge
  for (int i = 0; i < (int) edge[x].size(); ++i) {
    if (color[edge[x][i]] == 1) {
      hasBackEdge = true;
      // a back edge to a dfsnum that's too small
      // this means an edge is shared by two cycles
      if (dfsnum[edge[x][i]] < minBackEdge)
	return false;
    }
  }

  if (hasBackEdge) minBackEdge = dfsnum[x];

  for (int i = 0; i < (int) edge[x].size(); ++i) {
    if (color[edge[x][i]] == 0) {
      // recurse on forward edge
      if (!dfs(edge[x][i], minBackEdge)) return false;
    } else if (color[edge[x][i]] == 2) {
      // found a forward/cross edge - so an edge is shared by two cycles
      return false;
    }
  }
  color[x] = 2;
  return true;
}

int main() {
  int ncase;
  cin >> ncase;
  while (ncase--) {
    cin >> n >> m;

    memset(scc, -1, sizeof(scc));
    memset(dfsnum, -1, sizeof(dfsnum));
    memset(low, -1, sizeof(low));
    memset(color, 0, sizeof(color));
    num_scc = num = stack_sz = 0;
    for (int i = 0; i < n; ++i) edge[i].clear();

    int tx, ty;
    for (int i = 0; i < m; ++i) {
      cin >> tx >> ty;
      edge[tx].push_back(ty);
    }

    // this handles the case of disconnected graph
    for (int i = 0; i < n; ++i) SCC(i);

    // make sure only one strongly connected component
    if (num_scc == 1) {
      if (dfs(0, -1)) cout << "YES" << endl;
      else cout << "NO" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
*/

/*
//ac 0ms
//https://www.luogu.com.cn/problem/solution/UVA10510
#include <cstdio>
#include <cctype>
#include <stack>
#include <cstring>
#define rr register
using namespace std;
const int N=20011; stack<int>stac;
struct node{int y,next;}e[N*3]; bool v[N];
int dfn[N],low[N],TOT,cnt,n,k,tot,flag,as[N];
inline signed iut(){
	rr int ans=0; rr char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans;
}
inline signed min(int a,int b){return a<b?a:b;}
inline void tarjan(int x){
	dfn[x]=low[x]=++tot;
	stac.push(x); v[x]=1;
	rr int TOT=0;
	for (rr int i=as[x];i;i=e[i].next)
	if (!dfn[e[i].y]){
		tarjan(e[i].y);
		low[x]=min(low[x],low[e[i].y]);
		if (low[e[i].y]<dfn[x]) ++TOT;
		if (low[e[i].y]>dfn[x]) flag=0;//第二条性质
	}
	else if (v[e[i].y])
	    low[x]=min(low[x],dfn[e[i].y]),++TOT;
	if (TOT>1) flag=0;//第三条性质
	if (dfn[x]==low[x]){
		++cnt; rr int y;
		do{
			y=stac.top();
			stac.pop();
			v[y]=0;
		}while (x!=y);
	}
}
signed main(){
	for (rr int T=iut();T;--T){
		n=iut(),k=flag=1,cnt=TOT=tot=0;
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(as,0,sizeof(as));
		for (rr int m=iut();m;--m){
			rr int x=iut()+1,y=iut()+1;
			e[++k]=(node){y,as[x]},as[x]=k;
		}
		for (rr int i=1;i<=n;++i)
		    if (!dfn[i]) tarjan(i);
		if (cnt>1||!flag) printf("NO\n");//有一条不满足即为NO
		    else printf("YES\n");
	}
	return 0;
}
*/
