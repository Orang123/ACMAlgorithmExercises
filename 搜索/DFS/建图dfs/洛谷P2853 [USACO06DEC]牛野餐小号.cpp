/*
题意:奶牛们正在野餐！Farmer John 的每头 K (1 ≤ K ≤ 100) 头奶牛都在 N (1 ≤ N ≤ 1,000)
个牧场之一放牧，方便地编号为 1...N。牧场由 M (1 ≤ M ≤ 10,000) 条单向路径连接
（没有路径将牧场与其自身相连）。奶牛们想聚集在同一个牧场上野餐，但是（因为是单向路径）
有些奶牛可能只能到达一些牧场。通过计算所有奶牛可以到达多少牧场来帮助奶牛，因此是可能的野餐地点。
K(1≤K≤100)只奶牛分散在N(1≤N≤1000)个牧场．现在她们要集中起来进餐．牧场之间有M(1≤M≤10000)条有向路连接，
而且不存在起点和终点相同的有向路．她们进餐的地点必须是所有奶牛都可到达的地方．那么，有多少这样的牧场呢？
链接:https://www.luogu.com.cn/problem/P2853
思路:最先开始想到,可以枚举每个点,dfs反向遍历是否能遍历到所有奶牛所在农场,
但所有点有1000个,边集10^4,复杂度太大,会TLE.
其实可以从每个奶牛所在农场开始dfs正向遍历,如果最终每个农场被遍历的次数达到了k次(奶牛个数),
则说明这个农场所有奶牛都能到达.
注意要用vis标记遍历过的点,否则会重复标记,使得结果出错.
列如这样一组数据:1->2->3,1->4->3 如果不做vis标记,3这个点就会被记录两次.
*/
#include<cstdio>
#include<cmath>
#include<cstring>
#define N 1010
#define M 10100

int k,n,m,head[N],cnt,a[110],num[N],vis[N],ans;
struct Node{
    int to,next;
}edge[M];


void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    vis[u]=1;
    num[u]++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v])
            dfs(v);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&k,&n,&m);
    for(int i=1;i<=k;i++)
        scanf("%d",&a[i]);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=k;i++){
        memset(vis,0,sizeof(vis));
        dfs(a[i]);
    }
    for(int i=1;i<=n;i++)
        if(num[i]==k)
            ans++;
    printf("%d\n",ans);
    return 0;
}
