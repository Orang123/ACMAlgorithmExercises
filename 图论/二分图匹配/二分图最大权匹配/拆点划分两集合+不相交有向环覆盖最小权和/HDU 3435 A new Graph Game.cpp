#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;
//ac 1107ms 最优匹配 slack数组松弛优化 dfs匈牙利不考虑实际不存在的边
//此题还可用费用流求解
/*
相关概念:
1.哈密顿回路:
(1).在无向连通图中,从起点出发,通过其余所有点1次,且仅1次,
最后回到起点的回路.注意这里起点访问了2次.其余所有点只访问1次.
哈密顿回路至少要有2个点.
(2).图G的一个回路,若它通过图的每一个节点一次,且仅一次,就是哈密顿回路.
2.哈密顿图:存在哈密顿回路的图就是哈密顿图.

通过此题也可看出,任何通过建模转化成的二分图如果存在完美匹配,
那么原图实际可以表示成多个环(哈密顿回路)的并集.注意不是交叉环.
*/

/*
题意:n个点,m条边的无向图,每条边都有权值,现在可
以删掉任意数量的边,使得原图变成一些分离的连通子图,
每个连通子图刚好构成一个哈密顿回路,不能是几个相交
的环,因为相交环除了起点外交点访问次数大于2(不构成哈密顿回路),
一个连通子图恰好构成一个简单环.现在要求出所有可能
情况的连通子图构成的所有哈密顿回路边权之和的最小值,
如果原图无法通过删边分离出各个哈密顿回路子图,输出NO.
释义:就是问用1个或多个不相交的有向环覆盖无向图中所有点,求这些环的最少边权和.
注意:
1.原无向图存在重边.(mp存图需要记录最小边权)
2.对于u-v这条边,已经构成了哈密顿回路,
先从u到v,再从v到u,每个点都只经过1次,恰好回到u点,u点访问2次.
3.每个回路至少要有2个点.
4.输入无自环,实际有自环也不会影响二分匹配的结果,X集合i点到Y集合i点构成一个匹配,不会死循环.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3435
思路:一条无向边u-v,可以表示成的边有2个方向,即u->v和v->u,
即:两个点都可以作为发出边的点,也可以作为连入边的点.实际
可以将无向图中所有点划分出2个状态(拆点),一种是发出边的点,一种是
流入边的点,将这两个状态作为左右2个集合,一个集合只考虑发出边,
另一个集合只考虑流入边,这恰好构成2分图.那么对于删边后形成的
各个连通子图构成的各个哈密顿回路而言,每个点的出度入度都是1,
也就是每个点都只能发出一条边,流入一条边.那么实际对应的二分图中
的连边恰好是没有公共点的,这恰好构成了匹配的边集,而要想构成回路,
那么这个二分图必须存在完美匹配才行,即每个点度刚好为2,既能发出一
条边,也能流入一条边,而且要求取最小边权和,可以将权值取负,KM算法求解
即可.建边按照无向图若存在u-v的无向边,用邻接矩阵建mp[u][v]=mp[v][u]=-w
边权的负数即可,注意因为有重边,每次要判断当前边权是否比已存在的边权
正值更小,如更小,再更新.
此题删边只是个幌子,其实就是在选取匹配边后,剩下的边自然就是要删掉的边,
这样各个连通子图就分离互不连通,并且每个连通子图都是哈密顿回路.

注意:对于交叉环,并不是哈密顿回路,因为要遍历所有点1次,那么交叉点必然会遍历
2次,不满足定义,而实际转化为匹配问题,交叉环构成的匹配会有公共点,也不符合匹配
的定义.
*/
int cas,n,m,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],slack[N],d,ans;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(mp[u][v] == -INF || visy[v]) continue;
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

