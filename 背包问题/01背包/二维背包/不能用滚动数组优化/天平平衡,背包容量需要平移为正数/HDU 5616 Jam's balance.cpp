#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 4100
using namespace std;
//ac 0ms 二维数组做法 砝码可放置在左右两侧,不要求全部放上去
//dp[i][j-w[i]]=dp[i-1][j]
//dp[i][j+w[i]]=dp[i-1][j]
/*
题意:n个砝码,每个砝码有一定重量w[i],每个砝码可以放在
天平的左侧或右侧,这个天平只能辨别天平两侧的物品的重量
是否相等,现在问这个天平能否测得重量为v的物品的重量.
说明:测试时实际天平两侧都可以有砝码,也就是物品可以和
砝码放在同一侧.并且并不是所有砝码都要放置.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5616
思路:01背包,sum是所有砝码重量和的2倍.
最后只需判断dp[n][sum/2+v]或dp[n][sum/2-v]是否合法.
若合法则在这种状态下,在天平某一侧放置物品,这样
左侧砝码+物品=右侧砝码 或左侧砝码=右侧砝码+物品,
物品重量就可得知.
*/
//dp[i][j]=1表示前i个砝码放置天平上得到重量差为|j-sum/2|这种情况是存在的
int n,m,w[N],dp[N][M],sum;

int main(){
    int T,v;
    scanf("%d",&T);
    while(T--){
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sum*=2;
        memset(dp,-1,sizeof(dp));
        dp[0][sum/2]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=sum;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=0;j<=sum;j++){
                if(dp[i-1][j] == -1) continue;
                dp[i][j-w[i]]=dp[i-1][j];
                dp[i][j+w[i]]=dp[i-1][j];
            }
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d",&v);
            if(dp[n][sum/2+v] == 1 || dp[n][sum/2-v] == 1)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}

/*
//ac 0ms 一维数组做法
//dp[j+w[i]]=dp[j]
//dp[j-w[i]]=dp[j]
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 4100
using namespace std;

int n,m,w[N],dp[M],vis[M],sum;

int main(){
    int T,v;
    scanf("%d",&T);
    while(T--){
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sum*=2;
        memset(dp,-1,sizeof(dp));
        dp[sum/2]=1;
        for(int i=1;i<=n;i++){
            //第i个阶段的dp[j]表示前i个砝码放置天平上得到重量差为|j-sum/2|这种情况是存在的
            memset(vis,0,sizeof(vis));
            for(int j=0;j<=sum;j++){
                if(dp[j] == -1) continue;
                vis[j-w[i]]=1;
                vis[j+w[i]]=1;
            }
            for(int j=0;j<=sum;j++)
                if(vis[j])
                    dp[j]=1;
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d",&v);
            if(dp[sum/2+v] == 1 || dp[sum/2-v] == 1)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
*/

/*
//ac 0ms 另一种转移
//dp[j]=dp[j-w[i]]
//dp[j]=dp[j+w[i]]
//不知道为啥这里必须判断dp[j-w[i]]是合法的
//直接vis[j]=dp[j-w[i]]会wa
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 4100
using namespace std;

int n,m,w[N],dp[M],vis[M],sum;

int main(){
    int T,v;
    scanf("%d",&T);
    while(T--){
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sum*=2;
        memset(dp,0,sizeof(dp));
        dp[sum/2]=1;
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            for(int j=0;j<=sum;j++){
            	if(j-w[i]>=0){
                    //不知道为啥这里必须判断dp[j-w[i]]是合法的
                    //直接vis[j]=dp[j-w[i]]会wa
            		if(dp[j-w[i]]==1)
            			vis[j]=1;
				}
            	if(j+w[i]<=sum){
            		if(dp[j+w[i]]==1)
            			vis[j]=1;
				}
            }
            for(int j=0;j<=sum;j++){
            	if(vis[j])
                    dp[j]=1;
			}
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d",&v);
            if(dp[sum/2+v] == 1 || dp[sum/2-v] == 1)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
*/

/*
//TLE 暴力枚举搜索 O(3^n)
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 2100
using namespace std;

int n,m,w[N],sum,vis[M][M];

void dfs(int k,int l,int r){
    vis[l][r]=1;
    if(k == n+1)
        return;
    dfs(k+1,l+w[k],r);//第i个砝码放在左侧
    dfs(k+1,l,r+w[k]);//第i个砝码放在右侧
    dfs(k+1,l,r);//不放第i个砝码
}

int main(){
    int T,v;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        dfs(1,0,0);
        scanf("%d",&m);
        while(m--){
            scanf("%d",&v);
            int flag=0;
            for(int l=0;l<=sum;l++){
                for(int r=0;r<=sum;r++){
                    if(vis[l][r] && (l+v==r || l==r+v)){
                        flag=1;
                        break;
                    }
                }
                if(flag) break;
            }
            if(flag)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
*/
