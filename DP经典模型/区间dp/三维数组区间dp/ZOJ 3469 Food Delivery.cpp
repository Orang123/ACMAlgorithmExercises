#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
题意:有一个人他外卖员要去送外卖，他的店在X位置，他的速度为(1/V)，也就是走V的单位长度需要花费V分钟,
然后现在有N个人要外卖，坐标分别为Xi， 这N个人每等一分钟不满意度增加Bi，
他送完所有人要让总的不满意度最少,求最少的不满意度是多少.
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827368754
思路:区间dp
dp[i][j][0]代表送完i~j停在i客户位置的最少不满意度
dp[i][j][1]代表送完i~j停在j客户位置的最少不满意度
*/

struct Node{
    int pos,val;
    bool operator < (const Node &x)const{
        return pos<x.pos;
    }
}node[1005];

int dp[1005][1005][2],sum[1005],n,v,x;

int main(){
    while(scanf("%d%d%d",&n,&v,&x)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d%d",&node[i].pos,&node[i].val);
        node[n+1].pos=x,node[n+1].val=0;//加入餐厅的位置,餐厅的不满意度,永远为0
        n++;
        sort(node+1,node+n+1);//排序方便dp 状态转移时从餐厅向两边的客户转移
        memset(dp,0x3f,sizeof(dp));
        int st;
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+node[i].val;//sum数组记录不满意度的前缀和
            if(node[i].pos == x){
                st=i;//记录餐厅的位置
                dp[i][i][0]=dp[i][i][1]=0;//最小的子状态应是从餐厅开始
            }
        }
        for(int i=st;i>=1;i--){//从餐厅的位置出发开始向客户位置转移
            for(int j=st;j<=n;j++){//右端点最小状态也是从餐厅开始 有意义的状态必须要包含餐厅位置
                if(i == j) continue;//i==j==st 在餐厅 已经是最小的子状态了,去掉if判断也不影响结果
                /*
                dp[i][j][0]可从dp[i+1][j][0] dp[i+1][j][1]转移而来,对于dp[i+1][j][0] 要从位置i+1再到啊位置i,之间的路程为node[i+1].pos-node[i].pos
                在这期间其余还没送到的客户(1~i j+1~n 这些位置)不满意度都在丞没分钟增加所以要用不满意度和 乘以时间
                */
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][0]+(node[i+1].pos-node[i].pos)*(sum[i]+sum[n]-sum[j]));
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][1]+(node[j].pos-node[i].pos)*(sum[i]+sum[n]-sum[j]));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+(node[j].pos-node[i].pos)*(sum[i-1]+sum[n]-sum[j-1]));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+(node[j].pos-node[j-1].pos)*(sum[i-1]+sum[n]-sum[j-1]));
            }
        }
        /*
        dp的过程中没有算上真实的速度,所以结果里统一乘上,如果要在dp里算上V,
        需要设置 long long 不然会溢出,因为中间dp的结果可能过大,而最终的结果本身是最小的.
        这个送外卖的途径最后一个客户一定是1或n,可以想如果最后一个送的客户在中间,
        那么实际上在送两端的时候中间的客户已经走过了,还不如直接在送两端经过中间的时候就给中间的一送呢
        所以最优解一定最后送的客户是1或n.
        */
        printf("%d\n",min(dp[1][n][0],dp[1][n][1])*v);
    }
    return 0;
}
/*
区间dp 枚举长度和起始点
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct Node{
    int pos,val;
    bool operator < (const Node &x)const{
        return pos<x.pos;
    }
}node[1005];

int dp[1005][1005][2],sum[1005],n,v,x;

int main(){
    while(scanf("%d%d%d",&n,&v,&x)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d%d",&node[i].pos,&node[i].val);
        node[n+1].pos=x,node[n+1].val=0;
        n++;
        sort(node+1,node+n+1);
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+node[i].val;
            if(node[i].pos == x)
                dp[i][i][0]=dp[i][i][1]=0;//最小子状态只有餐厅有意义
        }
        //这样时间复杂度相比从餐厅位置开始转移,会差一些
        for(int l=1;l<n;l++){//从小区间向大区间转移,其中有意义的小区间还是从餐厅位置开始的
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                if(i == j) continue;
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][0]+(node[i+1].pos-node[i].pos)*(sum[i]+sum[n]-sum[j]));
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][1]+(node[j].pos-node[i].pos)*(sum[i]+sum[n]-sum[j]));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+(node[j].pos-node[i].pos)*(sum[i-1]+sum[n]-sum[j-1]));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+(node[j].pos-node[j-1].pos)*(sum[i-1]+sum[n]-sum[j-1]));
            }
        }
        printf("%d\n",min(dp[1][n][0],dp[1][n][1])*v);
    }
    return 0;
}
*/

/*记忆化搜索
#include<algorithm>
#include<cctype>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<string>
#define ll long long
#define pr(x) cout << #x << " = " << (x) << '\n';
using namespace std;

const int MAXN = 1e3 + 11;

ll dp[MAXN][MAXN][2];
struct P {
    ll x, b;
    bool operator < (const P &t)const {
        return x < t.x;
    }
}a[MAXN];

int n;
ll X, v, sum[MAXN];

ll dfs(ll l, ll r, int sta) {
    ll &ret = dp[l][r][sta];

    if (ret >= 0) return ret;
    if (l == r) return ret = abs((X - a[l].x)) * v * sum[n];

    if (sta == 0) {
        ll mul = sum[l] + sum[n] - sum[r];
        ret = min(dfs(l + 1, r, 0) + (a[l + 1].x - a[l].x) * v * mul,
                  dfs(l + 1, r, 1) + (a[r].x - a[l].x) * v * mul);
    }
    else {
        ll mul = sum[l - 1] + sum[n] - sum[r - 1];
        ret = min(dfs(l, r - 1, 1) + (a[r].x - a[r - 1].x) * v * mul,
                  dfs(l, r - 1, 0) + (a[r].x - a[l].x) * v * mul);
    }

    return ret;
}

int main()
{
    while (~scanf("%d%d%lld", &n, &v, &X)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld%lld", &a[i].x, &a[i].b);
        }
        sort(a + 1, a + n + 1);

        sum[0] = 0;
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i].b;
        memset(dp, -1, sizeof dp);
        printf("%lld\n", min(dfs(1, n, 0), dfs(1, n, 1)));
    }
    return 0;
}
*/
