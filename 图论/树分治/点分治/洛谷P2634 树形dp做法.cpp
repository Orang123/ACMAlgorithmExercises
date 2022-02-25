/*
我们定义 f[x][0,1,2] 表示在点x及其子树中，距离点x的距离在模3意义下为0,1,2的点分别有多少个。
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=2e4+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
int f[maxn][3];
int n,ans,full,g;

inline void addedge(int from,int to,int len)
{
    static int cnt = 0;
    t[++cnt] = to;
    l[cnt] = len;
    nxt[cnt] = s[from];
    s[from] = cnt;
}

inline int mod(int x)
{
    return (x%3+3)%3;
}

inline int gcd(int x,int y)
{
    if( ! ( x && y ) )
        return x | y;
    register int t;
    while( t = x % y )
        x = y , y = t;
    return y;
}

inline void dfs(int pos,int fa)
{
    f[pos][0] = 1;
    for(int at=s[pos];at;at=nxt[at])
    {
        if( t[at] == fa )
            continue;
        dfs(t[at],pos);
        for(int i=0;i<3;i++)
            ans += f[t[at]][i] * f[pos][mod(-i-l[at])] * 2;
        for(int i=0;i<3;i++)
            f[pos][mod(i+l[at])] += f[t[at]][i];
    }
}

inline int getint()
{
    int ret = 0 , fix = 1;
    char ch = getchar();
    while( ! isdigit(ch) )
        fix = ch == '-' ? -1 : fix,
        ch = getchar();
    while( isdigit(ch) )
        ret = ret * 10 + ( ch - '0' ),
        ch = getchar();
    return ret * fix;
}

int main()
{
    n = getint();
    for(int i=1,a,b,l;i<n;i++)
    {
        a = getint() , b = getint() , l = getint();
        addedge(a,b,l);
        addedge(b,a,l);
    }
    
    dfs(1,-1);
    
    ans += n;
    full = n * n;
    g = gcd( ans , full );
    ans /= g , full /= g;
    
    printf("%d/%d\n",ans,full);
    
    return 0;
}