#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
//ac 148ms
/*
����:����һ��n����m��������ͼ,ÿ������һ��Ȩֵ,
��һ��·��,ʹ·�������ĵ�Ȩֵ֮�����.��ֻ��Ҫ������Ȩֵ��.
�����ξ���һ���߻���һ����,����,�ظ������ĵ�,Ȩֵֻ����һ��.
Ȩֵû�и�ֵ.
����:https://www.luogu.com.cn/problem/P3387
˼·:��Ϊ����ظ�����,Ȩֵֻ����һ��,���Կɿ���scc������Ϊһ������Ȩֵ����.
����dfs dp������·�����Ȩֵ���ۼӵ����ڵ�,
����ԭͼ���л�,����ͨ��tarjan���㽫ͼת����DAG,
����DAG�Ͻ�������dp��¼����SCC������Ȩֵ��.
*/

/*
����dp֮ǰҪ����ԭ��:
(������Ϊ��ͨ���������ﵽ��Сdp��ĸ���������ʱ�临�Ӷ�,
��Ϊ����Ҳ���ⲻ��tarjan���㱾��O(V+E)��ʱ��)
����ͼ
1->2->3->1,1->4->5
��Ϊԭͼ���л�1->2->3->1,ֱ��dp�Ļ�,���ڱ�����1-2->3
3->1 �ٻص�1��ʱ,��Ȼ1��Ҳ��������,����Ϊ���ܱ���1->4->5����·���ĵ�Ȩ��
��Ȼ�����ظ������ĵ㻹��Ҫ����������ȥ,�����������ص�1��ʱ,
1->2->3���ԭ�ȱ������Ļ�Ҳ�޷��������ֻ����,Ȼ�󲻶��������޵ݹ�,dfs���ܽ���.
���������������޻�ͼ(DAG),����������1->2->3->1
�����Ļ��ĵ�Ȩ�ͻ�����һ����(x)�ĵ�Ȩ��,�����ͻ�ͼ�ͻ���x->4->5,
��������������ĿҪ��"�����ξ���һ���߻���һ����,�ظ������ĵ�,Ȩֵֻ����һ��."
���ܱ�����1->2->3->1�����Ļ����������ݹ�,���ܻص�1�㽫1->4->5��һ��·��������.
���1��������1->6->7�����ĵ���,��dpʱ���ڱ���������x,��x->4->5 x->6->7��ѡ��,
Ȩֵ�ͽϴ��ȥ����,��Ϊ4->5 6-7����ʱ��û�лر���ȥ�������·��,����ѡ��һ��·��.
��ʵ�Ͼ���ͨ���������ǿ��ͨ�������ɵĻ�����ֱ�ӵ�����һ�������ĵ�(��Ȩ�ǻ������нڵ��Ȩ��),
�����Ͳ���ͨ���ٻص��������ĳ�ʼ�� ȥ�������·��,��Ϊ�����޷�����ԭ�ȱ������Ļ�,
�����������˻���Ӱ��,ֱ�ӽ�ԭͼ����˵���,ͨ����������һ���Ա������˻������е�,
�����žͿ��Ա�����ķ�֧�ĵ�.
*/

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int val[N],sum[N];
stack<int> s;
bool in[N];
int block[N],id;
int a[M],b[M];
int dis[N];//dis[u]������u�ڵ�Ϊ���׵���·���е���·������Ȩֵ��

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){//O(N+E)
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=true;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++id;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            sum[id]+=val[v];
            s.pop();
        }while(v != u);
    }
}

void dp(int u){//O(n) n����ĸ���
    dis[u]=sum[u];
    int v,maxWe=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        //������ȱ�������·�� ��ͳ��������·��Ȩֵ����,��������֧���ʹ�ֱ�ӱȽ�dp[v]�Ľ����֮ǰ�Ƿ�һ��
        //ѭ������dp���ĵ��п����ǵ������м�ĵ�v,��������ǵ�����ǰ��ĵ�u,����u�ٱ�����vʱֱ���ۼ�v������ĵ�Ȩֵ�;ͺ�
        //�������Ϊ���仯����.
        if(!dis[v]) dp(v);
        maxWe=max(maxWe,dis[v]);//ѡ��Ȩֵ�ͽϴ��������Ϊ·��
    }
    dis[u]+=maxWe;//������Ȩֵ���ۼӵ����׽����
}

int main(){
    int n,m;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a[i],&b[i]);
        addEdge(a[i],b[i]);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    memset(head,-1,sizeof(head));
    cnt=0;
    for(int i=1;i<=m;i++){
        if(block[a[i]] != block[b[i]])//��������Ӧ��ǿ��ͨ������Ų�ͬ,�����Ϊ����������֮��������
            addEdge(block[a[i]],block[b[i]]);//�������¹�ͼ,�����ɵ�ͼû��SCC,�������޻�ͼ(DAG),���ǽ�������dp���Ⱦ�����
    }
    int ans=0;
    for(int i=1;i<=id;i++){//�����п����Ծɲ�����ͨ��,���������ǹ�����,���Ҫ��ÿ����û�������ĵ����dp
        if(!dis[i]){
            dp(i);
            ans=max(ans,dis[i]);
        }
    }
    printf("%d\n",ans);
    return 0;
}

/*
//��������DAG��Ӧ�����·�㷨,��Ϊû��ָ�����,�����������������.
//ac 102ms
//��Ȼ���������޻�ͼDAG���ض��㷨�ܹ���������ͼ������·��,
//���Կ�����������,���������Ϊ0�ĵ㿪ʼ����,����ֻ��һ�ξ���
//������ͼ������·���������.���������·���Ĺ����н���dp.
//dis[u]������u�ڵ�Ϊ�յ�Ŀɵ���ĵ���·��������Ȩֵ��
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int val[N],sum[N];
stack<int> s;
bool in[N];
int block[N],id;
int a[M],b[M];
int dis[N],inde[N],ans;

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){//O(N+E)
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=true;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++id;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            sum[id]+=val[v];
            s.pop();
        }while(v != u);
    }
}

void topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i]){
            dis[i]=sum[i];
            Q.push(i);
        }
    }
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        ans=max(ans,dis[u]);
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            dis[v]=max(dis[v],dis[u]+sum[v]);
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int n,m;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a[i],&b[i]);
        addEdge(a[i],b[i]);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    memset(head,-1,sizeof(head));
    cnt=0;
    for(int i=1;i<=m;i++){
        if(block[a[i]] != block[b[i]]){//��������Ӧ��ǿ��ͨ������Ų�ͬ,�����Ϊ����������֮��������
            addEdge(block[a[i]],block[b[i]]);//�������¹�ͼ,�����ɵ�ͼû�лر�,���ṹ�ɻ�,�������޻�ͼ(DAG),���ǽ�������dp���Ⱦ�����
            inde[block[b[i]]]++;
        }
    }
    topSort();//��ʼ���������Ϊ0�ĵ����,���ܽ�DAG������·���������
    printf("%d\n",ans);
    return 0;
}
*/
