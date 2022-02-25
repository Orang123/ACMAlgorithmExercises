#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//ac 421ms
/*
����:һ���˴�0�������1~n-1�㴫����Ϣ,��m�����򴫵ݹ�ϵ
(���㴫����),���a->b,b->c,��ô�͵�ͬ��a����Ϣ���ݸ�c,
ÿ�����ݹ�ϵ����һ������w,��������˿��Ի��ഫ����Ϣ,
����ͬһ��֧(ͬһǿ��ͨ����),��ô���Ǵ�����Ϣ����Ҫ����.
����������˴�0��Ҫ����Ϣ���ݸ�ʣ��������,���ٵĻ���.
�����ϵ��֤�����һ���ܴ�0�㽫��Ϣ���ݸ�������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3072
˼·:����ͬһ�����ݻ��е����໥������Ϣ����Ҫ����,����
tarjan����scc֮������,��¼������ߵ���С��Ȩ,Ȼ���ۼ�
ÿ��������ߵ���С��Ȩ���Ǵ�.
�е������ڹ���DAG�ϵ���С��
*/
//ans[i] ������i����ߵ���С����
int n,m,dfn[N],low[N],in[N],num,head[N],cnt,scc_cnt,block[N],ans[N];
stack<int> s;

struct Edge{
    int from,to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
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
            block[v]=scc_cnt;
        }while(v!=u);
    }
}

int main(){
    int u,v,w,sum;
    while(scanf("%d%d",&n,&m)!=EOF){
        sum=num=cnt=0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(ans,0x3f,sizeof(ans));
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])//�е������ڹ���DAG�ϵ���С��
                ans[block[v]]=min(ans[block[v]],edge[i].w);//��¼����󵽴�õ���ߵ���С����.
        }
        for(int i=1;i<=scc_cnt;i++){
            if(ans[i]!=INF)//0�����ڵ�scc���һ��Ϊ0,ansһ����INF ���ۼ�
                sum+=ans[i];
        }
        printf("%d\n",sum);
    }
    return 0;
}
