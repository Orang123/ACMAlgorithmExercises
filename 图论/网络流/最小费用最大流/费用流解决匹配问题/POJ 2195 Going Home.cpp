#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 10100
#define INF 0x3f3f3f3f
using namespace std;
//ac 94ms ������ Դ��->����->����->���
/*
����:һ��n*n����������n���˺�n�䷿��,��������'m'��ʾ,
������'H'��ʾ,ÿ���˿���ˮƽ��ֱ��һ����λ���뵽���ڵ�
��,��ÿ��һ��λ������Ҫ֧��1Ԫ,ֱ���˽��뷿��,��ÿ������
ֻ������һ����,�����ʽ���n���˶��ͽ�������Ҫ����С����.
n*n�����������n����,n�䷿.
����:http://poj.org/problem?id=2195
˼·:�ɿ��Ƿ�����,ͳ�����˸���num1,���Ӹ���num2,Դ��=0,���=num1+num2+1.
Դ�������˽�����Ϊ1,����Ϊ0�ı�,ÿ���������������˽�����Ϊ1,����Ϊ�����پ���
�ı�,���з������㽨����Ϊ1,����Ϊ0�ı�,�ܷ��������ɵõ���С����.
*/
int st,ed,cnt,head[N];
int n,m,dis[N],incf[N],pre[N],vis[N],num1,num2;
char mp[110][110];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

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
                incf[v]=min(incf[u],edge[i].cf);
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

int mcmf(){
    int sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed]*dis[ed];
    }
    return sum;
}

void init(){
    num1=num2=cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'm') node1[++num1]=Node(i,j);
                else if(mp[i][j] == 'H') node2[++num2]=Node(i,j);
            }
        }
        st=0,ed=num1+num2+1;
        for(int i=1;i<=num1;i++){
            addEdge(st,i,1,0);
            addEdge(i+num1,ed,1,0);
            for(int j=1;j<=num2;j++){
                int w=abs(node1[i].x-node2[j].x)+abs(node1[i].y-node2[j].y);
                addEdge(i,j+num1,1,w);
            }
        }
        printf("%d\n",mcmf());
    }
    return 0;
}

/*
//ac 16ms dinic ������ Դ��->����->����->���
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 10100
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,m,dis[N],incf[N],pre[N],vis[N],num1,num2;
char mp[110][110];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    memset(vis,0,sizeof(vis));
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
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return dis[ed] != INF;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    vis[u]=1;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v] && edge[i].cf>0 && dis[v] == dis[u]+edge[i].w){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
                if(!flow)
                    break;
            }
        }
    }
    return res;
}

int mcmf(){
    int sum=0,incf;
    while(spfa(st)){
        incf=dfs(st,INF);
        sum+=incf*dis[ed];
    }
    return sum;
}

void init(){
    num1=num2=cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'm') node1[++num1]=Node(i,j);
                else if(mp[i][j] == 'H') node2[++num2]=Node(i,j);
            }
        }
        st=0,ed=num1+num2+1;
        for(int i=1;i<=num1;i++){
            addEdge(st,i,1,0);
            addEdge(i+num1,ed,1,0);
            for(int j=1;j<=num2;j++){
                int w=abs(node1[i].x-node2[j].x)+abs(node1[i].y-node2[j].y);
                addEdge(i,j+num1,1,w);
            }
        }
        printf("%d\n",mcmf());
    }
    return 0;
}
*/

/*
//ac 0ms KM �㷨 slack�����ɳ��Ż�
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,num,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d,slack[N];
vector<pair<int,int> > node1,node2;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=num;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

int KM(){
    for(int i=1;i<=num;i++){
        lx[i]=-INF;//��Ϊ��ȨΪ��,̰��ѡ�����ֵ��С�ı�Ȩ,��ô��ʼ��Ϊ��ֵ ��С��-INF
        ly[i]=0;
        for(int j=1;j<=num;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=num;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=num;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            for(int j=1;j<=num;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
                else slack[j]-=d;//ʵ��û��slack[j]-=d�������Ҳ��0ms ac
            }
        }
    }
    int ans=0;
    for(int i=1;i<=num;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
    node1.clear();
    node2.clear();
}

int main(){
    char x;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == 'm')
                    node1.push_back(make_pair(i,j));//��¼�˵�����
                else if(x == 'H')
                    node2.push_back(make_pair(i,j));//��¼���ӵ�����
            }
        }
        num=node1.size();
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++)//ע������node�ı���Ǵ�0��ʼ,������mp���Ŵ�1��ʼ
                //��i�ߵ�����j�Ļ���Ϊ���뷿�ӵĺ��ݾ���� Ȩֵȡ��
                mp[i+1][j+1]=-1*(abs(node1[i].first-node2[j].first)+abs(node1[i].second-node2[j].second));
        }
        printf("%d\n",-1*KM());//���ʱ��ȡ�� ��Ϊ��ֵ
    }
    return 0;
}
*/
