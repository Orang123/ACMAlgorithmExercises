//
//  Created by TaoSama on 2016-02-10
//  Copyright (c) 2016 TaoSama. All rights reserved.
//  https://blog.csdn.net/lwt36/article/details/50650236
// �ӱ߳ɻ�ȥ��������С������ ac 483ms
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
���ӱ߳ɻ��Ĺ����޷���prim,��Ϊprim����ĵ�Ͳ����������,
�ᵼ�²�����ɻ�·�ı��޷����,����ӱ߳ɻ���kruskal,·����
��С��Ȩ��prim����,���������������Ψһ,��ôminLen��¼����С��Ȩ
��kurskal����õ��������ǲ�һ�µ�,�������Ҳ���.
�о�prim�ڳ��Ӻ��ɳ��������� ͬʱ����vis�ɻ����ж�����,���Ǵ���̫ӷ����.
*/
/*
����:���һ��������������Ȩ����С��Ȩ֮�����Сֵ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5624
˼·:ģ��MST���ɵĹ���,����Kruskal�㷨����ȷ��
��С����ӱ�,���ĳ�����γɻ���,��ɾȥ���ϵ���С�߰������߶���ȥ
����MSTʱ�͸��´�,���������б߾���ans.
ʱ�临�Ӷ�ΪO(mlogm+nm)
*/

int n, m;
struct Edge {
    int u, v, c;
    bool operator<(const Edge& e) const {
        return c < e.c;//���� min ����
    }
    bool operator==(const Edge& e) const {//vector erase���� ���� ==
        return u == e.u && v == e.v && c == e.c;
    }
} edge[15005];

Edge minEdge;
vector<Edge> G[2005];
//dfs�ҵ�����u��t·���ϵ���̱�Ȩ
bool dfs(int u, int fa, int t, multiset<int>& s) {
    if(u == t) return true;//������t�յ�ʱ,��ʼ����
    for(Edge& e : G[u]) {
        int v = e.v;
        if(v == fa) continue;
        if(dfs(v, u, t, s)) {//�����յ�t�� ��¼u��t��·���ϵ���С��Ȩ
            minEdge = min(minEdge, e);
            return true;
        }
    }
    return false;
}
//ɾ�� s�� G �ɻ���·���ϵ���̱�Ȩ
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
        multiset��<set>����һ���ǳ����õ����ͣ������Կ���һ�����У�
        ����һ������ɾ��һ�������ܹ���O(logn)��ʱ������ɣ���������ʱ�̱�֤�����е���������ģ�
        ���������п��Դ����ظ�����.�����ȶ���priority_queue��ͬ���� multiset֧��ɾ���Լ�����Ԫ�صĲ���
        */
        multiset<int> s;
        for(int i = 1; i <= n; ++i) {
            p[i] = i;
            G[i].clear();
        }

        int ans = 2e9, cnt = 0;
        /*
        ����֮�����ڻ�û�γ�mst(��������n-1)���ֻ���ʱ����ڻ���ɾ��С��,
        ����Ϊ���ֻ�����γ�mst�ﵽn-1���ߺ�,�ӱ��γɵĻ���ɾ����С��,
        ���ɾ������С���п���ɾ����������mst�￿��ǰ�� ��Ȩ��С��
        ��Щ��,������С�ı�û��ɾ��,����һֱ����,�ᵼ�²�ֵ��Ȼ�ڲ�������,
        ���ڻ�û�γ�mstʱ,�ɻ���ɾ��,�����ں����ʱ��Ȩֵ��С�ı�ɾ��,����
        ���ż���ı�Ȩ����,������С�ı�ȨҲ�ڲ���ɾ����СֵҲ������,��Ȩ���½���Ͻ����ͬʱ����,
        ������ֵ���ܾ����ܵ�С.
        */
        for(int i = 1; i <= m; ++i) {
            int u = edge[i].u, v = edge[i].v, c = edge[i].c;
            if(unite(u, v)) ++cnt;
            else {//���ڵ�ǰ�߼���ɻ������,���ǽ�ԭ�Ȼ���·������̱�Ȩȥ��,���ı����,������ʹ��ans��С
                minEdge.c = 2e9;
                dfs(u, -1, v, s);//�ҵ���u->v��·���ϵ���̱�Ȩ
                del(s);//s��G��ɾ������С��Ȩ
            }
            s.insert(c);//���뵱ǰ��
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
//  ��������ö����С����ʵλ����m��kruskal ac 3790ms
//������ݷ�ΧС�Ļ�,������m��Kruskal,��д,ʱ�临�Ӷ�ΪO(mlogm+m2)
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
