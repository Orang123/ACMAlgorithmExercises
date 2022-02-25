#include<cstdio>
#include<algorithm>
#define N 110
#define M 6000
using namespace std;
//Kruskal ��³˹�����㷨 �ӱ߿���
/*
����:Ҫ��n����ׯ��·,��������n����ׯ����n(n-1)/2������(��ȫͼ),
�������ׯ��·����С����.
ע:������һ������ͨ��,��Ϊ����ȫͼ.һ����ڲ���ͨ�������Ŀ��������˵��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1233
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
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            sum+=edge[i].w;
            cnt++;
            //������ֱ��return �����,n=1ʱ������������ѭ��,û��·Ҫ��,���ص���0
            if(cnt == n-1) break;
        }
    }
    //����1����0���ߵ���� cnt=0=n-1 ��ʵ����ͨ�ĵ��������ѭ��,�����жϲ���ͨһ��Ҫ��ѭ����Χ�ж�cnt!=n-1,������ѭ��������flag
    //һ�������Ŀ�Բ���ͨ����������Ҫ��,
    //����cnt==n-1ʱ���ñ��,���������ʹ����ͨ,���������СȨֵ��
    return sum;
}

int main(){
    while(scanf("%d",&n)&&n){
        m=n*(n-1)/2;
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("%d\n",kruskal());
    }
    return 0;
}
/*
//prim ����ķ�㷨 �ӵ㿼��
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 6000
using namespace std;
//minimum spanning tree(��С������)
int n,m,head[N],cnt,dis[N],vis[N];

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
    dis[s]=0;//����Ҫ��ʼ�� ��Ϊ���Ѻ�sum+=dis[u]
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
            //�����п��ܺ�����չ���ĵ��Ȩ��СһЩ,������ǰ����mst�ĵ��Ȩ�ǽϴ��,���Ҫ����dis
            //�������µ����ظ�����mst,sum�����ƫ��,���Լ���mstһ��Ҫ�жϱ���Ϊmst֮��ĵ�
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    //mst�еĵ����ﲻ��n,˵��ԭͼ����ͨ,��������ȫͼ���Բ������������
    //���ֻҪ�������С����,���ڲ���ͨ�����,prim��Ҫ��ÿ����ͨ��������һ��,��vis���ж�
    return -1;
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)&&n){
        cnt=0;
        memset(head,-1,sizeof(head));
        m=n*(n-1)/2;
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
