/*
题意:摘自网上
给你n个排列不规则的数（1~n），任务是把它从小到大排好，
每次仅仅能交换相邻两个数，交换一次的代价为两数之和。求最小代价。
n<=100000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2838
思路:线性代数中一个定理:
1个乱序序列的逆序数 = 在只允许相邻两个元素交换的条件下,得到有序序列的交换次数.
树状数组求解逆序数,构建两个树状数组,一个存小于等于a[i]的个数,
一个存小于等于a[i]的数值之和.
*/
//ac 46ms
#include<cstdio>
#include<cstring>
#define N 100010
typedef long long ll;

ll n,a[N],maxn;
ll c[N],b[N];

ll lowbit(ll x){
    return x & -x;
}

void update(ll *c,ll x,ll d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}

ll getsum(ll *c,ll x){
    ll sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll ans,sum,total,num;
    while(scanf("%lld",&n)!=EOF){
        ans=total=0;
        memset(c,0,sizeof(c));
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            if(maxn<a[i])
                maxn=a[i];
        }
        for(int i=1;i<=n;i++){
            update(c,a[i],1);
            update(b,a[i],a[i]);
            total+=a[i];
            num=i-getsum(c,a[i]);
            sum=total-getsum(b,a[i]);
            ans+=num*a[i]+sum;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 46ms 添加顺序从n到1 判断n~i+1是否有小于a[i]的 实际这个做法如果已添加的有代价相等的情况 会出错,
//因为c[x]表示的是小于等于,而逆序只是严格小于.
#include<cstdio>
#include<cstring>
#define N 100010
typedef long long ll;

ll n,a[N],maxn;
ll c[N],b[N];

ll lowbit(ll x){
    return x & -x;
}

void update(ll *c,ll x,ll d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}

ll getsum(ll *c,ll x){
    ll sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll ans,sum,num;
    while(scanf("%lld",&n)!=EOF){
        ans=0;
        memset(c,0,sizeof(c));
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            if(maxn<a[i])
                maxn=a[i];
        }
        for(int i=n;i>=1;i--){
            num=getsum(c,a[i]);
            sum=getsum(b,a[i]);
            ans+=num*a[i]+sum;
            update(c,a[i],1);
            update(b,a[i],a[i]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/
