/*
题意:摘自网上
给出一个字符串，有三种操作（任意位置删除、增加、替换一个字符），
问需要最少的操作次数使其变为回文串。
字符串个数<=1000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1680
思路:区间dp,记忆化搜索实现.
对于删除操作和增加操作本质是一样的.
dp[l][r]表示要使得区间[l,r]成为回文串至少要操作的次数.
*/
//ac 0ms 记忆化搜索
//时间复杂度(1000*1000)=10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int dp[N][N];
char str[N];

int dfs(int l,int r){
    if(dp[l][r] != -1)
        return dp[l][r];
    if(l>=r)
        return dp[l][r]=0;
    if(str[l] == str[r])//左右区间字符相等,无需再操作,操作次数为区间[l+1,r-1]的操作次数.
        dp[l][r]=dfs(l+1,r-1);
    else
        //左右区间不等,有三种操作方式使其成为回文
        //1.修改str[l]或str[r]使得str[l]==str[r],即:dp[l+1][r-1]+1
        //2.删除str[l],[l+1,r]本身是回文或在str[r]后再添加一个和str[l]相等的字符,即:dp[l+1][r]+1
        //3.删除str[r],[l,r-1]本身是回文或在str[l]前再添加一个和str[r]相等的字符,即:dp[l][r-1]+1
        dp[l][r]=min(dfs(l+1,r-1),min(dfs(l+1,r),dfs(l,r-1)))+1;
    return dp[l][r];
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,-1,sizeof(dp));
        scanf("%s",str+1);
        printf("Case %d: %d\n",cas,dfs(1,strlen(str+1)));
    }
    return 0;
}

/*
//ac 0ms 正向dp 枚举区间长度、起始点
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int dp[N][N],len;
char str[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",str+1);
        len=strlen(str+1);
        memset(dp,0,sizeof(dp));
        for(int l=1;l<len;l++){
        	for(int i=1;i+l<=len;i++){
        		int j=i+l;
        		if(str[i] == str[j])
        			dp[i][j]=dp[i+1][j-1];
        		else
        			dp[i][j]=min(dp[i+1][j-1],min(dp[i+1][j],dp[i][j-1]))+1;
			}
		}
		printf("Case %d: %d\n",cas,dp[1][len]);
    }
    return 0;
}
*/

/*
//ac 0ms 正向dp 枚举左右端点
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int dp[N][N],len;
char str[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",str+1);
        len=strlen(str+1);
        memset(dp,0,sizeof(dp));
        for(int i=len-1;i>=1;i--){
        	for(int j=i+1;j<=len;j++){
        		if(str[i] == str[j])
        			dp[i][j]=dp[i+1][j-1];
        		else
        			dp[i][j]=min(dp[i+1][j-1],min(dp[i+1][j],dp[i][j-1]))+1;
			}
		}
		printf("Case %d: %d\n",cas,dp[1][len]);
    }
    return 0;
}
*/
