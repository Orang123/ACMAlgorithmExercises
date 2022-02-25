#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 50100
using namespace std;

int a[N],pos[N],cnt[N],ans[N],res;

struct seq{
    int ql,qr,id;
    bool operator < (const seq &x)const{
        //奇偶化排序 要快一半时间左右 100ms
        if(pos[ql] != pos[x.ql]) return ql<x.ql;//这里如果块号不同 采用区间左端点排序会更快 原先 return pos[ql]<pos[x.ql];
        if(pos[ql] & 1) return qr<x.qr;
        else return qr>x.qr;
    }
}q[N];

void add(int id){
    int x=a[id];
    cnt[x]++;
    res+=cnt[x]*cnt[x]-(cnt[x]-1)*(cnt[x]-1);
}

void sub(int id){
    int x=a[id];
    cnt[x]--;
    res-=(cnt[x]+1)*(cnt[x]+1)-cnt[x]*cnt[x];
}

int main(){
    int n,m,k,siz;
    scanf("%d%d%d",&n,&m,&k);
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
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l<q[i].ql) sub(l++);
        while(l>q[i].ql) add(--l);
        while(r<q[i].qr) add(++r);
        while(r>q[i].qr) sub(r--);
        ans[q[i].id]=res;
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
