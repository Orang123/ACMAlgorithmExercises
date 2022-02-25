#include<cstdio>
#include<cstring>
#include<vector>
#define N 110
#define M 1100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//ac 873ms 最小路径覆盖
/*
此题floyd初始化一定要把自己到自己设置为0,全部设置为INF会wa.
实际全部设置为INF如果存在i->k->k->i这样的回路,mp[i][i]会错误
更新成mp[i][k]+mp[k][i]的数值,但它本身就应为0,但这并不影响
其余顶点对的最短距离,而且此题实际不同的请求(任务)有可能是
地点相同,但开始时间不同,所以有可能一个请求地点是x,下个请求
地点还是x,这时就用到了自己到自己mp[i][i]这个距离,而直接初始化INF会出错.
*/

/*
题意:n个城市,m条双向道路,每条道路有一定距离,哈利要
给一些城市的人送礼物,现在有q个请求,每个请求需要在某个城市
送礼物,显然只靠哈利自己一人很难完成,现在哈利需要朋友的帮助去送
剩下的礼物,问哈利最少需要几个朋友的帮助才能将q个请求的礼物送完.
每个请求由p,t构成分别代表送礼物的城市和送到的时间点,
每个人送礼物时每单位时间一个单位的距离,送完一个礼物可以沿着道路送下一个礼物,
假设每个人可以自由选择初始的城市和开始的时间.
注意:
1.哈利本身也会选择一条路线送礼物,同一要求礼物的城市可被多个朋友经过.
即:各个朋友路线可交叉.
2.不同请求,有可能送礼物的地点是相同的,但送达时间不同,因此会用到mp[i][i]这样的自环,
所以初始化一定要将mp[i][i]自己到自己设置为0,否则全设置INF,会错误更新mp[i][i]为某个回路分割的距离和.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3991
思路:和POJ 3216一样,建边按照当前请求开始时间点+两礼物间城市最短距离<=另一礼物送达时间建有向边.
最小可相交路径覆盖转化为最小不相交路径覆盖=顶点数-最大匹配-1.
因为哈利本身也会覆盖选择一条路径覆盖,因此结果要除去哈利 因此减1.
*/

int cas,n,m,q,vis[M],match[M],ans;
ll mp[N][N];
vector<int> G[M];

struct Node{
    int p;
    ll t;
}node[M];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(match[v] == -1 || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

//处理任意两片区最短距离刚好也处理相隔点的连通性问题
//将最小可相交的路径覆盖转化为了最小不相交的路径覆盖
void floyd(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                if(mp[i][j]>mp[i][k]+mp[k][j])
                    mp[i][j]=mp[i][k]+mp[k][j];
        }
    }
}

void init(){
    ans=0;
    cas++;
    //floyd不能直接初始化INF,直接初始化INF会导致mp[i][i]的值错误,
    //必须要将自己到自己设置为0才行.
    //memset(mp,0x3f,sizeof(mp));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            mp[i][j]=i==j?0:INF;//i==j自环必须是0
    }
    memset(match,-1,sizeof(match));
    for(int i=1;i<=q;i++) G[i].clear();
}

int main(){
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&q);
        init();
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            mp[u][v]=mp[v][u]=w;
        }
        for(int i=1;i<=q;i++)
            scanf("%d%lld",&node[i].p,&node[i].t);
        floyd();
        for(int i=1;i<=q;i++){
            for(int j=1;j<=q;j++){
                if(i == j) continue;
                //不同的任务node[i].p和node[j].p的地点可能相同,也就是会用到mp[i][i]这样的自环,
                //但送达时间node[i].t和node[j].t要求不同
                if(node[i].t+mp[node[i].p][node[j].p]<=node[j].t)
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=q;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("Case %d: %d\n",cas,q-ans-1);//最小路径覆盖=顶点数-最大匹配
    }
    return 0;
}
