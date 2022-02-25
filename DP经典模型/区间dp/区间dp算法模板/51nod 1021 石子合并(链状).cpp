/*
题意:N堆石子摆成一条线。现要将石子有次序地合并成一堆。规定每次只能选相邻
的2堆石子合并成新的一堆，并将新的一堆石子数记为该次合并的代价。
计算将N堆石子合并成一堆的最小代价。
例如： 1 2 3 4，有不少合并方法
1 2 3 4 => 3 3 4(3) => 6 4(9) => 10(19)
1 2 3 4 => 1 5 4(5) => 1 9(14) => 10(24)
1 2 3 4 => 1 2 7(7) => 3 7(10) => 10(20)
括号里面为总代价可以看出，第一种方法的代价最低，现在给出n堆石子的数量，
计算最小合并代价。
n<=100.
链接:https://www.51nod.com/Challenge/Problem.html#problemId=1021
思路:要求相邻的两堆石子合并,求取最小代价,那么贪心求取最小的两堆石子显然不满足条件,
因为不一定相邻.那么考虑常规的爆搜,第一次合并能考虑的有n-1个,第二次合并有n-2中选择,第三次n-3种...
最后一次合并1种选择.所以常规爆搜时间复杂度可达O((n-1)!),阶乘 时间复杂度 已经是一个无法接受的最坏的时间了,
已经远远超出1s的时间界.

dp[i][j]代表合并第i个石子堆到第j个石子堆所花费的最小代价
下面的解法是先枚举区间长度,后枚举区间起点来做的,实际是通过枚举区间左右端点不断合并,
也能解决此问题,关于区间dp感觉只要是不断地由小区间转移状态合并成大区间,而且每一次枚举区间的左右端点都不完全相同,
都是一个新的区间,方式不唯一.
*/
//时间复杂度O(n^3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int n,dp[110][110],sum[110];

int main(){
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i]+=sum[i-1];//表示前i个石子堆的总个数
        dp[i][i]=0;//第一次两个石子堆合并时,方便计算,用sum值替代
    }
    //O(N^3) 1s内时间限的样例N最大100
    for(int l=1;l<=n-1;l++){//枚举要合并石子堆的区间长度
        for(int i=1;i+l<=n;i++){//枚举合并石子堆区间的起点
            int j=i+l;
            /*
            枚举石子堆合并区间的分割点,dp[i][j]由之前子状态的两个区间石子堆合并构成,
            此次合并除了累加之前的花费dp[i][k-1]+dp[k][j]外,
            还需要加上此次合并的花费sum[j]-sum[i-1].
            for(int k=i;k<j;k++)
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]);两种都行
            */
            for(int k=i+1;k<=j;k++)
                dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k][j]+sum[j]-sum[i-1]);
        }
    }
    printf("%d",dp[1][n]);
    return 0;
}
/*
枚举区间的左右端点来dp,先枚举左端点,后枚举右端点,也是dfs记忆化搜索所采用的思维的dp版本
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp[110][110],sum[110];

int main(){
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i]+=sum[i-1];
        dp[i][i]=0;
    }
    for(int i=n-1;i>=1;i--){//枚举区间的左端点,不断向左扩展
        for(int j=i+1;j<=n;j++){//枚举从左端点开始可能的右端点,不断向n扩展
            for(int k=i;k<j;k++)//枚举区间的分割点,dp[i][k]在之前更靠左的右端点已经扩展过,dp[k+1][j]在之前的更靠右的左端点已经扩展过
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]);
        }
    }
    printf("%d",dp[1][n]);
    return 0;
}
*/
/*
枚举区间的左右端点来dp,先枚举右端点,后枚举左端点,
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp[110][110],sum[110];

int main(){
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i]+=sum[i-1];
        dp[i][i]=0;
    }
    for(int j=2;j<=n;j++){//枚举区间右端点 对于每一次右端点都不同,左端点就得相对重新枚举,来求解新的区间
        for(int i=j-1;i>=1;i--){//枚举区间左端点,通过不断左移左端点扩展成大区间
            for(int k=i+1;k<=j;k++)//枚举分割点
                dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k][j]+sum[j]-sum[i-1]);
        }
    }
    printf("%d",dp[1][n]);
    return 0;
}
*/

