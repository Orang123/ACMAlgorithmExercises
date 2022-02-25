/*
����:�������Ϊn���������ж��ٸ��ϸ�������������.
����Ԫ����ֵ������32λ�з�������.
n<=10^5.
����:http://lightoj.com/volume_showproblem.php?problem=1085
˼·:c[x]��ʾ��xΪ��βԪ�ص������еĸ���,������״����.
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
            //��Ϊ��״����c[x]��ʾС�ڵ���x�������еĸ���,�����ڲ�������������,���Զ�����ֵһ���� ��ɢ�����ֵҲҪ����һ��
            if(a[i].val == a[i-1].val)
                reflect[a[i].pos]=reflect[a[i-1].pos];
            else
                reflect[a[i].pos]=i;
        }
        ll num;
        for(int i=1;i<=n;i++){
            //���ϸ�С����ôreflect[i]Ҫ�ϸ����֮ǰ��������ĩβԪ��,�����reflect[i]-1��Ϊ���ұ�׼,
            //+1���������� ��reflect[i]��Ϊ��ʼԪ�ص�������
            num=getsum(reflect[i]-1)+1;
            ans=(ans+num)%Mod;
            update(reflect[i],num);//���� �µ����Ƚڵ� �����ӵ������и���Ϊnum
        }
        printf("Case %d: %lld\n",cas,ans);
    }
    return 0;
}
