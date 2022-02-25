#include<cstdio>
#include<cmath>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 20010
#define INF 0x3f3f3f3f
using namespace std;
//ac 171ms tarjan���ebc����+����dp
/*
����:n������,ÿ�����Ҷ���һ������,������m��ͨ���ܵ������н���
��ͨ����������������һ������Ⱥ,�����������Ⱥ���Ѿ���һ���յ�,
����Ҫ���һ��ͨ����ʹ�ý���Ⱥ�ָ����������Ⱥ,����һ������Ⱥ
���ٷ���һ���յ�,Ϊʹ�ô�ҵ����������������Ⱥ��������Ӧ������
����,������������,�����С��������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2242
˼·:��ȻҪ�жϵ�ͨ���ܱ�������,����ԭ����Ⱥ�е�ebc����û���ŵ�,
��ôtarjan���ebc��ebc�����������㹹��������,�����Ͻ�������dp
���������Ȩ�ۼӺ�,��������С��ֵ.
*/
int n,m,dfn[N],low[N],clock,cnt,block[N],ebc_cnt,head[N],num[N],dp[N],ans,sum;
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if((i^1) == fa) continue;
        if(!dfn[v]){
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
            block[v]=ebc_cnt;
            dp[ebc_cnt]+=num[v];
        }while(v!=u);
    }
}

void dfs(int u,int fa){
    for(int &v : G[u]){
        if(v == fa) continue;
        dfs(v,u);
        dp[u]+=dp[v];
    }
    ans=min(ans,abs(sum-2*dp[u]));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        sum=ebc_cnt=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(dp,0,sizeof(dp));
        memset(dfn,0,sizeof(dfn));
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=0;i<n;i++){
            scanf("%d",&num[i]);
            sum+=num[i];
        }
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        tarjan(0,-1);
        if(ebc_cnt == 1){
            printf("impossible\n");
            continue;
        }
        for(int i=0;i<cnt;i+=2){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                G[block[u]].push_back(block[v]);
                G[block[v]].push_back(block[u]);
            }
        }
        ans=INF;
        dfs(1,-1);
        printf("%d\n",ans);
    }
    return 0;
}
