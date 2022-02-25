#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 250
#define INF 0x3f3f3f3f
using namespace std;
//ac 62ms 邻接矩阵存边 slack数组优化 dfs匈牙利不判断不存在边
//也可用费用流解
/*
题意:n个城市,m条单向道路,每条道路有一定长度距离,现在要
用多条路线将所有的城市覆盖,每条线路必须经过每个城市一次,
并且构成回路,所有线路都不相交,现在问所有的城市用这样的路线
覆盖道路的最少距离和是多少.
释义:就是问用1个或多个不相交的有向环覆盖有向图中所有点,求这些环的最少边权和.
注意:
1.单向道路有重边,此题保证所有城市一定可以用不同的不相交有向环路线
覆盖,即保证存在完美匹配.
2.每条路线至少有2个城市,即环中至少2个点.
3.输入保证无自环.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3488
思路:同HDU 3435,每个点拆点成2个状态 一个是出度,一个是入度,刚好
划分成2个集合,所有不相交环刚好构成这个二分图的完美匹配,求最小边权和,
KM算法,边权取负即可.

//因为有重边就不好用链式前向星建图.
*/
int n,m,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;//因为本题保证一定存在完美匹配,所以不判贪心选最小边权,结果也不会错
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
    for(int i=1;i<=n;i++){
        lx[i]=-INF;
        ly[i]=0;
        for(int j=1;j<=n;j++){
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
            //不需判d == INF break,此题保证所有城市一定可以用不同的不相交有向环路线覆盖.
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        //此题保证所有城市一定可以用不同的不相交有向环路线覆盖.
        //if(mp[match[i]][i]!=-INF)
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            mp[i][j]=-INF;//有重边初始化为负无穷
    }
    //不能初始化为0,这样KM贪心每次最小差值会优先选择本身不存在的边,
    //因为不存在的边mp[i][j]=0,lx为负,差值d为负数最小,结果就会偏小
    //memset(mp,0,sizeof(mp));
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//权值为零不影响结果
            if(-mp[u][v]>w)//有重边,取单向边的最小边权
                mp[u][v]=-w;
        }
        printf("%d\n",-KM());
    }
    return 0;
}

/*
//ac 109ms 邻接矩阵存边 dfs匹配不考虑不存在边
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 250
#define INF 0x3f3f3f3f
using namespace std;

int n,m,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(mp[u][v] == -INF || visy[v]) continue;//mp[u][v] == -INF 不存在边不考虑匹配
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
    for(int i=1;i<=n;i++){
        lx[i]=-INF;
        ly[i]=0;
        for(int j=1;j<=n;j++){
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
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        //if(mp[match[i]][i]!=-INF)
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            mp[i][j]=-INF;
    }
    //不能初始化为0,这样KM贪心每次最小差值会优先选择本身不存在的边,
    //因为不存在的边mp[i][j]=0,lx为负,差值d为负数最小,结果就会偏小
    //memset(mp,0,sizeof(mp));
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//权值为零不影响结果
            if(-mp[u][v]>w)//有重边,取单向边的最小边权
                mp[u][v]=-w;
        }
        printf("%d\n",-KM());
    }
    return 0;
}
*/

/*
//因为有重边就不好用链式前向星建图.
*/
