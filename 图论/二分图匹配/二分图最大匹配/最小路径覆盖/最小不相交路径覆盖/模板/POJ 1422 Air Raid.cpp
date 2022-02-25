#include<cstdio>
#include<cstring>
#include<vector>
#define N 150
using namespace std;
//ac 0ms 最小不相交路径覆盖
//参考博客: https://blog.csdn.net/qq_39627843/article/details/82012572
/*
相关概念:
1   5
 \ /
  3
 / \
2   4
eg:图G:1->3,2->3,3->4,3->5(在草稿纸中注意是有向边)
定义:在一个有向图中,找出最少的路径,使得这些路径经过了所有的点.
最小路径覆盖分为最小不相交路径覆盖和最小可相交路径覆盖.
最小不相交路径覆盖:每一条路径经过的顶点各不相同.图G总,最小不相交路径覆盖数为3.即1->3->4,2,5或1->3->5,2,4.
最小可相交路径覆盖:每一条路径经过的顶点可以相同.图G其最小相交路径覆盖数为2.即1->3->4,2->3>5或1->3->5,2->3->4.
特别的,每个点自己也可以称为是路径覆盖,只不过路径的长度是0.
注意:无论是否相交这个问题不可简单转化为入度为0的点个数,因为DAG上会有分支,
对于分支路径因为不能相交还需单独计算.也无法同拓扑排序去做.

性质定理:
注意:这个定理的前提一定原图为DAG,原图为无向图或有环都会导致结果计算错误.
DAG上的最小路径覆盖(不相交)=顶点数(初始化的所有顶点数)-最大匹配
最小可相交路径覆盖=最不可相交路径覆盖(folyd处理原图传递闭包后)=顶点数-最大匹配
证明:
一开始每个点都是独立的为一条路径,总共有n条不相交路径.我们每次在二分图里
找一条匹配边就相当于把两条路径合成了一条路径,也就相当于路径数减少了1.
所以找到了几条匹配边,路径数就减少了多少.所以DAG最小路径覆盖=顶点数-最大匹配.
*/

/*
题意:一个有向无环图,现在要在每个点放置伞兵,每个点的伞兵可以沿着有向边
到达其余点(直到不能走,没有边连接时),并且每个点被一个伞兵访问过后,
其余伞兵便不可再访问,即所有路径中每条边只能由一个伞兵走,
现在问最少要在点放置多少伞兵可保证所有点都被访问.
链接:http://poj.org/problem?id=1422
思路:DAG上的最小路径覆盖,注意每个点只可被伞兵访问一次,即:最小不相交路径覆盖.
DAG的最小不相交路径覆盖=顶点数-最大匹配数.DAG中的最大匹配数并不需要每个点拆点
成Vx,Vy.直接枚举所有点跑匈牙利算法即可,当然直接求最大匹配(虽然有公共点)和但和
真实拆点对于V1到V2的有向边建立V1x->V2y的有向边,即只考虑从Vx集合出发的点跑
匈牙利搜索增广路结果是一样的.
*/
int n,m,cnt,head[N],vis[N],link[N],ans;
struct Edge{
    int to,next;
}edge[N*N];

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
    ans=cnt=0;
    memset(head,-1,sizeof(head));
    memset(link,0,sizeof(link));
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){//考虑DAG上所有点出发搜索增广路
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans);//最小路径覆盖=顶点数-最大匹配
    }
    return 0;
}
