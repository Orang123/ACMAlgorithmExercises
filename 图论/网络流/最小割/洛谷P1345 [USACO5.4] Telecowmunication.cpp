#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 250 //����i+n�� �����ߵ�Ч�����Ҫ2*N�Ŀռ俪��
#define M 1500//��˫��� (600+100)*2,����֮�以��ɴ�
#define INF 0x3f3f3f3f
using namespace std;
//ac 25ms dinic ��С��=����� ��㹹��������,��ɾ��ת��Ϊɾ��㵽�����ɾ������
/*
����:ũ��Լ������ţ��ϲ��ͨ�����ʱ�����ϵ,�������ǽ�����һ����ţ��������,
�Ա㻥�ཻ��.��Щ���������µķ�ʽ���͵���:�������һ����c̨������ɵ�����
a1,a2,...,ac,��a1��a2����,a2��a3����,�ȵ�.��ô����a1��ac�Ϳ��Ի�������.
�ܲ���,��ʱ����ţ�᲻С�Ĳȵ�������,ũ��Լ���ĳ�Ҳ�����������,��̨��ù��
���Ծͻỵ��.����ζ����̨���Բ����ٷ��͵�����,��������̨������ص�����Ҳ��
��������.����ͷ��ţ����:��������������ܻ�������,������Ҫ��������̨������?
���дһ������Ϊ���Ǽ��������Сֵ.
��ͷ��ţʹ�õĵ��Ա��Ϊc1��c2.
����������Ϊ��:1-3-2
����ͼ��������2�����ӵ�3̨����.������Ҫ�ڵ���1��2֮�䴫����Ϣ.����1��3,
2��3ֱ����ͨ.�������3����,����1��2�㲻�ܻ�����Ϣ��.
����:һ��n��������ͼ,������ɾ�����ٸ������ʹ�����е�Դ��ͻ�㲻��ͨ.

����:https://www.luogu.com.cn/problem/P1345
˼·:���Խ�һ����i���������i(���)��i+n(����),i��i+n֮�佨˫���,
����Ϊ1(��Ϊÿ����ֻ��ɾ��һ��),�����x����i��x-i��˫���,����ΪINF;
i�����������x,��i+n-x��˫���,����ΪINF.��������ת��Ϊ�˷���Դ�㵽���
������Ҫ��ȥ������,��Ȼ����С������,����С��=�����.��ʵ����С���бߵ���Ŀ
��ʵ������ɾ����ĸ����ǵȼ۵�,��Ϊɾȥ�ıߵ���������1,�����ͽ���ɾ�������
��Ŀת������ɾ�ߵ�������Ŀ.
ע��:��ʼԴ��Ҫ��c1+n(c1Դ��ĳ���)��ʼ,��Ϊc1-c1+n��ʵ����ֻ��1,���������ԶΪ1,
�𰸴���.

ע��:
1.u��v�ĵ�����˫��ͨ�ŵ�,˫��ͨ�ŵ�����߷�Ϊ u+n->v�� v+n->u�������ߵ���ʼ������INF,
���䷴��v->u+n��u->v+n��ʼ������0,�����������.
2.�����޷���tarjan���ĽǶȿ���,��Ϊtarjanֻ���жϳ����ٸ����,�޷�����Ӱ��Դ��ͻ���
��ͨ�Եľ������ٵĸ����Ŀ.����������Ŀһ���ǲ����ڸ���,�����޷�ɾ��һ����ʹ��ԭͼ����ͨ,
����Ҫ���������С����.
*/

struct node{
    int to,next,f;
}edge[M<<1];//��˫���
int head[N],cnt,vis[N],d[N];

void addEdge(int from,int to,int f){
    edge[cnt]=(node){to,head[from],f};
    head[from]=cnt++;
    edge[cnt]=(node){from,head[to],0};//������ʼ����Ϊ0
    head[to]=cnt++;
}

void init(int s){
    memset(d,-1,sizeof(d));//Դ������0,���������-1,�ж���dis[v]==-1,�ɱ���ʹ��!dis[v]ʹ��Դ���ٴ����
    d[s]=0;
}

bool bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].f>0 && d[v]==-1){
                d[v]=d[u]+1;
                if(v == t) return true;
                Q.push(v);
            }
        }
    }
    return false;
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int v,incf,res=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(edge[i].f>0 && d[v]==d[u]+1){
            incf=dfs(v,t,min(flow,edge[i].f));
            if(incf>0){
                edge[i].f-=incf;
                edge[i^1].f+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0) return res;
        }
    }
    if(res == 0) d[u]=-1;
    return res;
}

int maxFlow(int s,int t){
    int sum=0;
    while(bfs(s,t))
        sum+=dfs(s,t,INF);
    return sum;
}

