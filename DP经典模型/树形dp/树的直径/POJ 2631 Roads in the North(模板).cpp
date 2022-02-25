#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
//��������
/*
����:���һ���������˵���Զ�ľ���,������ֱ��
����:http://poj.org/problem?id=2631
˼·:����dfs,��һ��dfs�����Ӹ��ڵ�u���������ߵ��ĵ�Դ�����,���Ҽ�¼����������յ�v.
�ڶ���dfs�������յ�v��ʼ�ĵ�Դ�����,�������뼴������ֱ��.
����ֱ������:Ҳ���������������Ϊһ��������Զ�������ڵ��·����������һ�����ظ�����ĳһ���ߵ����·��
����ֱ��֤��:https://blog.csdn.net/forever_dreams/article/details/81051578
floydʱ��Ϳռ��϶����س���,����O(N^3) ��N=10^4,�ռ�������Ҳ���10^6,�����ڿռ俪��Ϊ10^4*10^4=10^8
*/

int cnt,n,head[N],dis[N],ans,st;
//int pre[N];��¼����ֱ���ľ���·��

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//O(V+E) bfsҲ��
void dfs(int u,int fa){
    if(dis[u]>ans){
        ans=dis[u];
        st=u;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=dis[u]+edge[i].w;
        //pre[v]=u;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    while(scanf("%d%d%d",&u,&v,&w)!=EOF){
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    ans=-1;
    dfs(1,-1);
    dis[st]=0;//�ٴӵ�һ�ε�Դ�·�����յ㿪ʼ����,��˳�ʼֵΪ0
    memset(pre,-1,sizeof(pre));
    dfs(st,-1);
    printf("%d",ans);
    /*
    while(st!=-1){
        printf("%d ",st);
        st=pre[st];
    }
    */
    return 0;
}

/*
//����dp���  ������·���Ƚ��鷳 ��Ϊֱ��������·������,���·���ʹδ�·��ƴ�Ӷ��ɵ�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
//dp[u][0]����������Ҷ�ӽڵ����u�ڵ��������
//dp[u][1]����������Ҷ�ӽڵ����u�ڵ�Ĵδ����
int cnt,n,head[N],dp[N][2],ans,st;

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
        //����������
        if(dp[u][0]<dp[v][0]+edge[i].w){
            dp[u][1]=dp[u][0];//��ǰ����������ɴδ����
            dp[u][0]=dp[v][0]+edge[i].w;
        }
        else if(dp[u][1]<dp[v][0]+edge[i].w)//���Ǹ��´δ����
            dp[u][1]=dp[v][0]+edge[i].w;
    }
    //���·�����ǲ�ͬ��������u�����������δ����֮��,���������ڵ���������֮�͵����ֵ��������ֱ��
    //���ﲻ�ؿ��Ǹ��ڵ����ϵķ������,��Ϊ���Ÿ��ڵ㲻�ϻ���,���ϵķ������ͻ����������븸�ڵ�ľ���
    ans=max(ans,dp[u][0]+dp[u][1]);
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    while(scanf("%d%d%d",&u,&v,&w)!=EOF){
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    ans=-1;
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/

/*
��һ������dp ��֪Ϊ��wa
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
//dp[u]����������Ҷ�ӽڵ����u�ڵ���Զ����
int cnt,n,head[N],dp[N],ans,st;

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
        //���ǵ�ǰdp[u](����u�ڵ��������)������������֧��������֮�� �������ڵ������͵����ֵ��������ֱ��
        //dp[v]+edge[i].w�п��ܱ�dp[u]����,��ʱdp[u]�ͱ�Ϊ�δ����,Ҳ���Ǵδ����+������
        ans=max(ans,dp[u]+dp[v]+edge[i].w);
        //����������Ҷ�ӽڵ����u�ڵ��������
        dp[u]=max(dp[u],dp[v]+edge[i].w);
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    while(scanf("%d%d%d",&u,&v,&w)!=EOF){
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    ans=-1;
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/
