/*
题意:有各种不同面值的货币，每种面值的货币有不同的数量，请找出利用这些货币可以凑成的最接近且小于等于给定的数字cash的金额。
链接:http://poj.org/problem?id=1276
思路:
*/
//ac 32ms 可行性求解 完全背包
//复杂度O(nv)=10*10^5=10^6
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        dp[0]=0;
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=v;j++){
                if(dp[j]!=-1)
                    dp[j]=num[i];
                if(j>=w[i]){
                    dp[j]=max(dp[j],dp[j-w[i]]-1);
                    if(dp[j]!=-1)
                        ans=max(ans,j);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 16ms 限制物品数量的完全背包
//复杂度O(nv)=10*10^5=10^6
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M],cnt[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        int ans=0;
        dp[0]=1;
        for(int i=1;i<=n;i++){
            memset(cnt,0,sizeof(cnt));
            for(int j=w[i];j<=v;j++){
                if(dp[j-w[i]] && !dp[j] && cnt[j-w[i]]+1<=num[i]){
                    dp[j]=1;
                    cnt[j]=cnt[j-w[i]]+1;
                    ans=max(ans,j);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 47ms 背包九讲 二进制优化版 完全背包+01背包 和明显比下面标准的二进制优化(79ms)要快
//复杂度比标准的二进制优化这个时间界O(∑log(num[i])*v) 可能要低
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        int tw;
        for(int i=1;i<=n;i++){
            if(num[i]*w[i]>=v){//第i种物品所有物品体积和不小于背包容积v时 完全背包
                for(int j=w[i];j<=v;j++)
                    dp[j]=max(dp[j],dp[j-w[i]]+w[i]);
            }
            else{//否则 二进制优化 01背包
                for(int k=1;num[i]>0;k<<=1){
                    num[i]-=k;
                    if(num[i]<0) k+=num[i];
                    tw=w[i]*k;
                    for(int j=v;j>=tw;j--)
                        dp[j]=max(dp[j],dp[j-tw]+tw);
                }
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 79ms 二进制优化的01背包
//复杂度O(∑log(num[i])*v)=10*log(1000)*10^5=10^7
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        int tw;
        for(int i=1;i<=n;i++){
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tw=w[i]*k;
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tw);
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//TLE 朴素01背包
//复杂度O(∑num[i]*v)=10*1000*10^5=10^9
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int k=1;k<=num[i];k++){
                for(int j=v;j>=w[i];j--)
                    dp[j]=max(dp[j],dp[j-w[i]]+w[i]);
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/
