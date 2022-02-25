#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 1000100
using namespace std;
typedef long long ll;
//kruskal 1752ms
/*
����:n����,m����,���mst,�Լ���������mst�����������������С����ѧ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5723
˼·:�ؼ������������������С����ѧ����,Ҫ����С,��Ȼ������Ҫ��������С������,
��ѧ����=(��������·���ľ����)/(��ȫͼ�����б���),��������·���ľ���Ϳ�ͨ��
����ÿ����������·�����׵Ĵ������,��:��Ȩ*��������ж˵����*���Ҳ����ж˵����.
��ô����������ĸ�����Ȼ��ͨ������dp���,��dpʱ˳����������·�������.
*/
//son[u]��ʾ��uΪ���ڵ�����ж��Ӹ���+1(�Լ�)
int m,fa[N],cnt,head[N];
ll n,ans,son[N];

struct Node{
    int to,next;
    ll w;
}node[N<<1];

struct Edge{
    int u,v;
    ll w;
    Edge(int u=0,int v=0,ll w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void addEdge(int from,int to,ll w){
    node[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

ll kruskal(){
    init();
    int x,y,num=0;
    ll sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            num++;
            sum+=edge[i].w;
            addEdge(edge[i].u,edge[i].v,edge[i].w);
            addEdge(edge[i].v,edge[i].u,edge[i].w);
            if(num == n-1) break;
        }
    }
    return sum;
}

void dfs(int u,int fa){
    son[u]=1;
    for(int i=head[u];i!=-1;i=node[i].next){
        int v=node[i].to;
        if(v == fa) continue;
        dfs(v,u);
        son[u]+=son[v];
        //ÿ����������·���й��׵Ĵ������������ߵ������˵�����`������Ŀ�ĳ˻�
        //��ô�����߹��׵�Ȩֵ�;�Ϊ��Ȩ*son[v]*(n-son[v])
        ans+=node[i].w*son[v]*(n-son[v]);
    }
}

int main(){
    int T;
    ll sum;
    scanf("%d",&T);
    while(T--){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%lld%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%lld",&edge[i].u,&edge[i].v,&edge[i].w);
        sum=kruskal();
        dfs(1,-1);
        printf("%lld %.2f\n",sum,(double)ans/(n*(n-1)/2));
    }
    return 0;
}
