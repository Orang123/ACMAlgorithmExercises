/*
题意:三种操作：插入，删除，修改，问最少操作次数使得第一个串变成第二个串
字符串长度<=1000.
链接:http://poj.org/problem?id=3356
思路:LCS.最长长度减去LCS长度,max(n,m)-dp[n][m].
*/
//ac 16ms 最长长度减去LCS长度,max(n,m)-dp[n][m]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,m,dp[N][N];
char a[N],b[N];

int main(){
    int len;
    while(scanf("%d %s",&n,a+1)!=EOF){
        scanf("%d %s",&m,b+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i]==b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        len=max(n,m);
        printf("%d\n",len-dp[n][m]);
    }
    return 0;
}

/*
//ac 0ms
//下述思路摘自博客:https://blog.csdn.net/u013480600/article/details/40780781
//dp[i][j] 为a串的前i部分变成b串的前j部分所需要的最小操作数
//初始状态: dp[0][i]==i且 dp[i][0]=i. 上述前者表示添加a串i个字符, 后者表示删除a串i个字符.
//状态转移: dp[i][j]如果我们只在源串的末尾进行3种操作,那么有下面3种情况.
//1.dp[i-1][j-1]+(x[i]==y[j]?0:1).即如果源串和目串最后一个字符相同, 自然dp[i-1][j-1]就是所求.
//如果他们最后一个字符不同, 那么可以替换源串的最后一个字符成目串的那个字符.
//2.dp[i-1][j]+1.我们可以删除源串最后一个字符(1步删除操作), 然后将源串变成目串(dp[i-1][j]步操作).
//3.dp[i][j-1]+1.我们可以将源串变成目串的前j-1个字符的串(dp[i][j-1]步操作),然后在源串末尾再添加一个b[j]即变成了目串(1步操作).
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,m,dp[N][N];
char a[N],b[N];

int main(){
    int len;
    for(int i=0;i<N;i++)
    	dp[i][0]=dp[0][i]=i;
    while(scanf("%d %s",&n,a+1)!=EOF){
        scanf("%d %s",&m,b+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
            	dp[i][j]=dp[i-1][j-1]+(a[i] == b[j]?0:1);
            	dp[i][j]=min(dp[i][j],min(dp[i-1][j]+1,dp[i][j-1]+1));
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
*/
