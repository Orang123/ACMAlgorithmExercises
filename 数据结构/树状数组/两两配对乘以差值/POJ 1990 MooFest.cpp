/*
����:ժ������
FJ��nͷţ�����г�һ��ֱ��(������ͬһ����)������ÿͷţ��ֱ���ϵ�����x��
���⣬ÿͷţ����һ���Լ�������v�������ͷţ(i��j)֮����Ҫ��ͨ�Ļ���
���Ǳ�����ͬ������max(v[i],v[j])����ͨ�������ĵ�����Ϊ��
max(v[i],v[j]) * ����֮��ľ��롣��Ҫʹ���е�ţ֮�䶼�ܹ�ͨ(����֮��)��
�ܹ���Ҫ���Ķ���������
n,v[i],x<=20000.
����:http://poj.org/problem?id=1990
˼·:����2����״����,һ���洢С������x���������,
һ���洢С������x������֮��,��ţ����h��С��������,
�����ܱ�֤�������ʱ,ȡ���ǵ�ǰ��iͷţ��v.
��Ϊ���������,���ǵ�iͷţʱֻ����ǰi-1ͷţ��С�ڵ�
iͷţ����ʹ��ڵ�iͷţ����,��Ϊ��ֵ�Ǿ���ֵ,Ҫд�ɴ�x�ļ�ȥС��x.
������ȵĲ�ֵ�������0,�����ر���.
*/
//ac 110ms ��С��������ͱ��Ϊ1~i-1ͷţ�Ա�,�Ȳ�ѯ�����.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20010
typedef long long ll;
using namespace std;

int n,maxn;
ll c[N],b[N];//c��ʾС�ڵ���x�ĸ���,b��ʾС�ڵ���x������֮��

struct Ele{
    int v,x;
    bool operator <(const Ele &p)const{
        return v<p.v;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(ll *c,int x,int d){
    while(x<=maxn){
        c[x]+=d;
        x+=lowbit(x);
    }
}

ll getsum(ll *c,int x){
    ll sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll total=0,sumc,sumb;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].v,&a[i].x);
        maxn=max(maxn,a[i].x);
    }
    sort(a+1,a+1+n);
    ll ans=0,res1,res2;
    for(int i=1;i<=n;i++){
        sumc=getsum(c,a[i].x);//С�ڵ���a[i].x�ĸ��� ����д��a[i].x-1 ֻͳ��С��a[i].xҲû�д�,���ڵ���������ֵ����0
        sumb=getsum(b,a[i].x);//С�ڵ���a[i].x������֮��
        res1=a[i].v*(sumc*a[i].x-sumb);//(a[i].x-a[1..i-1].x)*a[i].v
        //total-sumb��ʾ1~i-1�д���a[i].x������֮��,
        //(i-1-sumc)��ʾ1~i-1�д���a[i].x�ĸ���
        //��������ʽa[1..i-1].x-a[i].x
        res2=a[i].v*(total-sumb-(i-1-sumc)*a[i].x);
        ans+=res1+res2;
        total+=a[i].x;
        update(c,a[i].x,1);//����iͷţ������״����
        update(b,a[i].x,a[i].x);
    }
    printf("%lld",ans);
    return 0;
}

/*
//ac 63ms �Ӵ�С����ͱ��Ϊi+1~n ͷţ�Ա� �ȹ�����״����,ÿ�Ա�һ�� �ͽ���iͷţ����״������ɾ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20010
typedef long long ll;
using namespace std;

int n,maxn;
ll c[N],b[N];

struct Ele{
    int v,x;
    bool operator <(const Ele &p)const{
        return v>p.v;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(ll *c,int x,int d){
    while(x<=maxn){
        c[x]+=d;
        x+=lowbit(x);
    }
}

ll getsum(ll *c,int x){
    ll sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll sumc,sumb;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].v,&a[i].x);
        maxn=max(maxn,a[i].x);
    }
    for(int i=1;i<=n;i++){
    	update(c,a[i].x,1);
        update(b,a[i].x,a[i].x);
	}
    sort(a+1,a+1+n);
    ll ans=0,res1,res2;
    for(int i=1;i<=n;i++){
        sumc=getsum(c,a[i].x);//i+1~n��С�ڵ���a[i].x�ĸ���
        sumb=getsum(b,a[i].x);//i+1~n��С�ڵ���a[i].x������֮��
        res1=a[i].v*(sumc*a[i].x-sumb);
        //getsum(b,maxn)-getsum(b,a[i].x) i+1~n�д���a[i].x������֮��  maxn������x����,��״�������������Ƚڵ���
        //getsum(c,maxn)-getsum(c,a[i].x) i+1~n�д���a[i].x�ĸ���
        res2=a[i].v*(getsum(b,maxn)-getsum(b,a[i].x)-(getsum(c,maxn)-getsum(c,a[i].x))*a[i].x);
        ans+=res1+res2;
        update(c,a[i].x,-1);//��iͷţ�Ѿ�������������ţ�Աȹ���,���ٶԱ�,���ɾ��
        update(b,a[i].x,-a[i].x);
    }
    printf("%lld",ans);
    return 0;
}
*/
