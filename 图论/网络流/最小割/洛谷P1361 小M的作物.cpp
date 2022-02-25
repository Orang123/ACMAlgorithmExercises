#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 42000
#define M 4004000//����Ŀ�����ݷ�Χ����Ŀ��������,ʵ�ʵ��Ͻ�ﵽ�˰���,2���򼴿�,������Ŀ����,����10W�о��Ϳ�
#define INF 0x3f3f3f3f
using namespace std;
//ac 545ms dinic ��С��=����� ���ݽϴ�,EK�㷨��TLE.

/*����صĸ���
����ÿ��·������ȥ��С�������ߣ��Դﵽ·�������Ҵ�����С��Ҳ���Ƕ�ѡһ��
����һ��������ͼG=(V,E),���Ķ���Ϊһ�ֵ�Ļ��ַ�ʽ:�����еĵ㻮��ΪS��T=V-S
��������,����Դ��s����S,���t����T��
�������:���Ƕ����(S,T)������c(S,T)��ʾ���д�S��T�ıߵ�����֮��
��С��:��С�������һ����(S,T)ʹ�ø������c(S,T)��С��
����N��һ����Ƿ���Դ�ͻ�Ļ�֮���ϡ�
�����-��С���:�����=��С��,������������������ÿ������·�����ӵ����պ�
����������·������С�Ĳ�������,����С�Ĳ��������ۼ������պú���С�������,������ô���,
�����������·��ѡȡ����С������������С���еĸ��û��һ���ϵ,���������ֵ����ȡ�

�������
ֻ��Ҫ��ÿ���ߵ�������Ϊ1,Ȼ������������������.
*/

/*
����:СM��MC�￪��������޴�ĸ���A��B(�������Ϊ����������),
����СP��n�����������,ÿ�������������1��(���ǿ�����һ������)(��1...n���).
���ڵ�i��������ֲ��A����ֲ���Ի��ai������,��B����ֲ���Ի��bi������,
�������ڻ�����ôһ�����������,����ĳЩ���ﹲͬ����һ������п��Ի�ö��������,
СM�ҵ��˹����й���m���������,��i������е����ﹲͬ����A�п��Ի��c1i�Ķ�������,
��ͬ����B�п��Ի��c2i�Ķ�������.СM�ܿ���������ֲ���������,��������Ҫ������,
���ܻش����������ô?
����:https://www.luogu.com.cn/problem/P1361
˼·:
����ѡ��һ����ģ��
��Ŀ����˼������n������ֻ������A�ػ�B����,����ѡ������A����Ͳ�������B����
���ǿ��Թ���ͼ��ģ������������ϵ,����A��B���ص���Դ��(s)�ͻ��(t),����i����A����
��ô��s��һ��ָ��i��������,�����������Ϊ�ߵĲ�������,��������B����,��ô��i����һ��
ָ����(t)�������,�ñߵĲ�������ͬ��Ϊ����������,��������ĳ������������ͬʱ����A�ػ�
B�ػ������������档�����������ֲʹ�û�õ��������,��������һ��ì�ܵ�����,��Ϊ����ֻ��
ѡ������A�ػ�B��һ�ַ�ʽ,��Ӧ��ͼ��������������i�������ӵ�Դ��ͻ��ı�ֻ��ѡ��һ��
(��:����ѡ��һ),����Ҫ������ѡ���������������Щ�߼�,��ôʵ�����Ǿ���Ҫɾ����Щ������С
�ı߼����,���ﵽ����Դ��ͻ�����ӵ�����,��ô��Ȼ����һ����С�������,���������-��С���
(�����=��С��)���ǿ���ת��Ϊ�����������ȥ�������ڻ�������������,���Ƕ�������,���ǿ��Կ���
����һ�����x,������ʾ������A�ػ�B�ص�һ������(i��j)���,��Դ��(s)��һ�������ָ��x��,������Ϊ
������Ķ�������,ͬʱ��x��������е�ÿ���㶼�������,����ΪINF,Ȼ���ٹ���һ�����yͬ����ʾi��j����
ͬʱ����B�ص����,������е�����i��j�����������y,����ΪINF,Ȼ��y��������(t)��һ�������,��������
Ϊ����i��jͬʱ����B����������������.
ע��:���������������ѡ����A��,��B�ص����߱�Ȼ������ѡ,��Ϊ��Ҫ��������Դ�ͻ�.
��Ȼ���Ȿ��Ҳ�����Ķ���.

������������:������С��,���x��s�������ߴ���,�Ǳ�Ȼ����еĵ�����(t)�����߶����ж�,����y�����������ı�Ҳ���ж�,
����ΪʲôҪ��ô��ֻ�����Ǵ���Ŀ�����۸����������,�����ٴ���С��ĽǶ�����һ��,����i��j��������(t)�ı߶��Ѿ��ж�,
�����ڴ�s->x->i->y->t��s->x->j->y->t���ܵ�����t,��Ϊ�����ѹ�����x->i,i->y��ΪINF(�����),��Ȼ��С���߲���ѡ������,
���Ҽ�ʹѡ��������,��ôj����x��y�����ı�Ҳ���е�,���ǿ���ѡ��ֻ�е�y�����������ı�,��������"��С"�
ʵ�ʹ���s->i->t,s->j->t�������ô�е�,Ҳ�Ǹ�����С��ĸ�������ܺ���Сȥ�е�,ֻ�е�ʵ�����г���ߺ�ʣ�������ı����������ʱ,
��С�������С�ġ�����˵����Ҳ�������۵�����min(c(s->i),c(i->t))ȡ����������A�ػ�B��(�ֲ�)�����С���Ǹ���λ���,����
�Ӹ�߼����бߵ������ܺ���С(ȫ��)�����ǵġ������������Ĺ��̺���С��û�й���(���������С������������С��ĸ�߿���û�й���),
ֻ������ֵ�������������С��.
*/

