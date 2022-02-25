/*
题意:给你N个数Ai(i=1..n)，Q次命令，(N，Q<=100000)
命令有两种
Q x y 表示查询sum(Ai) (i=x..y)
C x y d 表示 Ai += d (i=x..y)
链接:http://poj.org/problem?id=3468
思路:线段树区间更新懒惰标记
线段树区间更新、区间查询参考博客:
https://blog.csdn.net/henulmh/article/details/98756541
https://blog.csdn.net/charles1e/article/details/53363144
懒惰标记
标记的含义：本区间已经被更新过了，但是子区间却没有被更新过，
被更新的信息是什么,核心就是我们可以直接修改一个大区间的值，
并不需要修改他的子节点，等我们需要单独提出该子节点信息的时候
再下传这个懒标记并修改这个子节点.

如果不采用懒惰标记,区间更新是指更新某个区间内的叶子节点的值，
因为涉及到的叶子节点不止一个，而叶子节点会影响其相应的非叶父节点，
那么回溯需要更新的非叶子节点也会有很多，如果一次性更新完，操作的时间
复杂度肯定不是O(lgn)，例如当我们要更新区间[0,3]内的叶子节点时，需要更新
出了叶子节点3,9外的所有其他节点。为此引入了线段树中的延迟标记概念，这也是线段树的精华所在。

延迟标记：每个节点新增加一个标记，记录这个节点是否进行了某种修改(这种修改操作会影响其子节点)，
对于任意区间的修改，我们先按照区间查询的方式将其划分成线段树中的节点，然后修改这些节点的信息，
并给这些节点标记上代表这种修改操作的标记。在修改和查询的时候，如果我们到了一个节点p，并且决定
考虑其子节点，那么我们就要看节点p是否被标记，如果有，就要按照标记修改其子节点的信息，并且给子
节点都标上相同的标记，同时消掉节点p的标记。
*/
//ac 2657ms 线段树区间更新懒惰标记
#include<cstdio>
#define N 100010
typedef long long ll;

int n,q;
struct Node{
    int l,r;
    ll sum,lazy;
}segTree[N<<2];

void pushup(int rt){
    segTree[rt].sum=segTree[rt<<1].sum+segTree[rt<<1|1].sum;
}

