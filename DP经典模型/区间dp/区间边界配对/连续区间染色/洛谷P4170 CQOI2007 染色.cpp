#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
题意:假设你有一条长度为5的木板，初始时没有涂过任何颜色。你希望把它的5个单位长度分别涂
上红、绿、蓝、绿、红色，用一个长度为5的字符串表示这个目标：RGBGR。每次你可以把一段连续
的木板涂成一个给定的颜色，后涂的颜色覆盖先涂的颜色。例如第一次把木板涂成RRRRR，第二次涂成RGGGR，
第三次涂成RGBGR，达到目标。用尽量少的涂色次数达到目标。
链接:https://www.luogu.com.cn/problem/P4170
思路:dp[i][j]代表[i,j]内由未染色的空串转化为目标串的[i,j]最少需要的染色次数
实际刷的时候可能是先刷大区间后刷小区间 覆盖染色的情况,但dp是从小的状态小区间开始转移的,
但这不影响这个问题的求解.
对于GBG的分解GBG=min(GB,BG)=2,实际的染法是先把三个都染成G,后把中间的染成B,总共2次
*/

char s[110];
int dp[110][110],len;

int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;//单个字符,只需染一次
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            if(s[i] == s[j])//如果两端点相等,则可在上一次染[i+1,j],[i,j-1]时一次染好s[i]或s[j]
                dp[i][j]=min(dp[i+1][j],dp[i][j-1]);//dp[i+1][j]、dp[i][j-1]可能不同因为s[i+1]和s[j]以及s[i]和s[j-1]的是否相等的情况不同
            else{//否则枚举[i,j]分割点,分成2部分分别染色,即[i,k] [k+1,j]2部分的染色次数之和最小值
                for(int k=i;k<j;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);//因为s[i] s[j]不相等,所以2个分割区间分别都包含s[i] s[j]的染色次数,s[i] s[j]都要单独染一次色
            }
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}

/*
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],len;

int main(){
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int l=0;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            /*
            dp[i][j]=dp[i+1][j]+1,是为了避免下面分割区间没有一个s[k]和s[i]相等时,
            dp[i][j]最坏的一种情况,就是s[i]单独再刷一次色即dp[i+1][j]+1,
            当然dp[i][j]也可以初始化为dp[i][j-1],只是下面的枚举分割点s[k]是和s[j]比较
            */
            /*
            若下面是s[i]和s[k]比较,这里就不能初始化dp[i][j-1],
            因为即使没有一个s[i]和s[k]相等,但也有可能s[j]和i~j-1中的某一个颜色相同,
            这样是有更优的分割点的,这个初始化反而不是最优值.
            */
            /*
            dp[i][j]=dp[i+1][j]+1;
            for(int k=i+1;k<=j;k++)
                if(s[i] == s[k])*/
                    /*
                    理论上枚举分割点若是拿s[i]和s[k]比较,分割区间中就不应出现i,
                    因为s[i]和s[k]是同一颜色,在刷s[k]时顺便就可以刷好s[i].
                    按照实际的刷法,应该是在[i+1,k]刷s[k]时顺便刷好s[i],所以这种转移dp[i+1][k]+dp[k+1][j]
                    更符合实际操作,但是因为我们只是求解最少刷的次数,不管怎么分割,s[i]和s[k]始终只计算刷s[k]的那一次,
                    所以dp[i+1][k-1]+dp[k][j],s[k]也可以算在刷[k,j]区间里的次数,同样还是只计算了一次.
                    */
                    /*
                    dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
                    //dp[i][j]=min(dp[i][j],dp[i+1][k-1]+dp[k][j]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/

/*
dp[i][j]=dp[i][j-1]+1 枚举s[j]和s[k]的关系
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],len;

int main(){
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int l=0;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            dp[i][j]=dp[i][j-1]+1;
            for(int k=i;k<j;k++)
                if(s[j] == s[k])//判断s[j]和s[k]的是否相等来使得s[k] s[j]的颜色只刷一次
                    dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k][j-1]);
                    //dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j-1]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/

/*
枚举区间左右端点 dp[i][j]=dp[i][j-1]+1;
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],len;

int main(){
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int i=len;i>=1;i--){
        for(int j=i;j<=len;j++){
            dp[i][j]=dp[i][j-1]+1;
            for(int k=i;k<j;k++)
                if(s[j] == s[k])
                    dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k][j-1]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/

/*
枚举区间左右端点 dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],len;

int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;
    for(int i=len-1;i>=1;i--){
        for(int j=i+1;j<=len;j++){
            if(s[i] == s[j])
                dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
            else{
                for(int k=i;k<j;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}

*/


