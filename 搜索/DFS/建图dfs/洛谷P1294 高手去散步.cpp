/*
题意:n个点m条边的无向图,求出最长路.
n<=20,m<=50.
链接:https://www.luogu.com.cn/problem/P1294
思路:枚举每个点dfs.
*/
#include<cstdio>
#include<cstring>
#include<cstring>
using namespace std;
int n,m,cnt,vis[30],sum,head[30],ans;
struct Node{
    int to,next,w;
}edge[110];

void addEdge(int u,int v,int w){
    edge[cnt]=(Node){v,head[u],w};
    head[u]=cnt++;
}

void dfs(int u,int sum){
    if(sum>ans) ans=sum;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        dfs(v,sum+edge[i].w);
    }
    vis[u]=0;
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    for(int i=1;i<=n;i++)
        dfs(i,0);
    printf("%d\n",ans);
    return 0;
}