//O(nlog(n))
void build(int rt,int l,int r){
    segTree[rt].l=l,segTree[rt].r=r;
    if(l == r){
        scanf("%lld",&segTree[rt].sum);
        segTree[rt].lazy=0;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void pushdown(int rt){//O(1)常数时间
    if(segTree[rt].lazy){//之前的父节点被修改过,需要将更新的数值向子区间传递
        segTree[rt<<1].lazy+=segTree[rt].lazy;//左儿子区间更新lazy
        segTree[rt<<1].sum+=segTree[rt].lazy*(segTree[rt<<1].r-segTree[rt<<1].l+1);
        segTree[rt<<1|1].lazy+=segTree[rt].lazy;//右儿子区间更新lazy
        segTree[rt<<1|1].sum+=segTree[rt].lazy*(segTree[rt<<1|1].r-segTree[rt<<1|1].l+1);
        segTree[rt].lazy=0;//父节点懒惰标记清除,不再更新
    }
}

//不加懒惰标记的区间更新复杂度为 O((r-l+1)*log(n)),[l,r]为要修改的区间,(r-l+1)实际就是要修改的叶子节点的个数.
//而加上懒惰标记并不会真的全部都递归到所有的叶子节点,故而时间降低.
void update(int rt,int l,int r,ll x){//O(log(n))
    if(l<=segTree[rt].l && segTree[rt].r<=r){//当前区间在待更新区间范围内
        //将该区间包含的所有元素都更新,更新的元素个数为(segTree[rt].r-segTree[rt].l+1),更新数值为x
        segTree[rt].sum+=(segTree[rt].r-segTree[rt].l+1)*x;
        segTree[rt].lazy+=x;// 当需要更新或查询该区间子区间时 用lazy记录的数值更新子区间
        return;
    }
    pushdown(rt);//当要判断子区间时,判断当前区间rt之前是否更新过,如果更新过并且lazy还没向下传递,就用lazy[rt]更新子区间
    int mid=(segTree[rt].l+segTree[rt].r)/2;
    if(l<=mid)
        update(rt<<1,l,r,x);
    if(r>mid)
        update(rt<<1|1,l,r,x);
    pushup(rt);
}

ll query(int rt,int l,int r){//O(log(n))
    if(l<=segTree[rt].l && segTree[rt].r<=r)
        return segTree[rt].sum;
    pushdown(rt);//当前区间rt如果更新过,查询时如果子区间还未更新之前父区间rt的lazy标记,则先更新
    int mid=(segTree[rt].l+segTree[rt].r)/2;
    ll res=0;
    if(l<=mid)
        res+=query(rt<<1,l,r);
    if(r>mid)
        res+=query(rt<<1|1,l,r);
    return res;
}

int main(){
    int a,b;
    ll c;
    char p;
    scanf("%d%d",&n,&q);
    build(1,1,n);
    while(q--){
        scanf(" %c",&p);
        if(p == 'C'){
            scanf("%d%d%lld",&a,&b,&c);
            update(1,a,b,c);
        }
        else{
            scanf("%d%d",&a,&b);
            printf("%lld\n",query(1,a,b));
        }
    }
    return 0;
}

/*
//ac 2860ms 线段树区间更新懒惰标记精简版
#include<cstdio>
#define N 100010
typedef long long ll;

int n,q;
ll sum[N<<2],lazy[N<<2];

void pushdown(int rt,int l,int r){
    if(lazy[rt]){
    	int mid=(l+r)/2;
        lazy[rt<<1]+=lazy[rt];
        sum[rt<<1]+=lazy[rt]*(mid-l+1);
        lazy[rt<<1|1]+=lazy[rt];
        sum[rt<<1|1]+=lazy[rt]*(r-mid);
        lazy[rt]=0;
    }
}

void update(int l,int r,int rt,int curl,int curr,ll x){
    if(l<=curl && curr<=r){
        sum[rt]+=(curr-curl+1)*x;
        lazy[rt]+=x;
        return;
    }
    pushdown(rt,curl,curr);
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid,x);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr,x);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

ll query(int l,int r,int rt,int curl,int curr){
    if(l<=curl && curr<=r)
        return sum[rt];
    pushdown(rt,curl,curr);
    int mid=(curl+curr)/2;
    ll res=0;
    if(l<=mid)
        res+=query(l,r,rt<<1,curl,mid);
    if(r>mid)
        res+=query(l,r,rt<<1|1,mid+1,curr);
    return res;
}

int main(){
    int a,b;
    ll c,x;
    char p;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&x);
    	update(i,i,1,1,n,x);
	}
    while(q--){
        scanf(" %c",&p);
        if(p == 'C'){
            scanf("%d%d%lld",&a,&b,&c);
            update(a,b,1,1,n,c);
        }
        else{
            scanf("%d%d",&a,&b);
            printf("%lld\n",query(a,b,1,1,n));
        }
    }
    return 0;
}
*/

/*
//ac 1728ms 树状数组做法 暂时没看懂这种做法
//摘自博客:https://www.cnblogs.com/Newdawn/p/4197324.html
//朴素的树状数组修改区间 时间复杂度为(r-l+1)*log(N),实际是区间内的每个点 都进行单点修改,如果实际区间很大 操作次数q很多,这个复杂度q*(r-l+1)*log(N) 会是平方复杂度
#include<cstdio>
#include<cstring>
#define lowbit(x) ((x)&-(x))
typedef long long LL;
const int maxn= 100003;
LL org[maxn+3];

struct tree{
    LL c[maxn+3];
    void clear() {    memset(c,0,sizeof(c));    }
    LL sum(int x) const {
        LL res= 0;
        while(x){
            res+= c[x];
            x-= lowbit(x);
        }
        return res;
    }
    void add(int x, LL d){
        while(x<=maxn){
            c[x]+= d;
            x+= lowbit(x);
        }
    }
} d1,d2;

inline LL sum(int x) {
    return org[x]+(x+1)*d1.sum(x)-d2.sum(x);
}

int main(){
    int n,q,a,b;
    LL x,c;
    while(~scanf("%d%d",&n,&q)){
        memset(org,0,sizeof(org));
        d1.clear();
        d2.clear();
        for(int i=1; i<=n; ++i){
            scanf("%lld",&x);
            org[i]= org[i-1]+x;
        }
        while(q--){
            getchar();
            if(getchar()=='Q'){
                scanf("%d%d",&a,&b);
                printf("%lld\n",sum(b)-sum(a-1));
            }
            else {
                scanf("%d%d%lld",&a,&b,&c);
                d1.add(a,c);
                d1.add(b+1,-c);
                d2.add(a,c*a);
                d2.add(b+1,-c*(b+1));
            }
        }
    }
    return 0;
}
*/
