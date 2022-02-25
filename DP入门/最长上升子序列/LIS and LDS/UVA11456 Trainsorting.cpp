/*
题意:摘自网上
给出n，表示有n节车厢，然后第i节车厢重量为t[i]，位于第i个车站，
列车长从有强迫症，一定要求说列车的车箱要按照质量从大到小排序，
所以他按照序号一次经过每一个车站，可以考虑是否添加位于该车站的车厢，
添加的话也只能放在已有车列的前端和后端，不能说从中间插入，问说列车最多能有多长。
n<=2000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2451
思路:思路摘自:https://www.iteye.com/blog/haierboos-1939734
假设第一个车厢选择第i个放进去，那么接下来，放在i的右边的一定是比i的重量小的，
为了让右边方向尽量长，就要在序列中第i个到最后一个选最长递减序列的顺序放。要放在i的左边的，
一定是比i的重量要大的，同理，为了让左边方向尽量长，应该找以i为第一个(不能让其他代替)的最长递增
序列。
所以需要逆序计算出LCS和LDS.那么答案就是LIS(i)+LDS(i)-1,减1是因为第i个车厢重复加了一次.
*/
//ac 10ms
#include<cstdio>
#include<algorithm>
#define N 2100
using namespace std;

//dp1[i]表示从n开始,以a[i]结尾的元素的LIS的长度
//dp2[i]表示从n开始,以a[i]结尾的元素的LDS的长度
int n,a[N],dp1[N],dp2[N],ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=1;
        scanf("%d",&n);
        if(!n){
            printf("0\n");
            continue;
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=n;i>=1;i--){
            dp1[i]=dp2[i]=1;
            for(int j=n;j>i;j--){
                if(a[j]<a[i])
                    dp1[i]=max(dp1[i],dp1[j]+1);
                if(a[j]>a[i])
                    dp2[i]=max(dp2[i],dp2[j]+1);
            }
            ans=max(ans,dp1[i]+dp2[i]-1);
        }
        printf("%d\n",ans);
    }
    return 0;
}

