#include<cstdio>
#include<cstring>
#include<queue>
#define N 5100
#define INF 0x3f3f3f3f
using namespace std;
//������ֵ�Ͻ�
/*
����:https://www.luogu.com.cn/problem/P5960
����:https://www.luogu.com.cn/problem/P5960
˼·:���Լ��ϵͳģ��
*/

/*
Dijkstra�޷������и�Ȩ�ߵ����,Bellman-Ford����
���ڲ���ʽ x1-x0<=2 ת��Ϊx1<=x0+2 ������x0->x1֮����һ������Ϊ2������� �����Ǹ������·���ɳں�����ȹ�����
�������ǲ���ʽ(1)B-A<=c,(2)C-B<=a,(3)C-A<=b �ֽ����߽����������ͼ ����ת������ A->B(w=c) B->c(w=a) A->C(w=b)
(1)+(2)�ɵ�C-A<=c+a ��ʵ��������ת��Ϊ�����
C-A<=c+a,C-A<=b����������ʽ�Ľ� ���ݲ���ʽͬСȡС��ԭ��C-A<=min(c+a,b) ���ڵ�����պñ�������
���ͼ�д�Դ��A���յ�C�����·����,���Ƕ���ԭ����ʽ��������������ȡ��������С���Ͻ磬����Ծ�����ȡ���ֵ��
ʵ�������������Ҳ������ȫ�����ɷ���� ��(1)A-B>=-c (2)C-B>=-a (3)A-C>=-b (2)+(3)�ɵ�:A-B>=-a-b,����������
���ݲ���ʽͬ��ȡ���ԭ��ת���max(-c,-a-b),ͼ���е�����ת����� ����Դ��B���յ�A���·����
���Լ���������Թ滮����,�о��е��������ѧ������Թ滮��ȡĿ�꺯�����ٽ�ֵ���⡣
���ڴ��������������Ҫ�����xi�ķ���������һ��ֵ,�����ǿ��Լ���һ������Դ��,������ת��Ϊ��ȡ�ӳ���Դ�㵽����������·����
��֮:���Լ���������ת��Ϊ���·���·���⣬��������ת��Ҳ���γ������ֲ�ͬ�����߷���,���ַ�������Ľ��ǲ�ͬ��,һ��x<=0 ��һ��x>=0
1.���ߺ������·
��xj-xi<=k����Ϊxj<=xi+k,����i��j��һ����ȨΪk�ı�,���볬��Դ��������·,�õ�xi<=0,���x�����ֵ
2.���ߺ����·
��xj-xi<=k����Ϊxi>=xj+(-k),����j��i��һ����ȨΪ-k�ı�,���볬��Դ������·,�õ�xi>=0,���x����Сֵ
ע��:1.����ԭͼ�д��ڸ���,��Ϊ���������·,���һֱ���Ÿ�����,���·�ͻ�Խ��ԽС�������-OO
���ڲ���ʽ������,������ʽ�� Ϊ��ȡx<=0 x>=5����û�н��������,������ʽ�޽⡣
2.����ԭͼ����ͨ,�����Ϊ���ֵ���޴�,�����������������
3.����xi-xj=c��ת����xi-xj<=c xi-xj>=c ��Ҫ��������
*/

struct node{
    int to,w,next;
}edge[N<<1];
//vis�ж��Ƿ���� num��¼��Ӵ��� dis[i]��ʾ����Դ�㵽i�����·
int cnt,vis[N],num[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[0]=0;//����Դ�㵽�������Ϊ0
    for(int i=1;i<=n;i++)
        dis[i]=INF;//��Ϊ�����· ���Գ���Դ���ʼ��������������ֵҪ����������,��һ���ɳڱ�ʱ��õ�����
}
//Shortest Path Faster Algorithm (SPFA)(���Ͻ��� �η��� ����BF�������) ��: Bellman-Ford�Ķ����Ż�,ʱ�临�Ӷ�� O(VE) ��ÿһ�γ���ÿ���㶼����������е�ı߽����ɳ�
bool SPFA(int u){
    init();
    queue<int> Q;
    int v;
    Q.push(u);//����Դ�㲢û�б��ɳ�,����Դ�㲻�ᱻ�ɳ�,������û�б����򳬼�Դ��
    vis[u]=1;
    while(!Q.empty()){//O(V)
        u=Q.front();
        vis[u]=0;//���� ���Ϊ0
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){//O(E)
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){//s->v���ɳ�Ϊs->u->v ����
                dis[v]=dis[u]+edge[i].w;
                num[v]++;//v����Ӵ�����1
                /*
                �ж��Ƿ���ڸ���,(�������ϳ���Դ����n+1����)������ÿ�������ֻ�ɱ����Լ���n���㹹�ɵ�·���ɳ�,
                ����n+1��·����ʼ��������ɳ�ʱ���·��һ�������˸���,��Ϊ��һ����֮ǰ��n��·���е�����һ���ظ���,
                �����ٶ��ɳھ�����Ϊ����Ȩֵ��Ϊ�����ŵ������ɳ�ֵԽ��ԽС
                */
                if(num[v] >= n+1) return false;//�����п��ܵڶ��η��ʾ��Ѿ��Ǹ�����,������Ϊ�ظ�����n�βŻ�ﵽ�ж�����,Ҳ�п��ܵڶ����������Ϊ��Ľ�㹹�ɵ�·���ɳڲ������ɸ���
                if(!vis[v]){//����Ѿ���Ӿ������ظ����,ֻ���ɳڹ��ĵ�û���ٶ����У���������´γ��Ӻ������ɳ�������������·
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return true;
}
int main(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(v,u,w);
    }
    for(int i=1;i<=n;i++)//���볬��Դ�� ����˳��������Է���ԭͼ������֮ǰ����
        addEdge(0,i,0);
    if(SPFA(0)){
        for(int i=1;i<=n;i++)
            printf("%d ",dis[i]);//�����Ľ�Ϊ 0 -2 0 �������밸�������� 5 3 5��ʵ�������ǵȼ۵�,���ڲ���ʽ�ڲ���ʽ���˼���ͬ����ֵ����ʽ�Գ���,�����5 0,-2,0��ת�����5,3,5
    }
    else//���ڸ����޽�
        printf("NO");
    return 0;
}

/*
//��Сֵ �·���� ��������Ȩ�� ����·����,������Ȩ���޷�����·,��Ȩ�߿���s
#include<cstdio>
#include<cstring>
#include<queue>
#define N 5100
#define INF -0x3f3f3f3f
using namespace std;

struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],num[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[0]=0;
    for(int i=1;i<=n;i++)
        dis[i]=INF;//�����ʼ��Ϊ����С,��ΪҪ���·,����Դ���ɳں�Ϳɸ���
}

bool SPFA(int u){
    init();
    queue<int> Q;
    int v;
    Q.push(u);
    vis[u]=1;
    num[u]++;
    while(!Q.empty()){
        u=Q.front();
        vis[u]=0;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]<dis[u]+edge[i].w){//�ɳ��ж� �·
                dis[v]=dis[u]+edge[i].w;
                num[v]++;
                if(num[v] >= n+1) return false;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return true;
}
int main(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,-w);
    }
    for(int i=1;i<=n;i++)
        addEdge(0,i,0);
    if(SPFA(0)){
        for(int i=1;i<=n;i++)
            printf("%d ",dis[i]);// 0 0 2 �����·�Ľⲻͬ����>=0
    }
    else
        printf("NO");
    return 0;
}
*/
