#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

/*
����:һ��n���ڵ����,ÿ���ڵ�����һЩ��,ÿ���ڵ�֮���о���w,����Ҫȷ���ĸ��ڵ�
��Ϊ������,ʹ�������ڵ��������ǰ���μӱ������ߵľ����ܺ���С.�����С�ľ����ܺ�.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3899
˼·:����dp,��51 nod 1405 ���ľ���֮��˼·һ��,ֻ������ÿ���ڵ㺬��һ������,Ҫ�������������ߵľ���.
�����ɸ��ڵ�u���ӽڵ�vת��,�ֳ�v֮���v֮ǰ��������dp[u]�Ļ����϶��߻�����wȥ����.
*/

int cnt,n,head[N];
ll siz[N],sum,dp[N],ans;//���ݿ����ֹ���

struct Node{
    int to,next;
    ll w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs1(int u,int fa,int w){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dp[1]+=siz[v]*(w+edge[i].w);
        dfs1(v,u,w+edge[i].w);
        siz[u]+=siz[v];
    }
}

void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dp[v]=dp[u]-siz[v]*edge[i].w+(sum-siz[v])*edge[i].w;
        ans=min(ans,dp[v]);
        dfs2(v,u);
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=sum=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++){
            scanf("%d",&siz[i]);
            sum+=siz[i];
        }
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        dp[1]=0;
        dfs1(1,-1,0);
        ans=dp[1];
        dfs2(1,-1);
        printf("%lld\n",ans);
    }
    return 0;
}

/*
BFS�汾 https://blog.csdn.net/racebug2010/article/details/6653090
#include <stdio.h>
#include <memory.h>

const int maxn = 100005;

struct Graph {
    int hed[maxn], nxt[maxn*2], pnt[maxn*2], val[maxn*2];
    int idx;

    void init(int n) {
        memset(hed + 1, -1, n * 4);
        idx = 0;
    }
    void addedge(int x, int y, int v) {
        pnt[idx] = y; val[idx] = v; nxt[idx] = hed[x]; hed[x] = idx++;
        pnt[idx] = x; val[idx] = v; nxt[idx] = hed[y]; hed[y] = idx++;
    }
} gra;

struct Node {
    int r, x, p;
} sta[maxn];

int teams[maxn], total;
__int64 cunt[maxn], cost[maxn];

void dfs_1() {
    int x, y, r, p, top = 0;
    sta[0].x = 1; sta[0].r = 0; sta[0].p = gra.hed[1];
    cunt[1] = teams[1];
    cost[1] = 0;

    while (true) {
        p = sta[top].p;
        if (p == -1) {
            top--;
            if (top >= 0) {
                p = sta[top].p;
                x = sta[top].x;
                y = gra.pnt[p];

                cunt[x] += cunt[y];
                cost[x] += cunt[y] * gra.val[p] + cost[y];

                sta[top].p = gra.nxt[p];
            } else {
                break;
            }
        } else {
            x = sta[top].x;
            r = sta[top].r;
            y = gra.pnt[p];
            if (y != r) {
                ++top;
                cunt[y] = teams[y];
                cost[y] = 0;
                sta[top].r = x;
                sta[top].x = y;
                sta[top].p = gra.hed[y];
            } else {
                sta[top].p = gra.nxt[p];
            }
        }
    }
}

void dfs_2() {
    int x, y, r, p, top = 0;
    sta[0].x = 1; sta[0].r = 0; sta[0].p = gra.hed[1];

    while (true) {
        p = sta[top].p;
        if (p == -1) {
            top--;
            if (top >= 0) {
                p = sta[top].p;
                sta[top].p = gra.nxt[p];
            } else {
                break;
            }
        } else {
            x = sta[top].x;
            r = sta[top].r;
            y = gra.pnt[p];
            if (y != r) {
                ++top;
                cost[y] = cost[x] + (total - 2 * cunt[y]) * gra.val[p];
                sta[top].r = x;
                sta[top].x = y;
                sta[top].p = gra.hed[y];
            } else {
                sta[top].p = gra.nxt[p];
            }
        }
    }
}

int main() {
    int n, x, y, v;

    while (scanf("%d", &n) != EOF) {
        total = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", teams + i);
            total += teams[i];
        }
        gra.init(n);
        for (int i = 1; i < n; i++) {
            scanf("%d %d %d", &x, &y, &v);
            gra.addedge(x, y, v);
        }
        dfs_1();
        dfs_2();

        __int64 ans = cost[1];
        for (int i = 2; i <= n; i++) {
            if (cost[i] < ans)
                ans = cost[i];
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
*/
