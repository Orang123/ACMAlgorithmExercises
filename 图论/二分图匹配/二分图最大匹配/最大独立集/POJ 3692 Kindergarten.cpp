#include<cstdio>
#include<cstring>
#include<vector>
#define N 250
using namespace std;
//ac 125ms 最大独立集
/*
参考博客:https://blog.csdn.net/u011815404/article/details/86609798
最大团相关概念:最大团是np问题
1.当G′是图G的子图,且G′是关于V′的完全图时,子图G'为图G的团;
当G'是团,且不是其他团的子集时,G'为图G的极大团;当G'是极大团时,
且点数最多,G'为图G最大团.
2.当G′中所有点不相邻,最大点集最大的图G′为图G的最大独立集,
且最大独立集数=补图的最大团.
3.当用个数最少的团覆盖图G所有的点时,称为最小团覆盖,由于每个团中最多取一个点,
因此有最大独立集<=最小团覆盖.
4.通俗来讲极大团是增加任一顶点都不再符合定义的团,最大团是图中含顶点数最多的极大团,
最大独立集是除去图中的团后的点集,而最大团问题就是在一个无向图中找出一个点数最多的完全图.

最大团模板题 应用Bron-Kerbosch 算法
Maximum Clique(HDU-1530) Graph Coloring(POJ-1419)
*/

/*
题意:g个女孩,b个男孩,其中所有的女孩之间相互认识,
所有的男孩之间也相互认识,还有m条男女相互认识的关系,
现在老师要挑选出一些孩子玩游戏,使得这些孩子任意两个
孩子都相互认识,现在求出这些孩子的最大数量.
释义:实际就是求解所有学生间认识关系的最大团,而最大团=补图的最大独立集.
链接:http://poj.org/problem?id=3692
思路:可以将女孩划分成左集合,男孩划分成右集合,
显然这些孩子之间任意两点间都要有相互认识的连边关系的,
但是同一集合都在左都在右可以忽略连边关系,所以只要左集合
和右集合之间的孩子任意两个孩子都有连边即可.这个问题本身是个
最大团问题可以转化为补图的最大独立集,因此可以考虑按照
反向关系建图即:若一个女孩i和男孩j不认识建i->j的有向边,这样构成
了单向关系的二分图,求出最大匹配,划分出最小顶点覆盖,则最小顶点覆盖
的补集即最大独立集剩下的孩子之间两两之间一定是认识的,因为若性别一致,
则本身就相互认识,若性别不一致,因为是按不认识建的边,剩下的补集如女孩x,
一定和所有的男孩都有认识关系,所以求出最大独立集即可,最大独立集=顶点数(g+b)-最大匹配.
*/
int cas,g,b,m,vis[N],mp[N][N],match[N],ans;
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
    cas++;
    memset(match,0,sizeof(match));
    memset(mp,0,sizeof(mp));
    for(int i=1;i<=g;i++) G[i].clear();
}

int main(){
    int u,v;
    while(scanf("%d%d%d",&g,&b,&m) && g+b+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);//u横坐标代表女生,v纵坐标代表男生
            mp[u][v]=1;//女孩u和男孩v认识
        }
        for(int i=1;i<=g;i++){
            for(int j=1;j<=b;j++){
                if(!mp[i][j])//女孩i和男孩j不认识
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=g;i++){//只考虑女孩集合中点的配对,结果无需除2
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("Case %d: %d\n",cas,g+b-ans);
    }
    return 0;
}
