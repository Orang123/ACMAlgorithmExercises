#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 2100
#define M 4000100
#define INF 0x3f3f3f3f
using namespace std;
//spfa����
/*
����:���1->n�����·����,������ͬ�����·����Ҫ��Ϊ
·��������ͬ(��Ϊ���·����)��������һ���߲��غ�,�������ݻ����ر�
��������ر����Ҳ�����ȥ�ͻᵼ��,���·��Ŀ����ƫ��.
����:https://www.luogu.com.cn/problem/P1608
˼·:����num����,num[v]��ʾ�����v�����·����.
*/


int n,m,cnt,head[N],vis[N],num[N],dis[N],mp[N][N];
struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s){
    init(s);
    queue <int>Q;
    num[s]=vis[s]=1;//��ʼ�����һ��·��
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        //һ��������n�㲻��Ҫ��ȥ��չ��ĵ�,��Ϊ�����չn�����·û��ʲô����,ֻ��ʹ��dis[n]���Խ��Խ��
        //��һ�������� �Ѿ�����õ�num[n]Ҳ�ᱻ���,���´𰸴���.
        if(u == n) continue;//����Ҳ����ֱ��return����,��Ϊspfa�ȳ��ӵĵ���dis��һ��������С��,����������·�����ٸ��µ��õ�
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                num[v]=num[u];//���·�������仯,����ǰ���ڵ��·����������v�ڵ�·������
            }
            else if(dis[v]==dis[u]+edge[i].w)
                num[v]+=num[u];//�����ʱ,v�ڵ�·��������Ҫ����uǰ���ڵ�·������
            /*
            spfa�㷨�������dis[v]==dis[u]+edge[i].wҲ����Ҫ��ӵ�,
            ��Ϊspfa��bfs�����޷���֤n����ʱ,����nǰ���Ľڵ��u�����·����num[u]��ͳ�Ƴ���,
            ���ܵ�һ��������Ѿ��б������ٵ����·�ȱ�������n��ǰ���ڵ�u,Ȼ������ɳڵ�
            n��ǰ���ڵ�uʱ,��Ȼdis[u]���,���Ǵ�ʱ�������,���Զ���num[n]Ҳ��û���ۼӵ�
            ������չ�����·�ĸ���.������������ȵ����,Ҳͬ����Ҫ��Ҫ���,��������ʹ��
            ������ܵ����·����չ��n�ڵ�.
            */
            //num[v]������0 �ʹ���dis[v]>=dis[u]+edge[i].w �����,����dis[v]<dis[u]+edge[i].w�ǲ���Ҫ��ӵ�
            if(num[v] && !vis[v]){
                vis[v]=1;
                Q.push(v);
            }
        }
        /*
        u�ڵ���չ������ num[u]Ҫ��0,�������Ա����������·num[v]�ۼ�ʱ,ԭ��v����Ѿ����ӵ����·�ظ�����
        ����ÿ���ۼ����·����ͬ���ۼӱ�����ͬ�����·����,���б������ٵ����·������ۼ�,�ۼ����˺�,
        ��ڵ��num�������,�����������ϳ������·�ۼ�ʱ�ظ��ۼ�.
        */
        num[u]=0;
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        //ע���������ݿ��ܻ����ر�,����Ϊ�˱������·��Ŀ�������,������������ֻ����һ����,��������С�ı�Ȩ.
        if(!mp[u][v] || w<mp[u][v]){
            addEdge(u,v,w);
            mp[u][v]=w;
        }
    }
    spfa(1);
    if(dis[n]!=INF)
        printf("%d %d",dis[n],num[n]);
    else
        printf("No answer");
    return 0;
}

/*
//Dijkstra,����Ҫ�����ظ���������,��Ϊ�������ĳЩ���·������չ��n�ڵ�����,
//����num[v]���Զ��ǽ�����v������·����ȫ��ͳ�����,�Ž�v�����,�ټ�����չ��ĵ�
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 2100
#define INF 0x3f3f3f3f
using namespace std;
//��Ϊ���ر����Կ������ڽӾ��� ���,��������
int n,m,cnt,head[N],vis[N],num[N],mp[N][N],dis[N];

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    num[s]=1;//��ʼ�����һ��·��
    Q.push(make_pair(0,s));
    int u;
    while(!Q.empty()){
        //ÿ�γ��ӵĶ���Ȩֵ�ͽ�С�ĵ�,����һ���Ǳ������ٵĵ�,���Լ�ʹ��ĳЩ·��������С,
        //��Ȩֵ����С����Ψһ�������,Ҳ�������г�����չ��n�ڵ�,��Ϊ�䵽��u�ڵ�ı�����,
        //��������ͬ�������·���Ͻڵ��ȨҲ��ϴ�,
        //������Ƚ�·�������϶ൽ��u�ڵ�dis[u]��ͬ�����,����Ҳ�����,��Ϊ������С��·���ڵ�Ȩֵ����Խ�С,
        //������u����ʱ����u�����·��Ŀ��ȫ����������ϵ�.
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int v=1;v<=n;v++){
            if(v == u) continue;
            if(dis[v]>dis[u]+mp[u][v]){
                dis[v]=dis[u]+mp[u][v];
                num[v]=num[u];//���·�������仯,����ǰ���ڵ��·����������v�ڵ�·������
                Q.push(make_pair(-dis[v],v));
            }
            else if(dis[v]==dis[u]+mp[u][v])
                num[v]+=num[u];//�����ʱ,v�ڵ�·��������Ҫ����uǰ���ڵ�·������
        }
    }
}

int main(){
    int u,v,w;
    memset(mp,INF,sizeof(mp));
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        mp[u][v]=min(mp[u][v],w);
    }
    Dijkstra(1);
    if(dis[n]!=INF)
        printf("%d %d",dis[n],num[n]);
    else
        printf("No answer");
    return 0;
}
*/
