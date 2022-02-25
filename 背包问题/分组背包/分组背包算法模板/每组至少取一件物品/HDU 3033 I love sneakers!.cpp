/*
题意:一个人要买鞋子,总共有n双鞋子,有k种品牌的鞋,要求
每种鞋至少买一双,给出每双鞋子的花费w和价值val,问m元钱
可以买到的鞋子的最大价值是多少.
n<=100,m<=10000,0<=w,val<=100000,1<=k<=10.num[k]<=100.
注意:每双鞋子的花费和价值都可以为0.
释义:有n组物品和一个容量是v的背包.每组物品有num[i]个,
同一组内的物品要求至少选一个.每件物品的体积是w[i][j],
价值是val[i][j],其中i是组号,j是组内编号.求解在物品总
体积不超过背包容量条件下,能得到的最大价值,若不能满足
每组物品至少取一个,输出"Impossible",否则输出能得到的
最大价值.每个物品仍然只有选或不选,同一个物品只能选一次.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3033
思路:每种品牌的所有鞋子可以作为一组物品,每种品牌的鞋子至少买一件.
分组背包 每组至少取一件物品模板题.前i组的最大价值可以由
前i-1组或前i组状态的最优解转移而来,要注意第i组的dp[i][j]
不能直接继承dp[i-1][j],否则那样无法保证每组至少买一件物品.
需要保存前i-1组上一状态,因此只能二维数组实现.
时间复杂度O(k*max(num[k])*m)=1*100*10000=10^6

注意:这个做法状态转移的顺序 暂时只能先考虑dp[i][j-w]转移 再考虑dp[i-1][j-w]转移
,即使物品体积能保证不为0,也得是这个顺序,HDU 3449那题物品花费并不会为0,但是错了,
暂不清楚原因.
*/
//ac 46ms 每组至少取一个物品
//时间复杂度O(k*max(num[k])*m)=1*100*10000=10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 10010
using namespace std;

//dp[i][j]代表前i组每组至少拿一件物品在背包容量为j时能获得的最大价值.
int n,m,k,num[N],w[N][110],val[N][110],dp[N][M];

int main(){
    int a,b,c;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        memset(num,0,sizeof(num));
        while(n--){
            scanf("%d%d%d",&a,&b,&c);//a是鞋子的品牌号
            num[a]++;//a组物品的个数 +1
            w[a][num[a]]=b;
            val[a][num[a]]=c;
        }
        //因为dp[i][j]的初始状态必须由dp[i-1][j-w[i][t]]+val[i][t]或dp[i][j-w[i][t]]+val[i][t]转移而来
        //因此dp[i][j]的初始状态必须是负无穷,才能保证当dp[i][j]合法时第i组的物品至少取了一件.
        //不初始化0是因为有可能物品价值本身为0,这样无法判断dp[k][m]到底是不是合法状态.
        //有可能实际每组物品价值都为0,但判断dp[k][m]=0 会输出"Impossible".
        //注意这个做法只有在初始化-INF为非法状态时才可以不判断上一状态是否合法,
        //如果初始化全0(物品价值能保证不为0)或-1(物品价值可以为0),需要判断上一状态dp[i-1][j-w]和dp[i][j-w]是否合法
        //否则某组物品可能一件也不能取,它的下一组物品也能通过累加使得不合法状态变得合法 会影响最后的结果
        memset(dp,-0x3f,sizeof(dp));//此题仍旧是判断了 上一状态是否合法,因此初始化为-1也不会错
        for(int i=1;i<=m;i++)
            dp[0][i]=0;//初始状态,一组物品也不取时,任何背包容量对应的价值都为0
        //考虑第i组物品
        for(int i=1;i<=k;i++){
            //第i组中的每一件物品t做01背包
            for(int t=1;t<=num[i];t++){
                for(int j=m;j>=w[i][t];j--){
                    /*
                    注意这里dp的顺序必须是先由前i组物品dp[i][j-w[i][t]]转移,
                    再考虑是否由前i-1组物品dp[i-1][j-w[i][t]]转移,因为有可能
                    第i组物品第t个物品体积为0,这样如果先考虑由前i-1组状态转移
                    而来,那么dp[i][j]=dp[i-1][j-0]+val[i][t],再考虑由前i组的
                    状态转移而来,dp[i][j]=dp[i][j-0]+val[i][t],发现dp[i][j]本身
                    已经将第t个物品取过了,而现在又在dp[i][j]取过第t个物品基础上,
                    重复地将第t个物品再取了一次.与一个物品只能取一次相违背,因此
                    会出错.
                    */
                    //dp[i][j-w[i][t]]>=0保证 前第i组每组物品已经至少取了一件
                    if(dp[i][j-w[i][t]]>=0)//考虑 能否在已经放入第i组物品的基础上,继续放入第i组的物品的最优解
                        dp[i][j]=max(dp[i][j],dp[i][j-w[i][t]]+val[i][t]);
                    //dp[i-1][j-w[i][t]]>=0保证前i-1组每组物品都取了一件 是合法状态
                    if(dp[i-1][j-w[i][t]]>=0)//考虑 在前i-1组物品最优解基础上至少放入一件第i组的物品获得的最优解
                        dp[i][j]=max(dp[i][j],dp[i-1][j-w[i][t]]+val[i][t]);
                }
            }
        }
        if(dp[k][m]>=0)
            printf("%d\n",dp[k][m]);
        else
            printf("Impossible\n");
    }
    return 0;
}

