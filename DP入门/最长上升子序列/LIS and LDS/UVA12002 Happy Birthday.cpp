/*
题意:摘自网上
给你一个序列，a[i]表示第i个盘子的大小。一共有n盘子。
你现在要从1走到n，拿走某些盘子，规则如下：
1、手中没有盘子，则可以拿起一个盘子。也可以不拿。
2、手中有一些盘子（必须保证上面的盘子的大小<=下面盘子的大小），
如果现在你面前这个盘子大小<=你手中最小的盘子的大小，就可以放到你
手中的盘子的最上面，如果>=你手中最大的盘子的大小，你就可以放到最下面。可以不拿。
求从1走到n最多能拿走多少盘子。
n<=500.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3153
思路:和UVA11456 Trainsorting一样只不过这个问题放在最上面或最下面的盘子可以相等.
如果仿照UVA11456 Trainsorting那种做法 会wa,因为统计的LIS和LDS会有重复相等的,重复的次数并不是只是a[i]一个,会wa.
因此需要枚举a[i]和a[j]保证其不等的情况,
如果
if(a[i]>a[j])//dp2[i]都是不比a[i]小的序列,dp1[j]是都不比a[j]大的序列
    ans=max(ans,dp2[i]+dp1[j]);
if(a[i]<a[j])//dp1[i]都是不比a[i]大的序列,dp2[j]是都不比a[j]小的序列
    ans=max(ans,dp1[i]+dp2[j]);
*/
//ac 150ms
#include<cstdio>
#include<algorithm>
#define N 5100
using namespace std;

//dp1[i]表示从n开始,以a[i]结尾的元素的最长不下降子序列的长度
//dp2[i]表示从n开始,以a[i]结尾的元素的最长不上升子序列的长度
int n,a[N],dp1[N],dp2[N],ans;

int main(){
    while(scanf("%d",&n) && n){
        ans=1;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=n;i>=1;i--){
            dp1[i]=dp2[i]=1;
            for(int j=n;j>i;j--){
                if(a[j]<=a[i])
                    dp1[i]=max(dp1[i],dp1[j]+1);
                if(a[j]>=a[i])
                    dp2[i]=max(dp2[i],dp2[j]+1);
            }
        }
        for(int i=n;i>=1;i--){//枚举a[i]和a[j]不相等,这样才能保证LIS和LDS没有重复值,组成单调的子序列记录最大长度
            //有可能a[i]和剩下的a[i-1..1]都相等,所以ans初始值为max(dp1[i],dp2[i])
        	ans=max(ans,max(dp1[i],dp2[i]));
        	for(int j=i-1;j>=1;j--){
                //这里不能有等于,因为dp2[i] dp1[j]本身就包括等于,这样会使结果偏大
        		if(a[i]>a[j])//dp2[i]都是不比a[i]小的序列,dp1[j]是都不比a[j]大的序列
        			ans=max(ans,dp2[i]+dp1[j]);
        		if(a[i]<a[j])//dp1[i]都是不比a[i]大的序列,dp2[j]是都不比a[j]小的序列
        			ans=max(ans,dp1[i]+dp2[j]);
			}
		}
        printf("%d\n",ans);
    }
    return 0;
}

/*
//wa 仿照UVA11456 Trainsorting那种做法 会wa,因为统计的LIS和LDS会有重复相等的,重复的次数并不是只是a[i]一个
#include<cstdio>
#include<algorithm>
#define N 5100
using namespace std;

//dp1[i]表示从n开始,以a[i]结尾的元素的最长不下降子序列的长度
//dp2[i]表示从n开始,以a[i]结尾的元素的最长不上升子序列的长度
int n,a[N],dp1[N],dp2[N],ans;

int main(){
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=n;i>=1;i--){
            dp1[i]=dp2[i]=1;
            for(int j=n;j>i;j--){
                if(a[j]<=a[i])
                    dp1[i]=max(dp1[i],dp1[j]+1);
                if(a[j]>=a[i])
                    dp2[i]=max(dp2[i],dp2[j]+1);
            }
            //这里会wa,假如n~i下标数值都是一样的,那么dp1[i]和dp2[i]实际表示的子序列是相同的,会重复多加了dp1[i]或dp2[i],多加了一半
            ans=max(ans,dp1[i]+dp2[i]-1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

