#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1500
#define M 3000000
#define INF 0x3f3f3f3f
using namespace std;
//ac 124ms dinic O(V^2*E) 此题边数远超点数,为稠密图
//参考题解:https://www.pianshen.com/article/216862946/
//EK 算法超时 O(V*E^2)
/*
题意:n个任务,m个机器,对于任务i,从si天开始处理,需要pi天才能处理完,
截止ei天,一台机器一次只能处理一个任务,而每个任务一次最多只能由一台
机器处理.但是,一个任务可以在不同的时间在不同的机器上中断和处理.
现在需要判断是否存在可行的时间安排能在规定时间内将所有任务处理完,
若能输出"Yes",否则输出"No".
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3572
思路:为一天以内只有m台机器可使用,显然需要将不同的任务安排在不同的机器上
并且合理分配每个任务执行的天,可以构造一个源点0,源点向每个任务i建0->i,容量
为pi的有向边,每个任务i向 任务的开始到结束日内的天j分别建边i->j+n,并且容量为1,
代表一个任务可安排在不同的天处理,并且该天内这个任务只能安排一次(容量为1),然后
每个天j+n向汇点ed建边,j+n->ed容量为m,代表该天内可供使用的机器数最多为m,ed为最大的
天数编号+n+1,显然这个网络每次求解的增广路最小残余容量都为1,代表安排某个任务再某天用
某个机器执行,而最大流ans就是完成尽可能多任务每个任务工作的天数总和,现在只要判断ans
是否等于所有任务工作的天数总和sum,等于就说明可以完成所有任务,不等于就说明不存在合理的
时间安排能完成所有任务.
*/
int cas,n,m,p,s,e,st,ed,sum,cnt,head[N],dis[N];
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
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
                flow-=incf;
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                res+=incf;
            }
            if(!flow)
                return res;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(){
    int ans=0;
    while(bfs(0))
        ans+=dfs(0,INF);
    return ans;
}

void init(){
    cas++;
    sum=ed=cnt=0;
    st=INF;
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);//n个任务,m个机器
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&p,&s,&e);//任务i需要执行p天,从s天开始,e天结束
            sum+=p;
            st=min(st,s);//st代表所有任务处理时间,开始天最小的编号
            ed=max(ed,e);//ed代表所有任务处理时间,开始天最大的编号
            addEdge(0,i,p);//源点->任务i 容量为p
            addEdge(i,0,0);
            for(int j=s;j<=e;j++){
                addEdge(i,j+n,1);//每个任务i建s~e内每一天容量为1的边
                addEdge(j+n,i,0);
            }
        }
        ed+=n+1;//汇点编号是最大的天编号+n+1
        for(int i=st;i<=ed;i++){//所有可能天建到汇点 容量为m的边,因为每一天只有m台机器能工作
            addEdge(i+n,ed,m);
            addEdge(ed,i+n,0);
        }
        printf("Case %d: %s\n",cas,max_flow() == sum?"Yes":"No");
        printf("\n");
    }
    return 0;
}

/*
//ac 93ms dinic 当前弧优化
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1500
#define M 3000000
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,p,s,e,st,ed,sum,cnt,head[N],cur[N],dis[N];
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
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
    for(int i=cur[u];i!=-1;i=edge[i].next){
        cur[u]=i;
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                flow-=incf;
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                res+=incf;
            }
            if(!flow)
                return res;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(){
    int ans=0;
    while(bfs(0)){
        for(int i=0;i<ed;i++) cur[i]=head[i];
        ans+=dfs(0,INF);
    }
    return ans;
}

void init(){
    cas++;
    sum=ed=cnt=0;
    st=INF;
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&p,&s,&e);
            sum+=p;
            st=min(st,s);
            ed=max(ed,e);
            addEdge(0,i,p);
            addEdge(i,0,0);
            for(int j=s;j<=e;j++){
                addEdge(i,j+n,1);
                addEdge(j+n,i,0);
            }
        }
        ed+=n+1;
        for(int i=st;i<=ed;i++){
            addEdge(i+n,ed,m);
            addEdge(ed,i+n,0);
        }
        printf("Case %d: %s\n",cas,max_flow() == sum?"Yes":"No");
        printf("\n");
    }
    return 0;
}
*/
