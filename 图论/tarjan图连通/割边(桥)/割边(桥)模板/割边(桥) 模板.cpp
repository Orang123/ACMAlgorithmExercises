#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20100
#define M 100100
using namespace std;
/*
相关概念:
割边:对于一个无向图,如果删掉一条边后图中的连通分量数增加了,则称这条边为桥或者割边.
无重边:只要满足dfn[u]<low[v],则是割边.
有重边:在满足上面条件下,自己与该儿子有多条边相连时,不是割边,因为删掉一条边还有边相连接,连通性不变.
现在讨论的割边都是在无重边的无向图中.对于有重边的情况需要一个记录两点间边数的二维数组来判定.

桥与割边的关系:
1.有割点不一定存在桥,有桥一定存在割点.有桥一定存在割点有点问题当只有2个点一条边相连时,有桥但没有割点.
2.对于桥的两端点,至少存在一个割点.
*/
struct node{
    int to,next;
    bool cut;
}edge[M<<1];//无向图有双向边 因此M*2
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int cutCnt;

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}
//O(E) E为边 此算法是建立在无重边的条件下
void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            /*
            去掉等号 因为当dfn[u]>=low[v]时,代表v不经过u-v这条边也能回到u及u之前结点,
            说明u-v不是割边(桥),反之dfn[u]<low[v],说明v不经过u-v这条边只能连通
            v及v结点之后的结点,无法连通u及u之前的结点,说明u-v是割边.
            dfn[u]>low[v]时,u不是回路所连接的前面的点,而是之后的点.
            dfn[u]==low[v]时,u本身就是回路所连接的前面的点.
            如果顶点u不能回到祖先也没有另外一条回到父亲的路，那么u-v这条边就是割边.
            */
            if(dfn[u]<low[v]){//对于有重边的情况还需判定edgeNum[u][v] == 1
                edge[i].cut=true;//将u-v v-u边都置为割边
                edge[i^1].cut=true;
                cutCnt++;//在无向图中的割边加1 不算反向边
            }
        }
        //u和u的父亲节点v之间的连边肯定是割边,因为没有重边,删掉这条边u和v一定不连通.无需更新low[u],直接默认dfn[v]<low[u]
        else if(v!=fa)//这里对于父亲节点这个if判定是不能省略的
            /*
            这里也可以是low[u]=min(low[u],low[v]),因为判断条件是dfn[u]<low[v],
            这样会使得low[u]更小,不影响结果,dfn[u]>=low[v]的情况都是不存在割边的.
            对于dfn[u]==low[v]仍然不是割边,因为即使断开u-v的连边还是存在v的后续连边
            有回到u点的连边.
            因为构成环的祖先节点和它直接相连的下一个节点的边本身就不是割边
            */
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int n,m,a,b;
    int len=M<<1;
    for(int i=0;i<len;i++)
        edge[i].cut=false;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&a,&b);
        addEdge(a,b);
        addEdge(b,a);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            dfs(i,-1);
        }
    }
    printf("%d\n",cutCnt);
    for(int i=1;i<=n;i++){
        for(int j=head[i];j!=-1;j=edge[j].next)
            if(edge[j].cut)//若是割边则输出其割边两端点 因为是无向图的缘故,实际输出的数量是cutCnt的2倍
                printf("%d %d\n",i,edge[j].to);
    }
    printf("\n");
    return 0;
}
/*
7 9
2 3
3 6
6 2
6 7
3 1
1 4
4 5
5 4
5 1
*/
