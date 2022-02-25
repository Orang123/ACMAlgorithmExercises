#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;
//ac 63ms dinic
/*
ժ������
����:n����,������np�������ṩ�����ĵ�,nc���������ѵ����ĵ�,ʣ�µĵ�(n-np-nc)
����תս�����ṩ����Ҳ�����ѵ���,�����֮��������·���ڵ�,��m����·,
ÿ����·����������޶�.ǰ4�����ݾ�����n����,np�������,nc�����ѵ�,m����·,
������Ŀ�ȸ�������m����·������,(���,�յ�)���������,Ȼ����np������������
(�����)��๩����,���ž���nc�����ѵ������(���ѵ�)������ѵ���.��ĿҪ����
���������ͼ��������ѵ��ܵ���(�����������).
����:http://poj.org/problem?id=1459
˼·:���������,dinic�㷨���.
*/
int n,np,nc,m,st,ed,cnt,head[N],dis[N];
struct Edge{
    int to,next,cf;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s,int ed){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int ed,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,ed,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(int st,int ed){
    int ans=0;
    while(bfs(st,ed))
        ans+=dfs(st,ed,INF);
    return ans;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,cf;
    while(scanf("%d%d%d%d",&n,&np,&nc,&m)!=EOF){
        init();
        while(m--){//m����·,������������cf
            scanf(" (%d,%d)%d",&u,&v,&cf);
            addEdge(u+1,v+1,cf);//������0~n-1,����Դ��0,���n+1,���Ե��Ŷ���1
        }
        while(np--){//np��������·,������Ϊicf
            scanf(" (%d)%d",&v,&cf);
            addEdge(0,v+1,cf);
        }
        while(nc--){//nc��������·,���ѵ���cf
            scanf(" (%d)%d",&v,&cf);
            addEdge(v+1,n+1,cf);
        }
        printf("%d\n",max_flow(0,n+1));
    }
    return 0;
}
