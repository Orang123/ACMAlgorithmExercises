#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:有一些狼，从左到右排列，每只狼有一个伤害。杀死一只狼的时候，
会受到这只狼的伤害和这只狼相邻两边的狼的额外伤害的和。若两只狼之
间的狼都被杀了，这两只狼就成新的相邻狼。求杀掉一排狼的最小代价。
杀掉一只狼左右两侧的狼可能不存在,额外伤害就为0.
注意:和POJ 1651 不同的是,狼是可以全部杀掉的,而POJ 1651 需要留下第1张牌和最后一张牌
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5115
思路:区间dp,dp[i][j]代表 杀死i~j的狼群所受到的最小伤害
*/
int n,a[210],b[210],dp[210][210];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        b[n+1]=0;//这里n+1的位置要设置为0,若测试样例前面的n较大,后面较小,b[n+1]位置的值就会影响两边狼的额外攻击值
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                dp[i][j]=INF;//初始化,值初始化j>=i时的值为INF,i>j的值为0,方便dp状态转移计算
	//第一次杀的狼初始状态就是 l=0的时候,最后杀的狼是l=n-1的时候
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                for(int k=i;k<=j;k++)//枚举对于狼群[i,j]中哪只狼为本次要杀死的,将区间分成两部分[i,k-1] [k+1,j] 这里dp[i][j] i>j时值为0,方便计算
                    //dp[i][k-1] dp[k+1][j]中的狼都是之前dp的状态已经被杀死
                    dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]+a[k]+b[i-1]+b[j+1]);
            }
        }
        printf("Case #%d: %d\n",cas,dp[1][n]);
    }
    return 0;
}


