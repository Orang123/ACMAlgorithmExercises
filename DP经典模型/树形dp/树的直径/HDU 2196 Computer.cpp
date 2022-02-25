#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
using namespace std;

/*
����:���һ�����ϸ����ڵ���������ڵ����Զ����
����:http://acm.hdu.edu.cn/showproblem.php?pid=2196
˼·:����ĳ���ڵ���������ڵ���Զ�ĵ�һ������Ⱦ�������ֱ���������˵㻹Զ,���
���������ֱ��,���������������ֱ�����˵�ľ���,��ȡ�������˵�����ֵ��Ϊ���.
Ҳ������dp������/�δ�����Լ����������������
*/
int cnt,n,head[N],dis1[N],dis2[N],ans,st;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    if(dis1[u]>ans){
        st=u;
        ans=dis1[u];
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis1[v]=dis1[u]+edge[i].w;
        dfs(v,u);
    }
}

int main(){
    int v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=2;i<=n;i++){
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
            addEdge(v,i,w);
        }
        ans=-1;
        dfs(1,-1);
        dis1[st]=0;
        ans=-1;
        dfs(st,-1);
        for(int i=1;i<=n;i++) dis2[i]=dis1[i];//dis2��¼����ֱ����һ������Ķ˵�ľ���
        dis1[st]=0;
        dfs(st,-1);//dis1��¼����ֱ���ڶ�������Ķ˵�ľ���
        for(int i=1;i<=n;i++)
            printf("%d\n",max(dis1[i],dis2[i]));//���ֱ�����˵��������ֵ
    }
    return 0;
}

/*
//ֻ��һ��dis���� ��¼�������˵�����ֵ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
using namespace std;


int cnt,n,head[N],dis[N],ans,st;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//sum�����st������������ߵ�Ȩֵ��
void dfs(int u,int fa,int sum){
    if(sum>ans){
        st=u;
        ans=sum;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=max(dis[v],sum+edge[i].w);//dis[v]ȡ����ֱ�����˵��������
        dfs(v,u,sum+edge[i].w);
    }
}

int main(){
    int v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(dis,0,sizeof(dis));
        memset(head,-1,sizeof(head));
        for(int i=2;i<=n;i++){
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
            addEdge(v,i,w);
        }
        ans=-1;
        dfs(1,-1,0);
        ans=-1;//����ֱ��Ȩֵ��û��֮ǰ��,����¼����ֱ������һ�˵�
        dfs(st,-1,0);
        dfs(st,-1,0);
        for(int i=1;i<=n;i++)
            printf("%d\n",dis[i]);
    }
    return 0;
}
*/
