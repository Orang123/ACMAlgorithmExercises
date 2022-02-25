#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 20100
#define M 50100
using namespace std;
//ac 171ms
//同UVA12167 Proving Equivalences 是一道题
/*
题意:a->b,b->c,c->d,d->a,则说四条语句都是等价的,
现在给出一系列语句,求使得所有语句都等价最少还要添加
多少条语句.
释义:求使得有向图最少要添加多少条边才能变成SCG(强连通图).
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2767
思路:tarjan求解SCC,计算出入度为0点的个数,求取出度和入度为0
个数的最大值即是答案.
*/

int n,m,dfn[N],low[N],in[N],num,cnt,head[N],id,block[N],inde[N],outde[N];
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
    in[u]=1;
    s.push(u);
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
            block[v]=id;
        }while(v!=u);
    }
}

int main(){
    int T,u,v,ans1,ans2;
    scanf("%d",&T);
    while(T--){
        ans1=ans2=id=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(inde,0,sizeof inde);
        memset(outde,0,sizeof outde);
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
        if(id == 1){//本身就是SCG时需特判,因为inde outde不会增加,输出0
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
        for(int i=1;i<=id;i++){
            if(!inde[i]) ans1++;
            if(!outde[i]) ans2++;
        }
        printf("%d\n",max(ans1,ans2));
    }
    return 0;
}
