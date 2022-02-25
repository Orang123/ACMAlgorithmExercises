#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define M 1000100
using namespace std;
//ac 172ms
/*
����:������ͼ�еı߸�Ϊ�����,ʹ������ͼ����������֮���Ծ�
��ͨ�໥�ɴ�,���ڵ����ֻ����䷽��ߵ����˵�,���ڱ�����˫���
��ͬʱ���������������Ķ˵�.ԭͼ��֤��ͨ.
����:http://poj.org/problem?id=1515
˼·:��Ȼ,ֻ��ԭͼ���ڻ���ı߲ű�����˫���,��ô������.
ʣ�µĵ����ʵ�ʽ���ǲ�Ψһ��,�Ͱ���tarjan dfs����һ������ͺ�,
��Ϊֻ�ǽ�ԭ�ȵ�2������ֻ��������һ������,������ɾ��ĳ����.
���Ծ���tarjan����.
*/
int n,m,dfn[N],low[N],clock,cnt,head[N],cas;

struct Edge{
    int from,to,next,flag;
}edge[M];

void addEdge(int from,int to,int flag){
    edge[cnt]=(Edge){from,to,head[from],flag};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(edge[i].flag!=-1) continue;//�����Ϊ-1 ˵������ߵķ���֮ǰ�Ѿ�ȷ����
        edge[i].flag=1;//��ǵ�ǰ��ʽΪҪ����������߷���
        edge[i^1].flag=0;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                edge[i^1].flag=1;//���ڸ�� ��ô����2������Ҫ����,edge[i]֮ǰ�Ѿ���ǹ���.
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    cas++;
    clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v,-1);//-1���������ߵķ���δȷ��
            addEdge(v,u,-1);
        }
        dfs(1,-1);//ԭͼ��֤����ͨ��.
        printf("%d\n\n",cas);
        for(int i=0;i<cnt;i++){
            if(edge[i].flag)
                printf("%d %d\n",edge[i].from,edge[i].to);
        }
        printf("#\n");
    }
    return 0;
}
