#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;
//ac 22ms 01背包 恰好装满背包方案数
/*
题意:n个物品,每个物品的体积为w[i],放入容量为v的背包,
问恰好装满背包的方案数.
链接:https://www.luogu.com.cn/problem/P1164
思路:01背包,考虑初试状态dp[0]=1,其余状态为0.
*/
int n,v,w[N],dp[M];

int main(){
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=w[i];j--)
            dp[j]+=dp[j-w[i]];
    }
    printf("%d",dp[v]);
    return 0;
}

/*
//ac 48ms 二维数组实现
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,v,w[N],dp[N][M];

int main(){
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=v;j++){
            if(j>=w[i])
                dp[i][j]=dp[i-1][j]+dp[i-1][j-w[i]];
            else
                dp[i][j]=dp[i-1][j];
		}
    }
    printf("%d",dp[n][v]);
    return 0;
}
*/

/*
//第11组样例 TLE 90分 暴力枚举搜索
//这个也不必剪枝 剪枝了也会超时
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,v,w[N],dp[M],ans;

void dfs(int k,int sum){
    if(sum>v) return;//超过v 不是恰好装满
    if(sum == v){//恰好装满 方案数+1
        ans++;
        return;//不再累加 不能大于背包容积v
    }
    if(k == n+1)//物品编号枚举到了最后一个 返回
        return;
    dfs(k+1,sum+w[k]);
    dfs(k+1,sum);
}

int main(){
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    sort(w+1,w+1+n);
    ans=0;
    dfs(1,0);
    printf("%d",ans);
    return 0;
}
*/

/*
样例11:
input
36 32
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 4 8 16

output
2147483647
*/
