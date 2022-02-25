#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 510
#define M 50100
using namespace std;
/*
题意:最小生成树中哪些边是必须存在的,输出这样的边的个数,
以及其边权和.
题目描述:https://www.codeqq.com/log/jyGoP8Wy.html
链接:ACM ICPC UVALive - 6837 or csu 1541 There is No Alternative
http://acm.csu.edu.cn/OnlineJudge/problem.php?id=1541 需要vpn
思路:可以先求解出mst的边权和sum,然后暴力枚举删除mst中的某条边之后再次求解mst,
如果最终求得的生成树或连通集(可能不连通)权值和之前不相等那么说明这条边是mst中必须要有的.
*/

int n,m,fa[N];
vector<int> seq;

struct Edge{
    int u,v,w;
    bool operator <(const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(int id){
    init();
    int x,y,sum=0,cnt=0;
    for(int i=1;i<=m;i++){
        if(i == id) continue;
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            cnt++;
            sum+=edge[i].w;
            if(!id) seq.push_back(i);//第一次求解mst时将边的编号记录下来方便枚举删除
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    int sum,cnt,ans;
    while(scanf("%d%d",&n,&m)!=EOF){
        ans=cnt=0;
        seq.clear();
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        sort(edge+1,edge+1+m);
        sum=kruskal(0);
        for(int i=0;i<seq.size();i++){
            int tmp=kruskal(seq[i]);
            if(tmp!=sum){
                cnt++;
                ans+=edge[seq[i]].w;
            }
        }
        printf("%d %d\n",cnt,ans);
    }
    return 0;
}

/*
//lca记录树上任意两点间路径线性判断成环后的路径上是否有和添加边权值相等的
//
//  Created by TaoSama on 2015-12-04
//  Copyright (c) 2015 TaoSama. All rights reserved.
//
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

using namespace std;
#define pr(x) cout << #x << " = " << x << "  "
#define prln(x) cout << #x << " = " << x << endl
const int N = 5e2 + 10, INF = 0x3f3f3f3f, MOD = 1e9 + 7;
const int M = N * N;

int n, m;

int par[N];
int find(int x) {
    return par[x] = par[x] == x ? x : find(par[x]);
}

struct Edge {
    int u, v, c;
    bool operator< (const Edge& e) const {
        return c < e.c;
    }
} edge[M];

bool vis[M];
int g[N][N];

int kruskal() {
    int ret = 0, cnt = 0;
    sort(edge + 1, edge + 1 + m);
    for(int i = 1; i <= n; ++i) par[i] = i;
    memset(g, 0, sizeof g);
    memset(vis, false, sizeof vis);
    for(int i = 1; i <= m; ++i) {
        Edge& e = edge[i];
        int u = find(e.u), v = find(e.v);
        if(u == v) continue;
        par[v] = u; vis[i] = true;
        g[e.u][e.v] = g[e.v][e.u] = e.c;
        ret += e.c;
        if(++cnt == n - 1) break;
    }
    return ret;
}

int dep[N], p[N];

void dfs(int u, int f, int d) {
    dep[u] = d; p[u] = f;
    for(int v = 1; v <= n; ++v) {
        if(!g[u][v] || v == f) continue;
        dfs(v, u, d + 1);
    }
}

int lca(int u, int v) {
    if(dep[u] > dep[v]) swap(u, v);
    while(dep[u] < dep[v]) v = p[v];
    while(u != v) u = p[u], v = p[v];
    return u;
}

pair<int, int> tryToDel(int u, int v, int c) {
    int _lca = lca(u, v);
    pair<int, int> ret(0, 0);
    while(u != _lca) {
        int f = p[u];
        if(c == g[f][u]) {
            ret.first += g[f][u];
            ret.second++;
            g[f][u] = g[u][f] = 0;
        }
        u = f;
    }
    while(v != _lca) {
        int f = p[v];
        if(c == g[f][v]) {
            ret.first += g[f][v];
            ret.second++;
            g[f][v] = g[v][f] = 0;
        }
        v = f;
    }
    return ret;
}

int main() {
#ifdef LOCAL
    freopen("C:\\Users\\TaoSama\\Desktop\\in.txt", "r", stdin);
//  freopen("C:\\Users\\TaoSama\\Desktop\\out.txt","w",stdout);
#endif
    ios_base::sync_with_stdio(0);

    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1; i <= m; ++i) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            edge[i] = (Edge) {u, v, c};
        }
        int ans = kruskal(), cnt = n - 1;
        dfs(1, -1, 0);
        for(int i = 1; i <= m; ++i) {
            if(vis[i]) continue;
            Edge &e = edge[i];
            pair<int, int> tmp = tryToDel(e.u, e.v, e.c);
            ans -= tmp.first, cnt -= tmp.second;
        }
        printf("%d %d\n", cnt, ans);
    }
    return 0;
}
*/

/*
input
4 4
1 2 3
1 3 3
2 3 3
2 4 3

4 4
1 2 3
1 3 5
2 3 3
2 4 3

4 4
1 2 3
1 3 1
2 3 3
2 4 3

3 3
1 2 1
2 3 1
1 3 1

output
1 3
3 9
2 4
0 0
*/
