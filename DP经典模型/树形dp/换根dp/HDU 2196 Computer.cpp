#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
typedef long long ll;

/*
ac 31ms
题意:求解一棵树上各个节点距离其它节点的最远距离
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2196
思路:换根dp
dp[u][0]代表u距其子树中其它节点的正向最大距离.
dp[u][1]代表u距其子树中其它节点的正向次大距离
dp[u][2]代表u距其走过的父节点向上的反向最大距离
dp[u][0],dp[u][1]这里正向次大距离和正向最大距离一定是在u节点
的不同子树中的,因为在求解dp[v][2]时比较的是v节点的不同分支,如果最大距离和次大距离都在一棵子树里,那么次大距离也无法表示出来了.无法比较.
最终每个结点的答案就是max(dp[u][0],dp[u][2])
*/

int cnt,n,head[N],path[N];
ll dp[N][3];
struct Node{
    ll to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//子节点向父节点转移
void dfs1(int u,int fa){
    dp[u][0]=dp[u][1]=dp[u][2]=path[u]=0;//dp[u][2]在这里只是为进行dfs2之前做一遍初始化
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        //更新正向最大距离
        if(dp[u][0]<dp[v][0]+edge[i].w){
            //次大距离和最大距离在不同的子树路径中
            dp[u][1]=dp[u][0];//同时说明先前的正向最大距离已经不是最大了,变成次大了.
            dp[u][0]=dp[v][0]+edge[i].w;
            path[u]=v;//记录正向最大距离的路径 用于区分路径
        }//如果某些子树的分支最大距离没有先前最大距离大,但是比之前的正向次大距离要大,就更新次大距离
        else if(dp[u][1]<dp[v][0]+edge[i].w)
            dp[u][1]=dp[v][0]+edge[i].w;
    }
}
//换根dp,从父节点向子节点转移
void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //v节点在正向最大距离路径里 则比较v到父节点的反向最大距离和v到u节点u节点后的正向次大距离
        if(path[u] == v) dp[v][2]=max(dp[u][2],dp[u][1])+edge[i].w;
        //若v不在正向最大距离路径里,则比较v到父节点的反向最大距离和v到u节点u节点后的正向最大距离
        else dp[v][2]=max(dp[u][2],dp[u][0])+edge[i].w;
        dfs2(v,u);//先求解前面父节点的反向最大距离,才能再求解子节点的
    }
}

int main(){
    int v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=2;i<=n;i++){//输入是从第2个结点开始向v点连边的
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
            addEdge(v,i,w);
        }
        dfs1(1,-1);
        dfs2(1,-1);
        for(int i=1;i<=n;i++)
            printf("%lld\n",max(dp[i][0],dp[i][2]));
    }
    return 0;
}

/*
树的直径做法
只用一个dis数组 记录距离两端点的最大值
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
using namespace std;


int cnt,n,head[N],dis[N],ans,st;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//sum代表从st点出发现在所走的权值和
void dfs(int u,int fa,int sum){
    if(sum>ans){
        st=u;
        ans=sum;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=max(dis[v],sum+edge[i].w);//dis[v]取距离直径两端点的最大距离
        dfs(v,u,sum+edge[i].w);
    }
}

int main(){
    int v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=2;i<=n;i++){
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
            addEdge(v,i,w);
        }
        ans=-1;
        dfs(1,-1,0);
        ans=-1;//避免直径权值和没有之前大,而记录不到直径的另一端点
        dfs(st,-1,0);
        dfs(st,-1,0);
        for(int i=1;i<=n;i++)
            printf("%d\n",dis[i]);
    }
    return 0;
}
*/

/*
记忆化搜索 没看懂
传统的记忆化搜索做法 对于每个点都需要搜一遍,而n最大可达10000,基本会超时,
这里的做法借助了 map映射的做法
#include<bits/stdc++.h>//记忆化搜索 ac 124ms
#define MAXN 10010
using namespace std;
typedef pair<int, int > P;
vector <P > a[MAXN];
map <P, int> dp;
void Init(int n){
    dp.clear();
    for(int i = 1; i <= n; i++) a[i].clear();
}
void add_edge(int u, int v, int len){
    a[u].push_back(make_pair(v, len));
    a[v].push_back(make_pair(u, len));
}
int dfs(int now, int now_p){
    P edge = make_pair(now_p, now);
    if(dp[edge]) return dp[edge];
    for(int i = 0; i < a[now].size(); i++){
        int u = a[now][i].first, len = a[now][i].second;
        if(u == now_p) continue;
        dp[edge] = max(dp[edge], dfs(u, now) + len);
    }
    return dp[edge];
}
int main(){
    int n;
    while(scanf("%d", &n) != EOF){
        Init(n);
        int u, len;
        for(int i = 2; i <= n; i++){
            scanf("%d%d", &u, &len);
            add_edge(u, i, len);
        }
        for(int i = 1; i <= n; i++) printf("%d\n", dfs(i, -1));
    }
    return 0;
}
*/
