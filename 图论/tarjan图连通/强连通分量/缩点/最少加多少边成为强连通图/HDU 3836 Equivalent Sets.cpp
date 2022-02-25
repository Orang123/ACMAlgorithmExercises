#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 20100
#define M 50010
using namespace std;
//ac 156ms
/*
����:n������,A->B,������A�Ǽ���B���Ӽ�,�����������֤��B->A,
��ô����BҲ�Ǽ���A���Ӽ�,��ô��˵����A��B�ǵȼ۵�,������m�������Ĺ�ϵ,
�����֤��n�������໥�ȼ����ٻ���Ҫ֤��������ϵ.
����:������ͼת��Ϊǿ��ͨͼ����Ҫ�ӵı���
����:http://acm.hdu.edu.cn/showproblem.php?pid=3836
˼·:tarjan���scc�����,���Ϊ0�ĵ�ͳ���Ϊ0������ֵ,
����ԭͼ�������ǿ��ͨͼ,Ҫ�������0.
*/

int n,m,dfn[N],low[N],clock,cnt,block[N],id,head[N],inde[N],outde[N];
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
        memset(outde,0,sizeof(outde));
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        if(id == 1){
            printf("0\n");
            continue;
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                inde[block[v]]++;
                outde[block[u]]++;
            }
        }
        int ans1=0,ans2=0;
        for(int i=1;i<=id;i++){
            if(!inde[i]) ans1++;
            if(!outde[i]) ans2++;
        }
        printf("%d\n",max(ans1,ans2));
    }
    return 0;
}
