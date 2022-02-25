/*
题意:求a数组和b数组的最长公共上升子序列(LCIS).
数组长度<=500.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1423
思路:O(n^2)求取LCIS模板.
dp[i][j]为当串a取前i个元素时(设为a[1 ~ i]),且当串b的子序列以j结尾时,它们的最长公共子序列长度.
dp[i][j]>=dp[i-1][j].
数组长度为500,按道理O(n^3)的做法会TLE才对,但是也过了.
算法参考博客:https://blog.csdn.net/lycheng1215/article/details/78343769
*/
//ac 0ms LCIS 二维数组实现 O(n*m)
//dp[i][j]为当串a取前i个元素时(设为a[1 ~ i]),且当串b的子序列以j结尾时,它们的最长公共子序列长度.
//dp[i][j]>=dp[i-1][j]
#include<cstdio>
#include<algorithm>
#define N 510
using namespace std;

int n,m,a[N],b[N],dp[N][N],ans;

int main(){
    int T,mx;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            mx=0;//记录最大的dp[i-1][1..j]的值
            for(int j=1;j<=m;j++){
                dp[i][j]=dp[i-1][j];
                if(a[i]>b[j])//记录最大的以j结尾之前的字符的LIS
                    mx=max(mx,dp[i-1][j]);
                else if(a[i] == b[j])//当构成LCS时,dp[i][j]=之前记录的j之前的最大的LIS
                    dp[i][j]=mx+1;
            }
        }
        ans=0;
        for(int i=1;i<=m;i++)//记录最长的LCIS,a数组的前n个元素,枚举b数组以b[i]结尾的LCIS 记录最大长度
            ans=max(ans,dp[n][i]);
        printf("%d\n",ans);
        if(T)
            printf("\n");
    }
    return 0;
}

/*
//ac 0ms O(n*m) 滚动数组优化,一维数组实现
//因为dp[i][j]的求取之和dp[i-1][j]有关,因此第一个维度可以省略,只是要初始化dp一维数组,否则多组样例,上一次的结果会影响下一次的结果
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
using namespace std;

int n,m,a[N],b[N],dp[N],ans;

int main(){
    int T,mx;
    scanf("%d",&T);
    while(T--){
    	memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            mx=0;
            for(int j=1;j<=m;j++){
                if(a[i]>b[j])
                    mx=max(mx,dp[j]);
                else if(a[i] == b[j])
                    dp[j]=mx+1;
            }
        }
        ans=0;
        for(int i=1;i<=m;i++)
            ans=max(ans,dp[i]);
        printf("%d\n",ans);
        if(T)
            printf("\n");
    }
    return 0;
}
*/

/*
//ac 0ms 二维数组O(n*m^2)朴素做法
//数组长度为500,按道理O(n^3)的做法会TLE才对,但是也过了.
//dp[i][j]为当串a取前i个元素时(设为a[1 ~ i]),且当串b的子序列以j结尾时,它们的最长公共子序列长度.
//dp[i][j]>=dp[i-1][j]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
using namespace std;

int n,m,a[N],b[N],dp[N][N],ans;

int main(){
    int T,mx;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
            	dp[i][j]=dp[i-1][j];//dp[i][j]>=dp[i-1][j]
            	if(a[i] == b[j]){//相等时,说明构成LCS,判断其是否构成LIS
            		for(int k=0;k<j;k++){//k的下界要从0开始,要不然如果b数组都是降序,就无法得到长度为1的LCIS
            			if(b[k]<b[j])//记录最大的LIS
            				dp[i][j]=max(dp[i][j],dp[i-1][k]+1);
					}
				}
            }
        }
        ans=0;
        for(int i=1;i<=m;i++)//记录最长的LCIS,a数组的前n个元素,枚举b数组以b[i]结尾的LCIS 记录最大长度
            ans=max(ans,dp[n][i]);
        printf("%d\n",ans);
        if(T)
            printf("\n");
    }
    return 0;
}
*/
