/*
LCS-Longest Common Subsequence(最长公共子序列)
题意:一个字符串，问最少添加几个字符，可以使之成为回文串.
链接:http://poj.org/problem?id=1159
思路:求字符串及其逆序串的最长公共子序列（LCS）,再用n-这个LCS就是答案.
dp[i][j]表示正序列的前i个元素和逆序列的前j个元素的LCS长度
注意:因为n=5000时，n*n=25M,空间复杂度太高
滚动数组优化空间复杂度 不过无法输出LCS字符串
注意到dp[i][j]只和dp[i-1][j-1],dp[i-1][j],dp[i][j-1]三个值相关，
我们可以只保留两行的数据即可，这样使用两个数组滚动计算即可。
这里dp采用了滚动数组优化.

LCS dp详解博客:https://www.cnblogs.com/moomcake/p/9385170.html
*/
/*
输入
5
Ab3bd
11
abbdsadsaab

输出
2
6
*/
//ac 1532ms
//时间复杂度O(n^2)
//空间复杂度 未采用滚动数组优化:O(n^2),采用滚动数组优化O(2*n)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[2][5010];

int main(){
    int n;
    char s[5010],a[5010],b[5010];
    while(scanf("%d",&n)!=EOF){
        scanf("%s",s+1);
        memset(dp,0,sizeof(dp));
        for(int i=1,j=n;i<=n;i++,j--){
            a[i]=s[i];//a数组存放正序列
            b[j]=s[i];//b数组倒序存放逆序列
        }
        /*
        i为偶数时 i%2=0,i-1就为奇数 (i-1)%2为1,这样dp[0][j]由dp[1][j]转移而来,
        然后i++后又为奇数,i%2=1,i-1为偶数 (i-1)%2=0,dp[1][j]又由dp[0][j]转移而来,
        而dp[0][j]就是上一次i-1所转移后的状态,依次类推.
        */
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i]==b[j])//a[i] b[j]相等时,dp[i][j]=dp[i-1][j-1]+1;
                    dp[i%2][j]=dp[(i-1)%2][j-1]+1;
                else
                    dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][j-1]);
            }
        }
        printf("%d\n",n-dp[n%2][n]);
    }
    return 0;
}

/*
无滚动数组优化
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[5100][5010];//会MLE 空间超出限制 25M 最大只能1M 1000000

int main(){
    int n;
    char s[5010],a[5010],b[5010];
    while(scanf("%d",&n)!=EOF){
        scanf("%s",s+1);
        memset(dp,0,sizeof(dp));
        for(int i=1,j=n;i<=n;i++,j--){
            a[i]=s[i];
            b[j]=s[i];
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i]==b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printf("%d\n",n-dp[n][n]);
    }
    return 0;
}
*/


/*
//记忆化搜索
//记忆化搜索无法用滚动数组优化空间
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110];
char s[110],a[110],b[110];
int dfs(int i,int j){
    if(!i || !j) return dp[i][j]=0;//当正序列或逆序列长度为0时,LCS返回0
    if(dp[i][j]!=-1) return dp[i][j];
    if(a[i] == b[j])
        dp[i][j]=dfs(i-1,j-1)+1;
    else
        dp[i][j]=max(dfs(i-1,j),dfs(i,j-1));//若a[i]!=b[j] dp[i][j]只取dp[i-1][j]和dp[i][j-1]的最大值
    return dp[i][j];
}

int main(){
    int n;
    while(scanf("%d",&n)!=EOF){
        scanf("%s",s+1);
        memset(dp,-1,sizeof(dp));//0可能也是合法状态,因此初始状态设置为-1
        for(int i=1,j=n;i<=n;i++,j--){
            a[i]=s[i];
            b[j]=s[i];
        }
        printf("%d\n",n-dfs(n,n));
    }
    return 0;
}
*/

/*
//打印LCS字符串
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],pos[110][110];
char a[110],b[110];
//打印LCS字符串
void printLCS(int st,int ed){
    if(!st || !ed) return;//当a或b字符串的长度为0时,LCS必为0 结束
    if(pos[st][ed] == 1){//说明a[st] b[ed]是LCS中的元素,这里从LCS第一个元素开始输出,所以回溯后再输出后面的LCS的元素.
        printLCS(st-1,ed-1);
        printf("%c",a[st]);
    }
    else if(pos[st][ed] == 2)//朝着实际LCS(长度最大)所在的区间遍历
        printLCS(st-1,ed);
    else if(pos[st][ed] == 3)
        printLCS(st,ed-1);
}

int main(){
    int len1,len2;
    scanf("%s",a+1);
    scanf("%s",b+1);
    len1=strlen(a+1);
    len2=strlen(b+1);
    for(int i=1;i<=len1;i++){
        for(int j=1;j<=len2;j++){
            if(a[i] == b[j]){
                dp[i][j]=dp[i-1][j-1]+1;
                pos[i][j]=1;//a[i]==a[j] 代表a[i]是LCS中的元素,代表要输出
            }
            else{
                if(dp[i-1][j]>dp[i][j-1]){
                    dp[i][j]=dp[i-1][j];
                    pos[i][j]=2;//[i-1,j]比[i,j-1]LCS的长度更大
                }
                else{
                    dp[i][j]=dp[i][j-1];
                    pos[i][j]=3;//[i,j-1]比[i-1,j]LCS的长度更大
                }
            }
        }
    }
    printLCS(len1,len2);
    return 0;
}
*/
