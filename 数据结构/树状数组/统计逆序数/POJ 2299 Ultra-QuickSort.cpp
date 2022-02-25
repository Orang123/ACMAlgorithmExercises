/*
题意:摘自网上
给出长度为n的序列，每次只能交换相邻的两个元素，
问至少要交换几次才使得该序列为递增序列。
n<=500000.0<=数值范围<=999999999.
链接:http://poj.org/problem?id=2299
思路:线性代数中一个定理:
1个乱序序列的逆序数 = 在只允许相邻两个元素交换的条件下,得到有序序列的交换次数.
树状数组或归并排序求解逆序数
*/
//ac 391ms 树状数组 添加顺序从1到n
//ans+=i-getsum(reflect[i]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500010
typedef long long ll;
using namespace std;

int n,c[N],reflect[N];
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

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll ans;
    a[0].val=-1;//避免离散化a[i] a[i-1]判断出错
    while(scanf("%d",&n) && n){
        ans=0;
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].val);
            a[i].pos=i;
        }
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++){
            if(a[i].val == a[i-1].val)
                reflect[a[i].pos]=reflect[a[i-1].pos];
            else
                reflect[a[i].pos]=i;
        }
        for(int i=1;i<=n;i++){
            update(reflect[i]);
            ans+=i-getsum(reflect[i]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 422ms 归并排序求逆序数
#include<cstdio>
#define N 500010
typedef long long ll;

int n,a[N],tp[N];
ll ans;

void mergeArr(int low,int mid,int high){
    int i=low,j=mid+1,k=low;
    while(i<=mid && j<=high){
        if(a[i]<=a[j])
            tp[k++]=a[i++];
        else{
            tp[k++]=a[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid)
        tp[k++]=a[i++];
    while(j<=high)
        tp[k++]=a[j++];
    for(int i=low;i<=high;i++)
        a[i]=tp[i];
}

void mergeSort(int low,int high){
    if(low<high){
        int mid=(low+high)/2;
        mergeSort(low,mid);
        mergeSort(mid+1,high);
        mergeArr(low,mid,high);
    }
}

int main(){
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        mergeSort(1,n);
        printf("%lld\n",ans);
    }
    return 0;
}
*/

/*
//ac 422ms 树状数组 添加顺序从n到1
//ans+=getsum(reflect[i]-1);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500010
typedef long long ll;
using namespace std;

int n,c[N],reflect[N];
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

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll ans;
    a[0].val=-1;//避免离散化时 元素值0 判断相等
    while(scanf("%d",&n) && n){
        ans=0;
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].val);
            a[i].pos=i;
        }
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++){
            if(a[i].val == a[i-1].val)
                reflect[a[i].pos]=reflect[a[i-1].pos];
            else
                reflect[a[i].pos]=i;
		}
        for(int i=n;i>=1;i--){
            update(reflect[i]);//放在getsum前后都行
            ans+=getsum(reflect[i]-1);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/
