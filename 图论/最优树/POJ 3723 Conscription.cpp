#include<cstdio>
#include<algorithm>
#define N 21000
#define M 51000
using namespace std;
//kruskal 329ms

/*
����:n��Ů��m���к�,����Ҫ����,ÿ����10000Ԫ�����,
��֪�к���Ů��������Ź�ϵȨ��d,��һ�����Ѿ������������,
��һ��������ķ���Ϊ10000-dԪ,�����ٵ���������.
����:http://poj.org/problem?id=3723
˼·:����ÿ����ֻ������һ�η���ֻ����һ��,��ô��������յĹ�ϵ������Ȼ�����л�·,
��Ϊ�л�·һ���˾ͻ�������,��ô��ʵ�������������ͨ������Ȩ��.�����Ĺ�ϵ��һ��
��һ����ͨ��,�����Ƕ����ͨ����.������kruskal����Щ,primһ��ֻ�ܼ���һ����ͨ������
����Ȩ��.�������յ���С���Ѿ��� 10000*(n+m)-sum(max).
*/
int n,m,r,fa[N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w>x.w;
    }
}edge[M];

void init(){
    for(int i=0;i<n+m;i++)
        fa[i]=i;
    sort(edge+1,edge+1+r);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,sum=0,cnt=0;
    for(int i=1;i<=r;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n+m-1) break;
        }
    }
    return sum;
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&r);
        for(int i=1;i<=r;i++){
            scanf("%d%d%d",&u,&v,&w);
            edge[i]=Edge(u,v+n,w);//v+n ��ʾ�����ı�Ų��ܺ�Ů������غ�
        }
        printf("%d\n",10000*(n+m)-kruskal());
    }
    return 0;
}
/*
//prim 422ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 21000
#define M 51000
using namespace std;

int n,m,r,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(dis,0,sizeof(dis));
    dis[s]=0;
}

int prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,sum=0,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        sum+=dis[u];
        num++;
        if(num == n+m) return sum;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w>dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return sum;
}

int main(){
    int T,u,v,w,sum;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        scanf("%d%d%d",&n,&m,&r);
        while(r--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v+n,w);
            addEdge(v+n,u,w);
        }
        //ԭͼ���ܲ�����ͨ,����Ҫ��������ͨ�����е����Ȩֵ�������,��Ҫ���prim,��vis�����
        for(int i=0;i<n+m;i++){
            if(!vis[i])
                sum+=prim(i);
        }
        printf("%d\n",10000*(n+m)-sum);
    }
    return 0;
}
*/
