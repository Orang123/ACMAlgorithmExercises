/*
����:����n������,����������Ƕ��ٸ���������Ӽ�.
[Si, Ei]an [Sj, Ej].If Si <= Sj and Ej <= Ei and Ei - Si > Ej - Sj
Ei - Si > Ej - Sj˵�����������Ӽ�,��������ȼ���.
����:http://poj.org/problem?id=2481
˼·:��״����,�����Ҷ˵�Ӵ�С��,��˵��С������,
����˵㹹����״����,����������ȵ����,ֱ�Ӽ̳���һ�������ֵ,
��Ϊ��ȵ����䲻�����Ӽ�.
*/
//ac 2282ms �����Ҷ˵�Ӵ�С��,��˵��С������
//cnt[a[i].id]=getsum(a[i].s+1);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

int n,c[N],cnt[N],maxn;
struct Ele{
    int s,e,id;
    bool operator <(const Ele &x)const{
        if(e!=x.e)
            return e>x.e;
        else
            return s<x.s;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int d){
    while(x<=maxn){
        c[x]+=d;
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
    while(scanf("%d",&n) && n){
        memset(c,0,sizeof(c));
        maxn=-1;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i].s,&a[i].e);
            a[i].id=i;
            maxn=max(maxn,a[i].s);
        }
        maxn++;
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++){
            if(a[i].s == a[i-1].s && a[i].e == a[i-1].e)
                cnt[a[i].id]=cnt[a[i-1].id];
            else
                cnt[a[i].id]=getsum(a[i].s+1);//��˵㲻����0,��˼�1 ��ѯ������a[i].s+1 ����Ϊ֮ǰ������˵���ͬ,�Ҷ˵���ڵ�ǰ���������Ҳ�������Ӽ�
            update(a[i].s+1,1);
        }
        printf("%d",cnt[1]);
        for(int i=2;i<=n;i++)//����ո�дif�жϻ�TLE,��������þ�,��һ��Ԫ�����,��������" %d"����
            printf(" %d",cnt[i]);
        printf("\n");
    }
    return 0;
}

/*
//ac 2313ms ������˵��С������,�Ҷ˵�Ӵ�С��
//cnt[a[i].id]=i-1-getsum(a[i].e);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

int n,c[N],cnt[N],maxn;
struct Ele{
    int s,e,id;
    bool operator <(const Ele &x)const{
        if(s!=x.s)
            return s<x.s;
        else
            return e>x.e;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int d){
    while(x<=maxn){
        c[x]+=d;
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
    while(scanf("%d",&n) && n){
        memset(c,0,sizeof(c));
        maxn=-1;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i].s,&a[i].e);
            a[i].id=i;
            maxn=max(maxn,a[i].e);
        }
        maxn++;
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++){
            if(a[i].s == a[i-1].s && a[i].e == a[i-1].e)
                cnt[a[i].id]=cnt[a[i-1].id];
            else//a[i].e�Ҷ˵ĵ㶼�ǵ�i����������Ӽ�,��˼���
                cnt[a[i].id]=i-1-getsum(a[i].e);//�����ѯʱ ʵ������Ϊa[i].e+1,��ֹ��a[i].e,��Ϊa[i].e+1�п���Ҳ�����Ӽ�,��Ϊ֮ǰ��������˵�ȵ�i������ҪС
            update(a[i].e+1,1);//�Ҷ˵�����״�����в���Ϊ0,ʵ�ʹ���ʱ��1
        }
        printf("%d",cnt[1]);
        for(int i=2;i<=n;i++)//����ո�дif�жϻ�TLE,��������þ�,��һ��Ԫ�����,��������" %d"����
            printf(" %d",cnt[i]);
        printf("\n");
    }
    return 0;
}
*/
