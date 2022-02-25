#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 110
using namespace std;
//ac 54ms 排序+01背包
/*
题意:暑期将至,忙碌的DB小公主想要找一些零零碎碎的工作来补贴家用.
已知DB小公主一共有m天的假期,每天的编号从1到m,一共有n份可以做的工作,
每份工作都知道起始时间s,终止时间e和对应的工资c,每份工作的起始和终止
时间以天为单位(即天数编号),每份工作必须从起始时间做到终止时间才能得
到总工资c,且不能存在时间重叠的工作.比如,第1天起始第2天结束的工作不能
和第2天起始,第4天结束的工作一起被选定,因为第2天DB小公主只能在一个地
方工作.现在,DB小公主想知道怎么安排才能在假期的m天内获得最大的工资数
(第m+1天DB小公主必须返回学校，m天以后起始或终止的工作是不能完成的).
链接:http://acm.nefu.edu.cn/problemShow.php?problem_id=1028
思路:因为给出的工作时间是以[开始时间,结束时间]=[s,e]的形式,并且多个工作
之间并不连续,如工作1 [1,3],工作2不能从3开始,只能从4开始.状态转移方程可表示
为:dp[j]=max(dp[j],dp[j]-(dp[work[i].e]-dp[work[i].s-1])+work[i].val),但是
工作集需要按照结束时间升序排序,结束时间相同按开始时间升序排,这样可以避免
若2个工作[5,10] [5,8] 时间重叠,价值也累加,显然同一时间只能做一份工作,与
题意不符.
*/
int n,m,dp[M];
struct Work{
    int s,e,val;
    bool operator <(const Work &x)const{
        if(e == x.e) return s<x.s;//工作结束点相同,按照工作开始时间升序排
        else return e<x.e;//否则按工作结束时间升序排
    }
}work[N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&work[i].s,&work[i].e,&work[i].val);
        sort(work+1,work+1+n);
        for(int i=1;i<=n;i++){
            for(int j=m;j>=work[i].e;j--)
                //(dp[work[i].e]-dp[work[i].s-1])表示第i份工作的时间段在前i-1个工作中所获得的价值,这里要减去这部分时间重叠的区域
                //work[i].s-1是因为2个工作之间边界不能有时间交集
                dp[j]=max(dp[j],dp[j]-(dp[work[i].e]-dp[work[i].s-1])+work[i].val);
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
