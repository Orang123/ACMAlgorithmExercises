#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 50100
typedef long long ll;
using namespace std;

int a[N],pos[N],cnt[N],ans1[N],ans2[N],res;

struct seq{
    int ql,qr,id;
    bool operator < (const seq &x)const{
        if(pos[ql] != pos[x.ql]) return pos[ql]<pos[x.ql];
        if(pos[ql] & 1) return qr<x.qr;
        else return qr>x.qr;
    }
}q[N];

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

void add(int id){
    int x=a[id];
    /*
    ����������Ϊ �±�Ϊi�����Ӻ�֮ǰѡ�����ͬ��ɫ�����Ӵ����ܹ������ ��˫,
    �����������Ͼ���������ɫ�������ܹ�����Լ�˫,cnt[x]����Ľ������һ��cnt[x]++����һ�ε�.
    */
    res+=cnt[x];
    cnt[x]++;
}

void sub(int id){
    int x=a[id];
    cnt[x]--;
    //����ͬ�� �ð���һ�����һ��ѡ�����ͬ��ɫ������֮ǰ����ͬ����Ŀ��ȥ,��Ϊ���Ǻ�������һ��ѡ������Ӻ�֮ǰ���ɵ����Ӵ����ӵĶ���
    res-=cnt[x];
}

int main(){
    int n,m,siz;
    scanf("%d%d",&n,&m);
    siz=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        pos[i]=(i-1)/siz+1;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&q[i].ql,&q[i].qr);
        q[i].id=i;
    }
    sort(q+1,q+1+m);
    int l=1,r=0,gcd0;
    for(int i=1;i<=m;i++){
        if(q[i].ql == q[i].qr){//������Ҫ����,��Ϊ�����c[i][j] j>=i,���ֻ��һ����ʱ�޷�ѡ��2������,��ĸ��Ϊ0ʧȥ����
            ans1[q[i].id]=0;
            ans2[q[i].id]=1;
            continue;
        }
        while(l<q[i].ql) sub(l++);
        while(l>q[i].ql) add(--l);
        while(r<q[i].qr) add(++r);
        while(r>q[i].qr) sub(r--);
        ans1[q[i].id]=res;
        ans2[q[i].id]=(ll)(r-l+1)*(r-l)/2;//�����C[r-l+1][2] [l,r]���������е�������ȡ2˫�����п��ܽ���� (r-l+1)*(r-l)���ܻᳬ��int�ķ�Χһ��,���Ҫǿ��ת���������
    }
    for(int i=1;i<=m;i++){
        gcd0=gcd(ans1[i],ans2[i]);
        ans1[i]/=gcd0;
        ans2[i]/=gcd0;
        printf("%d/%d\n",ans1[i],ans2[i]);
    }
    return 0;
}
/*
��ͬ���� ������� c[i][2]
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 50100
typedef long long ll;
using namespace std;

int a[N],pos[N],cnt[N],ans1[N],ans2[N],res;

struct seq{
    int ql,qr,id;
    bool operator < (const seq &x)const{
        if(pos[ql] != pos[x.ql]) return pos[ql]<pos[x.ql];
        if(pos[ql] & 1) return qr<x.qr;
        else return qr>x.qr;
    }
}q[N];

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

void add(int id){
    cnt[id]++;
    res+=(ll)cnt[id]*(cnt[id]-1)/2-(ll)(cnt[id]-1)*(cnt[id]-2)/2;//����2��cnt[id]-1Ϊ0 ��ȥ֮ǰ��ͬ��ɫ������ȡ2���ĸ��� �ټ���֮�����һ����ͬ��ɫ���Ӻ�ȡ2�������н����
}

void sub(int id){
    cnt[id]--;
    res-=(ll)cnt[id]*(cnt[id]+1)/2-(ll)cnt[id]*(cnt[id]-1)/2;
}

int main(){
    int n,m,siz;
    scanf("%d%d",&n,&m);
    siz=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        pos[i]=(i-1)/siz+1;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&q[i].ql,&q[i].qr);
        q[i].id=i;
    }
    sort(q+1,q+1+m);
    int l=1,r=0,gcd0;
    for(int i=1;i<=m;i++){
        if(q[i].ql == q[i].qr){
            ans1[q[i].id]=0;
            ans2[q[i].id]=1;
            continue;
        }
        while(l<q[i].ql) sub(a[l++]);
        while(l>q[i].ql) add(a[--l]);
        while(r<q[i].qr) add(a[++r]);
        while(r>q[i].qr) sub(a[r--]);
        ans1[q[i].id]=res;
        ans2[q[i].id]=(ll)(r-l+1)*(r-l)/2;
    }
    for(int i=1;i<=m;i++){
        gcd0=gcd(ans1[i],ans2[i]);
        ans1[i]/=gcd0;
        ans2[i]/=gcd0;
        printf("%d/%d\n",ans1[i],ans2[i]);
    }
    return 0;
}
*/
