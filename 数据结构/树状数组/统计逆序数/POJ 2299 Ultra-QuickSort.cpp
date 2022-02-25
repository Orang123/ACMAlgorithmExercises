/*
����:ժ������
��������Ϊn�����У�ÿ��ֻ�ܽ������ڵ�����Ԫ�أ�
������Ҫ�������β�ʹ�ø�����Ϊ�������С�
n<=500000.0<=��ֵ��Χ<=999999999.
����:http://poj.org/problem?id=2299
˼·:���Դ�����һ������:
1���������е������� = ��ֻ������������Ԫ�ؽ�����������,�õ��������еĽ�������.
��״�����鲢�������������
*/
//ac 391ms ��״���� ���˳���1��n
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
    a[0].val=-1;//������ɢ��a[i] a[i-1]�жϳ���
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
//ac 422ms �鲢������������
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
//ac 422ms ��״���� ���˳���n��1
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
    a[0].val=-1;//������ɢ��ʱ Ԫ��ֵ0 �ж����
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
            update(reflect[i]);//����getsumǰ����
            ans+=getsum(reflect[i]-1);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/
