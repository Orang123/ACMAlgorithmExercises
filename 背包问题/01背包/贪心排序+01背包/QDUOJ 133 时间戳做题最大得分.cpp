#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
using namespace std;
//ac 9ms 01背包+贪心(按照单位时间减少分数较多的排在前面) 尽可能多地装满背包
/*
题意:LYD要打CF,一共n道题,t单位时间,每道题都有初始分数a,
每单位时间减的分数d和做出这道题需要多长时间c,求最大的得分.
说明:每道题做出的分数a-d*c,这里的c是从比赛开始当前的时刻点,
并不是实际所用的时间.
链接:https://qduoj.com/problem/133
思路:摘自博客:https://blog.csdn.net/xuejye/article/details/77199802
打过应该都知道比赛机制吧 题意很好理解
关键说说本题排序的问题和为什么要排序
一开始看到题有贪心取背包的感觉 问题是怎么贪心
如果单纯判断一个变量 比如每道题中该题每分钟掉分的分数 或者只考虑时间 都会因为另一个因素影响而到不到最优
取两道题的例子研究 
设第一题的分数为v1  每分钟掉d1  需要t1分钟
设第二题的分数为v2  每分钟掉d2  需要t2分钟
先1后2的得到分数的情况是：sum1=( v1 - d1 * t1 ) + ( v2 - d2 * ( t2 + t1 ) )
先2后1的得到分数的情况是：sum2=( v2 - d2 * t2 ) + ( v1 - d1 * ( t1 + t2 ) )
另dif=sum1-sum2  自己纸上算一算 得到式子dif = d1 * t2 - d2 * t1
当dif > 0 即sum1>sum2 即 先取1所得到的分数大于先取2所得到的分数的时候 就应该满足
d1 * t2 > d2 * t1  （dif = d1 * t2 - d2 * t1 > 0推出来的） 变换得到d1 / t1 > d2 / t2
由于博主语文不大好 比较难用文字表达出容易让人理解的意思 各位自行感受上一行最后一个表达式的含义
虽然不能理解意思 但是可以得到这样一个结论：当d1 / t1 > d2 / t2时 先取1后取2更优
那么能够推出的结论就是 对于任意第i道题 di / ti值越大 就需要越先解决这道题
很明显了 通过额外记录一个judge=di / ti 对judge从大到小排序 然后进行01背包的动态规划
*/

int dp[N],n,t;//dp初始化为0,所有状态合法
struct Pro{
    int a,d,c;
    bool operator <(const Pro &x)const{
        /*
        按照单位时间内减少的分数降序,01背包优先考虑减少分数多的先做,
        因为分数累加中a[i]-d[i]*j,a[i]之和i∈[1,n]是恒定的,要想获得分数
        最多,就需要d[i]*j最小化,即先做单位时间内减少分数最多的,即d/c较大的.
        */
        return d*1.0/c>x.d*1.0/x.c;
    }
}p[N];

int main(){
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].a);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].d);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].c);
    sort(p+1,p+1+n);
    for(int i=1;i<=n;i++){
        for(int j=t;j>=p[i].c;j--)
            dp[j]=max(dp[j],dp[j-p[i].c]+p[i].a-p[i].d*j);//j是当前做完第i道题的时刻点
    }
    int ans=0;
    /*
    不一定要把全部题都做出分数才最高,有可能 时间点越靠后的题目a-d*c为负,
    c时间点很大,d*c很大;
    也有可能在t时间内 无法做完所有题,如果某个题的做完需要的时间较长,
    dp[t]可能只是把这个时间较长的题做完,而剩下的题都无法做了
    而dp[0...t]0~t之间的dp[i]可能能做多道题,其获得的分数可能更大
    造成这个问题的主要原因是,状态转移方程中对每个题获得的分数 是根据时间点来计算的 a-d*c,
    c表示做完该道题的当前时刻点.而经典的01背包问题 状态转移方程式,随着背包容量的增加,其获得
    的总价值是不断累加的,所以dp[v]所能获得价值一定是最大的.
    */
    for(int i=0;i<=t;i++)//取某个时刻点所做题目获得的最大分数
        ans=max(ans,dp[i]);
    /*
    样例中dp[t]=210,是选择在4分钟开始做第一题,6分钟时做完,
    紧接着6分钟开始做第二题,10分钟时做完.获得分数为 100-5*6+200-6*10=210,
    显然比从0时刻开始做第一题紧接着2分钟时做第二题获得的分数较低,100-5*2+200-4*6=254,
    之所以dp[t]=210,是因为恰好装满背包初始状态dp[0...t]都是合法的,这就导致了选择在比赛
    开始4分钟后才开始做第一题,因为dp[4]初始状态是0,是合法的.
    */
    printf("%d",ans);
    return 0;
}
/*
//ac 9ms 01背包+贪心(按照单位时间减少分数较多的排在前面) 恰好装满背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
using namespace std;
int dp[N],n,t;//初始状态只有dp[0]是合法的

struct Pro{
    int a,d,c;
    bool operator <(const Pro &x)const{
        return d*1.0/c>x.d*1.0/x.c;
    }
}p[N];

int main(){
    scanf("%d%d",&n,&t);
    memset(dp,-0x3f,sizeof(dp));
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].a);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].d);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].c);
    sort(p+1,p+1+n);
    dp[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=t;j>=p[i].c;j--)
            dp[j]=max(dp[j],dp[j-p[i].c]+p[i].a-p[i].d*j);
    }
    int ans=0;
    //相比尽可能多地装满背包,恰好装满背包只有dp[0]都是合法的,
    //所以dp[t]只有从0时刻开始做 第三题参满足恰好装满,10时刻刚好做完,
    //即dp[t]=250-7*10=180.最终dp[0..t]只有恰好装满的情形才满足dp[i]>0
    for(int i=0;i<=t;i++){//取某个时刻点所做题目获得的最大分数
        if(dp[i]>0)//只有恰好装满的情形 分数才会最大
            ans=max(ans,dp[i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//TLE 暴力搜索枚举 未剪枝
//因为暴搜本身就是一道题紧接着一道题做,中间时间没有空余
//但是枚举所有组合 只有编号较小的题目才会考虑先做,而实际
//可能需要编号较大的题目在时间点较小时先做,所以依然需要先贪心按照d/c降序排序
//也可以不贪心排序,其实也可以考虑 枚举全排列那种暴搜,这样就可以将编号靠后的题在较小时刻先做,编号靠前题较后时刻做
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
using namespace std;

int n,t,a[N],d[N],c[N],ans;
struct Pro{
    int a,d,c;
    bool operator <(const Pro &x)const{
        return d*1.0/c>x.d*1.0/x.c;
    }
}p[N];

void dfs(int k,int curt,int sum){
    if(ans<sum)
        ans=sum;
    if(k == n+1) return;
    if(curt+p[k].c<=t)
        dfs(k+1,curt+p[k].c,sum+p[k].a-p[k].d*(curt+p[k].c));
    dfs(k+1,curt+p[k].c,sum);
}

int main(){
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].a);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].d);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].c);
    sort(p+1,p+1+n);
    dfs(1,0,0);
    printf("%d",ans);
    return 0;
}
*/
