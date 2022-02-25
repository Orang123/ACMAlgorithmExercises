#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 110
#define M 25100
#define INF 0x3f3f3f3f
using namespace std;
//ac 748ms EK算法 费用流 拆边
/*
题意:有N个节点M条边的有向图,现在你需要从1号节点运送k个货物到N号节点.
每条边都有一个ai和ci值,ci值是指该边最多能运ci个货物,而你如果在该边运x
(1<=x<=ci)个货物需要花费ai*x*x代价.问你运送这k个货物的最小代价是多少?
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3667
思路:这里显然是最小费用最大流的问题,问题是每条边的权值为一个函数,大白书上有讲,
举个例子,比如最多能运4个货物，那么在该边分别运1,2,3,4个货物的代价就是ai*1,ai*4,
ai*9,ai*16,那么相减一下有ai*1,ai*3,ai*5,ai*7,显然运送几个货物的代价就是这个等差
数列的前n项和,那么把最多可以运送c件货物拆成c条边,每条边容量为1,权值为ai*(2*i-1),
这样费用流的时候第一次就会选权值最小的那条边,第二次就会选次小的那条边,因为求的是
最小费用,所以等差数列刚好只会选择连续的前几项,把结果累加就是前n项和了,非常巧妙的拆边建图.
*/
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
    return pre[ed];
}

int mcmf(){
    int sum=0,cost=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
    return sum == k?cost:-1;
}

void init(){
    cnt=0;
    st=0,ed=n;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,a,c;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        init();
        addEdge(st,1,k,0);
        while(m--){
            scanf("%d%d%d%d",&u,&v,&a,&c);
            for(int i=1;i<=c;i++)
                addEdge(u,v,1,(2*i-1)*a);
        }
        printf("%d\n",mcmf());
    }
    return 0;
}
