/*
题意:摘自网上
日本岛的东海岸和西海岸分别有N和M个城市，在这些城市中有K条高速公路，
每条公路连接着东海岸一个城市和西海岸的一个城市，问总共这些公路有多少交叉点
N,M<=1000.
链接:http://poj.org/problem?id=3067
思路:公路(u1,v1),(u2,v2)会出现交点的情况为u1<u2,v1>v2或
u1>u2,v1<v2 这种情况才会出现交点.其实就是固定一个端点的
大小关系找另一个端点构成的逆序对的总个数,可用树状数组优化时间.
2种做法:
1.按照u第一关键字,v第二关键字从小到大排序,将端点v作为树状数组中的节点编号.
那么树状数组节点存储的就是没有构成交点的公路个数,那么实际逆序对就是
i-getsum(a[i].v),i为当前更新的公路个数.
2.按照u第一关键字,v第二关键字从大到小排序,将端点v作为树状数组中的节点编号.
那么树状数组节点存储的就是构成交点的公路个数,那么实际逆序对就是
getsum(a[i].v-1),这里要注意右端有交点的情况不算入构成交点的情况,因此查询时
编号减1,但是更新编号不减1
*/
//ac 407ms
//从小到大排序 ans+=i-getsum(a[i].v) 先更新后查询
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000000
typedef long long ll;
using namespace std;

int n,m,k,maxn,c[N];
struct Ele{
    int u,v;
    bool operator < (const Ele &x)const{
        if(u!=x.u)
            return u<x.u;
        else
            return v<x.v;
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
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        maxn=-1;
        memset(c,0,sizeof(c));
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=k;i++){
            scanf("%d%d",&a[i].u,&a[i].v);
            maxn=max(maxn,a[i].v);//v节点编号最大编号 作为树状数组最大的祖先节点
        }
        sort(a+1,a+1+k);
        ll ans=0;
        for(int i=1;i<=k;i++){
            update(a[i].v,1);//先更新后查询
            ans+=i-getsum(a[i].v);//这里队友右端v节点重合的情况本身 就是算入不构成交点的情况会被减掉
        }
        printf("Test case %d: %lld\n",cas,ans);
    }
    return 0;
}

/*
//ac 391ms
//从大到小排序 ans+=getsum(a[i].v-1) 先查询后更新
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000000
typedef long long ll;
using namespace std;

int n,m,k,maxn,c[N];
struct Ele{
    int u,v;
    bool operator < (const Ele &x)const{
        if(u!=x.u)
            return u>x.u;
        else
            return v>x.v;
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
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        maxn=-1;
        memset(c,0,sizeof(c));
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=k;i++){
            scanf("%d%d",&a[i].u,&a[i].v);
            maxn=max(maxn,a[i].v);
        }
        sort(a+1,a+1+k);
        ll ans=0;
        for(int i=1;i<=k;i++){//先查询 后更新
            ans+=getsum(a[i].v-1);//v右端有交点时会错误算入交点,所以查询编号要减1
            update(a[i].v,1);//更新编号依旧是a[i].v
        }
        printf("Test case %d: %lld\n",cas,ans);
    }
    return 0;
}

*/
