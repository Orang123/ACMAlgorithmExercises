#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//ac 1.24s dinic��������
//��Ϊdfs��·����Է��ʵ������ԭ��,���Ա��������˵�ǰ���Ż�,ʵ��Ч�����.������赱ǰ���Ż�.
/*
����:����һ������n�����m���ߵ�����ͼ(�������Ϊ����)G=(V,E),
�����������е�ֱ���Ϊ1~n,���б߷ֱ���Ϊ1~m,���и������Դ��Ϊs,
���Ϊt,�����ϵ�ÿ����(u,v)����һ����������c(u,v)�͵�λ�����ķ���w(u,v).
����Ҫ����ڸ�������������ǰ����,ʹ��ˮ�������ķ���c(u,v)*w(u,v)��С��,
�ֳ������Ӧ�����������С����.
����:https://www.luogu.com.cn/problem/P3381
˼·:Dinic�㷨�����С���������ģ��,mcmf.
*/
struct node{
    int to,next,c,w;
}edge[M<<1];
int head[N],cnt,dis[N],n,m,vis[N];
int max_flow,min_cost;
void addEdge(int from,int to,int c,int w){
    edge[cnt].to=to;
    edge[cnt].c=c;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s,int t){
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
    memset(vis,0,sizeof(vis));//������Ϊ��һ��dfsͳ�ƶ�·����· ���������ʱ,��ǹ�vis[i]=1,���¸�ֵΪ0�Ա��´�spfa
    vis[s]=1;//Դ��s�����
}

//spfa����������̷�����ͬ������·,����Щ����·���ֵ�ͬһ���,
//����dfsʱ������Щ����·�ķ�����,���ǲ�һ����������·���ܱ�����,��Ϊdfsʱ������vis���.
bool spfa(int s,int t){
    queue<int> Q;
    init(s,t);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            /*
            ����ԭ���϶��ڸ�Ȩ�߷������ܹ� �ٴδ�v���ֻص�u���,����������>��û��=��,
            ���Ҳ����ʹ��u���ٴ����,ֻ��dis[u]=dis[v]+edge[i].w(���ܹ�������),
            dfsʱ�����,�����dfs������!vis[u].
            */
            if(edge[i].c>0 && dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    Q.push(v);
                    vis[v]=1;
                }
                // if(v==t) return true //spfaֱ�Ӿ�ȷ����һ�ε��������·,���úͲ�������С,�����wrong
            }
        }
    }
    return (dis[t]!=INF);//��dis[t]ΪINF˵��û������·
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int res=0,v,incf;
    /*
    �ѷ��ʹ��ĸ��ڵ���Ҫ���,�����ڶ��ӷ��ʷ���ʱ�ص����ڵ�,�����.
    �����Ǳ��������˵�ǰ���Ż�,�ѷ��ʹ�������·��֧�ڵ���Ϊ�����,
    �Ͳ����ٷ���.���Բ�����ʹ��cur������dfs�����ͷ����¼���±�.����
    ����Ƿ�Ҳ����ֵ�ǰ���Ż����ֵ��Ǹ�����,�����������Dinic�㷨ģ��
    ���й���¼.
    */
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        /*
        ����dis[v] == dis[u]+edge[i].w,���������!vis[v]�ᵼ����������·��v���,
        ����ͨ���ۼӷ��򻡵ĸ�Ȩֵ���û�ص�֮ǰ�ĸ��ڵ�u���¹�����ѭ��;
        �����ܹ��ɹ�������t,����ջ����ʱ,v->u��������ıߵĲ��������ͷ��򻡵�
        ���������ᱻ����+-incf,����Ϊ����߷���߸�����1��,����+-incf�պõ���,
        ʵ��v-u������ߺͷ���߲�������û�б仯.���Բ�����!vis[v]���ж�ֻ�ᵼ����ѭ��.
        vis���ͬ������ֵ�ǰ���Ż����Ǹ�����.
        */
        if(!vis[v] && edge[i].c>0 && dis[v] == dis[u]+edge[i].w){
            incf=dfs(v,t,min(flow,edge[i].c));
            if(incf>0){
                edge[i].c-=incf;
                edge[i^1].c+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0)
                return res;
        }
    }
    /*
    ����vis[u]=0
    ���ﲻ��ͨ������ʱȡ��vis�����ʹ����������·����֮ǰ����·���ʹ��ķ�֧
    (���ܲ�������û����),������ʹ������dis[v] == dis[u]+edge[i].w�ķ�֧·��,
    �����v��֮ǰ������·���ʹ�,�����ٴη�����Ϊȡ����ǰ���ڵ�ı��,�����v
    ��ǰ���ڵ�u,��������ߺͷ���߻��ٴθ��º�֮ǰ����·���µĵ�����,Ҳ����֮ǰ����·
    �ϱߵĲ���������������㲢û�б仯,����ʵ��������Ѿ��������,�ɲ�������û�б仯,
    �����ͻ����´�bfs�ֲ��dfs����·�ܵĽ��������ͻ����.
    */
    //vis[u]=0;//��������ȡ����� �����
    /*
    ����������dinic����ը���Ż����β�������������Щ�ϴ�������Ŀ�������·,
    ��Ϊ�����ѷ��ʹ��ĵ��Ѿ���ǹ�vis[u]=1��,�ѷ��ʹ��ĵ㱾����ǲ����ٷ��ʵ�.
    */
    //if(res == 0) dis[u]=INF;//�����������,vis[v]��Ǳ�����ܱ�֤�ѷ��ʹ�������·�ĵ㲻�ٷ���
    return res;
}

