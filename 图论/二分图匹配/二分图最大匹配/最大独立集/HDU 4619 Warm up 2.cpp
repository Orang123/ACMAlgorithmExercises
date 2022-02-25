#include<cstdio>
#include<cstring>
#include<vector>
#define N 1100
using namespace std;
//ac 15ms 最大独立集
//还有网络流的做法 https://blog.csdn.net/u011498819/article/details/38339115
/*
题意:1*2的纸牌分成n张水平放置坐标为(x,y)、(x+1,y),
m张垂直放置坐标为(x,y)、(x,y+1),现保证同一方向放置的
纸牌不会重叠,但水平方向和垂直方向可能会重叠,现在要移除
一些纸牌,使得剩下的纸牌两两相互之间不会重叠,现在请求出
剩下的互不相交纸牌的最大数量.
释义:最大团=补图的最大独立集,则按照相交关系建有向边.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4619
思路:可以将n张水平放置牌看做左集合,m张垂直放置的牌看做右集合.
那么n张水平放置的牌i与m张垂直放置的牌j相交的情况,
分为四种情况(x1==x2&&y1==y2)||(x1+1==x2&&y1==y2)||(x1+1==x2&&y1==y2+1)||(x1==x2&&y1==y2+1)
建边即i->j的有向边,则只需求出最小顶点覆盖,剩余的点必定两两无连边,
即纸牌间互不相交,所以求出最大独立集即可,最大独立集=顶点数(n+m)-最大匹配.
*/
int n,m,vis[N],match[N],ans;
vector<int> G[N];
struct Node{
    int x,y;
}node1[N],node2[N];

int dfs(int u){
    for(int &v : G[u]){
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
    for(int i=1;i<=N;i++) G[i].clear();
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d%d",&node1[i].x,&node1[i].y);
        for(int i=1;i<=m;i++)
            scanf("%d%d",&node2[i].x,&node2[i].y);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int x1=node1[i].x,y1=node1[i].y;
                int x2=node2[j].x,y2=node2[j].y;
                //水平和垂直相交分为4种情况
                if((x1==x2&&y1==y2)||(x1+1==x2&&y1==y2)||(x1+1==x2&&y1==y2+1)||(x1==x2&&y1==y2+1))
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=n;i++){//跑水平摆放的牌的左集合考虑配对 结果无需除2
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n+m-ans);
    }
    return 0;
}
