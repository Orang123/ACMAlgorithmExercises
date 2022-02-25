//最长回文子序列(LPS（Longest Palindromic Subsequence）)
//区间dp做法 也可以通过构造串的逆序通过LCS求得
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110];
char a[110];

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            if(a[i] == a[j]) dp[i][j]=dp[i+1][j-1]+2;//若两端点相等,就等于区间[i+1,j-1]最长回文子序列+2
            else dp[i][j]=max(dp[i][j-1],dp[i+1][j]);//若不相等 分为2个区间[i,j-1]、[i+1,j]记录最大值
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}

/*
滚动数组优化空间 枚举区间左右端点 有效,若是枚举右左端点,则dp[i%2][j]=max(dp[(i+1)%2][j-1],dp[i%2][j]),i+1 i %2位置刚好是返过来的
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[2][110];//滚动数组可优化空间复杂度,可解决n>1000的MLE问题.不影响pos数组输出最长回文子序列
char a[110];

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    //这种滚动数组优化只适合区间dp枚举左右端点的状态转移,不适合枚举区间长度和起始点的状态转移,dp[(i+1)%2][j-1]这里的状态会出错
    //只有枚举左右端点的状态转移,下一状态和上一状态左端点为i+1的各个dp[(i+1)%2][j]有关和本次状态dp[i%2][j-1]有关
    for(int i=len-1;i>=1;i--){
        //这里是为了方便长度为3回文子序列的计算,中间单个的字符算长度为1的回文子序列,这个状态在下一个左端点为i+1计算[i+1,i+3]时会用到
        dp[i%2][i]=1;
        for(int j=i+1;j<=len;j++){
            if(a[i]== a[j]) dp[i%2][j]=dp[(i+1)%2][j-1]+2;//i%2代表当前的状态,(i+1)%2是上一状态
            //dp[i%2][j-1]是上一次j-1循环计算出的区间,dp[(i+1)%2][j]是上一个状态左端点为i+1时到j的区间的值
            else dp[i%2][j]=max(dp[i%2][j-1],dp[(i+1)%2][j]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/

/*
//输出最长回文子序列
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int pos[110][110],dp[110][110];//记录最长回文子序列所在的区间
char a[110];

void output(int i,int j){
    if(i>j) return;//最长回文子序列已遍历完毕
    if(i == j){//只剩下一个字符时,说明长度时奇数,以该字符为中心对称
        printf("%c",a[i]);
        return;
    }
    if(pos[i][j] == 1){//两端点相等就输出
        printf("%c",a[i]);
        output(i+1,j-1);
        printf("%c",a[j]);
    }
    else if(pos[i][j] == 2)
        output(i,j-1);
    else if(pos[i][j] == 3)
        output(i+1,j);
}

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            if(a[i] == a[j]){
                dp[i][j]=dp[i+1][j-1]+2;
                pos[i][j]=1;
            }
            else{
                if(dp[i][j-1]>dp[i+1][j]){
                    dp[i][j]=dp[i][j-1];
                    pos[i][j]=2;
                }
                else{
                    dp[i][j]=dp[i+1][j];
                    pos[i][j]=3;
                }
            }
        }
    }
    output(1,len);
    return 0;
}
*/

/*
记忆化搜索 最长回文子序列
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110];
char a[110];

int dfs(int i,int j){
    if(i>j) return 0;
    if(dp[i][j]) return dp[i][j];
    if(a[i] == a[j])
        dp[i][j]=dfs(i+1,j-1)+2;
    else
        dp[i][j]=max(dfs(i,j-1),dfs(i+1,j));
    return dp[i][j];
}

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;
    printf("%d",dfs(1,len));
    return 0;
}
*/

/*
/*
滚动数组 对枚举区间长度后枚举起始点的区间dp不能生效,dp[(i+1)%2][j-1]这里的状态会出错 下面代码是错误的
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[2][110];
char a[110];

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            dp[i%2][i]=1;
            int j=i+l;
            if(a[i] == a[j]) dp[i%2][j]=dp[(i+1)%2][j-1]+2;//dp[(i+1)%2][j-1]表示的并不是dp[i+1][j-1],实际表示的是dp[i-1][j-1]
            else dp[i%2][j]=max(dp[i%2][j-1],dp[(i+1)%2][j]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/
