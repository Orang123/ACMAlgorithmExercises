//
//  Created by TaoSama on 2016-02-10
//  Copyright (c) 2016 TaoSama. All rights reserved.
//  https://blog.csdn.net/lwt36/article/details/50650236
// 加边成环去除环中最小边做法 ac 483ms
//
#pragma comment(linker, "/STACK:1024000000,1024000000")
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
const int N = 1e5 + 10, INF = 0x3f3f3f3f, MOD = 1e9 + 7;
/*
求解加边成环的过程无法用prim,因为prim加入的点就不可再入队了,
会导致部分造成回路的边无法入队,如果加边成环用kruskal,路径上
最小边权用prim来做,这样如果生成树不唯一,那么minLen记录的最小边权
和kurskal中求得的树可能是不一致的,这样结果也会错.
感觉prim在出队和松弛条件那里 同时加上vis成环的判定可行,但是代码太臃肿了.
*/
/*
题意:求解一棵生成树中最大边权与最小边权之差的最小值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5624
思路:模拟MST生成的过程,根据Kruskal算法的正确性
从小往大加边,如果某条边形成环了,就删去环上的最小边把这条边丢进去
生成MST时就更新答案,尝试完所有边就是ans.
时间复杂度为O(mlogm+nm)
*/

int n, m;
struct Edge {
    int u, v, c;
    bool operator<(const Edge& e) const {
        return c < e.c;//排序 min 重载
    }
    bool operator==(const Edge& e) const {//vector erase操作 重载 ==
        return u == e.u && v == e.v && c == e.c;
    }
} edge[15005];

Edge minEdge;
vector<Edge> G[2005];
//dfs找到树上u到t路径上的最短边权
bool dfs(int u, int fa, int t, multiset<int>& s) {
    if(u == t) return true;//当到达t终点时,开始返回
    for(Edge& e : G[u]) {
        int v = e.v;
        if(v == fa) continue;
        if(dfs(v, u, t, s)) {//到达终点t后 记录u到t点路径上的最小边权
            minEdge = min(minEdge, e);
            return true;
        }
    }
    return false;
}
//删除 s和 G 成环的路径上的最短边权
void del(multiset<int>& s) {
    int u = minEdge.u, v = minEdge.v, c = minEdge.c;
    s.erase(s.find(c));
    G[u].erase(find(G[u].begin(), G[u].end(), minEdge));
    swap(minEdge.u, minEdge.v);
    G[v].erase(find(G[v].begin(), G[v].end(), minEdge));
}

int p[2005];
int find(int x) {
    return p[x] = p[x] == x ? x : find(p[x]);
}

bool unite(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return false;
    p[u] = v;
    return true;
}

int main() {
#ifdef LOCAL
    freopen("C:\\Users\\TaoSama\\Desktop\\in.txt", "r", stdin);
//  freopen("C:\\Users\\TaoSama\\Desktop\\out.txt","w",stdout);
#endif
    ios_base::sync_with_stdio(0);

    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; ++i) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            edge[i] = (Edge) {u, v, c};
        }
        sort(edge + 1, edge + 1 + m);
        /*
        multiset是<set>库中一个非常有用的类型，它可以看成一个序列，
        插入一个数，删除一个数都能够在O(logn)的时间内完成，而且他能时刻保证序列中的数是有序的，
        而且序列中可以存在重复的数.和优先队列priority_queue不同的是 multiset支持删除以及查找元素的操作
        */
        multiset<int> s;
        for(int i = 1; i <= n; ++i) {
            p[i] = i;
            G[i].clear();
        }

        int ans = 2e9, cnt = 0;
        /*
        这里之所以在还没形成mst(边数不够n-1)出现环的时候就在环里删最小边,
        是因为如果只是在形成mst达到n-1条边后,加边形成的环里删除最小边,
        这个删除的最小边有可能删除不到整个mst里靠近前列 边权最小的
        那些边,这样最小的边没被删除,最大边一直增大,会导致差值仍然在不断增大,
        而在还没形成mst时,成环就删边,就能在很早的时候将权值较小的边删除,这样
        随着加入的边权增大,树中最小的边权也在不断删除最小值也在增大,边权的下界和上界就能同时增加,
        这样差值就能尽可能地小.
        */
        for(int i = 1; i <= m; ++i) {
            int u = edge[i].u, v = edge[i].v, c = edge[i].c;
            if(unite(u, v)) ++cnt;
            else {//对于当前边加入成环的情况,考虑将原先换上路径里最短边权去掉,将改变加入,这样会使得ans更小
                minEdge.c = 2e9;
                dfs(u, -1, v, s);//找到那u->v上路径上的最短边权
                del(s);//s和G中删除该最小边权
            }
            s.insert(c);//加入当前边
            G[u].push_back((Edge) {u, v, c});
            G[v].push_back((Edge) {v, u, c});
            if(cnt == n - 1) ans = min(ans, c - *s.begin());
        }
        if(ans == 2e9) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}

/*
//
//  Created by TaoSama on 2016-02-06
//  Copyright (c) 2016 TaoSama. All rights reserved.
//  暴力做法枚举最小边其实位置跑m次kruskal ac 3790ms
//如果数据范围小的话,可以跑m遍Kruskal,易写,时间复杂度为O(mlogm+m2)
#pragma comment(linker, "/STACK:1024000000,1024000000")
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
const int N = 1e5 + 10, INF = 0x3f3f3f3f, MOD = 1e9 + 7;

int n, m;
struct Edge {
    int u, v, c;
    void read() {scanf("%d%d%d", &u, &v, &c);}
    bool operator<(const Edge& e) const {
        return c < e.c;
    }
} edge[N];

int p[N];
int find(int x) {
    return p[x] = p[x] == x ? x : find(p[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return false;
    p[x] = y;
    return true;
}

int kruskal(int i) {
    if(m - i + 1 < n - 1) return 0x7fffffff;
    int ret = -edge[i].c, cnt = 0, maxv = 0;
    for(int j = 1; j <= n; ++j) p[j] = j;
    for(int j = i; j <= m; ++j) {
        int u = edge[j].u, v = edge[j].v;
        cnt += unite(u, v);
        if(cnt == n - 1) {
            ret += edge[j].c;
            break;
        }
    }
    if(cnt != n - 1) return 0x7fffffff;
    return ret;
}

int main() {
#ifdef LOCAL
    freopen("C:\\Users\\TaoSama\\Desktop\\in.txt", "r", stdin);
//  freopen("C:\\Users\\TaoSama\\Desktop\\out.txt","w",stdout);
#endif
    ios_base::sync_with_stdio(0);

    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; ++i) edge[i].read();
        sort(edge + 1, edge + 1 + m);
        int ans = 0x7fffffff;
        for(int i = 1; i <= m; ++i) {
            ans = min(ans, kruskal(i));
        }
        if(ans == 0x7fffffff) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
*/
