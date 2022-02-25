#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;
//ac 16ms
/*
����:һ���绰����,���ĳ���绰�����ֹ���,���˹������ڵ��޷�������,
�����ܵ�������һЩ�ط��޷�����,��ô��Щ�ط����ǹؼ�,
����Ҫ����绰�����������ؼ��ط�����Ŀ.
����:�������ͼ�и�����Ŀ.
����:http://poj.org/problem?id=1144
˼·:tarjan�������ͼ�����Ŀ.
*/

int n,dfn[N],low[N],num,cnt,head[N],id,rt,vis[N],ans;
struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v,son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            if(u == rt)
                son++;
            low[u]=min(low[u],low[v]);
            if(u != rt && dfn[u]<=low[v])
                vis[u]=1;
            else if(u == rt && son>=2)
                vis[u]=1;
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v;
    while(scanf("%d",&n) && n){
        ans=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(head,-1,sizeof head);
        memset(vis,0,sizeof vis);
        while(scanf("%d",&u) && u){
            while(getchar()!='\n'){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                rt=i;
                dfs(i,-1);
            }
        }
        for(int i=1;i<=n;i++){
            if(vis[i])
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
