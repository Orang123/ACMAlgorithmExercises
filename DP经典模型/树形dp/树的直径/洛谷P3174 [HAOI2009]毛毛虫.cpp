#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300100
using namespace std;

/*
����:һ��n���ڵ����,���һ����ʹ�ù����������ĵ��Լ���������ֱ�������ĵ�(ֻ��һ��������)�������
����:https://www.luogu.com.cn/problem/P3174
˼·:���Բ�������ֱ����˼άȥ��,ֻ��������ά������ĳ�����ϵĽڵ��ĳ������ֱ�������Ľڵ����,
������ĸ���,��������dfs�ֱ�����������˵�.

*/
//son[u]��¼u�ڵ�ֱ�������ż����ڵ�
int cnt,n,m,head[N],son[N],ans,st;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int sum){
    if(sum>ans){
        ans=sum;
        st=u;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u,sum+son[v]-1);//son[v]��Ὣu�ڵ��ظ���һ��,v�ڵ㱾���Ѿ���son[u]��������
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
        son[u]++;
        son[v]++;
    }
    dfs(1,-1,1+son[1]);//1����ʼ�ڵ� son[1]/son[st]����ʼ�ڵ������˼����ڵ�
    dfs(st,-1,1+son[st]);
    printf("%d",ans);
    return 0;
}

/*
����dp �������ʹγ����������ֱ��
#include <iostream>
#include <cstdio>
using namespace std;
#define N 300050
int n,m,d[N],head[N],son[N],num,ans;
struct node
{
    int next,to;
}tree[N*2];
void addedge(int u,int v)
{
    tree[++num]=(node){head[u],v};
    head[u]=num;
    son[v]++;
}
void dfs(int x,int fa)
{
    d[x]=1;
    int maxx=1,minn=1;
    for(int i=head[x];i;i=tree[i].next)
    {
        int y=tree[i].to;
        if(y==fa)continue;
        dfs(y,x);
        if(d[y]>maxx){minn=maxx;maxx=d[y];}
        else if(d[y]>minn){minn=d[y];}
        d[x]=max(d[x],d[y]+son[x]-1);
    }
    ans=max(maxx+minn+son[x]-1,ans);
}
int main()
{
    scanf("%d%d",&n,&m);
    int u,v;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        addedge(u,v);addedge(v,u);
    }
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/
