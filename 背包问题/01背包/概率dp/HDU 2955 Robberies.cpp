#include<cstdio>
#include<cstring>
#define max(i,j) i>j?i:j
//ac 46ms 01背包恰好装满
/*
题意:一个劫匪去抢劫n(n<=100)个银行,每个银行都有一定存款,劫匪对于抢劫
每个银行都有对应的被抓的概率,现在给出一个被抓的概率p,计算劫匪
抢劫这些银行被抓的概率小于给定的被抓概率p的情况下最多能抢劫的金钱.
注意:这个被抓的概率表示劫匪抢劫银行时,至少有一个银行时被抓的,没和银行
要么被抓要么逃跑.
所有银行存款上限<=100*100=10^4
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2955
思路:摘自:https://blog.csdn.net/u012294939/article/details/39674323
这道题属于01背包的经典题,与概率相结合.题目大意是在保证小于被抓
的概率之下偷到更多的钱.但是与一般的01背包对比的话,我们会发现不同的地方,
如果将dp[i]作为获得的钱的数量的话,这个i就是被抓的概率,但是由于概率是浮点数,
而且浮点数的位数也不确定,即使通过对浮点数放大一定的倍数也不一定能得到正确答案.
所以我们要考虑概率与钱数这两者之间的关系.取到的钱数越多越好,只要不被抓住就好.
被抓的概率小于指定概率p的条件下,取到钱数尽可能多.如果从被抓的角度考虑的话,
dp[0]表示偷走0元钱的概率,那么dp[0]=0,在状态转移时我们要考虑不偷走当前的钱和偷
走当前的钱这两种决策.而dp[i]代表偷走i元钱时被抓的概率,在算被抓的概率时,他在这
一次可能被抓,也可能没有被抓,但是总的来说至少有一次被抓.通过概率的学习我们知道,
这样的情况是很多的,要分类1个银行被抓,2个银行被抓...,n个银行被抓,这会变成一个
在给定n个物品中选取指定数量物品乘法原理计算概率的问题,这是一个暴力枚举搜索的问题,
不可在多项式时间内求解,所以考虑被抓的概率是不太可行的.所以我们要从它的对立事件考虑,
考虑他能够逃走的概率,这样问题就转换为抢劫银行逃走的概率大于等于1-p的情况下,能偷走的
尽可能多的钱,这显然构成一个01背包问题,物品的体积为银行的存款,物品的价值为抢劫银行逃走的
概率,而背包的容积是所有物品的体积和,即:所有银行的存款和,而这个抢劫银行获得的存款在这个
问题中它是不会有剩余的,即:背包容量必须恰好装满,那么初始化dp[0]=1,其余值都设置为0,因为要
求取抢劫这些银行所能逃跑的最大概率.最终最多能抢到的钱可能并不是所有银行的存款,因为所有
银行都抢劫的最大逃跑概率可能并不大于等于1-p,要选择大于等于1-p条件下所能抢劫银行获得的最多钱数,
可能实际并没有把所有银行都抢劫,总之考察一个抢劫银行的可能的组合方案.
因为逆否事件的等价性,2个事件最多所能抢的钱是等价的.
*/
int money[105];
double dp[10005],val[105];
int main(){
    int T,n,sum;
    double p;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        sum=0;
        scanf("%lf%d",&p,&n);
        p=1-p;//从对立事件 逃跑概率考虑
        for(int i=1;i<=n;i++){
            scanf("%d%lf",money+i,val+i);
            sum+=money[i];//背包的容量本身就是根据物品的容量累加起来的,这样在求解时实际情况恰好是装满的情形
            val[i]=1-val[i];
        }
        dp[0]=1.0;//恰好装满只初始化dp[0]=1,其余值设置为0,因为是求取最大逃跑概率,
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=money[i];j--)
                dp[j]=max(dp[j],dp[j-money[i]]*val[i]);
        }
        //这里如果不采用恰好装满 只初始化dp[0]=1.0,而尽可能多装 全部初始化1.0,
        //输出的抢劫的钱就可能偏大,因为容量有剩余的背包也成了合法状态
        for(int i=sum;i>=0;i--)//降序遍历抢劫的钱,如果满足逃跑率大于等于1-p,就输出能获得最大金额
            //因为用了滚动数组优化 这里的最优解也并不清楚是抢劫了几个银行,只知道满足大于等于1-p下的最大抢劫金额
            if(dp[i]>=p){//逃跑率满足大于等于1-p,这里的p之前已经赋值为1-p了
                printf("%d\n",i);
                break;
            }
    }
    return 0;
}

