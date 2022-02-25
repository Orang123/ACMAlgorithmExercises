#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
题意:n场舞会 按顺序参加,每场舞会要求穿特定颜色的衣服,衣服可以套着覆盖着穿,
但是一件衣服一旦脱下就不能再穿上了(是指这件衣服,而不是这种颜色的衣服),问按
顺序参加完所有舞会最少要穿多少件衣服.
链接:http://lightoj.com/volume_showproblem.php?problem=1422
思路:其实就是CQOI2007染色题目换了个场景,一种优化,对于舞会i<j如果要求穿的衣服颜色相同即a[i]==a[j],
那么ij这两场舞会可以只穿一件这种颜色的衣服,可以把这件衣服穿在最底层,在舞会i穿完后不脱下,对于接下
来的舞会需要什么颜色的衣服套在它上面,最后到了j舞会,那件a[i]的衣服依然穿在最下层,这样这种颜色的衣服
就只穿了一件.dp[i][j]代表i~j的舞会所需穿的最少数量的衣服
*/

int a[110],dp[110][110],n;

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=dp[i+1][j]+1;//初试化若a[i]和a[k]没有衣服颜色相同,则单独再穿一件a[i]颜色的衣服
                for(int k=i+1;k<=j;k++)
                    if(a[i] == a[k])//若i舞会和k舞会穿衣颜色相同,那么这种颜色的衣服可以重复利用,将它穿在最底层,所以只就只计算dp[i+1][k]中k舞会的这件衣服
                        dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
            }
        }
        printf("Case %d: %d\n",cas,dp[1][n]);
    }
    return 0;
}

/*
dp[i][j]=dp[i][j-1]+1;
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a[110],dp[110][110],n;

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=dp[i][j-1]+1;
                for(int k=i;k<j;k++)
                    if(a[j] == a[k])
                        dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k][j-1]);
            }
        }
        printf("Case %d: %d\n",cas,dp[1][n]);
    }
    return 0;
}
*/

/*
dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a[110],dp[110][110],n;

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            dp[i][i]=1;
        for(int l=1;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                if(a[i] == a[j])
                    dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
                else{
                    for(int k=i;k<j;k++)
                        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                }
            }
        }
        printf("Case %d: %d\n",cas,dp[1][n]);
    }
    return 0;
}
*/





