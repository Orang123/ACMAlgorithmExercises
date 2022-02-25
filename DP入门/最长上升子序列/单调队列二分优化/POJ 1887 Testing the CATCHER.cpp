/*
题意:求解最长下降子序列.
n<=5000.
链接:http://poj.org/problem?id=1887
思路:此题O(n^2)和O(nlogn)做法都可.
按道理O(n^2)会TLE的.只是注意stl的lower_bound
函数对于二分查询降序 要设置参数或数组逆序.
*/
//ac 0ms 单调队列二分优化
#include<cstdio>
#define N 5000

int m,dp[N],len;

void erfen(int val){
    int l=1,r=len,mid;
    while(l<r){
        mid=(l+r)/2;
        if(val<dp[mid])//注意dp数组是降序,因此和升序时,l,r的操作刚好相反.
            l=mid+1;
        else
            r=mid;
    }
    dp[l]=val;
}

int main(){
    int cas=0;
    while(scanf("%d",&m) && m!=-1){
        cas++;
        len=0;
        dp[++len]=m;
        while(scanf("%d",&m) && m!=-1){
            if(m<=dp[len])
                dp[++len]=m;
            else
                erfen(m);
        }
        printf("Test #%d:\n",cas);
        printf("  maximum possible interceptions: %d\n\n",len);
    }
    return 0;
}

/*
//ac 0ms
//lower_bound dp数组降序
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5000
using namespace std;

int n,a[N],dp[N];

int main(){
    int cas=0;
    while(scanf("%d",&a[++n]) && a[n]!=-1){
        cas++;
        memset(dp,0,sizeof(dp));
        while(scanf("%d",&a[++n]) && a[n]!=-1);
        n--;
        for(int i=1;i<=n;i++)//lower_bound 模式是对升序容器查找,若是降序 需要设置greater<int>()参数
        	*lower_bound(dp,dp+n,a[i],greater<int>())=a[i];
        printf("Test #%d:\n",cas);
        //因为dp数组是单调下降的,所以dp数组要初始化为0,求解单调队列长度要拿0做比较
        printf("  maximum possible interceptions: %d\n\n",lower_bound(dp,dp+n,0,greater<int>())-dp);
        n=0;
    }
    return 0;
}
*/

/*
//ac 0ms
//lower_bound dp数组reverse设置为升序
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5000
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[N];

int main(){
    int cas=0;
    while(scanf("%d",&a[++n]) && a[n]!=-1){
        cas++;
        memset(dp,0x3f,sizeof(dp));
        while(scanf("%d",&a[++n]) && a[n]!=-1);
        n--;
        reverse(a+1,a+1+n);
        for(int i=1;i<=n;i++)
        	*lower_bound(dp,dp+n,a[i])=a[i];
        printf("Test #%d:\n",cas);
        //因为dp数组是单调上升的,所以dp数组要初始化为INF,求解单调队列长度要拿INF做比较
        printf("  maximum possible interceptions: %d\n\n",lower_bound(dp,dp+n,INF)-dp);
        n=0;
    }
    return 0;
}
*/

/*
//ac 47ms O(n^2)做法
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5000
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[N],ans;

int main(){
    int cas=0;
    while(scanf("%d",&a[++n]) && a[n]!=-1){
        cas++;
        while(scanf("%d",&a[++n]) && a[n]!=-1);
        n--;
        ans=1;
        for(int i=1;i<=n;i++){
        	dp[i]=1;
        	for(int j=1;j<i;j++){
        		if(a[j]>a[i])
        			dp[i]=max(dp[i],dp[j]+1);
			}
			ans=max(ans,dp[i]);
		}
        printf("Test #%d:\n",cas);
        printf("  maximum possible interceptions: %d\n\n",ans);
        n=0;
    }
    return 0;
}
*/
