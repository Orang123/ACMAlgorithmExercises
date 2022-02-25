#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

/*
题意:给2个串分别是key和val,如果相邻的两个数不互质,可以取2个数的val的和,并且取完后,
两边的数就会变成新的相邻的数,问1~n的数最多能取到的价值val的和时多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5900
思路:区间dp,dp[i][j]代表i~j的数能取到的最大价值val的和
*/

ll n,key[310],val[310],dp[310][310],sum[310],ans;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%lld",&n);
        for(int i=1;i<=n;i++)
            scanf("%lld",&key[i]);
        for(int i=1;i<=n;i++){
            scanf("%lld",&val[i]);
            sum[i]=sum[i-1]+val[i];//计算前缀和,用来判断中间的数是否取完,两边的数是否相邻
        }
        for(int l=1;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                //若两端的数不互质,并且中间的数之前已经取完,这样两端的数i j就会成为新的相邻的数
                //因为取相邻数需保证互质才能取,因此上一dp状态不见得都取完了
                if(gcd(key[i],key[j])!=1 && dp[i+1][j-1] == sum[j-1]-sum[i]){
                    dp[i][j]=dp[i+1][j-1]+val[i]+val[j];
                }
                for(int k=i;k<j;k++)
                    dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
        printf("%lld\n",dp[1][n]);
    }
    return 0;
}


