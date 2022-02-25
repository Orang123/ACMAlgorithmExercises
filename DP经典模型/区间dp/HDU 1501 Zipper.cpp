/*
题意:给三个字符串判断第三个字符串能否由前两个按照次序组成,可以交错.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1501
思路:最优子结构是需要枚举第三个字符串中的当前字符和第一个字符串的
当前位置匹配还是第二个字符串的当前位置匹配.
记忆化搜索
dp[l1][l2] 代表在s第三个字符串中s1匹配了l1个,s2匹配了l2个.
重叠子问题是,当前面的状态s1匹配了l1,s2匹配了l2失败后,回溯回来通过
调换s1、s2和s匹配的位置,有可能还会出现s1匹配了l1,s2匹配了l2这种情况,
因此需要记录这个不匹配的结果,直接返回0,避免重复搜索.
*/
//ac 31ms 记忆化搜索
//dp[l1][l2]=1 代表在第三个字符串中s1匹配了l1个,s2匹配了l2个这种情况已被计算过,不能推出s1 s2能组成s3
//时间复杂度O(len1*len2) 因为dp[l1][l2]只会计算一次
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[250][250],len1,len2,len0;
char s1[250],s2[250],s[500];
int dfs(int l1,int l2,int len){

    if(len == len0+1) return 1;//s字符串匹配完毕 结束

    if(dp[l1][l2]) return 0;//如果这种情形已经尝试过,匹配失败,直接返回0
    dp[l1][l2]=1;
    if(s1[l1]==s[len]){//优先匹配s1中的字符,若匹配,则s1和s的下标+1
        if(dfs(l1+1,l2,len+1)) return 1;
    }
    if(s2[l2]==s[len]){//匹配s2的中的字符,若匹配,则s2和s的下标+1
        if(dfs(l1,l2+1,len+1)) return 1;
    }
    return 0;//匹配失败
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s",s1+1);
        scanf("%s",s2+1);
        scanf("%s",s+1);
        len0=strlen(s+1);
        if(dfs(1,1,1)) printf("Data set %d: yes\n",cas);
        else printf("Data set %d: no\n",cas);
    }
    return 0;
}

/*
//ac 31ms 正向dp
//dp[i][j]=1/0表示与s3相对比,s1串按顺序匹配了i个字符,s2串按顺序匹配j个字符为真(1)或假(0)
//这个做法的正确性在于对于s1中的每一位匹配后,s3中的下一位在匹配时 会考虑所有s2中的所有位j,
//同样s2中的第j位也会考虑s1中的所有第i位 从而保证组合结果的正确性.
//这个做法更多地理解为递推,这个过程因为每次i,j都不同,所以几乎是列举了s1、s2中匹配顺序的所有可能情况,所以不存在重叠子问题的情形
#include<cstdio>
#include<cstring>
#define N 210
using namespace std;

char s1[N],s2[N],s3[N<<1];
int cas,dp[N][N];

int main(){
    int T,len1,len2;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s%s%s",s1+1,s2+1,s3+1);
        len1=strlen(s1+1);
        len2=strlen(s2+1);
        dp[0][0]=1;//初始状态,s1,s2串一个字符还未匹配为真
        for(int i=0;i<=len1;i++){//枚举s1中的第i位
            for(int j=0;j<=len2;j++){//枚举s2中的第j位
                //考虑s1中第i个字符是否和s3中i+j个字符匹配,如果上一状态dp[i-1][j]匹配,则一定匹配
                if(i>0 && dp[i-1][j] && s1[i] == s3[i+j])
                    dp[i][j]=1;
                //考虑s2中第j个字符是否和s3中i+j个字符匹配,如果上一状态dp[i][j-1]匹配,则一定匹配
                if(j>0 && dp[i][j-1] && s2[j] == s3[i+j])
                    dp[i][j]=1;
            }
        }
        if(dp[len1][len2])
            printf("Data set %d: yes\n",cas);
        else
            printf("Data set %d: no\n",cas);
    }
    return 0;
}
*/
