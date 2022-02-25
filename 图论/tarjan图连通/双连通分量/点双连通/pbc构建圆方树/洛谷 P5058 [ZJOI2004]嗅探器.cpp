#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 200100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
//ac 19ms tarjan求解pbc+构造圆方树+dfs搜索a-b间最小圆点
//如果增强数据加上q次询问 可以考虑lca倍增或st表lca倍增的做法遍历圆方树
//圆方树参考博客: https://www.cnblogs.com/PinkRabbit/p/10446473.html
/*
题意:某军搞信息对抗实战演习,红军成功地侵入了蓝军的内部网络.
蓝军共有两个信息中心,红军计划在某台中间服务器上安装一个嗅探器,
从而能够侦听到两个信息中心互相交换的所有信息.但是蓝军的网络
相当的庞大,数据包从一个信息中心传到另一个信息中心可以不止有
一条通路.现在需要你尽快地解决这个问题,应该把嗅探器安装在哪个
中间服务器上才能保证所有的数据包都能被捕获?
释义:n个点的无向图,求解影响a、b两点连通性的最小编号的割点.
链接:https://www.luogu.com.cn/problem/P5058
思路:
圆方树:把原图中每个点当成一个圆点,给每个pbc创建一个虚拟的方点,
把属于这个pbc中的圆点和对应的方点连无向边,这样如果原图是连通的,则
圆方树会是一棵树,如果原图不连通,则圆方树是森林.
圆方树中方点的个数就是PBC的个数,而pbc的个数取决于割点的个数,而
原图割点的个数(算上初始根节点,不考虑其分支数)最多为n-1个,因此圆方树
中的点的个数<2N.而对于圆方树中的叶子节点(圆点)就是每个pbc中除过割点外的节点,
而圆方树中度大于1的圆点就是每个pbc中的割点,因为割点至少连接2个pbc.
圆方树中方点的点的度为每个pbc中点的个数.
tarjan求解pbc,构建圆方树.dfs从a点遍历圆方树找最小圆点编号(除过a、b两点).
这里不用特判是否是割点,因为在a-b的路径上除过a、b可能度为1外,中间的点度
必然是大于1的,因此只需判断中间的点是否是圆点即可.
*/

int head[N],cnt,a,b;
int n,m,dfn[N],low[N],clock,pbc_cnt,vis[N<<1],ans;
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//O(V+E)
void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
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
                    //标记圆点 除过pbc割点外 其余点都是圆方树中的叶子节点(圆点)
                    //而割点为圆方树中的方点
                    vis[tmp]=1;
                    s.pop();
                    G[pbc_cnt].push_back(tmp);
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                vis[u]=1;
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

//O(V+E)
int dfs(int u,int fa){
    for(int v : G[u]){
        if(v == fa) continue;
        //找到b点回溯a-b间路径的点编号
        if(v == b) return 1;//除过a b 两端点和中间的方点外 都比较记录最小圆点编号
        if(dfs(v,u)){
            if(vis[v])//不记录方点的编号
                ans=min(ans,v);
            return 1;
        }
    }
    return 0;
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;//圆方树 方点编号要从n+1开始编
    ans=INF;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    m=n<<1;//圆方树点的个数最大为2n-1
    for(int i=1;i<m;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    while(scanf("%d%d",&u,&v) && u+v){
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,-1);
    }
    scanf("%d%d",&a,&b);
    dfs(a,-1);
    if(ans!=INF) printf("%d",ans);
    else printf("No solution");
    return 0;
}

/*
//4ms tarjan求解割点,根据时间戳dfn判断割点是否在a与b之前的路径上
//还有另外一种 做法是low[u]=min(low[u],low[v]);只有在u不是割点时才更新,有点奇怪 https://www.luogu.com.cn/problem/solution/P5058 江镗(洛谷网友题解)
//4ms tarjan求解割点,根据时间戳dfn判断割点是否在a与b之前的路径上
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 200100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

int head[N],cnt,a,b;
int n,dfn[N],low[N],clock,ans;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//O(V+E)
void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            //dfn[v]<=dfn[b] 说明b是v子树中的节点,u!=a,那么删除u必然会使得a与b所在连通块不连通
            if(dfn[u]<=low[v] && u!=a && dfn[v]<=dfn[b])//对于u=b时,dfn[v]>dfn[b]显然也不成立
                ans=min(ans,u);//记录最小割点编号
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    clock=cnt=0;
    ans=INF;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    while(scanf("%d%d",&u,&v) && u+v){
        addEdge(u,v);
        addEdge(v,u);
    }
    scanf("%d%d",&a,&b);
    tarjan(a,-1);//直接从a点开始遍历 a b两点不能作为割点
    if(!dfn[b]){//若a b两点不连通 则无解
        printf("No solution");
        return 0;
    }
    if(ans!=INF)
        printf("%d",ans);
    else
        printf("No solution");
    return 0;
}
*/

