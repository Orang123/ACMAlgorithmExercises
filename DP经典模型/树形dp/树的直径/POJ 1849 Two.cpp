#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
//dfs������ֱ��
/*
����:һ��n���ڵ��������,ÿ���߶���Ȩֵ,�����˴�s�ڵ������
�������˷�ͷ��������������Ҫ�����е����߶�������,����һ���ߵĻ���Ϊ����Ȩ��ֵ,
�������˲�Ҫ�����ص�������,�������˱�����������ߵ���С����.
����:http://poj.org/problem?id=1849
˼·:һ���˱���һ��·����Ҷ�ӽڵ�ʱ,Ҫ��ȥ�������·����һ��Ҫ������,��ô�����߹���·����,
ֻ������ߵ�·��ֻ����һ��,����·��������2��,Ҫ����С����,ֻҪ�������·����һ��,����·��������,
�������Ѿ������ٵ�,֮����������һ���·����ֱ������Ϊ���������Ǵ�ͬһ����������߲�ͬ·����,Ҫ�뻨����С,
��ô2�������ߴ���������,�պ�ֱ��ֻ����һ��ʱ,������С����.������ʵ�������������,��һ�����߹���,�ڶ������ֻ������,
Ȼ�����ֱ���պû���ֻ����һ��,�������ճ���ֱ��·��������·��������2��,������С���Ѿ���sum*2-ֱ��Ȩ
������ʾ��:https://blog.csdn.net/Dilly__dally/article/details/82229776
*/

int cnt,n,s,head[N],dis[N],sum,st,ans;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    if(ans<dis[u]){
        ans=dis[u];
        st=u;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=dis[u]+edge[i].w;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&s);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        sum+=w;
    }
    ans=-1;
    dfs(1,-1);
    dis[st]=0;
    dfs(st,-1);
    printf("%d",sum*2-ans);
    return 0;
}

/*
bfs������ֱ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 100010
using namespace std;

int cnt,n,s,head[N],dis[N],sum,ans,vis[N];

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void bfs(){
    queue <int>Q;
    Q.push(s);
    while(!Q.empty()){
        int u=Q.front();
        vis[u]=1;
        if(dis[u]>ans){
            ans=dis[u];
            s=u;
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
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&s);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        sum+=w;
    }
    ans=-1;
    bfs();
    dis[s]=0;
    memset(vis,0,sizeof(vis));
    bfs();
    printf("%d",sum*2-ans);
    return 0;
}
*/
