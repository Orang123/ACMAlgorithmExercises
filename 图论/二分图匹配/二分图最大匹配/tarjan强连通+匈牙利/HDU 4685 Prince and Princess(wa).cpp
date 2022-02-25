#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 2100
#define M 250000
using namespace std;
//是POJ 1904 King's Quest加强版,HDU 4685 没给出初始完美匹配,需要匈牙利先求出完美匹配
//wa 好像网上的做法求解二分图完美匹配和tarjan求scc并不建在一张图里,
//求完美匹配用的vector,求scc用的是链式前向星,不懂原因,不知道是不是以为这个原因wa了,而且数组大小按照题目给出的数据设500,会runtime error,
//设大设成2000 不会runrime error,但是会wa,不懂原因.
/*
题意:同POJ 1904 只不过此题没有给出初始的完美匹配,而且王子和公主的
人数不等.
题意:n个王子和m个公主,王子只能和他喜欢的公主结婚,公主可以和所有
的王子结婚,输出所有王子可能的结婚对象,必须保证王子与任意这些对象
中的一个结婚,都不会影响到整体所有王子的最大匹配数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4685
思路:做法和POJ 1904是相同的,还是tarjan求解scc,判断王子和公主是否在同
一个scc中,如果在同一个scc这个王子就可以选取这个公主.因为没有初始匹配,
所以可以先求出初始最大匹配,将匹配的公主j+n和王子i连j+n->i的有向边,
问题是初始的王子个数n和公主个数m,可能不等,当n>m 只按照已有的边去求解scc,
最终,n>m多出的那些王子,因为没有公主到王子的有向边所以最终这些多出的王子
没有和任何公主在一个scc里,而题目要求的是不影响最大匹配数的每个王子能选
的公主,显然这些王子是可以选那些已被其它王子选的公主的,所以结果会错,那就需要
在求解最大匹配前构造一些虚拟点使得每个王子都能找到一个公主配对,即就是若n>m
,虚拟出一些公主使得公主数量等于王子,所有的王子都和这些公主有连边,之后求解完美
匹配,这样每个王子都能配对一个公主,也就是构造公主到王子的匹配边时,每个王子都能
和这个配对公主至少在同一个scc,这样最后tarjan求解scc时,原本多出的那部分王子,就能
和之前它本身喜欢的一些公主在同一个scc内,就能输出它们,因为这些本身喜欢的公主和其它
王子也会有连边,而其它公主和其它王子必然在一个scc内,而其它王子也和只写虚拟公主有连边,
这样就能使得多出的王子和本身喜欢的公主在一个scc内.

讲真的这题出的有点勉勉强强,和POJ 1904一样 我的输入样例同样能hack掉这个算法的思路.
POJ 1904和HDU 4685这两题都出的有些勉强.

网上的题解 对于n<m的情况 也构造了虚拟王子使得王子数目和公主数目相等,实际对于n<m的情况,
不需要虚拟王子,只需要正常建边,最终tarjan求解scc时,不影响公主和王子在一个scc的判定,结果
是正确的,只有n>m的时候需要虚拟公主,求解scc.
*/
int cas,cnt,head[N<<1],match[N<<1],vis[N<<1],nx,ny;
int n,m,e,dfn[N<<1],low[N<<1],clock,block[N<<1],id;
stack<int> s;
vector<int> seq;

struct Edge{
    int to,next;
}edge[N*N*4];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int hungary(int num){
    int ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=num;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }
    return ans;
}

void init(){
    cas++;
    clock=id=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
    memset(block,0,sizeof(block));
}

int main(){
    int T,v,tp;;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);
        tp=max(n,m);//求出最大的数目
        for(int i=1;i<=n;i++){
            scanf("%d",&e);
            while(e--){
                scanf("%d",&v);
                addEdge(i,v+tp);//公主编号1+tp~m+tp
            }
        }
        tp=hungary(n);
        nx=ny=n+m-tp;//nx ny表示虚拟后的完美匹配中每个集合的个数
        for(int i=1;i<=nx;i++){
            for(int j=m+1;j<=ny;j++)//从m+1设置虚拟公主
                addEdge(i,j+nx);//每个王子都和虚拟公主有连边
        }
        for(int i=n+1;i<=nx;i++){//从n+1开始设置虚拟王子
            for(int j=1;j<=ny;j++)
                addEdge(i,j+nx);//每个虚拟王子都和所有的公主有连边
        }
        hungary(nx);
        for(int i=1;i<=ny;i++)
            addEdge(i+nx,match[i+nx]);//构建匹配中公主到王子的有向连边
        for(int i=1;i<=2*nx;i++){//求解scc
            if(!dfn[i])
                tarjan(i);
        }
        printf("Case #%d:\n",cas);
        for(int u=1;u<=n;u++){
            seq.clear();
            for(int i=head[u];i!=-1;i=edge[i].next){
                v=edge[i].to;
                if(v-nx>m) continue;//不考虑虚拟的公主
                if(block[u] == block[v])//儿子u和女孩v在同一scc,则可以结婚不影响其它儿子选取配偶
                    seq.push_back(v-nx);//女孩实际编号减nx
            }
            sort(seq.begin(),seq.end());
            printf("%d",seq.size());
            for(int &i : seq)
                printf(" %d",i);
            printf("\n");
        }
    }
    return 0;
}

