#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 150
using namespace std;

/*
题意:一个有向图,求:
1)至少要选几个顶点,才能做到从这些顶点出发,可以到达全部顶点.
2)至少要加多少条边,才能使得从任何一个顶点出发,都能到达全部顶点,即成为一个强连通图.
链接:http://poj.org/problem?id=1236
思路:第一问就是tarjan缩点后,入度为0的点的个数,
第二问是入度为0的个数incnt和出度为0的个数outcnt的最大值.
要为每个入度为0的点添加入边,为每个出度为0的点添加出边,
在填补出度为0的点时,会同时填补入度为0的点,但较大者仍然还有剩余此时图仍旧不连通,
因此取出度、入度最大值即可,这个画图直观理解就行.
一个SCG(强连通图)中的所有点的出入度都是不为0的,因此使得DAG成为SCG需要加边的
最小条数就为出度和入度为0的点的最大值.
*/

struct node{
    int to,next;
}edge[N*(N-1)];

int head[N],cnt;
int dfn[N];
int low[N];
int num;
stack<int> s;
bool in[N];
int block[N],id,inde[N],outde[N];

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=true;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++id;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            s.pop();
        }while(v != u);
    }
}

int main(){
    int n,a[N];
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=0;;j++){
            scanf("%d",&a[j]);
            if(a[j] == 0) break;//输入为0 i连向的边结束.
            addEdge(i,a[j]);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    for(int i=1;i<=n;i++){//遍历各个点统计SCC 缩点的出度、入度
        for(int j=head[i];j!=-1;j=edge[j].next){
            if(block[i]!=block[edge[j].to]){//两个结点对应的强连通分量编号不同,则可认为是两个缩点之间有连接
                inde[block[edge[j].to]]++;//统计入度
                outde[block[i]]++;//统计i的出度 ++  这里不需要真正地重新建图
            }
        }
    }
    int incnt=0,outcnt=0;
    for(int i=1;i<=id;i++){
        if(!inde[i]) incnt++;//统计缩点后 入度为0和出度为0的点的个数
        if(!outde[i]) outcnt++;
    }
    if(id == 1){//这里不能判断incnt == 1 && outcnt == 1 因为对于o->o而言 有两个SCC,但其入度为0和出度为0的点也都各有1个
        printf("1\n");//只有一个SCC的时候 无需添加边,本身就是SCS
        printf("0\n");
    }
    else{
        printf("%d\n",incnt);
        printf("%d\n",max(incnt,outcnt));
    }
    return 0;
}
