#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 35
using namespace std;
//ac 30ms 01背包 尽可能多地装满背包,做m次01背包
/*
题意:超市中有n种物品,每种物品数量不限,都有自己的重量和价值,
有m个人,每个人每种物品只能取一个,并且每个人都有自己最大能承受的重量,
要求这m个人在自己的承受重量范围内,取到的物品价值总和最大.
链接:https://www.luogu.com.cn/problem/UVA10130
思路:"每个人每种物品只能取一个",显然对于每个人能取的最大价值是一个01背包,
可以对每个人做一次01背包,累加最大价值和.
*/
int n,m,v,w[N],val[N],dp[M],ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&val[i],&w[i]);
        scanf("%d",&m);
        while(m--){//m个人 每个人做一次01背包
            scanf("%d",&v);
            memset(dp,0,sizeof(dp));
            for(int i=1;i<=n;i++){
                for(int j=v;j>=w[i];j--)
                    dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
            }
            ans+=dp[v];
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms 因为实际对于每个人来说所做的01背包物品个数价值体积都是相同的,这有背包容量不同
//可以按照每个人的承重上限30,只做一次01背包,之后对于每个人的承重上限v(背包容积)只累加dp[v]即可
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 35
using namespace std;

int n,m,v,w[N],val[N],dp[M],ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&val[i],&w[i]);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=30;j>=w[i];j--)
                dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        scanf("%d",&m);
        while(m--){//m个人 每个人做一次01背包
            scanf("%d",&v);
            ans+=dp[v];
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
