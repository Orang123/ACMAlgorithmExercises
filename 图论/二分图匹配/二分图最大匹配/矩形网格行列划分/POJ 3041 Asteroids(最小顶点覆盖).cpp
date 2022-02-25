#include<cstdio>
#include<cstring>
#define N 510
#define M 10100
//ac 32ms 最小点覆盖
//同HDU 2119 ac 46ms 记录在杭电上
/*
相关概念:
点覆盖:
图G的顶点覆盖是一个顶点集合V,使得G中的每一条边都接触V中的至少一个顶点.
我们称集合V覆盖了G的边.最小顶点覆盖是用最少的顶点来覆盖所有的边.
通俗的讲:
假如选了一个点就相当于覆盖了以它为端点的所有边.最小顶点覆盖就是选择最少的点来覆盖所有的边.
最小点覆盖就是用最少点去覆盖所有边;最小边覆盖就是用最少边去覆盖所有点.

性质定理:
在二分图中:最小顶点覆盖=最大匹配数

*/

/*
题意:n*n的矩形网格里包含m个行星,每个行星对应唯一的一组行列号,
现在你有一个武器,每次可以清除矩形网格中任意一行或一列上的
所有行星,现在问最少需要使用几次武器可以清除所有行星.
链接:http://poj.org/problem?id=3041
思路:每个行星对应唯一一组行列号,可以将所有的行号作为左集合,
所有的列号作为右集合,这样任意一组行星就表示为行号和列号间的
连边.而每次使用武器清除一行可以看做是选择左集合中的某点u,
将u点连接右集合所有点v的边全部删掉;每次使用武器清除一列可以看做是
选择右集合中的某点v,将v点连接左集合所有点u的边全部删掉;所以问题
就转化为在行列构成的二分图中选取尽可能少的点集,使其覆盖到二分图中
所有的边,这样只要删除这些点邻接的所有边就相当于清除这个点对应的行或列中的所有行星,
而这个最少的点集就是最小顶点覆盖,最小顶点覆盖=最大匹配数.
*/
int n,m,cnt,head[N],vis[N],link[N],ans;
struct Edge{
    int to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(head,-1,sizeof(head));
    memset(link,0,sizeof(link));
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);//只建立行到列的有向边
    }
    for(int i=1;i<=n;i++){//只考虑左集合中的所有行号 出发计算最大匹配 结果无需除2
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }
    printf("%d\n",ans);
    return 0;
}
