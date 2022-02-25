#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 200100
using namespace std;
//ac 670ms
/*
����:n̨�����֮����m����·����ʹ��ֱ�ӻ�����������,
�������ݲ���ͨ����·�����������������ת��,�г�ĳЩ��·�ᵼ��,
�������������޷�ת��,����������·��������,������q���µ�����Ҫ��������,
���ÿ���һ���µ����Ӻ����ŵ���Ŀ.
����:������n����m���ߵ�����ͼ��,ÿ���һ���ߺ����ʣ�ĸ�ߵ���Ŀ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2460
˼·:tarjan�����.����dfs�м�¼ÿ���ڵ��ǰ���ڵ�,�����һ���±�ʱ,
ͨ��ǰ���ڵ���ǰ����u��v��lca(u,v)���ɵĻ��м�����ĸ��,�������,
ֱ��dfn[u]==dfn[v]ʱ,Ҳ����u==vʱ,����.�����뱶�����lca���Ǹ�����.
�ͱ�׼���ϱ���lca��ͬ����,���ϱ���lca�ǻ�������ͬһ�߶�,Ȼ����ͬʱ����lca;
������������u��v�ǲ���ͬʱ��������,��������αض���һ���ڵ�������lca(u,v),
��һ���ڵ�������lca,Ҳ�п���v��u��ͬһ��֧,��ôdfn�ϴ��,
ֻ��һ��������dfn��С����һ���ڵ㼴��.
*/

int dfn[N],low[N],num,head[N],cnt,pre[N],n,m,ans,vis[N];
struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            pre[v]=u;//��¼�л�����ͼ��v��ǰ���ڵ�,��Ϊ����dfsÿ���ڵ�Ҳֻ�����һ��,
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v]){
                ans++;//�����+1
                vis[v]=1;//�����v��Ϊ�˵�ı��Ǹ��.��ΪҪ��⻷�еı�,��Ҫ�������������еı�,���Ա��edge[i]�ߵ��±�i�޷���������
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);//Ҳ������low[u]=min(low[u],low[v])
    }
}

void lca(int u,int v){
    //����̶�dfn[u]>dfn[v],�����պõ�һ��ѭ������u��ǰ�����dfn[u]<dfn[v]ʱ,
    //�ٽ���ѭ������v��ǰ��ʹ��dfn[v]==dfn[u],������Ҫ��������ʱ,��һ��ѭ��������,
    //ֻ�����ڶ���ѭ��,��û��ʹ��u==v����lca(u,v)
    if(dfn[u]<dfn[v]) swap(u,v);
    /*
    dfn[u]>dfn[v]ʱ,˵��u�ڵ����ڱ�������v�ڵ���ݵ�u��v��lca��,�ſ�ʼ����u�ڵ����ڵķ�֧�Ľڵ�,
    ��ô��u��v�ڵ��lca(u,v)=x,��x-u���·���е����нڵ�y��dfn[y]���Ǵ���dfn[v]��,
    ��Ϊtarjan�������dfs������ȱ�����.�����������v���u������һ����֧,��ôu
    һ��������lca(u,v)��ֹͣ,Ȼ���¸�ѭ��v����������lca(u,v),�ͱ�׼���ϱ���lca��ͬ
    ����,���ϱ���lca�ǻ�������ͬһ�߶�,Ȼ����ͬʱ����lca;������������u��v�ǲ���ͬʱ
    ��������,��������αض���һ���ڵ�������lca(u,v),��һ���ڵ�������lca,Ҳ�п���v��
    u��ͬһ��֧,��ôdfn�ϴ��,ֻ��һ��������dfn��С����һ���ڵ㼴��.
    */
    while(dfn[u]>dfn[v]){
        if(vis[u]){
            ans--;
            vis[u]=0;
        }
        u=pre[u];
    }
    while(dfn[v]>dfn[u]){
        if(vis[v]){
            ans--;
            vis[v]=0;
        }
        v=pre[v];
    }
}

int main(){
    int u,v,q,cas=0;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        ans=num=cnt=0;
        memset(dfn,0,sizeof(dfn));
        memset(vis,0,sizeof vis);
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        scanf("%d",&q);
        printf("Case %d:\n",cas);
        while(q--){
            scanf("%d%d",&u,&v);
            lca(u,v);
            printf("%d\n",ans);
        }
        printf("\n");
    }
    return 0;
}