/*
//ac 608ms Hopcroft-Karp(HK)算法,复杂度为O(sqrt(V)*E)
//求完美匹配用的是 参考博客:https://blog.csdn.net/a1325136367/article/details/75434592
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
using namespace std;
const int inf = 0x3f3f3f3f;
const int mx = 2005;
int dis,dx[mx],dy[mx],vis[mx];
int x[mx],y[mx],head[mx],ans[mx];
int pre[mx],low[mx],sccno[mx];
int cnt,tot,dfn;
stack<int>st;
vector<int>g[mx];
int n,m,nv,nu;
struct node{
    int v,next;
}E[mx*mx];
void init(){
    for(int i = 1; i <= n+m; i++) g[i].clear();
    memset(head,0,sizeof(head));
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    dfn = cnt = tot = 0;
}
void add(int u,int v){
    tot++;
    E[tot].v = v;
    E[tot].next = head[u];
    head[u] = tot;
}
bool search(){
    dis = inf;
    queue<int>q;
    memset(dx,0,sizeof(dx));
    memset(dy,0,sizeof(dy));
    for(int u = 1; u <= nu; u++)
        if(!x[u]){
            dx[u] = 1;
            q.push(u);
        }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(dx[u]>dis)  break;
        for(int i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(!dy[v]){
                dy[v] = dx[u]+1;
                if(!y[v]) dis = dy[v];
                else{
                    dx[y[v]] = dy[v]+1;
                    q.push(y[v]);
                }
            }
        }
    }
    return dis!=inf;
}
bool find(int u){
    for(int i = 0; i < g[u].size(); i++){
        int v = g[u][i];
        if(!vis[v]&&dy[v] == dx[u]+1){
            vis[v] = 1;
            if(y[v]&&dis == dy[v])  continue;
            if(!y[v]||find(y[v])){
                x[u] = v;
                y[v] = u;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch(){
    int ans = 0;
    while(search()){
        memset(vis,0,sizeof(vis));
        for(int u = 1; u <= nu; u++)
            if(!x[u]&&find(u))  ans++;
    }
    return ans;
}
void tarjan(int u){
    pre[u] = low[u] = ++dfn;
    st.push(u);
    for(int i = head[u]; i; i = E[i].next){
        int v = E[i].v;
        if(!pre[v]){
            tarjan(v);
            low[u] = min(low[v],low[u]);
        }
        else if(!sccno[v])
            low[u] = min(low[v],low[u]);
    }
    if(pre[u] == low[u]){
        cnt++;
        while(1){
            int x = st.top();
            st.pop();
            sccno[x] = cnt;
            if(x == u)  break;
        }
    }
}
void solve(){
    nu = n;
    nv = m;
    int cnt = MaxMatch();
    nu = nv = n+m-cnt;
    for(int u = 1; u <= n; u++)
        for(int v = m+1; v <= nv; v++)
            g[u].push_back(v);
    for(int u = n+1; u <= nu; u++)
        for(int v = 1; v <= m; v++)
            g[u].push_back(v);
    MaxMatch();
    for(int u = 1; u <= nu; u++)
        for(int i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            add(u,v+nu);
        }
    for(int v = 1; v <= nv; v++)
        add(nu+v,y[v]);
    for(int u = 1; u <= 2*nu; u++)
        if(!pre[u])
            tarjan(u);
    for(int u = 1; u <= n; u++){
        int len = 0;
        for(int i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(v>m)
                break;
            if(sccno[v+nu] == sccno[u])
                ans[len++] = v;
        }
        sort(ans,ans+len);
        printf("%d",len);
        for(int i = 0; i < len; i++)
            printf(" %d",ans[i]);
        printf("\n");
    }
}
int main(){
    int t;
    scanf("%d",&t);
    for(int casei = 1; casei <= t; casei++){
        scanf("%d%d",&n,&m);
        init();
        for(int u = 1; u <= n; u++){
            int num,v;
            scanf("%d",&num);
            for(int i = 1; i <= num; i++){
                scanf("%d",&v);
                g[u].push_back(v);
            }
        }
        printf("Case #%d:\n",casei);
        solve();
    }
    return 0;
}
*/

