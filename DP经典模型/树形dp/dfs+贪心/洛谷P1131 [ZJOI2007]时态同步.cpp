#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500010
using namespace std;
typedef long long ll;
//dfs+̰��
/*
����:һ��n���ڵ����,���ڵ�Ϊs,ÿ���߶���Ȩֵ,
����Ҫ��������Ҫ��ԭ�ȱ�Ȩ���������Ӷ���Ȩֵ����
ʹ�ôӸ��ڵ�(s)��������ÿ��Ҷ�ӽڵ��Ȩֵ�Ͷ�һ��.
����:https://www.luogu.com.cn/problem/P1131
˼·:Ҫ�����ӵ�Ȩֵ������,��ô����ȨֵӦ�ôӵ����Ͽ���,������ʹ������Ȩֵ�Ͷ���ͬ,
����������ڵ����ϵı�Ȩ,����Խ�����ڵ����֦�����Ĵ���Խ�١����Կ������ÿ�����ڵ�u������Ȩֵ�����,
Ȼ������������������Ȩֵ����ۼ�,����u�ڵ��ÿ������Ȩֵ�;Ͷ���һ������,
�´ε���ʱֻ��Ҫ�������u�ڵ����ϵı�Ȩ,����������Ȩ�;Ͷ�������,�������ӵ�Ȩֵ������С��.
*/
//dis[u]��ʾҶ�ӽڵ㵽u�ڵ�����Ȩ��
int cnt,n,head[N],dis[N];
ll ans;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //���Ҷ�ӽڵ㵽u�ڵ�����Ȩ��
        dis[u]=max(dis[u],dis[v]+edge[i].w);
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //������������С������Ȩ����Ҫ���ӱ�Ȩ,����
        ans+=dis[u]-dis[v]-edge[i].w;
    }
}

int main(){
    int n,s,u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&s);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dfs(s,-1);
    printf("%lld",ans);
    return 0;
}
