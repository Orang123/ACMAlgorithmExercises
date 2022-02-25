#include<cstdio>
#include<cstring>
#include<vector>
#define N 25
#define M 250
#define INF 0x3f3f3f3f
using namespace std;
//ac 79ms 最小顶点覆盖
/*
题意:一个城市有q片区域,每片区域之间有一定的距离,用邻接
矩阵表示,-1代表不可达,一个维修公司,收到n个维修任务,每个
任务规定了维修的片区p,开始维修的时间t,以及修理时间d,一个
任务由一名工人单独完成,必须完成当前修理任务才能进行下一个
任务现在公司想要完成所有的维修任务,需要的分配的最少工人数是多少.
公司分配工人可以以任意的时间选择任意区域作为初始地点.
注意:工人维修每个任务必须严格按照开始时间开始维修,同一个维修区域不同工人都可以经过.
各个工人路线可交叉.
链接:http://poj.org/problem?id=3216
思路:问题问的就是至少要派几名工人选择合适的维修路线完成所有的
维修任务.那么对于维修路线必然是一个任务和另一个任务衔接,那么两个
任务要能正常衔接,必须是前一个任务i完成时间(开始时间+维修时间)+
到达下一个任务j地点的时间要小于等于下个任务j开始时间node[j].t,
即node[i].t+node[i].p+minDis(node[i].p,node[j].p)<=node[j].t
就建立任务i->任务j的有向边,这里为了使任务之间更好地衔接,两个
任务地点间的距离应尽可能最短,即需要求出所有任务地点间的最短距离,
因为q<=20可用floyd,之后各个任务间刚好构建成一个DAG,问题就变成
最小可相交的路径覆盖=顶点数-最大匹配.因为floyd本身已经处理了相隔
点之间的连通性,所以已经将最小可相交的路径覆盖转化为了最小不相交的路径覆盖.
这个建边的方式保证了一定没有环,因为时间点越往后是越大的,一定是DAG.
*/
int q,n,mp[N][N],vis[M],match[M],ans;
vector<int> G[M];

struct Node{
    int p,t,d;
}node[M];

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

//处理任意两片区最短距离刚好也处理相隔点的连通性问题
//将最小可相交的路径覆盖转化为了最小不相交的路径覆盖
void floyd(){
    for(int k=1;k<=q;k++){
        for(int i=1;i<=q;i++){
            for(int j=1;j<=q;j++)
                if(mp[i][j]>mp[i][k]+mp[k][j])
                    mp[i][j]=mp[i][k]+mp[k][j];
        }
    }
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int u,v;
    while(scanf("%d%d",&q,&n) && q+n){
        init();
        for(int i=1;i<=q;i++){
            for(int j=1;j<=q;j++){
                scanf("%d",&mp[i][j]);
                if(mp[i][j] == -1) mp[i][j]=INF;//-1 代表不可达初始化INF无穷大
            }
        }
        for(int i=1;i<=n;i++)//n个维修任务 p代表维修区域编号 t代表维修开始时间 d代表维修时长
            scanf("%d%d%d",&node[i].p,&node[i].t,&node[i].d);
        floyd();
        //这个建边的方式保证了一定没有环,因为时间点越往后是越大的,一定是DAG
        for(int i=1;i<=n;i++){//枚举i任务做完后是否能衔接j任务的开始时间
            for(int j=1;j<=n;j++){//因为判断时单向关系所以j从1开始
                if(i == j) continue;
                //若i任务的开始时间+维修时长+i任务地点->j任务地点最短距离小于等于j任务开始时间 则建i->j单向边
                if(node[i].t+node[i].d+mp[node[i].p][node[j].p]<=node[j].t)
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans);//最小路径覆盖=顶点数-最大匹配
    }
    return 0;
}
