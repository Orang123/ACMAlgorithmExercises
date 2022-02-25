/*
题意:摘自网上
FJ有n头牛，排列成一条直线(不会在同一个点)，给出每头牛在直线上的坐标x。
另外，每头牛还有一个自己的声调v，如果两头牛(i和j)之间想要沟通的话，
它们必须用同个音调max(v[i],v[j])，沟通起来消耗的能量为：
max(v[i],v[j]) * 它们之间的距离。问要使所有的牛之间都能沟通(两两之间)，
总共需要消耗多少能量。
n,v[i],x<=20000.
链接:http://poj.org/problem?id=1990
思路:构建2个树状数组,一个存储小于坐标x的坐标个数,
一个存储小于坐标x的坐标之和,将牛按照h从小到达排序,
这样能保证两两配对时,取的是当前第i头牛的v.
因为是两两配对,考虑第i头牛时只考虑前i-1头牛中小于第
i头牛坐标和大于第i头牛坐标,因为差值是绝对值,要写成大x的减去小的x.
坐标相等的差值本身就是0,不用特别考虑.
*/
//ac 110ms 从小到大排序和编号为1~i-1头牛对比,先查询后加入.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20010
typedef long long ll;
using namespace std;

int n,maxn;
ll c[N],b[N];//c表示小于等于x的个数,b表示小于等于x的坐标之和

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
        sumc=getsum(c,a[i].x);//小于等于a[i].x的个数 这里写成a[i].x-1 只统计小于a[i].x也没有错,等于的情况本身差值就是0
        sumb=getsum(b,a[i].x);//小于等于a[i].x的坐标之和
        res1=a[i].v*(sumc*a[i].x-sumb);//(a[i].x-a[1..i-1].x)*a[i].v
        //total-sumb表示1~i-1中大于a[i].x的坐标之和,
        //(i-1-sumc)表示1~i-1中大于a[i].x的个数
        //坐标差的形式a[1..i-1].x-a[i].x
        res2=a[i].v*(total-sumb-(i-1-sumc)*a[i].x);
        ans+=res1+res2;
        total+=a[i].x;
        update(c,a[i].x,1);//将第i头牛加入树状数组
        update(b,a[i].x,a[i].x);
    }
    printf("%lld",ans);
    return 0;
}

/*
//ac 63ms 从大到小排序和编号为i+1~n 头牛对比 先构建树状数组,每对比一个 就将第i头牛在树状数组中删除
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
        sumc=getsum(c,a[i].x);//i+1~n中小于等于a[i].x的个数
        sumb=getsum(b,a[i].x);//i+1~n中小于等于a[i].x的坐标之和
        res1=a[i].v*(sumc*a[i].x-sumb);
        //getsum(b,maxn)-getsum(b,a[i].x) i+1~n中大于a[i].x的坐标之和  maxn是最大的x坐标,树状数组中最大的祖先节点编号
        //getsum(c,maxn)-getsum(c,a[i].x) i+1~n中大于a[i].x的个数
        res2=a[i].v*(getsum(b,maxn)-getsum(b,a[i].x)-(getsum(c,maxn)-getsum(c,a[i].x))*a[i].x);
        ans+=res1+res2;
        update(c,a[i].x,-1);//第i头牛已经和其余所有奶牛对比过了,不再对比,因此删掉
        update(b,a[i].x,-a[i].x);
    }
    printf("%lld",ans);
    return 0;
}
*/
