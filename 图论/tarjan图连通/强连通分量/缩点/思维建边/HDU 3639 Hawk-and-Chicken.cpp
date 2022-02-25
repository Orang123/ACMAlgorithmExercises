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
题意:n个人参与投票,有m条投票的单向关系,u->v代表u将投票给v,
最终获得投票最多的人获胜,请按升序输出获得投票最多的人编号.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3639
思路:对于DAG来说,获得前驱祖先节点(获得投票数)最多的一定是在出度为0的点.
那么我们就可以从出度为0的点进行树形dp,求解每个出度为0的点前驱祖先节点的个数,
所以需要反向建边转换成以u为根节点的儿子的个数,
但是要注意某个点的入度可能>1,这样直接累加会重复累加导致结果偏大,
要做上标记,对于已访问过的点就不能再累加.首先tarjan求解出scc和scc中节点个数,
后缩点反向建边建立DAG,反向建边是因为u->v u是投给v票,
那么反向建边后从入度为0的点进行树形dp注意儿子节点只能加一次.

拓扑排序无法解决这个问题,因为无法避免路径中节点重复累加的问题.
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
    dp[u]=amout[u];//dp[u] 代表以u为根节点 投票给u的所有子节点的个数,子节点不会重复.
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){//v节点如果已经加过就不再累加.
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
                //每次都要初始化vis,不然之前入度为0的根节点遍历完后,当前点有些儿子就会错误以为已经累加过了.
                memset(vis,0,sizeof(vis));
                dfs(i);
                dp[i]--;//这个scc里有很多节点 节点本身不算入投票数,因为自己不能投给自己.
                a[i]=dp[i];
                ans=max(ans,dp[i]);
            }
        }
        printf("Case %d: %d\n",cas,ans);
        int flag=0;
        //直接按顺序输出获得投票最多的节点编号
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
一组考察是否会重复累加儿子的数据
1
6 6
0 1
0 2
1 5
1 3
2 3
2 4

输出应该是
3 3
*/

/*
//ac 343ms
//vector 排序
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
