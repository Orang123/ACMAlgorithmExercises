#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define N 100010
using namespace std;

/*
����:����һ����n���ڵ�,����m����,�����еĵ���(������m����)ȷ����Щ�������m����ľ��붼������d
����:https://codeforces.ml/contest/337/problem/D
˼·:����dp
���Բο�HDU 2196����Ļ���dp,��ȡÿ��������m������Զ�ľ���
dp[u][0]����u����������m���������������.
dp[u][1]����u����������m���������δ����
dp[u][2]����u�����߹��ĸ��ڵ�����·������m����ķ���������
dp[u][0],dp[u][1]��������δ���������������һ������u�ڵ�
����ʱ��Ҫ��dp��ʼ��Ϊ������,Ȼ��m�����dp[u][0] dp[u][1]�������/�δ�����ʼ��Ϊ0,
����dfs1��ÿ��������Ĳ��Ǿ���m�����е�������
*/

int cnt,n,m,d,dp[N][3],head[N];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        //����u����m����,v������ʱ,dp[u][0]����0���ڸ��������� dp[u][1]ͬ��,����ʱ����¸��ڵ������m�����е�ľ���
        if(dp[u][0]<dp[v][0]+1){
            dp[u][1]=dp[u][0];
            dp[u][0]=dp[v][0]+1;
        }
        else if(dp[u][1]<dp[v][0]+1)
            dp[u][1]=dp[v][0]+1;
    }
}

void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        /*
        dp[v][2]�����ʼ��,��u��uǰ��Ľڵ㲻����m,dp[v][2]������µ��Ǹ�����,
        ��u����m,������ֻ��һ����֧·��,��ʱdp[u][1]��0,�ɸ��·������m�����·��.
        dp[v][2]��ͨ��dp[u][0] dp[u][1]  ȥת�Ƶ�,��ʹu��m�еĵ�,��һ��0Ҳ��ͨ��dp[u][1](0)ת��
        */
        if(dp[u][0] == dp[v][0]+1) dp[v][2]=max(dp[u][2],dp[u][1])+1;
        else dp[v][2]=max(dp[u][2],dp[u][0])+1;
        dfs2(v,u);
    }
}

int main(){
    int u,v,ans=0;
    memset(dp,-INF,sizeof(dp));
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&d);
    while(m--){
        scanf("%d",&v);
        dp[v][0]=dp[v][1]=0;
    }
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs1(1,-1);
    dfs2(1,-1);
    for(int i=1;i<=n;i++)
        ans+=max(dp[i][0],dp[i][2])<=d?1:0;
    printf("%d\n",ans);
    return 0;
}

