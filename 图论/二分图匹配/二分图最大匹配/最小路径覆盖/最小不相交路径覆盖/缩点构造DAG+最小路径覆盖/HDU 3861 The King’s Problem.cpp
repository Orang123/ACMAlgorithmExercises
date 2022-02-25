#include<cstdio>
#include<cstring>
#include<vector>
#include<stack>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//ac 109ms tarjan缩点+DAG上最小路径覆盖
/*
题意:n个城市m条单向道路,国王要给n个城市进行规划,
分成若干个州.划分的规则为:
1.有边u到v以及有边v到u,则u,v必须划分到同一个州内.
2.一个州内的两点至少要有一方能到达另一方.即存在u到达v或v到达u,则u,v可划分到同一州.
3.一个点只能划分到一个州内.
4.在每对同属同一州的城市u到v的路上不能经过另一个州的城市.
现在国王希望所有城市划分的州数最少,输出这个最少数量.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3861
思路:首先若2城市互相可达,则必须划分到同一州,那么也就是原图中所有的scc必然是
同属于同一州的.可以先tarjan求解出scc缩点构造出DAG.若u到达v或v到达u,则u,v可
划分到同一州,也就是DAG上一条不分叉路径的直链上的节点都可划分到同一州,而且
因为同一州内u到v路径上不能有别的州的城市,因此不同州所属的直链不能有交点,显然
问最少划分州数,就是求解DAG上不相交的最小路径覆盖,而最小路径覆盖=顶点数-DAG上最大匹配.
*/
int n,m,dfn[N],low[N],clock,id,block[N],link[N],vis[N],ans;
vector<int> G[N],mp[N];
stack<int> s;

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    for(int &v: G[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        int v;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

int hungary(int u){
    for(int &v : mp[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || hungary(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    clock=id=ans=0;
    memset(dfn,0,sizeof(dfn));
    memset(block,0,sizeof(block));
    memset(link,0,sizeof(link));
    for(int i=1;i<=n;i++){
        G[i].clear();
        mp[i].clear();
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
        }
        for(int i=1;i<=n;i++){//原图可能不连通
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=1;i<=n;i++){//缩点构造DAG
            for(int &j : G[i]){
                if(block[i]!=block[j])
                    mp[block[i]].push_back(block[j]);
            }
        }
        for(int i=1;i<=id;i++){//求解DAG上的最小路径覆盖
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",id-ans);//最小路径覆盖=顶点数-最大匹配
    }
    return 0;
}
