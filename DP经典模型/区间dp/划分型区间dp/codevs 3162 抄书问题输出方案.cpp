#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//这个做法的输出好像还是有点问题
/*
题意:现在要把M本有顺序的书分给K个人复制（抄写），每一个人的抄写速度都一样，
一本书不允许给两个（或以上）的人抄写，分给每一个人的书，必须是连续的，比如不能把第一、第三、第四本数给同一个人抄写。
现在请你设计一种方案，使得复制时间最短。复制时间为抄写页数最多的人用去的时间。
如果有多解，则尽可能让前面的人少抄写。
链接:https://blog.csdn.net/qq_34374664/article/details/68953181
思路:dp[i][j]代表前i本书交给j个人去抄写 一个人抄写的最多的页数
*/

int dp[110][110],m,k,a[110],sum[110],pos[110];

int main(){
    scanf("%d%d",&m,&k);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)
        sum[i]=sum[i-1]+a[i];
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=m;i++)
        dp[i][1]=sum[i];
    for(int t=2;t<=k;t++){
        for(int i=t;i<=m;i++){
            for(int j=t-1;j<i;j++)
                //一个人抄写最多的页数为总抄写时间,区间分割方案要使得这个抄写最多的时间最小
                dp[i][t]=min(dp[i][t],max(dp[j][t-1],sum[i]-sum[j]));//sum[i]-sum[j]为第t个人抄写的页数 和前面的t-1个人抄写的最多页数比较
        }
    }
    pos[1]=0;
    pos[k+1]=m;//最后一个人最后抄写得到页数为m
    int tmp=0,p=k;
    for(int i=m;i>=1;i--){
        if(a[i]+tmp<=dp[m][k])//因为一个人抄的书必须是连续的,所以只要不大于一个人抄写的最多的页数,这本书就是这个人抄的,后面的人尽可能多抄
            tmp+=a[i];
        else{//当这本书超出一个人抄的最多页数时,说明是第t-1个人抄的
            tmp=a[i];
            pos[p--]=i;//将第p-1个人的最后一个抄写的书编号记录
        }
    }
    for(int i=2;i<=k+1;i++)
        printf("%d %d\n",pos[i-1]+1,pos[i]);
    return 0;
}

/*
区间dp 正确的输出方案做法
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int INF =0x3f3f3f3f;
const int maxn=100    ;


int dp[maxn+5][maxn+5],a[maxn+5];
int n,m;
int sum[maxn+5];
int ans;

void print(int num ,int v)
{

    int best;

    if(num==1)   {printf("%d %d\n",1,v);return;}
    for(int k=num-1;k<v;k++)
    {

        int ret=max(dp[num-1][k],sum[v]-sum[k]);
        if(ret<=ans  )
        {
            best=k;
            break;
        }
    }


   print(num-1,best);
    printf("%d %d\n",best+1,v);


}
int main()
{
    while(~scanf("%d%d",&m,&n))
    {
        if(m==0)
        {
            continue;
        }
        sum[0]=0;
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&a[i]);
            sum[i]=sum[i-1]+a[i];
            dp[1][i]=sum[i];
        }


        for(int i=2;i<=n;i++)//i个人
        {
            for(int j=i;j<=m-(n-i);j++)//j本书
            {
                dp[i][j]=INF;
                for(int k=i-1;k<j;k++  )
                {
                    int ret=max(dp[i-1][k], sum[j]-sum[k] );
                    if(  ret<dp[i][j]   )
                    {
                        dp[i][j]=ret;
                    }
                }

            }
        }
        ans=dp[n][m];
        print(n,m);


    }


   return 0;
}
*/


/*
二分最大值最小化抄书页数做法
inline bool check(int limit) {
    memset(pageCount, 0, sizeof(pageCount));

    int j = k - 1, lastEnd = m - 1;
    for (int i = m - 1; i >= 0; i--) {
        if (pageCount[j] + a[i] <= limit) {
            pageCount[j] += a[i];
        } else {
            if (j == 0) {//说明最大的抄书页数太小了
                return false;
            }

            lastEnd = i;
            pageCount[--j] += a[i];
        }
    }

    return sum(0, lastEnd - 1) <= limit;//不能不够k个人 抄书页数太大了
}

inline int binaryDivide() {
    int l = max, r = sum(0, m - 1);
    while (l < r) {
        int mid = l + ((r - l) >> 1);
        if (check(mid)) r = mid;//说明最大抄书页数太大了,都不能分够k个人 调小右边界
        else l = mid + 1;//说明最大的抄书页数太小了 调大左边界
    }

    return l;
}
*/
