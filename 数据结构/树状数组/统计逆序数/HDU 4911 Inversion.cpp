/*
题意:给出n个数的序列,最多可以相邻交换k次,求交换后最小逆序对数.
n<=10^5,0<=a[i],k<=10^9.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4911
思路:树状数组求解逆序数,对于逆序数ans大于k的情况,实际剩下的
逆序数就为ans-k,如果ans<=k,当ans=k时,恰好交换k次,逆序数就为0了,
当ans<k时,还没交换完k次,逆序数就为0了,2种情况最终逆序数都为0.
*/
//ac 124ms 树状数组
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
typedef long long ll;
using namespace std;

int n,k,reflect[N];
ll c[N];
struct Ele{
    int val,pos;
    bool operator <(const Ele &x)const{
        return val<x.val;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x){
    while(x<=n){
        c[x]+=1;
        x+=lowbit(x);
    }
}

ll getsum(int x){
    ll sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll ans;
    a[0].val=-1;//原始数值 有0,避免离散化出错,a[0].val设置为-1
    while(scanf("%d%d",&n,&k)!=EOF){
        ans=0;
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].val);
            a[i].pos=i;
        }
        sort(a+1,a+1+n);//C++ stl中的sort并非稳定排序,因此离散化对于相同的数值 仍旧要处理成相等的
        for(int i=1;i<=n;i++){
            //这里离散化要将 相等的值 离散后的值也相等,如果不这样,
            //原先序列排在前面相等的值,排序后放在后面,离散后的值就大,
            //这样树状数组查找时,离散后大于的值,但本身数值是相等 并不构成逆序就不包括结果就会出错
            if(a[i].val == a[i-1].val)
                reflect[a[i].pos]=reflect[a[i-1].pos];
            else
                reflect[a[i].pos]=i;
        }
        for(int i=1;i<=n;i++){
            update(reflect[i]);
            ans+=i-getsum(reflect[i]);
        }
        printf("%lld\n",ans-k>0?ans-k:0);
    }
    return 0;
}
