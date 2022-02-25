/*
题意:n个城市,m条路,一开始m个路是双向的,要修改成单向的,
问图里 可能的树有几个,即不构成环的连通图的个数.
其实就是求解连通无向图中一个环都没有的连通块(树)的个数.
链接:https://codeforces.ml/problemset/problem/659/E
思路:遍历一棵树.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
int n,m,head[N],cnt,vis[N],flag;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa) continue;
        if(vis[v]){//只要重复访问过且不是父节点则说明有环,但还不能结束,得把这个连通图所有点跑完做标记
            flag=1;
            continue;
        }
        dfs(v,u);
    }
}

int main(){
    int u,v,ans=0;
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        flag=0;
        if(!vis[i]){
            dfs(i,0);
            if(!flag)
                ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
