#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 15100
using namespace std;
//ac 79ms 01背包模拟把全部砝码都放上天平平衡的总方案数
//dp[i][j]+=dp[i-1][j+l[k]*w[i]]
//同类型题目:HDU 3578 不要求橘子全部放入扁担,只有左、右两侧两种放法
/*
题意:一个天平,分别给出c个位置和g个钩码的质量,求解所有钩码
全部放上时有多少种使天平平衡的方案,输出方案数.
c<=20,g<=20,-15<=力臂长度c[i]<=15,砝码质量w[i]<=25.
注意:这里必须是所有砝码都放上去,不能有砝码没放上去.
链接:http://poj.org/problem?id=1837
思路:
实际也是个标准的分组背包问题,将每个砝码看做单独一组,每组物品为
这个砝码可能的g种放置位置,但只能选择一种放置位置放置.
力臂平衡 力臂=力距*力,该题最大力=20*15*25=7500,
实际每个砝码都有不同的挂钩,这只会影响这个砝码的力距长度,相当于
第i个砝码在不同力臂下会有不同的力臂,所以对于第i个砝码的放入
只需考虑在前i-1个砝码放入力臂基础上枚举不同挂钩下力距产生的力臂,
作为第i个砝码产生的所有合法状态,挂钩并不能作为每个砝码的独有属性,
因此并不构成二维费用背包的条件.
考虑01背包,因为背包容量数组下标不能为负数,所以最大力[-7500,7500]扩展为
[0,15000],平衡点为7500.dp[i][j]表示将前i个砝码全部放入天平上天平两侧力臂
矢量差为|j-7500|时的方案数.要恰好装满背包,因此初始状态为dp[0][7500]=0.
而状态转移方程有两种:
1.dp[i][j]+=dp[i-1][j+l[k]*w[i]];
2.dp[i][j+l[k]*w[i]]+=dp[i-1][j];
注意这里不能用滚动数组优化掉第一维度i,每个砝码要枚举放在不同的挂钩上,
dp[j+l[k]*w[i]],无论j降序还是升序,l[k]*w[i]可能为正可能为负,都不能保证
dp[j+l[k]*w[i]]一定是前i-1个砝码放置的情况,因此无法用滚动数组优化必须严格
表示成dp[i-1][j+l[k]*w[i]].

这里注意状态转移方程中的dp[i][j]不能继承前i-1个砝码的状态dp[i-1][j]
因为这样会导致,dp[i][7500]也会成为初始状态,也就是说当枚举放入第i个
砝码时,可以不在前i-1个砝码的放入的dp[i-1][j+l[k]*w[i]]合法状态基础上
放入第i个砝码,可以在dp[i-1][7500]平衡点基础上放入第i个砝码,也就是可以
考虑不放入前i-1个砝码,只放入第i个砝码.而且如果dp[i][j]初始继承dp[i-1][j]
会导致dp[i][j]+=累加方案时,将上一个状态前i-1个物品达到天平两侧力臂矢量差
为|j-7500|时的方案数也累加,这个显然也多加了,因为这个方案并没有放入第i个砝码.
*/
//dp[i][j]表示将前i个砝码全部放入天平上天平两侧力臂矢量差为(j-7500)时的方案数
int c,g,l[N],w[N],dp[N][M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&c,&g);
    for(int i=1;i<=c;i++)
        scanf("%d",&l[i]);
    for(int i=1;i<=g;i++)
        scanf("%d",&w[i]);
    dp[0][7500]=1;//初始状态
    for(int i=1;i<=g;i++){
        //注意这里不能dp[i][j]=dp[i-1][j] 因为 要求砝码全部放上去
        //枚举力臂矢量差的所有可能[0,15000]
        for(int j=0;j<=15000;j++){//这里升序降序都可 因为二维01背包本身就将前i-1个状态都存储下来了
            //枚举第i个砝码在不同力距下所产生的的力臂作为第i个状态 实际就是枚举放置在天平上的位置
            for(int k=1;k<=c;k++){
                //上一状态的力臂 只能在[0,15000]才是合法的
                if(j+l[k]*w[i]<0 || j+l[k]*w[i]>15000) continue;
                //累加将第i个砝码放到天平上产生力臂为|j-7500|的方案数
                //这里dp[i][j]初始都为空,第i个砝码放在不同挂钩 可能都能再上一状态dp[i-1][j+l[k]*w[i]]产生|j-7500|的力臂
                dp[i][j]+=dp[i-1][j+l[k]*w[i]];
            }
        }
    }
    //输出将g个砝码全部放到天平上产生力臂为|7500-7500|的方案数,也就是平衡的方案数
    printf("%d",dp[g][7500]);
    return 0;
}

/*
注意这个题必须扩大区间为原来的2倍,
不能用dp[i][abs(j+l[k]*w[i])]+=dp[i-1][j]的做法,
因为比如本身是-2,取绝对值变成了2,再往下放 力臂2加上为4,
可本身这里是-2,加2后应该为0 平衡了,HDU 3578和 牛客 失衡天平
之所以可以 是因为 每个砝码都尝试枚举放在左右两侧了,所以对于2,
2+2不行 还有2-2.
*/

/*
//ac 0ms  dp[i][j+l[k]*w[i]]+=dp[i-1][j]
//确定出所有砝码所能产生出最大力臂
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 15100
using namespace std;

int c,g,l[N],w[N],dp[N][M],sum;

int main(){
	int maxl=0,maxm=0;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&c,&g);
    for(int i=1;i<=c;i++){
    	 scanf("%d",&l[i]);
		 maxl=max(maxl,l[i]);//求出最大力距
	}
    for(int i=1;i<=g;i++){
    	scanf("%d",&w[i]);
    	maxm=max(maxm,w[i]);//求出最大砝码重量
	}
	sum=maxm*maxl*g*2;//求出g个砝码所能产生的最大力臂,乘2是将区间平移为正数
    dp[0][sum/2]=1;
    for(int i=1;i<=g;i++){
        for(int j=0;j<=sum;j++){
            if(!dp[i-1][j]) continue;
            for(int k=1;k<=c;k++){
                //在dp[i-1][j]是合法状态时,j+l[k]*w[i]一定是在[0,15000]范围内的 所以无需判断
                dp[i][j+l[k]*w[i]]+=dp[i-1][j];
            }
        }
    }
    printf("%d",dp[g][sum/2]);
    return 0;
}
*/

/*
//TLE 暴力枚举搜索 复杂度可达O(20^g) g<=20所以 20^20
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 15100
using namespace std;

int c,g,len[N],w[N],ans;

//此做法无法剪枝,因为是统计方案数,必须遍历所有情况 每个砝码有c种可放置的挂钩位置
//所以复杂度O(c^g) 而c<=20,g<=20因此 20^20 显然会炸
void dfs(int k,int l,int r){
    if(k == g+1){
        if(-l == r)
            ans++;
        return;
    }
    //枚举第k个砝码放置在哪个挂钩上
    for(int i=1;i<=c;i++){//O(c) O(20)
        if(len[i]<0)//放置在天平左臂
            dfs(k+1,l+len[i]*w[k],r);
        else////放置在天平右臂
            dfs(k+1,l,r+len[i]*w[k]);
    }
}

int main(){
    ans=0;
    scanf("%d%d",&c,&g);
    for(int i=1;i<=c;i++)
    	 scanf("%d",&len[i]);
    for(int i=1;i<=g;i++)
    	scanf("%d",&w[i]);
    dfs(1,0,0);
    printf("%d",ans);
    return 0;
}
*/
