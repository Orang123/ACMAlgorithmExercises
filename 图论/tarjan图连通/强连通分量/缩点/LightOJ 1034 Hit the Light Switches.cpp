#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
//ac 89ms
/*
题意:n个路灯,m条相邻关系,如果有关系路灯a->路灯b,则说明打开
路灯a就会使得相邻的路灯b的开关触发同时点亮,但打开b不能触发a.
现在问最少需要打开几个路灯即可触发所有路灯都被打开.
链接:http://lightoj.com/volume_showproblem.php?problem=1034
思路:tarjan求解scc缩点,求解入度为0的点即可.
*/

int n,m,dfn[N],low[N],clock,cnt,block[N],id,head[N],inde[N];
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
    int T,u,v,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
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
            if(block[u]!=block[v])
                inde[block[v]]++;
        }
        int ans=0;
        for(int i=1;i<=id;i++){
            if(!inde[i])
                ans++;
        }
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}
