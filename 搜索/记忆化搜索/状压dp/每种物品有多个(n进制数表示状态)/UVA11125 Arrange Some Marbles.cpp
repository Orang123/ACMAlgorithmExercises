/*
题意:摘自网上
给你n(n<=4)种不同颜色的弹珠，然后给出每种颜色的弹珠的个数，
现在要求你将这些弹珠排序，要求相同颜色的部分最多3个。
然后相同颜色的弹珠称为一个组，那么每个相邻的组要求长度不同，
颜色也不同，然后首位的两组颜色和长度也不能相同。每个颜色的
弹珠数量在[0,7].
n<=4.
有3000组样例.
链接:https://www.luogu.com.cn/problem/UVA11125
思路:记忆化搜索.
可以枚举每一组的颜色和数量,但是对于前面的分组段,颜色和数量
都相同只是排放顺序不同的情况,实际对于后面的段的分组枚举所做
的搜索是相同,这是重叠子问题.所以对于状态的表示应该包含上一组
的颜色的数量,以及第一组的颜色和数量,以及剩下颜色的弹珠,因为
每个颜色的弹珠最多有7个,关于剩下的弹珠可以用8进制表示,注意计算8
进制时要固定8进制位数长度为4,否则按照n作为位数长度,对于不同的样例,
状态的表示就会出错,实际是重叠子问题的状态 缺没有正确表示 无法正确判断.
dp[sc][sn][curc][curn][sta]表示第一组颜色为sc,数量为sn,上一组颜色为curc,
数量为curn,剩下弹珠的8进制状态为sta时,剩下弹珠排放方案的数目.
注意初始弹珠数目都为0时,实际排放方案是1,不是0.

不用3进制、5进制小于8的进制原因是,剩下弹珠数目 情况不同时有可能对应10进制
数值也是相等的,这样状态数值并不是唯一表示的,不能有效标识已经搜索过的状态.
*/
//ac 20ms 记忆化搜索
//dp[sc][sn][curc][curn][sta]表示第一组颜色为sc,数量为sn,上一组颜色为curc,
//数量为curn,剩下弹珠的8进制状态为sta时,剩下弹珠排放方案的数目.
//num[i]表示颜色为i的弹珠剩下的数目
//复杂度O(4*8*4*8*4095)=4193280
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define M 8
#define INF 0x3f3f3f3f
using namespace std;

int n,num[N],dp[N][M][N][M][4096],sc,sn,ans;

int dfs(int curc,int curn){
    int sta=0;
    for(int i=1;i<=4;i++)//这里无论n的取值如何,都按照4位8进制来计算,这样才能保持状态数值的一致性
        sta=sta*8+num[i];
    int &res=dp[sc][sn][curc][curn][sta];
    if(res!=-1)
        return res;
    if(!sta){//剩下弹珠数目为0,说明curc,curn是最后一组
        if(curc!=sc && curn!=sn)//最后一组和初始组 颜色、数目不同 是合法方案,返回1
            return 1;
        else
            return 0;
    }
    res=0;
    for(int i=1;i<=n;i++){
        if(i == curc)//和上一组颜色不同
            continue;
        for(int j=1;j<=3 && j<=num[i];j++){
            if(j == curn)//和上一组数目不同
                continue;
            num[i]-=j;
            res+=dfs(i,j);
            num[i]+=j;
        }
    }
    return res;
}

int main(){
    int T,sum;
    memset(dp,-1,sizeof(dp));//dp只会初始化一次,因为不同的样例之间 也会存在重叠子问题,每个样例都初始化一次 会TLE
    scanf("%d",&T);
    while(T--){
        sum=ans=0;
        memset(num,0,sizeof(num));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&num[i]);
            sum+=num[i];
        }
        if(!sum){//初始弹珠数目为0时,方案数为1
            printf("1\n");
            continue;
        }
        for(int i=1;i<=n;i++){
            sc=i;
            for(int j=1;j<=3 && j<=num[i];j++){
                sn=j;
                num[i]-=j;
                ans+=dfs(i,j);
                num[i]+=j;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
