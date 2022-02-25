#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 20100
using namespace std;
//ac 12ms 区间右移扩大区间 [0,20000]
/*
题意:终于Alice走出了大魔王的陷阱,可是现在傻傻的她忘了带武器了,这可如何是好???这个时候,
一个神秘老人走到她面前答应无偿给她武器,但老人有个条件,需要将所选武器分别放在天平的两端,
若天平平衡则可以将天平上的所有武器拿走,还好这个天平锈迹斑斑,只要两端重量相差小于等于m就
会保持平衡,Alice傻傻的认为越重的武器越好,求Alice最多能拿走的武器总重量.(不限操作次数)
链接:https://ac.nowcoder.com/acm/problem/19158?&headNav=acm
思路:还是天平平衡,每个物品可以放天平左侧也可以放天平右侧,也可以不放.
区别是平衡的条件是降低了,并不是左侧重量等于右侧重量,而是左右侧重量差
不超过m,那么实际平衡的可能情况就是[sum/2-m,sum/2+m]
*/
//dp[i][j]表示将i个武器放置在天平上得到左右两侧重量差为j-sum/2的所有武器的最大重量.
//j-sum/2为父表示左侧重,j-sum/2为正表示右侧重
int n,m,w[N],sum,dp[N][M];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        sum+=w[i];
    }
    sum<<=1;
    dp[0][sum/2]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++)
            dp[i][j]=dp[i-1][j];
        for(int j=sum;j>=0;j--){
            if(dp[i-1][j]<0) continue;
            dp[i][j-w[i]]=max(dp[i][j-w[i]],dp[i-1][j]+w[i]);
            dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);
        }
    }
    int ans=0;
    //平衡条件可能是左侧比右侧重m即:[sum/2-m,sum/2],也可能是右侧比左侧重m即:[sum/2,sum/2+m]
    for(int i=sum/2-m;i<=sum/2+m;i++){
        if(dp[n][i]>0)
            ans=max(ans,dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 9ms 不扩大区间 [0,10000]
//dp[i][abs(j-w[i])]=max(dp[i][abs(j-w[i])],dp[i-1][j]+w[i]);
//dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);
//实际对于左侧比右侧重m,还是右侧比左侧重m,对这个最大值并没有影响.
//因此就在[0,sum]内模拟01背包,dp[0][0]为初始状态
//dp[i][j]表示将i个武器放置在天平上得到左右两侧重量差为j的所有武器的最大重量.
//这里不区分到底是左侧重还是右侧重
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,m,w[N],sum,dp[N][M];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        sum+=w[i];
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++)
            dp[i][j]=dp[i-1][j];
        for(int j=0;j<=sum;j++){
            if(dp[i-1][j]<0) continue;
            //j-w[i]本身可能为负,表示左侧较重,取绝对值后,不区分到底左右两侧谁重,只表示左右差值
            //只取这个最优解的结果
            //对于本身力臂为-2的变成2后,原先-2+2=0 第二次放右侧能平衡,现在放右侧2+2=4 不平衡,但是每个物品都会枚举放左侧放右侧,
            //如果考虑枚举放左侧 2-2=0 就会平衡,不影响其结果的正确性.
            dp[i][abs(j-w[i])]=max(dp[i][abs(j-w[i])],dp[i-1][j]+w[i]);
            dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        if(dp[n][i]>0)
            ans=max(ans,dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 22ms 区间右移扩大2倍做法 [0,20000]
//dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);
//dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+w[i]);
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 20100
using namespace std;

int n,m,w[N],sum,dp[N][M];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        sum+=w[i];
    }
    sum<<=1;
    dp[0][sum/2]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++){
            dp[i][j]=dp[i-1][j];
            if(j+w[i]<=sum && dp[i-1][j+w[i]]>=0)
                dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);
            if(j-w[i]>=0 && dp[i-1][j-w[i]]>=0)
                dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+w[i]);
        }
    }
    int ans=0;
    for(int i=sum/2-m;i<=sum/2+m;i++){
        if(dp[n][i]>0)
            ans=max(ans,dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 11ms 不扩大区间 [0,10000]
//dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);
//dp[i][j]=max(dp[i][j],dp[i-1][abs(j-w[i])]+w[i]);
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,m,w[N],sum,dp[N][M];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        sum+=w[i];
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++){
            dp[i][j]=dp[i-1][j];
            if(j+w[i]<=sum)
                dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);
            dp[i][j]=max(dp[i][j],dp[i-1][abs(j-w[i])]+w[i]);
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        if(dp[n][i]>0)
            ans=max(ans,dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}
*/
