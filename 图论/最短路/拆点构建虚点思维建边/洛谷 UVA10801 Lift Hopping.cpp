#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 650
#define M 5000
#define INF 0x3f3f3f3f
using namespace std;
//分层图最短路 不同的是这个题目是对点状态的拆分
//这个题目分层图就是电梯所在的楼层,同层之间的连边代表换乘电梯,
//层与层之间代表电梯在楼层间移动,而经典分层图移动是在每个层的横向边中,纵向层间的连边代表交互
//因为一层楼有n部电梯,每一层就有n个状态,分别表示不同的电梯在这层楼
/*
题意:0~99的楼层,一个人初始在0层(不花费时间),n个电梯(n<=5),
电梯i上下相邻两层的时间为t[i],人可在同一层停下的电梯互换,耗费时间60s,
现在求人从0层到达k层,最少需要花费多少时间.
链接:https://www.luogu.com.cn/problem/UVA10801
思路:可以把每一层抽象成一个点,但是每一层都有n个电梯,
所以将每层拆成n个状态表示,代表不同电梯在这层的状态,
因为楼层最高有99层,所以电梯i在j层的点状态可以表示为
i*100+j,对于电梯之间的换乘,因为层数和电梯数很小,
所以可以暴力枚举每一层任意两个电梯状态建边.
*/

int n,k,cnt,head[N],vis[N],dis[N],t[N],floor[N];

struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void spfa(int s){
    init(s);
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&t[i]);//t[i] 每个电梯上下相邻两层间的单位时间
        for(int i=1;i<=n;i++){
            int num=0;//表示电梯暂停在几个楼层
            addEdge(0,100*i,0);//设置一个超级源点到0层的每个电梯,实际就是考虑初始0层尝试每个电梯作为初始点
            while(scanf("%d",&floor[++num]))//floor记录的是每个电梯在楼层暂停的序列
                if(getchar()=='\n') break;//因为没有说具体暂停在几个楼层,所以以回车符结束.
            for(int j=1;j<num;j++){
                //因为电梯是上下互通,所以构建电梯i运行相邻序列楼层(j,j+1)的双向边
                //耗费时间为(floor[j+1]-floor[j])*t[i]
                addEdge(100*i+floor[j],100*i+floor[j+1],(floor[j+1]-floor[j])*t[i]);
                addEdge(100*i+floor[j+1],100*i+floor[j],(floor[j+1]-floor[j])*t[i]);
            }
        }
        /*
        枚举每个楼层间可以互乘的电梯构建双向边,
        实际这层的电梯可能无法互通,因为电梯暂停序列不一定都停在这层
        */
        for(int i=0;i<=99;i++){
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++){
                    if(j!=k)
                        addEdge(100*j+i,100*k+i,60);//因为是O(n^2)枚举,所以只要枚举单向边就好
                }
            }
        }
        spfa(0);//因为构建了 超级源点所以只需一次最短路
        int ans=INF;
        for(int i=1;i<=n;i++)//不清楚第k层哪个电梯到达时所用时较小,所以比较记录最小值
            ans=min(ans,dis[i*100+k]);//实际上也可以将给第k层建一个公共汇点t,权为0,求取dis[t]即可
        if(ans!=INF) printf("%d\n",ans);
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}
