#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//ac 1.24s EK�㷨�����С��������� mcmf
/*
��ظ���:
1.������:
����һ������G=(V,E),ÿ���߳�������������c(u,v),����һ����λ�����ķ���w(u,v).
��(u,v)������Ϊf(u,v)ʱ,��Ҫ����f(u,v)*w(u,v).
wҲ����б�Գ���,��w(u,v)=-w(u,v).
����������ܻ�����С���������Ϊ��С���������,�������f(s,v)(Դ��s�������ۺ�)
��ǰ������С��f(u,v)*w(u,v).
2.��С���������:
ÿ���߳���Ҫ����������,����һ������,����λ�������������ߵĿ���.
����Ҫ������������ͬʱ,Ҫ�󻨷ѵķ�����С.
*/

/*
����:����һ������n�����m���ߵ�����ͼ(�������Ϊ����)G=(V,E),
�����������е�ֱ���Ϊ1~n,���б߷ֱ���Ϊ1~m,���и������Դ��Ϊs,
���Ϊt,�����ϵ�ÿ����(u,v)����һ����������c(u,v)�͵�λ�����ķ���w(u,v).
����Ҫ����ڸ�������������ǰ����,ʹ��ˮ�������ķ���c(u,v)*w(u,v)��С��,
�ֳ������Ӧ�����������С����.
����:https://www.luogu.com.cn/problem/P3381
˼·:EK�㷨�����С���������ģ��,mcmf.
*/

struct node{
    int to,next,c,w;
}edge[M<<1];
int head[N],incf[N],pre[N],cnt,dis[N],n,m,vis[N];
int max_flow,min_cost;

void addEdge(int from,int to,int c,int w){
    edge[cnt].to=to;
    edge[cnt].c=c;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s,int t){
    for(int i=1;i<=n;i++)//memset(dis,0x3f,sizeof(dis)) dis[s]=0Ҳ����ȷ��
        dis[i]=i==s?0:INF;//��Դ��dis[s]����Ϊ0,�����dis����ΪINF,������¹滮��С����
    pre[t]=-1;//���û��ı��Ϊ-1,�����жϴ˴��Ƿ����������µ�����·
    incf[s]=INF;//����Ƚϸ�������·�е���С��������
    vis[s]=1;//����Դ�� �������
}

/*
��Ϊ���򻡵Ĵ���,ÿ�����п��ܷ���Ϊ����,����Ȩ��,�������spfa,������ֱ����Dijkstra,
��Ϊ���·����Dijkstra̰���ǽ����ڱ�Ȩ��Ϊ�������,������������и��ͻ����.
��Ҫ��Dijkstra����Ҫ�����ƺ���h[i]����Ȩ���������������ܱ�֤�������ȷ��.
ʵ���Ͼ�������������·��ͬʱ��������Ȩ���·,Ҫ��֤�䵽���������ѵķ����ܺ���С
*/
int spfa(int s,int t){
    queue<int> Q;
    init(s,t);//��ʼ��
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            /*
            �ñ߼�Ҫ�����������>0,ҲҪ�����Դ�㵽��v�������ѵķ������ٴα�ø�С,
            dis[v]>dis[u]+edge[i].w ����ԭ���϶��ڸ�Ȩ�߷������ܹ��ٴδ�v���ֻص�u���,
            ����������>��û��=��,dis[u]=dis[v]+edge[i].w(���ܹ�������).
            ��Ϊ��dis[v]>dis[u]+edge[i].w�ɱ�֤��������ѱ������ĵ�,������Բ���pre[v]==-1�ж�.
            */
            if(edge[i].c>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;//��¼����·v�����ڵıߵ��±�
                incf[v]=min(incf[u],edge[i].c);//���ϼ�¼��Ȿ������·�е���С��������
                dis[v]=dis[u]+edge[i].w;//���´�Դ�㵽��v�������ѵ���С����
                if(!vis[v]){//��v�㻹δ���,��������
                    Q.push(v);
                    vis[v]=1;
                }
                //���ﲻ�ܵ�����t��ֱ�ӽ���,��Ϊspfa�ȵ���ĳ�����·�������ۺϲ�һ������С��,�����
                //����ʵ��ȷ��������·����Ҳ��һ������̵�,spfa�����·��Ȩֵ��(����)��С
                //if(v == t){ return incf[t];
            }
        }
    }
    return pre[t];//pre[t]==-1 ���������������һ��s��t��·���ж����ٺ���һ����������Ϊ0�ı�,������������·
}
//mcmf(min cost max flow ��С���������)
void mcmf(int s,int t){
    while(spfa(s,t)!=-1){//����������·ʱ����-1�ͽ���
        for(int i=t;i!=s;i=edge[pre[i]^1].to){
            edge[pre[i]].c-=incf[t];//����߲�����������
            edge[pre[i]^1].c+=incf[t];//����߲�����������
            /*
            ����������ÿһ������·�õ�ÿ�����϶�ÿ���������ѵ�����*��λ�����������
            ��������������Ż�,ֱ��һ��һ���� �����������ᳬʱ,ʵ����ѧ���ʽ:
            edge[pre[i]].w*incf[t]+edge[pre[j]].w*incf[t]+...+edge[pre[t]].w*incf[t],
            ������ȡ����ʽincf[t],incf[t]*(edge[pre[i]].w+edge[pre[j]].w+...edge[pre[t]].w)
            ��(edge[pre[i]].w+edge[pre[j]].w+...edge[pre[t]].w)ÿ�����������ѵķ���֮��,
            ʵ�ʾ���spfa����Ĵ�sԴ�㵽����t��С����Ȩֵ��,����dis[t]����ʵ�ʾ���incf[t]*dis[t].
            */
            //min_cost+=incf[t]*edge[pre[i]].w;//һ����һ�����ۼ�����*���û�TLE,�ӷ����ʱ.
        }
        max_flow+=incf[t];//�ۼ������
        min_cost+=incf[t]*dis[t];//һ���Լ��� ��С����
    }
}

