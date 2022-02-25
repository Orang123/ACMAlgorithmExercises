#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
//ac 16ms ����dp ����һ����,ֱ����ÿ���ڵ�ö��2��״̬������dp��ʽ
/*
����:ѧУ����У��,����Ա�����μӾۻ�,ÿ�����������Լ��Ŀ��ֶ�,����ÿ��Ա�������ܺ��Լ�����˾
ͬʱ�ڳ�,�����μӾۻ���������ֶ��ܺ��Ƕ���.
����:http://poj.org/problem?id=2342
˼·:dp[i][0] dp[i][1]�ֱ����Ա��i�������������ۼӵ������ֶ�.
����������ϴ�Ȩ��������.���ǲ����ö���ͼ�����������=������-���ƥ������,
����ʱ����N<=6000,��������O(VE)�϶���ʱ,��һ������ͼ�е���������ֻ�ܴ��������ϵ�
���,�޷������Ȩ���ϵ����,��Ϊ�������ƥ�䷽���ǲ�Ψһ��,��С���㸲��Ҳ�Ͳ�Ψһ,
��ô����������ȻҲ��Ψһ,����������������ö�����п�����������������Ƚ������ֵ,
���鷳,�������Ѿ���һ������,�Ϳ���Ӧ������dpO(V+E)ȥ���.
*/
struct _edge{
    int to,next;
}edge[6005];
int x[6005],dp[6005][2],head[6005],father[6005];

void dfs(int root){
    int son;
    for(int i=head[root];i!=-1;i=edge[i].next){
        son=edge[i].to;
        dfs(son);
        //ö�ٸ��ڵ��Ƿ����μӾۻ�
        //�����˾����,����¼��Ķ��ӵĿ��ֶȸ���,��ô�¼��������ֶȾ������,����¼����ӿ��ֶȱ��¼�С�ܶ�,��ô�¼����ܿ��ֶȲŻ����
        dp[root][0]+=max(dp[son][0],dp[son][1]);//����������ȡ�ӽڵ����������ֶȵ����ֵ,��Ϊ�Ƕ������������+=
        dp[root][1]+=dp[son][0];//���� �ӽڵ�ز���
    }
}

int main(){
    int N,a,b,root;
    scanf("%d",&N);
    memset(head,-1,sizeof(head));
    memset(father,-1,sizeof(father));
    for(int i=1;i<=N;i++){
        scanf("%d",&x[i]);
        dp[i][0]=0;//���ڵ�Ϊi����
        dp[i][1]=x[i];//���ڵ�Ϊi��
    }
    for(int i=0;i<N-1;i++){
        //��Ϊb��a�ĸ��ڵ㣬b��a����˾,�����֪��һ����������������轨�����ߣ���������visit�������
        scanf("%d %d",&a,&b);
        edge[i].to=a;
        edge[i].next=head[b];
        head[b]=i;
        father[a]=1;
    }
    //�ҳ����ڵ�
    for(int i=1;i<=N;i++){
        if(father[i]==-1){
            root=i;
            break;
        }
    }
    dfs(root);//��ȱ�����Ϊ���¼��Ĺ�ϵ������ô��������ĸ��ڵ������ϼ���ʼ����
    printf("%d\n",max(dp[root][0],dp[root][1]));
    return 0;
}

/*
//ac 32ms ���μ��仯����
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

struct _edge{
    int to,next;
}edge[6005];
int x[6005],dp[6005][2],head[6005],father[6005];

//������ص��������� u������u�㲻��,�������еĽڵ��״̬��һ����,
//��u������u�㲻��,����Ҫ����v�㲻����״̬,���״̬�����ظ����ֵ�
int dfs(int u,int k){
    if(dp[u][k])//�����ص�������ֻ�����һ��
        return dp[u][k];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(k)//k=1 u����,��ô�¼�v�϶�������
            dp[u][k]+=dfs(v,0);
        else//k=0 u��û��,��ô�¼�v������ Ҳ���Բ���
            dp[u][k]+=max(dfs(v,0),dfs(v,1));
        //����״̬�� dfs(v,0)���������ص�������
    }
    if(k) dp[u][k]+=x[u];//k=1����u����,�������u��Ŀ��ֶ�
    return dp[u][k];
}

int main(){
    int N,a,b,root;
    scanf("%d",&N);
    memset(head,-1,sizeof(head));
    memset(father,-1,sizeof(father));
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=N;i++)
        scanf("%d",&x[i]);
    for(int i=0;i<N-1;i++){
        //��Ϊb��a�ĸ��ڵ㣬b��a����˾,�����֪��һ����������������轨�����ߣ���������visit�������
        scanf("%d %d",&a,&b);
        edge[i].to=a;
        edge[i].next=head[b];
        head[b]=i;
        father[a]=1;
    }
    //�ҳ����ڵ�
    for(int i=1;i<=N;i++){
        if(father[i]==-1){
            root=i;
            break;
        }
    }
    printf("%d\n",max(dfs(root,0),dfs(root,1)));//root ������ ���������еĶ��Ӷ���Ҫ���Ƕ��Ӳ����������Ȼ�ص�������
    return 0;
}
*/
