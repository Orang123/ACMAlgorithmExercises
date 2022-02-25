/*
题意:ACBOY有n门功课要做,他总共有m天做这些功课,一门课有m种上法,
分别分为1..m天来上,如果利用j天在功课i上,他能够获得的价值是a[i][j],
问ACBOY在m天内上课能获得最大价值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1712
1<=n,m<=100
思路:对于每门课的上法有m种方式来上,而这门课只能选择一种方式去上,
可以将不同课作为不同的分组,组内的物品就是这门课m种上课方式,物品
的体积是这种上课方式的天数,物品价值是这种上课方式获得的价值a[i][j].
背包容量为总天数m,转化为一个分组背包模型.
*/
//ac 62ms 一维数组实现
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int a[N][M],dp[M];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        for(int i=1;i<=n;i++){
            for(int j=m;j>=1;j--){//因为所有课程至少要花1天上,所以背包容量j的下界是1
                for(int k=1;k<=j;k++)//上课的天数不会超过当前背包容量j,因此上课方式天数上界是j
                    dp[j]=max(dp[j],dp[j-k]+a[i][k]);
            }
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}

/*
//ac 62ms 二维数组实现 后两层循环顺序,先枚举枚举背包容量,再枚举每组物品
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int a[N][M],dp[N][M];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(dp[0],0,sizeof(dp[0]));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        for(int i=1;i<=n;i++){
            //虽然所有课程至少要花1天上,背包容量j的下界是1,但是每个状态的dp[i][0]都要继承前dp[i-1][0],
            //因为某个组可以一个物品也不取,因此j下界是0
            for(int j=m;j>=0;j--){
                dp[i][j]=dp[i-1][j];
                for(int k=1;k<=j;k++)//上课的天数不会超过当前背包容量j,因此上课方式天数上界是j
                    dp[i][j]=max(dp[i][j],dp[i-1][j-k]+a[i][k]);
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
*/

/*
//ac 46ms 二维数组实现 颠倒后两层循环顺序,先枚举每组物品,再枚举背包容量
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int a[N][M],dp[N][M];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(dp[0],0,sizeof(dp[0]));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++)
                dp[i][j]=dp[i-1][j];
            for(int k=1;k<=m;k++)//上课的天数不会超过当前背包容量j,因此上课方式天数上界是j
                for(int j=k;j<=m;j++){//因为所有课程至少要花1天上,所以背包容量j的下界是1
                    dp[i][j]=max(dp[i][j],dp[i-1][j-k]+a[i][k]);
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
*/
