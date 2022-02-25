#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:给出一个多边形,每条边上都一种运算符(加法或乘法),每个顶点上有个数字,
开始时会删除一条边的运算,之后就两个顶点运算合并为一个顶点,直到只剩下一个顶点时,
求最终的运算所得顶点的最大值,并输出这样的积分 开始时删除哪条边能获得.
链接:https://www.luogu.com.cn/problem/P4342
思路:其实就是环状的石子合并,需要将数组扩大2倍,开始删除的边实际上就是将环状切开,转化成链式问题,
选择哪个链式区间[i,i+n-1]的最值,但在求解最值时,加法的操作比较简单,但乘法的状态转移,因为存在负数
负负得正的情况,因此乘法最大值不光和之前状态的最大值有关还和最小值有关,即dp1[1][j]也可能是由
dp2[i][k]*dp2[k+1][j],dp1[i][k]*dp2[k+1][j],dp2[i][k]*dp1[k+1][j]转移而来.最小值的转移也和最大值有关.
关于乘法的分析实际有9种情况,但总结下来状态转移只有4种情形.
*/

char a[110];
int dp1[110][110],dp2[110][110],b[60],n;

int main(){
    int ans=-1;
    memset(dp1,-INF,sizeof(dp1));
    memset(dp2,INF,sizeof(dp2));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
        dp1[i][i]=dp1[i+n][i+n]=b[i];
        dp2[i][i]=dp2[i+n][i+n]=b[i];
        a[i+n]=a[i];
    }
    for(int l=1;l<n;l++){
        for(int i=1;i+l<2*n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                if(a[k+1] == 't'){//加法运算转移
                    dp1[i][j]=max(dp1[i][j],dp1[i][k]+dp1[k+1][j]);//最大值只和最大值有关
                    dp2[i][j]=min(dp2[i][j],dp2[i][k]+dp2[k+1][j]);//最小值之和最小值有关
                }
                else{//乘法运算转移 最大值的转移和最大值 最小值都有关联
                    dp1[i][j]=max(dp1[i][j],max(dp1[i][k]*dp1[k+1][j],max(dp2[i][k]*dp2[k+1][j],max(dp1[i][k]*dp2[k+1][j],dp2[i][k]*dp1[k+1][j]))));
                    dp2[i][j]=min(dp2[i][j],min(dp1[i][k]*dp1[k+1][j],min(dp2[i][k]*dp2[k+1][j],min(dp1[i][k]*dp2[k+1][j],dp2[i][k]*dp1[k+1][j]))));
                }
            }
        }
    }
    for(int i=1;i<n;i++)//判断开始删除哪条边的最大值最大
        ans=max(ans,dp1[i][i+n-1]);
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)//输出删除的边
        if(dp1[i][i+n-1] == ans)
            printf("%d ",i);
    return 0;
}
