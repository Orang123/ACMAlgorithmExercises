/*
题意:摘自网上
给定一个长度为n的序列，每个数是v[i]，然后再给出n个数a[i],表示合成i个数的代价。
每次可以将连续的子序列和成一个数，即为序列中各个项的和。
要求将给定长度n的序列变成一个回文串，一个数字只能被合成一次。
求出合并的最小代价.
n<=5000,v[i]<=10^9,a[i]<=10^4.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4960
思路:因为要变成回文,就需要枚举左端开始的连续数字是否和右端开始的连续数字相等.
因为合并不同个数的连续序列需要的花费不同,无法贪心考虑,需要枚举所有可能合并的
情况,列如先合并2个,再合并5个,亦或是直接合并7个亦或是先合并3个,再合并4个等等.
然而对于不同情况合并后新生成的新序列,实际是有可能相同的,也就是说,对于(l,r)的
序列是有可能重复的,这是在枚举生成新序列的过程中产生了重叠子问题,因此在搜索的
过程中需要记录下重叠子问题的最优解,当再次出现重叠子问题时,直接返回这个结果.
记忆化搜索 dp[l][r]表示序列所属区间在[l,r]时合并成回文串时所需最小花费
*/
//ac 624ms 记忆化搜索
//时间复杂度是O(n*n*cnt),因为dp[i][j]只会计算一次
//dp[l][r]表示序列所属区间在[l,r]时合并成回文串时所需最小花费
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
typedef long long ll;
using namespace std;

int n,v[N],a[N],dp[N][N];
ll sum[N];//sum[i]表示1~i序列的前缀和

int dfs(int l,int r){
    if(dp[l][r]!=-1)
        return dp[l][r];
    if(l>=r)
        return dp[l][r]=0;
    //子串(l,r)合并成回文串的初始状态是直接将长度为r-l+1的整个子串合并成一个数字的花费
    //因为下面的判断左右两端子串不包括这个情况,因此这个状态需要单独考虑.
    dp[l][r]=a[r-l+1];
    int ll=l,rr=r;
    //枚举左右两端相等的连续子串来合并,先枚举长度较小的子串合并,回溯后,再枚举长度较长的子串合并
    while(ll<rr){
        if(sum[ll]-sum[l-1]<sum[r]-sum[rr-1])//左端的前缀比右端的后缀小,增大左端前缀的长度
            ll++;
        else if(sum[ll]-sum[l-1]>sum[r]-sum[rr-1])//左端的前缀比右端的后缀大,增大右端前缀的长度
            rr--;
        else{//左端的前缀和右端的后缀长度相等时,将左右两端合并判断继续判断中间部分的子串(ll+1,rr-1)需要合并的最少花费
            dp[l][r]=min(dp[l][r],a[ll-l+1]+dfs(ll+1,rr-1)+a[r-rr+1]);
            ll++;
            rr--;
        }
    }
    return dp[l][r];
}

int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-1,sizeof(dp));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            scanf("%d",&v[i]);
            sum[i]+=sum[i-1]+v[i];
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        printf("%d\n",dfs(1,n));
    }
    return 0;
}

/*
//ac 514ms 预处理相等子段区间+记忆化搜索
//dp[l][r]表示序列所属区间在[l,r]时合并成回文串的最小花费
//时间复杂度是O(n*n*cnt),因为dp[i][j]只会计算一次
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
typedef long long ll;
using namespace std;

int n,v[N],a[N],dp[N][N],cnt;
ll sum[N];
struct Section{
    int l,r;
    Section(int l=0,int r=0):l(l),r(r){}
}sec[N/2];//左右相等子串最大长度是N/2

int dfs(int l,int r,int i){
    if(dp[l][r]!=-1)
        return dp[l][r];
    if(l>=r)
        return dp[l][r]=0;
    dp[l][r]=a[r-l+1];
    while(i<=cnt){//i是左右两端相等子串的下标,先枚举较小的子串i合并,回溯回来再枚举较大的子串i+1
        dp[l][r]=min(dp[l][r],a[sec[i].l-l+1]+dfs(sec[i].l+1,sec[i].r-1,i+1)+a[r-sec[i].r+1]);
        i++;
    }
    return dp[l][r];
}

int main(){
    while(scanf("%d",&n) && n){
        cnt=0;
        memset(dp,-1,sizeof(dp));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            scanf("%d",&v[i]);
            sum[i]+=sum[i-1]+v[i];
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int l=1,r=n;
        while(l<r){//预处理出左右相等子串的所有情况
            if(sum[l]<sum[n]-sum[r-1])
                l++;
            else if(sum[l]>sum[n]-sum[r-1])
                r--;
            else{
                sec[++cnt]=Section(l,r);
                l++;
                r--;
            }
        }
        printf("%d\n",dfs(1,n,1));
    }
    return 0;
}
*/

