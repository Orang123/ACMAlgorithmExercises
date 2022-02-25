#include<cstdio>
#include<algorithm>
#define N 550
#define M 250100
using namespace std;
//kruskal ac 488ms
/*
����:n*n�����ũ��,ÿ��ũ��ֻ�ܳ���������4������ũ����ͨ,
ũ�������ͨ�Ĵ���Ϊũ����ĸ߶Ȳ�D,��������ũ�������ʹ��
������,Ҫ���һ��ũ������һ��ũ��,�����������ֵ����Ҳ����D,
���������������Ϊũ������һ��(����Ϊ����ʱ��������)ʱ��Ҫ������������С��ֵ.
����:https://www.luogu.com.cn/problem/P3073
˼·:�������mst��ǡ��������һ�����������Ȩ����Сֵ.
̰��,Kruskal�ӱ߹����е����պô��ڵ���(n*n+1)/2ʱ�ı�Ȩ���Ǵ�.��Ҫ����һ��
����ÿ����ͨ�������siz����.
ע��:prim���� ��Ҫ��n*n��prim,��Ϊprim�Ǵ�ĳ���㿪ʼ�����,���Ǹ����պõ������һ��
ʱ��ͨ���е����߲�һ���������п��ܵ���һ����ͨ����б�Ȩ��С��.������TLE.
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
            //��Ϊy���ϵĸ��ڵ�ָ��x���ϸ��ڵ�,����x���ϸ��ڵ�Ľڵ���Ҫ����y��ϵĽڵ���
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
//prim TLE ����O(N^2)�Ż�����TLE
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
dfs+����
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
#define TP int
inline TP read(){//���
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
