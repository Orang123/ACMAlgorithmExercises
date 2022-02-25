#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
题意:输入一个序列，两只兔子分别顺时针、逆时针走，
同一时刻它们到的石头上的数值要相同，不能回到起点,求最多走过几个石头。
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4745
思路:区间dp求解环状最长回文子序列长度.
dp[i][j]表示区间[i,j]中最长回文子序列的长度.
实际就是求解环状的最长回文子序列,和环状石子合并处理一样,将数组扩大到2n.
只是要注意两只兔子有可能一开始就在同一起点,本身0时刻石头数值就是相同的,
所以这种情况得单独考虑,dp[i+n-2]+1,表示将同一起点单独算作一个,只考虑长度为n-1
的链的最长回文子序列长度.
*/
int a[2100],dp[2100][2100];

int main(){
    int n;
    while(scanf("%d",&n)&&n){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            a[i+n]=a[i];
            dp[i][i]=dp[i+n][i+n]=1;
        }
        for(int l=1;l<n;l++){
            for(int i=1;i+l<2*n;i++){
                int j=i+l;
                if(a[i] == a[j])
                    dp[i][j]=dp[i+1][j-1]+2;
                else
                    dp[i][j]=max(dp[i][j-1],dp[i+1][j]);
            }
        }
        int ans=1;
        for(int i=1;i<n;i++){
            ans=max(ans,dp[i][i+n-1]);//两只兔子起点不同 dp[i][i+n-1]长度为n的链
            ans=max(ans,dp[i][i+n-2]+1);//dp[i][i+n-2]+1 两只兔子0时刻起点相同,只考虑长度为n-1的链
        }
        printf("%d\n",ans);
    }
    return 0;
}
