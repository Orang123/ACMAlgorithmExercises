#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 5500
using namespace std;
//ac tarjan+scc���� 94ms
/*
����:����һ������ͼ,����:���ڵ�v�����ܵ���ĵ�{wi},���ܷ���������v,
��ô�ƽڵ�v��sink.��ĿҪ�����е�sink��.
����:http://poj.org/problem?id=2553
˼·:����tarjan���scc��������Ϊ0��.����,���ⶼ�ǿ�����֪��Ҫ��ʲô��,
��������˵��,�м�ĳ���ȶ���Ϊ0�ĵ㲻Ҳ����������.
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
