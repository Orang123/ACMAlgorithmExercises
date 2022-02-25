#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

/*
����:һ��n���ڵ����,���������ľ���Ϊ�������·��Ȩֵ�����ֵ,������q��ѯ��,����ÿ��
��ѯ�ʾ���s,�����������Ϊs�ĵ�Ե���Ŀ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5416
˼·:��Ϊ�����Ǳ�Ȩ���ֵ,����ֱ�����ÿ���������ڵ�ľ���,��ô���������ľ��붼�����þ�����ڵ�ľ��������
dp1[u]��¼u�ڵ����1�ڵ����,dp2[s]���������ڵ����Ϊs�ĵ㹲�ж��ٸ�
*/

int cnt,n,q,dp1[N],dp2[N*10],head[N];//dp2����Ǳ�Ȩ���ֵ ����Ҫ����һ��

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
                //ֱ�������е������������,����õ��ľ���Ҳ��ĳ����ľ���,����Ժ;�����w�ĵ㹹�ɾ���Ϊtmp�ĵ��,������ͬ��
                w=tmp^dp1[i];//tmp^dp1[i]=w tmp^w=dp1[i] ������ظ�����2��,�������ս��Ҫ��2
                ans+=dp2[w];
            }
            if(!tmp)
                ans+=n;//�������(i,i)�ĵ��n���� ����1���ڵ㳤����ͬ�ĵ����򹹳ɳ���Ϊ0�ĵ�� ans/2��պþ�����ȷ��
            printf("%lld\n",ans/2);
        }
    }
    return 0;
}

/*
�˷�ԭ�� ��������㷽��
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
                ans/=2;//i��i^t���ö��һ�� �����ظ�����һ��
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}
*/

