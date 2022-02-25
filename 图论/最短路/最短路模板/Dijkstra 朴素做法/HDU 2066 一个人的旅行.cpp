#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

/*
题意:n+1个点,t条双向边有权值,编号为0的点和某些点直接相连,权值为0,
现在求0点到指定某些目标点的最短距离.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2066
思路:单源多目标最短路比较求取最小值.
*/

int cost[1500],G[1500][1500],n;
int expect[1500];
bool visit[1500];

void init(){
    for(int i=0;i<=n;i++){
        G[i][i]=0;
        cost[i]=G[0][i];
    }
    visit[0]=true;
}

void Dijkstra(){
    int pos,minDis;
    init();
    for(int i=1;i<=n;i++){//这里其实只要n-1次即可 因为起点本身就已经默认选过了
        minDis=INF;
        for(int j=1;j<=n;j++){
            if(!visit[j]&&cost[j]<minDis){
                minDis=cost[j];
                pos=j;
            }
        }
        //printf("cost[%d]=%d\n",pos,minDis);
        visit[pos]=true;
        for(int k=1;k<=n;k++){
            if(!visit[k]&&cost[pos]+G[pos][k]<cost[k]){
                cost[k]=cost[pos]+G[pos][k];
            }
        }
    }
}

int main(){
    int T,S,D,a,b,price,minDis;
    while(scanf("%d%d%d",&T,&S,&D)!=EOF){
        n=0;
        memset(G,INF,sizeof(G));
        memset(visit,false,sizeof(visit));
        for(int i=0;i<T;i++){
            scanf("%d%d%d",&a,&b,&price);
            n=max(max(n,a),b);
            if(price<G[a][b])//因为用的是邻接矩阵,会有重边,要记录最小权值
                G[a][b]=G[b][a]=price;
        }
        for(int i=0;i<S;i++){
            scanf("%d",&a);
            G[0][a]=G[a][0]=0;
        }
        for(int i=0;i<D;i++)
            scanf("%d",&expect[i]);
        Dijkstra();
        minDis=INF;
        for(int i=0;i<D;i++)
            minDis=min(minDis,cost[expect[i]]);
        printf("%d\n",minDis);
    }
    return 0;
}
