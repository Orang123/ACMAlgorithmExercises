#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define M 300100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

/*
����:n������,1Ϊ�׶�,m����·����,����k������·
ֱ�Ӻ��׶�ֱͨ,�����������Թرն���������·,
ʹ��ÿ�����е��׶�����̾��벻�ܵ�Ӱ��.
����:https://codeforces.ml/problemset/problem/449/B
˼·:���Խ�m����·��k������·,��ͬ����,��Ϊÿ��
���е��׶������·,�м�߿��ܻ��õ�����·,Ȼ��������
ͳ�����·�����İ취ͳ���׶�����ÿ�������ж��������·,
ֻ��������о�������Ϊ�˱������̫�������,ÿ��ֻ��1,
ʵ��ԭ�ȵ�·�����·ֻҪ����һ������,��ɾ����k������·���
û��Ӱ��,�п���ͬ1���е����׶��Ļ���·�ж���,����Ҳ�п�����ͬ.
*/

int n,m,k,cnt,head[N],vis[N],a[N],num[N],ans;
ll dis[N],b[N];
struct Node{
    int to,next;
    ll w;
}edge[(M<<1)+N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(dis[s],s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                num[v]=1;//��׼������num[v]=num[u] �������ʵ�ʸ�����һЩ ����Ӱ���,ֱ��ͳ�ƿ��ܻ������
                Q.push(make_pair(-dis[v],v));
            }
            else if(dis[v]==dis[u]+edge[i].w)
                //��������Ӱ����,��Ϊʵ��ֻ��֪������k������·,ԭ��·�����ṩһ�����·����
                num[v]++;//��׼������num[v]+=num[u]
        }
    }
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    for(int i=1;i<=k;i++){
        scanf("%d%lld",&a[i],&b[i]);
        addEdge(1,a[i],b[i]);
    }
    Dijkstra(1);
    for(int i=1;i<=k;i++){
        u=a[i];
        if(b[i]>dis[u])//���߱����·�� ֱ�Ӽ�1
            ans++;
        //�����ߺ����·��� ����ʣ��ͼ�а�����ǰ������������2�����·,��ΪҪ��֤ͼ�����ٻ���һ�����·
        else if(b[i] == dis[u] && num[u]>1){
            ans++;
            num[u]--;//ʣ�����·������һ
        }
    }
    printf("%d",ans);
    return 0;
}
