#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 5000
#define INF 0x3f3f3f3f
using namespace std;
//ac 46ms dinic floyd+���+��С��
/*
����:���1���յ�n,��һЩ����ı�,ÿ���ߵ�ʱ������Ϊ1,
�ƻ��м��һЩ��,����ݻٶ��ٸ�����������kʱ�����޷�����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2485
˼·:������floyd�������1��n�����·,���ڴ�1��n����ʱ��С�ڵ���k��
��������INF,����������ɾ�����ٵ����ʹ����Щ���·���Ͽ�,���Բ��,i���,i+n����,
����佨����Ϊ1�ı�,��ô���������ת��Ϊ����Դ�ͻ�����Ҫɾ���ٱ�,����Щ��ǡ�þ��ǲ��,
,�������ɾ��ת��Ϊ��ɾ��,ת��Ϊ�������С�������,��ô��С��=�����.
*/
int n,m,k,st,ed,cnt,head[N],dis[N],vis[N],mp[N][N],a[M],b[M];
struct Edge{
    int to,next,cf;
}edge[M<<1];

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

int max_flow(){
    int sum=0;
    while(bfs(st))
        sum+=dfs(st,INF);
    return sum;
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
    cnt=0;
    st=1,ed=n*2;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i == j) mp[i][j]=0;
            else mp[i][j]=INF;
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            mp[u][v]=1;
            a[i]=u,b[i]=v;
        }
        floyd();
        for(int i=2;i<n;i++)
            addEdge(i,i+n,1);
        addEdge(1,1+n,INF);
        addEdge(n,n+n,INF);
        for(int i=1;i<=m;i++){
            if(mp[1][a[i]]+1+mp[b[i]][n]<=k)//a[i]->b[i] ����ʱ��1
                addEdge(a[i]+n,b[i],INF);
        }
        printf("%d\n",max_flow());
    }
    return 0;
}

/*
//ac 31ms EK�㷨 ������
//������õ�Ч�����·��Ȩֵ֮���Բ�����ͳ����ķ���Ϊ0,
//����Ϊ���䲢��������ʵ��·��Ȩֵ,��ֻ��ʵ�ʵı�Ȩ�����ۼ�Ȩֵ��,
//��ÿ��ʵ�ʵı�Ȩ����ΪINF,����Ϊ1(ÿ������Ҫ��λʱ��1ͨ��),��ÿ��������
//һ��ͨ��ʱ��С�ڵ���k������·���ӵĲ�������ǡ�þ��ǲ����ĳ������1,
//���ǿ��Խ����е�ĳ����ɾȥ,ʹ������·�Լ�������·��֧������·��ʹ�ò��ܴ�1�ߵ�n.
//֮����spfa��������·�˳�ѭ���������ǵ�ǰ����·����Ȩֵ��>k,����Ϊ����������������·
//Ȩֵ��ֻ��Խ��Խ��,�϶����Ǵ���k��,��˲��ٿ���ֱ���˳�ѭ��.
//1��n������������,��Ϊ���ܻ��ж�����1����n�����·
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 5000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<1];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    //����ǰ����·���·����k,��������������·���·Ҳһ������k,ֻ��Խ��Խ��,
    //��Ϊ�����ڲ��ϼ���,�ɹ�ѡ��ı�Ҳ��Խ��,��spfa������һ���ǵ�ǰ���ú���С������·,����ֻ��Խ��Խ��
    return dis[ed]<=k;
}

int mcmf(){
    int sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];//ÿ������·����С��������һ����ĳ�������ʣ������,��Ч��ɾ��ĳ������ʹ��1��n����ͨ
    }
    return sum;
}

void init(){
    cnt=0;
    st=1,ed=n;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v;
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=2;i<n;i++)
            addEdge(i,i+n,1,0);
        addEdge(1,1+n,INF,0);//1��n������������,��Ϊ���ܻ��ж�����1����n�����·
        addEdge(n,n+n,INF,0);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            addEdge(u+n,v,1,1);
        }
        printf("%d\n",mcmf());
    }
    return 0;
}
*/

/*
//ac 873ms ������������ ��ʱ�����
//��Ŀ��Ҫʹ�ﵽҪ��Ҫȥ���ߵ��������٣�Ҫ����1��N�ľ���Ҫ����K��
//��ôһ��Ҫ��ȡ1��N֮������·��Ȼ����ȥ�����·���е�һ���㣬
//�������·���䳤��Ȼ��������ȡ���·����ͬ���Ĳ�����ֱ�����·������K��
//�����˼·�У�����Ψһ��ȷ���ľ���ÿ��ȥ���ĵ�ľ����ź�һ��Ҫȥ����ĸ�����
//���ǿ���ö����ȣ��𲽼��ȥ���ĵ����ǿ���ö�����·���ϵĵ㣬�ݹ�ؽ������
//������������̽�ܲ����ҵ����н⣬ֻҪ���ҵ����н⣬��ô��ǰ��Ⱦ�����С��ȣ�
//��Ϊ����С����Ⱦ��Ҳ�����
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#define MAX 57

using namespace std;
bool inqueue[MAX];
bool okay[MAX];
int dis[MAX];
int pre[MAX];
int n,m,k;

struct
{
    int v , next;
}e[MAX*MAX<<2];

int head[MAX];
int cc;

void add ( int u , int v )
{
    e[cc].next = head[u];
    e[cc].v = v;
    head[u] = cc++;
}

void spfa ( int u )
{
    memset ( inqueue , 0 , sizeof ( inqueue) );
    memset ( dis , 0x3f , sizeof ( dis ) );
    inqueue[u] = true;
    queue<int> q;
    dis[u] = 0;
    q.push ( u );
    while ( !q.empty())
    {
        int temp = q.front();
        q.pop ();
        inqueue[u] = false;
        for ( int i = head[temp] ; i != -1 ; i = e[i].next )
        {
            int v = e[i].v;
            if ( inqueue[v]||okay[v] ) continue;
            if ( dis[v] > dis[temp] + 1 )
            {
                dis[v] = dis[temp] + 1;
                inqueue[v] = true;
                q.push ( v );
                pre[v] = temp;
            }
        }
    }
}

bool flag = false;
int path[MAX][MAX];

void dfs ( int size )
{
    spfa( 1 );
    if ( dis[n] > k )
    {
        flag = true;
        return;
    }
    if ( size == 0 ) return;
    int cnt = 0;
    for ( int i = n ; i != 1 ; i = pre[i] )
        path[size][cnt++] = i;
    for ( int i = 1 ; i < cnt ; i++ )
    {
        int index = path[size][i];
        if ( okay[index] ) continue;
        okay[index] = true;
        dfs ( size - 1 );
        okay[index] = false;
    }
}


int main ( )
{
    int u,v;
    while ( ~scanf ( "%d%d%d" , &n , &m , &k ), n+m+k )
    {
        cc = 0;
        memset ( head , -1  , sizeof ( head ) );
        for ( int i = 0 ; i < m ; i++ )
        {
            scanf ( "%d%d" , &u ,&v );
            add ( u , v );
        }
        flag = false;
        for ( int i = 0 ; i < n ; i++ )
        {
            dfs ( i );
            if ( flag )
            {
                printf ( "%d\n" , i );
                break;
            }
        }
    }
    return 0;
}
*/
