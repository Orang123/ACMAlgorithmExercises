/*
题意:摘自网上
有两个长度分别为p+1和q+1的序列，每个元素中的各个元素互不相同。
都是1~n^2之间的整数，求A和B的最长公共子序列。
n<=250,p,q<=n*n=62500.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1576
思路:显然如果直接求LCS,复杂度=p*q=62500*62500=3.9*10^9.
实际因为每个数组中的元素都不相同,可以对a数组中的串进行映射,
mp[a[i]]=i,再根据a数组的映射去转换b数组,b[i]=mp[b[i]].
这样原先的LCS问题实际就转换成了,b数组中的LIS问题,
对于mp[b[i]]=0,即:a数组中不存在的数,不映射.
*/
//ac 10ms b数组中a没有的数不映射
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 63000
#define INF 0x3f3f3f3f
using namespace std;

int n,p,q,a[N],b[N],mp[N],dp[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(mp,0,sizeof(mp));
        scanf("%d%d%d",&n,&p,&q);
        for(int i=1;i<=p+1;i++){
            scanf("%d",&a[i]);
            mp[a[i]]=i;
        }
        n=0;
        for(int i=1;i<=q+1;i++){
            scanf("%d",&b[i]);
            if(mp[b[i]])//a数组也中存在的数才映射
            	a[++n]=mp[b[i]];
        }
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++)
            *lower_bound(dp,dp+q+1,a[i])=a[i];
        printf("Case %d: %d\n",cas,lower_bound(dp,dp+n,INF)-dp);
    }
    return 0;
}
