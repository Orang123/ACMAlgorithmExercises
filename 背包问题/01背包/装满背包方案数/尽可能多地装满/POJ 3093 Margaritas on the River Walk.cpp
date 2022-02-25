#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 1100
using namespace std;
//ac 0ms 一维数组实现 01背包 尽可能多地装满背包方案数
//逆序从n开始枚举装不下的物品 优化后的时间复杂度O(nv)
//《浅谈积累背包问题》 徐持衡 pdf有解释POJ 3093这道题
/*
题意:n个物品,每个物品的体积为w[i],放入容量为v的背包,
问背包再也装不下任何物品的方案数,即:尽可能多地装满背包
的方案数.
链接:http://poj.org/problem?id=3093
思路:首先如果像恰好装满背包方案数那样统计,即:dp[v]+=dp[v-w],
只是初试状态都是1,那么假如第一个物品体积2,dp[2]+=dp[2-2],dp[2]=1+1=2,显然结果是错的.
所以01背包它这个本身只能统计恰好装满的情况,所以就尝试把尽可能多地装满的方案转化为恰好
装满背包情况的方案统计,但是问题是恰好装满又不知道具体哪些容量是恰好装满.可以将物品按照
体积从大到小排序,枚举假设第i个物品是恰好装不进去的(背包剩余容量比第i个物品体积至少小1),
那么编号为1~(i-1)的物品肯定是全部放入背包了,这个时候对背包剩余容量在编号为n~(i+1)物品中
做01背包尝试装入一些物品使得背包剩余容量不够装下第i个物品,使得之前的假设成立,而n~i+1中
剩下未装入背包的物品体积都比第i个物品体积大,所以这些剩下的物品也全都无法装入背包,所以此时
装入背包的物品使得背包再也装不下别的物品,达到了尽可能多地装满背包.所以具体的做法里装入背包
的物品需要逆序从最大体积的物品n开始装.

dp[i][v]表示的是n~(i+1)个物品中恰好装满容量为v背包的方案数 实际滚动数组优化掉了第一位度i 只有dp[v]
*/
int n,v,w[N],dp[M],sum,ans;

int main(){
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        ans=sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sort(w+1,w+1+n);
        //如,n=6,v=4,w[i]={8,9,8,7,16,5}
        //不特判dp时i==1时,ans累加的循环里,j下界=0,上界=4 ans会累加dp[0]=1,会错误输出1
        if(w[1]>v){
            printf("%d 0\n",t);
            continue;
        }
        dp[0]=1;//初始状态 只有0为1,必须是恰好装满背包
        //逆序从体积最大的物品开始枚举,假设i是恰好不能装入背包的物品
        for(int i=n;i>=1;i--){
            sum-=w[i];//sum表示1~(i-1)物品预先装入背包所占据的容积
            //v-sum是1~(i-1)物品装入背包后剩余的容积
            //这里是枚举n~(i+1)物品可能占据的当前背包剩余容量
            //v-sum-w[i]+1表示所选择的n~(i+1)物品必须至少恰好装满v-sum-w[i]+1剩余背包容量
            //v-sum-w[i] 表示背包剩余容量除去第i个物品占据的容量所剩下的容量,+1是为了使得
            //剩下的背包容量至少比第i个物品的体积少1,这样就能保证第i个物品不能装入背包.保证枚举假设的正确性.
            //所以v-sum-w[i]+1是枚举n~(i+1)恰好装满背包的下界,上界为v-sum.
            //而下界要保证不能为负数,因为v-sum可能为负,就是实际1~(i-1)的物品并不能全部放入背包
            //那么当前的假设就是不成立的,这里v-sum-w[i]+1<0,和0取最大后j=0,v-sum<0就能保证ans不累加任何dp[j]
            //或者当i == n,v-sum实际比w[i]小时,那么实际只有w[i]是装不下的,这时max运算j下界为0,而dp[0]=1可以算一种方案
            //eg:n=3,v=3 w[i]={1,2,4} 方案数为1 只有{1,2}这种方案组合
            for(int j=max(v-sum-w[i]+1,0);j<=v-sum;j++)
                //累加n~(i+1)物品中恰好装满的容量j的方案数,j是在当前剩余背包容量内占据的容量,
                //而且v-sum-j<w[i],能保证当前装完n~(i+1)物品后剩下的背包容积也装不下第i个物品,从而保证假设的正确性.
                ans+=dp[j];//上一状态dp[j] 选择n~(i+1)的物品装入容量为j的背包恰好装满的方案数
            //在上一状态n~(i+1)的物品最优解基础上放入第i个物品,求解编号为n~i的物品中01背包的最优解
            //因为背包剩余容积不确定,这里是取初始背包容积
            for(int j=v;j>=w[i];j--)
                dp[j]+=dp[j-w[i]];
        }
        printf("%d %d\n",t,ans);
    }
    return 0;
}
/*
//ac 0ms 二维数组实现 逆序从n开始枚举装不下的物品 时间复杂度O(nv)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 1100
using namespace std;

int n,v,w[N],dp[N][M],sum,ans;

int main(){
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        ans=sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sort(w+1,w+1+n);
        if(w[1]>v){
            printf("%d 0\n",t);
            continue;
        }
        for(int i=n+1;i>=2;i--)
            dp[i][0]=1;
        for(int i=n;i>=1;i--){
            sum-=w[i];
            for(int j=max(v-sum-w[i]+1,0);j<=v-sum;j++)
                ans+=dp[i+1][j];
            for(int j=w[i];j<=v;j++)//升序 降序都可
                //不能写成dp[i][j]+=dp[i+1][j-w[i]],因为只加上了dp[i+1][j-w[i]],
                //原先前n~i+1物品放入背包容量为j恰好装满的方案数dp[i+1][j]没加上
                //HDU 2126那题是滚动数组优化后二维,没优化之前应该是三维数组dp,和下面这个写法是一样的,不能"+="
                dp[i][j]=dp[i+1][j]+dp[i+1][j-w[i]];
        }
        printf("%d %d\n",t,ans);
    }
    return 0;
}
*/

