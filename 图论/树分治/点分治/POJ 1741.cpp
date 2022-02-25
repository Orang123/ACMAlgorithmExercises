#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#define MAXN 10005
using namespace std;
struct Edge {
    int v, l;//v表示连接到的下一个节点，l表示长度
    Edge(int v_, int l_) :v(v_), l(l_) {};
};
vector<Edge> g[MAXN];//用变长数组存储图
vector<int> dep;    //用来计算在某图下，以某个节点作为根节点时的各子节点的deep，它不需要知道具体是哪个子节点
int dist[MAXN];     //
int n, k;
int vis[MAXN];
int f[MAXN];//存储在当前图下,以某个节点作为根节点时，得到的最大子树的大小
int root;   //当前找到的根节点
int ans;    //最后要求的配对数目
int s[MAXN];//s for size，记录在当前图下每个节点的子树大小之和，包括自己
int totalNodes;//n-删除的点的个数
void getroot(int now, int fa) {
    int u;
    //s的存在是为了累加，然后得出父节点等所有祖先构成子树的大小
    s[now] = 1;//自己
    f[now] = 0;//存储每个节点的最大子树
    for (int i = 0; i < g[now].size(); i++) {//不会陷入死循环的原因之一：树上存在叶节点（只与父节点相连）
        u = g[now][i].v;//子节点
        if (u != fa && !vis[u]) {//不是父节点且未被切除，如果不排除父节点会陷入死循环
            getroot(u, now);//递归地找到子树的最大子树和子树的大小
            s[now] += s[u]; //加入子树的大小
            f[now] = max(f[now], s[u]);//找最大子树
        }
    }
    f[now] = max(f[now], totalNodes - s[now]);//把父节点等所有祖先当作一棵子树
    if (f[now] < f[root]) root = now;//找最大子树最小的根节点
}
void getdep(int now, int fa) {//在某个图某个根节点下求deep，天然的深度是dist[now]
    int u;
    dep.push_back(dist[now]);
    s[now] = 1;
    for (int i = 0; i < g[now].size(); i++) {
        u = g[now][i].v;
        if (u != fa && !vis[u]) {
            dist[u] = dist[now] + g[now][i].l;
            getdep(u, now);
            s[now] += s[u];
        }
    }
}
int calc(int now, int len) {//在减去属于同一棵子树的时候,len是这个子树到原根节点的距离
                            //我们把这个距离考虑进来，
    dep.clear();
    dist[now] = len;//以dist[now]作为基础求deep
    getdep(now, 0);//在当前图当前根节点下，计算每个子节点的deep,放入dep数组
    sort(dep.begin(), dep.end());
    int cnt = 0;//统计数目
    int l = 0, r = dep.size() - 1;
    /*
    用l表示左指针，r表示右指针，i从左向右遍历。
    如果dep[i]+dep[j]≤k，则点对(i,t)(i<t≤j)都符合题意，将r-l加入答案中，并且l++；否则r--。
    */
    while (l < r) {
        if (dep[l] + dep[r] <= k) {
            cnt += r - l;
            l++;
        }
        else r--;
    }
    return cnt;
}
void work(int now) {//以now作为根节点，在当前的图下计算满足题意的pair个数
    int u;
    ans += calc(now, 0);//以now作为根节点，在当前的图下所有deep[i]+deep[j]<=k的(i,j)的数目
                        //然后减去属于同一棵子树的(i,j)，于是得到了经过根节点的所有(i,j)路径
    vis[now] = true;//剪掉根节点，得到不连通的几棵子树
    for (int i = 0; i < g[now].size(); i++) {
        u = g[now][i].v;
        if (!vis[u]) {
            ans -= calc(u, g[now][i].l);//减去属于同一棵子树的(i,j)
            f[0] = totalNodes = s[u];//考虑连通的某棵子树，其总的大小
            root = 0;
            getroot(u, 0);//找到新的根节点
            work(root);//递归地增加不经过当前根节点，但是经过新的根节点的路径数目
        }
    }
}
int main() {
    while (cin >> n >> k) {
        if (!n && !k) break;
        for (int i = 0; i <= n; i++)
            g[i].clear();
        memset(vis, 0, sizeof(vis));
        int u, v, l;
        for (int i = 1; i < n; i++) {//读入n-1条边
            cin >> u >> v >> l;
            g[u].push_back(Edge(v, l));
            g[v].push_back(Edge(u, l));
        }
        f[0] = n;
        root = 0;
        totalNodes = n;
        getroot(1, 0);
        ans = 0;
        work(root);
        cout << ans << endl;
    }
}