/*
//ac 109ms 正向dp 没完全理解,这类题目正向的动态规划都需要完全把问题看透才行,并不容易,
//因为初始状态不好确定,还是建议 写记忆化搜索的递归版本
//摘自博客:https://www.cnblogs.com/zibaohun/p/4046801.html
//先记录前i个的和和后n  - j个和相同的(i,j)对，然后进行dp，
//dp[i]表示合并前i个和合并后n - g[i]个和合并所需最小代价，
//那么有递推公式dp[i] = min(dp[j] + b[i-j] + b[k - t]);
//所求ans即为min(dp[i] + b[g[i] - i - 1]);
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include<set>
#include <iostream>
#include <algorithm>
using namespace std;
#define RD(x) scanf("%d",&x)
#define RD2(x,y) scanf("%d:%d",&x,&y)
#define clr0(x) memset(x,0,sizeof(x))
typedef long long LL;
#define N 10005
int n , m , K;
int a[N] , b[N];
LL sum[N];
int f[N] , g[N];

void work(){
    int i , j , k , t;
    int ans;
    sum[0] = 0;
    a[0] = 0;
    for (i=1;i<=n;++i) scanf("%d",&a[i]) , sum[i] = sum[i-1] + a[i];
    for (i=1;i<=n;++i) scanf("%d",&b[i]); ans = b[n]; b[0] = 0;
    j = n;
    for (i=1;i<=n;++i){
        while (sum[n] - sum[j-1] < sum[i]) --j;
        if (sum[n] - sum[j-1] == sum[i])
            g[i] = j;
        else g[i] = -1;
    }
    memset(f,0x3f,sizeof(f));
    g[0] = n+1; f[0] = 0;
    for (i=1;i<=n;++i){
        if (g[i] == -1) continue;
        t = g[i];
        for (j=0;j<i;++j){
                if (g[j] == -1) continue;
                k = g[j];
                if (t <= i) continue;
                f[i] = min(f[i],f[j]+b[i-j]+b[k-t]);
                ans = min(ans,f[i]+b[t-i-1]);
        }
    }
    printf("%d\n",ans);
}

int main(){
    while (~scanf("%d",&n) && n)
            work();
    return 0;
}
*/

/*
//ac 31ms 正向dp
//摘自博客:https://blog.csdn.net/u013840081/article/details/48231977
//思路：由于最后需要转化成回文序列，我们可以从两端开始模拟，如果左边的数小于右边的数，
那么左边加上下一个数，如果左边大于右边，那么右边加上下一个数，直到二者相等，那么这部分就作为一个整体，
分别记录下左边和右边合并了多少数字。假设最后左右各有len个部分，但这len个部分还可以从两端或中间合并来得到更小的花费，
所以我们dp一下，dp【i】为左右对称前i个部分合并的最小代价，那么dp【i】=min(,dp【j】+cost【左边j到i 部分合并的个数】+cost【右边j到i 部分合并的个数】)，
这是从两端的最小花费。从中间合并的时候，分别减去两端合并的个数，再加上中间合并的花费就行了。
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include<climits>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;

#define PB push_back
#define MP make_pair

#define REP(i,x,n) for(int i=x;i<(n);++i)
#define FOR(i,l,h) for(int i=(l);i<=(h);++i)
#define FORD(i,h,l) for(int i=(h);i>=(l);--i)
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define RI(X) scanf("%d", &(X))
#define RII(X, Y) scanf("%d%d", &(X), &(Y))
#define RIII(X, Y, Z) scanf("%d%d%d", &(X), &(Y), &(Z))
#define DRI(X) int (X); scanf("%d", &X)
#define DRII(X, Y) int X, Y; scanf("%d%d", &X, &Y)
#define DRIII(X, Y, Z) int X, Y, Z; scanf("%d%d%d", &X, &Y, &Z)
#define OI(X) printf("%d",X);
#define RS(X) scanf("%s", (X))
#define MS0(X) memset((X), 0, sizeof((X)))
#define MS1(X) memset((X), -1, sizeof((X)))
#define LEN(X) strlen(X)
#define F first
#define S second
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)
#define Dpoint  strcut node{int x,y}
#define cmpd int cmp(const int &a,const int &b){return a>b;}

const int MOD = 1e9+7;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long LL;
typedef pair<int,int> PII;
//#define HOME

int Scan()
{
	int res = 0, ch, flag = 0;

	if((ch = getchar()) == '-')				//判断正负
		flag = 1;

	else if(ch >= '0' && ch <= '9')			//得到完整的数
		res = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9' )
		res = res * 10 + ch - '0';

	return flag ? -res : res;
}



int a[5005];
int cost[5005];
int dp[5005];
int ll[5005];
int rr[5005];
int main()
{ int n;
while(RI(n)!=EOF)
{   if(!n)
break;
     for(int i=1;i<=n;i++)
      RI(a[i]);
     for(int i=1;i<=n;i++)
        RI(cost[i]);
    int len=0;
    for(int i=1,j=n;i<j;i++,j--)
    {
        long long int lsum=a[i];
        long long int rsum=a[j];
        int lnum=1;
        int rnum=1;

        while(lsum!=rsum)
        {
            if(lsum<rsum)
            {
                lsum+=a[++i];
                lnum++;
            }
            else
            {
                rsum+=a[--j];
                rnum++;
            }
        }
        if(lsum==rsum)
        {len++;
         ll[len]=lnum;
         rr[len]=rnum;
        }


    }
    dp[0]=0;
    for(int i=1;i<=len;i++)
    {
        dp[i]=INT_MAX;
        int lt=0,rt=0;
        for(int j=i;j>=1;j--)
        {  lt+=ll[j];
           rt+=rr[j];

            dp[i]=min(dp[i],dp[j-1]+cost[lt]+cost[rt]);}
    }
    int ans=cost[n];
    for(int i=1;i<=len;i++)
    {
        n-=ll[i]+rr[i];
        ans=min(ans,dp[i]+cost[n]);
    }
    printf("%d\n",ans);

}



        return 0;
}
*/
