#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
typedef long long ll;

/*
����:����һ��n����������������ж���������Ϊż����·����·���ĳ���Ϊ�����ıߵ�������
x��y��y��x����Ϊͬһ��·����·����������յ㲻����ͬ��
Wannafly��ս��1����:https://ac.nowcoder.com/acm/contest/15#question
����:https://ac.nowcoder.com/acm/contest/15/A
˼·:
dp[u][0]�����u�ڵ�����������ڵ㹹��ż������·���ĸ���
dp[u][1]�����u�ڵ�����������ڵ㹹����������·���ĸ���
*/

ll dp[N][2],head[N],cnt,n,ans;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}


void dfs(int u,int fa){
    /*
    �������ȿ�ʼ ��Ҷ�ӽڵ�dp[u][0]=1,��Ϊ�� �����ĸ��ڵ��dp[u][1]=1,
    ������ڵ㽫����������ʱ,���ڵ���Ե�2���������ڵ㳤��Ϊ1�������˹��ɳ���Ϊ2��ż��·���ļ���dp[u][1]*dp[to][0]��һ����
    ��������ڵ�dp[u][0]=1,�������u->v�����ߵĳ���Ϊ1���Ժ�v�ڵ�������еļ�������·�����1��ż������·�� ��:����+1=ż��.
    */
    dp[u][0]=1;
    dp[u][1]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        /*
        dp[u][0]*dp[v][1]�����u�ڵ��Ѿ��������������г���Ϊż����·�������͵�ǰ����v�г���Ϊ�����ĸ������Ӷ��ɵĳ���Ϊż���ĸ���,
        ��Ϊu->v�ǳ���Ϊ1��·��,��ż��+(1+����)=ż��+ż��=ż��,����һ��ʼ������һ������vʱ,
        dp[u][0]=1,dp[u][0]*dp[v][1]���� u-v��v�о���v����Ϊ������·����ϳɳ���Ϊż����·��.
        ans�ۼӻὫ֮ǰ��������ÿ���������͵�ǰ����v�˷�ԭ�����һ��.
        dp[u][1]*dp[v][0]����ͬ��,��һ�������,u������������u->v1 u->V2��������Ϊ1�ı� v1->u->v2��ɵĳ���Ϊ2��ż��·��
        */
        ans+=dp[u][0]*dp[v][1];
        ans+=dp[u][1]*dp[v][0];
        dp[u][0]+=dp[v][1];//ż������·��������������·������u->v(1)������ת�ƶ���
        dp[u][1]+=dp[v][0];//��������·����������ż��·������u->v(1)������ת�ƶ���
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    printf("%lld",ans);
    return 0;
}
