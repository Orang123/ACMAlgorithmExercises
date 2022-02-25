/*
����:ժ������
n����,m���ߵ�����ͼ,���ÿ�����Ϊ��ĵ��ߵ�Ψһ��һ��
����Ϊ��ĵ�������߷��У�������������һ���߱������Ĵ���.
n<=5000,M<=50000.
����:https://www.luogu.com.cn/problem/P2883
˼·:��������ͼ,���������Ϊ0�ĵ��������ͼ����������,
num1[v]��¼���Ϊ0�ĵ㵽��v���·������,�ٴ�n���ڷ���ͼ
������������,num2[v]��¼��v���������n���·������.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
#define M 50100
using namespace std;
int n,m,head1[N],head2[N],cnt1,cnt2,ans=-1,inde[N],outde[N],num1[N],num2[N],vis[N];
struct Node1{
    int from,to,next;
}edge1[M];
struct Node2{
    int from,to,next;
}edge2[M];

void addEdge1(int from,int to){
    edge1[cnt1]=(Node1){from,to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node2){from,to,head2[from]};
    head2[from]=cnt2++;
}

void dfs1(int u){
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        int v=edge1[i].to;
        num1[v]+=num1[u];
        if(!--inde[v])//ֻ�е�v�����Ϊ0 ʱ�ż����������,�����ظ���������·��,���Ӷȹ���
            dfs1(v);
    }
}

void dfs2(int u){
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        num2[v]+=num2[u];
        if(!--outde[v])
            dfs2(v);
    }
}
//����������ͼ���ֱ������ÿ�����·����
int main(){
    int u,v;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge1(u,v);
        addEdge2(v,u);
        inde[v]++;
        outde[u]++;
    }
    for(int i=1;i<=n;i++){
        if(!inde[i]){
            vis[i]=1;//vis��¼���Ϊ0�ĵ�,��Ϊdfs1���������Ϊ0�ĵ�
            num1[i]=1;
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i])
            dfs1(i);
    }
    num2[n]=1;
    dfs2(n);
    for(int i=0;i<m;i++)
        ans=max(ans,num1[edge1[i].from]*num2[edge1[i].to]);//��������·�� ���˵�(���򡢷���)ͨ���Ĵ��� ��˼�ʹ�� ��ȡ���ֵ
    printf("%d\n",ans);
    return 0;
}
