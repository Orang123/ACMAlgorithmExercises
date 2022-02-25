/*
题意:N堆石子摆成一条线。现要将石子有次序地合并成一堆。规定每次只能选相邻
的2堆石子合并成新的一堆，并将新的一堆石子数记为该次合并的代价。
计算将N堆石子合并成一堆的最小代价。
例如： 1 2 3 4，有不少合并方法
1 2 3 4 => 3 3 4(3) => 6 4(9) => 10(19)
1 2 3 4 => 1 5 4(5) => 1 9(14) => 10(24)
1 2 3 4 => 1 2 7(7) => 3 7(10) => 10(20)
括号里面为总代价可以看出，第一种方法的代价最低，现在给出n堆石子的数量，
计算最小合并代价。
n<=1000.
链接:https://www.51nod.com/Challenge/Problem.html#problemId=1022
思路:
n最大有1000,如果按照原先朴素的区间dp O(N^3)=10^9,1s之内显然会超时,
这里需要用到四边形不等式优化,实质是在分割区间时记录最优的断点,
这个四边形不等式暂时也没看懂,有几个证明的链接:
https://blog.csdn.net/noiau/article/details/72514812
https://wenku.baidu.com/view/c44cd84733687e21af45a906.html
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp[2100][2100],s[2100][2100],sum[2100];
int main(){
    int minc=INF;
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
    }
    for(int i=1;i<=2*n-1;i++){
        sum[i]+=sum[i-1];
        dp[i][i]=0;
        s[i][i]=i;
    }
    for(int l=1;l<=n-1;l++){
        for(int i=1;i+l<=2*n-1;i++){
            int j=i+l;
            for(int k=s[i][j-1];k<=s[i+1][j];k++){
                if(dp[i][j]>dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]){
                    dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
                    s[i][j]=k;//记录断点
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
        minc=min(minc,dp[i][i+n-1]);
    printf("%d",minc);
    return 0;
}
