#include<cstdio>
#include<cstring>
#include<vector>
#define N 250
using namespace std;
//ac 16ms
/*
题意:n个奶牛,m个牛栏,每个奶牛只愿意在特定的牛栏产奶,
并且一个牛栏只能分配给一头奶牛,一头奶牛也只能分配给一个牛栏.
求出最多有多少奶牛能在牛栏产奶.
链接:http://poj.org/problem?id=1274
思路:二分图最大匹配.奶牛为左集合,牛栏为右集合.
*/
int n,m,vis[N],match[N],ans;
vector<int> G[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int a,t;
    while(scanf("%d%d",&n,&m)!=EOF){//m实际没用
        init();
        for(int i=1;i<=n;i++){//i奶牛编号
            scanf("%d",&t);//每头奶牛有t个愿意产奶的牛栏
            while(t--){
                scanf("%d",&a);//牛栏a
                G[i].push_back(a);//奶牛i愿意在牛栏a产奶
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
