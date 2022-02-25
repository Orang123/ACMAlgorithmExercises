#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1500
#define M 3000000
#define INF 0x3f3f3f3f
using namespace std;
//ac 124ms dinic O(V^2*E) �������Զ������,Ϊ����ͼ
//�ο����:https://www.pianshen.com/article/216862946/
//EK �㷨��ʱ O(V*E^2)
/*
����:n������,m������,��������i,��si�쿪ʼ����,��Ҫpi����ܴ�����,
��ֹei��,һ̨����һ��ֻ�ܴ���һ������,��ÿ������һ�����ֻ����һ̨
��������.����,һ����������ڲ�ͬ��ʱ���ڲ�ͬ�Ļ������жϺʹ���.
������Ҫ�ж��Ƿ���ڿ��е�ʱ�䰲�����ڹ涨ʱ���ڽ�������������,
�������"Yes",�������"No".
����:http://acm.hdu.edu.cn/showproblem.php?pid=3572
˼·:Ϊһ������ֻ��m̨������ʹ��,��Ȼ��Ҫ����ͬ���������ڲ�ͬ�Ļ�����
���Һ������ÿ������ִ�е���,���Թ���һ��Դ��0,Դ����ÿ������i��0->i,����
Ϊpi�������,ÿ������i�� ����Ŀ�ʼ���������ڵ���j�ֱ𽨱�i->j+n,��������Ϊ1,
����һ������ɰ����ڲ�ͬ���촦��,���Ҹ������������ֻ�ܰ���һ��(����Ϊ1),Ȼ��
ÿ����j+n����ed����,j+n->ed����Ϊm,��������ڿɹ�ʹ�õĻ��������Ϊm,edΪ����
�������+n+1,��Ȼ�������ÿ����������·��С����������Ϊ1,������ĳ��������ĳ����
ĳ������ִ��,�������ans������ɾ����ܶ�����ÿ���������������ܺ�,����ֻҪ�ж�ans
�Ƿ���������������������ܺ�sum,���ھ�˵�����������������,�����ھ�˵�������ں����
ʱ�䰲���������������.
*/
int cas,n,m,p,s,e,st,ed,sum,cnt,head[N],dis[N];
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
}

int bfs(int s){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                flow-=incf;
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                res+=incf;
            }
            if(!flow)
                return res;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(){
    int ans=0;
    while(bfs(0))
        ans+=dfs(0,INF);
    return ans;
}

void init(){
    cas++;
    sum=ed=cnt=0;
    st=INF;
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);//n������,m������
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&p,&s,&e);//����i��Ҫִ��p��,��s�쿪ʼ,e�����
            sum+=p;
            st=min(st,s);//st��������������ʱ��,��ʼ����С�ı��
            ed=max(ed,e);//ed��������������ʱ��,��ʼ�����ı��
            addEdge(0,i,p);//Դ��->����i ����Ϊp
            addEdge(i,0,0);
            for(int j=s;j<=e;j++){
                addEdge(i,j+n,1);//ÿ������i��s~e��ÿһ������Ϊ1�ı�
                addEdge(j+n,i,0);
            }
        }
        ed+=n+1;//���������������+n+1
        for(int i=st;i<=ed;i++){//���п����콨����� ����Ϊm�ı�,��Ϊÿһ��ֻ��m̨�����ܹ���
            addEdge(i+n,ed,m);
            addEdge(ed,i+n,0);
        }
        printf("Case %d: %s\n",cas,max_flow() == sum?"Yes":"No");
        printf("\n");
    }
    return 0;
}

/*
//ac 93ms dinic ��ǰ���Ż�
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1500
#define M 3000000
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,p,s,e,st,ed,sum,cnt,head[N],cur[N],dis[N];
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
}

int bfs(int s){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=cur[u];i!=-1;i=edge[i].next){
        cur[u]=i;
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                flow-=incf;
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                res+=incf;
            }
            if(!flow)
                return res;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(){
    int ans=0;
    while(bfs(0)){
        for(int i=0;i<ed;i++) cur[i]=head[i];
        ans+=dfs(0,INF);
    }
    return ans;
}

void init(){
    cas++;
    sum=ed=cnt=0;
    st=INF;
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&p,&s,&e);
            sum+=p;
            st=min(st,s);
            ed=max(ed,e);
            addEdge(0,i,p);
            addEdge(i,0,0);
            for(int j=s;j<=e;j++){
                addEdge(i,j+n,1);
                addEdge(j+n,i,0);
            }
        }
        ed+=n+1;
        for(int i=st;i<=ed;i++){
            addEdge(i+n,ed,m);
            addEdge(ed,i+n,0);
        }
        printf("Case %d: %s\n",cas,max_flow() == sum?"Yes":"No");
        printf("\n");
    }
    return 0;
}
*/
