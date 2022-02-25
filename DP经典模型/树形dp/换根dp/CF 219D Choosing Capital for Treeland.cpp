#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define N 200010
using namespace std;

/*
����:һ��n���ڵ��������,��Ҫ����ĳ���ڵ�Ϊ�׶�,Ϊ���ܹ����׶��������нڵ�,���ܸ������Ҫ������,
����Ҫ�� ѡȡ��Щ����Ϊ�׶���ʹ�÷������������.
����:https://codeforces.ml/problemset/problem/219/D
˼·:�ڽ��ߵ��Ƿ��������߸�ֵ0,������Ҫ�ı�,���ڷ���߸�ֵ1,����Ҫ�ı�,��������ת������
ÿ���㶼�������Ȩֵ֮��.���յ�Ȩֵ֮�ʹ�����Ҫ�ı�ı���.
dp[i]������iΪ�׶�,��Ҫ�ı�ı���,��һ��dfs1����ڵ�1��Ϊ�׶�Ҫ�ı�ı���
�ڶ���dfs2()˳�����u���ӽڵ�v��Ϊ�׶�Ҫ�ı�ı���,vֻ��Ҫ��u�Ļ����ϸı�1���ߵ�����,
��Ҫ��dp[u]�Ļ����ϸı�u->v�ĵ���,���u->v������������,��dp[v]=dp[u]+1,��u->v�Ƿ����,��v->u���������,dp[v]=dp[u]-1
*/

int cnt,n,dp[N],head[N],ans=INF;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

//����1�ڵ���Ϊ�׶�Ҫ�ı�ı��� �ӽڵ��򸸽ڵ�ת��
void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        dp[u]+=dp[v]+edge[i].w;
    }
}

//����1�ڵ�֮��Ķ�����Ϊ�׶�Ҫ�ı�ı��� ���ڵ����ӽڵ�ת��
void dfs2(int u,int fa){
    if(dp[u]<ans) ans=dp[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(edge[i].w)//u->v�Ƿ��� ��ʱv->u���� ��dp[u]-1
            dp[v]=dp[u]-1;
        else//u->v���� v->u���� ��dp[u]+1
            dp[v]=dp[u]+1;
        dfs2(v,u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v,0);
        addEdge(v,u,1);
    }
    dfs1(1,-1);
    dfs2(1,-1);
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){
        if(dp[i] == ans)
            printf("%d ",i);
    }
    return 0;
}

