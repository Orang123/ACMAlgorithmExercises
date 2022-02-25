#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 20100
#define M 50010
using namespace std;
//ac 156ms
/*
题意:n个集合,A->B,代表集合A是集合B的子集,反过来如果能证明B->A,
那么集合B也是集合A的子集,那么就说集合A和B是等价的,现在有m条这样的关系,
请求出证明n个集合相互等价最少还需要证明几条关系.
释义:将有向图转化为强连通图最少要加的边数
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3836
思路:tarjan求解scc缩点后,入度为0的点和出度为0点的最大值,
对于原图本身就是强连通图,要特判输出0.
*/

int n,m,dfn[N],low[N],clock,cnt,block[N],id,head[N],inde[N],outde[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(outde,0,sizeof(outde));
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        if(id == 1){
            printf("0\n");
            continue;
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                inde[block[v]]++;
                outde[block[u]]++;
            }
        }
        int ans1=0,ans2=0;
        for(int i=1;i<=id;i++){
            if(!inde[i]) ans1++;
            if(!outde[i]) ans2++;
        }
        printf("%d\n",max(ans1,ans2));
    }
    return 0;
}