/*
摘自博客:https://blog.csdn.net/ayyyyy_zc/article/details/88887718
//ac 0ms 从第1个物品开始枚举装不下 dp 复杂度O(n^2*v)
//之所以复杂度多一个维度是因为 同一个物品多次被考虑放入背包,这样会造成
//时间的浪费,观察得到第i件物品共考虑了i-1次.每一次循环都会少一件物品.如果
//逆序从第n个物品开始枚举作为不能放入背包的物品,在对n~(i-1)物品进行01背包
//利用滚动数组优化一个物品就可只放入一次,就能在O(nv)复杂度内完成dp 来自《浅谈几类背包问题》 徐持衡
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 2e3;
int dp[maxn],s[50];
int main()
{
    ios::sync_with_stdio(false);
//    freopen("in.txt", "r", stdin);
    int T,cas=1;
    cin>>T;
    while(T--)
    {
        int n,sum=0,v,ans = 0;
        cin>>n>>v;
        s[0] = 0;
        for(int i = 1; i<=n; i++) cin>>s[i];
        sort(s+1,s+1+n);
        for(int i = 1; i<=n; i++)
        {
            memset(dp,0,sizeof(dp));
            sum+=s[i-1];
            dp[sum] = 1;//初始状态是1~(i-1)的物品所占的容积
            //每次i都需要做一遍 (i+1)~n的01背包 O(nv)
            //对(i+1)~n做01背包,得累加上本身的sum(1~(i-1)的所有物品)
            for(int j = i+1; j<=n; j++)//对于每个比枚举的物品大的物品
                for(int k = v-s[j]; k>=sum; k--) dp[k+s[j]]+=dp[k];
            //v-s[i] 背包中已经装入的物品所占容积 这里的j代表的也是1~i-1全部物品和i+1~n的部分物品所占容积
            for(int j = max(1,v-s[i]+1); j<=v; j++) ans+=dp[j];//+1是为了装不下s[i]
        }
        cout<<cas++<<" "<<ans<<endl;
    }
    return 0;
}
*/

/*
//摘自博客:http://www.cppblog.com/csu-yx-2013/archive/2012/08/30/188748.html
//ac 16ms 记忆化搜索
//背包问题不建议用记忆化搜索去做,可能会错,因为记忆化搜索并不是线性分解枚举子问题的背包的容量的
//有些子问题的背包容量不能通过分解得到 最后答案可能会出错
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long INT;
INT nAns[40][1010];
INT nValue[100];
INT nSum[100];
INT nN, nM;

INT GetAns(INT nNum, INT nMoney)
{
    if (nAns[nNum][nMoney] == -1)
    {
        if (nNum == 0)
        {
            nAns[nNum][nMoney] = 1;
            if (nMoney == nM)
            {
                nAns[nNum][nMoney] = 0;
            }
        }
        else
        {
            INT nRet = 0;

            if (nMoney - nSum[nNum - 1] >= nValue[nNum])
            {
                nRet = GetAns(nNum - 1, nMoney - nValue[nNum]);
            }
            else
            {
                if (nMoney >= nValue[nNum])
                {
                    nRet += GetAns(nNum - 1, nMoney - nValue[nNum]);
                }
                nRet += GetAns(nNum - 1, nMoney);
            }

            nAns[nNum][nMoney] = nRet;
        }
    }
    return nAns[nNum][nMoney];
}

int main()
{
    INT nT;

    scanf("%I64d", &nT);
    for (INT i = 1; i <= nT; ++i)
    {
        scanf("%I64d%I64d", &nN, &nM);
        for (INT j = 1; j <= nN; ++j)
        {
            scanf("%I64d", &nValue[j]);
        }
        memset(nAns, -1, sizeof(nAns));
        sort(nValue + 1, nValue + nN + 1);
        nSum[0] = 0;
        for (INT j = 1; j <= nN; ++j)
        {
            nSum[j] = nSum[j - 1] + nValue[j];
        }
        printf("%I64d %I64d\n", i, GetAns(nN, nM));
    }

    return 0;
}
*/

/*
直接暴力枚举搜索 模拟 不太好实现
每次都需要判断剩下未放入背包的最小物品是否还能放入背包,不能放入的时候才说明背包再不能放入物品了 也会TLE
*/
