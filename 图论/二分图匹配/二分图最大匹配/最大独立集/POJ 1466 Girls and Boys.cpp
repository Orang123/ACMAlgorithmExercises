#include<cstdio>
#include<cstring>
#include<vector>
#define N 550
using namespace std;
//ac 500ms 最大独立集
/*
题意:有n个学生,不同男女之间存在恋爱关系,
即:恋爱关系一定是一男一女,现在要在这些恋爱
关系中找到最大集合,这个集合中任意两个学生之间
不存在恋爱关系,并且学生人数最多.
释义:最大团=补图的最大独立集,按照存在恋爱关系建有向边.
注意:输入中并没有给出具体谁是男谁是女,只是恋爱关系中学生的性别一定是不同的.
实际恋爱关系中男女可自己划分,这并不响应实际结果,也可不划分,暴力所有点跑匈牙利.
链接:http://poj.org/problem?id=1466
思路:首先恋爱关系是按照一男一女连接的,也就是恋爱关系
中相邻两点间的颜色一定是不同的,这满足了交叉染色法,因此
该恋爱关系构成的无向图一定是二分图,而问题问的显然是最大独立集
而二分图中最大独立集=顶点数-最大匹配.这里没有用交叉染色法划分
2个集合,因此所有点连跑遍匈牙利,结果/2.
*/
int n,m,vis[N],match[N],ans;
vector<int> G[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(match[v] == -1 || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(match,-1,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=0;i<n;i++){
            scanf("%d: (%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                G[u].push_back(v);
                G[v].push_back(u);
            }
        }
        for(int i=0;i<n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans/2);
    }
    return 0;
}
