#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5500
#define INF 0x3f3f3f3f
using namespace std;
//prim+dp 10ms

/*
����:�����С�������ͷ��ϸ��С������,�������ͨ,���"No way",
��������ڷ��ϸ��С���������"No second way",�������������ϸ�
��С��������Ȩֵ��.
����:https://www.luogu.com.cn/problem/UVA10462
˼·:��Ϊ���ر�,������used[N][N]�ж��Ƿ����mst��,ֱ����edge[M<<1]�м���flag���
�Ƿ����mst,primʱ��Ҫ�ñ߼���ŵ������ͬʱ�������ߺͷ����.֮�����prim+dp��¼·�����
��Ȩ,�����ϸ��С��.
*/

int n,m,head[N],cnt,dis[N],vis[N],maxLen[N][N],seq[N],sum;

struct state{
    int u,v,dis,id;
    state(int u=0,int v=0,int dis=0,int id=0):u(u),v(v),dis(dis),id(id){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Edge{
    int from,to,next,w,flag;
}edge[M<<1];

void addEdge(int from,int to,int w,int flag){
    edge[cnt]=(Edge){from,to,head[from],w,flag};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    dis[s]=0;
    memset(maxLen,0,sizeof maxLen);
}

int prim(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(s,s,0,0));
    int u,v,num=0;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        Q.pop();
        u=tmp.v;
        if(vis[u]) continue;
        vis[u]=1;
        if(u!=s)
            //�������ߺͷ���߼���mst,���ֻ���һ����,�ж�ʱ�����Ҳ����г�δ����mst�ĵ��½������
            edge[tmp.id].flag=edge[tmp.id^1].flag=1;
        sum+=dis[u];
        for(int i=1;i<=num;i++)
            maxLen[seq[i]][u]=maxLen[u][seq[i]]=max(maxLen[seq[i]][tmp.u],dis[u]);
        seq[++num]=u;
        if(num == n) return 1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(state(u,v,dis[v],i));
            }
        }
    }
    return 0;
}

int main(){
    int T,u,v,w,ans,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=cnt=0;
        ans=INF;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w,0);
            addEdge(v,u,w,0);
        }
        if(!prim(1)){
            printf("Case #%d : No way\n",cas);
            continue;
        }
        for(int i=0;i<cnt;i+=2){
            u=edge[i].from;
            v=edge[i].to;
            if(!edge[i].flag)//����ñ�δ����mst,�����ñ߳ɻ��� ȥ����������Ȩ,��¼Ȩֵ����Сֵ
                ans=min(ans,sum-maxLen[u][v]+edge[i].w);
        }
        if(ans == INF)  printf("Case #%d : No second way\n",cas);
        else printf("Case #%d : %d\n",cas,ans);
    }
    return 0;
}

/*
//kruskal+����dp(O(n)) ac 10ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5500
#define INF 0x3f3f3f3f
using namespace std;
//dp[u][v] ��������u��v·���ϵ�����Ȩ
int n,m,fa[N],cnt,head[N],sum,dp[N][N],seq[N],num;

struct Node{
    int to,next,w;
}node[N<<1];

void addEdge(int from,int to,int w){
    node[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

struct Edge{
    int u,v,w,flag;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    memset(dp,0,sizeof dp);
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,num0=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            addEdge(edge[i].u,edge[i].v,edge[i].w);
            addEdge(edge[i].v,edge[i].u,edge[i].w);
            edge[i].flag=1;
            sum+=edge[i].w;
            num0++;
            if(num0 == n-1) break;
        }
    }
    if(num0 == n-1) return 1;
    else return 0;
}

void dfs(int u,int fa){
    seq[++num]=u;//ÿ����һ����ͽ������seq������,����dp
    for(int i=head[u];i!=-1;i=node[i].next){
        int v=node[i].to;
        if(v == fa) continue;
        for(int j=1;j<=num;j++)//���֮ǰ�������ĵ㵽��ǰ��·���ϵ�����Ȩ
            dp[seq[j]][v]=dp[v][seq[j]]=max(dp[seq[j]][u],node[i].w);//�Ƚ�֮ǰ�㵽ǰ���͵�ǰ��Ȩ�����ֵ
        dfs(v,u);
    }
}

int main(){
    int T,u,v,ans,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=cnt=0;
        ans=INF;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
            edge[i].flag=0;
        }
        if(!kruskal()){
            printf("Case #%d : No way\n",cas);
            continue;
        }
        num=0;
        dfs(1,-1);//O(n)
        for(int i=1;i<=m;i++){
            u=edge[i].u;
            v=edge[i].v;
            if(!edge[i].flag)
                ans=min(ans,sum-dp[u][v]+edge[i].w);
        }
        if(ans == INF)  printf("Case #%d : No second way\n",cas);
        else printf("Case #%d : %d\n",cas,ans);
    }
    return 0;
}
*/

/*
kruskal/prim+lca(������������������������Ȩֵ)
*/