/*
无法用尽可能多地装满背包的思想去做,因为判断dp[i]>=p时,
i到底是不是恰好装满无法判断,直接输出,结果可能出错.
*/

/*
//TLE 暴力枚举搜索+剪枝
#include<cstdio>
#include<cstring>
#define N 110
#define max(i,j) i>j?i:j

//sufxmey[i]表示i~n后缀银行存款总和
//sufxval[i]表示i~n后缀所有银行中逃跑率最大的概率
int money[N],n,ans,sufxmey[N];
double val[N],p,sufxval[N];

void dfs(int k,int sum,double res){
    //当当前逃跑的概率大于等于1-p时,更新最多抢的钱
    if(res>=1-p && sum>ans)
        ans=sum;
    //剪枝1 当前抢的钱加上k~n后缀所有银行的钱 不比ans大时 返回,回溯上一层
    if(sum+sufxmey[k]<=ans) return;
    //剪枝2 当前逃跑概率乘k~n银行中最大逃跑概率都比1-p小时返回,因为乘其余银行概率只会更小,返回,回溯到上一层.
    if(res*sufxval[k]<1-p) return;
    if(k == n+1) return;//枚举完所有物品 返回上一层
    dfs(k+1,sum+money[k],res*(1-val[k]));
    dfs(k+1,sum,res);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        sufxmey[n+1]=0;
        sufxval[n+1]=0.0;
        scanf("%lf%d",&p,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%lf",money+i,val+i);
        for(int i=n;i>=1;i--)
            sufxmey[i]=sufxmey[i+1]+money[i];
        for(int i=n;i>=1;i--)
            sufxval[i]=max(sufxval[i+1],(1-val[i]));
        dfs(1,0,1.0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 234ms 正向二维数组dp
#include<cstdio>
#include<cstring>
#define max(i,j) i>j?i:j
int money[105];
double dp[105][10005],val[105];
int main(){
    int T,n,sum;
    double p;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%lf%d",&p,&n);
        p=1-p;//从对立事件 逃跑概率考虑
        for(int i=1;i<=n;i++){
            scanf("%d%lf",money+i,val+i);
            sum+=money[i];//背包的容量本身就是根据物品的容量累加起来的,这样在求解时实际情况恰好是装满的情形
            val[i]=1-val[i];
        }
        dp[0][0]=1.0;//恰好装满只初始化dp[0][0]=1,其余值设置为0,因为是求取最大逃跑概率,
        for(int i=1;i<=n;i++){
            for(int j=0;j<=sum;j++)
                if(j>=money[i])
                    dp[i][j]=max(dp[i-1][j],dp[i-1][j-money[i]]*val[i]);
                else
                    dp[i][j]=dp[i-1][j];
        }
        int flag=0;
        for(int j=sum;j>=0;j--){//降序遍历抢劫的钱,如果满足逃跑率大于等于1-p,就输出能获得最大金额
            for(int i=n;i>=1;i--){
                if(dp[i][j]>=p){//逃跑率满足大于等于1-p,这里的p之前已经赋值为1-p了
                    printf("%d\n",j);
                    flag=1;
                    break;
                }
            }
            if(flag) break;
        }
    }
    return 0;
}
*/