int main(){
    int n,m,c1,c2,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    scanf("%d%d",&c1,&c2);
    for(int i=1;i<=n;i++)
        //i��Ϊ��ĵ����߽���ĵ�,i+n��Ϊi����������ȥ�ĵ� ��ʵ��������Ϊ1,��Ϊ1����ֻ��ɾ��1��
        //���򻡳��㵽���i+n��i��ʼ����Ϊ0
        addEdge(i,i+n,1);
    while(m--){
        scanf("%d%d",&u,&v);
        /*
        �����͵�֮���������˫����ͨ��,������Ҫ����ΪINF,
        ��Ϊʵ�ʸ������i��i+n֮����Ϊ1�ı�,��Ч�ڸ��i��,
        ������С��������������֮��������ΪINF������.
        */
        //u-v�ǻ�ͨ��,��u�ĳ���ɴ�v�����,v�ĳ���Ҳ�ɴ�u����� ������ʼ��������INF
        //�䷴��������0
        addEdge(u+n,v,INF);//u��v������ʼ����ΪINF ����v->u+n��ʼ����Ϊ0
        addEdge(v+n,u,INF);//v��u������ʼ����ΪINF ����u->v+n��ʼ����Ϊ0
    }
    /*
    ���ﲻ��ɾ��Դ��c1��c1+n֮�������,��ᵼ��ɾ��c1�����,�Ǿ�ֱ����c2�ָ���,�����Ϊ1,
    ��ʼԴ��Ҫ��c1+n(c1Դ��ĳ���)��ʼ.
    �𰸴���,Դ�����Ҫ��c1+nԴ������ȥ�ı߿�ʼ
    */
    printf("%d",maxFlow(c1+n,c2));//���i��i+n֮��ĸ�� ��С�:��С��� ��Ч�������
    return 0;
}

/*
//ac 25ms dinic ��ǰ���Ż� ���
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 250
#define M 1500
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,next,f;
}edge[M<<1];
int n,m,head[N],cnt,vis[N],d[N],cur[N];

void addEdge(int from,int to,int f){
    edge[cnt]=(node){to,head[from],f};
    head[from]=cnt++;
    edge[cnt]=(node){from,head[to],0};
    head[to]=cnt++;
}

void init(int s){
    memset(d,-1,sizeof(d));//Դ������0,���������-1,�ж���dis[v]==-1,�ɱ���ʹ��!dis[v]ʹ��Դ���ٴ����
    d[s]=0;
}

bool bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].f>0 && d[v]==-1){
                d[v]=d[u]+1;
                if(v == t) return true;
                Q.push(v);
            }
        }
    }
    return false;
}

int dfs(int u,int t,int flow){
    if(u == t) return flow;
    int v,incf,res=0;
    for(int i=cur[u];i!=-1;i=edge[i].next){
    	cur[u]=i;
        v=edge[i].to;
        if(edge[i].f>0 && d[v]==d[u]+1){
            incf=dfs(v,t,min(flow,edge[i].f));
            if(incf>0){
                edge[i].f-=incf;
                edge[i^1].f+=incf;
                flow-=incf;
                res+=incf;
            }
            if(flow == 0) return res;
        }
    }
    if(res == 0) d[u]=-1;
    return res;
}

int maxFlow(int s,int t){
    int sum=0;
    while(bfs(s,t)){
    	for(int i=1;i<=2*n;i++)
    		cur[i]=head[i];
		sum+=dfs(s,t,INF);
	}
    return sum;
}

int main(){
    int c1,c2,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    scanf("%d%d",&c1,&c2);
    for(int i=1;i<=n;i++)
        addEdge(i,i+n,1);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u+n,v,INF);//������Ϊ1  �����С������ֵ��Ϊ�������
        addEdge(v+n,u,INF);
    }
    printf("%d",maxFlow(c1+n,c2));//����߸��� ���������-��С���,ת��Ϊ��������
    return 0;
}
*/

/*
//ac 23ms EK�㷨 bfs��������·
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 250
#define M 1500
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],pre[N],incf[N],sum;
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
}

void init(int s){
    memset(pre,-1,sizeof(pre));
    incf[s]=INF;
}

int bfs(int s,int t){
    queue<int> Q;
    init(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        if(u == t) return 1;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && pre[v] == -1){
                incf[v]=min(incf[u],edge[i].cf);
                pre[v]=i;
                Q.push(v);
            }
        }
    }
    return 0;
}

int max_flow(int s,int t){
    int ans=0,v;
    while(bfs(s,t)){
        v=t;
        while(v!=s){
            edge[pre[v]].cf-=incf[t];
            edge[pre[v]^1].cf+=incf[t];
            v=edge[pre[v]^1].to;
        }
        ans+=incf[t];
    }
    return ans;
}

int main(){
    int c1,c2,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    scanf("%d%d",&c1,&c2);
    for(int i=1;i<=n;i++){
        addEdge(i,i+n,1);//��㵽���� ����Ϊ1(ÿ����ֻ��ɾ��1��)
        addEdge(i+n,i,0);//���򻡳��㵽��� ����Ϊ0
    }
    while(m--){
        scanf("%d%d",&u,&v);
        //u-v�ǻ�ͨ��,��u�ĳ���ɴ�v�����,v�ĳ���Ҳ�ɴ�u����� ������ʼ��������INF
        //�䷴��������0
        addEdge(u+n,v,INF);//u��v ��ʼ����INF
        addEdge(v,u+n,0);//����v->u+n��ʼ����Ϊ0
        addEdge(v+n,u,INF);//v��u ��ʼ����INF
        addEdge(u,v+n,0);//����u->v+n��ʼ����Ϊ0
    }
    printf("%d",max_flow(c1+n,c2));//����߸��� ���������-��С���,ת��Ϊ��������
    return 0;
}
*/
