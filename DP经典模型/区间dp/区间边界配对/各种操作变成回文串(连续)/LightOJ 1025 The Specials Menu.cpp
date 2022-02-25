/*
题意:摘自网上
一串字符， 通过删除其中一些字符， 能够使这串字符变成回文串。
现在给你一串字符，问能够得到多少种不同的回文串；
注意：字符串"abba", 可以得到9串回文串，分别为'a', 'a', 'b', 'b', 'aa', 'bb', 'aba', 'aba', 'abba'.
字符串长度<=60.
链接:http://www.lightoj.com/volume_showproblem.php?problem=1025
思路:摘自https://www.cnblogs.com/aiterator/p/5875206.html
声明dp[i][j]为字符串[i,j]区间中通过删除可以得到不同回文串的数量
那么有以下两种情况：
1：当str[i] != str[j]时， dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1];
（之所以减去dp[i+1][j-1] 是前面两项多加了一个dp[i+1][j-1]）,是公共重叠部分
2：当str[i] == str[j]时， dp[i][j] = (dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]) + (dp[i+1][j-1] + 1);
（前面一项是指str[i]和str[j]不对应时能够组成回文串的方案数，第二项是指str[i]和str[j]对应时能够组成回文串的方案数）
实际并不需要真得删去字符,实际就是通过判断区间两端点计算可能构成的回文子串的数目.
*/
//ac 5ms 记忆化搜索(区间dp)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
typedef long long ll;
using namespace std;

ll dp[N][N];
char str[N];

ll dfs(int l,int r){
    ll &res=dp[l][r];
    if(res!=-1)
        return res;
    if(l == r)
        return res=1;
    if(l>r)
        return res=0;
    if(str[l]!=str[r])
        res=dfs(l+1,r)+dfs(l,r-1)-dfs(l+1,r-1);
    else
        res=dfs(l+1,r)+dfs(l,r-1)+1;
    return res;
}

int main(){
    int T,len;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(dp,-1,sizeof(dp));
        scanf("%s",str+1);
        len=strlen(str+1);
        printf("Case %d: %lld\n",i,dfs(1,len));
    }
    return 0;
}

/*
//ac 4ms 正向区间dp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
typedef long long ll;
using namespace std;

ll dp[N][N];
char str[N];

int main(){
    int T,len;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(dp,0,sizeof(dp));
        scanf("%s",str+1);
        len=strlen(str+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;
        for(int l=1;l<len;l++){
            for(int i=1;i<len;i++){
                int j=i+l;
                if(str[i]!=str[j])
                    dp[i][j]=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
                else
                    dp[i][j]=dp[i+1][j]+dp[i][j-1]+1;
            }
        }
        printf("Case %d: %lld\n",i,dp[1][len]);
    }
    return 0;
}
*/
