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
