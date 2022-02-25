#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
题意:给一个长度相等的字符串,每次可以将初始串一段连续的子串刷成同一颜色,后刷的颜色会覆盖先刷的颜色,
问将初始串刷成目标串,需要刷的最少的次数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2476
思路:dp[i][j]代表[i,j]内由未染色的空串转化为目标串s2的[i,j]最少需要的染色次数
实际刷的时候可能是先刷大区间后刷小区间 覆盖染色的情况,但dp是从小的状态小区间
开始转移的,但这不影响这个问题的求解.
ans[i]代表前i个字符由s1转向s2需要刷的最少次数.
*/

char s1[110],s2[110];
int dp[110][110],ans[110],len;

int main(){
    while(scanf("%s",s1+1)!=EOF){
        scanf("%s",s2+1);
        memset(dp,0x3f,sizeof(dp));
        len=strlen(s2+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;//单个字符,只需染一次
        for(int l=1;l<len;l++){
            for(int i=1;i+l<=len;i++){
                int j=i+l;
                if(s2[i] == s2[j])//如果两端点相等,则可在上一次染[i+1,j],[i,j-1]时一次染好s[i]或s[j]
                    dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
                else{//否则枚举[i,j]分割点,分成2部分分别染色,即[i,k] [k+1,j]2部分的染色次数之和最小值
                    for(int k=i;k<j;k++)
                        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                }
            }
        }
        for(int i=1;i<=len;i++)
            ans[i]=dp[1][i];//ans[i]初始化为由空串转化为s2的状态,这是最坏的情形,即ans[i]理论上的最大值
        for(int i=1;i<=len;i++){
            if(s1[i] == s2[i])//如果初始串和目标串当前字符相同,则要刷的次数等于前i-1个状态要刷的次数
                ans[i]=ans[i-1];
            else{//若不相等,则枚举分割点j,由前面的子串ans[j](初始串s1)+[j+1,i](由空白串转移到s2的次数)
                for(int j=1;j<i;j++)
                    ans[i]=min(ans[i],ans[j]+dp[j+1][i]);//这个地方的依据看不太懂
            }
        }
        printf("%d\n",ans[len]);
    }
    return 0;
}
/*
一位网友“defKaeru”关于ans[j]+dp[j+1][i] s1转移到s2的刷次数的理解
初始串不会比空串更劣
在前缀区间 [1, i] 中，可以保证在这之前的区间都转移过，现在要以之前的区间为基础拓展一位
于是把区间 [1, i] 分成两段，[1, j] 是被当作初始串对待，[j+1, i] 被当作空白串对待；
这么做的正确性在于如果只把一个非前缀区间 [j, k] 当作初始串看待一定不会比把一个前缀区间 [1, j] 当作初始串看待更优
而后面的部分 [j+1, i]，再去讨论和目标串的相同部分很麻烦，所以不妨当作空白串；如果有相同部分，
会在枚举到更后面的断点时被考虑到。
*/
/*
枚举左右端点的区间dp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s1[110],s2[110];
int dp[110][110],ans[110],len;

int main(){
    while(scanf("%s",s1+1)!=EOF){
        scanf("%s",s2+1);
        memset(dp,0,sizeof(dp));
        len=strlen(s2+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;
        for(int i=len-1;i>=1;i--){
            for(int j=i+1;j<=len;j++){
                dp[i][j]=dp[i+1][j]+1;//这里是初始化dp[i][j]最坏的情况,如果s[i]和s[k]不相等,是多刷一次s2[i]的颜色
                for(int k=i+1;k<=j;k++){
                    if(s2[i] == s2[k])//若s2[i]和s2[k]相等 区间分割成dp[i+1,k]+dp[k+1,j]在刷[i+1,k]的时候就顺便刷s2[i],这样没必要再单独多刷一次s2[i]
                        dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
                }
            }
        }
        for(int i=1;i<=len;i++)
            ans[i]=dp[1][i];
        for(int i=1;i<=len;i++){
            if(s1[i] == s2[i])
                ans[i]=ans[i-1];
            else{
                for(int j=1;j<i;j++)
                    ans[i]=min(ans[i],ans[j]+dp[j+1][i]);
            }
        }
        printf("%d\n",ans[len]);
    }
    return 0;
}
*/