/*
//wa 二维数组 记忆化搜索
//关于涉及到概率背包恰好装满的问题 记忆化搜索会出错,实际上记忆化搜索,
//在分解子问题时背包的容量只能通过j-money[i]来减小分解子问题,对于这种背包容量为
//物品体积之和的情况,即:背包恰好装满的情况,个别子问题可能无法全部分解出来,要谨慎使用
//而正向dp 第二层嵌套的循环会线性枚举背包容量[0...V],所以会把所有情况都考虑到.
//本题出错的原因在于 记忆化搜索 分解子问题没能分解出dp[3][2]这组子问题,导致题目第一组样例,输出为1
//可以对每个可能的背包容积0<=j<=sum,dfs(n,j)进行记忆化搜索解决这个问题,这个做法比较玄学,反正貌似是可以分解出
//所有子问题的,在最后下面代码里提供
#include<cstdio>
#include<cstring>
#define max(i,j) i>j?i:j
int money[105];
double dp[105][10005],val[105];

double dfs(int i,int j){
    if(!i && !j) return 1.0;//恰好装满只初始化dp[0][0]=1,其余值设置为0,因为是求取最大逃跑概率
    if(!i && j) return -1.0;//i == 0,背包容量初始不为0时,并不是初始状态,如果返回1,会导致背包不能装满,返回-1 是为了比0小,因为p可能为0 避免判断错误
    if(dp[i][j] != -1.0) return dp[i][j];
    if(j>=money[i])
        dp[i][j]=max(dfs(i-1,j),dfs(i-1,j-money[i])*val[i]);
    else
        dp[i][j]=dfs(i-1,j);
    return dp[i][j];
}

int main(){
    int T,n,sum;
    double p;
    scanf("%d",&T);
    while(T--){
        sum=0;
        scanf("%lf%d",&p,&n);
        p=1-p;//从对立事件 逃跑概率考虑
        for(int i=1;i<=n;i++){
            scanf("%d%lf",money+i,val+i);
            sum+=money[i];//背包的容量本身就是根据物品的容量累加起来的,这样在求解时实际情况恰好是装满的情形
            val[i]=1-val[i];
        }
        for (int i=1;i<= n;i++) {
            for (int j=0;j<=sum;j++)
                dp[i][j]=-1.0;//初始化负数 判断时 本身不合法的状态 才能排除 因为0<=p<=1
        }
        dfs(n,sum);
        int flag=0;
        for(int j=sum;j>=0;j--){//降序遍历抢劫的钱,如果满足逃跑率大于等于1-p,就输出能获得最大金额
            for(int i=n;i>=1;i--){
                if(dp[i][j]>=p){//逃跑率满足大于等于1-p,这里的p之前已经赋值为1-p了
                    printf("%d\n",j);
                    flag=1;
                    break;
                }
            }
            if(flag) break;
        }
    }
    return 0;
}
*/

/*
//ac 358ms 记忆化搜索 AgOH群里1173007724提供
//因为这个一次记忆化搜索并不能将所有子问题分解出来,所以枚举容量j属于[sum,0] dfs(n,j)才能分解出所有子问题,才能求出最优解
//这个做法不敢保证它 一定是对的,大概是枚举可能的背包容量 这样才能求出可能的接近于所有子问题吧
//注意因为 0<=val[i]<=1.0 0<=p<=1.0 所以1-val[i] 1-p可能本身就是0,实际的概率结果有可能会有0 所以初始化以及不合法状态不能为0
//因此dp数组就不能初始化为0,必须初始化为一个别的值,否则会影响实际 重叠子问题的判重,
//因为实际合法值就是0,因此需要用别的值初始化dp数组
#include<cstdio>
#include<cstring>
#define max(i,j) i>j?i:j
int money[105];
double dp[105][10005],val[105];

double dfs(int i,int j){
    if(!i && !j) return 1.0;//恰好装满只初始化dp[0][0]=1,其余值设置为0,因为是求取最大逃跑概率
    if(!i && j) return -1.0;//i == 0,背包容量初始不为0时,并不是初始状态,如果返回1,会导致背包不能装满,返回-1 是为了比0小,因为p可能为0 避免判断错误
    if(dp[i][j]!=-1.0) return dp[i][j];
    if(j>=money[i])
        dp[i][j]=max(dfs(i-1,j),dfs(i-1,j-money[i])*val[i]);
    else
        dp[i][j]=dfs(i-1,j);
    return dp[i][j];
}

int main(){
    int T,n,sum;
    double p;
    scanf("%d",&T);
    while(T--){
        sum=0;
        scanf("%lf%d",&p,&n);
        p=1-p;//从对立事件 逃跑概率考虑
        for(int i=1;i<=n;i++){
            scanf("%d%lf",money+i,val+i);
            sum+=money[i];//背包的容量本身就是根据物品的容量累加起来的,这样在求解时实际情况恰好是装满的情形
            val[i]=1-val[i];
        }
        //注意因为 0<=val[i]<=1.0 所以1-val[i[可能本身就是0,实际的概率结果有可能会有0
        //因此dp数组就不能初始化为0,必须初始化为一个别的值,否则会影响实际 重叠子问题的判重,
        //因为实际合法值就是0,因此需要用别的值初始化dp数组
        for (int i=1;i<= n;i++) {
            for (int j=0;j<=sum;j++)
                dp[i][j]=-1.0;
        }
        for(int j=sum;j>=0;j--){
            //因为这个一次记忆化搜索并不能将所有子问题分解出来,所以枚举容量j属于[sum,0] dfs(n,j)才能分解出所有子问题,才能求出最优解
            //这个做法不敢保证它 一定是对的,大概是枚举可能的背包容量 这样才能求出可能的接近于所有子问题吧
            if(dfs(n,j)>=p){
                printf("%d\n",j);
                break;
            }
        }
    }
    return 0;
}
*/
