/*
����:����n����������,���������ڽ���k��,�󽻻�����С�������.
n<=10^5,0<=a[i],k<=10^9.
����:https://acm.hdu.edu.cn/showproblem.php?pid=4911
˼·:��״�������������,����������ans����k�����,ʵ��ʣ�µ�
��������Ϊans-k,���ans<=k,��ans=kʱ,ǡ�ý���k��,��������Ϊ0��,
��ans<kʱ,��û������k��,��������Ϊ0��,2�����������������Ϊ0.
*/
//ac 124ms ��״����
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
    a[0].val=-1;//ԭʼ��ֵ ��0,������ɢ������,a[0].val����Ϊ-1
    while(scanf("%d%d",&n,&k)!=EOF){
        ans=0;
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].val);
            a[i].pos=i;
        }
        sort(a+1,a+1+n);//C++ stl�е�sort�����ȶ�����,�����ɢ��������ͬ����ֵ �Ծ�Ҫ�������ȵ�
        for(int i=1;i<=n;i++){
            //������ɢ��Ҫ�� ��ȵ�ֵ ��ɢ���ֵҲ���,���������,
            //ԭ����������ǰ����ȵ�ֵ,�������ں���,��ɢ���ֵ�ʹ�,
            //������״�������ʱ,��ɢ����ڵ�ֵ,��������ֵ����� ������������Ͳ���������ͻ����
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