int main(){
    int s,t,u,v,c,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        scanf("%d%d%d%d",&u,&v,&c,&w);//cΪ���� wΪͨ����λ������Ҫ�ķ���
        addEdge(u,v,c,w);
        addEdge(v,u,0,-w);//���򻡵�����·��ѡ��������ʱ�ṩ���ڵĻ��� ������Ϊ0,����Ϊ��Ȩ
    }
    mcmf(s,t);
    printf("%d %d",max_flow,min_cost);
    return 0;
}

/*
//ac 555ms EK�㷨 Dijkstra���ֲ������ ��Ϊ�и�Ȩ����,
//��Ҫ���ƺ���h[i]����Ȩ���������������ܱ�֤�������ȷ��
//������̫����ƺ���h[i]�Ĳ���
//����ƺ����ǲ����� Johnson�㷨��������ǲ���ʽ��˼· http://hoblovski.is-programmer.com/posts/52364.html
//�ο�����:https://www.cnblogs.com/zbwmqlw/archive/2011/01/01/1923694.html
//https://www.luogu.com.cn/problem/solution/P3381?page=1 //���P3381 ���
//https://blog.csdn.net/weixin_43741224/article/details/98970032
//https://www.cnblogs.com/zwfymqz/p/8543329.html
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//h[i]��һֱ�ۼ�,������������Ȩ����ܴ�,��Ҫ��long long
int head[N],incf[N],pre[N],cnt,dis[N],n,m,h[N];
int max_flow,min_cost;
struct node{
    int to,next,c,w;
}edge[M<<1];

void addEdge(int from,int to,int c,int w){
    edge[cnt].to=to;
    edge[cnt].c=c;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s,int t){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;//��ʼ����Ϊ0
    pre[t]=-1;//���ǰ�����-1
    incf[s]=INF;//Դ����С�����������INF
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
                pre[v]=i;
                incf[v]=min(incf[u],edge[i].c);
                dis[v]=dis[u]+edge[i].w+h[u]-h[v];
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return pre[t];
}

void mcmf(int s,int t){
    while(Dijkstra(s,t)!=-1){
        for(int i=t;i!=s;i=edge[pre[i]^1].to){
            edge[pre[i]].c-=incf[t];
            edge[pre[i]^1].c+=incf[t];
        }
	//��Ҫ��ÿ��Dijkstra��������ǰ�ۼӽ��
        for(int i=1;i<=n;i++)//h[i]��һֱ�ۼ�,������������Ȩ����ܴ�,��Ҫ��long long
            h[i]+=dis[i];//Ҳ��h[i]=min(h[i]+dis[i],INF); ���ﲻ���
        max_flow+=incf[t];
        min_cost+=incf[t]*h[t];//����Դ�㵽���ķ��ú�Ҫ��h[t],������dis[t],�����������������
    }
}

int main(){
    int s,t,u,v,c,w;
    memset(head,-1,sizeof(head));
    memset(h,0,sizeof(h));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        scanf("%d%d%d%d",&u,&v,&c,&w);//cΪ���� wΪͨ����λ������Ҫ�ķ���
        addEdge(u,v,c,w);
        addEdge(v,u,0,-w);
    }
    mcmf(s,t);
    printf("%d %d",max_flow,min_cost);
    return 0;
}
*/

/*
zkw������ ��δ�˽�
*/
