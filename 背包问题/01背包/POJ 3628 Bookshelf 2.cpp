//ac 32ms 01背包 背包容量恰好装满
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
/*
题意:n(n<=20)头牛,每头牛有一定高度,现在有一书架高度为b,
现在要将这些的牛叠放在一起,这些牛的高度就为叠放在一起牛
的总高度,现在要求这个总高度不小于书架高度b,并且要求叠放
在一起牛的总高度与书架高度b的差值最小,求这个最小差值.
链接:http://poj.org/problem?id=3628
思路:实际上就是枚举所有牛的可能叠放情况,具体哪头牛选取,哪头牛
不选,因为n<=20,可以考虑暴力搜索+剪枝,或者用恰好装满的01背包模型
模拟搜索,升序遍历出dp[i]大于等于b的情况,输出最小差值.注意这里题目
并没有要求求取奶牛叠放在一起的最大高度,只是用背包容量恰好装满的01背包
(背包容量为所有奶牛高度和,物品价值和体积都是奶牛高度)去模拟暴力搜索的
这个奶牛组合的可能情况的高度和,虽然状态转移方程是求取最大高度,这个只是
01背包状态转移方程的性质,在这里本身只是模拟取和不取的最优解.

总结:这种背包容量恰好装满,即:背包容量就是所有物品价值和的问题实际就是裸的
暴力枚举物品组合情况的问题,只是一般这类问题当物品数量n较大时,暴力枚举dfs会
超时,会转为为01背包的模型去模拟搜索枚举得到的最优解,而且这类问题一般会给出
一个最优解的衡量标准,即:最后需要判断dp[i]的合法性是否是恰好装满的情形(是否等于-INF).
而且所对应的暴力枚举搜索问题 也不会指定选取几个物品,基本是要遍历所有可能物品的
组合情况,记录更新要求的最优解.
*/
int dp[1000010];//题目Hi<=1000000,按道理所有物品总容量上限应该为20*1000000,但这样MLE
int main(){
    int n,b,a[25],sum;
    while(scanf("%d%d",&n,&b)!=EOF){
        sum=0;
        memset(dp,-0x3f,sizeof(dp));//背包恰好装满
        for(int i=0;i<n;i++){
            scanf("%d",a+i);
            sum+=a[i];
        }
        dp[0]=0;//除了初始0状态合法,其余状态都不合法
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=a[i];j--)
                dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
        }
        for(int i=b;i<=sum;i++){//升序从书架高度开始判断,满足>=b时输出最小差值即可
            if(dp[i]>=b){
                printf("%d\n",dp[i]-b);
                break;
            }
        }
    }
    return 0;
}

/*
//ac 32ms 01背包 尽可能多地装满背包
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int dp[1000010];
int main(){
    int n,b,a[25],sum;
    while(scanf("%d%d",&n,&b)!=EOF){
        sum=0;
        memset(dp,0,sizeof(dp));//初始化所有状态合法
        for(int i=0;i<n;i++){
            scanf("%d",a+i);
            sum+=a[i];
        }
        for(int i=0;i<n;i++){
            for(int j=sum;j>=a[i];j--)
                dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
        }
        for(int i=b;i<=sum;i++){//这里因为升序从b开始判断,第一个满足dp[i]>=b的一定是恰好装满的情况,i是不会有剩余的,所以能保证答案的正确性
            if(dp[i]>=b){
                printf("%d\n",dp[i]-b);
                break;
            }
        }
    }
    return 0;
}
*/

/*
//ac 16ms 暴力搜索枚举+剪枝
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;
int n,a[N],ans,b,sufxh[N];

int dfs(int k,int sum){
    if(sum>=b){//奶牛高度总和大于等于书架高度b时 记录最小差值
        ans=min(ans,sum-b);
        if(!ans) return 1;//当最小差值为0时说明奶牛高度总和恰好达到书架高度,为最优(理想)情况,直接返回1退出搜索
        return 0;//最小差值不为0,则返回0,继续枚举搜索下去
    }
    if(k == n+1) return 0;
    if(sum+sufxh[k]<b) return 0;//剪枝 当前高度+编号为k~n的奶牛高度总和比书架高度b小,则返回0,不再继续当前搜索,尝试下一组搜索
    if(dfs(k+1,sum+a[k])) return 1;//返回1 说明最小差值为0,直接退出搜索
    if(dfs(k+1,sum)) return 1;
    return 0;//最小差值不为0,返回0,尝试下一组搜索
}

int main(){
    while(scanf("%d%d",&n,&b)!=EOF){
        ans=INF;
        sufxh[n+1]=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=n;i>=1;i--)
            sufxh[i]=sufxh[i+1]+a[i];
        dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/
