/*
����:FJ��N(1 <= N <= 100)ͷ��ţ������μ��˳�������ƾ���:)��
�������ϣ���ţ�ǰ�1..N���α�š�ÿͷ��ţ�ı������������ͬ��
����û������ͷ��ţ��ˮƽ�������£�Ҳ����˵����ţ�ǵı����������ȷ��������
�����������ֳ��������֣�ÿһ������ͷָ����ŵ���ţ�ĶԾ���
������ΪA����ţ�ı������ǿ�ڱ��ΪB����ţ(1 <= A <= N; 1 <= B <= N; A != B) ��
��ô���ǵĶԾ��У����ΪA����ţ������ʤ���� FJ��֪����ţ�Ǳ�������ľ���������
��������������ţ������ M(1 <= M <= 4,500)�ֱ����Ľ����ϣ�����ܸ�����Щ��Ϣ��
�ƶϳ������ܶ����ţ�ı���������������������֤��������ì�ܡ�
�������ܹ�ȷ�����ε���ţ����Ŀ.��ţ����Ӯ��ϵ���㴫����.
����:https://www.luogu.com.cn/problem/P2419
˼·:��һ�� Ӯ��ͼ,��һ�����ͼ.�ֱ���dfs.
���ĳ����ţӮ�Ĵ���+��Ĵ���==n-1��˵������ţ��������ȷ����.
ע��Ҫ��vis����Ѿ����ʹ��ĵ�,��Ϊ�п���1->2->3,1->3,����3�����,
�ᱻ����һ��.
*/
#include<cstdio>
#include<cstring>
#define N 110
#define M 5000
using namespace std;

int n,m,vis[N],cnt1,cnt2,head1[N],head2[N];
struct Node{
    int to,next;
}edge1[M],edge2[M];

void addEdge1(int from,int to){
    edge1[cnt1]=(Node){to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node){to,head2[from]};
    head2[from]=cnt2++;
}
//����ţӮ�Ĵ���
void dfs1(int u){
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        int v=edge1[i].to;
        if(!vis[v]){
            vis[v]=1;
            cnt1++;
            dfs1(v);//���㴫����
        }
    }
}
//����ţ��Ĵ���
void dfs2(int u){
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            vis[v]=1;
            cnt2++;
            dfs2(v);
        }
    }
}

int main(){
    int u,v,ans=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge1(u,v);
        addEdge2(v,u);
    }
    for(int i=1;i<=n;i++){
        cnt1=cnt2=0;
        dfs1(i);
        dfs2(i);
        memset(vis,0,sizeof(vis));
        if(cnt1+cnt2 == n-1) ans++;//ĳţӮ�Ĵ���+��Ĵ���֮��Ϊn-1ʱ,����������ȷ����
    }
    printf("%d\n",ans);
    return 0;
}
/*
//ac floyd����
#include<cstdio>
#include<cstring>
#define N 110
#define M 5000
using namespace std;
int n,m,a[N][N];

//floyd
int main(){
    int u,v,ans=0;
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        a[u][v]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                a[i][j]|=(a[i][k]&a[k][j]);//���ݴ����� ����
    for(int i=1;i<=n;i++){
        int k=1;
        for(int j=1;j<=n;j++)
            if(i!=j)
                k&=(a[i][j]|a[j][i]);//���i������Լ����������ÿ���㶼�� ��Ӯ��ϵ,������������ȷ����s
        ans+=k;
    }
    printf("%d\n",ans);
    return 0;
}

*/
