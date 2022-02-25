#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//�ֲ�ͼ˼ά�������� 498ms �ǶԱ�״̬�Ĳ��,һ�ֻ���w��,һ�ֻ���0��
/*
����:n����,m��ȨֵΪw��˫���,����Ҫ��s�㵽��t��,
��k�����ͨ���ߵĻ���,����С����.
����:https://www.luogu.com.cn/problem/P4568
˼·:����ֲ�ͼ���·.
*/

/*
�ֲ�ͼ����:
����ͼ�е�ÿ�����u,���԰������k+1���ڵ�, 0<=j<=k,
�ֱ��ʾ��ʹ��j�����ͨ��Ȩ�޺󵽴�u�Žڵ��״̬��
*/

int n,m,k,s,t,cnt,head[N*11],vis[N*11],dis[N*11];
/*
0~k��ÿ�㶼��M��˫���,�����֮�����i��ԭͼ���ڵ�һ��˫���,
������2���������i+1��������ô�൱��ÿ�����2M�������,
�ܹ�(k+1)��(k<=10),���Թ���(M*2*11)<<1����.
*/
struct Node{
    int to,next,w;
}edge[(M*2*11)<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}
//O(mklog(nk))
void Dijkstra(int s){
    priority_queue<pair<int,int> >Q;
    init(s);
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
    int u,v,w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    scanf("%d%d",&s,&t);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        /*
        ��ͼ�ֳ�k+1�㼴0~k ��0�����ԭͼ�ڵ�,���Ϊu�ĵ��ڵ�i��ı��Ϊu+i*n,
        ÿһ�㶼��ͬ����n����,m����,ȨֵҲ��ͬ.�����֮�������,ֻ���ɽϵͲ�ָ��ϸ߲�.
        */
        for(int i=0;i<=k;i++){
            //��i�� u->v��ȨΪw��˫���
            addEdge(u+n*i,v+n*i,w);
            addEdge(v+n*i,u+n*i,w);
            if(i){//i��Ϊ��0��ʱ,������һ�㵽��һ��֮���ȨΪ0������.
                //����i-1���u������i��v���ȨΪ0,����ʹ�õ�i����ѻ���,��i-1��u���ֱ�ӵ���i��v��
                addEdge(u+(i-1)*n,v+i*n,0);
                //����i-1���v������i��u���ȨΪ0,����ʹ�õ�i����ѻ���,��i-1��v���ֱ�ӵ���i��u��
                addEdge(v+(i-1)*n,u+i*n,0);
            }
        }
    }
    Dijkstra(s);
    /*
    ���ȶ���m>kʱ
    ��Ϊ���ڴ�s��t����·������,����������·�����������ڵ���k,�����ڱ���С��k��·��,
    ����s��t���б߶�ʹ����ѻ���,k����ʣ��,���Ž����k����ǰ,����Ϊ0.���Ҫ�Ƚ�0~k��t��
    ����Сֵ��Ϊ��С����.
    ���ǵ�m<kʱ,��s����t������·�������϶�С�ڵ���k,��ʱs����t������·�����Ѷ�Ϊ0.
    ����ֱ�������С����,�����ؽ��ֲ�ͼ�����·.
    */
    for(int i=0;i<=k;i++)
        ans=min(ans,dis[t+n*i]);
    printf("%d",ans);
    return 0;
}

/*
//���������Ǵ�״̬ö��ת�� dp�ĽǶ�dis������չһ��ά������ʾ�ֲ�ͼ��,
//���ߺ͵�������ԭͼ���ÿռ俪�� 391ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;

//dis[i][j]������i������j����ѻ������С����,��i���ڵ�j��ͼ��
//vis[i][j]������i������j����ѻ����״̬���Ƿ��Ѽ���ȷ����
int head[N],vis[N][11],cnt,dis[N][11],n,k;

struct node{
    int to,next,w;
}edge[M<<1];

struct state{
    int v,w,nowCnt;//wΪ����v��ʹ��nowCnt���ѵ���С����
    state(){}
    state(int v,int w,int nowCnt):v(v),w(w),nowCnt(nowCnt){}
    bool operator < (const state &x)const{//�������������С����
        return w>x.w;
    }
};

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    //ע���ʼ�����������Ѵ���(0~k)�ε�״̬��Ҫ��0
    //�������Ա���s��� 1~k����Ѵ���״̬�㱻�߳�ȥ�ĵ㷴���߻����ĸ���,�ᵼ��ö�ٺܶ��������״̬��
    for(int i=0;i<=k;i++)
        dis[s][i]=0;
}
//���Ӷ���Ҫ��ÿ����ö�� ʹ�û��ǲ�ʹ����ѻ���������״̬,����չ���ܶ�״̬��
//��Щ��ӵ�״̬��������ܻ���Ҫk��ͼ���еĽ�������
void Dijkstra(int s){
    priority_queue<state> Q;
    init(s);
    Q.push(state(s,0,0));
    int u,v,nowCnt;
    while(!Q.empty()){
        state tmp=Q.top();//������ǰ������С�ĵ� ȥ�ɳ��������Ļ���
        u=tmp.v,nowCnt=tmp.nowCnt;
        Q.pop();
        //����״̬��֮ǰ�Ѿ�������,����ȷ����,֮ǰ�Ǹ��϶�������С,��Ϊ���б߶�����Ȩ��,
        if(vis[u][nowCnt]) continue;
        vis[u][nowCnt]=1;
        //����v��ö��2��״̬��,һ��ʹ����ѻ���,һ�ֲ�ʹ��,ÿ�ε���ֻȡ������С�ĵ� ȥ�ɳ�������
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //�����п���ǰ�漸�ζ�ʹ����ѻ���պ��滻�����ýϴ�ı�,������״̬���ǽ��ŵ�,��֮����
            //��ǰʹ����ѻ����������k�� �����Գ���ʹ��һ����ѻ���
            if(nowCnt<k && dis[v][nowCnt+1]>dis[u][nowCnt]){
                dis[v][nowCnt+1]=dis[u][nowCnt];//����Ϊ֮ǰ�ĵ���u��Ļ���
                Q.push(state(v,dis[v][nowCnt+1],nowCnt+1));//���
            }
            //����ʹ����ѻ������ж��Ƿ񵽴�ʹ����Ѵ�������,ֻ�жϵ�ǰ��Ѵ����·����Ƿ��ܸ���
            //������ʵ�ʻ����߹��ı߻��Ѹպ��ǽ�С��,�Ѻ����ĺ��໨�ѽϴ�ı�����ѻ������,������״̬�ǽ��ŵ�,��֮����
            if(dis[v][nowCnt]>dis[u][nowCnt]+edge[i].w){
                dis[v][nowCnt]=dis[u][nowCnt]+edge[i].w;//���·���
                Q.push(state(v,dis[v][nowCnt],nowCnt));//���
            }
        }
    }
}

int main(){
    int m,s,t,a,b,c,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    scanf("%d%d",&s,&t);
    while(m--){
        scanf("%d%d%d",&a,&b,&c);
        addEdge(a,b,c);//������Ȩ����ͼ
        addEdge(b,a,c);
    }
    Dijkstra(s);
    //ͳ�Ƶ���t�յ� �ڸ���i(0~k)��������С�Ļ���
    //��Ϊ����������·���ı���������k
    for(int i=0;i<=k;i++)
        ans=min(ans,dis[t][i]);
    printf("%d",ans);
    return 0;
}
*/
