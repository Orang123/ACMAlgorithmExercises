/*
题意:给出n个区间,问这个区间是多少个区间的真子集.
[Si, Ei]an [Sj, Ej].If Si <= Sj and Ej <= Ei and Ei - Si > Ej - Sj
Ei - Si > Ej - Sj说明必须是真子集,不能是相等集合.
链接:http://poj.org/problem?id=2481
思路:树状数组,按照右端点从大到小排,左端点从小到大排,
对左端点构建树状数组,连续区间相等的情况,直接继承上一个区间的值,
因为相等的区间不是真子集.
*/
//ac 2282ms 按照右端点从大到小排,左端点从小到大排
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
                cnt[a[i].id]=getsum(a[i].s+1);//左端点不能是0,因此加1 查询坐标是a[i].s+1 是因为之前存在左端点相同,右端点大于当前坐标的区间也算作真子集
            update(a[i].s+1,1);
        }
        printf("%d",cnt[1]);
        for(int i=2;i<=n;i++)//这里空格写if判断会TLE,卡在这里好久,第一个元素输出,后面的输出" %d"就行
            printf(" %d",cnt[i]);
        printf("\n");
    }
    return 0;
}

/*
//ac 2313ms 按照左端点从小到大排,右端点从大到小排
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
            else//a[i].e右端的点都是第i个区间的真子集,因此减法
                cnt[a[i].id]=i-1-getsum(a[i].e);//这里查询时 实际坐标为a[i].e+1,截止到a[i].e,因为a[i].e+1有可能也是真子集,因为之前的区间左端点比第i个区间要小
            update(a[i].e+1,1);//右端点在树状数组中不能为0,实际构造时加1
        }
        printf("%d",cnt[1]);
        for(int i=2;i<=n;i++)//这里空格写if判断会TLE,卡在这里好久,第一个元素输出,后面的输出" %d"就行
            printf(" %d",cnt[i]);
        printf("\n");
    }
    return 0;
}
*/
