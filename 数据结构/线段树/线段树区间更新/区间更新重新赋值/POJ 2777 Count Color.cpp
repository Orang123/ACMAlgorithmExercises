/*
题意:摘自网上
给出L段木棒，每段1cm，初始的颜色都为1，给出T种颜色，给出O个操作，
C l r c 将l到r内的木棒所有颜色更改为x ， P l r 问在l到r内有多少种颜色。
L<=10^5,T<=30,O<=10^5.
链接:http://poj.org/problem?id=2777
思路:线段树单点染色区间修改 懒惰标记,此题区别于ZOJ 1610,
ZOJ 1610是区间染色,染色是对于区间而言,而POJ 2777是针对区间
内的点进行染色更新,线段树对于POJ 2777能完美解决,但是对于区间段
的染色ZOJ 1610不一定能完美解决,会遗留掉某些区间.
*/
//ac 469ms 线段树单点染色区间修改 懒惰标记
#include<cstdio>
#include<cstring>
#define N 100010

int sum[N<<2],L,T,O,vis[31],cnt;

void pushup(int rt){
    if(sum[rt<<1] == sum[rt<<1|1])//子树颜色相同时,父节点整体更新为子树的颜色
        sum[rt]=sum[rt<<1];
    else//否则父节点大区间标记为-1
        sum[rt]=-1;
}

void pushdown(int rt){
    if(sum[rt]!=-1){
        sum[rt<<1]=sum[rt<<1|1]=sum[rt];
        //sum[rt]=-1;这里无需标记父节点颜色为-1,因为pushup时 会更新sum[rt]
    }
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=1;//初始颜色是1
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int l,int r,int rt,int curl,int curr,int c){
    if(l<=curl && curr<=r){
        sum[rt]=c;
        return;
    }
    pushdown(rt);//需要将懒惰标记下推,因为rt父节点颜色和子节点可能已经不一致了
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid,c);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr,c);
    pushup(rt);
}

void query(int l,int r,int rt,int curl,int curr){
    //查询颜色,因为初始颜色都是1,在查找过程中一定会遇到sum[rt]有颜色的情况,不会出现搜索到叶子节点还继续搜索的情况.
    if(sum[rt]!=-1){
        if(!vis[sum[rt]]){
            vis[sum[rt]]=1;
            cnt++;//[l,r]区间内不同颜色数+1
        }
        return;
    }
    //if(l == r) return;//因为初始颜色都是1,不会出现叶子节点 sum[rt]== -1的情况
    //这里无需下推懒惰标记,因为只要父节点有颜色,就会直接统计这种颜色,而不会搜索左右子树
    int mid=(curl+curr)/2;
    if(l<=mid)
        query(l,r,rt<<1,curl,mid);
    if(r>mid)
        query(l,r,rt<<1|1,mid+1,curr);
}

int main(){
    int l,r,c;
    char p;
    scanf("%d%d%d",&L,&T,&O);
    build(1,1,L);
    while(O--){
        scanf(" %c",&p);
        if(p == 'C'){
            scanf("%d%d%d",&l,&r,&c);
            update(l,r,1,1,L,c);
        }
        else{
            scanf("%d%d",&l,&r);
            memset(vis,0,sizeof(vis));
            cnt=0;
            query(l,r,1,1,L);
            printf("%d\n",cnt);
        }
    }
    return 0;
}

/*
//ac 438ms 二进制状压查询到的[l,r]内的颜色
//摘自博客:https://blog.csdn.net/winddreams/article/details/38375799
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 110000
#define lmin 1
#define rmax n
#define lson l,(l+r)/2,rt<<1
#define rson (l+r)/2+1,r,rt<<1|1
#define root lmin,rmax,1
#define now l,r,rt
#define int_now int l,int r,int rt
#define INF 0x3f3f3f3f
#define eqs 1e-6
#define LL __int64
#define mod 10007
#define zero(x) ( fabs(x) < eqs ? 0 : x )
#define mem(a,b) (memset(a),b,sizeof(a))
int cl[maxn<<2] ;
int lazy[maxn<<2] ;
void push_up(int_now)
{
    cl[rt] = cl[rt<<1] | cl[rt<<1|1] ;
}
void push_down(int_now)
{
    if( lazy[rt] )
    {
        lazy[rt<<1] = lazy[rt<<1|1] = lazy[rt] ;
        cl[rt<<1] = cl[rt<<1|1] = lazy[rt] ;
        lazy[rt] = 0 ;
    }
}
void creat(int_now)
{
    cl[rt] = lazy[rt] = 0 ;
    if( l != r )
    {
        creat(lson);
        creat(rson);
        push_up(now);
    }
    else
        cl[rt] = 1 ;
}
void update(int ll,int rr,int x,int_now)
{
    if( ll > r || rr < l )
        return ;
    if( ll <= l && r <= rr )
    {
        cl[rt] = lazy[rt] = 1<<(x-1);
        return ;
    }
    push_down(now);
    update(ll,rr,x,lson);
    update(ll,rr,x,rson);
    push_up(now);
}
int query(int ll,int rr,int_now)
{
    if(ll > r || rr < l)
        return 0;
    if(ll <= l && r <= rr)
        return cl[rt] ;
    push_down(now);
    return query(ll,rr,lson) | query(ll,rr,rson);
}
int ans(int x)
{
    int aa = 0 ;
    while(x)
    {
        if(x & 1)
            aa++ ;
        x >>= 1 ;
    }
    return aa ;
}
int main()
{
    int n , ls , m ;
    int l , r , x ;
    char str[10] ;
    while(~scanf("%d %d %d", &n, &ls, &m))
    {
        creat(root);
        while(m--)
        {
            scanf("%s", str);
            if(str[0] == 'C')
            {
                scanf("%d %d %d", &l, &r, &x);
                if(l > r)
                    swap(l,r);
                update(l,r,x,root);
            }
            else
            {
                scanf("%d %d", &l, &r);
                if(l > r)
                    swap(l,r);
                printf("%d\n",ans( query(l,r,root) ) );
            }
        }
    }
    return 0;
}
*/
