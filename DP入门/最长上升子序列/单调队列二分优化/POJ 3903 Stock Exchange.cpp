/*
题意:世界金融危机是一个相当大的话题。有些人比较放松，
而另一些人则相当焦虑。约翰就是其中之一。他非常关注证券交易所的演变。
他每天跟踪股价，寻找上涨趋势。给定代表股票价格的数字序列 p1, p2,...,pn，
上升趋势是子序列 pi1 < pi2 < ... < pik，其中 i1 < i2 < ... < ik。John
的问题是快速找到最长的上升趋势。
n<=10^5.
链接:http://poj.org/problem?id=3903
思路:n<=10^5.O(n^2)的做法会TLE,需要用单调队列二分优化,
O(nlogn).
*/
//ac 63ms 单调队列二分优化
#include<cstdio>
#define N 100010
using namespace std;

int n,m,dp[N],len;

void erfen(int val){
    int l=1,r=len,mid;
    while(l<r){
        mid=(l+r)/2;
        if(val>dp[mid])//val<dp[mid] r=mid 会wa
            l=mid+1;
        else
            r=mid;
    }
    dp[l]=val;
}

int main(){
    while(scanf("%d",&n)!=EOF){
        len=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&m);
            if(m>dp[len])
                dp[++len]=m;
            else
                erfen(m);
        }
        printf("%d\n",len);
    }
    return 0;
}

/*
//ac 63ms
//lower_bound
#include<cstdio>
#include<algorithm>
#define N 100010
using namespace std;

int n,a[N],b[N],len;

int main(){
    int pos;
    while(scanf("%d",&n)!=EOF){
        len=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
            if(a[i]>b[len])
                b[++len]=a[i];
            else{
            	pos=lower_bound(b+1,b+1+len,a[i])-b;
            	b[pos]=a[i];
			}
        }
        printf("%d\n",len);
    }
    return 0;
}
*/

/*
//ac 79ms
//lower_bound b数组下标从0开始,为了方便统计末尾合法位置b数组初始化为INF
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dp[N];

int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
        	scanf("%d",&m);
        	*lower_bound(dp,dp+n,m)=m;
		}
        printf("%d\n",lower_bound(dp,dp+n,INF)-dp);
    }
    return 0;
}
*/
