#include<cstdio>
#include<functional>
#include<algorithm>
#define N 100100
#define M 100100
using namespace std;
//93ms
/*
题意:给你一个连通的有权无向图，图中不包含有自环和重边，
你的任务就是寻找出有多少条边，它至少在一个最小生成树里。图保证连通。
链接:http://acm.fzu.edu.cn/problem.php?pid=2087
思路:kruskal,将相同权值的边分为一类,按照并查集判别条件如果不在同一个连通集,
那么个数+1,因为对于此时加边加任一条都是可以的,但是在不断加边的过程中,会导致
后面的边加不进去会成环,我们只需要记录有多少条边是能作为mst的边加入的因为在
还未成环时选择哪一条都是可以的,然后再正常将这些权值相同的边的fa[N]数组合并.
*/

int n,m,fa[N],sum;

struct Edge{
    int u,v,w;
    bool operator <(const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    sum=0;
    sort(edge+1,edge+1+m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        init();
        int x,y,cnt=0;
        for(int i=1,j;i<=m;i=j){//i=j,从权值不相等的边开始
            for(j=i;edge[j].w==edge[i].w;j++){//j=i先判断本身i这条边能否作为mst的边,再判断后面和i权值相等的边
                x=find(edge[j].u);
                y=find(edge[j].v);
                /*
                对于权值相同的边先不合并,先计数,这里若相等 加哪一个边都是可以的,但是可能后续合并时,
                会出现环,但是在还没成环加边时这些权值相等的边任意一条都是能作为mst的边的.
                */
                if(x!=y)
                    sum++;
            }
            for(j=i;edge[j].w==edge[i].w;j++){//之后在正常合并为一个连通集
                x=find(edge[j].u);
                y=find(edge[j].v);
                if(x!=y){
                    fa[x]=y;
                    cnt++;
                }
            }
            if(cnt == n-1) break;//构成一棵树时 结束
        }
        printf("%d\n",sum);
    }
    return 0;
}