/*
//tarjan时间戳判断法 的一般形式 if(!dfn[i]) tarjan(i,-1);需要同时判断a或b的时间戳哪个在前面哪个在后面
#include <bits/stdc++.h>
using namespace std;

const int N=2e5+10,M=5e5+10;
int vex[N],k,n,m,A,B,ans=1e9;
struct edge {
	int u,v,next;
}e[M*2];

void add(int u,int v){
	k++;
	e[k].u=u;
	e[k].v=v;
	e[k].next=vex[u];
	vex[u]=k;
	return;
}

int dfn[N],low[N],idx;

int check(int u,int v){
	if(dfn[v]<=dfn[A]&&dfn[v]>dfn[B]) return 1;
	if(dfn[v]<=dfn[B]&&dfn[v]>dfn[A]) return 1;
	return 0;
}

void tarjan(int u,int fa){
	dfn[u]=low[u]=++idx;
	for(int i=vex[u];i;i=e[i].next){
		int v=e[i].v;
		if(!dfn[v]) {
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]&&u!=A&&u!=B&&check(u,v)) {
				ans=min(ans,u);
			}
		}
		else if(v!=fa) low[u]=min(low[u],dfn[v]);
	}
	return;
}

int main(){
	cin>>n;
	while(1){
		int u,v;
		cin>>u>>v;
		if(u==0&&v==0) break;
		add(u,v);
		add(v,u);
	}
	cin>>A>>B;
	tarjan(1,0);
	if(ans==1e9) cout<<"No solution";
	else cout<<ans;
	return 0;
}
*/

/*
//ac 20ms tarjan求解pbc+构造圆方树+bfs搜索a-b间最小圆点
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 200100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
int head[N],cnt,a,b;
int n,m,dfn[N],low[N],clock,pbc_cnt,vis[N<<1],ans;
stack<int> s;
vector<int> G[N<<1];
struct Node{
    int u,minv,fa;
    Node(int u=0,int minv=0,int fa=0):u(u),minv(minv),fa(fa){}
};

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
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
                    vis[tmp]=1;
                    s.pop();
                    G[pbc_cnt].push_back(tmp);
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                vis[u]=1;
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void bfs(){
    queue<Node> Q;
    Q.push(Node(a,INF,-1));
    int u;
    Node tmp;
    while(!Q.empty()){
        tmp=Q.front();
        Q.pop();
        u=tmp.u;
        for(int v : G[u]){
            if(v == tmp.fa) continue;
            if(v == b){
                ans=tmp.minv;
                return;
            }
            Q.push(Node(v,vis[v]?min(tmp.minv,v):tmp.minv,u));
        }
    }
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;
    ans=INF;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    m=n<<1;
    for(int i=1;i<m;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    while(scanf("%d%d",&u,&v) && u+v){
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,-1);
    }
    scanf("%d%d",&a,&b);
    bfs();
    if(ans!=INF) printf("%d",ans);
    else printf("No solution");
    return 0;
}
*/

/*
若有q次询问,q很大,可以考虑lca倍增遍历圆方树
若q更大,可以考虑st表存lca O(1)查询
*/

/*
//ac 18ms tarjan求解pbc+构造a点的圆方树+dfs搜索a-b间最小圆点
//tarjan不构造森林,只构造包含a点的圆方树
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 200100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

int head[N],cnt,a,b;
int n,m,dfn[N],low[N],clock,pbc_cnt,vis[N<<1],ans;
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//O(V+E)
void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
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
                    vis[tmp]=1;
                    s.pop();
                    G[pbc_cnt].push_back(tmp);
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                vis[u]=1;
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

//O(V+E)
int dfs(int u,int fa){
    for(int v : G[u]){
        if(v == fa) continue;
        if(v == b) return 1;
        if(dfs(v,u)){
            if(vis[v])
                ans=min(ans,v);
            return 1;
        }
    }
    return 0;
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;//方点编号要从n+1开始编
    ans=INF;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    m=n<<1;
    for(int i=1;i<m;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    while(scanf("%d%d",&u,&v) && u+v){
        addEdge(u,v);
        addEdge(v,u);
    }
    scanf("%d%d",&a,&b);
    tarjan(a,-1);//只需构造包含a点的连通块的圆方树
    if(!dfn[b]){//若a b两点不连通 则无解
        printf("No solution");
        return 0;
    }
    dfs(a,-1);
    if(ans!=INF) printf("%d",ans);
    else printf("No solution");
    return 0;
}
*/
