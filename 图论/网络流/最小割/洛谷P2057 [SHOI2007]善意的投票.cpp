#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 320
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;
//ac 24ms dinic ��С��=�����
/*
����:�׶�԰����n��С���Ѵ���ͨ��ͶƱ������˯��˯���.
��������˵,������Ⲣ���Ǻ���Ҫ,�������Ǿ�������ǫ�þ���.
��Ȼÿ���˶����Լ�������,����Ϊ���չ�һ���Լ����ѵ��뷨,
����Ҳ����Ͷ���Լ�������Ը�෴��Ʊ.���Ƕ���һ��ͶƱ�ĳ�ͻ��
Ϊ������֮�䷢����ͻ���������Ϻ����к��Լ�������Ը������ͻ������.
���ǵ��������,ÿλС����Ӧ������ͶƱ,����ʹ��ͻ����С?
����:https://www.luogu.com.cn/problem/P2057
˼·:һ��С����ͶƱ����˯��˯��,ֻ����һ��ѡ��:ͬ��˯���򷴶�˯��.
���Ҷ��ں�����֮��Ĺ۵�Ӧ����һ�¡�����ͼ��ģ��,Դ��s,���t,s->i(flow=1)��ʾ
iͬѧͬ��˯��,j->t(flow=1)��ʾjͬѧ����˯��,����i��j�Ǻ�����,�򹹽�i->j j->i ��
˫���,˫��߱�֤i��j����Ҫ��Է����Լ�ͬ����,��Ϊ�����i��j�ĸ��Ǵ�Դ�����,
��Ҫ��֤����s��t����ͨ��.��ô�������iͬѧͬ��,jͬѧ����,���������Ǻ�����,������
����������Դͨ�����ı�s->i->j->t,i��ͬ���,j�Ƿ���,����i->j j->i��������֮�䶼Ҫ
��Է���ͬ�Լ��Ĺ۵�,����ì�ܵ�,��ô����ѡ����s->i��j->t��ʹ��i��ͬj�Ĺ۵��j��ͬ
i�Ĺ۵�,���߸��i->jʹ��֮�䲻�������ѹ�ϵ,������֮��Ĺ۵�ɲ�ͬ,��ϸ�����ⲻ����
�Ҹ,��С��ʹ�÷���Դ�ͻ��Ŀ����.
������Ŀ����ì�ܳ�ͻ1.������֮�䷢����ͻ������2.���к��Լ�������Ը������ͻ������
2��ͻʵ���Ͼ�����1��ͻ�����µ�,���С����֮�䲻���ں����ѹ�ϵ,��ʹ����ͶƱ��Ը��ͬ,
Ҳ�������ì�ܹ�ϵ,��Ϊ����Υ�������ѵ���Ը,Ҳ����Ϊ�˺ͺ����ѵ���������һ�¶�Υ��
���������Ը,�����1+2��ì�ܳ�ͻ�ܺ� ���������ì������Ҫ�г�����С����,�������
������,��ô��ÿ���ߵ���������Ϊ1 �����С��������;��Ǹ�ߵ�����,����ֱ��ת��Ϊ���
�����.

eg:
ʵ�ʶ���iͬ��,j��ͬ��,kͬ��,Ȼ��i-jΪ����,j-kΪ����,�������k����Ը�������i����Ը,
����ì������Ϊ2,�����������j����Ը,��û��ì����,ì����Ϊ1.

ע��:һ����A����>B�ı�,��ʾAҪ��Bͬ��ͬ����
��ôΪʲô������֮����Ҫ��˫����ǲ��Ǿͽ����?
�����ѻ���Ҫ��Է�ͬ�Լ�һ������
�����������,���ǻ����Զ�Ƕ�˼��:
�������ǿ��Ե�������:����������֮���ǵ����?��ô����ͼ�����߲�ͨ��,Ҳ�Ͳ����ڳ�ͻ��,��Ȼ����
Ҳ���ԴӶԳ��ԵĽǶ�����:A��B�����ѹ�ϵ����Ե�,�������Ȼ�����϶Գ���.
*/
struct node{
    int to,next,f;
}edge[M<<1];
int head[N],cnt,vis[N],d[N];

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
    int n,m,p,s,t,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&p);
        if(p) addEdge(s,i,1);//iͬѧͬ��˯�� ������Ϊ1 �����������
        else addEdge(i,t,1);//iͬѧ����˯��
    }
    while(m--){
        scanf("%d%d",&u,&v);
        //u��v֮�以Ϊ���ѹ�ϵ,��Ϊu��v��ȷ��˭�ǿ���Դ��s�����ĵ�,
        //�����Ҫ�������������ߵĳ�ʼ������Ϊ1,�������ܱ�֤������s����t�����ڳ�ʼ����Ϊ0������·,���ܱ�֤ͼ����ͨ��.
        addEdge(u,v,1);//u->v����uҪ��v����ͬ����
        addEdge(v,u,1);//v->u����vҪ��u����ͬ����
    }
    printf("%d",maxFlow(s,t));//����߸��� ���������-��С���,ת��Ϊ��������
    return 0;
}

/*
//ac 25ms dinic ��ǰ���Ż�
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 320
#define M 100000//����Ŀ�����ݷ�Χ����Ŀ��������,ʵ�ʵ��Ͻ�ﵽ�˰���,2���򼴿�,������Ŀ����,����10W�о��Ϳ�
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
        for(int i=1;i<=n+2;i++)
            cur[i]=head[i];
        sum+=dfs(s,t,INF);
    }
    return sum;
}

int main(){
    int p,s,t,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&p);
        if(p) addEdge(s,i,1);
        else addEdge(i,t,1);
    }
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v,1);
        addEdge(v,u,1);
    }
    printf("%d",maxFlow(s,t));
    return 0;
}
*/

/*
//ac 26ms EK�㷨 bfs��������·
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 3100
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],pre[N],incf[N],sum;
struct Edge{
    int to,next,cf;
}edge[M];

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
    int p,s,t,u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&p);
        if(p){
            addEdge(s,i,1);//iͬѧͬ��˯�� ������Ϊ1 �����������
            addEdge(i,s,0);
        }
        else{
            addEdge(i,t,1);//iͬѧ����˯��
            addEdge(t,i,0);
        }
    }
    while(m--){
        scanf("%d%d",&u,&v);
        //u��v֮�以Ϊ���ѹ�ϵ,��Ϊu��v��ȷ��˭�ǿ���Դ��s�����ĵ�,
        //�����Ҫ�������������ߵĳ�ʼ������Ϊ1,�������ܱ�֤������s����t�����ڳ�ʼ����Ϊ0������·
        addEdge(u,v,1);
        addEdge(v,u,1);
    }
    printf("%d",max_flow(s,t));//����߸��� ���������-��С���,ת��Ϊ��������
    return 0;
}
*/
