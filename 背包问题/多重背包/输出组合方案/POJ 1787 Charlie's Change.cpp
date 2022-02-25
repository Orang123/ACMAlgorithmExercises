/*
题意:4种面值为1、5、10、25的硬币各有num[i]枚,现在求恰好能凑出p面值钱的
硬币的最多个数,并输出各个面值硬币所用的个数.
链接:http://poj.org/problem?id=1787
思路:带物品数量限制的完全背包+一维空间记录路径,当容量为j时放入第i种硬币
所用硬币个数更多时,记录pre[j]=j-val[i],那么实际输出方案时就是j-pre[j]就能
知道某一容量j状态下所用哪一种硬币.

注意:这里不能记录pre[j-val[i]]=j,因为统计每个硬币选了几个时,j是从0开始转移的,
但它的终止状态并不能保证是给出的金额p.
*/
//ac 94ms 428K 带物品数量限制的完全背包+一维空间记录路径
//这种做法不好理解,建议用后面的2种做法
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
#define M 10010
using namespace std;

//pre[j]记录背包容量为j时最优解的上一状态,pre[j]<j,终止状态为pre[j]=0
int val[N]={0,1,5,10,25},num[N],p,pre[M],cnt[M],dp[M];

int main(){
    while(scanf("%d%d%d%d%d",&p,&num[1],&num[2],&num[3],&num[4])){
        if(p+num[1]+num[2]+num[3]+num[4] == 0)
            break;
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=4;i++){
            memset(cnt,0,sizeof(cnt));
            for(int j=val[i];j<=p;j++){
                if(dp[j-val[i]] == -1) continue;
                if(dp[j-val[i]]+1>dp[j] && cnt[j-val[i]]<num[i]){
                    dp[j]=dp[j-val[i]]+1;
                    cnt[j]=cnt[j-val[i]]+1;
                    pre[j]=j-val[i];//记录上个状态不用第i种硬币时恰好凑出的面值
                }
            }
        }
        if(dp[p]<0){
            printf("Charlie cannot buy coffee.\n");
            continue;
        }
        //注意这里num[i]代表面值为i的硬币的个数,而前面的num[i]是第i种硬币的个数
        memset(num,0,sizeof(num));
        int j=p;
        while(j){//因为是恰好装满,所以初始状态一定是 0面值
            num[j-pre[j]]++;//j-pre[j]代表容量为j时最大硬币个数最优解是放入面值为j-pre[j]的硬币,这种硬币个数+1
            j=pre[j];//最优解的上一状态
        }
        printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",num[1],num[5],num[10],num[25]);
    }
    return 0;
}

/*
//ac 94ms 544K 带物品数量限制的完全背包+二维数组记录个数路径
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define M 10010
using namespace std;

//vis[i][j]=k表示恰好装满背包容量j时,在用的硬币数最多的方案中,第i种硬币用了k个
int val[N]={0,1,5,10,25},num[N],p,vis[N][M],dp[M];

int main(){
    while(scanf("%d%d%d%d%d",&p,&num[1],&num[2],&num[3],&num[4])){
        if(p+num[1]+num[2]+num[3]+num[4] == 0)
            break;
        memset(vis,0,sizeof(vis));
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=4;i++){
            for(int j=val[i];j<=p;j++){
                if(dp[j-val[i]] == -1) continue;
                if(dp[j-val[i]]+1>dp[j] && vis[i][j-val[i]]<num[i]){
                    dp[j]=dp[j-val[i]]+1;
                    vis[i][j]=vis[i][j-val[i]]+1;
                }
            }
        }
        if(dp[p] == -1){
            printf("Charlie cannot buy coffee.\n");
            continue;
        }
        memset(num,0,sizeof(num));
        int i=4,j=p;
        while(j){
            if(vis[i][j]){//代表最多方案中使用到了vis[i][j]个第i种硬币
                num[i]=vis[i][j];
                j-=val[i]*num[i];//最优方案的上一状态 是背包容量为j-val[i]*num[i]
            }
            i--;
        }
        printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",num[1],num[2],num[3],num[4]);
    }
    return 0;
}
*/

/*
//ac 329ms 544K 二进制优化+二维数组记录个数路径
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define M 10010
using namespace std;

//vis[i][j]=k表示恰好装满背包容量j时,在用的硬币数最多的方案中,第i种硬币用了k个
int val[N]={0,1,5,10,25},num[N],p,vis[N][M],dp[M];

int main(){
    while(scanf("%d%d%d%d%d",&p,&num[1],&num[2],&num[3],&num[4])){
        if(p+num[1]+num[2]+num[3]+num[4] == 0)
            break;
        memset(vis,0,sizeof(vis));
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        int tv;
        for(int i=1;i<=4;i++){
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tv=k*val[i];
                for(int j=p;j>=tv;j--){
                    if(dp[j-tv] == -1) continue;
                    if(dp[j-tv]+k>dp[j]){
                        dp[j]=dp[j-tv]+k;
                        vis[i][j]=vis[i][j-tv]+k;//第i种硬币用了k个
                    }
                }
            }
        }
        if(dp[p] == -1){
            printf("Charlie cannot buy coffee.\n");
            continue;
        }
        memset(num,0,sizeof(num));
        int i=4,j=p;
        while(j){
            if(vis[i][j]){
                num[i]=vis[i][j];
                j-=val[i]*num[i];
            }
            i--;
        }
        printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",num[1],num[2],num[3],num[4]);
    }
    return 0;
}
*/
