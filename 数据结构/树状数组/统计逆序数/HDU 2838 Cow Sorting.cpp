/*
����:ժ������
����n�����в����������1~n���������ǰ�����С�����źã�
ÿ�ν����ܽ�������������������һ�εĴ���Ϊ����֮�͡�����С���ۡ�
n<=100000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2838
˼·:���Դ�����һ������:
1���������е������� = ��ֻ������������Ԫ�ؽ�����������,�õ��������еĽ�������.
��״�������������,����������״����,һ����С�ڵ���a[i]�ĸ���,
һ����С�ڵ���a[i]����ֵ֮��.
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
//ac 46ms ���˳���n��1 �ж�n~i+1�Ƿ���С��a[i]�� ʵ����������������ӵ��д�����ȵ���� �����,
//��Ϊc[x]��ʾ����С�ڵ���,������ֻ���ϸ�С��.
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
