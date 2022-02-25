#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 300
#define INF 0x3f3f3f3f
using namespace std;
//ac 94ms floyd+二分距离(最大值最小化)+最大流验证
/*
题意摘自网上
题意:k个机器,每个机器最多服务m头牛.c头牛,每个牛需要1台机器来服务.
告诉你牛与机器每个之间的直接距离,问让所有的牛都被服务的情况下,
使走的最远的牛的距离最短,求这个距离.
输入的矩阵是(k+c)*(k+c),代表机器到奶牛之间的距离,和奶牛到机器之间
的距离,机器编号1~k,奶牛编号k+1~k+c,若机器奶牛输入为0,代表机器和奶牛
之间不可通行.
链接:http://poj.org/problem?id=2112
思路:显然是求奶牛与机器间距离使其最大值最小化,那么可以考虑二分枚举最大距离,
构建网络跑最大流验证,源点0,汇点k+c+1,源点向每个机器1~k建容量为m的边,每个机器
向每个可通行得到奶牛(距离不为INF)建容量为1的边,每个奶牛想汇点建容量为1的边,
跑最大流判断结果是否为c奶牛个数,若是,将最远距离变小,若不是,将最远距离变大.
*/
int k,c,m,n,st,ed,cnt,head[N],dis[N],vis[N],mp[N][N];
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

int max_flow(int mid){
    int sum=0;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=k;i++)
        addEdge(st,i,m);
    for(int i=k+1;i<=n;i++)
        addEdge(i,ed,1);
    for(int i=1;i<=k;i++){
        for(int j=k+1;j<=n;j++){
            if(mp[i][j] != INF && mp[i][j]<=mid)//若机器i和奶牛j之间距离不大于mid,则构建链接关系
                addEdge(i,j,1);
        }
    }
    while(bfs(st))
        sum+=dfs(st,INF);
    return sum == c;
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
    st=0,ed=k+c+1;
    n=k+c;
}

int main(){
    int l,r,mid;
    scanf("%d%d%d",&k,&c,&m);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mp[i][j]);
            if(i != j && !mp[i][j])
                mp[i][j]=INF;
        }
    }
    floyd();
    l=0,r=0;
    for(int i=1;i<=k;i++){
        for(int j=k+1;j<=n;j++){
            r=max(r,mp[i][j]);//求出最大距离的初始上界
        }
    }
    while(l<r){
        mid=(l+r)/2;
        if(max_flow(mid))
            r=mid;
        else
            l=mid+1;
    }
    printf("%d",r);
    return 0;
}

/*
//ac 125ms 二分最大距离+多重匹配(匈牙利)
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 250
#define INF 0x3f3f3f3f
using namespace std;

int k,c,m,n,cnt,head[N],link[50][20],vis[50],num[50],mp[N][N];
struct Edge{
    int to,next;
}edge[N*30];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int clock){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(num[v]<m){
            link[v][++num[v]]=u;
            return 1;
        }
        else{
            for(int i=1;i<=num[v];i++){
                if(dfs(link[v][i],clock)){
                    link[v][i]=u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void init(int mid){
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(num,0,sizeof(num));
    memset(vis,0,sizeof(vis));
    for(int i=k+1;i<=n;i++){
        for(int j=1;j<=k;j++){
            if(mp[i][j] !=INF && mp[i][j]<=mid)//若奶牛i距离挤奶机j距离不大于mid,则构建可到达关系
                addEdge(i,j);
        }
    }
}

int hungary(int mid){
    int sum=0;
    init(mid);
    for(int i=k+1;i<=n;i++)
        if(dfs(i,i)) sum++;
    return sum == c;
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

int main(){
    int l,r,mid;
    scanf("%d%d%d",&k,&c,&m);
    n=k+c;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mp[i][j]);
            if(i != j && !mp[i][j])
                mp[i][j]=INF;
        }
    }
    floyd();
    l=0,r=0;
    for(int i=k+1;i<=n;i++){
        for(int j=1;j<=k;j++)
            r=max(r,mp[i][j]);//求出最大距离的初始上界
    }
    while(l<r){
        mid=(l+r)/2;
        if(hungary(mid))
            r=mid;
        else
            l=mid+1;
    }
    printf("%d",r);
    return 0;
}
*/