/*
//ac 1388ms 参考博客:https://www.gonglin91.com/hdu-4685-prince-and-princess/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 1010
#define M 5000010
#define cl(xx,yy) memset((xx),(yy),sizeof((xx)))
#define pb push_back

int n,m;
bool g[N][N],vis[N];
int xmatch[N],ymatch[N];
int tot,head[N];
int ans[N][N],num[N];
struct edge{
    int u,v,next;
}e[M];
int dfn[N],low[N],belong[N],stack[N],top,dcnt,bcnt;
bool ins[N];

int dfs(int u){
    for(int v = 1; v <= m; v++)
        if(g[u][v] && !vis[v]){
            vis[v] = true;
            if(ymatch[v] == -1 || dfs(ymatch[v])){
                xmatch[u] = v; ymatch[v] = u; return 1;
            }
        }
    return 0;
}

int MaxMatch(){
    int ans = 0;
    cl(xmatch,-1); cl(ymatch,-1);
    for(int u = 1; u <= n; u++){
        cl(vis,false);
        ans += dfs(u);
    }
    return ans;
}

inline void add(int u,int v){
    e[tot].u = u; e[tot].v = v;
    e[tot].next = head[u]; head[u] = tot++;
}

void tarjan(int u){
    dfn[u] = low[u] = ++dcnt;
    stack[++top] = u; ins[u] = true;
    for(int k = head[u]; k != -1; k = e[k].next){
        int v = e[k].v;
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(ins[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++bcnt;
        while(true){
            int x = stack[top--];
            belong[x] = bcnt; ins[x] = false;
            if(x == u) break;
        }
    }
}

void SCC(int nn){
    dcnt = bcnt = top = 0;
    cl(dfn,0); cl(ins,false);
    for(int i = 1; i <= nn; i++)
        if(!dfn[i])
            tarjan(i);
}

int main(){
    int T;
    scanf("%d",&T);
    for(int cas = 1; cas <= T; cas++){
        scanf("%d%d",&n,&m);
        cl(g,false);
        for(int u = 1; u <= n; u++){
            int k,v;
            scanf("%d",&k);
            while(k--){
                scanf("%d",&v);
                g[u][v] = true;
            }
        }
        int res = MaxMatch();

        for(int u = 1,cnt = 0; u <= n; u++)
            if(xmatch[u] == -1){ //王子没有匹配
                xmatch[u] = m + (++cnt); //虚构一个新的公主和他匹配
                ymatch[m+cnt] = u;
                g[u][m+cnt] = true; //连一条边
            }
        for(int v = 1,cnt = 0; v <= m; v++)
            if(ymatch[v] == -1){ //公主没有匹配
                ymatch[v] = n + (++cnt); //虚构一个新的王子和他匹配
                xmatch[n+cnt] = v;
                g[n+cnt][v] = true;
            }
        for(int u = n+1; u <= n+m-res; u++) //新虚构出来的王子，每一个都喜欢所有公主
            for(int v = 1; v <= n+m-res; v++)
                g[u][v] = true;
        for(int v = m+1; v <= n+m-res; v++) //新虚构出来的公主，每一个都被所有王子喜欢
            for(int u = 1; u <= n+m-res; u++)
                g[u][v] = true;

        cl(head,-1); tot = 0;
        for(int u = 1; u <= n+m-res; u++){
            int wife = xmatch[u];
            for(int v = 1; v <= n+m-res; v++)
                if(g[u][v] && v != wife)
                    add(wife,v);
        }
        SCC(n+m-res);
        printf("Case #%d:\n",cas);
        cl(num,0);
        for(int u = 1; u <= n; u++){ //不需要看虚构的王子
            int wife = xmatch[u];
            int bw = belong[wife];
            if(wife <= m) ans[u][num[u]++] = wife;
            for(int k = head[wife]; k != -1; k = e[k].next){
                int v = e[k].v;
                if(v > m) continue; //虚构的直接抛弃
                int bv = belong[v];
                if(bw == bv) ans[u][num[u]++] = v;
            }
            sort(ans[u],ans[u]+num[u]);
            printf("%d",num[u]);
            for(int i = 0; i < num[u]; i++)
                printf(" %d",ans[u][i]);
            puts("");
        }
    }
    return 0;
}
*/
