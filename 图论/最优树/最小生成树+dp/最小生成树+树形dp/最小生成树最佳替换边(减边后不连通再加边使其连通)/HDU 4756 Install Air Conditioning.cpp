#include<cstdio>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 1e18
using namespace std;
//prim 514ms
//����Ϊ����ͼ ��kruskal ��TLE
//������С�������ʹ���С������������������
/*
����:1������վ(���Ϊ1),n-1������,����Ҫ������ͷ���վ���������,�������kԪ/��,
ʹ���໥��ͨ,����������2������䲻�������µĸ߸��ɵ���,���������������������,
���ڵ������Ҫ׼������Ǯ����ʹ������ͷ���վ�໥��ͨ.
ע�ⷢ��վ������֮����һ������������µ�.
������:
n�������ȫͼ,���mst��ɾ��mst��һ���ߺ��mstȨֵ�͵����ֵ,
��1�Ž�������ı߲���ɾ��.

����:http://acm.hdu.edu.cn/showproblem.php?pid=4756
˼·:��Ϊ����������������᲻������߸��ɵ���,����Ҫö��ɾ��������������������.
�������ɾ��ĳ���ߺ���С��������Ȩֵ�͵����ֵ,����ԭͼ����ȫͼ,�������ö��
ɾ��ԭͼ�е�ÿ����,n<=1000 O(n^2*nlog(n))�϶�TLE,����������mst,����mst�Ļ�����,
ɾ��mst�еı�,�����С������,��������ֵ,ʵ�ʾ�������ڲ�ѡ��ԭ��ĳ���ߵ�ǰ������С�����������ֵ.
����ɾ��ĳ���ߺ����С������ԭ��mst��Ȩֵ��-ɾ����Ȩ+(�����2����ͨ��������������С��Ȩ)���,
�����2����ͨ��������������С��Ȩ����O(n^2)����dp���.
*/

int n,k,vis[N],cnt,head[N];
double mp[N][N],dis[N],dp[N][N],sum,ans;

struct state{
    int u,v;
    double w;
    state(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const state &x)const{
        return w>x.w;
    }
};

struct Node{
    int from,to,next;
    double w;
}edge[N<<1];

void addEdge(int from,int to,double w){
    edge[cnt]=(Node){from,to,head[from],w};
    head[from]=cnt++;
}

struct Point{
    double x,y;
}point[N];

double getDis(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
}

void prim(int s){
    init(s);
    priority_queue<state>Q;
    Q.push(state(s,s,0));
    int u,num=0;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        if(dis[u]){
            addEdge(tmp.u,tmp.v,tmp.w);
            addEdge(tmp.v,tmp.u,tmp.w);
        }
        num++;
        sum+=tmp.w;
        if(num == n) return;
        for(int v=1;v<=n;v++){
            if(!vis[v] && mp[u][v]<dis[v]){
                dis[v]=mp[u][v];
                Q.push(state(u,v,dis[v]));
            }
        }
    }
}

double dfs1(int u,int fa,int rt){
    double res=INF;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        double tmp=dfs1(v,u,rt);
        res=min(res,tmp);
        dp[u][v]=dp[v][u]=min(dp[u][v],tmp);
    }
    if(rt!=fa) res=min(res,mp[rt][u]);
    return res;
}

void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(u!=1)//�ͷ���վ(1�Žڵ�)�����ı߲���ɾ
            ans=max(ans,sum-edge[i].w+dp[u][v]);
        dfs2(v,u);
    }
}

int main(){
    int T;
    double w;
    scanf("%d",&T);
    while(T--){
        cnt=sum=0;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                dp[i][j]=dp[j][i]=INF;
        for(int i=1;i<=n;i++)
            scanf("%lf%lf",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                mp[i][j]=mp[j][i]=w;
            }
        }
        prim(1);
        for(int i=1;i<=n;i++)
            dfs1(i,-1,i);
        ans=sum;//�п��ܹ������mst���еı߶��ͷ���վ(1�ڵ�)����,��ʱ�޷�ɾ��,��󻨷Ѿ���ԭmst�ķ���
        dfs2(1,-1);
        printf("%.2f\n",ans*k);
    }
    return 0;
}