/*
����������:
S��ÿ���㽨�ߣ�����Ϊ����A�����棬ÿ������T���ߣ�����Ϊ����B�����棬����ÿһ���㣬
���Ǳ�ȻҪ�������S��T��һ���ҽ�һ���ߡ����ڸ�֮���ͼ��S���ĵ��ѡ��������A��
T���ĵ��ѡ��������B���Ƕ��ڹ�ͬ����A���ж�������ĵ���ô���أ��������½�һ����x��S��x���ߣ�
����Ϊ���棬x��������Ҫ��ͬ����A�ĵ����ߣ�����Ϊinf���������Щ����һ����û�и����T�����ߣ�
�����Ʊ�Ҫ������������ߡ��������������û���������˵��������Ҫ�ĵ���󶼸�����T�����ߣ�
Ҳ���Ƕ���S���У�Ҳ���Ƕ�������A���������⡣���ڹ�ͬ����B���ж��������Ҳͬ��
�½�һ����x��x��T���ߣ�����Ϊ���棬������Ҫ��ͬ����B�ĵ���x���ߣ�����Ϊinf�������𰸾���������-��С�
*/
struct node{
    int to,next,f;
}edge[M];
int head[N],cnt,vis[N],d[N];

void addEdge(int from,int to,int f){
    edge[cnt].to=to;
    edge[cnt].f=f;
    edge[cnt].next=head[from];
    head[from]=cnt++;
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
    int n,a,b,s,t,m,k,c1,c2,h,ans=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    s=n+1,t=n+2;//Դ����n+1 �����n+2
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        ans+=a;
        addEdge(s,i,a);//i��������A�� s����i�������
        addEdge(i,s,0);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b);
        ans+=b;
        addEdge(i,t,b);//i��������B�� i����t�������
        addEdge(t,i,0);
    }
    scanf("%d",&m);//m����� ���� ��� ������A�ش�(n+2)+1��ʼ��� ������B�ش�(n+2+m)+1��ʼ���
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&k,&c1,&c2);//����ϰ���k������
        ans+=c1+c2;
        addEdge(s,n+2+i,c1);//n+2+i��������ﶼ����A�� ��õĶ�������C1
        addEdge(n+2+i,s,0);
        addEdge(n+2+m+i,t,c2);//n+2+m+i��������ﶼ����B�� ��õĶ�������C2
        addEdge(t,n+2+m+i,0);
        while(k--){
            scanf("%d",&h);
            addEdge(n+2+i,h,INF);//������X�� ������е�ÿһ�����������
            addEdge(h,n+2+i,0);
            addEdge(h,n+2+m+i,INF);//����ڵ�ÿһ��������� ������Y������
            addEdge(n+2+m+i,h,0);
        }
    }
    printf("%d\n",ans-maxFlow(s,t));//�����С��,����Щì�ܵĸ��ɾ��,ʣ�µľ����������,��:�������-�����
    return 0;
}

/*
//ac 437ms dinic ��ǰ���Ż�
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 42000
#define M 4004000
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
struct node{
    int to,next,f;
}edge[M];
int head[N],cnt,vis[N],d[N],cur[N];

void addEdge(int from,int to,int f){
    edge[cnt].to=to;
    edge[cnt].f=f;
    edge[cnt].next=head[from];
    head[from]=cnt++;
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
        cur[u]=i;//��ǰ���Ż�
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
        for(int i=1;i<=2*n+m+2;i++)
            cur[i]=head[i];
        sum+=dfs(s,t,INF);
    }
    return sum;
}

int main(){
    int a,b,s,t,k,c1,c2,h,ans=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        ans+=a;
        addEdge(s,i,a);
        addEdge(i,s,0);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b);
        ans+=b;
        addEdge(i,t,b);
        addEdge(t,i,0);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&k,&c1,&c2);
        ans+=c1+c2;
        addEdge(s,n+2+i,c1);
        addEdge(n+2+i,s,0);
        addEdge(n+2+m+i,t,c2);
        addEdge(t,n+2+m+i,0);
        while(k--){
            scanf("%d",&h);
            addEdge(n+2+i,h,INF);
            addEdge(h,n+2+i,0);
            addEdge(h,n+2+m+i,INF);
            addEdge(n+2+m+i,h,0);
        }
    }
    printf("%d\n",ans-maxFlow(s,t));
    return 0;
}
*/

/*
//EK �㷨TLE O(V*E^2) E<=4*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 3100
#define M 4000100
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
    int a,b,c1,c2,k,v;
    cnt=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        sum+=a;
        addEdge(0,i,a);
        addEdge(i,0,0);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b);
        sum+=b;
        addEdge(i,n+1,b);
        addEdge(n+1,i,0);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&k,&c1,&c2);
        sum+=c1+c2;
        addEdge(0,n+1+i,c1);
        addEdge(n+1+i,0,0);
        addEdge(n+1+m+i,n+1,c2);
        addEdge(n+1,n+1+m+i,0);
        while(k--){
            scanf("%d",&v);
            addEdge(n+1+i,v,INF);
            addEdge(v,n+1+i,0);
            addEdge(v,n+1+m+i,INF);
            addEdge(n+1+m+i,v,0);
        }
    }
    printf("%d",sum-max_flow(0,n+1));
    return 0;
}
*/
