#include<cstdio>
#include<algorithm>
#define N 100
#define M 5000//��Ϊ����ȫͼ ����n*(n-1)/2=4950
using namespace std;
//kruskal
/*
����:n���㹹�ɵ�����,ÿ�����������ж�������,
ÿ��������һ������,������ʹ�����е��໥��ͨҪ����
����̵��µĳ���.
����:http://poj.org/problem?id=1287
˼·:��С��ģ����.
*/

int n,m,fa[N];

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,sum=0,cnt=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    while(scanf("%d",&n)&&n){
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("%d\n",kruskal());
    }
    return 0;
}

/*
//prim
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5000
using namespace std;

int n,m,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
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
        sum+=dis[u];
        num++;
        if(num == n) return sum;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return sum;
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)&&n){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        printf("%d\n",prim(1));
    }
    return 0;
}
*/

/*
//prim ������dis,����δ����mst�ĵ�ı�Ȩֱ�����,pop��������,Ч�ʽϵ�
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define M 5000
using namespace std;

int n,m,cnt,head[N],vis[N];

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
}

int prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,sum=0,num=0;
    pair<int,int> tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.second;
        Q.pop();
        if(vis[u]) continue;
        sum+=-tmp.first;
        num++;
        if(num == n) return sum;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //����δ����mst�ĵ�ı�Ȩֱ�����,����ʱֻ������Ȩ��С�ĵ�,����pop��������
            if(!vis[v])
                Q.push(make_pair(-edge[i].w,v));
        }
    }
    return sum;
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)&&n){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        printf("%d\n",prim(1));
    }
    return 0;
}
*/
