#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f
using namespace std;
//˼ά���߷�ʽ 403ms
//״̬ת�Ʒ�ʽ��Ϊֻ��2��,���Ժ���������·�ֱ�������ͼ��,Dijkʱö���л���·����
/*
����:n*n������ͼ,�����������һ���߻���2,�ɺ���ת������
��������ת����򻨷�1,��������վ��ֻ��m��,���������յ�,
�ʴ���㵽�յ����ٻ��Ѷ���ʱ��.
����:https://www.luogu.com.cn/problem/P3831
˼·:����n<=20000,n*n������ʵ�����õĵ������m���ɹ�վ�ڻ��˵ĵ�,
ֻ�蹹��m���������߼���,����ʵ�ʶ��ڵ�ǰ�ߵ�״̬��Ҫ���ֺ��������,
��������վ�ڻ��˵����л�����ʱ��Ҫ�໨1����,���Կ��Խ�2��ͼ,һ����
�����ߵı�,��һ���������ߵı�,����ÿ���㹹������֮���Ӧ�㽻����˫���.
�����n�޹�
*/
//����k=1��˫��ͼ
int n,m,cnt,head[N<<1],dis[N<<1],vis[N<<1];

struct Pos{
    //��Ϊ��������ԭ�еı��,���Ҫ��ʵ��ȷ���õĵ�ı�ż�¼����,���� ���򽨱ߵĵ���ܺͺ��򽨱ߵĵ��Ӧ����
    int x,y,id;
}pos[N];

bool cmpx(Pos a,Pos b){
    if(a.x!=b.x) return a.x<b.x;
    else return a.y<b.y;
}

bool cmpy(Pos a,Pos b){
    if(a.y!=b.y) return a.y<b.y;
    else return a.x<b.x;
}
//����N���� ����N���� 2��֮��ÿ����һ����,��N���� ����Ϊ˫���,����3N*2
struct Node{
    int to,next,w;
}edge[N*3*2];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s){
    priority_queue<pair<int,int> > Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        //���ն����յ�m+2 ���п��ܴӺ��򵽴�Ҳ�п������򵽴�,���ȳ��ӵ�һ������С����
        if(u == m+2 || u == m+2+m+2) return dis[u];
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
    return -1;//���ɴ��յ�
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);//�����n�޹�
    //m+1 m+2�����������յ�
    for(int i=1;i<=m+2;i++){
        scanf("%d%d",&pos[i].x,&pos[i].y);
        pos[i].id=i;
    }
    //���պ�����·��������
    sort(pos+1,pos+1+m+2,cmpx);
    for(int i=1;i<m+2;i++){
        if(pos[i].x == pos[i+1].x){//��ͬһ������,��������վ�㹹���
            //0��ͼ���id
            addEdge(pos[i].id,pos[i+1].id,(pos[i+1].y-pos[i].y)*2);
            addEdge(pos[i+1].id,pos[i].id,(pos[i+1].y-pos[i].y)*2);
        }
    }
    //����������·��������
    sort(pos+1,pos+1+m+2,cmpy);
    for(int i=1;i<m+2;i++){
        if(pos[i].y == pos[i+1].y){//��ͬһ������,��������վ�㹹���
            //1��ͼ���Ϊid+(m+2)
            addEdge(pos[i].id+m+2,pos[i+1].id+m+2,(pos[i+1].x-pos[i].x)*2);
            addEdge(pos[i+1].id+m+2,pos[i].id+m+2,(pos[i+1].x-pos[i].x)*2);
        }
    }
    /*
    ��һ��ֲ�ͼ��ͬ����,��������֮��ı�Ϊ˫���,��Ϊ����ͬһ����
    ���ܴӺ����л�������,Ҳ�ܴ������л�������.
    */
    for(int i=1;i<=m;i++){
        addEdge(i,i+m+2,1);
        addEdge(i+m+2,i,1);
    }
    //������� �ȿ������ߺ���Ҳ������������
    addEdge(m+1,m+1+m+2,0);
    printf("%d",Dijkstra(m+1));
    return 0;
}

/*
//�ֲ�ͼ���· dp���� 355ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f
using namespace std;
//dis[u][0]�����u��ʼ�ߺ�����·
//dis[u][1]�����u��ʼ��������·
int n,m,cnt[2],head[N][2],dis[N][2],vis[N][2];

struct state{
    int v,dis,sign;
    state(int v=0,int dis=0,int sign=0):v(v),dis(dis),sign(sign){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Pos{
    int x,y,id;
}pos[N];

bool cmpx(Pos a,Pos b){
    if(a.x!=b.x) return a.x<b.x;
    else return a.y<b.y;
}

bool cmpy(Pos a,Pos b){
    if(a.y!=b.y) return a.y<b.y;
    else return a.x<b.x;
}
//edge[cnt][0] ��ź����
//edge[cnt][1] ��������
struct Node{
    int to,next,w;
}edge[N<<1][2];

void addEdge(int from,int to,int w,int k){
    edge[cnt[k]][k]=(Node){to,head[from][k],w};
    head[from][k]=cnt[k]++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s][0]=dis[s][1]=0;
}

int Dijkstra(int s){
    priority_queue<state> Q;
    init(s);
    Q.push(state(s,0,0));//��㿪ʼ ö�ٺ�������2����·�߷�
    Q.push(state(s,0,1));
    int u,v,k;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,k=tmp.sign;
        if(u == m+2) return dis[u][k];
        Q.pop();
        if(vis[u][k]) continue;
        vis[u][k]=1;
        //k=0 ������º���վ�� k=1�����������վ��
        for(int i=head[u][k];i!=-1;i=edge[i][k].next){
            v=edge[i][k].to;
            if(dis[v][k]>dis[u][k]+edge[i][k].w){
                dis[v][k]=dis[u][k]+edge[i][k].w;//���Ǻ���/������·����
                Q.push(state(v,dis[v][k],k));
                //����һ��Ҫ�ж��Ƿ�����ɳڵ����� ���Ѹ�С,�����wa
                if(dis[v][k^1]>dis[v][k]+1){//�����෴��·k���1����,��ԭ�Ⱥ���/������·����õ�Ҫ��+1
                    dis[v][k^1]=dis[v][k]+1;
                    Q.push(state(v,dis[v][k^1],k^1));
                }
            }
        }
    }
    return -1;
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m+2;i++){
        scanf("%d%d",&pos[i].x,&pos[i].y);
        pos[i].id=i;
    }
    sort(pos+1,pos+1+m+2,cmpx);
    for(int i=1;i<m+2;i++){
        if(pos[i].x == pos[i+1].x){
            addEdge(pos[i].id,pos[i+1].id,(pos[i+1].y-pos[i].y)*2,0);
            addEdge(pos[i+1].id,pos[i].id,(pos[i+1].y-pos[i].y)*2,0);
        }
    }
    sort(pos+1,pos+1+m+2,cmpy);
    for(int i=1;i<m+2;i++){
        if(pos[i].y == pos[i+1].y){
            addEdge(pos[i].id,pos[i+1].id,(pos[i+1].x-pos[i].x)*2,1);
            addEdge(pos[i+1].id,pos[i].id,(pos[i+1].x-pos[i].x)*2,1);
        }
    }
    printf("%d",Dijkstra(m+1));
    return 0;
}
*/

