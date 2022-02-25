#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define mod 1000000007
using namespace std;
typedef long long ll;

/*
题意:公司的n个员工排队取餐,如果一个主管排在第k位,那么主管的下级员工不能排在1~k-1位,
问这n位员工有多少种排队方式.
链接:http://lightoj.com/volume_showproblem.php?problem=1382
思路:假如将主管排在k位上,那么其下属的员工只能排在后面的n-k个位置上.
将主管作为一棵树的根节点,其下级员工在它下面的子树里,对于子树中的兄弟节点之间没有排队的次序之分,
那么可以将一棵子树中的元素(个数k1),放置在n-k个位置中,第一个棵子树dp[v1]*C[n-k][k1],
第二棵子树dp[v2]*C[n-k-k1][k2],第三棵子树dp[v3]*C[n-k1-k2][k3],然后将三个子树的排列方式累乘起来即可.
dp[u]代表以u为根节点的子树其下级员工的排队方式有多少种.
*/

ll dp[N],C[N][N],siz[N];
int head[N],fa[N],cnt;
struct Node{
    int to,next;
}edge[N];

void init(){//O(n^2) 预处理组合数 这里可以用乘法逆元预处理O(n)
    for(int i=0;i<N;i++)
        C[i][0]=1;
    for(int i=1;i<N;i++)
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
}

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dp[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v);
        //siz[u]记录当前遍历过的的所有子树的节点个数,siz[v]为当前子树的节点个数
        siz[u]+=siz[v];
        /*
        这里实际在转移时第一次选择的子树时siz[u]==siz[v],
        然后随着遍历的子树增多,siz[u]才慢慢增大,但结果是一样的.
        dp[v]代表子树的元素总共的排列方式,dp[u]代表之前的子树的方案数,
        这里是利用乘法原理累乘u节点的子树总共的排列方式
        */
        dp[u]=((dp[u]*C[siz[u]][siz[v]])%mod*dp[v])%mod;
    }
    siz[u]++;//加上u主管的个数
}

int main(){
    int T,n,u,v,rt,cas=0;
    init();
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        memset(fa,-1,sizeof(fa));
        memset(head,-1,sizeof(head));
        memset(siz,0,sizeof(siz));
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);//u是v的主管
            fa[v]=u;
        }
        for(int i=1;i<=n;i++){
            if(fa[i] == -1){
                rt=i;//rt为最大的主管
                break;
            }
        }
        dfs(rt);
        printf("Case %d: %lld\n",cas,dp[rt]);
    }
    return 0;
}

/*
乘法逆元预处理O(n) 组合数优化
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
struct Edge
{
    int v,next;
}edge[1111];
int tot;
typedef long long ll;
int head[1111];
int size[1111];
ll fac[1111];
ll inv[1111];
const int maxn=1111;
ll quickpower(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1){
            ans*=a;
            ans%=mod;
        }
        a=(a*a)%mod;
        b=b>>1;
    }
    return ans;
}

ll C(int a,int b)
{
    ll res;
    res=fac[a]*inv[b]%mod*inv[a-b]%mod;
    return res;
}
void addedge(int u,int v)
{
    edge[tot].v=v;edge[tot].next=head[u];head[u]=tot++;
}
int getsize(int u)
{
    if(size[u]) return size[u];
    int res=1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].v;
        res+=getsize(v);
    }
    return size[u]=res;
}

ll dfs(int u)
{
    int cnt=size[u]-1;
    ll res=1;
    for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int v=edge[i].v;
            res*=(dfs(v)*C(cnt,size[v]))%mod;
            res%=mod;
            cnt-=size[v];
        }
    return res;
}
int vis[10101];

int main()
{
    int t;int n;
    scanf("%d",&t);
    fac[0]=1;
    for(int i=1;i<maxn;i++)
        fac[i]=(fac[i-1]*i)%mod;
     inv[maxn-1]=quickpower(fac[maxn-1],mod-2);
     for(int i=maxn-2;i>=0;i--)
        inv[i]=inv[i+1]*(i+1)%mod;
    for(int cse=1;cse<=t;cse++)
    {
        cin>>n;
        tot=0;
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        memset(size,0,sizeof(size));
        for(int i=1;i<n;i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            addedge(a,b);
            vis[b]=1;
        }
        int root;
        for(int i=1;i<=n;i++)
        {
            if(!vis[i]) {
                root=i; break;
            }
        }
        getsize(root);
        printf("Case %d: %lld\n",cse,dfs(root) );
    }

}
*/
