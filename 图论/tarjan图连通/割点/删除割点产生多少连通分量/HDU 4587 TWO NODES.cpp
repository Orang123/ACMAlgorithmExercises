#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 5100
#define M 5100
using namespace std;
//ac 3588ms
//2013 ACM-ICPC�Ͼ�����ȫ��������
/*
����:����ͼ��ɾ��2�������ʣ�����ͨ��������ʹ�����,���������ͨ��������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4587
˼·:N,M<=5000.��Ϊԭͼ�п��ܸ��������ڸ��(ֱ��������и��,dfs����ѡ2����
������Ϸ�����Ȼ����,����Ҳ��TLE),�������ǿ���ö����ɾ��һ����,Ȼ��tarjan���
��ʣ����ö��ɾ���ڶ�����,��Ȼ��ʱ�п����Ծ��ǲ����ڸ���.����ԭͼ�������
���,��ô��һ��ö�ٵĵ��п����Ǹ��Ҳ�п��ܲ���,��Ϊ�������ԭͼ�Ƿ���ڸ��,
����Ҫ����ö��ɾ����һ����O(n^2)*O(tarjan(V+E)).
*/

int n,m,dfn[N],low[N],num,cnt,head[N],cut[N],ans;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int k){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa || v == k) continue;//k����ɾ��,������k�����ı߾Ͷ����ᱻ����
        if(!dfn[v]){
            dfs(v,u,k);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v])
                cut[u]++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(fa < 0) cut[u]--;//fa == -1 ʱ,�Ǹ��ڵ� ʵ����ͨ���� ��cut[u]��1,��Ϊ��û�и��ײ��ֵ���ͨ����.
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        cnt=0;
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        ans=1;//�������ٴ���һ����ͨ����
        for(int i=0;i<n;i++){//��ö��ɾ��һ����
            memset(dfn,0,sizeof dfn);
            memset(cut,0,sizeof cut);
            num=0;
            int sum=0;
            for(int j=0;j<n;j++){
                if(j == i) continue;//������i��Ϊ���ڵ� tarjan���� ��Ϊ�Ѿ��ٶ�ɾ����
                if(!dfn[j]){
                    sum++;//�������游�ڵ���ʣ���һ����ͨ����
                    //i����Ϊ��ɾ���ĵ�,tarjan����ʱ����i�� continue ������i�����ı߾Ͷ����ᱻ����,����ģ���ɾ��i���ͼ�����
                    dfs(j,-1,i);
                }
            }
            for(int k=0;k<n;k++){
                if(k!=i)//����о���ʹ����k!=i���ж�Ӧ��Ҳ�ǶԵ�(i���cut�϶�Ϊ0),���ǲ���if ��wa
                    ans=max(ans,sum+cut[k]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
