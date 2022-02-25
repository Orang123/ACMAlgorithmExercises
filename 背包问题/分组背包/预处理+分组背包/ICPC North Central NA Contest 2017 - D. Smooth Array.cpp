/*
题意:有n个数,给出两数k,s.每个数字可以改变成0-s.
让你以相邻的k个为一组[a[1]…a[k]],[a[2]…a[k+1]].
并且每组的每个位置对应的数都必须是完全相同的,
即:a[1]=a[k+1],a[2]=a[k+2],a[i] == a[i + j * k].
问使每一组的和为s.至少需要改变多少个数.

释义:题目的意思实际就是给出原本n个数字的串按照连续k
个为一组,分出[(n-1)/k]+1个长度为k的连续串出来,最后一个
连续串长度可能不够k,现在要使得这[(n-1)/k]+1每一个对应
位置的数字都相同并且每个串数字之和都是s,最少需要改变这
[(n-1)/k]+1串中原本多少个数字才能满足要求.
1<=n,k<=5000.
0<=a[i],s<=5000.
链接:https://nanti.jisuanke.com/t/43371
思路:参考博客图解:https://blog.csdn.net/tianyizhicheng/article/details/104600786
https://blog.csdn.net/qq_21433411/article/details/104619093
https://blog.csdn.net/The___Flash/article/details/104598915

n,k<=5000,dp复杂度必须是O(n^2)复杂度的才行.
可以将这[(n-1)/k]+1个串每个自上而下串竖排放置,这样可以将
每一竖列长度为k即:这些串的第1个位置、第2个位置、...、第k个位置
分别作为一列作为单独的一组,这样就会得到k个组,可能到了某个列时这组
的长度不够k,而是k-1.这样分组背包,将前i列每个横排放置长度为i的每个串
上数字的和上限s作为背包容量.每一组,第i列的物品是考虑将这一列的数字
全部改变为数字x时需要改变的数字个数,这个第i列要改变的数字个数实际就是
除了原本本身数字就是x外第i列其余位置不是x的个数.
dp[i][j]表示前i列长度为i的每个横排放置的串各个数字之和为j时最少需要改变
的数字个数,实际改变后的前i列每个横排串都是相同的.
那么状态转移方程就是dp[i][j]=min(dp[i][j],dp[i-1][j-x]+num[i]-cnt[i][x]);
num[i]是第i列的长度(k或k-1),cnt[i][x]表示第i列中数字为x的个数,num[i]-cnt[i][x]
就是第i列全变为x时要改变的数字个数.注意上面转移方程只是将第i列数字全部改变为本身
第i列就有的数字,实际第i列可能还能改变成别的本身没有的数字,那么就是第i列所有位置都要
改变,改变数字个数就是num[i],这时对应前i-1列和为j,只取实际前i-1列所改变数字最少的和j.
需要再用一个数组tp,tp[j]表示前j列前缀中改变数字最少的个数.那么转移是
dp[i][j]=min(dp[i][j],tp[j]+num[i]);
每次第i列dp转移完,就需要再更新tp前i列的前缀最小值改变数字最少的个数.转移方程是:
tp[j]=min(j?tp[j-1]:INF,dp[i][j]);

时间复杂度O(k*s*(n/k))=O(sn) 5000*5000=2.5*10^7
k越大,n/k就越小,k越小,n/k就越大. 实际第i组物品个数最多为n/k
所以复杂度可保证为O(ns) 在1s时限内

注意这个题目并不能用滚动数组优化成一维的,因为会有某一列本身存在数字是0,如果考虑
将其余不是0的数字改变为0,那么对于一维数组转移是dp[j]=dp[j-0]+num[i]-cnt[i][0],
而这个dp[j]可能已经是dp[i][j]就是前面的枚举第i列的数字可能已经更新过的值,并不能保证
是前i-1列的状态dp[i-1][j],就会导致第i列的数字改变多次 重复累加更改次数,导致结果偏大.
而且初始状态dp[0]本身就为0,对于前i列数字和为0的也无法更新为实际可能更大的改变个数.
*/
//ac 126ms 二维数组实现 记录最小改变数字个数
//dp[i][j]=min(dp[i][j],dp[i-1][j-x]+num[i]-cnt[i][x]);
//时间复杂度O(k*s*(n/k))=O(sn) 5000*5000=2.5*10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 5100
#define M 5100
#define INF 0x3f3f3f3f
using namespace std;

