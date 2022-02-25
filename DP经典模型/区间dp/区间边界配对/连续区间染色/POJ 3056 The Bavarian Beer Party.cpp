#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
/*
题意:有偶数个人，所有人都必须互相敬酒，而不是只有相同标号的才能敬酒，
而且不能交叉，问在这种情况下，互相敬酒的人牌子相同的最大对数
链接:http://poj.org/problem?id=3056
思路:类似括号匹配,只不过对于区间[i,j]我们判断a[i]==a[j] [xxxx]oooo=xxxx+oooo+1
并且不能每个人都要敬酒,而且不能交叉,所以区间长度必须为偶数增长
*/
int dp[1100][1100],a[1100],n;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=1;l<n;l+=2){//每个人必须敬酒,不能出现dp[i][i]以及奇数长度区间的情况,即某个人不敬酒的情况
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=dp[i+1][j];//初始化dp[i+1][j]
                for(int k=i+1;k<=j;k+=2){//判断a[i]和a[k] (k>=i+1 k<=j) k的增长同样也呈偶数增长,区间必须都为偶数长度
                    if(a[i] == a[k])//每个人敬酒不能交叉,根据i k边界分割区间 若相等 牌子对数还要+1
                        dp[i][j]=max(dp[i][j],dp[i+1][k-1]+dp[k+1][j]+1);
                    else//若不相等,也敬酒 只不过不统计牌子相同的个数
                        dp[i][j]=max(dp[i][j],dp[i+1][k-1]+dp[k+1][j]);
                }
            }
        }
        printf("%d\n",dp[1][n]);
    }
	return 0;
}

/*
dp[i][j]=dp[i+1][j-1]+1
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
int dp[1100][1100],a[1100],n;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=1;l<n;l+=2){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                if(a[i] == a[j])
                    dp[i][j]=dp[i+1][j-1]+1;
                else//不相等 也敬酒 只不过不统计牌子的对数
                    dp[i][j]=dp[i+1][j-1];//a[i]和a[j]不相等 初始化为dp[i+1][j-1],否则仅凭下面的分割区间 解集覆盖不完全
                for(int k=i+1;k<j;k+=2)
                    dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
        printf("%d\n",dp[1][n]);
    }
	return 0;
}
*/

