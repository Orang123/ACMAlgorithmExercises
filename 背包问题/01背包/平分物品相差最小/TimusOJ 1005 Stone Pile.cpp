#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
#define M 1000100
using namespace std;
//ac 15ms 01背包分成2堆尽可能相近,价值和差值最小
/*
题意:n块石头,每块石头有重量val[i],现在要求把n块石头
分成2堆,要求2堆石头重量之和的差值最小,输出这个最小差值.
链接:https://vjudge.net/problem/URAL-1005
https://acm.timus.ru/problem.aspx?space=1&num=1005
思路:将01背包容量看做所有石头重量之和的一半,求出背包
所能载重的最大重量,剩下的就是另一堆(较大堆),作差即可.
*/
int n,val[N],dp[M],sum;

int main(){
    memset(dp,0,sizeof(dp));//尽可能多地装入背包
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
        sum+=val[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=sum/2;j>=val[i];j--)
            dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
    }
    printf("%d",sum-2*dp[sum/2]);
    return 0;
}

/*
//ac 15ms 暴力枚举搜索
//因为n<=20,所以2^20=10^6 1s内还行,一般n超过30,2^n就比较爆炸了
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
#define M 1000100
using namespace std;

int n,val[N],dp[M],sum,ans;

void dfs(int k,int res){
    if(res>sum/2) return;
    if(res>ans)
        ans=res;
    if(k == n+1) return;
    dfs(k+1,res+val[k]);
    dfs(k+1,res);
}

int main(){
    memset(dp,0,sizeof(dp));//尽可能多地装入背包
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
        sum+=val[i];
    }
    dfs(1,0);
    printf("%d",sum-2*ans);
    return 0;
}
*/
