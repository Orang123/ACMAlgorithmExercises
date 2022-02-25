#include <bits/stdc++.h>
using namespace std;
const int N = 200020 , SIZE = 1020;
int n,m,a[N],cnt[N],Min,size,T,ans[N];
int cnt_[N],ans_,belo[N],L[N],R[N];
struct query{int l,r,id;}q[N];
inline void input(void)
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for (int i=1;i<=m;i++)
        scanf("%d%d",&q[i].l,&q[i].r) , q[i].id = i;
}
inline void init(void)
{
    for (int i=1;i<=n;i++)
        if ( a[i] <= n+1 )
            cnt[ a[i] ]++;
    while ( cnt[ ans_ ] ) ans_++;
    // 先把整个序列加入桶，同时得到整体的答案
}
inline void setblocks(void)
{
    size = sqrt(n) , T = n/size;
    for (int i=1;i<=T;i++)
    {
        if ( i * size > n ) break;
        L[i] = (i-1)*size + 1;
        R[i] = i * size;
    }
    if ( R[T] < n ) T++ , L[T] = R[T-1] + 1 , R[T] = n;
    for (int i=1;i<=T;i++)
        for (int j=L[i];j<=R[i];j++)
            belo[j] = i;
}
inline bool compare(query p1,query p2)
{
    if ( belo[p1.l] ^ belo[p2.l] )
        return belo[p1.l] < belo[p2.l];
    else return p1.r > p2.r;
}
// 删点
inline void remove(int p,int &Minval)
{
    if ( a[p] > n+1 ) return;
    cnt[a[p]]--;
    if ( cnt[a[p]] == 0 ) Minval = min( Minval , a[p] );
}
// 撤销
inline void resume(int p)
{
    if ( a[p] > n+1 ) return;
    cnt[a[p]]++;
}
inline void CaptainMo(void)
{
    sort( q+1 , q+m+1 , compare );
    int l = 1 , r = n , lastblock = 0;
    for (int i=1;i<=m;i++)
    {
        // 处理同一块中的询问
        if ( belo[q[i].l] == belo[q[i].r] )
        {
            for (int j=q[i].l;j<=q[i].r;j++)
                if ( a[j] <= n+1 ) cnt_[a[j]]++;
            int temp = 0;
            while ( cnt_[temp] ) temp++;
            ans[ q[i].id ] = temp;
            for (int j=q[i].l;j<=q[i].r;j++)
                if ( a[j] <= n+1 ) cnt_[a[j]]--;
            continue;
        }
        // 如果移动到了一个新的块，就先把左右端点初始化
        if ( belo[q[i].l] ^ lastblock )
        {
            while ( r < n ) resume(++r);
            while ( l < L[belo[q[i].l]] ) remove(l++,ans_);
            Min = ans_ , lastblock = belo[q[i].l];
        }
        // 单调地移动右端点
        while ( r > q[i].r ) remove(r--,Min);
        // 移动左端点回答询问
        int temp = Min , l_ = l;
        while ( l_ < q[i].l ) remove(l_++,temp);
        // 回滚
        while ( l_ > l ) resume(--l_);
        ans[ q[i].id ] = temp;
    }
}
int main(void)
{
    input();
    init();
    setblocks();
    CaptainMo();
    for (int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
