#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
/*
链接:http://poj.org/problem?id=3186
题意:n个数排成一行,每次只能取首部或尾部所产生的贡献为所取的数值*取得次数,求取完所有数的最大贡献.
思路:首先贪心不行,即使每次都取较小的数,将较大的数放在次数较大的时候,但是取走较小数后新的首部尾部元素也许更大,
显然贪心不行,再考虑传统的爆搜,对于一行的数每次取分两种选择,要么取首部要么取尾部,总共取n次,那么时间复杂度O(2^n),
本题n=2000,,2^(2000)显然也超时.
综上,思路肯定还是暴力,只是不能直接按一般的暴力方案枚举可能性,可以采用区间去模拟取的过程,只不过从里向外取,反着进行这个过程,区间dp.
dp[i][j]代表[i,j]内取数从末尾向前取数所产生最大贡献
*/
//枚举长度 起始端点的区间dp
int dp[2100][2100],a[2100];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int l=0;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            //因为只能取首部或尾部 所以不能再枚举分割点k
            //尝试a[i]或a[j]作为第(n-l)次取的数字 求取dp[i][j]最大值
            dp[i][j]=max(dp[i][j],dp[i][j-1]+a[j]*(n-l));
            dp[i][j]=max(dp[i][j],dp[i+1][j]+a[i]*(n-l));
        }
    }
    printf("%d",dp[1][n]);
	return 0;
}

/*
正向从大区间向小区间dp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[2100][2100],a[2100];
int main(){
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);

    //从大区间向小区间dp,dp[i][j]只能由两个区间推移过来 分别是dp[i-1][j]和dp[i][j+1],
    //若是由dp[i-1][j]而来,说明本次要取a[i-1]这个数,对应的是取第(n-l-1)个数
    //若是由dp[i][j+1]而来,说明本次要取a[j+1]这个数,对应的是取第(n-l-1)个数
    //长度从n-1开始,因为第一次取完后,长度时n-1,当l==0,即只剩下一个数时,计算的是取第n-1个数,所以dp最后还剩下最后一个数没取
    //这个也充分体现的dp的无后效性,后面的计算可以直接使用这个结果，而无需考虑子问题里面对后面计算的影响
    //即某个区间[i,j]后面的取法和前面dp[i-1][j] do[i][j+1]没有关系,只是对于dp[i][j]的最优值可以根据dp[i-1][j] do[i][j+1]来求解
    for(int l=n-2;l>=0;l--){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            dp[i][j]=max(dp[i-1][j]+a[i-1]*(n-l-1),dp[i][j+1]+a[j+1]*(n-l-1));
        }
    }
    for(int i=1;i<=n;i++)//再取剩下的最后一个数,第n次取
        ans=max(ans,dp[i][i]+n*a[i]);
    printf("%d",ans);
	return 0;
}
*/

/*
枚举区间左右端点的区间dp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[2100][2100],a[2100];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=n;i>=1;i--){
        for(int j=i;j<=n;j++){
            int l=j-i;
            dp[i][j]=max(dp[i][j],dp[i][j-1]+a[j]*(n-l));
            dp[i][j]=max(dp[i][j],dp[i+1][j]+a[i]*(n-l));
        }
    }
    printf("%d",dp[1][n]);
	return 0;
}
*/

/*
记忆化搜索 [i,j]是初始问题,[i+1,j] [i,j-1]是子问题 由大区间分解小区间
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[2100][2100],a[2100];

int dfs(int st,int ed,int num){
    if(st == ed) return dp[st][ed]=a[st]*num;
    if(dp[st][ed]) return dp[st][ed];
    //大的方案上就是假定[st+1,ed]和[st,ed-1]已求出,然后先取a[st]或a[ed],递归优先求取子区间的贡献,直到st==ed最后一次取完最小子问题完成,开始回溯.
    dp[st][ed]=max(dp[st][ed],dfs(st+1,ed,num+1)+a[st]*num);
    dp[st][ed]=max(dp[st][ed],dfs(st,ed-1,num+1)+a[ed]*num);
    return dp[st][ed];;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    printf("%d",dfs(1,n,1));
	return 0;
}
*/

/*
记忆化搜索 [i,j]是初始问题,[i-1,j] [i,j+1]是子问题 由小区间分解大区间
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,dp[2100][2100],a[2100];

int dfs(int i,int j){
    //当i==0或j==n+1超出区间边界点或是[1,n]初试状态一个数还没取(j-i==n-1) 返回0
    if(!i || j==n+1 || j-i==n-1) return 0;
    if(dp[i][j]) return dp[i][j];
    dp[i][j]=max(dfs(i-1,j)+a[i-1]*(n-j+i-1),dfs(i,j+1)+a[j+1]*(n-j-1+i));
    return dp[i][j];
}

int main(){
    int ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)//再取剩下的最后一个数,第n次取
        ans=max(ans,dfs(i,i)+a[i]*n);
    printf("%d",ans);
	return 0;
}

*/

