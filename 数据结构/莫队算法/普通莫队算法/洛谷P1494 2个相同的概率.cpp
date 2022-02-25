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
    这里可以理解为 下标为i的袜子和之前选择的相同颜色的袜子搭配总共能配对 几双,
    把这个结果加上就是这种颜色的袜子总共能配对几双,cnt[x]本身的结果是上一次cnt[x]++多了一次的.
    */
    res+=cnt[x];
    cnt[x]++;
}

void sub(int id){
    int x=a[id];
    cnt[x]--;
    //这里同理 得把上一次最后一次选择的相同颜色的袜子之前的相同的数目减去,因为这是和这个最后一次选入的袜子和之前构成的袜子搭配多加的对数
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
        if(q[i].ql == q[i].qr){//这里需要特判,因为组合数c[i][j] j>=i,如果只有一个数时无法选出2个数的,分母会为0失去意义
            ans1[q[i].id]=0;
            ans2[q[i].id]=1;
            continue;
        }
        while(l<q[i].ql) sub(l++);
        while(l>q[i].ql) add(--l);
        while(r<q[i].qr) add(++r);
        while(r>q[i].qr) sub(r--);
        ans1[q[i].id]=res;
        ans2[q[i].id]=(ll)(r-l+1)*(r-l)/2;//组合数C[r-l+1][2] [l,r]区间内所有的袜子任取2双的所有可能结果数 (r-l+1)*(r-l)可能会超出int的范围一点,因此要强制转化避免溢出
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
相同袜子 组合数法 c[i][2]
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
    res+=(ll)cnt[id]*(cnt[id]-1)/2-(ll)(cnt[id]-1)*(cnt[id]-2)/2;//不够2个cnt[id]-1为0 减去之前相同颜色袜子里取2个的个数 再加上之后加入一个相同颜色袜子后取2个的所有结果数
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
