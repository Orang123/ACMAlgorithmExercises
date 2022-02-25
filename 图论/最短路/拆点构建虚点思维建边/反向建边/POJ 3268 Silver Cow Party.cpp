#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//ȡ�����·,���򽨱�,��ʽǰ����ʵ��
/*
����:n��ũ��,ÿ��ũ����һͷ��ţ,ũ��֮����m�������·,
����Ҫ��sũ���μӾۻ�,ÿͷ��ţ����Ҫ����s,Ȼ��ۻ������Ҫ�ٴ�
����ԭ��,����Ϊ��·�ǵ����,һ��һ�ص�·�������ǲ�ͬ��.��ÿͷ
��ţһ��һ������Ҫ��������.
����:http://poj.org/problem?id=3268
˼·:s�㷵��n����ţ���ڵصľ�����Դ�s����һ������ߵ����·���,
������ÿ����ţ��ԭ���ڵ�n����s��ľ������ͨ�����򽨱�,����һ��
��s����������·,��Ϊ�����Ƿ��򽨱����s->n�����,�Ƕ���ԭͼ,n->s
Ҳ�������.���ͨ����������Դ��,����ÿ����,ֻ�����ĳ����ţ����s���
��̾���,�޷����������ţ��.
*/

int n,m,s,cnt1,cnt2,head1[N],head2[N],vis[N],dis1[N],dis2[N];
struct Node{
    int to,next,w;
}edge1[M],edge2[M];

void addEdge1(int from,int to,int w){
    edge1[cnt1]=(Node){to,head1[from],w};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to,int w){
    edge2[cnt2]=(Node){to,head2[from],w};
    head2[from]=cnt2++;
}

void init(int s,int *dis){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s,int *dis,int *head,Node *edge){
    init(s,dis);
    queue <int>Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,w,ans=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d%d",&n,&m,&s);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge1(u,v,w);
        addEdge2(v,u,w);
    }
    spfa(s,dis1,head1,edge1);
    spfa(s,dis2,head2,edge2);
    for(int i=1;i<=n;i++)
        ans=max(ans,dis1[i]+dis2[i]);
    printf("%d",ans);
    return 0;
}

/*
//�ڽӾ���ʵ��
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,s,mp[N][N],vis[N],dis1[N],dis2[N];

void init(int s,int *dis){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s,int *dis){
    init(s,dis);
    queue <int>Q;
    vis[s]=1;
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int v=1;v<=n;v++){
            if(!mp[u][v]) continue;
            if(dis[v]>dis[u]+mp[u][v]){
                dis[v]=dis[u]+mp[u][v];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,w,ans=0;
    scanf("%d%d%d",&n,&m,&s);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        mp[u][v]=w;
    }
    spfa(s,dis1);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
            swap(mp[i][j],mp[j][i]);
    }
    spfa(s,dis2);
    for(int i=1;i<=n;i++)
        ans=max(ans,dis1[i]+dis2[i]);
    printf("%d",ans);
    return 0;
}
*/


