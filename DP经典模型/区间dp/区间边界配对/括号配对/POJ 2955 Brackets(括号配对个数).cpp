#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
题意:求字符串中最大匹配括号个数/
链接:http://poj.org/problem?id=2955

思路:这个问题几乎只能借助区间的数组模型,常规不借助空间型结构想不到.
如果找到一对匹配的括号[xxx]oooo，就把区间分成两部分，
一部分是xxx，一部分是oooo.

*/
int main(){
    int dp[120][120],len;
    char s[120];
    while(scanf("%s",s+1)&&strcmp(s+1,"end")!=0){
        len=strlen(s+1);
        memset(dp,0,sizeof(dp));
        for(int l=1;l<len;l++){
            for(int i=1;i+l<=len;i++){
                int j=i+l;
                /*
                dp[i][j]不能记录dp[i][j-1]的原因,因为对分割点k的选取
                是在[i+1,j]之间,也就是若s[i]==s[k]
                dp[i][j]=dp[i+1][k-1]+dp[k+1][j]+2,这个dp[i+1][k-1]+dp[k+1][j]+2,
                是一定大于等于dp[i][j-1]和dp[i+1][j]的,但有种极端情况
                对于s[i]=']'右括号也就是s[i]和s[k]分割点都不相等时,假设s[i+1,j]="[[[[]]]]"
                dp[i][j-1]=6,dp[i+1][j]=8,在无法枚举分割点更新结果时,显然为了保证dp[i][j]的正确性,
                dp[i][j]应记录dp[i+1][j]的值.
                其实就是当s[i]和s[k](i+1<=k<=j)都不相等时,也就是[i+1,j]的区间和i点不能再组成更大匹配数目了,
                [i,j]的括号匹配数就还是原先的[i+1,j]中的数目.
                */
                dp[i][j]=dp[i+1][j];//当s[i]与[i+1,j]没有一个字符括号匹配时,dp[i,j]应该记录区间[i+1,j]的最大括号匹配数即:dp[i+1,j]
                for(int k=i+1;k<=j;k++){
                    /*
                    若括号配对则将区间分割成2部分利用之前小区间的最优值合并成大区间+2,更新最优解
                    */
                     if((s[i]=='('&&s[k]==')')||(s[i]=='['&&s[k]==']'))
                        dp[i][j]=max(dp[i][j],dp[i+1][k-1]+dp[k+1][j]+2);
                }
            }
        }
        printf("%d\n",dp[1][len]);
    }
    return 0;
}
/*
dp[i][j]=dp[i][j-1]
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    int dp[120][120],len;
    char s[120];
    while(scanf("%s",s+1)&&strcmp(s+1,"end")!=0){
        len=strlen(s+1);
        memset(dp,0,sizeof(dp));
        for(int l=1;l<len;l++){
            for(int i=1;i+l<=len;i++){
                int j=i+l;
                dp[i][j]=dp[i][j-1];
                for(int k=i;k<j;k++){
                     if((s[j]==')'&&s[k]=='(')||(s[j]==']'&&s[k]=='['))//用s[j]和s[i~j-1]判断是否构成括号配对,注意s[j]是右括号,s[i~j-1]是左括号
                        dp[i][j]=max(dp[i][j],dp[i][k-1]+dp[k+1][j-1]+2);
                }
            }
        }
        printf("%d\n",dp[1][len]);
    }
    return 0;
}

*/