//dp[i][j]表示前i列长度为i的每个横排放置的串各个数字之和为j时最少需要改变
//的数字个数,实际改变后的前i列每个横排串都是相同的.
//tp[i][j]表示前i列长度中数字前缀和小于等于j中需要改变数字个数最少的个数,实际对应最少的个数 可能数字之和小于j,0~j中的某个数字
//num[i]表示第i列数字的个数,实际长度要么是k要么是k-1,因为最后一组连续串可能长度并不够k.
//cnt[i][x]表示第i列中数字为x的位置的个数
int n,k,s,dp[N][M],tp[M],num[N],cnt[N][M];
vector<int> a[N];

int main(){
    int x,id;
    scanf("%d%d%d",&n,&k,&s);
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        id=i%k+1;//列1~k
        num[id]++;//第id列数字个数+1
        if(!cnt[id][x])//第id列数字x还未记录
            a[id].push_back(x);
        cnt[id][x]++;//第id列数字x个数+1
    }
    memset(dp,0x3f,sizeof(dp));
    memset(tp,0,sizeof(tp));
    dp[0][0]=0;//初始状态 恰好装满数字之和为s的最小改变数字个数
    //时间复杂度O(k*s*(n/k))=O(sn) 5000*5000=2.5*10^7
    //k越大,n/k就越小,k越小,n/k就越大. 实际第i组物品个数最多为n/k
    //所以复杂度可保证为O(ns) 在1s时限内
    for(int i=1;i<=k;i++){//O(k)
        for(int j=0;j<=s;j++){//枚举 前i列构成的横排串数字之和为j
            for(int &x : a[i]){//枚举第i列可能保留的数字x O(n/k)
                if(j>=x)
                    //dp[i-1][j-x]表示前i-1列的横排串数字之和为j-x最少改变数字个数加上当前第i列数字x 恰好数字之和为j
                    dp[i][j]=min(dp[i][j],dp[i-1][j-x]+num[i]-cnt[i][x]);
                 //实际这个第i列没有对应的前i-1列的情况 直接在下面dp[i][j]=min(dp[i][j],tp[j]+num[i]);转移就好
                 //因为第i列并不是只能只能全放数字为0 才是总改变个数最少的
                 //else
                    //dp[i][j]=min(dp[i][j],dp[i-1][j]+num[i]);
            }
        }
        //考虑实际第i列可能本身不存在的数字,那么第i列要全部都改变为这个不存在数字,改变个数为num[i]
        //次数前i-1列只需考虑前缀和0~j内 改变数字最少的情况 即:tp[j]
        for(int j=0;j<=s;j++)
            dp[i][j]=min(dp[i][j],tp[j]+num[i]);
        //更新i长度的前缀和为0~j时最少改变的数字个数
        for(int j=0;j<=s;j++)
            tp[j]=min(j?tp[j-1]:INF,dp[i][j]);
    }
    printf("%d",dp[k][s]);
    return 0;
}

/*
//ac 138ms 二维数组实现 记录最多不改变本身保留数字个数
//dp[i][j]=max(dp[i][j],dp[i-1][j-x]+cnt[i][x]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 5100
#define M 5100
using namespace std;

//dp[i][j]表示前i列长度为i的每个横排放置的串各个数字之和为j时最多不改变本身保留数字个数
//tp[i][j]表示前i列长度中数字前缀和小于等于j中不改变本身保留数字个数最多的个数,实际对应最多的个数 可能数字之和小于j,0~j中的某个数字
//cnt[i][x]表示第i列中数字为x的位置的个数
int n,k,s,dp[N][M],tp[M],cnt[N][M];
vector<int> a[N];

int main(){
    int x,id;
    scanf("%d%d%d",&n,&k,&s);
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        id=i%k+1;
        if(!cnt[id][x])
            a[id].push_back(x);
        cnt[id][x]++;
    }
    memset(tp,0,sizeof(tp));
    memset(dp,-0x3f,sizeof(dp));
    dp[0][0]=0;//初始状态 是恰好装满背包的问题
    for(int i=1;i<=k;i++){
        for(int j=0;j<=s;j++){
            for(int &x : a[i]){
                if(j>=x)
                    dp[i][j]=max(dp[i][j],dp[i-1][j-x]+cnt[i][x]);
            }
        }
        for(int j=0;j<=s;j++)
            dp[i][j]=max(dp[i][j],tp[j]);
        for(int j=0;j<=s;j++)
            tp[j]=max(j?tp[j-1]:0,dp[i][j]);
    }
    //最少需要改变的个数就是 n-dp[k][s]
    printf("%d",n-dp[k][s]);
    return 0;
}
*/
