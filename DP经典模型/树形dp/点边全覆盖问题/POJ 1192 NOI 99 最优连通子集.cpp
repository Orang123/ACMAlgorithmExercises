#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
using namespace std;

/*
����:��������������Ȩֵ�͵����ֵ
����:http://poj.org/problem?id=1192
˼·:
dp[u][0]������uΪ���ڵ������������u�ڵ��Ȩֵ����
dp[u][1]������uΪ���ڵ����������u�ڵ��Ȩֵ����
*/

int dp[N][2],head[N],a[N],b[N],val[N],cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//O(V+E)
void dfs(int u,int fa){
    dp[u][0]=0;
    dp[u][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        /*
        ����ѡu�ڵ�Ȩֵ,��ѡ��u�ڵ�������Ȩֵ�ͽϴ��������Ϊdp[u][0]��ֵ,
        ����ĳ�������е�v�� ����ѡҲ���ܲ�ѡ,��֮��ѡȡȨֵ�ϴ�����
        */
        dp[u][0]=max(dp[u][0],max(dp[v][0],dp[v][1]));
        /*
        ��ѡ��u�ڵ�Ȩֵ,��ô����������Ȩֵ��ֻҪ��С��0�򶼼���,��dp[v][1]С��0,
        ��dp[u][1]����dp[v][1]�������.
        */
        dp[u][1]+=max(dp[v][1],0);
    }
}

int main(){
    int n;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i],&b[i],&val[i]);
    //i��j=i+1��ʼ�Ƚ���Ϊ�˱���2�ڵ�֮���ظ�����
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(abs(a[i]-a[j])+abs(b[i]-b[j]) == 1){//���������Ͳ�����1�ĵ�֮������
                addEdge(i,j);
                addEdge(j,i);
            }
        }
    }
    dfs(1,-1);
    printf("%d",max(dp[1][0],dp[1][1]));
    return 0;
}

/*
��������������,�����ܶ��ÿ���ڵ��Ȩֵ,��ȡ���Ȩֵ��
��������������кͲ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define INF -0x3f3f3f3f
using namespace std;

int dp[N],head[N],a[N],b[N],cnt,ans=INF;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        dp[u]+=max(dp[v],0);//ֻҪ����Ȩֵ�Ͳ�Ϊ���ͼ���
    }
    //��¼��ÿһ���ڵ�Ϊ���ڵ������Ȩֵ�͵����ֵ ʵ�ʸ��ڵ���ܲ�һ�����ӽڵ�Ϊ��������Ȩֵ�ʹ�,��Ϊ���ڵ㱾��Ȩֵ�����Ǹ�����С
    ans=max(ans,dp[u]);
}

int main(){
    int n;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i],&b[i],&dp[i]);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(abs(a[i]-a[j])+abs(b[i]-b[j]) == 1){
                addEdge(i,j);
                addEdge(j,i);
            }
        }
    }
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/
