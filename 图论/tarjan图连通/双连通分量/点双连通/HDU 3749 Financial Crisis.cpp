#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;
//ac 156ms stackջ��� ���pbc�������ص�����
/*
����:n����ҵ,m���ʽ�����ɵĽ��ڽ��׹�ϵ����,���ͬһ���ʽ�����
��һ����ҵ�����Ʋ�,�����ֽ�������,��ô��֮��ص�������ҵҲ���ܵ�Ӱ��,
�������ʽ�����ָ���������������ҵ��ɵĵ�·,��������֮����ʽ���
��ϵ���й�ͬ�����s���յ�t,����s��t��,��������·��û���κ�һ��
��ҵͬʱ����������������·��,��������һ����ҵ��һ����·���Ʋ�,
��һ����ҵ���ʽ��������յ�Ӱ��,������q��ѯ��u v֮���м���������
�ʽ���,�������ͨ���"zero",�����ֻͨ��һ���������ʽ���,���"one",
�����2����2�������ʽ���,���"two or more".

����:����ͼ(���ر�),���u��v�Ƿ���ͬһ��˫��ͨ����,ע�����u��v��ͬһ��˫��ͨ������,
������Ԫ�ظ���ֻ��u��v����ʱ,��ô֮��Ķ����ʽ���Ҳֻ��Ψһ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3749
˼·:tarjan���pbc,��Ϊÿ������Դ������pbc,�����ڼ�¼pbcʱ,Ҫ��belong����
��¼ÿ����������pbc�ı��.
*/

int n,m,q,dfn[N],low[N],clock,cnt,id,pbc_cnt,head[N],vis[N];
stack<int> s;
vector<int> pbc[N],belong[N];//belong[u]����u����pbc�ı�ż���

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
        //n���������ͼ�����n-1��pbc ע��belong���±�0��ʼ,��Ϊ��ı������С��0
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
            if(vis[u]!=vis[v]){//����ͨ û�ж����ʽ������"zero"
                printf("zero\n");
                continue;
            }
            int flag=0;
            for(int &i : belong[u]){
                for(int &j : belong[v]){
                    if(i == j && pbc[i].size()>2){//u��v��ͬһpbc,��pbc�е����>2,�����ʽ����Ų�ֹһ��.
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
//3�������������
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
//ac 156ms vector����+belong�жϵ��Ƿ���ͬһpbc
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
vector<int> pbc[N],belong[N];//belong[u]����u����pbc�ı�ż���

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
        //n���������ͼ�����n-1��pbc ע��belong���±�0��ʼ,��Ϊ��ı������С��0
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
            if(vis[u]!=vis[v]){//����ͨ û�ж����ʽ������"zero"
                printf("zero\n");
                continue;
            }
            int flag=0;
            for(int &i : belong[u]){
                for(int &j : belong[v]){
                    if(i == j && pbc[i].size()>2){//u��v��ͬһpbc,��pbc�е����>2,�����ʽ����Ų�ֹһ��.
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
//ac 594ms setȥ�� ����
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
        //n���������ͼ�����n-1��pbc
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
