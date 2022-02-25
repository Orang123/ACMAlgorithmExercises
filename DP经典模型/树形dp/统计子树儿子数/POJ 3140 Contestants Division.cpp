#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define fabs(a) (a)>0?(a):0-(a)//�궨��ķ�ʽ,һ��Ҫ�ڲ�������Χ��()
#define INF 1e16
using namespace std;
typedef long long ll;

/*
����:һ����,���ɾ��ĳ���ߺ�ֳɵ��������ָ����ܺ͵���С��ֵ.
����:http://poj.org/problem?id=3140
˼·:����dp,���ÿ����������еĽڵ�����.��ans=min(ans,sum-2*siz[u])
*/
int cnt,n,m,head[N];
ll a[N],siz[N],sum,ans;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    siz[u]=a[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
    ans=min(ans,llabs(sum-2*siz[u]));//����abs()ֻ�ܱȽ�int,��sum siz[u]��ll,����Ҫ��llabs(),�󾫶�תС���Ȼᾫ�ȶ�ʧ poj���벻ͨ��
}

int main(){
    int u,v,cas=0;
    while(scanf("%d%d",&n,&m) && n && m){
        cas++;
        ans=INF;
        sum=cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            sum+=a[i];
        }
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        printf("Case %d: %lld\n",cas,ans);
    }
    return 0;
}
