#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
int dp[1100][1100];
char a[1100];
/*
题意:求出一个字符串里含有多少回文子序列.
提示:子序列不一定要连续,下标可以分隔.
如:aaa 含有7个回文子序列,a(3个) aa(2个([12][23])+1个([13])) aaa([123])
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4632
传统的暴力不知如何下手.几乎只能从小的状态转移到大的状态,才能解决此问题.
思路:这个回文的问题,在状态转移的时候,只是单方面分隔区间求和求出的并不是最优解,
如[1,6]=[1,3]+[4,6]这样只能求出[1,3]和[4,6]2个区间的回文子序列的个数总和,
对于[1,3]和[4,6]区间内字符可以相互组合构成新的回文子序列.
如对aaa而言如果只计算组合最优解max([1,1]+[2,3],[1,2]+[3,3])=4
只计算了一个aa,对于[1,1][2,3]除了[2,3]的aa外,s它无法考虑[1,2]这个aa,第二种分割方案同理.
所以可以采取容斥原理dp[i][j]=max(dp[i][j],dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1]);,这样中间交互的部分就都能计算进去.
*/
//枚举区间长度起始点
int main(){
    int T,len,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s",a+1);
        len=strlen(a+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;
        for(int l=1;l<len;l++){
            for(int i=1;i+l<=len;i++){
                int j=i+l;
                /*
                容斥原理 这里刚好会把中间的部分多计算一次,所以要减掉.
                dp[i][j-1]、dp[i+1][j]、dp[i+1][j-1]已经是取模后的结果了,
                所以大小情况并不确定,减去dp[i+1][j-1]有可能结果为负,
                所以要再加上mod后再取模.
                */
                dp[i][j]=(dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1]+mod)%mod;
                if(a[i] == a[j])
                /*
                如果新区间的左右端点相同,则a[i]a[j]可构成一个回文子序列+1,
                并且它还可和中间的a[i+1][j-1]的回文子序列再度组合构成新的回文子序列,
                因此要再加上dp[i+1][j-1].
                */
                    dp[i][j]=(dp[i][j]+dp[i+1][j-1]+1)%mod;
            }
        }
        printf("Case %d: %d\n",cas,dp[1][len]);
    }
	return 0;
}
/*
枚举左右2端点dp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
int dp[1100][1100];
char a[1100];

int main(){
    int T,len,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s",a+1);
        len=strlen(a+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;
        for(int i=len-1;i>=1;i--){
            for(int j=i+1;j<=len;j++){
                dp[i][j]=(dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1]+mod)%mod;
                if(a[i] == a[j])
                    dp[i][j]=(dp[i][j]+dp[i+1][j-1]+1)%mod;
            }
        }
        printf("Case %d: %d\n",cas,dp[1][len]);
    }
	return 0;
}
*/
/*
记忆化搜索
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
int dp[1100][1100];
char a[1100];

int dfs(int st,int ed){
    if(st == ed) return dp[st][ed]=1;
    if(st>ed) return 0;
    if(dp[st][ed]) return dp[st][ed];
    //一定要先计算容斥这部分的答案,这样dp[st+1][ed-1]可以直接用结果
    //否则先计算dfs(st+1,ed-1),dp[st+1][ed] dp[st][ed-1]还需要重新递归计算.
    dp[st][ed]=(dfs(st,ed-1)+dfs(st+1,ed)-dp[st+1][ed-1]+mod)%mod;
    if(a[st] == a[ed])
        dp[st][ed]=(dp[st][ed]+dp[st+1][ed-1]+1)%mod;
    return dp[st][ed];
}

int main(){
    int T,len,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s",a+1);
        len=strlen(a+1);
        printf("Case %d: %d\n",cas,dfs(1,len));
    }
	return 0;
}
*/
