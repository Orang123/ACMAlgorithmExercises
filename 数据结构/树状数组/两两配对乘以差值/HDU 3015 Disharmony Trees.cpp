/*
����:ժ������
����n��������������λ�ú͸߶ȣ�Ȼ��ֱ������λ�ú͸߶������´���
λ�ã���λ������������С�Ķ���ȼ�Ϊ 1����С�Ķ���ȼ�Ϊ2�����ǣ�
Ҫ��λ����ͬ�ģ���ȼ�����Ҫ��ͬ��
���� λ�� 1��2��1��5��2��3
     �ȼ�  1��3��1��6��3��5
���ڸ߶�Ҳ�������ϴ���
Ȼ�󣬶���f=����֮��ľ����ľ���ֵ��s=��������С�ĸ߶ȣ���������֮��f*s�͡�
n<=100000,x,h<=10^9
����:https://acm.hdu.edu.cn/showproblem.php?pid=3015
˼·:��POJ 1990һ��,ֻ����Ҫ�Ȱ�����͸߶ȵĵȼ������
*/
//ac 124ms �Ӵ�С����ͱ��Ϊ1~i-1�����Ա�,�Ȳ�ѯ�����.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
typedef long long ll;
using namespace std;

int n;
ll c[N],b[N];//c��ʾС�ڵ���x�ĸ���,b��ʾС�ڵ���x������֮��

struct Ele{
    int x,h;
}a[N];

bool cmp1(Ele u,Ele v){
    return u.x<v.x;
}

bool cmp2(Ele u,Ele v){
    return u.h<v.h;
}

bool cmp3(Ele u,Ele v){
    return u.h>v.h;
}

int lowbit(int x){
    return x & -x;
}

void update(ll *c,int x,int d){
    while(x<=n){
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
    ll total,sumc,sumb;
    while(scanf("%d",&n)!=EOF){
        total=0;
        memset(c,0,sizeof(c));
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i].x,&a[i].h);
        sort(a+1,a+1+n,cmp1);
        int tp=a[1].x;
        a[1].x=1;
        for(int i=2;i<=n;i++){
            if(a[i].x != tp){
                tp=a[i].x;
                a[i].x=i;
            }
            else
                a[i].x=a[i-1].x;
        }
        sort(a+1,a+1+n,cmp2);
        tp=a[1].h;
        a[1].h=1;
        for(int i=2;i<=n;i++){
            if(a[i].h != tp){
                tp=a[i].h;
                a[i].h=i;
            }
            else
                a[i].h=a[i-1].h;
        }
        sort(a+1,a+1+n,cmp3);
        ll ans=0,res1,res2;
        for(int i=1;i<=n;i++){
            sumc=getsum(c,a[i].x);//С�ڵ���a[i].x�ĸ���
            sumb=getsum(b,a[i].x);//С�ڵ���a[i].x������֮��
            res1=a[i].h*(sumc*a[i].x-sumb);//(a[i].x-a[1..i-1].x)*a[i].h
            //total-sumb��ʾ1~i-1�д���a[i].x������֮��,
            //(i-1-sumc)��ʾ1~i-1�д���a[i].x�ĸ���
            //��������ʽa[1..i-1].x-a[i].x
            res2=a[i].h*(total-sumb-(i-1-sumc)*a[i].x);
            ans+=res1+res2;
            total+=a[i].x;
            update(c,a[i].x,1);//����i����������״����
            update(b,a[i].x,a[i].x);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 140ms ��С�������� �ȼ�����ѯ ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
typedef long long ll;
using namespace std;

int n;
ll c[N],b[N];//c��ʾС�ڵ���x�ĸ���,b��ʾС�ڵ���x������֮��

struct Ele{
    int x,h;
}a[N];

bool cmp1(Ele u,Ele v){
    return u.x<v.x;
}

bool cmp2(Ele u,Ele v){
    return u.h<v.h;
}

int lowbit(int x){
    return x & -x;
}

void update(ll *c,int x,int d){
    while(x<=n){
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
    ll total,sumc,sumb;
    while(scanf("%d",&n)!=EOF){
        total=0;
        memset(c,0,sizeof(c));
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i].x,&a[i].h);
        sort(a+1,a+1+n,cmp1);
        int tp=a[1].x;
        a[1].x=1;
        for(int i=2;i<=n;i++){
            if(a[i].x != tp){
                tp=a[i].x;
                a[i].x=i;
            }
            else
                a[i].x=a[i-1].x;
        }
        sort(a+1,a+1+n,cmp2);
        tp=a[1].h;
        a[1].h=1;
        for(int i=2;i<=n;i++){
            if(a[i].h != tp){
                tp=a[i].h;
                a[i].h=i;
            }
            else
                a[i].h=a[i-1].h;
        }
        for(int i=1;i<=n;i++){
    		update(c,a[i].x,1);
        	update(b,a[i].x,a[i].x);
		}
        sort(a+1,a+1+n,cmp2);
        ll ans=0,res1,res2;
    	for(int i=1;i<=n;i++){
        	sumc=getsum(c,a[i].x);//i+1~n��С�ڵ���a[i].x�ĸ���
        	sumb=getsum(b,a[i].x);//i+1~n��С�ڵ���a[i].x������֮��
        	res1=a[i].h*(sumc*a[i].x-sumb);
        	//getsum(b,maxn)-getsum(b,a[i].x) i+1~n�д���a[i].x������֮��  n������x����ĵȼ�,��״�������������Ƚڵ���
        	//getsum(c,maxn)-getsum(c,a[i].x) i+1~n�д���a[i].x�ĸ���
        	res2=a[i].h*(getsum(b,n)-getsum(b,a[i].x)-(getsum(c,n)-getsum(c,a[i].x))*a[i].x);
        	ans+=res1+res2;
        	update(c,a[i].x,-1);//��i�����Ѿ��������������Աȹ���,���ٶԱ�,���ɾ��
        	update(b,a[i].x,-a[i].x);
    	}
        printf("%lld\n",ans);
    }
    return 0;
}
*/
