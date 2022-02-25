#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
using namespace std;
//ac 47ms
/*
题意:n头牛,m条关系,如果A认为B受欢迎,B认为C受欢迎,
那么牛A也认为牛C受欢迎,即:A->B->C,现在要求出有多少头牛被所以牛认可.
释义:就是问有向图中,有多少个点可由其余所有点到达这个点.
链接:http://poj.org/problem?id=2186
思路:N<=10111,暴力解法,考虑从每个点开始遍历所有点,最后判断每个点被到达的次数,
如果达到n-1,说明该点能从其余所有点到达,但O(N^2),显然TLE.如果考虑floyd处理传递闭包,
O(N^3)时间复杂度,O(N^2)空间复杂度,TLE,MLE.
可以考虑tarjan求解强连通分量(SCC)后缩点转换成有向无环图(DAG).
性质:在DAG中如果有且仅由一个点的出度为0时,则其余所有点都可达该点(可以画图理解).
那么缩点后统计SCC的出度,如果出度为0的点恰有一个,则输出该SCC中点的个数,否则因为
出度为0的点大于1,则必然至少有一个点不可达该点,则说明没有一个点可从其它点到达该点.
*/

int n,m,dfn[N],low[N],in[N],num,cnt,head[N],id,block[N],outde[N],amout[N];
stack<int> s;
struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
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
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            amout[id]++;
            block[v]=id;
        }while(v!=u);
    }
}

int main(){
    int u,v,ans=0;
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u] != block[v])
            outde[block[u]]++;//统计出度
    }
    int k;
    for(int i=1;i<=id;i++){
        if(!outde[i]){
            ans++;//记录出度为0的点的个数
            k=i;
        }
    }
    if(ans == 1) printf("%d",amout[k]);
    else printf("0");
    return 0;
}