/*
//��С�������ʹ���С������������
//https://www.iteye.com/blog/xxx0624-2186837
//˼·��̰�ģ����Yamidie��˼·��������
//�ֱ������С�������ʹ���С��������������������������С������
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
using namespace std;
const int maxn = 1015;
const int maxm = maxn*maxn;
const int inf1 = 0x3f3f3f3f;
const double inf2 = 9999999999;

struct Point {
    double x,y;
}pnt[ maxn ];
struct Edge{
    int u,v;
    double val;
    int id;
}edge[ maxn<<1 ];
int cnt_edge;
double mat[ maxn ][ maxn ];
double dis[ maxn ];
bool vis[ maxn ];
int pre[ maxn ];

double LenPrim1;
double LenPrim2;

int fa[ maxn ],rank[ maxn ];

int find( int x ){
    if( x==fa[x] ) return x;
    else return fa[ x ] = find( fa[x] );
}

void init( int n ){
    for( int i=0;i<n;i++ ){
        fa[ i ] = i;
        rank[ i ] = 1;
    }
    return ;
}

double dist( int i,int j ){
    return sqrt( (pnt[i].x-pnt[j].x)*(pnt[i].x-pnt[j].x)+(pnt[i].y-pnt[j].y)*(pnt[i].y-pnt[j].y) );
}

int cmp( Edge a,Edge b ){
    return a.val<b.val;
}

void GetMap( int n ){
    for( int i=0;i<n;i++ )
        for( int j=0;j<n;j++ ){
            mat[i][j] = dist( i,j );
            //printf("mat[%d][%d]=%.3lf\n",i,j,mat[i][j]);
        }
    return ;
}

double prim( int n,int Belong ){
    for( int i=0;i<n;i++ ){
        dis[ i ] = mat[0][i];
        vis[ i ] = false;
        pre[ i ] = 0;
    }
    vis[0] = true;
    //if( Belong==2 ){
    //    for( int i=0;i<n;i++ )for( int j=0;j<n;j++ )
            //printf("mat[%d][%d]=%.3lf\n",i,j,mat[i][j]);
    //}
    double ans = 0;
    for( int i=0;i<n;i++ ){
        int id = -1;
        double M = inf2;
        for( int j=0;j<n;j++ ){
            if( !vis[j] && M>dis[j] ){
                M = dis[j];
                id = j;
            }
        }
        if( id==-1 ) break;
        vis[ id ] = true;
        ans += M;
        edge[ cnt_edge ].u = pre[ id ];
        edge[ cnt_edge ].v = id;
        edge[ cnt_edge ].id = Belong;
        edge[ cnt_edge ].val = mat[ id ][ pre[id] ];
        //printf("u = %d,v = %d\n",edge[cnt_edge].u,edge[cnt_edge].v);
        cnt_edge ++ ;
        for( int j=0;j<n;j++ ){
            if( !vis[j] && dis[j]>mat[id][j] ){
                dis[j] = mat[id][j];
                pre[ j ] = id;
            }
        }
    }
    return ans;
}

void Deal( int n ){
    for( int i=0;i<cnt_edge;i++ ){
        mat[ edge[i].u ][ edge[i].v ] = inf2;
        mat[ edge[i].v ][ edge[i].u ] = inf2;
    }
}

double Kruskal( int n,int id ){
    double ans = 0;
    init( n );
    int cnt = 0;
    for( int i=0;i<cnt_edge;i++ ){
        if( i==id ) continue;
        int fx = find( edge[i].u );
        int fy = find( edge[i].v );
        if( fx!=fy ){
            if( rank[ fx ]<rank[ fy ] ){
                rank[ fy ] += rank[ fx ];
                fa[ fx ] = fy;
            }
            else {
                rank[ fx ] += rank[ fy ];
                fa[ fy ] = fx;
            }
            cnt ++ ;
            ans += edge[i].val;
            if( cnt==n-1 ) break;
        }
       }
       return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    while( T-- ){
        int n;
        double k;
        scanf("%d%lf",&n,&k);
        for( int i=0;i<n;i++ )
            scanf("%lf%lf",&pnt[i].x,&pnt[i].y);
        GetMap( n );
        cnt_edge = 0;
        LenPrim1 = prim( n,1 );
        Deal( n );
        LenPrim2 = prim( n,2 );
        double ans = LenPrim1;
        double temp_ans = 0;
        sort( edge,edge+cnt_edge,cmp );
        //printf("cnt_edge = %d\n",cnt_edge);
        for( int i=0;i<cnt_edge;i++ ){
            if( edge[i].id==1 && edge[i].u!=0 && edge[i].v!=0 ){
                temp_ans = Kruskal( n,i );
                if( temp_ans>ans )
                    ans = temp_ans;
            }
        }
        printf("%.2lf\n",ans*k);
    }
    return 0;
}
*/
