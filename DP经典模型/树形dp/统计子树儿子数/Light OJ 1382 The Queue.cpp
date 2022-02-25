#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define mod 1000000007
using namespace std;
typedef long long ll;

/*
����:��˾��n��Ա���Ŷ�ȡ��,���һ���������ڵ�kλ,��ô���ܵ��¼�Ա����������1~k-1λ,
����nλԱ���ж������Ŷӷ�ʽ.
����:http://lightoj.com/volume_showproblem.php?problem=1382
˼·:���罫��������kλ��,��ô��������Ա��ֻ�����ں����n-k��λ����.
��������Ϊһ�����ĸ��ڵ�,���¼�Ա�����������������,���������е��ֵܽڵ�֮��û���ŶӵĴ���֮��,
��ô���Խ�һ�������е�Ԫ��(����k1),������n-k��λ����,��һ��������dp[v1]*C[n-k][k1],
�ڶ�������dp[v2]*C[n-k-k1][k2],����������dp[v3]*C[n-k1-k2][k3],Ȼ���������������з�ʽ�۳���������.
dp[u]������uΪ���ڵ���������¼�Ա�����Ŷӷ�ʽ�ж�����.
*/

ll dp[N],C[N][N],siz[N];
int head[N],fa[N],cnt;
struct Node{
    int to,next;
}edge[N];

void init(){//O(n^2) Ԥ��������� ��������ó˷���ԪԤ����O(n)
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
        //siz[u]��¼��ǰ�������ĵ����������Ľڵ����,siz[v]Ϊ��ǰ�����Ľڵ����
        siz[u]+=siz[v];
        /*
        ����ʵ����ת��ʱ��һ��ѡ�������ʱsiz[u]==siz[v],
        Ȼ�����ű�������������,siz[u]����������,�������һ����.
        dp[v]����������Ԫ���ܹ������з�ʽ,dp[u]����֮ǰ�������ķ�����,
        ���������ó˷�ԭ���۳�u�ڵ�������ܹ������з�ʽ
        */
        dp[u]=((dp[u]*C[siz[u]][siz[v]])%mod*dp[v])%mod;
    }
    siz[u]++;//����u���ܵĸ���
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
            addEdge(u,v);//u��v������
            fa[v]=u;
        }
        for(int i=1;i<=n;i++){
            if(fa[i] == -1){
                rt=i;//rtΪ��������
                break;
            }
        }
        dfs(rt);
        printf("Case %d: %lld\n",cas,dp[rt]);
    }
    return 0;
}

/*
�˷���ԪԤ����O(n) ������Ż�
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
