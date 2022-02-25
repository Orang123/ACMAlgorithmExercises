#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 1100
#define INF -0x3f3f3f3f
using namespace std;
//ac 31ms 二维01背包 求解给定背包容积下装入m个物品能获得的最大价值
//优化,装入背包物品个数降序从当前物品i开始枚举,即前i个物品,最多装入i个
/*
题意:从N部电影中选M部看,每部都有不同的时长和价值,问是否
可以看完M部电影,可以的话求价值的最大值,否则输出0.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3496
思路:在01背包模型基础上,再加一个维度,装入背包物品个数,
初始状态,对于背包容量来说是尽可能多装满,对于背包放入物品个数来说是恰好装满,
初始化dp[0][i]=0,对于装入背包物品个数j需要降序序循环遍历原因和01背包剩余容积
降序是一样的,都是保证dp[j-w[i]]是上一状态的值,而不是当前第i个物品加入后改变后的,
即第i个物品不会重复累加.
*/
//dp[j][k] 代表容量为k的背包恰好装入j个物品最多能获得的价值,容量k不一定恰好装满,而是尽可能多地装
int n,m,l,w[N],val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,INF,sizeof(dp));//尽可能多地装入背包
        scanf("%d%d%d",&n,&m,&l);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&w[i],&val[i]);
        //对于背包容量来说是尽可能多装满,对于背包放入物品个数来说是恰好装满,
        //因为只有装入背包物品个数为0被初始化为0,其余对应的容量是任意的
        for(int i=0;i<=l;i++)//初始状态 背包容量为0,放入背包物品个数为0时
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            //枚举前i个物品中应选择几个物品放入背包,前i个物品,
            //最多放入i个,这是优化,网上很多代码这里j初始上界是m
            //同样需要降序,这样才能保证dp[j-1][k-w[i]]中的j-1是在上一个状态前i-1个状态时的值,
            //不会重复将同一物品累加多次,如果升序dp[j-1][k-w[i]]中的j-1,可能已经变成了当前状态前i个物品的值,val[i]重复放入背包了
            //逆序的原理和01背包剩余容量逆序的原因相同
            //装入j个物品的上移状态是装入j-1个物品 符合二维费用背包的特性
            for(int j=i;j>=1;j--){
                for(int k=l;k>=w[i];k--)
                    dp[j][k]=max(dp[j][k],dp[j-1][k-w[i]]+val[i]);
            }
        }
        if(dp[m][l]>0)//能恰好装满m个物品,是合法转态,输出结果
            printf("%d\n",dp[m][l]);
        else
            printf("0\n");
    }
    return 0;
}

/*
//ac 31ms 未优化,装入背包物品个数降序从m开始枚举
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 1100
#define INF -0x3f3f3f3f
using namespace std;
int n,m,l,w[N],val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,INF,sizeof(dp));//尽可能多地装入背包
        scanf("%d%d%d",&n,&m,&l);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&w[i],&val[i]);
        for(int i=0;i<=l;i++)
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            for(int j=m;j>=1;j--){
                for(int k=l;k>=w[i];k--)
                    dp[j][k]=max(dp[j][k],dp[j-1][k-w[i]]+val[i]);
            }
        }
        if(dp[m][l]>0)
            printf("%d\n",dp[m][l]);
        else
            printf("0\n");
    }
    return 0;
}
*/

/*
//ac 46ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 1100
#define INF -0x3f3f3f3f
using namespace std;
int n,m,l,w[N],val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,INF,sizeof(dp));//尽可能多地装入背包
        scanf("%d%d%d",&n,&m,&l);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&w[i],&val[i]);
        for(int i=0;i<=l;i++)
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            for(int k=l;k>=w[i];k--)
                for(int j=1;j<=i;j++)
                    dp[j][k]=max(dp[j][k],dp[j-1][k-w[i]]+val[i]);
        }
        if(dp[m][l]>0)
            printf("%d\n",dp[m][l]);
        else
            printf("0\n");
    }
    return 0;
}
*/