/*
//dfs 记忆化搜索=分治+记忆化判重
//时间复杂度O(n^3)
//剪枝和记忆化判重并不是一回事,剪枝对于某种情况的深度遍历,
//如果已经通过一种计算判定这个结点开始的深度遍历对于问题的求解没有任何更新时可不去遍历,
//而记忆化判重是对于之前已经遍历过的结果不再去重新遍历,而直接返回这个结果去优化时间复杂度.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp[110][110],sum[110];
//dfs爆搜的解法 思路就是分治+记忆化判重  整体还是记忆化搜索
//首先对于一个大的区间的最优解,要通过不断分割这个区间由两个区间合并,
//这两个区间其实就是不同的石子堆 分成的两个大堆,再求取在各个分割点下的代价,
//不断更新这个区间的最小代价.然后分割时所产生的两个子区间,
//也同样应用这样的思路去分割区间,直到最终变为最小的子问题开始返回结果.
//然后在回溯时,再重新枚举分割点去更新其余的2个子区间组合是否有更小的代价,不断更新大区间的最小代价.
//在这个过程中有些区间的解需要记录下来,当回溯到一开始 大区间再次枚举分割点深度求解时,
//有些区间之前已经计算过,无需再次深度遍历,只需返回结果.
//这个时间复杂度如果不考虑记忆化去重应该是要大于N^3的,但采用了记忆化后,反正没超时,
//应该差不多O(N^3)吧,这个时间复杂度证明 要采用数学办法证明
int dfs(int st,int ed){
    //这个重复遍历(重叠子问题)具体是发生在 :比如一开始大区间的求解[1,n]=[1,1]+[2,n]
    //然后[1,1]区间返回0,对于[2,n]区间深度遍历时再次分割[2,n]=[2,2]+[3,n]
    //[2,2]=0  对于区间[3,n]再次分割[3,n]=[3,3]+[4,n]以后依次类推,
    //最终这个结果当区间长度时1、2时就会依次类推不断返回,然后[3,n]求出来了,对于第一次枚举的分割点回溯回来
    //[1,n]=[1,1]+[2,n],枚举下一个分割点2,那么[1,n]=[1,2]+[3,n]那么此时就不必再次深度遍历[3,n]这个区间,
    //直接利用之前计算的结果dp[3][n]返回即可.事实上重复区间计算的地方非常多,仔细想想就好.
    //因为dfs深搜对于每一个区间的计算方法都是不断枚举分割点,划分为最小的子区间去更新计算,对于每一次区间分割,
    //实际上就是产生更多新的区间,dfs(st,i)+dfs(i+1,ed),dfs(st,i)是枚举可能的右端点,dfs(i+1,ed)是枚举可能的左端点
    //所以深搜枚举分割点本质上就是去枚举区间的左右端点进而枚举出更多新的子区间,进而去合并成大区间求解最小代价.
    if(dp[st][ed]!=INF) return dp[st][ed];
    if(st == ed) return dp[st][ed]=0;//相等时 返回0,以为一个石子堆无法合并,没有代价.返回时sum[ed]-sum[st-1]结果刚好是2个石子堆的和
    int ans=INF;
    for(int i=st;i<ed;i++)//sum[ed]-sum[st-1]是将区间[st,i]和区间[i+1,ed]合并时所消耗的代价.
        ans=min(ans,dfs(st,i)+dfs(i+1,ed)+sum[ed]-sum[st-1]);
    return dp[st][ed]=ans;
}

int main(){
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i]+=sum[i-1];
    }
    printf("%d",dfs(1,n));
    return 0;
}
*/

/*
这最后一种做法 没太看懂,感觉它在dp的时候会从大的区间向小的区间转。。。
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int f[101][101],s[101],n,temp;//初始化
int main()
{
	memset(f,127/3,sizeof(f));//先把f里的所有数变成一个很大的数
	scanf("%d",&n);//读入
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&temp);//读入
		s[i]=temp+s[i-1];//计算前缀和
		f[i][1]=0;//标记初始的值
	}
	for (int j=2;j<=n;j++)
	for (int i=1;i<=n-j+1;i++)
	for (int k=1;k<=j-1;k++)
	f[i][j]=min(f[i][j],f[i][k]+f[i+k][j-k]+s[i+j-1]-s[i-1]);//状态转移方程
	printf("%d",f[1][n]);//输出
	return 0;
}
*/
