#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//ac 421ms
/*
题意:一个人从0点给其余1~n-1点传递信息,有m条单向传递关系
(满足传递性),如果a->b,b->c,那么就等同于a将信息传递给c,
每条传递关系都有一个代价w,如果两个人可以互相传达信息,
即在同一分支(同一强连通分量),那么它们传递信息不需要花费.
现在问这个人从0点要把信息传递给剩余所有人,最少的花费.
输入关系保证这个人一定能从0点将信息传递给所有人.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3072
思路:对于同一个传递环中的人相互传递信息不需要花费,可以
tarjan求解出scc之后缩点,记录缩点入边的最小边权,然后累加
每个缩点入边的最小边权即是答案.
有点类似在构造DAG上的最小树
*/
//ans[i] 代表到达i点入边的最小代价
int n,m,dfn[N],low[N],in[N],num,head[N],cnt,scc_cnt,block[N],ans[N];
stack<int> s;

struct Edge{
    int from,to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
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
        scc_cnt++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=scc_cnt;
        }while(v!=u);
    }
}

int main(){
    int u,v,w,sum;
    while(scanf("%d%d",&n,&m)!=EOF){
        sum=num=cnt=0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(ans,0x3f,sizeof(ans));
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])//有点类似在构造DAG上的最小树
                ans[block[v]]=min(ans[block[v]],edge[i].w);//记录缩点后到达该点入边的最小代价.
        }
        for(int i=1;i<=scc_cnt;i++){
            if(ans[i]!=INF)//0点所在的scc入度一定为0,ans一定是INF 不累加
                sum+=ans[i];
        }
        printf("%d\n",sum);
    }
    return 0;
}
