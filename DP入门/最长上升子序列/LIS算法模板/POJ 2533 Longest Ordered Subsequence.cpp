/*
LIS(Longest Increasing Subsequence)最长上升子序列,最长不下降子序列.
题意:N个数，求一个严格单调上升子序列的最大长度
链接:http://poj.org/problem?id=2533
思路:可采用O(N^2)的dp做法和O(NlogN)的二分单调队列(LIS)两种做法,
其中LIS无法记录子序列路径。
二分优化可参考博客:https://www.cnblogs.com/itlqs/p/5743114.html
这里采用dp做法.
*/
//ac 15ms
//dp[i]表示以第i个数结尾的单调递增子序列的最大长度,而不是长度为i的这些元素里整体的上升子序列的最大长度
//严格来讲求解单调递增的最长子序列这更像递推,状态的转移是由之前的单调递增子序列转移到更长的单调子序列
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a[1100],dp[1100];

int main(){
    int n,ans=1;//这里一定要设置成1,否则当长度为1时,输出的是为更新的ans的初始值,答案至少为1
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    dp[1]=1;//初始值单个元素构成一个上升序列
    for(int i=2;i<=n;i++){
        /*
        这个元素有可能是最小的,但其本身也是长度为1的上升子序列,这里不能继承dp[i-1]的值,
        因为若a[i]本身是最小的,它继承了dp[i-1],下个元素a[i+1],大于当前的a[i]时,dp[i+1]=dp[i]+1,
        有可能a[i+1]只大于a[i],对于a[i]前面的元素都小于呢,实际a[i+1]只大于a[i],a[i+1]=2才对.
        */
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
        }
        ans=max(ans,dp[i]);//ans记录各个单调递增子序列的最大长度,dp[i+1]不一定大于dp[i]
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 16ms O(n^2) 最精简版
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],dp[1100];

