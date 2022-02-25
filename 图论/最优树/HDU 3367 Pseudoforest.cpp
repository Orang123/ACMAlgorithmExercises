#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
typedef long long ll;
//296ms kruskal
/*
����prim�㷨��˼������ⲻ��,��Ϊ��������Ϊһ����ͨ��ʱ,
prim�������ԶҲֻ��һ����ͨ��,��kruskal ����Ŀ����Ƕ����ͨ��,������ܲ�ͬ,
����ĿҪ��Ϊαɭ��(pseudoforest),��ȻҪ�����������л��з���,���prim������
����.
*/
/*
����:n�����ͼ(αɭ��),Ҫ����ȡ������ͨ�Ӽ������Ȩֵ��,
ÿ����ͨ�Ӽ������һ����.������ͼ������ȫͼ,Ҳ��һ����ͨ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3367
˼·:kruskal,���������������Ļ�����,����һ�������˵㲻��ͬһ��ͨ����
���,ֻҪ������ͨ�������л��Ϳ�������,�����������������2���������ⲻ��,
����һ�������˵���ͬһ��ͨ����,�����ͨ�������л�,����Ҳ�����2����.fa����
���˼�¼����,�����и������¼��ͨ�����ĸ���.
*/

int n,m;

struct Fa{
    int ptr;
    int cnt;
}fa[N];

struct Edge{
    int u,v;
    ll w;
    bool operator < (const Edge &x)const{
        return w>x.w;
    }
}edge[M];

void init(){
    sort(edge+1,edge+1+m);
    for(int i=0;i<n;i++){
        fa[i].ptr=i;
        fa[i].cnt=0;
    }
}

int find(int x){
    return fa[x].ptr==x?x:fa[x].ptr=find(fa[x].ptr);
}

ll kruskal(){
    init();
    int x,y;
    ll sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y && fa[x].cnt+fa[y].cnt<2){//����ͬһ��ͨ�� ���ĸ�����ҪС��2
            if(fa[x].cnt>fa[y].cnt)
                swap(x,y);
            fa[x].ptr=y;//xָ��y,���������е�cnt���ĸ���Ϊ1
            sum+=edge[i].w;
        }
        else if(x == y && fa[x].cnt+fa[y].cnt == 0){//��ͬһ��ͨ�� �������л�,�ӱߺ�����һ����
            fa[y].cnt=1;//��������cnt���ĸ���Ϊ1
            sum+=edge[i].w;
        }
    }
    return sum;
}

int main(){
    int u,v;
    ll w;
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d%d%lld",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("%lld\n",kruskal());
    }
    return 0;
}

/*
//wa prim����������
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N];
ll sum;

struct Edge{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void prim(int s){
    priority_queue<pair<ll,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,num=0,flag=0;
    pair<ll,int> tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.second;
        Q.pop();
        if(vis[u]){
            //���������ѱ����뼯��,���ԭ�ȼ��ϻ�û�л�,����������ϴ�ı߲���һ����
            if(!flag){
                sum+=tmp.first;
                flag=1;
            }
            continue;
        }
        vis[u]=1;
        num++;
        sum+=tmp.first;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v])
                Q.push(make_pair(edge[i].w,v));
        }
    }
}

int main(){
    int u,v;
    ll w;
    while(scanf("%d%d",&n,&m) && n+m){
        cnt=sum=0;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        for(int i=0;i<n;i++)//ԭͼ���ܲ�����ͨͼ,�ж����ͨ�Ӽ�
            if(!vis[i])
                prim(i);
        printf("%lld\n",sum);
    }
    return 0;
}
*/
