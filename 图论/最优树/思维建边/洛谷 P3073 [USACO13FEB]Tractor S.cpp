#include<cstdio>
#include<algorithm>
#define N 550
#define M 250100
using namespace std;
//kruskal ac 488ms
/*
题意:n*n网格的农场,每个农场只能朝上下左右4个方向农场连通,
农场间的连通的代价为农场间的高度差D,现在你在农场间遍历使用
拖拉机,要想从一个农场到另一个农场,你的拖拉机价值至少也得是D,
现在问你遍历数量为农场总数一半(总数为奇数时四舍五入)时需要买拖拉机的最小价值.
链接:https://www.luogu.com.cn/problem/P3073
思路:就是求解mst中恰好连接了一半点数的最大边权的最小值.
贪心,Kruskal加边过程中点数刚好大于等于(n*n+1)/2时的边权即是答案.需要设置一个
代表每个连通集点个数siz数组.
注意:prim做法 需要跑n*n次prim,因为prim是从某个点开始加入点,但是个数刚好到达点数一半
时连通集中的最大边不一定就是所有可能点数一半连通情况中边权最小的.这样会TLE.
*/

int n,m,fa[N*N],mp[N][N],siz[N*N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M<<1];

void init(){
    n*=n;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        siz[i]=1;
    }
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            //因为y集合的根节点指向x集合根节点,所以x集合根节点的节点数要加上y结合的节点数
            siz[x]+=siz[y];
            if(siz[x]>=(n+1)/2) return edge[i].w;
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mp[i][j]);
            if(j>1)
                edge[++m]=Edge((i-1)*n+j,(i-1)*n+j-1,abs(mp[i][j]-mp[i][j-1]));
            if(i>1)
                edge[++m]=Edge((i-1)*n+j,(i-2)*n+j,abs(mp[i][j]-mp[i-1][j]));
        }
    }
    printf("%d",kruskal());
    return 0;
}

/*
//prim TLE 开启O(N^2)优化都会TLE
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define N 550
#define M 250100
#define INF 0x3f3f33f
using namespace std;

int n,m,mp[N][N],vis[N*N],dis[N*N];
vector<pair<int,int> > edge[M];

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,num=0,ans=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        num++;
        ans=max(ans,dis[u]);
        if(num == (n*n+1)/2) break;
        for(pair<int,int> &e:edge[u]){
            v=e.first;
            if(!vis[v] && e.second<dis[v]){
                dis[v]=e.second;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return ans;
}

int main(){
    int w,ans=INF;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mp[i][j]);
            if(j>1){
                w=abs(mp[i][j]-mp[i][j-1]);
                edge[(i-1)*n+j].push_back(make_pair((i-1)*n+j-1,w));
                edge[(i-1)*n+j-1].push_back(make_pair((i-1)*n+j,w));
            }
            if(i>1){
                w=abs(mp[i][j]-mp[i-1][j]);
                edge[(i-1)*n+j].push_back(make_pair((i-2)*n+j,w));
                edge[(i-2)*n+j].push_back(make_pair((i-1)*n+j,w));
            }
        }
    }
    for(int i=1;i<=n*n;i++)
        ans=min(ans,prim(i));
    printf("%d",ans);
    return 0;
}
*/

/*
dfs+二分
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
#define TP int
inline TP read(){//快读
    char c=getchar();TP x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
const int wlxsq=505;
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int n=read(),a[wlxsq][wlxsq],l=1e6,r=-1,ans;
bool vis[wlxsq][wlxsq];
int dfs(int x,int y,int k)
{
    vis[x][y]=1;
    int res=1;
    For(i,0,3)
    {
        int xx=x+dx[i],yy=y+dy[i];
        if(xx>0&&yy>0&&xx<=n&&yy<=n&&!vis[xx][yy]&&abs(a[xx][yy]-a[x][y])<=k)
            res+=dfs(xx,yy,k);
    }
    return res;
}
bool check(int k)
{
    memset(vis,0,sizeof vis);
    For(i,1,n)
        For(j,1,n)
            if(!vis[i][j])
                if(dfs(i,j,k)*2>=n*n)
                	return 1;
    return 0;
}
int main()
{
    For(i,1,n)
        For(j,1,n){
        	a[i][j]=read();
        	r=max(r,a[i][j]);
        	l=min(l,a[i][j]);
        }
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))r=mid-1,ans=mid;
        else l=mid+1;
    }
    printf("%d",ans);
    return 0;
}
*/
