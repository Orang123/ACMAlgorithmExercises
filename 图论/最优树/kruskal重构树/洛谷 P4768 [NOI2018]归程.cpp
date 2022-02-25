#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 200100
#define M 400100
#define INF 0x3f3f3f3f
using namespace std;

/*
�����ֻ��78�� ��֪�������ˡ�����
������������:
���԰�����ѯ��ȫ������,Ȼ����һЩ���ݽṹ���,
�Ѷ�Ӧλ�õ�����ش���,���ֽ�����.

������������:
�����������ش���,�㶼�ò�����ȷ����һ����������,
һ����õķ�ʽ�ǽ���һ�ִ𰸺ͱ�������ȡģ�������֮��ĵ���������������������.
*/

/*
����:YazidҪ�ؼ�,��Ҫ�ص�1�Ž��,ÿ����·���ܻ��л�ˮ,�л�ˮʱ�Ͳ��ܿ���
ֻ�ܲ����߹���·�ĳ��ȣ�ÿ����·����һ���ĺ���,ÿ�춼��Ӧ����ˮλ��,������
������ˮλ��ʱ,�ͻ��л�ˮ.
����:https://www.luogu.com.cn/problem/P4768
˼·:���������1��㵽�����������·.
���ں��δ���ˮλ�ߵı�,�ǿ��Կ�������Ҫ������ʹ��,��ô�����ת��Ϊ��,
���к��δ���ˮλ�ߵı��е������ӵĽڵ����1�ڵ����̾���.�ؼ�����ο��ٱ���
���к��δ���ˮλ�ߵı��е������ӵĽڵ�,�����Ժ�����Ϊ��Ȩֵ����kruskal�ع���,
��Ȩ��Ϊ����,����Խ�������ڵ�ĵ�Ȩ���θ߶�ԽС,����������kruskal�ع��������lca(Q��ѯ��ʱ��QlogN)
����dpʱ,����ÿ�����ڵ�����������нڵ����1�ڵ����̾���,���¸��ڵ��dis[u],
֮��Q������ѯ��,ֱ������lca��fa���鱶��������,����ǰ�ĸ��׽ڵ��ȨС�ڵ��ڵ���ˮλ��
���ڸ���ˮλ��ʱ,�����ߵĸ��׽ڵ���Ǻ��θ���ˮλ�ߵ��ٽ�ֵ,��ô�������������еı�,
���Ǻ��θ���ˮλ�ߵ�,ֱ�ӷ���dis[u]�����ڵ㼰�䱾�����1�ڵ������С��ֵ����.

���������1��㵽�����������·,Ȼ���պ��θ߶�,�ع�һ��kruskal�����,
����ֻҪ���ձ�����ԭ��������,����ǰ���ڵ�õ���Ȩ�߶ȴ��ڵ���ˮλ��,����������������ڵ�
�ĵ�Ȩ(����)������ˮλ��,�����������е�����һ��������ͨ��������ͨ,��Ҫע�������Yazidѡ����
�����ĳ��ӻ�����ԭ��,�������ٴ�ʹ����.���ֻҪ���������ڵ㼰�������еĽ�����1������̾���Ϳ�,
��ô������뼴�� yazid���е���С����.
*/
int head1[N],head2[N<<1],fa[N<<1][21],cnt1,cnt2,val[N<<1],ver[N<<1],vis[N],dis[N<<1];

struct Node0{
    int u,v,h;
    bool operator < (const Node0 &x)const{
        return h>x.h;
    }
}edge0[M];
struct Node1{
    int to,next,w;
}edge1[M<<1];
struct Node2{
    int to,next;
}edge2[N<<2];

void addEdge1(int from,int to,int w){
    edge1[cnt1]=(Node1){to,head1[from],w};
    head1[from]=cnt1++;
    edge1[cnt1]=(Node1){from,head1[to],w};
    head1[to]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node2){to,head2[from]};
    head2[from]=cnt2++;
    edge2[cnt2]=(Node2){from,head2[to]};
    head2[to]=cnt2++;
}

void init(int n){
    cnt1=cnt2=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    memset(fa,0,sizeof(fa));
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=n;i++)
        ver[i]=i;
}

int find(int x){
    return ver[x]==x?x:(ver[x]=find(ver[x]));
}

void Dijkstra(int s){
    priority_queue<pair<int,int> > Q;
    Q.push(make_pair(dis[s],s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head1[u];i!=-1;i=edge1[i].next){
            v=edge1[i].to;
            if(dis[v]>dis[u]+edge1[i].w){
                dis[v]=dis[u]+edge1[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

void kruskal(int n,int m){
    int num=n,x,y;
    for(int i=0;i<m;i++){
        x=find(edge0[i].u);
        y=find(edge0[i].v);
        if(x!=y){
            num++;
            ver[x]=ver[y]=num;
            val[num]=edge0[i].h;
            addEdge2(x,num);//�����kruskal �о�����ֻ��������� ������Ҳ��
            addEdge2(y,num);
            if(num - n == n-1) return;
        }
    }
}

//���dfs�о�Ҳ����ʡ��,����fa����� ��������о���1������̾��� ����ת�Ƶ��ع�kruskal���ĵط����
void dfs(int u,int fath){
    fa[u][0]=fath;
    for(int i=1;i<=19;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(v!=fath){
            dfs(v,u);
            dis[u]=min(dis[u],dis[v]);//���¸������ڵ��������������нڵ��о���1�������ľ���
        }
    }
}

int lca(int u,int h){
    for(int i=19;i>=0;i--){
        if(fa[u][i] && val[fa[u][i]]>h)
            u=fa[u][i];//��������ǳ��û�л�ˮ�������ĸ��ڵ�
    }
    return dis[u];//����������������н�����1��������ľ���
}

int main(){
    int T,n,m,u,v,l,h,Q,K,S,v0,p0,p,lastans=0;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init(2*n-1);
        for(int i=0;i<m;i++){
            scanf("%d%d%d%d",&u,&v,&l,&h);
            edge0[i].u=u,edge0[i].v=v,edge0[i].h=h;
            addEdge1(u,v,l);
        }
        Dijkstra(1);
        sort(edge0,edge0+m);
        kruskal(n,m);
        dfs(2*n-1,0);
        scanf("%d%d%d",&Q,&K,&S);
        while(Q--){
            scanf("%d%d",&v0,&p0);
            v=(v0+K*lastans-1)%n+1;//v�ǳ�����
            p=(p0+K*lastans)%(S+1);//p�ǵ���ˮλ��
            lastans=lca(v,p);
            printf("%d\n",lastans);
        }
    }
    return 0;
}
