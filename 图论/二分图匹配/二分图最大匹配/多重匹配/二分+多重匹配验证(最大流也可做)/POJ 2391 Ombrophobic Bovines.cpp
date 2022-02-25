#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 500
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//ac 282ms ���+floyd+����ö�����ʱ��+�������֤
//ͬPOJ 2112
//�ö���ͼ����ƥ��,��Զ���,�����ܶ�һ��һ���ĵ�,���鷳
/*
����ժ������
����:��n���,ÿ��س�ʼ��aͷţ��һ��������bͷţ��ţ��,
��m����Ȩ��,��ʾ�߹���������Ҫ��ʱ��,��������Ҫ����ʱ��
�������е�ţ�ڽ�������(nͷţͬʱ�ж�).
����:http://poj.org/problem?id=2391
˼·:������Ҫ����ʱ��,����ʵ���ƶ�����ʱ�����ţ���ѵ�ʱ��,
����Ҫ��������ʱ����С��,��Ȼ���ֵ��С���������ö�����ʱ��,
�������֤,ͬPOJ 2112,��ͬ��������ÿ�����ʼ��ţ,����һ��������ţ��
���������ţ��,���Կɽ���i���Ϊ,i��i+n,i��ʾ��ʼʱţ�ĸ���,i+n��ʾ
ÿ����ţ�������ɵ�ţ������.Դ��0,���2*n+1,Դ����ÿ����i����,����Ϊ
��ʼţ�ĸ���,ÿ����i+n���㽨����Ϊ����ţ������޵ı�,�ٽ�i->j+n,����
Ϊ��ʼi��ţ����,��ʾi���ţҪ�ƶ���j���ţ��,�������϶������ʱ��,�����
����֤�Ƿ�������������г�ʼţ������,�����Ƿ�����ţ���ƶ�����ţ��.

ע��:�������������������ƥ������,��Ϊÿ�����ʼҲ�ж�ֻţ,��һ����Զ������,
����ò��,��Ҫ���һ��һ���ĵ�(����һ����ʼ��ţ),���������ܷ���.
*/
int n,m,st,ed,cnt,head[N],dis[N],vis[N],a[N],b[N],sum;
ll mp[N][N];
struct Edge{
    int to,next,cf;
}edge[N*N];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(ll mid){
    int ans=0;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){//����㱾���ʼ��ţ,Ҳ���Ե�����������ţ�� ��mp[i][i]=0Ҳ�ǿ��Ե�
        addEdge(st,i,a[i]);
        addEdge(i+n,ed,b[i]);
        for(int j=1;j<=n;j++){
            if(mp[i][j] != INF && mp[i][j]<=mid)
                addEdge(i,j+n,a[i]);
        }
    }
    while(bfs(st))
        ans+=dfs(st,0x3f3f3f3f);
    return ans == sum;
}

void floyd(){
    for(int t=1;t<=n;t++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j]>mp[i][t]+mp[t][j])
                    mp[i][j]=mp[i][t]+mp[t][j];
            }
        }
    }
}

void init(){
    st=0,ed=n*2+1;
    sum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            mp[i][j]=i==j?0:INF;
    }
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
        sum+=a[i];
    }
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        mp[u][v]=mp[v][u]=min(mp[u][v],w);//˫���
    }
    floyd();
    ll l=0,r=0,mid;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
            r=max(r,mp[i][j]);//���������ĳ�ʼ�Ͻ�
    }
    if(!max_flow(r)){//�������붼����ʹ������ţ���ƶ���ţ��,���޽�
        printf("-1");
        return 0;
    }
    while(l<r){
        mid=(l+r)/2;
        if(max_flow(mid))
            r=mid;
        else
            l=mid+1;
    }
    printf("%lld",r);
    return 0;
}
