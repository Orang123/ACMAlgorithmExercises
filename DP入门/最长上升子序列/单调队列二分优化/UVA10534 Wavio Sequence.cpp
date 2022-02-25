/*
题意:摘自网上
给出一个字符串，找出一个奇数的子序列，子序列的前半部分要递增，
后半部分要递减，且递增和递减的长度要相等，要求输出最长满足条件的子序列的长度。
子序列长度<=10010.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1475
思路:正反序求出LIS,枚举出a[i]为中心点,则实际对称半径为min(dp1[i],dp2[i]),
最大值为ans=max(ans,min(dp1[i],dp2[i])*2-1);
*/
//ac 50ms stl lower_bound
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;

//dp1[i]表示从1开始,以a[i]结尾的元素的LIS的长度
//dp2[i]表示从n开始,以a[i]结尾的元素的LIS的长度
int n,x[N],a[N],dp1[N],dp2[N],len,ans;

int main(){
    int pos;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        len=0;
        for(int i=1;i<=n;i++){
            if(x[i]>a[len]){
                a[++len]=x[i];
                dp1[i]=len;
            }
            else{
                pos=lower_bound(a+1,a+1+len,x[i])-a;
                a[pos]=x[i];
                dp1[i]=pos;
            }
        }
        len=0;
        for(int i=n;i>=1;i--){
            if(x[i]>a[len]){
                a[++len]=x[i];
                dp2[i]=len;
            }
            else{
                pos=lower_bound(a+1,a+1+len,x[i])-a;
                a[pos]=x[i];
                dp2[i]=pos;
            }
        }
        ans=1;
        for(int i=1;i<=n;i++)
            ans=max(ans,min(dp1[i],dp2[i])*2-1);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 40ms 手写二分
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;

//dp1[i]表示从1开始,以a[i]结尾的元素的LIS的长度
//dp2[i]表示从1开始,以a[i]结尾的元素的LDS的长度
int n,x[N],a[N],dp1[N],dp2[N],len,ans;

int erfen(int val){
	int l=1,r=len,mid;
	while(l<=r){
		mid=(l+r)/2;
		if(val == a[mid])
			return mid;
		if(val<a[mid])
			r=mid-1;
		else
			l=mid+1;
	}
	return l;
}

int main(){
    int pos;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        len=0;
        for(int i=1;i<=n;i++){
            if(x[i]>a[len]){
                a[++len]=x[i];
                dp1[i]=len;
            }
            else{
                pos=erfen(x[i]);
                a[pos]=x[i];
                dp1[i]=pos;
            }
        }
        len=0;
        for(int i=n;i>=1;i--){
            if(x[i]>a[len]){
                a[++len]=x[i];
                dp2[i]=len;
            }
            else{
                pos=erfen(x[i]);
                a[pos]=x[i];
                dp2[i]=pos;
            }
        }
        ans=1;
        for(int i=1;i<=n;i++)
            ans=max(ans,min(dp1[i],dp2[i])*2-1);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//TLE O(n^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;

//dp1[i]表示从1开始,以a[i]结尾的元素的LIS的长度
//dp2[i]表示从1开始,以a[i]结尾的元素的LDS的长度
int n,x[N],dp1[N],dp2[N],ans;

int main(){
    int pos;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        for(int i=1;i<=n;i++){
        	dp1[i]=1;
        	for(int j=1;j<i;j++){
        		if(x[i]>x[j])
        			dp1[i]=max(dp1[i],dp1[j]+1);
			}
        }
        for(int i=n;i>=1;i--){
        	dp2[i]=1;
        	for(int j=n;j>i;j--){
        		if(x[i]>x[j])
        			dp2[i]=max(dp2[i],dp2[j]+1);
			}
        }
        ans=1;
        for(int i=1;i<=n;i++)
            ans=max(ans,min(dp1[i],dp2[i])*2-1);
        printf("%d\n",ans);
    }
    return 0;
}
*/
