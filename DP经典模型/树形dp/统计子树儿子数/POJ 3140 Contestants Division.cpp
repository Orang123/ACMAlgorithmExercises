#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define fabs(a) (a)>0?(a):0-(a)//宏定义的方式,一定要在参数里外围加()
#define INF 1e16
using namespace std;
typedef long long ll;

/*
题意:一棵树,求出删掉某条边后分成的两个部分各自总和的最小差值.
链接:http://poj.org/problem?id=3140
思路:树形dp,求出每个点的子树中的节点总数.再ans=min(ans,sum-2*siz[u])
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
    ans=min(ans,llabs(sum-2*siz[u]));//这里abs()只能比较int,而sum siz[u]是ll,所以要用llabs(),大精度转小精度会精度丢失 poj编译不通过
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
