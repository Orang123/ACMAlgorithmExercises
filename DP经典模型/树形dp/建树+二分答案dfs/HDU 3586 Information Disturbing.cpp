#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define INF 1<<20//���ֵ����ȥ̫��,����dp[u]�ۼ�ʱ���ܻ����,����dp�������llҲ���Ա������
using namespace std;

/*
����:һ������Ҫ�ж�һЩ��ʹ�ó�ʼ���ڵ�(���Ϊ1)��Ҷ�ӽڵ㲻��ͨ,���Ҷ����и�ı�Ȩֵ��һ����������,
�����и�����б�Ȩ�Ͳ��ܳ���m��Ԥ��,����Ҫ������������������Ƕ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3586
˼·:�������������Ʋ�ȷ��,�������Ӽ���ֵ��ʼ������֤,��ôҲ�ᳬʱ,���Կ��Ƕ����������.
�����������,dfs��֤�Ƿ���Է�����ڵ�������Ҷ�ӽڵ�,���ܷ���,������ұ߽��С��,�����ܷ����������߽�����
dp[u]�������u���������е�Ҷ�ӽڵ�����Ҫ�и�ı�Ȩ��
*/

int cnt,n,m,head[N],dp[N],ans;
struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa,int maxw){
    dp[u]=0;
    int flag=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        flag=1;
        dfs(v,u,maxw);
        //��u->v��Ȩ��С���������,��Ƚ�u->v��ǰ��Ȩ��v�����еı�Ȩȡ��С��Ȩ
        if(edge[i].w<=maxw)
            dp[u]+=min(edge[i].w,dp[v]);
        else//�����ѡv�������н�С�ı�Ȩ
            dp[u]+=dp[v];
    }
    //����Ҷ�ӽڵ�����INF,������ݵ����ڵ�û��һ�����ڵ����ӽڵ�֮��ı�Ȩ���������С,��˵���޷��ָ���ڵ���Ҷ�ӽڵ���ͨ
    if(!flag)
        dp[u]=INF;
}

int judge(int maxw){
    dfs(1,-1,maxw);
    if(dp[1]<=m) return 1;
    else return 0;
}

int main(){
    int u,v,w,l,r;
    while(scanf("%d%d",&n,&m) && n && m){
        ans=-1;
        r=cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            r=max(r,w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        if(!judge(m)){
            printf("-1\n");
            continue;
        }
        l=1;
        //��������ƽ��ж���,�����Сֵ
        while(l<r){
            int mid=(l+r)/2;
            if(judge(mid)) r=mid;//������Ȩֵ��С��mԤ�� ���Խ���������ٷ�С��
            //���������ƺ���INF,��˵����һ���������̫С,����ĳ��·��û��һ����ȨС������������,����Ҫ��������Ƶ����
            else l=mid+1;
        }
        printf("%d\n",l);
    }
    return 0;
}
