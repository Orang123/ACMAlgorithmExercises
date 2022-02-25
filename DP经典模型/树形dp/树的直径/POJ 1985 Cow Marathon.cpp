#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100010
using namespace std;

/*
����:�����νṹ��ũ��,����ũ��֮����ľ���
����:http://poj.org/problem?id=1985
˼·:�������ֱ��
��Ŀ������Ǹ�Ӣ����ĸû��ֱ���ô�,Ӧ�������ֲ�ͬ��С·����.
*/

int cnt,n,m,head[N],dis[N],ans,vis[N],st;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void bfs(){
    queue <int>Q;
    Q.push(st);
    while(!Q.empty()){
        int u=Q.front();
        vis[u]=1;
        if(ans<dis[u]){
            ans=dis[u];
            st=u;
        }
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(vis[v]) continue;
            dis[v]=dis[u]+edge[i].w;
            Q.push(v);
        }
    }
}

int main(){
    char c;
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d %d %d %c",&u,&v,&w,&c);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    st=1;
    bfs();
    dis[st]=0;
    memset(vis,0,sizeof(vis));
    bfs();
    printf("%d",ans);
    return 0;
}
