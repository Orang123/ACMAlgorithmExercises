/*
题意:摘自网上
病人要检验过敏源，现在有n种过敏源需要检测，给出过敏源在人体内个一存活得天数a[i]，
要求用最少的天数检测出过敏源，检测的条件即每个中过敏原有一个注册日期，在检验
的过程中，至少保证每种过敏原都有单独在人体内存活的一天，要求用最少得天数检测
出过敏原（直到体内所有的过敏原全部死亡）.
n<=20,a[i]<=7.
链接:https://www.luogu.com.cn/problem/UVA11691
思路:记忆化搜索.
dp[sta][k]表示当前已注射的过敏原的状态为sta,并且最后一个单独存活过敏原
剩下的时间为k时,对还未注射的过敏原要检测出来需要的最少的天数.
*/
//ac 70ms 记忆化搜索+状压+vis对过敏原存活时间标记
//不加vis对过敏原存活时间标记 2.23s
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[1<<N][8];

int dfs(int sta,int k){
    if(dp[sta][k]!=INF)
        return dp[sta][k];
    if(sta == (1<<n)-1)
        return dp[sta][k]=k;//剩下的时间为k
    int vis[8];
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++){
        if((sta & 1<<i) || vis[a[i]]) continue;
        vis[a[i]]=1;//当前状态下所选的过敏原天数相同的只需选一次,否则是重复搜索,不加这个剪枝,时间是2.23s
        //加入第i个过敏原后,第i个过敏原单独存在的时间为max(0,a[i]-k-1)
        //当a[i]>k时,在当前时刻注入第i个过敏原,使得k个时间点覆盖,等到上一个过敏原消失后,
        //再用1天检测第i个过敏原,第i个过敏原剩下时间为a[i]-k-1
        //当a[i]<=k时,注射第i个过敏原的时间需要保证,k个时间点过后,第i个过敏原恰好只剩1天时间用来检测,这样第i个过敏原剩下存活时间就为0
        //而等待的时间2种情况都是k+1.
        dp[sta][k]=min(dp[sta][k],dfs(sta|1<<i,max(0,a[i]-k-1))+k+1);
    }
    return dp[sta][k];
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        printf("%d\n",dfs(0,0));
    }
    return 0;
}

/*
//ac 0ms 大根堆 贪心做法
//摘自博客:https://www.cnblogs.com/avema/p/3921552.html
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <stack>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <iostream>
#define FFI freopen("in.txt", "r", stdin)
#define maxn 1010
#define INF 0x3f3f3f3f
#define inf 1000000000
#define mod 1000000007
#define ULL unsigned long long
#define LL long long
#define _setm(houge) memset(houge, INF, sizeof(houge))
#define _setf(houge) memset(houge, -1, sizeof(houge))
#define _clear(houge) memset(houge, 0, sizeof(houge))
using namespace std;

const int N = (1<<20)+5;
const int M = 30;

int n;
priority_queue <int> Q;

int main () {
    // FFI;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++ i) {
            int a;
            scanf("%d", &a);
            Q.push(a);
        }
        if(n == 1) {
            printf("%d\n", Q.top());
            Q.pop();
            continue;
        }
        int ans = 0;
        while(!Q.empty()) {
            int a = Q.top();
            Q.pop();
            int b = Q.top();
            Q.pop();
            if(Q.empty()) {
                ans += a+1;
                break;
            }
            ans += b;
            Q.push(a-b+1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
*/
