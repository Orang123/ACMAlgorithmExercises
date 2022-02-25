#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 550
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;
//�ֲ�ͼ���· ˼ά��������
/*
����:������N����վ,��������·,�����ߺ���ҵ��,��ҵ�߽Ͽ�,
��ֻ�ܳ���һվ,������Ҫ��sվ����eվ,�ҵ�һ����̵�·��.
����:https://www.luogu.com.cn/problem/UVA11374
˼·:�ֲ�ͼ���·,k��Ϊ1����������,���Խ���ҵ�߿���0����1��������·,��Ȩ.
*/

int n,m,k,s,e,y,cnt,head[N<<1],dis[N<<1],vis[N<<1],pre[N<<1];
struct Node{
    int to,next,w;
}edge[(M*2*2)<<1];

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
    priority_queue<pair<int,int> > Q;
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
                pre[v]=u;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

void print(int x){
    //��һ��С��n��ŵĵ㼴0��ͼ��1��ͼ���ӵıߴ���0��ͼ�������ҵ��ת�۵�
    if(x<n && !y) y=x;
    if(x == s){
        printf("%d",s);
        return;
    }
    print(pre[x]);
    printf(" %d",(x-1)%n+1);//���ʱҪȡģ�����������n��1��ͼ�еı��
}

int main(){
    int u,v,w,cas=0;
    while(scanf("%d%d%d",&n,&s,&e)!=EOF){
        if(cas++) printf("\n");//��������֮���л���,����Ŀû˵,����
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);//o��ͼ
            addEdge(v,u,w);
            addEdge(u+n,v+n,w);//1��ͼ
            addEdge(v+n,u+n,w);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v+n,w);//����0����1����������Ϊ��ҵ��
            addEdge(v,u+n,w);
        }
        Dijkstra(s);
        int flag=0;
        y=0;
        if(dis[e+n]<dis[e])
            flag=1;
        print(e+flag*n);
        if(flag) printf("\n%d\n",y);
        else printf("\nTicket Not Used\n");
        printf("%d\n",dis[e+n*flag]);
    }
    return 0;
}


/*
//�ֲ�ͼ���· dp����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 550
#define M 2100
#define INF 0x3f3f3f3f
using namespace std;
//dis[v][0]������v��û�г�����ҵ��
//dis[v][1]������v���Ѿ���������ҵ��
int n,m,k,s,e,z,cnt,head[N],dis[N][2],vis[N][2],preu[N][2],precnt[N][2];

struct state{
    int v,dis,cnt;
    state(){}
    state(int v,int dis,int cnt):v(v),dis(dis),cnt(cnt){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next,w,sign;
}edge[M<<1];

void addEdge(int from,int to,int w,int sign){
    edge[cnt]=(Node){to,head[from],w,sign};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s][0]=dis[s][1]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(s,0,0));
    state tmp;
    int u,v,nowCnt;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,nowCnt=tmp.cnt;
        Q.pop();
        if(u == e) return;
        if(vis[u][nowCnt]) continue;
        vis[u][nowCnt]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!edge[i].sign){//���ñ��Ǿ����� �ж��Ƿ�Ȩֵ�͸�С
                if(dis[v][nowCnt]>dis[u][nowCnt]+edge[i].w){
                    dis[v][nowCnt]=dis[u][nowCnt]+edge[i].w;
                    preu[v][nowCnt]=u;//��¼����vʹ����ҵ��nowCnt�ε�ǰ���ڵ�u
                    precnt[v][nowCnt]=nowCnt;//��¼����vʹ����ҵ��nowCnt�ε�ǰ���ڵ�uʹ����ҵ�ߴ���nowCnt
                    Q.push(state(v,dis[v][nowCnt],nowCnt));
                }
            }
            else{
                if(!nowCnt){//���ñ�����ҵ���� �����ж�֮ǰ��û���߹���ҵ�� ���ж��Ƿ�Ȩֵ�͸�С
                    if(dis[v][nowCnt^1]>dis[u][nowCnt]+edge[i].w){
                        dis[v][nowCnt^1]=dis[u][nowCnt]+edge[i].w;
                        preu[v][nowCnt^1]=u;//��¼����vʹ����ҵ��1�ε�ǰ���ڵ�u
                        precnt[v][nowCnt^1]=nowCnt;//��¼����vʹ����ҵ��1�ε�ǰ���ڵ�uû��ʹ����ҵ��
                        Q.push(state(v,dis[v][nowCnt^1],nowCnt^1));
                    }
                }
            }
        }
    }
}

void print(int x,int y){
    if(!y&&!z) z=x;//��һ��û����ҵ�ߵ�ǰ������ʹ����ҵ�ߵ�ת�۵�,zֻ��¼һ��
    if(x == s){
        printf("%d",x);
        return;
    }
    print(preu[x][y],precnt[x][y]);
    printf(" %d",x);
}

int main(){
    int u,v,w,cas=0;
    while(scanf("%d%d%d",&n,&s,&e)!=EOF){
        if(cas++) printf("\n");//��������֮���л���,����Ŀû˵,����
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w,0);//0��������
            addEdge(v,u,w,0);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w,1);//1������ҵ��
            addEdge(v,u,w,1);
        }
        Dijkstra(s);
        int flag=0;
        z=0;
        if(dis[e][0]>dis[e][1])
            flag=1;//����ʹ����ҵ�����
        print(e,flag);
        if(flag) printf("\n%d\n",z);
        else printf("\nTicket Not Used\n");
        printf("%d\n",dis[e][flag]);
    }
    return 0;
}
*/

/*
ö�ٲ�����·���� ac
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 550
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;
//����spfa Dijkstra���ܹ� ������spfa,V��E��ʵ����С.

//˼·:��Ϊ��ҵ��ֻ�ܳ���һվ,���ھ����߿��Էֱ��s,e��ʼ������
//���·,ö��ÿһ����ҵ��u->v ����dis1[u]+w+dis2[v] �Ƿ��dis1[e]��
//��.


int n,m,k,s,e,cnt,head[N],dis1[N],dis2[N],vis[N],pre1[N],pre2[N];
struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s,int *dis){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
}

void Dijkstra(int s,int *dis,int *pre){
    init(s,dis);
    priority_queue<pair<int,int> > Q;
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
                pre[v]=u;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

void print1(int v){
    if(v == s){
        printf("%d",v);
        return;
    }
    print1(pre1[v]);
    printf(" %d",v);
}

void print2(int v){
    if(v == e){
        printf(" %d",v);
        return;
    }
    printf(" %d",v);
    print2(pre2[v]);
}

int main(){
    int u,v,w,ans,st,ed,cas=0;
    while(scanf("%d%d%d",&n,&s,&e)!=EOF){
        if(cas++) printf("\n");//��������֮���л���,����Ŀû˵,����
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(s,dis1,pre1);
        Dijkstra(e,dis2,pre2);
        ans=dis1[e];
        scanf("%d",&k);
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            //ö��ÿһ����ҵ�� ������ u->v v->u��������
            if(dis1[u]+w+dis2[v]<ans){
                st=u;
                ed=v;
                ans=dis1[u]+w+dis2[v];
            }
            if(dis1[v]+w+dis2[u]<ans){
                st=v;
                ed=u;
                ans=dis1[v]+w+dis2[u];
            }
        }
        if(ans!=dis1[e]){
            print1(st);
            print2(ed);
            printf("\n%d\n",st);//����ط���\n�������stǰ�� ���ܷ���print�� �����wa,����
        }
        else{
            print1(e);
            printf("\nTicket Not Used\n");//\n ͬ��
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
