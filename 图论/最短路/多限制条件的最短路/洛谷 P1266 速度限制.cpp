#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 150
#define M 25000
#define INF 1e18
using namespace std;
//�ֲ�ͼ���· dp״̬ת��
/*
����:n������(���0~n-1),m�������·,ÿ����·�г��Ⱥ�һ������,
����Ϊ0ʱ,��Ҫ���յ�ǰ�ٶȼ���ǰ��,�������0�㿪ʼ����D
��,�����ѵ�����ʱ��,���г�ʼ�ٶ�Ϊ70.
����:https://www.luogu.com.cn/problem/P1266
˼·:ͨ��ÿ����·��ʱ��Ϊ��·����/�������,���ǵ�����Ϊ0ʱ,
ͨ��������·��ʱ���ȡ���ڵ���õ�ĳ�ʼ�ٶ�,��ô���ڵ����v
�����ѵ�ʱ�����,���ܵ��������ʱ�����б�,��Ϊ����õ��ʱ����,
���ǳ�ʼ�ٶ�̫С,ͨ����ǰ��·�����ѵ�ʱ��ͻ�Խ��,����ʹ����v��
����ʱ��϶�,���ǳ�ʼ�ٶȽϴ�,ͨ����ǰ��·������ʱ���Խ��,������
������·�����Ⱥܴ�ʱ,�������յ���v�㱾����ʱ��϶�,��ʼ�ٶȽϴ�
����������յ�D������ʱ�����,����˵��������Ϊ0�ı�,��ͬ�ĳ�ʼ�ٶ�,
��Ӱ������ı�Ȩ,��ô����Ҫ��ԭ��ʱ�仨���������һ���ٶ�����,
���Էֲ�ͼ���·,����dis[i][j]�������ٶ�j����i���ʱ�仨��.
ʵ�ʾ��൱�ڰ����ٶȷֲ㽨����ͼ.������Ϊ�ٶ�V<=500,
ֱ�ӹ����ֲ�ͼ�Ŀռ䡢ʱ�����̫��(ʵ��Ҳ��̫�ý���),
����ֻ����״̬ת��dp�İ취.
*/

int n,m,t,cnt,head[N],vis[N][510],preu[N][510],prev[N][510];
double dis[N][510];

struct state{
    int u,v;
    double dis;
    state(int u=0,int v=0,double dis=0):u(u),v(v),dis(dis){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next,v;
    double l;
}edge[M];

void addEdge(int from,int to,int v,double l){
    edge[cnt]=(Node){to,head[from],v,l};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    //������������memset 0x3f��ֵ��ʼ�� �����
    for(int i=0;i<n;i++){
        for(int j=1;j<510;j++)
            dis[i][j]=i==s?0:INF;
    }
}

void Dijkstra(int s){
    priority_queue<state> Q;
    init(s);
    Q.push(state(s,70,0));
    int u,v,nowV,edgeV;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.u,nowV=tmp.v;//nowVΪ����ǰ���ڵ�u�ĳ�ʼ�ٶ�
        Q.pop();
        if(vis[u][nowV]) continue;
        vis[u][nowV]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //�����ǰ��·�ٶ����Ʋ�Ϊ0,ͨ���õ�·���ٶȾ�Ϊ��·����
            //�����ǰ��·�ٶ�����Ϊ0,ͨ���õ�·���ٶȾ�Ϊ��ʼ����u����ٶ�
            edgeV=edge[i].v?edge[i].v:nowV;
            if(dis[v][edgeV]>dis[u][nowV]+edge[i].l/edgeV){
                dis[v][edgeV]=dis[u][nowV]+edge[i].l/edgeV;
                preu[v][edgeV]=u;//��¼���ٶ�edfeV����v���ǰ���ڵ�.
                prev[v][edgeV]=nowV;//��¼���ٶ�edfeV����v���ǰ���ڵ�ĳ�ʼ�ٶ�
                Q.push(state(v,edgeV,dis[v][edgeV]));
            }
        }
    }
}

void print(int x,int v){
    if(!x){
        printf("0");
        return;
    }
    print(preu[x][v],prev[x][v]);
    printf(" %d",x);
}

int main(){
    int x,y,v;
    double l,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&t);
    while(m--){
        scanf("%d%d%d%lf",&x,&y,&v,&l);
        addEdge(x,y,v,l);
    }
    Dijkstra(0);
    for(int i=1;i<510;i++){//�Ƚ���������յ���С�����Լ��ٶ�
        if(ans>dis[t][i]){
            v=i;
            ans=dis[t][i];
        }
    }
    print(t,v);//���·��
    return 0;
}
