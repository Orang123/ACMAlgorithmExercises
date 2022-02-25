#include<cstdio>
#include<algorithm>
#define N 550
#define M 25500
#define INF 0x3f3f3f3f
using namespace std;
//ac 686ms  数据改过 之前普通的并查集合并会TLE,需要用下面的启发式合并
//这里wa了很多次 是因为不连通情况的判定没有用cnt!=n-1在循环外判断,
//用了循环里flag标记,实际已有连通集可能已经连接了n个点此时加边数还未kurskal之前已经达到n-1
/*
题意:n个城市,m条道路需要修建,已经有t个城市群相互连通,所以
这t个城市群之间不需要再修建道路,问使得所有城市相互连通修建
道路的最低费用是多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3371
思路:将城市群中城市fa[N]数组都连接接起来,再跑一遍kruskal进行启发式合并即可.
*/

int n,m,k,fa[N],seq[N],cnt;

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    cnt=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    int x,y,sum=0;
    //这里对于不能构成树的情况不能用flag标记,因为有可能已有的连通集已经将n个点连接起来,
    //根本不会进入这个循环,但是cnt=n-1,这时会特判为不连通.
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    if(cnt != n-1) sum=-1;
    return sum;
}

int main(){
    int T,num,x,y;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        init();
        while(k--){
            scanf("%d",&num);
            for(int i=0;i<num;i++){
                scanf("%d",&x);
                seq[i]=x;
                x=find(seq[i]);
                y=find(seq[0]);
                if(x!=y){
                    fa[x]=y;
                    cnt++;
                }
            }
        }
        //for(int i=1;i<=n;i++) 计算已有连通集连了多少边 也可以这样计算
            //if(fa[i]!=i) cnt++;
        printf("%d\n",kruskal());
    }
    return 0;
}

/*
https://www.cnblogs.com/liyinggang/p/5471493.html 启发式合并
启发式合并：启发式合并是为了解决合并过程中树退化成链的情况，用dep[i]表示根为i的树的最大深度，
合并ra和rb时，采用最大深度小的向最大深度大的进行合 并，如果两棵树的最大深度一样，则随便选择一个作为根，
并且将根的最大深度dep自增1，这样做的好处是在n次操作后，任何一棵集合树的最大深度都不会超过log(n)，
所以使得查找的复杂度降为O( log(n) ）。
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int N = 505;
const int M = 25000;
struct Edge
{
    int s,e,len;
} edge[M];
int father[N],n,m,k;
int dep[N];
int _find(int x)
{
    if(x==father[x])return x;
    return _find(father[x]);
}
int cmp(Edge a,Edge b)
{
    return a.len<b.len;
}
int kruskal(int m)
{
    sort(edge+1,edge+m+1,cmp);
    int cost = 0;
    for(int i=1; i<=m; i++)
    {
        int x  = _find(edge[i].s);
        int y  = _find(edge[i].e);
        if(x!=y)
        {
            if(dep[x]==dep[y])
            {
                father[x] = y;
                dep[y]++;
            }
            else if(dep[x]<dep[y])
            {
                father[x] = y;
            }
            else
            {
                father[y]=x;
            }
            cost += edge[i].len;
        }
    }
    return cost;
}
int main()
{
    int tcase;
    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1; i<=n; i++)
        {
            father[i] = i;
            dep[i] =0;
        }
        for(int i=1; i<=m; i++)
        {
            scanf("%d%d%d",&edge[i].s,&edge[i].e,&edge[i].len);
        }
        while(k--)
        {
            int t,a;
            scanf("%d%d",&t,&a);
            t--;
            while(t--)
            {
                int b;
                scanf("%d",&b);
                int x = _find(a);
                int y = _find(b);
                if(x!=y)
                {
                    if(dep[x]==dep[y])
                    {
                        father[x] = y;
                        dep[y]++;
                    }
                    else if(dep[x]<dep[y])
                    {
                        father[x] = y;
                    }
                    else
                    {
                        father[y]=x;
                    }
                }
            }
        }
        int ans = 0;
        int cost = kruskal(m);
        for(int i=1; i<=n; i++)
        {
            if(father[i]==i) ans++;
        }
        if(ans==1)printf("%d\n",cost);
        else printf("-1\n");
    }
}
*/
