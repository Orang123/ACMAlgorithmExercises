#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 1100
#define M 1000100
using namespace std;
//ac 10ms tarjan缩点求解ebc
//洛谷详细题解:https://www.luogu.com.cn/problem/solution/UVA10972 没太详细看,有时间再看看.
/*
题意:一个无向图要添加多少条边才能使其变为边双连通图,原图可能不连通.
另一种题意:给你一个n个点m条边的无向图,不一定联通.现在你需要把原有的无向边变为有向边,
并加入一些新的有向边.问最少加入多少条有向边使得图只有一个强连通分量.
原英文题意 有点看不明白,感觉意思是第二种题意,加的是有向边.
链接:https://www.luogu.com.cn/problem/UVA10972
思路:还是用原图连通的办法tarjan缩点求出无向树,对于度为1的叶子节点,ans+=1,
对于被孤立的点度为0,ans+=2,最后最少加边数=(ans+1)/2.
*/

int n,m,dfn[N],low[N],clock,cnt,ebc_cnt,head[N],block[N],de[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
            block[v]=ebc_cnt;
        }while(v!=u);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        ebc_cnt=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(de,0,sizeof(de));
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=1;i<=n;i++){//原图可能不连通
            if(!dfn[i])
                dfs(i,-1);
        }
        //因为图不连通的情况 要判断度为0 +2的情况,所以原图如果本事就是EBG,要特判
        if(ebc_cnt == 1){//原图本身就是边双连通图,不需要添加边,输出0.
            printf("0\n");
            continue;
        }
        for(int i=0;i<cnt;i+=2){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                de[block[u]]++;
                de[block[v]]++;
            }
        }
        int ans=0;
        for(int i=1;i<=ebc_cnt;i++){
            if(!de[i]) ans+=2;//原图不连通被孤立的 度为0的缩点,+2
            if(de[i] == 1) ans++;//对于度为1的叶子节点+1
        }
        printf("%d\n",(ans+1)/2);
    }
    return 0;
}

/*
//另一种复杂写法,感觉有点没必要
//https://www.cnblogs.com/scau20110726/archive/2013/05/18/3086330.html
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;
#define N 1010

int n,tot;
int dfn[N],low[N],vis[N],de[N],dcnt,bcnt;
vector<int>e[N];

void init()
{
    dcnt = bcnt = 0;
    for(int i=1; i<=n; i++)
    {
        dfn[i] = 0;
        e[i].clear();
        vis[i] = de[i] = 0;
    }
}

void dfs(int u ,int fa)
{
    dfn[u] = low[u] = ++dcnt;
    vis[u] = 1;
    for(int i=0; i<e[u].size(); i++)
    {
        int v = e[u][i];
        if(v == fa) continue;
        if(!vis[v]) //树边
        {
            dfs(v,u);
            low[u] = min(low[u] , low[v]);
            if(low[v] > dfn[u]) //找到一个桥,新增一个连通分量
                bcnt++;
        }
        else if(vis[v] == 1) //后向边
            low[u] = min(low[u] , dfn[v]);
    }
}

void solve()
{
    for(int i=1; i<=n; i++)
        if(!vis[i])
        {
            dfs(i,-1);
            bcnt++;
        }
    if(bcnt == 1) //整个图本身就是个双连通分量
    { cout << 0 << endl; return ; }

    bool used[N];
    memset(used,false,sizeof(used));
    for(int i=1; i<=n; i++)
    {
        if(e[i].size() == 0) //孤立点，它自身形成一个连通分量
        { used[low[i]] = true ; continue; }

        for(int j=0; j<e[i].size(); j++)
        {
            int u = i;
            int v = e[i][j];
            used[low[u]] = used[low[v]] = true;
            if(low[u] != low[v]) //不同的连通分量
                de[low[u]]++;
        }
    }

    int res = 0;
    for(int i=1; i<=n; i++)  //扫描缩点后每个点的度
        if(used[i] && de[i] == 0) //度为0即孤立点
            res += 2;
        else if(de[i] == 1) //叶子
            res++;
    cout << (res+1)/2 << endl;
}

int main()
{
    while(cin >> n >> tot)
    {
        init();
        while(tot--)
        {
            int u,v;
            cin >> u >> v;
            e[u].push_back(v);
            e[v].push_back(u);
            //偷懒直接用vector建图不用静态链表了
        }
        solve();
    }
    return 0;
}
*/

/*
//这种做法好像是将无向图转化为有向图,加有向边考虑的.
//https://www.luogu.com.cn/problem/solution/UVA10972
#include <stack>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

const int N = 1010;

int n, m, color, tot;
int col_p[N], dfn[N], low[N];
bool in[N], visit[N];
std::vector <int > link[N];
std::vector <int > new_link[N];
std::stack <int > s;

void tarjan(int wz, int fa)//无向图求环...类似有向图
{
	dfn[wz] = low[wz] = ++tot;
	in[wz] = true, s.push(wz);

	for(int k = 0; k < (int )link[wz].size(); k++)
	{
		int to = link[wz][k];

		if(!dfn[to])
		{
			tarjan(to, wz);
			low[wz] = std::min(low[wz], low[to]);
		}
		else if(in[to] && to != fa)
			low[wz] = std::min(low[wz], dfn[to]);
	}

	if(low[wz] == dfn[wz])
	{
		color++;

		while(s.top() != wz)
		{
			col_p[s.top() ] = color;

			in[s.top() ] = false, s.pop() ;
		}

		col_p[wz] = color;

		in[s.top() ] = false, s.pop() ;
	}
}

void build()
{
	for(int k = 1; k <= n; k++)
		for(int i = 0; i < (int )link[k].size() ; i++)
		{
			int to = link[k][i];

			if(col_p[to] != col_p[k])
				new_link[col_p[to]].push_back(col_p[k]);
		}
}

int answ;

int dfs(int wz, int fa)
{
	visit[wz] = true;

	int size1 = (int )new_link[wz].size();

	int size0 = size1 == 0 ? 2 : size1 == 1 ? 1 : 0;

	for(int k = 0; k < (int )new_link[wz].size(); k++)
	{
		int to = new_link[wz][k];

		if(to != fa)
			size0 += dfs(to, wz);
	}

	return size0;
}

void work()
{
	memset(link, 0, sizeof(link));
	memset(new_link, 0, sizeof(new_link));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(visit, 0, sizeof(visit));
	tot = color = answ = 0;

	for(int k = 1; k <= m; k++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		link[l].push_back(r);
		link[r].push_back(l);
	}

	//缩点
	for(int k = 1; k <= n; k++)
		if(!dfn[k])
			tarjan(k, 0);

	//重建图
	build();

	//搜索度数为0或1的点
	for(int k = 1; k <= color; k++)
		if(!visit[k])
			answ += dfs(k, 0);

	if(color!=1)
		printf("%d\n", (int )ceil(answ / 2.0));
	else
		printf("0\n");
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		work();
	}

	return 0;
}
*/
