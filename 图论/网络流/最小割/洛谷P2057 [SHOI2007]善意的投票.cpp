#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 320
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;
//ac 24ms dinic 最小割=最大流
/*
题意:幼儿园里有n个小朋友打算通过投票来决定睡不睡午觉.
对他们来说,这个问题并不是很重要,于是他们决定发扬谦让精神.
虽然每个人都有自己的主见,但是为了照顾一下自己朋友的想法,
他们也可以投和自己本来意愿相反的票.我们定义一次投票的冲突数
为好朋友之间发生冲突的总数加上和所有和自己本来意愿发生冲突的人数.
我们的问题就是,每位小朋友应该怎样投票,才能使冲突数最小?
链接:https://www.luogu.com.cn/problem/P2057
思路:一个小朋友投票决定睡不睡觉,只能有一种选择即:同意睡觉或反对睡觉.
而且对于好朋友之间的观点应保持一致。构建图论模型,源点s,汇点t,s->i(flow=1)表示
i同学同意睡觉,j->t(flow=1)表示j同学反对睡觉,对于i和j是好朋友,则构建i->j j->i 即
双向边,双向边保证i和j都能要求对方和自己同立场,因为不清楚i、j哪个是从源点出发,
需要保证网络s到t的连通性.那么假设对于i同学同意,j同学反对,并且他们是好朋友,构建的
网络有条从源通往汇点的边s->i->j->t,i是同意的,j是反对,根据i->j j->i两个朋友之间都要
求对方认同自己的观点,即是矛盾的,那么可以选择割掉s->i或j->t来使得i认同j的观点或j认同
i的观点,或者割掉i->j使其之间不存在朋友关系,则他们之间的观点可不同,仔细想想这不就是
找割集,最小割使得分离源和汇的目的吗.
对于题目两种矛盾冲突1.好朋友之间发生冲突的总数2.所有和自己本来意愿发生冲突的人数
2冲突实际上就是由1冲突所导致的,如果小朋友之间不存在好朋友关系,即使它们投票意愿不同,
也不会存在矛盾关系,因为不会违背好朋友的意愿,也不会为了和好朋友的立场保持一致而违背
了自身的意愿,因此求1+2的矛盾冲突总和 就是求解解决矛盾所需要切除的最小边数,即求解割边
的数量,那么将每条边的流量设置为1 求解最小割的容量和就是割边的数量,可以直接转化为求解
最大流.

eg:
实际对于i同意,j不同意,k同意,然后i-j为朋友,j-k为朋友,如果更改k的意愿还需更改i的意愿,
这样矛盾数就为2,但是如果更改j的意愿,就没有矛盾了,矛盾数为1.

注意:一条从A——>B的边,表示A要求B同它同立场
那么为什么好朋友之间需要连双向边是不是就解决了?
好朋友互相要求对方同自己一个立场
关于这个问题,我们还可以多角度思考:
这里我们可以倒过来想:倘若好朋友之间是单向边?那么本身图就是走不通的,也就不存在冲突了,显然不符
也可以从对称性的角度来看:A与B的朋友关系是相对的,单向边显然不符合对称性.
*/
struct node{
    int to,next,f;
}edge[M<<1];
int head[N],cnt,vis[N],d[N];

void addEdge(int from,int to,int f){
    edge[cnt]=(node){to,head[from],f};
    head[from]=cnt++;
    edge[cnt]=(node){from,head[to],0};
    head[to]=cnt++;
}

void init(int s){
    memset(d,-1,sizeof(d));//源点设置0,其余点设置-1,判断用dis[v]==-1,可避免使用!dis[v]使得源点再次入队
    d[s]=0;
}

bool bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].f>0 && d[v]==-1){
                d[v]=d[u]+1;
                if(v == t) return true;
                Q.push(v);
            }
        }
    }
    return false;
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int v,incf,res=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(edge[i].f>0 && d[v]==d[u]+1){
            incf=dfs(v,t,min(flow,edge[i].f));
            if(incf>0){
                edge[i].f-=incf;
                edge[i^1].f+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0) return res;
        }
    }
    if(res == 0) d[u]=-1;
    return res;
}

int maxFlow(int s,int t){
    int sum=0;
    while(bfs(s,t))
        sum+=dfs(s,t,INF);
    return sum;
}

