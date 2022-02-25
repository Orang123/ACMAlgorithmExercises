#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

/*
题意:给出一个长度为n的数列，将其分成若干段，要求各个分段首数值*2^(分段里的数值个数)累加最小，
同一段的数 要<=20个.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4570
思路:dp[i][j]代表i~j内分成若干段求和的最小值
*/
ll dp[70][70],a[70],n,sum[70];

ll cal(int j){
    int tmp=1;
    for(int i=1;i<=j;i++)
        tmp*=2;
    return tmp;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&n);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            sum[i]=sum[i-1]+a[i];
        }
        //状态转移应该是小区间转移到大区间 但初始化最小子问题时,对于一个子段可以是任意长度,要分为<=20和>20,2种情况
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                if(j-i+1<=20)
                    dp[i][j]=a[i]*cal(j-i+1);
                else//若大于20默认每个数都当做一段,求解最优分段会在dp分割区间时计算
                    dp[i][j]=(sum[j]-sum[i-1])*2;
            }
        }
        for(int l=1;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                for(int k=i;k<j;k++)//分割区间的过程实际就是不断划分段求解最优值的过程.到底分成几段题目没有要求只要求解最优值
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
        printf("%lld\n",dp[1][n]);
    }
	return 0;
}
