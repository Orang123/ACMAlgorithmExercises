#include<cstdio>
#include<queue>
#include<cstring>
#define N 2010
#define INF 0x3f3f3f3f
using namespace std;
/*
����:n������,m���� ���s->t����̾���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1874
˼·:���·����.
*/

struct node{
    int to,w,next;
}edge[N];
int n,m,cnt,dis[N],head[N],vis[N];
/* bool operator < (const node &x)const �������ȶ���,С����
    {
     return dist>x.dist;
    }
*/
/*
Dijsktra �޷�����Ȩ ����������,��Ϊÿ�ζ�ȡ������С��Ȩֵ�͵ĵ�,����ֻ��ȡһ��,���㵯����ǰ�Ѿ������ѵĵ�,
Ҳ��������ɳڲ���,������ÿ��������2�μ�������,��˸����Ͳ����γɷ��ʵ�һ����·������,��ȻҲ���޷��������
��ȡ������ɳڵĴ���>=n���ж����ڸ���������,����˵��ʹȫ�Ǹ�Ȩ,���whileѭ��Ҳֻ�� ѭ��n�� vis[u]����1 ʣ��ĵ���ȻҲС,���㷨����ÿ����ֻ��ȡһ��,����޷��ظ������γɻ�·
*/
void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s){
    for(int i=0;i<n;i++)
        dis[i]=(i==s?0:INF);
}
//O(MlogN+M)~=O(MlogN) Dijkstra,spfa�޷���⸺Ȩͼ�����·����,��Ϊ�޷�����ص��߹���ǰ���ڵ�,������
void Dijkstra(int s){
    priority_queue<pair<int,int> > Q;//Ĭ���Ǵ����
    int u,v;
    init(s);
    Q.push(make_pair(0,s));//pair first Ϊ·��Ȩ�� second Ϊ�յ�
    //����ѭ���Ĵ�����ʵ��������Dijkstra ��ĸ���,��Ϊÿ�ζ�ֻȡ��һ����̵�·����,�ܹ�ȡn�ξ�ǡ����������ж�������·����
    while(!Q.empty()){
        /*
        //ÿ�ζ������Ѷ�·��Ȩ��С�ĵ�ȥ�ɳ������,�ܹ���n��,�����ܽ���ع滮���³����е�����·
        ÿ���ʱ�临�Ӷ�O(logN) ����һ���Ż��Ǻ����ɳڵĵ�����dis[v]��֮ǰ�Ĵ�����Ҳ����
        �ٴθ�ֵ����,��Ϊÿһ����ȡ����Ȩֵ����С�ĵ�ȥ�ɳڵ�.
        */
        u=Q.top().second;
        Q.pop();
        /*
        ��Ҫ���Ż�������������,��Ϊwhile��Ч��ѭ��ֻ��ѭ��n��,
        ʣ��ĵ��vis[u]��ʵ֮ǰ���ѵ�����,ʣ�����Щ��֮ǰ�ϴ��·��Ȩ��,
        ��û���ɳڵı�Ҫ.
        */
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){//�����ۼӵ�for�����պ�Ϊͼ�бߵ��ܸ��� M
            v=edge[i].to;
            /*
            ������Ϊ�����· ������û�и�Ȩ��,������Ȩ���� �����ж�!vis[v],
            �����������и�ȨҲ�ɼ���,�������ܲ��ᵼ��dis[v]������,
            Ҳ����������.
            */
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
            //���ﲻ����֮ǰv���Ƿ��ڶ���,��Ϊpriority_queue Q�б����dis[v]�ǲ�����µ�,
            //����ֻҪdis[v]�и��¶����²������
                Q.push(make_pair(-dis[v],v));//����Ȩֵ��ȡ����,�󶥶ѵĶѶ�Ԫ��ʵ�ʱ�����С�� O(logN)���
            }
        }
    }
}
/*
ע��Dijkstra�޷������Ȩͼ�е��·
2��ԭ��:����ͼ ǰ���ڵ�������Ӹ���,��һ�㼴ʹ������ͼ,��Ϊ̰�ĵ�ԭ��,���Ҳ����ȷ.
eg:1->2->3 1->3 ����1->2Ȩ2 2->3Ȩ3 1->3Ȩ4,��ô��1�㿪ʼ����ʱ,
��2��3����Ӻ�,��ΪȨֵ��2,4,����̰����ȡ��ǰ�������Ȩ��,
3�����,����3�㲻���ٱ��������,��ʵ��1->2->3��Ȩֵ��5��������,
��Ȼ�������.������������ԭ����Ҫ���� ���· Dijkstra�ǽ�����bfs��������Ļ����ϵ�,
�ڱ���Խ��Ȩֵ�ͽ�С�ĵ����ɳ�ʱ,��Ȩֵ��һ��������С��,�������������ȡ�·,
�ڱ���Խ��Ȩֵ�ͽϴ�ĵ����ɳ�ʱ,��Ȩֵ��ȷ��һ������������,��Dij��vis�����ӱ��,
ʹ�ú��ɳڵ�ԭ�ȱ����϶�Ľϴ�Ȩֵ�����������,���ǳ���ʱ,�޷��ٶ�ȥ�ɳ������,
��Ϊ��ǰ�����ѱ����,���º�����disֵ�������.
�������ڸ�Ȩ�ߵ��·Dijkstra������ͨ�õ�,ʵ�����Ծ���������·.

//����spfa�����޷������Ȩͼ���·����,��Ϊ���޷�����ص�ǰ���ڵ�,������,
//��Ϊ���ɳڵı���Ͳ�һ�������ŵ�,���Զ���һ�����,��ʹһ���ڵ��Ѿ��������и��ŵ��ɳھͻ��ٴ����,
//������������߹���ǰ���ڵ�ͻ��ظ���,���ǲ��ɱ��������,���Ǹ�Ȩͼ���·spfa��������.
void Dijkstra(){
    priority_queue<pair<int,int> > Q;//Ĭ���Ǵ����
    int u,v;
    memset(dis,0,sizeof(dis));
    Q.push(make_pair(0,s));
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //ֻ���ø�Ȩͼ�·
            if(dis[v]<dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(dis[v],v));
            }
        }
    }
}
*/

int main(){
    int s,t,a,b,x;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(head,-1,sizeof(head));
        memset(dis,0,sizeof(dis));
        memset(vis,0,sizeof(vis));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&a,&b,&x);
            addEdge(a,b,x);
            addEdge(b,a,x);
        }
        scanf("%d%d",&s,&t);
        Dijkstra(s);
        if(dis[t]!=INF)
            printf("%d\n",dis[t]);
        else
            printf("-1\n");
    }
    return 0;
}
