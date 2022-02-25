#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
题意:有一根长度为L（L＜1000）的棍子，还有n（n＜50）个切割点的位置（按照从小到大排 列）。
你的任务是在这些切割点的位置处把棍子切成n＋1部分，使得总切割费用最小。每次 切割的费用等于被切割的木棍长度。
例如，L=10，切割点为2, 4, 7。如果按照2, 4, 7的顺序， 费用为10＋8＋6=24，如果按照4, 2, 7的顺序，费用为10＋4＋6=20。
链接:https://www.luogu.com.cn/problem/UVA10003
思路:dp[i][j]代表当前木棍在i到j这部分,i j节点显然已经切割过了,再切割下一个节点(在i+1~j-1中选取)所用到的最小花费
*/
int dp[60][60],L,n,a[60];

int main(){
    while(scanf("%d",&L)&&L){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        a[n+1]=L;//在切割最先开始整块木棍的时候的花费为木棍的总长度
        for(int i=0;i<=n;i++)
            //只剩下两个节点的木棍已经没有节点可切割,因为两个端点是已经被切割过的才能单独分出来, [0,1] [n,n+1]分别代表切割只剩下一个1节点和一个n节点
            dp[i][i+1]=0;
        for(int l=2;l<=n+1;l++){//从长度为3开始
            for(int i=0;i+l<=n+1;i++){//起始点从0开始
                int j=i+l;
                for(int k=i+1;k<j;k++)//i,j已经切割过 [i+1,j-1]枚举切割点k,k所在的木棍长度为a[j]-a[i]
                    //dp[i][k] dp[k][j]的k为什么重叠是因为,i k j本身就是切割点,为了保证木棍长度正确性,这三个端点都是之前切割过的,不能再切割,所以子状态的k是重叠的
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+a[j]-a[i]);
            }
        }
        printf("The minimum cutting is %d.\n",dp[0][n+1]);
    }
    return 0;
}
