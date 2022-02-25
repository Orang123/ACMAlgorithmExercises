//ac 0ms dfs每次搜索一条增广路 邻接矩阵存边
//但每次搜索增广路不能保证该增广路时最短的,也就是最终所有增广路组合,
//整体路径长度总和是不确定因素,可能会很长,但是dfs刚开始能快速找到一条增广路
//随着路径中边的残余容量不断减少为0,后续搜索增广路,也会重复搜索无意义的路径,效率就会变低.
//整体搜索效率是不如bfs的
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;
/*
题意:m个池塘,n条水渠,每条水渠水的流向只能是一个方向,
每条水渠有个水流的速率,求水渠中从1点流向m点(溪流)的水
流的最大速率.
释义:m个点,n条有向边的网络,每条边有一定容量,求解1到m的最大流.
注意:输入会有重复边,即1->2 20 1->2 30,这样1->2实际容量为30,
因此要累加容量.
链接:http://poj.org/problem?id=1273
思路:EK变种算法dfs搜索增广路求解最大流模板.
*/
int net[N][N],n,m;
bool vis[N];

//一次dfs只搜索一条增广路
int dfs(int s,int flow){
    if(s == m) return flow;//搜索到汇点t就返回
    int incf;
    for(int i=1;i<=m;i++){
        if(!vis[i] && net[s][i]>0){
            //vis[i]标记已访问避免之前所增广过的路径产生的反向弧,又从i点连边dfs进入s点,
            //s点又进入i点的dfs,会产生环导致死循环
            vis[i]=true;//一条增广路 一个点只会访问一次
            incf=dfs(i,min(net[s][i],flow));//记录增广路上最小的残余容量
            if(incf){//回溯时更新 增广路上边的残余容量
                net[s][i]-=incf;//正向边容量减少incf
                net[i][s]+=incf;//反向边容量增加incf
                return incf;
            }
        }
    }
    return 0;//没有搜索到增广路
}

int maxFlow(){
    int sum=0,tmp;
    while(1){
        memset(vis,false,sizeof(vis));
        vis[1]=true;//dfs时下界从2开始这里就无需标记源点1已访问
        tmp=dfs(1,INF);//flow 初始化为最大
        if(tmp) sum+=tmp;//最大流累加当前增广路最小残余容量
        else break;//返回0没有搜索到增广路
    }
    return sum;
}

int main(){
    int x,y,cap;
    while(scanf("%d %d",&n,&m)!=EOF){
        memset(net,0,sizeof(net));
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&x,&y,&cap);
            net[x][y]+=cap;
        }
        printf("%d\n",maxFlow());
    }
    return 0;
}

/*
//ac 0ms dfs每次搜索一条增广路 链式前向星存边
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],vis[N];
struct Edge{
    int to,next,cf;
}edge[N<<1];//因为要存反向边,所以边数*2

void addEdge(int from,int to,int cf){
    edge[cnt].to=to;
    edge[cnt].cf+=cf;//有重复边,要累加容量,不累加也能ac 不知啥原因
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

//一次dfs只搜索一条增广路
int dfs(int u,int flow){
    if(u == m) return flow;//搜索到汇点t就返回
    int incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v] && edge[i].cf>0){
            //vis[i]标记已访问避免之前所增广过的路径产生的反向弧,又从i点连边dfs进入s点,
            //s点又进入i点的dfs,会产生环导致死循环
            vis[v]=1;//一条增广路 一个点只会访问一次
            incf=dfs(v,min(edge[i].cf,flow));//记录增广路上最小的残余容量
            if(incf){//回溯时更新 增广路上边的残余容量
                edge[i].cf-=incf;//正向边容量减少incf
                edge[i^1].cf+=incf;//反向边容量增加incf
                return incf;
            }
        }
    }
    return 0;//没有搜索到增广路
}

int maxFlow(){
    int sum=0,tmp;
    while(1){
        memset(vis,0,sizeof(vis));
        vis[1]=1;//dfs时下界从2开始这里就无需标记源点1已访问
        tmp=dfs(1,INF);//flow 初始化为最大
        if(tmp) sum+=tmp;//最大流累加当前增广路最小残余容量
        else break;//返回0没有搜索到增广路
    }
    return sum;
}

int main(){
    int x,y,cap;
    while(scanf("%d %d",&n,&m)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        memset(edge,0,sizeof(edge));//因为要累加容量,所以容量cf初始化为0
        while(n--){
            scanf("%d %d %d",&x,&y,&cap);
            addEdge(x,y,cap);
            addEdge(y,x,0);
        }
        printf("%d\n",maxFlow());
    }
    return 0;
}
*/

/*
//ac 0ms dfs用stl栈stack模拟搜索增广路 邻接矩阵存边
#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;

int net[N][N],n,m,pre[N],incf[N];//in capacity flow 进入的容量流

int dfs(int s,int t){
    int p;
    stack<int> Q;
    incf[s]=INF;
    memset(pre,-1,sizeof(pre));
    Q.push(s);
    while(!Q.empty()){
        p=Q.top();
        Q.pop();
        for(int i=2;i<=m;i++){
            if(net[p][i]>0 && pre[i]==-1){//该边的残余容量要可用 该点之前必须未被访问 对于反向弧,无需标记vis 避免其又返回s点dfs,因为有pre[v]限制
                incf[i]=min(incf[p],net[p][i]);//记录该增广路中最小的残余容量
                pre[i]=p;//pre记录增广路中该点的前驱节点
                if(i==t)//到达汇点时构成一条可增广路,返回
                    return incf[t];
                Q.push(i);
            }
        }
    }
    return -1;
}


int maxFlow(){
    int sum=0,q;
    while(dfs(1,m)!=-1){
        q=m;
        while(q!=1){
            net[pre[q]][q]-=incf[m];
            net[q][pre[q]]+=incf[m];
            q=pre[q];
        }
        sum+=incf[m];
    }
    return sum;
}

int main(){
    int x,y,cap;
    while(scanf("%d %d",&n,&m)!=EOF){
        memset(net,0,sizeof(net));
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&x,&y,&cap);
            net[x][y]+=cap;
        }
        printf("%d\n",maxFlow());
    }
    return 0;
}
*/
