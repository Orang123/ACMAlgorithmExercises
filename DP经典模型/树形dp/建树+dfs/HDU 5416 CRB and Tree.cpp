#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

/*
题意:一棵n个节点的树,任意两点间的距离为这两点间路径权值的异或值,现在有q个询问,对与每次
的询问距离s,输出两点间距离为s的点对的数目.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5416
思路:因为距离是边权异或值,所以直接求出每个点距离根节点的距离,那么任意两点间的距离都可以用距离根节点的距离相异或
dp1[u]记录u节点距离1节点距离,dp2[s]求出距离根节点距离为s的点共有多少个
*/

int cnt,n,q,dp1[N],dp2[N*10],head[N];//dp2存的是边权异或值 数组要开大一点

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa,int w){
    dp1[u]=w;
    dp2[w]++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u,w^edge[i].w);
    }
}

int main(){
    int T,u,v,w,tmp;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(dp2,0,sizeof(dp2));
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        dfs(1,-1,0);
        scanf("%d",&q);
        ll ans;
        while(q--){
            scanf("%d",&tmp);
            ans=0;
            for(int i=1;i<=n;i++){
                //直接用现有点距异或这个距离,如果得到的距离也是某个点的距离,则可以和距离是w的点构成距离为tmp的点对,反过来同理
                w=tmp^dp1[i];//tmp^dp1[i]=w tmp^w=dp1[i] 这里会重复计算2遍,所以最终结果要除2
                ans+=dp2[w];
            }
            if(!tmp)
                ans+=n;//这里包括(i,i)的点对n个和 距离1根节点长度相同的点对异或构成长度为0的点对 ans/2后刚好就是正确答案
            printf("%lld\n",ans/2);
        }
    }
    return 0;
}

/*
乘法原理 组合数计算方法
https://blog.csdn.net/acm_cxq/article/details/51668482
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 200005
#define LL long long
struct Edge
{
    int u,v,w,next;
} edge[N*2];
int cnt,head[N],n;
int f[N],vis[N];
void init()
{
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(f,0,sizeof(f));
}
void addedge(int u,int v,int w)
{
    edge[cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void dfs(int root,int cost)
{
    f[cost]++;
    vis[root]=1;
    for(int i=head[root]; i!=-1; i=edge[i].next)
    {
        int v=edge[i].v,w=edge[i].w;
        if(vis[v]) continue;
        dfs(v,cost^w);
    }
}
int main()
{
    int T,q,t;
    int u,v,w;
    scanf("%d",&T);
    while(T--)
    {
        init();
        scanf("%d",&n);
        for(int i=1; i<n; i++)
        {
            scanf("%d %d %d",&u,&v,&w);
            addedge(u,v,w);
            addedge(v,u,w);
        }
        dfs(1,0);
        scanf("%d",&q);
        while(q--)
        {
            LL ans=0;
            scanf("%d",&t);
            if(t==0)
            {
                for (int i=0;i<N;i++)
                    ans=ans+(LL)f[i]*(f[i]-1)/2;//C[n][2]
                ans+=n;
            }
            else
            {
                for(int i=0; i<N; i++)
                {
                    int tt=i^t;//(s^i)^i=s
                    if(tt>=N) continue;
                    ans+=(LL)f[i]*f[tt];
                }
                ans/=2;//i和i^t会各枚举一次 但会重复计算一次
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}
*/

