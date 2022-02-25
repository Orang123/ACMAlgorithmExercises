#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;
//ac 156ms stack栈存点 求解pbc无需判重的做法
/*
题意:n家企业,m条资金链组成的金融交易关系网络,如果同一条资金链上
的一家企业面临破产,导致现金流受阻,那么与之相关的其他企业也会受到影响,
独立性资金链是指如果存在两条由企业组成的道路,并且它们之间的资金链
关系具有共同的起点s和终点t,除了s和t外,这两条道路中没有任何一家
企业同时被包括在这两条道路上,这样其中一家企业在一条道路上破产,
另一家企业的资金链并不收到影响,现在有q条询问u v之间有几条独立的
资金链,如果不连通输出"zero",如果连通只有一条独立的资金链,输出"one",
如果有2条或2条以上资金链,输出"two or more".

释义:无向图(无重边),求解u和v是否在同一点双连通分量,注意如果u和v在同一点双连通分量中,
但其中元素个数只有u和v两个时,那么之间的独立资金链也只有唯一条数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3749
思路:tarjan求解pbc,因为每个点可以从属多个pbc,所以在记录pbc时,要用belong数组
记录每个点所属的pbc的编号.
*/

int n,m,q,dfn[N],low[N],clock,cnt,id,pbc_cnt,head[N],vis[N];
stack<int> s;
vector<int> pbc[N],belong[N];//belong[u]代表u所在pbc的编号集合

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    vis[u]=id;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            s.push(v);
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                int tmp;
                pbc_cnt++;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc[pbc_cnt].push_back(tmp);
                    belong[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                pbc[pbc_cnt].push_back(u);
                belong[u].push_back(pbc_cnt);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,cas=0;
    while(scanf("%d%d%d",&n,&m,&q) && n+m+q){
        id=pbc_cnt=clock=cnt=0;
        cas++;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        //n个点的无向图最多有n-1个pbc 注意belong从下标0开始,因为点的编号是最小是0
        for(int i=0;i<n;i++){
            pbc[i].clear();
            belong[i].clear();
        }
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i]){
                id++;
                dfs(i,-1);
            }
        }
        printf("Case %d:\n",cas);
        while(q--){
            scanf("%d%d",&u,&v);
            if(vis[u]!=vis[v]){//不连通 没有独立资金链输出"zero"
                printf("zero\n");
                continue;
            }
            int flag=0;
            for(int &i : belong[u]){
                for(int &j : belong[v]){
                    if(i == j && pbc[i].size()>2){//u和v在同一pbc,且pbc中点个数>2,独立资金链才不止一条.
                        flag=1;
                        break;
                    }
                }
                if(flag) break;
            }
            if(!flag) printf("one\n");
            else printf("two or more\n");
        }
    }
    return 0;
}

/*
//3组输入测试数据
7 8 5
2 0
1 2
4 1
4 0
6 0
2 5
4 5
2 3
3 4
4 5
6 4
1 4
0 1

7 3 5
1 4
0 6
4 6
5 0
0 4
1 6
3 5
6 2

6 6 5
2 0
3 2
0 3
5 3
2 4
5 2
3 5
3 4
0 5
1 2
1 4
*/

/*
//ac 156ms vector判重+belong判断点是否处于同一pbc
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;

int n,m,q,dfn[N],low[N],clock,cnt,id,pbc_cnt,head[N],vis[N],block[N];
stack<pair<int,int> > s;
vector<int> pbc[N],belong[N];//belong[u]代表u所在pbc的编号集合

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    vis[u]=id;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                pair<int,int> tmp;
                pbc_cnt++;
                do{
                    tmp=s.top();
                    s.pop();
                    if(block[tmp.first]!=pbc_cnt){
                        pbc[pbc_cnt].push_back(tmp.first);
                        block[tmp.first]=pbc_cnt;
                        belong[tmp.first].push_back(pbc_cnt);
                    }
                    if(block[tmp.second]!=pbc_cnt){
                        pbc[pbc_cnt].push_back(tmp.second);
                        block[tmp.second]=pbc_cnt;
                        belong[tmp.second].push_back(pbc_cnt);
                    }
                }while(tmp.first!=u);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,cas=0;
    while(scanf("%d%d%d",&n,&m,&q) && n+m+q){
        id=pbc_cnt=clock=cnt=0;
        cas++;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        //n个点的无向图最多有n-1个pbc 注意belong从下标0开始,因为点的编号是最小是0
        for(int i=0;i<n;i++){
            pbc[i].clear();
            belong[i].clear();
        }
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i]){
                id++;
                dfs(i,-1);
            }
        }
        printf("Case %d:\n",cas);
        while(q--){
            scanf("%d%d",&u,&v);
            if(vis[u]!=vis[v]){//不连通 没有独立资金链输出"zero"
                printf("zero\n");
                continue;
            }
            int flag=0;
            for(int &i : belong[u]){
                for(int &j : belong[v]){
                    if(i == j && pbc[i].size()>2){//u和v在同一pbc,且pbc中点个数>2,独立资金链才不止一条.
                        flag=1;
                        break;
                    }
                }
                if(flag) break;
            }
            if(!flag) printf("one\n");
            else printf("two or more\n");
        }
    }
    return 0;
}
*/

/*
//ac 594ms set去重 查找
#include<cstdio>
#include<cstring>
#include<stack>
#include<set>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;

int n,m,q,dfn[N],low[N],clock,cnt,id,pbc_cnt,head[N],vis[N];
stack<pair<int,int> > s;
set<int> pbc[N];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    vis[u]=id;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                pair<int,int> tmp;
                pbc_cnt++;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc[pbc_cnt].insert(tmp.first);
                    pbc[pbc_cnt].insert(tmp.second);
                }while(tmp.first!=u);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,cas=0;
    while(scanf("%d%d%d",&n,&m,&q) && n+m+q){
        id=pbc_cnt=clock=cnt=0;
        cas++;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        //n个点的无向图最多有n-1个pbc
        for(int i=1;i<n;i++) pbc[i].clear();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i]){
                id++;
                dfs(i,-1);
            }
        }
        printf("Case %d:\n",cas);
        while(q--){
            scanf("%d%d",&u,&v);
            if(vis[u]!=vis[v]){
                printf("zero\n");
                continue;
            }
            int flag=0;
            for(int i=1;i<=pbc_cnt;i++){
                if(pbc[i].count(u) && pbc[i].count(v) && pbc[i].size()>2){
                    flag=1;
                    break;
                }
            }
            if(!flag) printf("one\n");
            else printf("two or more\n");
        }
    }
    return 0;
}
*/
