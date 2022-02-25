#include<cstdio>
#include<cstring>
#define N 10010  //���������ó�100010��ʱ����100ms,����10010��ʱ���900ms ����ѧ
#define INF 0x3f3f3f3f
using namespace std;

/*
����:https://www.luogu.com.cn/problem/P1993
����:https://www.luogu.com.cn/problem/P1993
˼·:���Լ����ģ �и���,��������dfs�и���,�����spfa��,dfs��ȷ�Եò���֤��,��ʱ�����.s
*/

struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[0]=0;
    for(int i=1;i<=n;i++)
        dis[i]=INF;
}

bool dfs(int u){
    int v;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(dis[v]>dis[u]+edge[i].w){//�ɳ��ж� ���·
            dis[v]=dis[u]+edge[i].w;
            /*
            ����ڶ��η��ʵ��õ�(˵�������˻�),��Ϊ��dfs�����������ԭ�ȵ�����·��һ·���ʵ���,
            �˹���Ȩֵ�����������ǲ����ۼӱ��Ĺ���,���ڶ��η����ٶȱ�ø�С��
            ֻ��˵�������ɵĻ�Ȩֵ��Ϊ��������˲����ڵڶ��η���ʱ�õ��ɳ�,˵���ڷ��ʵĹ����й����˸���,֮��ͻ�������ȫ����ջ
            �������spfa�и�����ȻЧ�ʸ�,���ڶ��η��ʵ���ʱ��Ϳ����ж�����,��spfa��Ҫ��������n�β�����ʽ�ж�
            */
            if(vis[v]) return false;
            if(!dfs(v)) return false;//û�и����ͳ�����һ�����Ƿ񹹳ɸ���
        }
    }
    vis[u]=0;
    return true;//û�и����������˳�
}
int main(){
    int u,v,w,k;
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    init();
    while(m--){
        scanf("%d%d%d",&k,&u,&v);//�������ﹹ�����·ģ�� ��ȡ���ֵ
        if(k==1){
            scanf("%d",&w);
            addEdge(u,v,-w);//u-v>=w  v<=u+(-w)
        }
        else if(k==2){
            scanf("%d",&w);
            addEdge(v,u,w);//u-v<=w u<=v+w
        }
        else{
            addEdge(u,v,0);//u=v u-v>=0 u-v<=0 ����������
            addEdge(v,u,0);
        }
    }
    for(int i=1;i<=n;i++)
        addEdge(0,i,0);
    if(dfs(0)) printf("Yes");
    else printf("No");
    return 0;
}
