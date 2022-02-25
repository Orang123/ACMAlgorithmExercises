#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
typedef long long ll;

/*
����:����һ���޸���,��������n���ڵ�,�ڵ��Ŵ�1��n,
��1-n��n���ڵ�,������n-1���ڵ�ľ���֮��.
����:http://www.51nod.com/Challenge/Problem.html#problemId=1405
˼·:siz[u]������u�ڵ�Ϊ�������������нڵ����
������v��u�Ķ���,������֪dp[u],��ô��siz[v]���ڵ㵽v��ľ���ȵ�u��ľ�������1,
��n-siz[v]���ڵ㵽v�ڵ�ľ���ȵ�u�ڵ�ľ����1.����dp[v]=dp[u]-siz[v]+n-siz[v]
*/

ll dp[N],head[N],dep[N],siz[N],cnt,n;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

//����siz[u] dp[1] �̶�1�ڵ�Ϊ����dp[1]
void dfs1(int u,int fa){
    siz[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dep[v]=dep[u]+1;
        dp[1]+=dep[v];//�����������ڵ�ľ���Ϊ�������нڵ�����֮��
        dfs1(v,u);
        siz[u]+=siz[v];
    }
}
//��1�ڵ����ӽڵ�ת��,���ڵ��ٷֱ����ӽڵ�ת��
void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dp[v]=dp[u]-siz[v]+n-siz[v];
        dfs2(v,u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs1(1,-1);
    dfs2(1,-1);
    for(int i=1;i<=n;i++)
        printf("%lld\n",dp[i]);
    return 0;
}
