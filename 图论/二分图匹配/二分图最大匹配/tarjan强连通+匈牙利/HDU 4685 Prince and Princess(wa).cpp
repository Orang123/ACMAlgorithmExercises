#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 2100
#define M 250000
using namespace std;
//��POJ 1904 King's Quest��ǿ��,HDU 4685 û������ʼ����ƥ��,��Ҫ���������������ƥ��
//wa �������ϵ�����������ͼ����ƥ���tarjan��scc��������һ��ͼ��,
//������ƥ���õ�vector,��scc�õ�����ʽǰ����,����ԭ��,��֪���ǲ�����Ϊ���ԭ��wa��,���������С������Ŀ������������500,��runtime error,
//������2000 ����runrime error,���ǻ�wa,����ԭ��.
/*
����:ͬPOJ 1904 ֻ��������û�и�����ʼ������ƥ��,�������Ӻ͹�����
��������.
����:n�����Ӻ�m������,����ֻ�ܺ���ϲ���Ĺ������,�������Ժ�����
�����ӽ��,����������ӿ��ܵĽ�����,���뱣֤������������Щ����
�е�һ�����,������Ӱ�쵽�����������ӵ����ƥ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4685
˼·:������POJ 1904����ͬ��,����tarjan���scc,�ж����Ӻ͹����Ƿ���ͬ
һ��scc��,�����ͬһ��scc������ӾͿ���ѡȡ�������.��Ϊû�г�ʼƥ��,
���Կ����������ʼ���ƥ��,��ƥ��Ĺ���j+n������i��j+n->i�������,
�����ǳ�ʼ�����Ӹ���n�͹�������m,���ܲ���,��n>m ֻ�������еı�ȥ���scc,
����,n>m�������Щ����,��Ϊû�й��������ӵ����������������Щ���������
û�к��κι�����һ��scc��,����ĿҪ����ǲ�Ӱ�����ƥ������ÿ��������ѡ
�Ĺ���,��Ȼ��Щ�����ǿ���ѡ��Щ�ѱ���������ѡ�Ĺ�����,���Խ�����,�Ǿ���Ҫ
��������ƥ��ǰ����һЩ�����ʹ��ÿ�����Ӷ����ҵ�һ���������,��������n>m
,�����һЩ����ʹ�ù���������������,���е����Ӷ�����Щ����������,֮���������
ƥ��,����ÿ�����Ӷ������һ������,Ҳ���ǹ��칫�������ӵ�ƥ���ʱ,ÿ�����Ӷ���
�������Թ���������ͬһ��scc,�������tarjan���sccʱ,ԭ��������ǲ�������,����
��֮ǰ������ϲ����һЩ������ͬһ��scc��,�����������,��Ϊ��Щ����ϲ���Ĺ���������
����Ҳ��������,�������������������ӱ�Ȼ��һ��scc��,����������Ҳ��ֻд���⹫��������,
��������ʹ�ö�������Ӻͱ���ϲ���Ĺ�����һ��scc��.

�������������е�����ǿǿ,��POJ 1904һ�� �ҵ���������ͬ����hack������㷨��˼·.
POJ 1904��HDU 4685�����ⶼ������Щ��ǿ.

���ϵ���� ����n<m����� Ҳ��������������ʹ��������Ŀ�͹�����Ŀ���,ʵ�ʶ���n<m�����,
����Ҫ��������,ֻ��Ҫ��������,����tarjan���sccʱ,��Ӱ�칫����������һ��scc���ж�,���
����ȷ��,ֻ��n>m��ʱ����Ҫ���⹫��,���scc.
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
        tp=max(n,m);//���������Ŀ
        for(int i=1;i<=n;i++){
            scanf("%d",&e);
            while(e--){
                scanf("%d",&v);
                addEdge(i,v+tp);//�������1+tp~m+tp
            }
        }
        tp=hungary(n);
        nx=ny=n+m-tp;//nx ny��ʾ����������ƥ����ÿ�����ϵĸ���
        for(int i=1;i<=nx;i++){
            for(int j=m+1;j<=ny;j++)//��m+1�������⹫��
                addEdge(i,j+nx);//ÿ�����Ӷ������⹫��������
        }
        for(int i=n+1;i<=nx;i++){//��n+1��ʼ������������
            for(int j=1;j<=ny;j++)
                addEdge(i,j+nx);//ÿ���������Ӷ������еĹ���������
        }
        hungary(nx);
        for(int i=1;i<=ny;i++)
            addEdge(i+nx,match[i+nx]);//����ƥ���й��������ӵ���������
        for(int i=1;i<=2*nx;i++){//���scc
            if(!dfn[i])
                tarjan(i);
        }
        printf("Case #%d:\n",cas);
        for(int u=1;u<=n;u++){
            seq.clear();
            for(int i=head[u];i!=-1;i=edge[i].next){
                v=edge[i].to;
                if(v-nx>m) continue;//����������Ĺ���
                if(block[u] == block[v])//����u��Ů��v��ͬһscc,����Խ�鲻Ӱ����������ѡȡ��ż
                    seq.push_back(v-nx);//Ů��ʵ�ʱ�ż�nx
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
//ac 608ms Hopcroft-Karp(HK)�㷨,���Ӷ�ΪO(sqrt(V)*E)
//������ƥ���õ��� �ο�����:https://blog.csdn.net/a1325136367/article/details/75434592
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
//ac 1388ms �ο�����:https://www.gonglin91.com/hdu-4685-prince-and-princess/
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
            if(xmatch[u] == -1){ //����û��ƥ��
                xmatch[u] = m + (++cnt); //�鹹һ���µĹ�������ƥ��
                ymatch[m+cnt] = u;
                g[u][m+cnt] = true; //��һ����
            }
        for(int v = 1,cnt = 0; v <= m; v++)
            if(ymatch[v] == -1){ //����û��ƥ��
                ymatch[v] = n + (++cnt); //�鹹һ���µ����Ӻ���ƥ��
                xmatch[n+cnt] = v;
                g[n+cnt][v] = true;
            }
        for(int u = n+1; u <= n+m-res; u++) //���鹹���������ӣ�ÿһ����ϲ�����й���
            for(int v = 1; v <= n+m-res; v++)
                g[u][v] = true;
        for(int v = m+1; v <= n+m-res; v++) //���鹹�����Ĺ�����ÿһ��������������ϲ��
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
        for(int u = 1; u <= n; u++){ //����Ҫ���鹹������
            int wife = xmatch[u];
            int bw = belong[wife];
            if(wife <= m) ans[u][num[u]++] = wife;
            for(int k = head[wife]; k != -1; k = e[k].next){
                int v = e[k].v;
                if(v > m) continue; //�鹹��ֱ������
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
