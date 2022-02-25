/*
题意:Matrix67要在下个月交给老师n篇论文,论文的内容可以从m个课题中选择.
由于课题数有限,Matrix67不得不重复选择一些课题.完成不同课题的论文所花的时间不同.
具体地说,对于某个课题i,若 Matrix67计划一共写x篇论文,则完成该课题的论文总共需要
花费 a[i]*x^b[i] 个时间单位给定与每一个课题相对应的a[i]和b[i]的值,请帮助Matrix67
计算出如何选择论文的课题使得他可以花费最少的时间完成这n篇论文.
链接:https://www.luogu.com.cn/problem/P1336
思路:对于每个课题可以选择完成1篇论文、2篇论文、...、n篇论文,只能选取其中一个方案,
可以按照课题分组,每组物品是课题完成论文的数量1~n.
*/
//ac 37ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 21
#define M 210
typedef long long ll;
using namespace std;

int n,m,a[N],b[N];
ll dp[M];

ll cal(int x,int b){
    ll tp=1;
    for(int i=1;i<=b;i++)
        tp*=x;
    return tp;
}

int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&a[i],&b[i]);
    dp[0]=0;
    for(int i=1;i<=m;i++){
        for(int j=n;j>=1;j--){
            for(int k=1;k<=j;k++)
                dp[j]=min(dp[j],dp[j-k]+a[i]*cal(k,b[i]));
        }
    }
    printf("%lld",dp[n]);
    return 0;
}
