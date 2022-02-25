/*
题意:摘自网上
给定n个整数序列，求出绝对值小于等于k的有序对个数。
n<=100000,k<=10^9.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5178
思路:按照从小到达排序后,再尺取.
当x[r+1]-x[l]>k时 不再移动右指针,此时有r-l个点对满足情况
即:(l,l+1),(l,l+2)...,(l,r).
*/
//ac 202ms
#include<cstdio>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

int n,k,x[N];
ll ans;

int main(){
    int T,l,r;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        sort(x+1,x+1+n);
        ans=0;
        l=r=1;//初始位置从1开始
        while(l<n){//结束条件是l左指针移到n-1位置,因为(n,n)是同一个点
            while(r+1<=n && x[r+1]-x[l]<=k)
                r++;
            ans+=r-l;
            l++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
