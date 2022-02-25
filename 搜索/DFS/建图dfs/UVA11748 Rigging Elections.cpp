/*
题意:摘自网上
有n个竞选人，由m个人投票，每个人对竞选人都有一个排名，每次两个人竞选，
m个人分别投票，每次两个人，胜利者继续参与竞选，失败者淘汰，剩余一个人
的时候停止你希望让c最后获得胜利，你可以安排每次参与竞选的两个竞选人，
问是否有可能让c竞选成功。
1<=n,m<=100.
链接:https://www.luogu.com.cn/problem/UVA11748
思路:对于任意两个人i,j,在m个人的优先级中,若第i个人能占到半数朝上,则建i->j的
优先边,否则建j->i的有向边.最后从c点开始遍历是否能形成一棵以c为根节点的有向树,
若能形成,则说明c可以获得最后的胜利.对于c处于中间节点不在两端边缘的情况都说明,
c并不是最终票数优先级最高的,因此c不能获胜.
*/
//ac 0ms dfs建边
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

int n,m,c,vis[N],g[N][N];
vector<int> G[N];

int dfs(int u){
    if(vis[u])
        return 0;
    vis[u]=1;
    int res=1;
    for(int &v : G[u]){
        res+=dfs(v);
    }
    return res;
}

int main(){
    int x;
    while(scanf("%d%d%d",&n,&m,&c) && n+m+c){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            G[i].clear();
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&x);
                g[i][x]=j;//x的优先级 为j
            }
        }
        int num=0;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                num=0;
                for(int k=1;k<=m;k++){
                    if(g[k][i]<g[k][j])
                        num++;
                }
                if(num>m/2)//在m个人的投票中 第i个人的票数要多于第j个人 建i->j的有向边
                    G[i].push_back(j);
                else
                    G[j].push_back(i);
            }
        }
        if(dfs(c) == n)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
