#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1010
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;

/*
����:n����,m�������,���s��t�����·��Ŀ��
�����·���ȶ�1�Ĵζ�·��Ŀ֮��,����ζ�·���Ȳ�����
�����·��1,��������·��Ŀ.
����:http://poj.org/problem?id=3463
˼·:���·����+�ζ�·,��ͬ���Ƕ��ڴζ�·�ĸ���,
�п�����Դ�����·Ҳ�п�����Դ�ڴζ�·,��������ʱ
��Ҫ����һ�����·�ʹζ�·�ı�־,�����ڸ��´ζ�·����ʱ,
��֪���̳�ԭ�����·�������Ǵζ�·����.
*/
//dis[v][0]������v�����·���� num[v][0]������v�����·����
//dis[v][1]������v��ζ�·���� num[v][1]������v��ζ�·����
//vis[v][0]������v�����·�Ƿ��Ѽ���
//vis[v][1]������v��ζ�·�Ƿ��Ѽ���

int n,m,cnt,st,ed,head[N],vis[N][2],dis[N][2],num[N][2];

struct state{
    int v,dis,flag;//flag��������·���Ǵζ�·
    state(int dis=0,int v=0,int flag=0):dis(dis),v(v),flag(flag){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(num,0,sizeof(num));
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s][0]=0;
    num[s][0]=1;//�ζ�·�������ó�ʼ��,�տ�ʼ�ζ�·����һ�����ɽϳ������·���µ�
}

int Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(0,s,0));
    int u,v,flag;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,flag=tmp.flag;
        Q.pop();
        if(u == ed && flag) break;
        if(vis[u][flag]) continue;//�������u���flag·�����,��ǰ�ľͲ������ŵ�,���ؼ���
        vis[u][flag]=1;//����v����/�ζ�·�ѱ����� ���ϱ��
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //�������·
            if(dis[v][0]>tmp.dis+edge[i].w){
                //��ԭ�����·�ѱ�����,��֮ǰ�����·��Ϊ�µĴζ�·,������Ϊ�˱���ζ�·����������
                if(dis[v][0]!=INF){
                    dis[v][1]=dis[v][0];
                    num[v][1]=num[v][0];
                    Q.push(state(dis[v][1],v,1));
                }
                dis[v][0]=tmp.dis+edge[i].w;
                num[v][0]=num[u][0];
                Q.push(state(dis[v][0],v,0));
            }
            else if(dis[v][0]==tmp.dis+edge[i].w)
                num[v][0]+=num[u][0];//�ۼ����·����
            else if(dis[v][1]>tmp.dis+edge[i].w){//���´ζ�· tmp.dis+edge[i].w�п��������·Ҳ�п��ܴζ�·
                dis[v][1]=tmp.dis+edge[i].w;
                num[v][1]=num[u][flag];//�ζ�·���������ɾ���֮ǰ������õı�־����,0�����·,1�Ǵζ�·
                Q.push(state(dis[v][1],v,1));
            }
            else if(dis[v][1]==tmp.dis+edge[i].w)
                num[v][1]+=num[u][flag];//�ۼӴζ�·���� �п������·Ҳ�п��ܴζ�· ��flag����
        }
    }
    if(dis[ed][0]+1 == dis[ed][1])
        return num[ed][0]+num[ed][1];
    else
        return num[ed][0];
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);//����ͼʾ��֪�ǵ����
        }
        scanf("%d%d",&st,&ed);
        printf("%d\n",Dijkstra(st));
    }
    return 0;
}
