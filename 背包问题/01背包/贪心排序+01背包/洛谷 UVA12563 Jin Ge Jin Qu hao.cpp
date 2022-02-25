#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 10000
using namespace std;
//ac 0ms 贪心+01背包 恰好装满背包
//dp[j]代表在j时间唱了dp[j]首歌,唱了j时间时长.
/*
题意:有t秒钟,n+1首歌可供选择,其中《金歌金曲》长达678s是时长最长的歌,
其它歌时长不会超过3分钟,而KTV就算t秒钟到达,也不会终止你正在唱的最
后一首歌.现在要求要尽可能唱尽可能多数目的歌,并且唱歌时间尽可能地久,
输出最多唱歌数目和唱歌时间.输入n+1受歌的时长总和保证大于t.
n<=50
链接:https://www.luogu.com.cn/problem/UVA12563
思路:显然最后唱的歌一定得是《金歌金曲》才能使唱歌时长最长,那么可以将问题转化为
在t-1秒内唱尽可能多数量尽可能长时长的歌,最后1s用来听《金歌金曲》,这是一个恰好装
满背包的01背包问题.dp[j]代表在j时间最多唱了dp[j]首歌,恰好唱了j时间时长.
属于多目标条件的01背包问题.
*/
int cas,n,v,w[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++)
            scanf("%d",&w[i]);
        dp[0]=0;//只有dp[0]是合法状态
        for(int i=1;i<=n;i++){
            for(int j=v-1;j>=w[i];j--){//最后1秒用来听《金歌金曲》,t-1秒听其它歌
                if(dp[j-w[i]]>=0)
                    //在ts内选择听尽可能多数量的歌
                    dp[j]=max(dp[j],dp[j-w[i]]+1);
            }
        }
        int ans=0;
        for(int i=v-1;i>=1;i--){
            //首先要保证听歌数目最大,再在听歌数目基础上听歌时长最长,因此是严格大于不能大于等于
            if(dp[i]>0 && dp[i]>dp[ans])
                ans=i;
        }
        printf("Case %d: %d %d\n",cas,dp[ans]+1,ans+678);
    }
    return 0;
}

/*
//ac 0ms 01背包
//设定num[j]表示时长j内,听歌的最多数目
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 10000
using namespace std;
//num[j]表示时长j内,听歌的最多数目
int cas,n,v,w[N],dp[M],num[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(num,0,sizeof(num));
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++)
            scanf("%d",&w[i]);
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=v-1;j>=w[i];j--){
                if(dp[j-w[i]]>=0){
                    if(num[j-w[i]]+1>num[j])//听歌数目要最大
                        num[j]=num[j-w[i]]+1;
                    dp[j]=dp[j-w[i]]+w[i];
                }
            }
        }
        int ans=0;
        for(int i=v-1;i>=1;i--){
            if(dp[i]>0 && num[i]>num[ans])
                ans=i;
        }
        printf("Case %d: %d %d\n",cas,num[ans]+1,ans+678);
    }
    return 0;
}
*/
