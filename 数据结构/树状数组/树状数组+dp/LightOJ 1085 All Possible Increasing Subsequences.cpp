/*
题意:求出长度为n的序列中有多少个严格上升的子序列.
序列元素数值不超过32位有符号整数.
n<=10^5.
链接:http://lightoj.com/volume_showproblem.php?problem=1085
思路:c[x]表示以x为结尾元素的子序列的个数,构建树状数组.
*/
//ac 269ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define Mod 1000000007
typedef long long ll;
using namespace std;

int n,reflect[N];
ll c[N],ans;
struct Ele{
    int val,pos;
    bool operator <(const Ele &x)const{
        return val<x.val;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,ll d){
    while(x<=n){
        c[x]=(c[x]+d)%Mod;
        x+=lowbit(x);
    }
}

ll getsum(int x){
    ll sum=0;
    while(x){
        sum=(sum+c[x])%Mod;
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        ans=0;
        memset(c,0,sizeof(c));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].val);
            a[i].pos=i;
        }
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++){
            //因为树状数组c[x]表示小于等于x的子序列的个数,而等于并不构成子序列,所以对于数值一样的 离散后的数值也要保持一致
            if(a[i].val == a[i-1].val)
                reflect[a[i].pos]=reflect[a[i-1].pos];
            else
                reflect[a[i].pos]=i;
        }
        ll num;
        for(int i=1;i<=n;i++){
            //是严格小于那么reflect[i]要严格大于之前的子序列末尾元素,因此用reflect[i]-1作为查找标准,
            //+1是新增加了 以reflect[i]作为起始元素的子序列
            num=getsum(reflect[i]-1)+1;
            ans=(ans+num)%Mod;
            update(reflect[i],num);//更新 新的祖先节点 所增加的子序列个数为num
        }
        printf("Case %d: %lld\n",cas,ans);
    }
    return 0;
}
