#include<cstdio>
#include<cstring>
#include<vector>
#define N 550
using namespace std;
//ac 15ms 最小不相交路径覆盖
/*
题意:n个洋娃娃,有w(宽度),l(长度),h(高度),
当一个洋娃娃i的w、l、h三个指标都小于洋娃娃j时,
这时就可以将洋娃娃i套在洋娃娃j里边,每个洋娃娃内部
最多只能嵌套一个洋娃娃,现在按照这种套法,最后最少有
几个洋娃娃在裸露在最外面,注意裸露在最外面的洋娃娃内部
可能含有很多洋娃娃,现在只是问裸露最外面的这些洋娃娃的整体
最小个数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4160
思路:因为每个洋娃娃内部最多只能嵌套一个洋娃娃,很明显被嵌套
与嵌套的洋娃娃可以看做一对匹配,那么实际每个裸露在最外面的洋娃娃
和其内部嵌套的洋娃娃恰好可以看做一条简单路径,而每个裸露在外面的洋娃娃,
它们可以看做几条不相交的路径(每个不同最外层洋娃娃的彼此内部洋娃娃是不相交的),
要想裸露在最外面的洋娃娃数目最少,把每个洋娃娃看做点,问题转化为了
最少有几条路径覆盖所有的点,即:最小不相交路径覆盖,而这里点与点间的
有向边就是洋娃娃间的嵌套关系,所以若洋娃娃i的w、l、h都小于洋娃娃j,
则建立i->j的有向边,这样恰好构建出DAG,最后匈牙利求解最大匹配,
则最小不相交路径覆盖=顶点数-最大匹配.
*/
int n,vis[N],match[N],ans;
vector<int> G[N];

struct Node{
    int w,l,h;
}node[N];

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
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&node[i].w,&node[i].l,&node[i].h);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i == j) continue;
                //洋娃娃i的宽、长、高都严格小于洋娃娃j时,就建立i->j的有向边.
                if(node[i].w<node[j].w && node[i].l<node[j].l && node[i].h<node[j].h)
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans);//最小不相交路径覆盖=顶点数-最大匹配
    }
    return 0;
}
