#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
/*
题意:求1->n的最短路
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2544
思路:最短路裸题,这是Dijkstra的朴素版本.
*/

int G[110][110];
int cost[110],n;
bool visit[110];
void init(){//初始化点1到其它各点的距离
    for(int i=1;i<=n;i++){
        G[i][i]=0;
        cost[i]=G[1][i];
    }
}
//O(n^2+m)~=O(n^2)
int Dijkstra(){
    int minVal,minIndex;
    init();
    for(int i=1,j;i<=n;i++){
        minVal=INF;//这里minval初始化INF要放在第一层循环的开始处，当时因为这个位置放错了 wrong了好久
        for(j=1;j<=n;j++){//贪心
            if(!visit[j]&&cost[j]<minVal){
                minVal=cost[j];//求解当前点1到其它各点的最短距离
                minIndex=j;
            }
        }
        visit[minIndex]=true;
        for(int k=1;k<=n;k++){//根据求解出的这个最小点去尽可能更新其它点集
            if(!visit[k]&&cost[minIndex]+G[minIndex][k]<cost[k]){
                cost[k]=cost[minIndex]+G[minIndex][k];
            }
        }
    }
    return cost[n];
}

int main(){
    int m,x,y,val,res;
    while(scanf("%d%d",&n,&m)&&n+m){
        memset(G,INF,sizeof(G));
        memset(visit,false,sizeof(visit));
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&x,&y,&val);
            G[x][y]=G[y][x]=val;
        }
        printf("%d\n",Dijkstra());
    }
    return 0;
}
