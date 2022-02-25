#include<set>
#include<map>
#include<stack>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
int n,m,rt;
int x,y;
int head[500010];
int to[1000010];
int next[1000010];
int son[500010];
int mx[500010];
int top[500010];
int d[500010];
int f[500010];
int tot;
void add(int x,int y)
{
    tot++;
    next[tot]=head[x];
    head[x]=tot;
    to[tot]=y;
}
void dfs(int x)
{
    d[x]=d[f[x]]+1;
    mx[x]=d[x];
    for(int i=head[x];i;i=next[i])
    {
        if(to[i]!=f[x])
        {
            f[to[i]]=x;
            dfs(to[i]);
            mx[x]=max(mx[to[i]],mx[x]);
            if(mx[to[i]]>mx[son[x]])
            {
                son[x]=to[i];
            }
        }
    }
}
void dfs2(int x,int tp)
{
    top[x]=tp;
    if(son[x])
    {
        dfs2(son[x],tp);
    }
    for(int i=head[x];i;i=next[i])
    {
        if(to[i]!=f[x]&&to[i]!=son[x])
        {
            dfs2(to[i],to[i]);
        }
    }
}
int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(d[top[x]]<d[top[y]])
        {
            swap(x,y);
        }
        x=f[top[x]];
    }
    return d[x]<d[y]?x:y;
}
int main()
{
    scanf("%d%d%d",&n,&m,&rt);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs(rt);
    dfs2(rt,rt);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
}