void mcmf(int s,int t){
    int flow;
    while(spfa(s,t)){
        flow=dfs(s,t,INF);//һ��dfsͳ�Ƽ����������·�������,
        max_flow+=flow;
        /*
        ������С�����ܺ�Ҳ��ͨ������ ��ȡ����ʽ �򻯼���õ�,
        ��һ����ȡ����ʽincf�������ܺϻ���Ϊ dis[t],�ڶ�����ȡ
        ����ʽdis[t]����������·��������ͻ���Ϊflow.
        */
        min_cost+=flow*dis[t];
    }
}

int main(){
    int s,t,u,v,c,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        scanf("%d%d%d%d",&u,&v,&c,&w);
        addEdge(u,v,c,w);
        addEdge(v,u,0,-w);
    }
    mcmf(s,t);
    printf("%d %d",max_flow,min_cost);
    return 0;
}

/*
//ac 695ms Dinic�㷨 Dijkstra���ֲ������ ��Ϊ�и�Ȩ����,
//��Ҫ���ƺ���h[i]����Ȩ���������������ܱ�֤�������ȷ��
//������̫����ƺ���h[i]�Ĳ���
////����ƺ����ǲ����� Johnson�㷨��������ǲ���ʽ��˼· http://hoblovski.is-programmer.com/posts/52364.html
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;

struct node{
    int to,next,c,w;
}edge[M<<1];
int head[N],cnt,dis[N],n,m,vis[N],h[N];
int max_flow,min_cost;
void addEdge(int from,int to,int c,int w){
    edge[cnt].to=to;
    edge[cnt].c=c;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s,int t){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    memset(vis,0,sizeof(vis));
}

int Dijkstra(int s,int t){
    priority_queue<pair<int,int> ,vector<pair<int,int>>,greater<pair<int,int>> >Q;//������С���� Ҳ����pair ����Ѵ渺ֵ
    init(s,t);//��ʼ��
    Q.push(make_pair(dis[s],s));
    int u,v;
    pair<int,int> tp;
    while(!Q.empty()){
        tp=Q.top();
        u=tp.second;
        Q.pop();
        //���ﲻ�������·������vis���,��vis���,������ж�u == t�ͻ�tle �㲻��ɶԭ��
        if(dis[u]<tp.first) continue;//��֮ǰ���µ�dis[u]�����Ѿ��ȵ�ǰ�����ѵķ���С�򲻱ظ���
        if(u == t) break;//Dijkstra�Ѿ���������С����һ�������ŵĲ����ٸ���,����
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].c>0 && dis[v]>dis[u]+edge[i].w+h[u]-h[v]){//h[u]-h[v]�����
                dis[v]=dis[u]+edge[i].w+h[u]-h[v];
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return dis[t]!=INF;
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int res=0,v,incf;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!vis[v] && edge[i].c>0 && dis[v] == dis[u]+edge[i].w+h[u]-h[v]){
            incf=dfs(v,t,min(flow,edge[i].c));
            if(incf>0){
                edge[i].c-=incf;
                edge[i^1].c+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0)
                return res;
        }
    }
    return res;
}

void mcmf(int s,int t){
    int flow;
    while(Dijkstra(s,t)){
        flow=dfs(s,t,INF);//һ��dfsͳ�Ƽ����������·�������,
        for(int i=1;i<=n;i++)
            h[i]+=dis[i];
        max_flow+=flow;
        min_cost+=flow*h[t];//����Դ�㵽���ķ��ú�Ҫ��h[t],������dis[t],�����������������
    }
}

int main(){
    int s,t,u,v,c,w;
    memset(head,-1,sizeof(head));
    memset(h,0,sizeof(h));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        scanf("%d%d%d%d",&u,&v,&c,&w);
        addEdge(u,v,c,w);
        addEdge(v,u,0,-w);
    }
    mcmf(s,t);
    printf("%d %d",max_flow,min_cost);
    return 0;
}
*/

/*
zkw��������δ�˽�
*/
