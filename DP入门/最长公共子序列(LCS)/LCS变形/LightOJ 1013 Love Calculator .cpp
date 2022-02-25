/*
题意:此题和UVA10723 Cyborg Genes以同一道题
摘自网上
给你两个字符串a，b，问存在多少个这样的字符串。这样的字符串是指
字符串a和字符串b都是该字符串的子序列，且这样的字符串要求长度最小。
输出这样的字符串的长度和存在多少个
字符串长度<=30.
链接:http://www.lightoj.com/volume_showproblem.php?problem=1013
思路:LCS变形.实际最短的串要使得a、b是其子序列,那么最短的串就是
ab的LCS加上a、b字符串剩余的部分,则最短长度为len(a)+len(b)-LCS(a,b),
因为len(a)+len(b)将LCS(a,b)多加了一次.
dp[i][j]表示a的前i个字符和b的前j个字符LCS的最大长度.
num[i][j]表示a的前i个字符和b的前j个字符所能构成LCS的个数.
*/
//ac 3ms 正向dp LCS
//dp[i][j]表示a串的前i个元素和b串的前j个元素的LCS的长度
//num[i][j]表示对应满足dp[i][j]的LCS的方案个数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;
typedef long long ll;

int n,m,dp[N][N];
ll num[N][N];
char a[N],b[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",a+1);
        scanf("%s",b+1);
        n=strlen(a+1);
        m=strlen(b+1);
        memset(num,0,sizeof(num));
        num[0][0]=1;//初始状态
        for(int i=1;i<=n;i++)
            num[i][0]=1;
        for(int i=1;i<=m;i++)
            num[0][i]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i] == b[j]){
                    dp[i][j]=dp[i-1][j-1]+1;
                    num[i][j]=num[i-1][j-1];
                }
                else{
                    if(dp[i-1][j]>dp[i][j-1]){
                        dp[i][j]=dp[i-1][j];
                        num[i][j]=num[i-1][j];
                    }
                    else if(dp[i-1][j]<dp[i][j-1]){
                        dp[i][j]=dp[i][j-1];
                        num[i][j]=num[i][j-1];
                    }
                    else{
                        dp[i][j]=dp[i][j-1];
                        num[i][j]=num[i-1][j]+num[i][j-1];
                    }
                }
            }
        }
        printf("Case %d: %d %lld\n",cas,n+m-dp[n][m],num[n][m]);
    }
    return 0;
}

/*
//ac 4ms 记忆化搜索
//dp[i][j]表示a串的前i个元素和b串的前j个元素的LCS的长度
//num[i][j]表示对应满足dp[i][j]的LCS的方案个数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;
typedef long long ll;

int n,m,dp[N][N];
ll num[N][N];
char a[N],b[N];

int dfs(int i,int j){
	if(!i || !j){
		dp[i][j]=0;
		num[i][j]=1;
		return 0;
	}
	if(dp[i][j]!=-1)
		return dp[i][j];
	if(a[i] == b[j]){
		dp[i][j]=dfs(i-1,j-1)+1;
		num[i][j]+=num[i-1][j-1];
	}
	else{
		dfs(i-1,j);
		dfs(i,j-1);
		if(dp[i-1][j]>dp[i][j-1]){
            dp[i][j]=dp[i-1][j];
            num[i][j]=num[i-1][j];
        }
        else if(dp[i-1][j]<dp[i][j-1]){
            dp[i][j]=dp[i][j-1];
            num[i][j]=num[i][j-1];
        }
    	else{
            dp[i][j]=dp[i][j-1];
            num[i][j]+=num[i-1][j]+num[i][j-1];
        }
	}
	return dp[i][j];
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",a+1);
        scanf("%s",b+1);
        n=strlen(a+1);
        m=strlen(b+1);
        memset(dp,-1,sizeof(dp));
        memset(num,0,sizeof(num));
        dfs(n,m);
        printf("Case %d: %d %lld\n",cas,n+m-dp[n][m],num[n][m]);
    }
    return 0;
}
*/

/*
//ac 4ms
//dp[i][j]表示构成的目标字符串的最小长度.
//num[i][j]表示所能构成目标字符串的方案个数.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;
typedef long long ll;

int n,m,dp[N][N];
ll num[N][N];
char a[N],b[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",a+1);
        scanf("%s",b+1);
        n=strlen(a+1);
        m=strlen(b+1);
        memset(num,0,sizeof(num));
        num[0][0]=1;//初始状态
        for(int i=1;i<=n;i++){
        	dp[i][0]=i;//初始状态,a串的前i个还未匹配,因此至少还需要i长度 这个写成记忆化搜索可能好理解点
            num[i][0]=1;//表示一个可行方案的初始状态
		}
        for(int i=1;i<=m;i++){
        	dp[0][i]=i;//初始状态,b串的前i个还未匹配,因此至少还需要i长度
            num[0][i]=1;
		}
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i] == b[j]){
                    dp[i][j]=dp[i-1][j-1]+1;
                    num[i][j]=num[i-1][j-1];
                }
                else{
                	dp[i][j]=min(dp[i-1][j],dp[i][j-1])+1;//求取目标串的最小长度 再加上不在LCS里的a[i]或b[j]
                    if(dp[i-1][j]>dp[i][j-1])
                        num[i][j]=num[i][j-1];//记录最小长度的目标串的方案数
                    else if(dp[i-1][j]<dp[i][j-1])
                        num[i][j]=num[i-1][j];
                    else
                        num[i][j]=num[i-1][j]+num[i][j-1];
                }
            }
        }
        printf("Case %d: %d %lld\n",cas,dp[n][m],num[n][m]);
    }
    return 0;
}
*/
