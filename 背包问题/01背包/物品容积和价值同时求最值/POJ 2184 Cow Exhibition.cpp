#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 200001
#define INF -0x3f3f3f3f
using namespace std;
//ac 391ms 01背包容量为负数 平移容量区间为正数,恰好装满背包
//背包容量为s[i]之和,物品价值为f[i]
/*
题意:给你n头奶牛,每头奶牛有个聪明值s[i]和一个有趣值f[i].问你从其中
取出若干头奶牛,使得这些奶牛的s[i]+f[i]最大的同时s[i]的总和>=0,fi的
总和也>=0,输出最大值.
1<=n<=100,-1000<=s[i],f[i]<=1000
链接:http://poj.org/problem?id=2184
思路:因为要得到聪明度和有趣值之和的最大值,可以将聪明度s[i]之和作为
背包容积,有趣值f[i]作为物品价值,s[i]作为物品容积.因为聪明度s[i]可能
为负数,即:-1000<=s[i]<=1000,100个s[i]之和的上下限为[-100000,100000],
但背包容积不能为负数,因为数组下标不能为负,所以在这个上下限基础上再加
100000,变为[100000,200000],原先的初始状态0变为100000,因此新的初始状态
为dp[100000]=0,对其求解01背包,则s[i]和f[i]之和的最大值为i+dp[i]-100000.
这里注意对s[i]为负数时,dp背包容积j应该升序枚举因为j-s[i]>j,如果按照常规
降序枚举,后面的dp[j-s[i]]会重复累加,上一个状态会被重复计算,真正的上一个状态
已经被提前改变了.因为i+dp[i]为s[i]之和加f[i]之和,i和dp[i]都代表着实际的有意义
的取值,所以问题应该是恰好装满,而不能尽可能多地装.
*/
int n,s[N],f[N],dp[M];

int main(){
    memset(dp,INF,sizeof(dp));//初始化负无穷
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&s[i],&f[i]);
    dp[100000]=0;//初始状态从0移位到100000
    for(int i=1;i<=n;i++){
        if(s[i]>=0){//s[i]为正数,背包容量降序
            for(int j=2e5;j>=s[i];j--)
                if(dp[j-s[i]]!=INF)//恰好装满,判断上一状态是否合法
                    dp[j]=max(dp[j],dp[j-s[i]]+f[i]);
        }
        else{//s[i]为负数,背包容量升序,因为降序会导致上一个状态d[i-1][j]更新后 再度被作为上一个状态,但实际它已经不是原始的上一个状态
            //而背包容量s[i]之和最少从0开始,所以下界0;
            //背包容量最大为2e5,所以上界为j-s[i]<=2e5.
            for(int j=0;j-s[i]<=2e5;j++)//j的下界不能为负,所以下界为0,但j-s[i]最大为2e5,所以j的上界是s[i]+2e5
                if(dp[j-s[i]]!=INF)//j-s[i]>j,上一个状态的j-s[i],即s[i]之和较大,因为s[i]本身就是负的,现在只是将<0的部分平移到了原点右侧
                    dp[j]=max(dp[j],dp[j-s[i]]+f[i]);
        }
    }
    int ans=0;
    //s[i]之和必须大于0,所以从偏移后的原点100000开始遍历,
    for(int i=1e5;i<=2e5;i++){//因为s[i]之和大,f[i]之和也有可能小,所以要遍历所有结果取最大值
        if(dp[i]>0)//dp[i]代表f[i]之和要为正数
            ans=max(ans,i-100000+dp[i]);//因为s[i]之和实际是向右便宜了100000,所以实际值要减去100000
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 422ms 背包容积为f[i]之和,物品价值为s[i]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 200001
#define INF -0x3f3f3f3f
using namespace std;

int n,s[N],f[N],dp[M];

int main(){
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&s[i],&f[i]);
    dp[100000]=0;
    for(int i=1;i<=n;i++){
        if(f[i]>=0){
            for(int j=2e5;j>=f[i];j--)
                if(dp[j-f[i]]!=INF)
                    dp[j]=max(dp[j],dp[j-f[i]]+s[i]);
        }
        else{
            for(int j=0;j-f[i]<=2e5;j++)
                if(dp[j-f[i]]!=INF)
                    dp[j]=max(dp[j],dp[j-f[i]]+s[i]);
        }
    }
    int ans=0;
    for(int i=1e5;i<=2e5;i++){
        if(dp[i]>0)
            ans=max(ans,i+dp[i]-100000);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//MLE 模拟天平平衡 二维数组做法 此题对空间有要求N*M=2*10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 200100
#define INF -0x3f3f3f3f
using namespace std;

int n,s[N],f[N],dp[N][M],sum;

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&s[i],&f[i]);
        sum+=abs(f[i]);//有可能f[i]之和为负,所以这里全部按正值取极限最大值
    }
    sum<<=1;
    dp[0][sum/2]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++)
            dp[i][j]=dp[i-1][j];
        for(int j=0;j<=sum;j++){//这里有问题 j+f[i]可能为负数
            if(dp[i-1][j]>INF){//因此s[i]有可能为负所以只要 比负无穷大 即为合法状态
                dp[i][j+f[i]]=max(dp[i][j+f[i]],dp[i-1][j]+s[i]);
            }
        }
    }
    int ans=0;
    for(int i=sum/2;i<=sum;i++){
        if(dp[i]>0)
            ans=max(ans,i-sum/2+dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
暴力枚举搜索 n<=100,TLE
*/
