#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 5500
using namespace std;
//ac tarjan+scc缩点 94ms
/*
题意:给出一个有向图,定义:若节点v所有能到达的点{wi},都能反过来到达v,
那么称节点v是sink.题目要求所有的sink点.
链接:http://poj.org/problem?id=2553
思路:就是tarjan求解scc缩点后出度为0点.讲真,这题都是看样例知道要求什么的,
按它题意说的,中间的出入度都不为0的点不也满足条件吗.
*/

int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id,outde[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            tarjan(v);
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
    while(scanf("%d",&n) && n){
        clock=id=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(block,0,sizeof(block));
        memset(outde,0,sizeof(outde));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])
                outde[block[u]]++;
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(!outde[block[i]]){
                if(!flag){
                    printf("%d",i);
                    flag=1;
                }
                else
                    printf(" %d",i);
            }
        }
        printf("\n");
    }
    return 0;
}
