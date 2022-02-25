#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f
using namespace std;
//���ⲻ����� ��ȡģ��������Ϊʵ�ʵĵ�
/*
����:����һ������K.��һ��K��������SUM,ʹ��SUM����λ�ۼӺ���С
����:https://atcoder.jp/contests/arc084/tasks/arc084_b
˼·:
https://blog.csdn.net/ACM2017/article/details/81395233 ���Դ˲���
���ȣ�������ת��һ��˼ά��������ͼ����˵˵��������������һ��0..k-1֮�������x����x����һ���㡣
���ڴ�x�������������������������
(1)x*=10,��ʱx�ĸ�λ���ֺͲ������ı䣬�˲�������ת���ɴ�x��x*10%k��һ������ߣ�Ȩֵ0��
(2)x++,��ʱx�ĸ�λ���ֺ�Ҳ��һ���˲�������ת���ɴ�x��(x+1)%k��һ������ߣ�Ȩֵ1��
����ͼ����k���㣨0..k-1����2*k���ߡ�
Ȼ�� ���ں����Ժͺ��壬�������¡����ж�kͬ�����Ŀ���Կ���ͼ�е�ͬһ���㣬�����Ǵӵ�1������
���Ź���õ�����ͼ�ı��ߵ�0��ʱ�����൱���ߵ���һ��k�������������ĵ�ֵ����������Ϊak��
����һ·�������������бߵ�Ȩֵ֮�ͣ�Ҳ�����𲽻��1���0�õ����ܺͣ�����ak�ĸ�λ��ֵ�ܺͼ�һ��
����һ·�����Ǿ��������ӵ�����·��������������1����0����������Ȼ�������յ���ͬ���ʲ�����0��
�������㲻��1����1����ĵ㣬����������һЩ���Ǻ���ĵ�֮ǰ�Ŀ��ܵıȽ��ŵ�·�������Ӧ��1��0��һ�ˣ���
��֪������ͼ�����·�����ȼ�һ���Ǵ𰸡�
(3)k<=1e5,����k������2k����dijkstra���ɡ�
*/

int n,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[N*10];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        for(int j=0;j<=9;j++)
            addEdge(i,(i*10+j)%n,j);
    }
    Dijkstra(1);
    printf("%d",dis[0]+1);//%nΪ0�� �պþ���n�ı��� ����λ�;������·Ȩֵ��+1,�����1�ǵ�һ��1��Ϊ���û�м��ϵ�1��λ
    return 0;
}

/*
��һ������:https://blog.csdn.net/ACM2017/article/details/81395233
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100001;
struct node{
    int v,nxt,cost;
}edge[N<<1];
int head[N],k,tot;
int q[N*8],l,r,u,v;
int dist[N];
void addEdge(int u,int v,int val) {
    edge[++tot].v=v;
    edge[tot].cost=val;
    edge[tot].nxt=head[u];
    head[u]=tot;
}
int main() {
    //freopen("out.txt","w",stdout);
    scanf("%d",&k);
    for (int i=0;i<k;++i) {
        addEdge(i,i+1==k?0:i+1,1);
        addEdge(i,i*10%k,0);
        dist[i]=N;
    }
    dist[1]=0;
    l=-1;
    r=0;
    q[0]=1;
    while (l<r) {
        u = q[++l];
        for (int i=head[u];i;i=edge[i].nxt) {
            v=edge[i].v;
            if (dist[u]+edge[i].cost<dist[v]) {
                dist[v]=dist[u]+edge[i].cost;
                q[++r]=v;
            }
        }
    }
    printf("%d\n",dist[0]+1);
    return 0;
}
*/