int main(){
    int n,m,p,s,t,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&p);
        if(p) addEdge(s,i,1);//i同学同意睡觉 容量设为1 方便求解数量
        else addEdge(i,t,1);//i同学反对睡觉
    }
    while(m--){
        scanf("%d%d",&u,&v);
        //u、v之间互为朋友关系,因为u和v不确定谁是靠近源点s发出的点,
        //因此需要设置正反两条边的初始容量都为1,这样才能保证网络流s到达t不存在初始容量为0的增广路,才能保证图的连通性.
        addEdge(u,v,1);//u->v代表u要求v和他同立场
        addEdge(v,u,1);//v->u代表v要求u和他同立场
    }
    printf("%d",maxFlow(s,t));//求解割边个数 根据最大流-最小割定理,转化为求解最大流
    return 0;
}

/*
//ac 25ms dinic 当前弧优化
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 320
#define M 100000//这题目的数据范围和题目描述不符,实际地上界达到了百万,2百万即可,按照题目描述,卡死10W感觉就可
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,next,f;
}edge[M<<1];
int n,m,head[N],cnt,vis[N],d[N],cur[N];

void addEdge(int from,int to,int f){
    edge[cnt]=(node){to,head[from],f};
    head[from]=cnt++;
    edge[cnt]=(node){from,head[to],0};
    head[to]=cnt++;
}

void init(int s){
    memset(d,-1,sizeof(d));//源点设置0,其余点设置-1,判断用dis[v]==-1,可避免使用!dis[v]使得源点再次入队
    d[s]=0;
}

bool bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].f>0 && d[v]==-1){
                d[v]=d[u]+1;
                if(v == t) return true;
                Q.push(v);
            }
        }
    }
    return false;
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int v,incf,res=0;
    for(int i=cur[u];i!=-1;i=edge[i].next){
        cur[u]=i;
        v=edge[i].to;
        if(edge[i].f>0 && d[v]==d[u]+1){
            incf=dfs(v,t,min(flow,edge[i].f));
            if(incf>0){
                edge[i].f-=incf;
                edge[i^1].f+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0) return res;
        }
    }
    if(res == 0) d[u]=-1;
    return res;
}

int maxFlow(int s,int t){
    int sum=0;
    while(bfs(s,t)){
        for(int i=1;i<=n+2;i++)
            cur[i]=head[i];
        sum+=dfs(s,t,INF);
    }
    return sum;
}

int main(){
    int p,s,t,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&p);
        if(p) addEdge(s,i,1);
        else addEdge(i,t,1);
    }
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v,1);
        addEdge(v,u,1);
    }
    printf("%d",maxFlow(s,t));
    return 0;
}
*/

/*
//ac 26ms EK算法 bfs搜索增广路
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 3100
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],pre[N],incf[N],sum;
struct Edge{
    int to,next,cf;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
}

void init(int s){
    memset(pre,-1,sizeof(pre));
    incf[s]=INF;
}

int bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        if(u == t) return 1;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && pre[v] == -1){
                incf[v]=min(incf[u],edge[i].cf);
                pre[v]=i;
                Q.push(v);
            }
        }
    }
    return 0;
}

int max_flow(int s,int t){
    int ans=0,v;
    while(bfs(s,t)){
        v=t;
        while(v!=s){
            edge[pre[v]].cf-=incf[t];
            edge[pre[v]^1].cf+=incf[t];
            v=edge[pre[v]^1].to;
        }
        ans+=incf[t];
    }
    return ans;
}

int main(){
    int p,s,t,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&p);
        if(p){
            addEdge(s,i,1);//i同学同意睡觉 容量设为1 方便求解数量
            addEdge(i,s,0);
        }
        else{
            addEdge(i,t,1);//i同学反对睡觉
            addEdge(t,i,0);
        }
    }
    while(m--){
        scanf("%d%d",&u,&v);
        //u、v之间互为朋友关系,因为u和v不确定谁是靠近源点s发出的点,
        //因此需要设置正反两条边的初始容量都为1,这样才能保证网络流s到达t不存在初始容量为0的增广路
        addEdge(u,v,1);
        addEdge(v,u,1);
    }
    printf("%d",max_flow(s,t));//求解割边个数 根据最大流-最小割定理,转化为求解最大流
    return 0;
}
*/