/*
区间组合合并特殊情形:s[i]==s[j] dp[i][j]=dp[i+1][j-1]+2;
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    int dp[120][120],len;
    char s[120];
    while(scanf("%s",s+1)&&strcmp(s+1,"end")!=0){
        len=strlen(s+1);
        memset(dp,0,sizeof(dp));
        for(int l=1;l<len;l++){
            for(int i=1;i+l<=len;i++){
                int j=i+l;
                if((s[i]=='('&&s[j]==')')||(s[i]=='['&&s[j]==']'))
                    dp[i][j]=dp[i+1][j-1]+2;
                for(int k=i;k<j;k++){
                    //枚举区间分割点,合并大区间求解最优解,但是这个做法忽略了s[i]==s[j]这种情况,也许2+dp[i+1][j-1]更大.
                    dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
                }
            }
        }
        printf("%d\n",dp[1][len]);
    }
    return 0;
}
*/
/*
枚举区间左右端点
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    int dp[120][120],len;
    char s[120];
    while(scanf("%s",s+1)&&strcmp(s+1,"end")!=0){
        len=strlen(s+1);
        memset(dp,0,sizeof(dp));
        for(int i=len-1;i>=1;i--){
            for(int j=i+1;j<=len;j++){
                if((s[i]=='('&&s[j]==')')||(s[i]=='['&&s[j]==']'))
                    dp[i][j]=dp[i+1][j-1]+2;
                for(int k=i;k<j;k++){
                    //枚举区间分割点,合并大区间求解最优解,但是这个做法忽略了s[i]==s[j]这种情况,也许2+dp[i+1][j-1]更大.
                    dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
                }
            }
        }
        printf("%d\n",dp[1][len]);
    }
    return 0;
}
*/
/*
枚举区间右左端点,dp[i][j]=dp[i+1][j]; s[i]==s[k]分割区间
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
    int dp[120][120],len;
    char s[120];
    while(scanf("%s",s+1)&&strcmp(s+1,"end")!=0){
        len=strlen(s+1);
        memset(dp,0,sizeof(dp));
        for(int j=2;j<=len;j++){
            for(int i=j-1;i>=1;i--){
                dp[i][j]=dp[i+1][j];
                for(int k=i+1;k<=j;k++){
                    if((s[i]=='('&&s[k]==')')||(s[i]=='['&&s[k]==']'))
                        dp[i][j]=max(dp[i][j],dp[i+1][k-1]+dp[k+1][j]+2);
                }
            }
        }
        printf("%d\n",dp[1][len]);
    }
    return 0;
}
*/

/*
188ms 记忆化搜索dfs 考虑分割区间dp[a][k]+dp[k+1][b] dp[a][b]=dp[a+1][b-1]+2 这种情形
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int dp[110][110];
char str[110];
int match(int x,int y){
	if((str[x]=='('&&str[y]==')') || (str[x]=='['&&str[y]==']'))
        return 2;
    else return 0;
}
int dfs(int a,int b){
    int result=0;
    if(b<a) return 0;
    if(a==b) return dp[a][b]=0;
    if(b-a==1) return dp[a][b]=match(a,b);
    if(dp[a][b]!=-1) return dp[a][b];
    if(match(a,b))//str[a]==str[b]是遗漏的一种情况 这种情况((()))
        result=dfs(a+1,b-1)+2;
    for(int i=a;i<b;i++)//这里分割区间会少考虑其中一种情况,如str[a]==str[b]时,考虑2+[a+1,b-1]中的最大匹配数
        result=max(dfs(a,i)+dfs(i+1,b),result);
    return dp[a][b]=result;
}
int main(){
    int len;
    while(scanf("%s",str+1),strcmp(str+1,"end")){
        len=strlen(str+1);
        memset(dp,-1,sizeof(dp));
        printf("%d\n",dfs(1,len));
    }
    return 0;
}
*/

/*
//32ms dfs记忆化搜索 枚举分割点a<k<=b考虑[a,b] 若str[a]==str[k] [a+1,k-1]+[k+1,b]+2
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int dp[110][110];
char str[110];
int match(int x,int y){
	if((str[x]=='('&&str[y]==')') || (str[x]=='['&&str[y]==']'))
        return 2;
    else return 0;
}
int dfs(int a,int b){
    int result;
    if(b<a) return 0;
    if(a==b) return dp[a][b]=0;
    if(dp[a][b]!=-1) return dp[a][b];
    result=dfs(a+1,b);//万一str[a]=']'或')',下面的区间就无法拆分那么先计算[a+1,b]中的最大匹配数
    for(int i=a+1;i<=b;i++)
        if(match(a,i))//str[a]和str[i]相等,[a,b]分割成[a+1,i-1]和[i+1,b],每个区间不断分割成最小子问题
            result=max(dfs(a+1,i-1)+dfs(i+1,b)+2,result);
    return dp[a][b]=result;
}
int main(){
    int len;
    while(scanf("%s",str+1),strcmp(str+1,"end")){
        len=strlen(str+1);
        memset(dp,-1,sizeof(dp));
        printf("%d\n",dfs(1,len));
    }
    return 0;
}
*/
