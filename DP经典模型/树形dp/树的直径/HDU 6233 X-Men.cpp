#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
using namespace std;

/*
����:һ��n���ڵ����,��m�����Ϸ���ս��,�ڵ�ֱ�ӵľ���Ϊ1����,1Сʱ����,
ս���ܺ����Լ����볬��1���������ս���໥����,ÿ��ս��������������ս�����붼������1,
�����Ǿͻᾲֹ����,��������Ҫ�೤ʱ�����ʹ������ս������ֹ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=6233
˼·:������ս�������ʼλ��·�����ɵ�������,����������ֱ��,ֻ��������ĳ�ʼ�˵�ͽ����˵㱾��Ҫ��ս��,
��Ϊս����ͬʱ�ж���,������ٵ�ʱ��Ҫ������������ϳ���2,����ȡ��,�������Ϊ3,ʵ������ս��ֻ��Ҫͬʱ��1Сʱ,�����Ϊ1,��������,
��3/2=1.00
*/

int cnt,n,m,head[N],vis[N],ans;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int dis){
    //ս�����ߵ��Ľڵ������������ս��,������ʼ��ս����ľ���,�����ֵ
    if(vis[u]) ans=max(ans,dis);
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u,dis+1);//disս�����ߵľ����1
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d",&u);//��¼��Щ�ڵ��Ϸ�����ս��
            vis[u]=1;
        }
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        ans=-1;
        for(int i=1;i<=n;i++){
            if(vis[i])//�ӽڵ��Ϸ�����ս���ĵ㿪ʼ���� ������ս�����������ֵ
                dfs(i,-1,0);
        }
        printf("%d.00\n",ans/2);//������������2��������ʱ��
    }
    return 0;
}