int main(){
    int n,ans=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
        }
        ans=max(ans,dp[i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 16ms 递归记忆化搜索写法O(N^2)
//重叠子问题是,对于不同的a[i]和a[j](j<i)比较时,dp[j]会重复搜索到,因此需要保存起来避免重复搜索.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],dp[1100],ans=1;

int dfs(int i){
    if(dp[i])
		return dp[i];
	dp[i]=1;
    for(int j=1;j<i;j++){
        //这里一定要先dfs(j),因为a[i]可能是前i个数中最小的,
        //写成dp[i]=max(dp[i],dfs(j)+1),可能就进入不了这个if条件,导致wa
    	dfs(j);
        if(a[i]>a[j])
            dp[i]=max(dp[i],dp[j]+1);
    }
    ans=max(ans,dp[i]);
    return dp[i];
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
		dp[i]=0;
	}
    dfs(n);
    printf("%d",ans);
    return 0;
}
*/

/*
//TLE 暴力dfs,不记录重叠子问题.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],dp[1100],ans=1;

int dfs(int i){
	int res=1;
    for(int j=1;j<i;j++){
    	dfs(j);
        if(a[i]>a[j])
            res=max(res,dfs(j)+1);
    }
    ans=max(ans,res);
    return res;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
		dp[i]=0;
	}
    dfs(n);
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 0ms 单调队列二分优化
//最长严格单调上升的子序列
//维护一个单调的队列(LIS)
//新的元素，如果大于队尾元素，即插入队尾
//否则二分查找比它大的最小元素，替换掉
//最后队列长度即为LIS的解
//下面理解摘自博客:https://www.cnblogs.com/frankchenfu/p/7107019.html
//所以每遇到一个比栈顶元素大的数，就放进栈里，遇到比栈顶元素小的就二分查找前边的元素，
//找到一个“最应该被换掉的元素”，用新数去更新前边的元素。这个元素可能不是最优解的一部分，
//但是它可以使得后面还未加入的、比较小的数更有可能进入这个队列。通俗地来说，作为门槛，
//他本来要大于当前序列的最后一个数才能加进去；就是如果我太大了，我就乖乖呆在末尾；如果
//前面有一个数比我大，也就是我比你好，既然我在你后面也就是我们两者只能选其一，那我只好
//把你替换掉了。虽然我这临时临头换的不一定最合适，但是对于后面还有很多的人等着排进来的
//情况下，我给他们创造了更多机会，使得这个序列的最后一个数有可能变小，让更多的人进来。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

//b数组为单调上升队列
int a[1100],b[1100];

void erfen(int l,int r,int val){
    int mid;
    while(l<r){
        mid=(l+r)/2;
        if(val>b[mid]) l=mid+1;//这里如果是val>=b[mid] 1 2 3 2 3 2 这组数据会输出4,实际结果应是3
        else r=mid;
    }
    b[l]=val;
}

int main(){
    int n,k=2;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    b[1]=a[1];//第一个元素要先放进去
    for(int i=2;i<=n;i++){//复杂度 O(NlogN) 从第二个元素开始加入队列
        //当a[i]比单调递增队列里队末最大值还大时 入队
        if(a[i]>b[k-1]) b[k++]=a[i];//最长不下降子序列这里是a[i]>=b[k-1]
        //当a[i]最大值时,二分查找队列中第一个大于a[i]的数,用a[i]替换它,这样做不会影响最长上升子序列的k值大小
        //如:一开始队列2个元素 1 4 i=3时a[3]=2,此时最长上升子序列还是2,假如将2放入队末,
        //1 4 2 i=4时,a[4]=5时,{1 4 5}{1 2 5}2个单调上升子序列长度都是3,
        //所以一开始a[3]小于4时,直接将4的值替换为a[2]最终的队列为1 2 5,
        //长度为3,就是说这样的做法恰好能使得队列的长度就是最长上升子序列的长度.
        //https://www.cnblogs.com/itlqs/p/5743114.html 参考博客
        //准确的说，并不是接在谁后面。而是替换掉谁。因为它接在前面的谁后面都是没有意义的，
        //再接也超不过最长的len，所以是替换掉别人。那么替换掉谁呢？就是替换掉那个最该被它替换的那个。
        //也就是在d数组中第一个大于它的。第一个意味着前面的都小于等于它。假设第一个大于它的是b[j]，
        //说明b[1..j-1]都小于等于它，那么它完全可以接上b[j-1]然后生成一个长度为j的不下降子序列，
        //而且这个子序列比当前的d[j]这个子序列更有潜力（因为这个数比d[j]小）。
        //以就替换掉它就行了，也就是b[j]=a[i]。其实这个位置也是它唯一能够替换的位置
        //（前面的替了不满足b[k]最小值的定义，后面替换了不满足上升序列）.
        else
            erfen(1,k-1,a[i]);
    }
    printf("%d",k-1);
    return 0;
}
*/

/*
//ac 0ms 单调队列 使用lower_bound stl二分搜索
//最长严格单调上升的子序列
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],b[1100];

int main(){
    int n,k=2,pos;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    b[1]=a[1];
    for(int i=2;i<=n;i++){
        if(a[i]>b[k-1]) b[k++]=a[i];//最长不下降子序列这里是a[i]>=b[k-1]
        else{
        //lower_bound()二分函数的返回值为一个指向单调序列[first, last) 中第一个不小于(大于等于)val的元素的地址 对应严格上升子序列 严格大于
        //upper_bound()二分函数返回的是单调序列中第一个大于val的元素的地址 对应不下降子序列,可以大于等于,非严格的
            pos=lower_bound(b+1,b+k,a[i])-b;//第二个参数是b+1+k-1=b+k
            b[pos]=a[i];
        }
    }
    printf("%d",k-1);
    return 0;
}
*/

/*
//ac 16ms 单调队列 使用lower_bound stl二分搜索
//lower_bound b数组下标从0开始,为了方便统计末尾合法位置b数组初始化为INF
//最长严格单调上升的子序列
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int maxn=1005;
const int INF=0x3f3f3f3f;
int n,res,x,dp[maxn];
int main(){
    while(~scanf("%d",&n)){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;++i){
            scanf("%d",&x);
            *lower_bound(dp,dp+n,x)=x;//更新最小序列
        }
        printf("%d\n",lower_bound(dp,dp+n,INF)-dp);
    }
    return 0;
}
*/
