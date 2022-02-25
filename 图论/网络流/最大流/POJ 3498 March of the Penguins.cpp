#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 300
#define M 200000
#define INF 0x3f3f3f3f
using namespace std;
//ac 625ms dinic ö�ٻ��
/*
����:��n�鸡��,ÿ���������Ծ����d,ÿ�鸡������һ�����������,
ÿ�鸡�����ܴ���鸡�����������������һ������,�����������ȫ��
��Ծ���е�ĳ�鸡���ı��,�������������ĸ���,�����-1.
ע��:��ĿҪ������ĸ�������Ǵ�0��ʼ,���Ա��Ҫ��1.
����:http://poj.org/problem?id=3498
˼·:ͬHDU 2732,ÿ��������һ��������������,��ͬ����ÿ�鸡���Ͽ���
�ж�ֻ���.����Դ��0,��Դ�㵽ÿ������i����Ϊ�ø�������������.
ÿ������i���Ϊ���i�ͳ���i+n,��i->i+n,����Ϊ��鸡��������������
��������,ɨ��ÿ����i�������������d���ڵĵ�j,����i+n->j,j+n->i,����
INF,֮��ö��ÿ������i��Ϊ��������������,�ж�������Ƿ�����������
����,������,������ø������-1,�������������ĸ��������-1.
*/
int n,m,cnt,head[N],ed,dis[N],sum;
double d;
struct Node{
    double x,y;
    int num,cnt;
}node[N];
struct Edge{
    int to,next,cf;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int getDis(double x1,double y1,double x2,double y2){
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<=d*d;
}

int bfs(int s,int ed){
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

int dfs(int u,int ed,int flow){
    if(u == ed) return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,ed,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow) break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(int ed){
    int ans=0;
    while(bfs(0,ed))
        ans+=dfs(0,ed,INF);
    return ans;
}

void init(){
    sum=cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
            if(node[i].num){
                sum+=node[i].num;
                addEdge(0,i,node[i].num);
            }
            addEdge(i,i+n,node[i].cnt);//i��� i+n����,����Ϊ����������������
            for(int j=i-1;j>=1;j--){
                if(getDis(node[i].x,node[i].y,node[j].x,node[j].y)){//�ж�i j�����������Ƿ�С�ڵ���d,����
                    addEdge(i+n,j,INF);//i�ĳ�������j ����ΪINF
                    addEdge(j+n,i,INF);//j�ĳ�������i ����ΪINF
                }
            }
        }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%lf",&n,&d);
        for(int i=1;i<=n;i++)//����ÿ������������
            scanf("%lf%lf%d%d",&node[i].x,&node[i].y,&node[i].num,&node[i].cnt);
        int flag=1;
        for(int i=1;i<=n;i++){//ö��i����Ϊ���,�ж��Ƿ�������춼������i��
            init();//��ʼ������,����
            if(sum == max_flow(i)){
                if(flag){
                    printf("%d",i-1);
                    flag=0;
                }
                else
                    printf(" %d",i-1);
            }
        }
        if(flag) printf("-1\n");
        else printf("\n");
    }
    return 0;
}

/*
//��һ��dinic �����ж� e.cap>e.flow,�е�û����
//ö�ٻ��+��㣬����֮��ľ���>=d�Ľ��ߣ�Ȼ�������
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
const int maxn=209;
const int inf=0x7fffffff;
double mp[maxn][maxn];
struct Edge{
    int from,to,cap,flow;
    Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};
struct Dinic{
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>g[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];
    void Init(int n){
        this->n=n;
        for(int i=0;i<n;i++) g[i].clear();
        edges.clear();
    }
    void Addedge(int from,int to,int cap){
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));//����
        m=edges.size();
        g[from].push_back(m-2);
        g[to].push_back(m-1);
    }
    bool Bfs(){
        memset(vis,0,sizeof(vis));
        queue<int>q;
        q.push(s);
        d[s]=0;
        vis[s]=1;
        while(!q.empty()){
            int x=q.front();q.pop();
            for(int i=0;i<(int)g[x].size();i++){
                Edge &e=edges[g[x][i]];
                if(!vis[e.to]&&e.cap>e.flow){
                    vis[e.to]=1;
                    d[e.to]=d[x]+1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int Dfs(int x,int a){
        if(x==t||a==0) return a;
        int flow=0,f;
        for(int&i=cur[x];i<(int)g[x].size();i++){
            Edge &e=edges[g[x][i]];
            if(d[x]+1==d[e.to]&&(f=Dfs(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f;
                edges[g[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }
    int Maxflow(int s,int t){
        this->s=s;this->t=t;
        int flow=0;
        while(Bfs()){
            memset(cur,0,sizeof(cur));
            flow+=Dfs(s,inf);
        }
        return flow;
    }
}dc;
int main()
{
    int n,t,peng[maxn],tim[maxn];
    double d,x[maxn],y[maxn];
    scanf("%d",&t);
    while(t--){
        scanf("%d%lf",&n,&d);
        int sum=0;
        for(int i=1;i<=n;i++){
            scanf("%lf%lf%d%d",&x[i],&y[i],&peng[i],&tim[i]);
            sum+=peng[i];
            for(int j=1;j<=i;j++){
                double dis=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                mp[i][j]=mp[j][i]=dis;
            }
        }
        int ans[102],cnt=0;
        for(int i=1;i<=n;i++){
            dc.Init(2*n+1);
            for(int j=1;j<=n;j++){
                if(j==i) continue;
                dc.Addedge(j,j+n,tim[j]);
                dc.Addedge(0,j,peng[j]);
                for(int k=1;k<=n;k++) if(mp[j][k]<=d)
                    dc.Addedge(j+n,k,inf);
            }
            if(dc.Maxflow(0,i)==sum-peng[i]) ans[cnt++]=i-1;
        }
        if(cnt==0) printf("-1\n");
        else{
            for(int i=0;i<cnt-1;i++) printf("%d ",ans[i]);
            printf("%d\n",ans[cnt-1]);
        }
    }
    return 0;
}
*/