void KM(){
    for(int i=1;i<=n;i++){
        lx[i]=-INF;//初始化为负无穷,因为边权为负值
        ly[i]=0;
        for(int j=1;j<=n;j++){
            if(mp[i][j]!=INF)
                lx[i]=max(lx[i],mp[i][j]);
        }
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
            //如果存在某个点找不到Y集合的配对点,则说明这个点度为2,
            //要么是度为1本身不存在回路,要么是存在交叉环度>=3的情况
            if(d == INF) return;
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    //说明存在完美匹配,即能分割出各个哈密顿回路的连通子图
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
}

void init(){
    ans=0;
    cas++;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            mp[i][j]=-INF;//-INF无法memset这样赋值最终结果并不等于-INF,因为每字节并不是0x3f
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//u即可作发出边的点,也可作连入边的点,v点同理
            if(-mp[u][v]>w)//要判断当前已存边边权是否比输入边权大,若大则更新
                mp[u][v]=mp[v][u]=-w;//KM求最大匹配边权和,因此存负值
        }
        KM();
        if(!ans) printf("Case %d: NO\n",cas);
        else printf("Case %d: %d\n",cas,-ans);
    }
    return 0;
}

/*
//ac 1903ms 最优匹配 slack数组松弛优化 对于不存在的边也考虑配对将其配对,
//最后累加权和时判断匹配边权是否-INF,若等于-INF,说明存在某个子图不构成环
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],slack[N],d,ans;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
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
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        //匹配边权为-INF,说明这条边本身不存在
        //说明X集合中的点match[i]实际是找不到Y集合中配对点的,
        //即删去匹配边集外的边,存在一个子图不构成哈密顿回路
        //这个点的度可能是1(本身不构成回路),也可能是交叉环度>=3的情况.
        if(mp[match[i]][i] == -INF){
            ans=0;
            break;
        }
        ans+=mp[match[i]][i];
    }
}

void init(){
    ans=0;
    cas++;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            mp[i][j]=-INF;
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            if(-mp[u][v]>w)
                mp[u][v]=mp[v][u]=-w;
        }
        KM();
        if(!ans) printf("Case %d: NO\n",cas);
        else printf("Case %d: %d\n",cas,-ans);
    }
    return 0;
}
*/

/*
//费用流 TLE 此题链式前向星莫名超时 vector能ac
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 2100
#define M 14000
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
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

void mcmf(){
    int sum=0,cost=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
    printf("Case %d: ",cas);
    if(sum == n) printf("%d\n",cost);
    else printf("NO\n");
}

void init(){
    cas++;
    cnt=0;
    st=0,ed=n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++){
            addEdge(st,i,1,0);
            addEdge(i+n,ed,1,0);
        }
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v+n,1,w);
            addEdge(v,u+n,1,w);
        }
        mcmf();
    }
    return 0;
}
*/

/*
//此题因为有重边,所以不好用链式前向星去建图,无法避免重边的权值也累加进去,
//无论是用match[v]==u(不是匹配的边也会满足)或标记匹配边的办法
//(dfs匈牙利算法搜索增广路匹配编和非匹配边交替,变成非匹配边的不好取消标记)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,match[N],visx[N],visy[N],lx[N],ly[N],slack[N],d,ans;
int cnt,head[N];
struct Edge{
    int from,to,next,w,flag;
}edge[N*N*2];

void addEdge(int from,int to,int w,int flag){
    edge[cnt]=(Edge){from,to,head[from],w,flag};
    head[from]=cnt++;
}

int dfs(int u){
    visx[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-edge[i].w;
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                edge[i].flag=1;
                match[v]=u;
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
    }
    for(int i=0;i<cnt;i++){
        int u=edge[i].from;
        for(int j=head[u];j!=-1;j=edge[j].next)
            lx[u]=max(lx[u],edge[i].w);
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
            if(d == INF) return;
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int num=0;
    for(int i=0;i<cnt;i++){
        if(edge[i].flag){
            ans+=edge[i].w;
            num++;
            if(num == n) break;
        }
    }
}

void init(){
    cnt=ans=0;
    cas++;
    memset(head,-1,sizeof(head));
    memset(match,0,sizeof(match));
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,-w,0);
            addEdge(v,u,-w,0);
        }
        KM();
        if(!ans) printf("Case %d: NO\n",cas);
        else printf("Case %d: %d\n",cas,-ans);
    }
    return 0;
}
*/
