#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

/*
����:����һ��n�������,���Ȩ,����ÿ���ڵ����������������k�����нڵ�Ȩֵ��m.
����:https://www.luogu.com.cn/problem/P3047
˼·:����dp+�ݳ�ԭ��
dp[u][k]�������u�ڵ�Ϊ����k�ĵ��Ȩֵ��.
����dfs,dfs1���ÿ���ڵ�������������ڵ��Ȩֵ��
dfs2�ɸ��ڵ����ӽڵ�ת��,��ÿ���ڵ����Ϸ�������游�ڵ��еĵ�Ȩ�ۼӸ���.
*/

int cnt,n,k,head[N],dp[N][25],ans;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

//���ÿ���ڵ�������������ڵ��Ȩֵ��
void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        //���ӽڵ��򸸽ڵ�ת��,��ͬ�ĵ���븸�ڵ�k,�����ӽڵ����k-1
        for(int j=1;j<=k;j++)
            dp[u][j]+=dp[v][j-1];
    }
}

//�ɸ��ڵ����ӽڵ�ת��,��ÿ���ڵ����Ϸ�������游�ڵ��еĵ�Ȩ�ۼӸ���.
void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        /*
        ��������ظ�ֵ���뵹��,����2-0 4-2 ��������ò�����,
        �½���2,dp[v][1]�ӵ���u���׵ĵ�Ȩ,�ǲ����ظ��ۼӵ�.
        */
        for(int j=k;j>=2;j--)
            dp[v][j]-=dp[v][j-2];
        /*
        u->v֮�䱾�����Ϊ1,Ҫ����v�游���Ͼ���v����Ϊk�ĵ�Ȩ��,��Ϊu��v֮�䱾������1,
        ����ת��Ϊ�ۼӾ��븸�ڵ�u����Ϊk-1�ĵ�Ȩ��,���ֵ��dfs1����u�����ڵ��еľ����Ȩ�Ѿ������,
        ʵ�ʾ���v���ֵܽڵ㼰���ֵ������еĽڵ�.
        �������dp[v][1]+=dp[u][0]��v���Ͼ���vΪ1�ĸ��׽��u�ĵ�Ȩû���ظ��ۼ���,
        �����ۼ��游���ϵķ������ڵ��Ȩʱ,���ظ��ۼ�v�ڵ㱾����������Ͼ���u���׽ڵ�k-1�ĵ�Ȩ,
        ����ʵ���ظ��ۼӵ��Ǿ���v k-2�ĵ�Ȩ,��Ϊ����v�ڵ�����ĵ�Ȩ�Ѿ���dfs1���ۼӹ���.����ظ��ۼӵ�
        ֵ��v����֮ǰ�ȼ�����������ת��ʱ�ظ��Ĳ���.
        eg:1->2,1->3,1->4,2->5,5->6 ��u=1,v=2ʱ dp[2][2]=dp[1][1],��ʱdp[1][1]����2��3��4����ĵ�Ȩ,
        ����2�ĵ�Ȩ����Ϊ����2Ϊ0�ĵ�Ȩ�Ѿ���dfs1�м������.2��Ҫ�ۼӵ��游���Ͼ���Ϊ2�ĵ�Ȩֻ��3 4�����ڵ�.
        */
        for(int j=1;j<=k;j++)
            dp[v][j]+=dp[u][j-1];
        //���ﲻ��Ҫ��ԭdp[v][k],��Ϊv������Ǹ�����ȷ��.
        dfs2(v,u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&dp[i][0]);//ÿ���ڵ����Ϊ0�ĵ�Ȩ���ǽڵ㱾��ĵ�Ȩ.
    dfs1(1,-1);
    dfs2(1,-1);
    for(int i=1;i<=n;i++){
        ans=0;
        for(int j=0;j<=k;j++)
            ans+=dp[i][j];
        printf("%d\n",ans);
    }
    return 0;
}

/*
��һ�ֻ���dp,���ݳ�����,��ǰ�ȰѸ��ڵ���������л����ľ������,�ٱ�����Ķ���ʱ�ٻָ�.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
//����dp
int cnt,n,k,head[N],dp[N][25],ans[N];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//��u�ڵ����v���������ظ����ּ���
void cut(int u,int v){
    for(int i=1;i<=k;i++)
        dp[u][i]-=dp[v][i-1];
}
//����u�ڵ��dfs1�����
void link(int u,int v){
    for(int i=1;i<=k;i++)
        dp[v][i]+=dp[u][i-1];
}

void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        for(int j=1;j<=k;j++)
            dp[u][j]+=dp[v][j-1];
    }
}

void dfs2(int u,int fa){
    //��û�ۼ�֮ǰu�ڵ��dpֵ����������,��¼��ans����
    for(int i=0;i<=k;i++)
        ans[u]+=dp[u][i];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //������Ϊv�ۼ�u�游���ϵĵ�Ȩʱ,v�������ڵ������ظ��ۼ�
        //�������ۼ�֮ǰ�Ȱ�u�ڵ����v�ڵ��������ĵ�Ȩ����
        //�ȼ���u�ظ��ĵ�Ȩ,v�ټ��Ͼ���u�Ķ��ӵĵ�Ȩ
        cut(u,v),link(u,v);
        dfs2(v,u);
        //��ΪҪ����u����һ������,���Ҫ�ٰ�u�ڵ����v�������ĵ�Ȩ��ԭ
        //����v֮ǰ���ϵ��游���ϵĵ�Ȩ�ȼ���,�ټ���u�ڵ����v�������ϵĵ�Ȩ
        cut(v,u),link(v,u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&dp[i][0]);
    dfs1(1,-1);
    dfs2(1,-1);
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}

*/

