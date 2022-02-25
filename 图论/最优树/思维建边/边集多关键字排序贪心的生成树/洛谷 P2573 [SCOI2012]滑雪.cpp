#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define N 100100
#define M 1000100
using namespace std;
typedef long long ll;
//prim ac 1.02s
/*
����:n����,m������Ȩֵ,ÿ�����и��߶�,һ���˳�ʼ��1��,
�����u����v,��u�ĸ߶ȱ��벻С��v�ĸ߶�,�����������
��1������ܵ���ĵ���,�Լ������������е������ѵ���СȨֵ��,
ע������˿�����ѻ��˵������ĵ�,������Ҫ����.
����:https://www.luogu.com.cn/problem/P2573
˼·:�����������ͼ�е���С������.���ǲ���prim�㷨,����prim�㷨����ȷ��
��Ҫ����������ͼ��,��������ͼ��̰�ĵ���ȷ���޷���֤,������Ŀ������u->v,
h[u]>=h[v],������Ҫ�޸�prim�㷨ÿ�δ�δ�����ѡ������Ѽ�����������ĵ�
�����Ѽ���㼯����,��һ����,��Ϊ����������ͼ,�¼���ĵ�����Ǹ߶Ƚϵ͵ĵ�,
����һЩ��δ����ĵ�����Ǹ߶Ƚϸߵĵ�,��ͳ�ƾ����Ѽ�������������ʱ��,�߶Ƚϴ�ĵ��޷�
���ǵ�(��ʹ��Ȩ��С),����̰�ĵ���ȷ���޷���֤,���һֱ���վ�����������,����Ȩֵ�Ϳ��ܲ�������С��.����
�������Ȱ���δ����ĵ�����߶Ȳ�ͬ,���ո߶ȵݼ���˳�����,�������ܱ�֤ÿ������ߵ�Ȩֵ���յ���ͬ
ʱ����ͬʱ����,��Ϊ�����ǰ��ո߶ȵݼ�����,������ӵ��Ǹ߶Ƚϵ͵�,��ôҲ�����ں����ĵ���ǰ���Ѽ��뼯��
�ĵ�������,��ȷ�Ծ͵��Ᵽ֤.���ڸ߶���ͬ,���Ȼ��˫���,�Ͱ�����ľ����������.
*/

int n,m,cnt,head[N],vis[N],h[N],num;
ll dis[N],sum;

struct Edge{
    int to,next;
    ll w;
}edge[M<<1];

struct state{
    int v;
    ll dis;
    state(int v=0,ll dis=0):v(v),dis(dis){}
    bool operator < (const state &x)const{
        //�߶Ȳ�ͬʱ,���ո߶ȵݼ�����,�����ڳ���ʱ��ͬһ�յ���ܿ��Ǹ��������
        if(h[v]!=h[x.v]) return h[v]<h[x.v];
        return dis>x.dis;//�߶���ͬ����˫���,�Ͱ�����ľ����������
    }
};


void addEdge(int from,int to,ll w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void prim(int s){
    init(s);
    priority_queue<state>Q;
    Q.push(state(s,0));
    int u,v;
    state tmp;
    while(!Q.empty()){
        u=Q.top().v;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        num++;
        sum+=dis[u];
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(state(v,dis[v]));
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        if(h[u] >= h[v])
            addEdge(u,v,w);
        if(h[u]<=h[v])
            addEdge(v,u,w);
    }
    prim(1);
    printf("%d %lld",num,sum);
    return 0;
}

/*

//kruskal ac 1.20s
//����bfsͳ������ܷ��ʵĵ�,�����ܷ��ʵıߴ����µı߼�
//���±߼�����߶Ȳ�ͬ���ո߶ȵݼ�����,����Ȩֵ��������,�ٶ��µı߼�kruskal���mst����
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 1000100
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],fa[N],h[N],vis[N],num;
ll sum;

struct Edge{
    int u,v;
    ll w;
    Edge(int u=0,int v=0,ll w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        //�߶Ȳ�ͬʱ,�Ȱ��߶���,���ܱ�֤kruskal�ϲ�ʱ,�ߵ������Եõ���֤,��Ϊֱ�Ӱ���Ȩ��,����ָ߶ȵ͵ĵ㵽��߶ȸߵĵ�ı�
        //���߶Ƚϵ͵ĵ���ԶҲ�޷�����߶Ƚϸߵĵ�,����Ҳ��֤��̰�ĵ���ȷ��.
        if(h[v]!=h[x.v]) return h[v]>h[x.v];
        else return w<x.w;//�߶���ͬʱ,����ͬһ�����ѡ���Ȩ��С������
    }
}edge[M];

struct Node{
    int to,next;
    ll w;
}node[M<<1];

void addEdge(int from,int to,ll w){
    node[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,cnt=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == num-1) break;
        }
    }
}

void bfs(int s){
    queue<int> Q;
    Q.push(s);
    vis[s]=1;
    num++;
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=node[i].next){
            v=node[i].to;
            edge[++m]=Edge(u,v,node[i].w);
            if(!vis[v]){
                vis[v]=1;
                num++;
                Q.push(v);
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        if(h[u]>=h[v]) addEdge(u,v,w);
        if(h[u]<=h[v]) addEdge(v,u,w);
    }
    m=0;
    bfs(1);
    kruskal();
    printf("%d %lld",num,sum);
    return 0;
}

*/
