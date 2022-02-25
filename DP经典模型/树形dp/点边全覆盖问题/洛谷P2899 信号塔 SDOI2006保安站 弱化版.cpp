#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define INF 0x3f3f3f3f
using namespace std;

/*
����:һ��n���ڵ����,��Ҫ��һЩ�ڵ㴦�����ź���,һ���ź����ܽ�
�źŷ��������������ڽӵĽڵ�(�ź������ýڵ�Ҳ�ܽ��յ�),
��������Ҫ�ڼ����ڵ㰲���ź�����ʹ�����нڵ���ܽ��ܵ��ź�
����:https://www.luogu.com.cn/problem/P2899
˼·:����dp
dp[u][0]������u�ڵ�λ�÷���һ���ź���,u���������ܹ�����Ҫ���õ����ٽڵ�
dp[u][1]����u�ڵ���ź��ɸ��ڵ���õ��ź������ݸ���,u���������ܹ�����Ҫ���õ����ٽڵ�
dp[u][2]����u�ڵ���ź����ӽڵ���õ��ź������ݸ���,u���������ܹ�����Ҫ���õ����ٽڵ�
*/

int cnt,n,head[N],dp[N][3];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    int t=INF;//����Ҷ�ӽڵ�û�ж��ӵ����,dp[u][2]��ֱ�Ӽ������t=INF������
    dp[u][0]=1;//��u�ڵ㱾�����һ���ź���,����Ϊ1
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        /*
        ����u�ڵ㱾������ź���,������ӽڵ�v�����ź���ֻ����dp[v][0],
        ������v�ڵ㲻�����ź���,��v���źŸ��ǿ�����v�ĸ��׻�v�Ķ��ӽڵ�
        ���õ��ź����ṩ.���ֱ���dp[v][1]��dp[v][2].
        ��Ϊ�����ܹ�Ҫ���õ��ź����������Ҫ�ۼ�ÿһ������v�Ĵ�
        */
        dp[u][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
        /*
        ��u�ڵ㱾����ź���u�ĸ��׽ڵ㸲��,������ӽڵ���ź�һ��������
        v�ĸ���u�ṩ,����ӽڵ�Ҫô��������ź���,Ҫô��v�Ķ��ӷ��õ��ź����ṩ�ź�.
        ���ֱ���dp[v][0],dp[v][2]
        */
        dp[u][1]+=min(dp[v][0],dp[v][2]);
        /*
        ��u�ڵ㱾����ź���u�Ķ��ӽڵ��ṩ,��ô����ź�ֻ��Ҫu��һ�������ṩ����,
        ��������ȡ�ڶ��ӽڵ㱾������ź�������v�Ķ��Ӹ����ź������ź�����С�ķ�������.
        �������Ȳ�����Ҫ����һ�����ӽڵ�����ź���,ȫ����������ȡ��С�ڵ����ķ���.
        */
        dp[u][2]+=min(dp[v][0],dp[v][2]);
        /*
        t���� ����u�ڵ���ź��ɶ����ṩʱ,Ӧ��ѡȡ�ĸ����ӽڵ�����ź����������Ӽӵ���С�ڵ���
        dp[v][0]-min(dp[v][0],dp[v][2]),����dp[v][0]�����ǽ�v��Ϊȷ������һ���ź����Ľڵ�,
        -min(dp[v][0],dp[v][2]),����֮ǰѡ��Ľ�Сֵ��Ҫ�����ӵĽڵ���,���ֵ���нڵ�ȡ��С��������,
        ��Ȼ�п��ܽ�С�ı������dp[v][0],�����ӽڵ�������0,����ֻ��Ҫȷ��һ�����õ��ź���v�ڵ�,�����ڵ�
        ȥѡȡ��С�ڵ����ķ���,�п���u�Ķ��ӽڵ��ֶ���������ź���,��������С�ķ���.
        */
        t=min(t,dp[v][0]-min(dp[v][0],dp[v][2]));
    }
    dp[u][2]+=t;//���� dp[u][2]����ȷ����v�ڵ���Ϊ�ź�����С���ӽڵ���
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
    dfs(1,-1);
    //1�ڵ�Ϊ��ֹ״̬,Ϊ���ڵ�û�и���,ֻ�迼��dp[1][0]��dp[1][2]
    printf("%d",min(dp[1][0],dp[1][2]));
    return 0;
}

/*
����dp��һ��˼·
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define INF 0x3f3f3f3f
using namespace std;

int cnt,n,head[N],dp[N][3];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dp[u][0]=1;
    dp[u][2]=INF;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        dp[u][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
        dp[u][1]+=min(dp[v][0],dp[v][2]);
    }
    //���ǽ�u����һ������v��Ϊȷ���ķ������ź����Ľڵ�
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //dp[u][1]ʵ�ʾ���dp[u][2]����������Ҫ��һ�����ӷ����ź���,���ж��Ӷ�ȡ���ٽڵ�����,��ֵ������ȵ�
        //+dp[v][0]����v������ź���,-min(dp[v][0],dp[v][2])����֮ǰѡ��Ľ��ŷ���������,��ԭ�Ȼ����ϼ��Ͽ������ӵĽڵ���
        dp[u][2]=min(dp[u][2],dp[u][1]+dp[v][0]-min(dp[v][0],dp[v][2]));
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
    dfs(1,-1);
    printf("%d",min(dp[1][0],dp[1][2]));
    return 0;
}
*/

/*
//dfs+̰��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
//̰��˼ά:�����ź���Ҫ��������,���ѡ����Ҷ�ӽڵ�,��ô�ź�ֻ�ܸ��ǵ���ǰ�ڵ�͸��ڵ�,
//�����ֵܽڵ���游�ڵ����޷����ǵ�,���Ҫ�������ź������ڸ��ڵ���
int cnt,n,head[N],fa[N],vis[N],ans;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fath){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fath) continue;
        fa[v]=u;
        dfs(v,u);
    }
    if(!vis[u]){
        //����ѡȡ��u�ڵ�ĸ��׽ڵ��Ͻ����ź���,�����źſ��Ը��ǵ�u���ֵܽڵ��u���游�ڵ�
        ans++;//�����ź�������+1 ̰��ѡ����ڸ��״�
        int u0=fa[u];//����ٶ�u0�ĸ���Ϊu1
        //��u(Ҷ��)�ĸ���(u0)����Ѿ����ù��ź���,ͬʱ����u0�����ж��Ӷ������,��ʾu0������ź������Ը���u0���ж��Ӻ͸���u1
        //�����ݵ�u1ʱ,����u1֮ǰ�Ѿ���Ϊu0�Ķ���(��ʵ��u0�ĸ���),����ǹ�,���Ե���u1�Ų������ź���,��Ҫ�ж�u1�Ƿ�����������,
        //��Ϊu1���������ӻ�δ�����,������������,����ʽ��ǰ��Ҷ�Ӵ���ʽ��ͬ,����ź���������u1(���״�),������ͬ��ʱ,
        //����u1֮ǰ�Ѿ��������,���ǲ���Ӱ��ans++�Լ�u1�������ӵı�ǲ���,������u1�����ź���,�������ж��Ӻ�u1�ĸ���,
        //��u1û����������,����Ϊu1֮ǰ�Ѿ����,����������if,�����վ�ֻ��u0�������ź���,ansֻ����1��
        vis[u0]=1;
        for(int i=head[u0];i!=-1;i=edge[i].next)//��u0�Ķ���ȫ�����Ϊ�źŸ���,�������Ҳ������u0�ĸ���
            vis[edge[i].to]=1;
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
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/
