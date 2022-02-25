#include<stdio.h>
#include<string.h>
#define N 101
#define INF 0x7ffffff

/*
题意:http://acm.hdu.edu.cn/showproblem.php?pid=1599
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1599
思路:floyd求最小环
*/

int mpt[N][N];
int dist[N][N];
int m,n,minc;
int min(int x,int y){
    if(x<y) return x;
    return y;
}
//https://blog.csdn.net/olga_jing/article/details/49928443
//https://blog.csdn.net/a1dark/article/details/11658153
//https://www.cnblogs.com/ziyi--caolu/p/3448467.html
/*
OI wiki版本
int val[maxn + 1][maxn + 1];  // 原图的邻接矩阵
inline int floyd(const int &n) {
  static int dis[maxn + 1][maxn + 1];  // 最短路矩阵
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) dis[i][j] = val[i][j];  // 初始化最短路矩阵
  int ans = inf;
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i < k; ++i)
      for (int j = 1; j < i; ++j)
        ans = std::min(ans, dis[i][j] + val[i][k] + val[k][j]);  // 更新答案
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dis[i][j] = std::min(
            dis[i][j], dis[i][k] + dis[k][j]);  // 正常的 floyd 更新最短路矩阵
  }
  return ans;
}
*/

void floyd(){
    minc=INF;
    for(int k=1;k<=n;k++){//前K-1个点的情况递推前K个点的情况
        for(int i=1;i<=k;i++)
            for(int j=i+1;j<=k;j++)//两个点必然是不同的
                minc=min(minc,dist[i][j]+mpt[i][k]+mpt[k][j]);//K为环的最大点、无向图三点成环  这个找回路的地方没太看明白
        for(int i=1;i<=n;i++)//floyd算法求任意两点的最短路、包含前K-1个点
            for(int j=1;j<=n;j++)
                if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
    }
}
void init(){//初始化必须全部都为无穷大、因为自身不能成环
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            mpt[i][j]=INF;
            dist[i][j]=INF;
        }
}
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        int s,e,v;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&s,&e,&v);
            if(v<mpt[s][e]){
                mpt[s][e]=v;
                mpt[e][s]=v;
                dist[s][e]=v;
                dist[e][s]=v;
            }
        }
        floyd();
        if(minc<INF)
            printf("%d\n",minc);
        else
            printf("It's impossible.\n");
    }
    return 0;
}
