#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 50100
using namespace std;
//ac 16ms 01背包 平摊物品成2堆 差值尽可能小
/*
题意:主人公与其女票一起洗衣服,两个人可以一起洗(不能2人洗同一件衣服,
只能一人单独洗一件),但是衣服有很多种颜色,为了不让衣服色混,所以俩人必须
要同时洗一种颜色的衣服,如果有一个人还没有洗完,另一个人就只能等待,
直到俩人都洗完,才能洗下一个颜色的衣服,计算最小的耗时.
每件衣服有对应的洗的时间和颜色,时间对2个人来说都是一样的.
链接:http://poj.org/problem?id=3211
思路:因为洗衣顺序是按照颜色顺序来的,也就是洗不同的颜色衣服实际是2个独立
事件,那么对于一种颜色的衣服,一个人先洗完也需要另一个人洗完他的最后一件衣服,
才能开始洗下一个颜色的衣服,要想总的洗的时间最短,只要2人对应洗衣服时间相差最小
即可,而实际理想情况是2人洗完自己所有衣服用的时间相同,也就是同时完成.那么问题转化为
要将同一颜色衣服分给2人,使得2人衣服洗完的总时差最小,很明显可以转化为01背包问题,
背包容量为所以衣服洗完时长的一半,那么最终的dp[sum/2]就是先洗完的那个人需要的时间,
sum-dp[sum/2]是后洗完的人用的时间,如果dp[sum/2]==sum-dp[sum/2],则两人同时洗完,用时
最少.即对所有颜色分别做一次平分总洗衣时长的01背包.累计最小用时即可.

注意:此题洗衣总时长sum/2,不区分其奇偶,因为只是找到一个相差最小的平衡点值作为背包容量尽可能地
装满背包,除非题目要求是否能等分.
*/
int n,m,dp[M],sum[12];
char color[12][15];

struct Clothes{
    int t;
    char c[15];
}clo[N];

int main(){
    while(scanf("%d%d",&m,&n) && n+m){
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=m;i++)
            scanf("%s",color[i]);
        for(int i=1;i<=n;i++){
            scanf("%d%s",&clo[i].t,clo[i].c);
            for(int j=1;j<=m;j++){
                if(!strcmp(clo[i].c,color[j])){
                    sum[j]+=clo[i].t;//计算 j颜色的衣服洗完的所有时长
                    break;
                }
            }
        }
        int ans=0;
        for(int k=1;k<=m;k++){
            memset(dp,0,sizeof(dp));
            //此题洗衣总时长sum/2,不区分其奇偶,因为只是找到一个相差最小的平衡点值
            int v=sum[k]/2;//背包容量为 该颜色衣服洗完时长的一半
            for(int i=1;i<=n;i++){
                if(!strcmp(color[k],clo[i].c)){//只对颜色k做01背包
                    for(int j=v;j>=clo[i].t;j--)
                        dp[j]=max(dp[j],dp[j-clo[i].t]+clo[i].t);
                }
            }
            //sum[k]-dp[v]为另一个人洗衣较长用时者,因为只有两个人都洗完才能开始下一个颜色的衣服
            ans+=sum[k]-dp[v];
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
n<100,暴力肯定TLE.
*/
