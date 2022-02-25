#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 1100
#define M 2100
using namespace std;
//ac 187ms
/*
����:n����ϵ��,ÿ���˿����������˵���ϵ��ʽ,����Wiskey��������Ҫ
֪ͨ������,��֪��֪ͨÿ���˵ĵ绰����,Wiskey����ÿ���˶�֪ͨ,֪ͨ��
���˿���ȥ֪ͨ�����,��Wiskey����Ҫ֪ͨ����,�Լ����ٻ��ѵĵ绰��.
ע��:��ϵ��ʽ�ǵ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1827
˼·:���tarjan�������scc�е���СȨֵ�ۼӺ�.

��չ:�����ϵ��ʽ�ǵ����,Ҳ�����ò��鼯��,��������ϵ��ʽ������˫��
tarjan���scc������������ǿ��е�.��������������ò��鼯��,һ��Ҳһ����
����tarjan���scc����.����tarjanЧ��Ҫ�ϸ�Щ.
*/

int n,m,dfn[N],low[N],val[N],clock,cnt,block[N],cost[N],id,head[N],inde[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
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
            cost[id]=min(cost[id],val[v]);
        }while(v!=u);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(cost,0x3f,sizeof(cost));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])
                inde[block[v]]++;
        }
        int ans=0,sum=0;
        for(int i=1;i<=id;i++){
            if(!inde[i]){
                ans++;
                sum+=cost[i];
            }
        }
        printf("%d %d\n",ans,sum);
    }
    return 0;
}
