#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#define N 5100
#define M 30100
using namespace std;
//ac 343ms
/*
����:n���˲���ͶƱ,��m��ͶƱ�ĵ����ϵ,u->v����u��ͶƱ��v,
���ջ��ͶƱ�����˻�ʤ,�밴����������ͶƱ�����˱��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3639
˼·:����DAG��˵,���ǰ�����Ƚڵ�(���ͶƱ��)����һ�����ڳ���Ϊ0�ĵ�.
��ô���ǾͿ��Դӳ���Ϊ0�ĵ��������dp,���ÿ������Ϊ0�ĵ�ǰ�����Ƚڵ�ĸ���,
������Ҫ���򽨱�ת������uΪ���ڵ�Ķ��ӵĸ���,
����Ҫע��ĳ�������ȿ���>1,����ֱ���ۼӻ��ظ��ۼӵ��½��ƫ��,
Ҫ���ϱ��,�����ѷ��ʹ��ĵ�Ͳ������ۼ�.����tarjan����scc��scc�нڵ����,
�����㷴�򽨱߽���DAG,���򽨱�����Ϊu->v u��Ͷ��vƱ,
��ô���򽨱ߺ�����Ϊ0�ĵ��������dpע����ӽڵ�ֻ�ܼ�һ��.

���������޷�����������,��Ϊ�޷�����·���нڵ��ظ��ۼӵ�����.
*/

int n,m,head1[N],cnt1,head2[N],cnt2;
int dfn[N],low[N],in[N],num,scc_cnt,block[N],inde[N],amout[N],dp[N],vis[N],ans,a[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge1[M],edge2[M];

void addEdge1(int from,int to){
    edge1[cnt1]=(Edge){from,to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Edge){from,to,head2[from]};
    head2[from]=cnt2++;
}

void tarjan(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        v=edge1[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        scc_cnt++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            amout[scc_cnt]++;
            block[v]=scc_cnt;
        }while(v!=u);
    }
}


void dfs(int u){
    vis[u]=1;
    dp[u]=amout[u];//dp[u] ������uΪ���ڵ� ͶƱ��u�������ӽڵ�ĸ���,�ӽڵ㲻���ظ�.
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){//v�ڵ�����Ѿ��ӹ��Ͳ����ۼ�.
            dfs(v);
            dp[u]+=dp[v];
        }
    }
}


int main(){
    int T,u,v,cas=0;
    scanf("%d",&T);
    while(T--){
        scc_cnt=ans=num=cnt1=cnt2=0;
        memset(head1,-1,sizeof(head1));
        memset(head2,-1,sizeof(head2));
        memset(amout,0,sizeof(amout));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(a,0,sizeof(a));
        cas++;
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge1(u,v);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=0;i<cnt1;i++){
            u=edge1[i].from;
            v=edge1[i].to;
            if(block[u]!=block[v]){
                inde[block[u]]++;
                addEdge2(block[v],block[u]);
            }
        }
        for(int i=1;i<=scc_cnt;i++){
            if(!inde[i]){
                //ÿ�ζ�Ҫ��ʼ��vis,��Ȼ֮ǰ���Ϊ0�ĸ��ڵ�������,��ǰ����Щ���Ӿͻ������Ϊ�Ѿ��ۼӹ���.
                memset(vis,0,sizeof(vis));
                dfs(i);
                dp[i]--;//���scc���кܶ�ڵ� �ڵ㱾������ͶƱ��,��Ϊ�Լ�����Ͷ���Լ�.
                a[i]=dp[i];
                ans=max(ans,dp[i]);
            }
        }
        printf("Case %d: %d\n",cas,ans);
        int flag=0;
        //ֱ�Ӱ�˳��������ͶƱ���Ľڵ���
        for(int i=0;i<n;i++){
            if(a[block[i]] == ans){
                if(!flag){
                    flag=1;
                    printf("%d",i);
                }
                else
                    printf(" %d",i);
            }
        }
        printf("\n");
    }
    return 0;
}
/*
һ�鿼���Ƿ���ظ��ۼӶ��ӵ�����
1
6 6
0 1
0 2
1 5
1 3
2 3
2 4

���Ӧ����
3 3
*/

/*
//ac 343ms
//vector ����
#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#define N 5100
#define M 30100
using namespace std;

int n,m,head1[N],cnt1,head2[N],cnt2;
int dfn[N],low[N],in[N],num,scc_cnt,block[N],inde[N],amout[N],dp[N],vis[N],ans;
stack<int> s;
vector<int> seq;

struct Edge{
    int from,to,next;
}edge1[M],edge2[M];

void addEdge1(int from,int to){
    edge1[cnt1]=(Edge){from,to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Edge){from,to,head2[from]};
    head2[from]=cnt2++;
}

void tarjan(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        v=edge1[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        scc_cnt++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            amout[scc_cnt]++;
            block[v]=scc_cnt;
        }while(v!=u);
    }
}


void dfs(int u){
    vis[u]=1;
    dp[u]=amout[u];
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            dfs(v);
            dp[u]+=dp[v];
        }
    }
}


int main(){
    int T,u,v,cas=0;
    scanf("%d",&T);
    while(T--){
        scc_cnt=ans=num=cnt1=cnt2=0;
        seq.clear();
        memset(head1,-1,sizeof(head1));
        memset(head2,-1,sizeof(head2));
        memset(amout,0,sizeof(amout));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        cas++;
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge1(u,v);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=0;i<cnt1;i++){
            u=edge1[i].from;
            v=edge1[i].to;
            if(block[u]!=block[v]){
                inde[block[u]]++;
                addEdge2(block[v],block[u]);
            }
        }
        for(int i=1;i<=scc_cnt;i++){
            if(!inde[i]){
                memset(vis,0,sizeof(vis));
                dfs(i);
                dp[i]--;
                ans=max(ans,dp[i]);
            }
        }
        for(int i=1;i<=scc_cnt;i++){
            if(!inde[i] && dp[i] == ans){
                for(int j=0;j<n;j++){
                    if(block[j] == i)
                        seq.push_back(j);
                }
            }
        }
        sort(seq.begin(),seq.end());
        printf("Case %d: %d\n",cas,ans);
        int flag=0;
        for(int &e:seq){
            if(!flag){
                flag=1;
                printf("%d",e);
            }
            else
                printf(" %d",e);
        }
        printf("\n");
    }
    return 0;
}
*/
