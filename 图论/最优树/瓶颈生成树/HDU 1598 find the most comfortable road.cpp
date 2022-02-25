#include<cstdio>
#include<algorithm>
#define N 250
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;
//78ms
/*
题意:http://acm.hdu.edu.cn/showproblem.php?pid=1598
n个点,m条边的无向图,求从s到e的所有路径中最大边与最小边之差
的最小值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1598
注意:这个不能prim+dp,求取路径最小边权和最大边权,这个树上的差值不一定是最小的,
有可能不在树上的路径差值才是最小的.
思路:枚举每条边开始kruskal求最小树的过程,当s和e在一个集合时,
记录当前边权减开始边权的差值,取最小.但这个最小差值个别时候
不一定有意义,因为s到e的路径上的最小边权不一定会是初始边,
当最小边不是初始边时,这个时候差值是偏大的,而后续初始边从最小边开始时,
这个值会更新更小,所以暴力枚举总能保证最终的结果正确性.
*/

int n,m,q,fa[N],ans;

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(int st,int s,int e){
    init();
    int x,y;
    for(int i=st;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y)
            fa[y]=x;
        //这里还是有些问题的,就是初始枚举的最小边权不一定就在s到e的路径上,也就是这个差值个别时候它实际是偏大没有意义的
        //但是因为初始边权枚举所有边都会考虑,所以最终肯定有一次kruskal能求出最小差值,我们实际就是因为不知道什么时候s到e的
        //edge[i].w-edge[st].w是正确有意义的,才要暴力枚举所有边的
        if(find(s) == find(e)){
            ans=min(ans,edge[i].w-edge[st].w);
            break;
        }
    }
}

int main(){
    int s,e;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        sort(edge+1,edge+1+m);
        scanf("%d",&q);
        while(q--){
            scanf("%d%d",&s,&e);
            ans=INF;
            for(int i=1;i<=m;i++){
                kruskal(i,s,e);
                if(ans == INF){//ans == INF时代表后面的所有的连边都不能使得s和e连通,就没必要再枚举了
                    ans=-1;
                    break;
                }
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
