/*
题意:
给出了一个由N个正整数 (10<N<100000)组成的序列，
每个都小于或等于10000，并给出一个正整数S(S< 100000000)。
编写一个程序，求出序列中连续元素之和大于或等于S的子序列的最小长度。
链接:http://poj.org/problem?id=3061
思路:尺取.复杂度O(n).直接暴力枚举每个起点开始遍历时间复杂度O(n^2).
*/
//ac 79ms
//r表示右边加上了几个数,l表示的是左边减去了几个数
#include<cstdio>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,s,a[N],sum,ans;

int main(){
    int T,l,r;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sum=l=r=0;
        ans=INF;
        while(1){
            //每次这里r向右扩,都是sum<s的情况才开始累加右边的
            while(r<n && sum<s)//O(n)
                sum+=a[++r];
            if(sum<s)
                break;
            //r表示连续字段的右边界 l+1是连续子段的左边界 字段元素个数r-(l+1)+1=r-l
            //因此实际长度就为r-l
            ans=min(ans,r-l);
            //l不可能超过r,最多相等
            sum-=a[++l];//每次减去一个l,sum如果仍然>=s,继续减去a[++l]. 时间复杂度这里最多减n次 是个常数
        }
        if(ans!=INF)
            printf("%d\n",ans);
        else//ans == INF 说明所有的数之和都比s小,因此长度为0,没有满足条件的子串(连续子序列)
            printf("0\n");
    }
    return 0;
}

/*
//ac 79ms
//下标从0开始 后++
//左右指针各一个循环
//l,r左右指针均表示下标
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int a[100001];
int main(){
    int k,n,s,sum,l,r,num,len,total;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&n,&s);
        total=0;
        for(int i=0;i<n;i++){
            scanf("%d",a+i);
            total+=a[i];
        }
        if(total<s){
            printf("0\n");
            continue;
        }
        sum=0,l=0,r=0,num=INF,len=0;
        while(r<n){
            while(r<n&&sum<s){
                sum+=a[r++];
            }
            while(sum>=s){
                sum-=a[l++];
            }
            //因为r,l都多算了1,所以直接抵消了,实际长度就为r-l+1(+1是因为下标之差比实际长度少1)
            num=min(num,r-l+1);
        }
        printf("%d\n",num);
    }
    return 0;
}
*/

/*
//ac 79ms 双指针,if(sum<s) break;结束大循环
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int a[100001];
int main(){
    int k,n,s,sum,l,r,num,len,total;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&n,&s);
        total=0;
        for(int i=0;i<n;i++){
            scanf("%d",a+i);
            total+=a[i];
        }
        if(total<s){
            printf("0\n");
            continue;
        }
        sum=0,l=0,r=0,num=INF,len=0;
        while(1){
            while(r<n&&sum<s)
                sum+=a[r++];
            if(sum<s)
            	break;
            while(sum>=s)
                sum-=a[l++];
            //因为r,l都多算了1,所以直接抵消了,实际长度就为r-l+1(+1是因为下标之差比实际长度少1)
            num=min(num,r-l+1);
        }
        printf("%d\n",num);
    }
    return 0;
}
*/

/*
//ac 79ms
//下标从0开始 先++
//左右指针各一个循环
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int a[100001];
int main(){
    int k,n,s,sum,l,r,num,len,total;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&n,&s);
        total=0;
        for(int i=0;i<n;i++){
            scanf("%d",a+i);
            total+=a[i];
        }
        if(total<s){
            printf("0\n");
            continue;
        }
        sum=0,l=-1,r=-1,num=INF,len=0;
        while(r<n-1){
            while(r<n-1&&sum<s){
                sum+=a[++r];
            }
            while(sum>=s){
                sum-=a[++l];
            }
            num=min(num,r-l+1);
        }
        printf("%d\n",num);
    }
    return 0;
}
*/

/*
//ac 79ms
//下标从1开始 先++
//左右指针各一个循环
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int a[100001];
int main(){
    int k,n,s,sum,l,r,num,total;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&n,&s);
        total=0;
        for(int i=1;i<=n;i++){
            scanf("%d",a+i);
            total+=a[i];
        }
        if(total<s){
            printf("0\n");
            continue;
        }
        sum=0,l=0,r=0,num=INF;
        while(r<n){
            while(r<n&&sum<s)
                sum+=a[++r];
            while(sum>=s)
                sum-=a[++l];
            //l是减去了下标为l的数后 sum<s的,那么实际左边的下标就是l,因此长度r-l+1
            num=min(num,r-l+1);
        }
        printf("%d\n",num);
    }
    return 0;
}
*/

/*
//ac 860ms
//摘自博客:https://tigerisland.blog.csdn.net/article/details/73699161
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000;
int prefixsum[N+1];

int main()
{
    int t, n, s, val, ans;

    cin >> t;
    while(t--) {
        cin >> n >> s;

        // 输入数据，计算前缀和
        prefixsum[0] = 0;
        for(int i=1; i<=n; i++) {
            cin >> val;

            prefixsum[i] = prefixsum[i - 1] + val;
        }

        if(prefixsum[n] < s)
            ans = 0;
        else {
            ans = n;
            for(int i=0; prefixsum[i] + s < prefixsum[n]; i++) {
                int pos = lower_bound(prefixsum + i, prefixsum + n, prefixsum[i] + s) - prefixsum;
                ans = min(ans, pos - i);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
*/
