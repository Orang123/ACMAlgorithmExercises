#include<stdio.h>
#include<string.h>
#define N 101
#define INF 0x7ffffff

/*
����:http://acm.hdu.edu.cn/showproblem.php?pid=1599
����:http://acm.hdu.edu.cn/showproblem.php?pid=1599
˼·:floyd����С��
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
OI wiki�汾
int val[maxn + 1][maxn + 1];  // ԭͼ���ڽӾ���
inline int floyd(const int &n) {
  static int dis[maxn + 1][maxn + 1];  // ���·����
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) dis[i][j] = val[i][j];  // ��ʼ�����·����
  int ans = inf;
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i < k; ++i)
      for (int j = 1; j < i; ++j)
        ans = std::min(ans, dis[i][j] + val[i][k] + val[k][j]);  // ���´�
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dis[i][j] = std::min(
            dis[i][j], dis[i][k] + dis[k][j]);  // ������ floyd �������·����
  }
  return ans;
}
*/

void floyd(){
    minc=INF;
    for(int k=1;k<=n;k++){//ǰK-1������������ǰK��������
        for(int i=1;i<=k;i++)
            for(int j=i+1;j<=k;j++)//�������Ȼ�ǲ�ͬ��
                minc=min(minc,dist[i][j]+mpt[i][k]+mpt[k][j]);//KΪ�������㡢����ͼ����ɻ�  ����һ�·�ĵط�û̫������
        for(int i=1;i<=n;i++)//floyd�㷨��������������·������ǰK-1����
            for(int j=1;j<=n;j++)
                if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
    }
}
void init(){//��ʼ������ȫ����Ϊ�������Ϊ�����ܳɻ�
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
