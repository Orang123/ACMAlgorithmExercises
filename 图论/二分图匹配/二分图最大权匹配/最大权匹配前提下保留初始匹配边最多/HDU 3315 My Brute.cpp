#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
//ac 31ms slack松弛优化
//也可用最大费用流求解
//同HDU 2853
/*
//题意摘自网上
题意:有S1到Sn这n个勇士要和X1到Xn这n个勇士决斗,初始时,Si的决斗对象是Xi.
如果Si赢了Xi,那么你将获得Vi分,否则你将获得-Vi分.Si和Xi对决时,Si有初始
生命Hi,初始攻击Ai, Xi有初始生命Pi,初始攻击Bi. 且Si先出手,然后Xi失去Ai
生命,之后如果Xi没死,那么Xi出手,Si失去Bi生命. 直到有一方的生命值<=0时,
决斗结束.现在要你重新安排S和X的决斗顺序,使得S1~Sn能获得的分最多.如果有多
个最优解,你要选取那个维持初始决斗顺序最多的解.如果S1~Sn最终得分总和大于0,
则输出最大得分和原始决斗顺序不变所占的比例(百分号保留3位小数),否则输出
"Oh, I lose my dear seaco!".
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3315
思路:在决斗得分最大的前提下要尽可能维持初始决斗配对,同HDU 2853,
将边权扩大(n+1),因为初始匹配是Si对Xi,所以mp[i][i]再加1.这里边权既
有正值,也有负值,所以lx初始化-INF,KM求解最大权匹配,就是Si最大得分.
*/
int v[N],h[N],p[N],a[N],b[N],ans;
int n,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!link[v] || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

void KM(){
    for(int i=1;i<=n;i++){
        lx[i]=-INF;
        ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
                else slack[j]-=d;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!link[i]) continue;
        ans+=mp[link[i]][i];
    }
}

int cal(int i,int j){
    int hi=h[i],pj=p[j];
    //Si和Xj决斗的方式是每轮Si攻击Xj一次,Xj再攻击Si一次
    //p[j](Xj的血量)每次减a[i],h[i](Si的血量)每次减b[j].
    while(1){
        pj-=a[i];
        if(pj<=0) return v[i];//当Xj血量小于等于0时,Si得分v[i]
        hi-=b[j];
        if(hi<=0) return -v[i];//当Si血量小于等于0时,Si得分-v[i]
    }
}

void init(){
    ans=0;
    memset(link,0,sizeof(link));
}

int main(){
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++) scanf("%d",&v[i]);
        for(int i=1;i<=n;i++) scanf("%d",&h[i]);
        for(int i=1;i<=n;i++) scanf("%d",&p[i]);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                mp[i][j]=cal(i,j)*(n+1);//边权扩大(n+1)倍
                if(i == j) mp[i][j]++;//初始匹配边权再加1
            }
        }
        KM();
        if(ans<=0)
            printf("Oh, I lose my dear seaco!\n");
        else
            printf("%d %.3f%%\n",ans/(n+1),ans%(n+1)*1.0/n*100);//输出最大权值和和最大权匹配中初始匹配所占的比例
    }
    return 0;
}

/*
//ac 780ms EK算法 费用流
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 220
#define INF 0x3f3f3f3f
using namespace std;

int v[N],h[N],p[N],a[N],b[N];
int n,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N],sum,cost;
struct Edge{
    int to,next,cf,w;
}edge[N*N];

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

void mcmf(){
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
}

int cal(int i,int j){
    int hi=h[i],pj=p[j];
    //Si和Xj决斗的方式是每轮Si攻击Xj一次,Xj再攻击Si一次
    //p[j](Xj的血量)每次减a[i],h[i](Si的血量)每次减b[j].
    while(1){
        pj-=a[i];
        if(pj<=0) return v[i];//当Xj血量小于等于0时,Si得分v[i]
        hi-=b[j];
        if(hi<=0) return -v[i];//当Si血量小于等于0时,Si得分-v[i]
    }
}

void init(){
    sum=cost=cnt=0;
    st=0,ed=2*n+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int w;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++) scanf("%d",&v[i]);
        for(int i=1;i<=n;i++) scanf("%d",&h[i]);
        for(int i=1;i<=n;i++) scanf("%d",&p[i]);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            addEdge(st,i,1,0);
            addEdge(i+n,ed,1,0);
            for(int j=1;j<=n;j++){
                w=cal(i,j)*(n+1);//边权扩大(n+1)倍
                if(i == j) w++;//初始匹配边权再加1
                addEdge(i,j+n,1,-w);
            }
        }
        mcmf();
        if(-cost/(n+1)<=0)
            printf("Oh, I lose my dear seaco!\n");
        else
            printf("%d %.3f%%\n",-cost/(n+1),-cost%(n+1)*1.0/n*100);//输出最大权值和和最大权匹配中初始匹配所占的比例
    }
    return 0;
}
*/