/*
//ac 46ms 每组至少取一个物品
//dp[i][j]=max(dp[i][j],max(dp[i-1][j-w[i][t]]+val[i][t],dp[i][j-w[i][t]]+val[i][t]));
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 10010
using namespace std;

//dp[i][j]代表前i组每组至少拿一件物品在背包容量为j时能获得的最大价值.
int n,m,k,num[N],w[N][110],val[N][110],dp[N][M];

int main(){
    int a,b,c;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        memset(num,0,sizeof(num));
        while(n--){
            scanf("%d%d%d",&a,&b,&c);
            num[a]++;
            w[a][num[a]]=b;
            val[a][num[a]]=c;
        }
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=m;i++)
            dp[0][i]=0;
        for(int i=1;i<=k;i++){
            for(int t=1;t<=num[i];t++){
                for(int j=m;j>=w[i][t];j--)
                    dp[i][j]=max(dp[i][j],max(dp[i-1][j-w[i][t]]+val[i][t],dp[i][j-w[i][t]]+val[i][t]));
            }
        }
        if(dp[k][m]>=0)
            printf("%d\n",dp[k][m]);
        else
            printf("Impossible\n");
    }
    return 0;
}
*/

/*
//ac 31ms 每组至少取一个物品
//滚动数组优化 两个数组 dp[M] tp[M]做法
//dp[j]=max(dp[j],max(tp[j-w[i][t]]+val[i][t],dp[j-w[i][t]]+val[i][t]));
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 10010
using namespace std;

//tp[j]代表前i-1组每组至少拿一件物品在背包容量为j时能获得的最大价值.
//dp[j]代表前i组每组至少拿一件物品在背包容量为j时能获得的最大价值.
int n,m,k,num[N],w[N][110],val[N][110],dp[M],tp[M];

int main(){
    int a,b,c;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        memset(num,0,sizeof(num));
        while(n--){
            scanf("%d%d%d",&a,&b,&c);
            num[a]++;
            w[a][num[a]]=b;
            val[a][num[a]]=c;
        }
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=k;i++){
            //将前i-1的状态赋值给tp
            for(int j=0;j<=m;j++)
                tp[j]=dp[j];
            //前i组状态初始是不合法的
            memset(dp,-0x3f,sizeof(dp));
            for(int t=1;t<=num[i];t++){
                for(int j=m;j>=w[i][t];j--)
                    dp[j]=max(dp[j],max(tp[j-w[i][t]]+val[i][t],dp[j-w[i][t]]+val[i][t]));
            }
        }
        if(dp[m]>=0)
            printf("%d\n",dp[m]);
        else
            printf("Impossible\n");
    }
    return 0;
}
*/

/*
dfs暴力枚举搜索 不好模拟每个组至少取一个,当然本身也是会TLE的
如果枚举每个组先取一件物品 对剩下的物品还要模拟01背包,但是又不好
区分这个物品是当前组还是已经到了下一组了,因此暴力做法不好想.
*/
