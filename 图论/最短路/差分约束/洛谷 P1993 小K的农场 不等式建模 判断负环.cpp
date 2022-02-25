#include<cstdio>
#include<cstring>
#define N 10010  //这里若设置成100010则时间界就100ms,若是10010则时间界900ms 很玄学
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:https://www.luogu.com.cn/problem/P1993
链接:https://www.luogu.com.cn/problem/P1993
思路:差分约束建模 判负环,这里用了dfs判负环,最好用spfa判,dfs正确性得不到证明,有时会出错.s
*/

struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[0]=0;
    for(int i=1;i<=n;i++)
        dis[i]=INF;
}

bool dfs(int u){
    int v;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(dis[v]>dis[u]+edge[i].w){//松弛判定 最短路
            dis[v]=dis[u]+edge[i].w;
            /*
            如果第二次访问到该点(说明构成了环),因为是dfs深度优先是以原先的那条路径一路访问到底,
            此过程权值和正常来讲是不断累加变大的过程,若第二次访问再度变得更小，
            只能说明所构成的环权值和为负数，因此才能在第二次访问时得到松弛,说明在访问的过程中构成了负环,之后就回溯依次全部退栈
            这里相比spfa判负环显然效率高,当第二次访问到的时候就可以判定负环,而spfa需要连续访问n次才能正式判定
            */
            if(vis[v]) return false;
            if(!dfs(v)) return false;//没有负环就尝试另一条边是否构成负环
        }
    }
    vis[u]=0;
    return true;//没有负环就正常退出
}
int main(){
    int u,v,w,k;
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    init();
    while(m--){
        scanf("%d%d%d",&k,&u,&v);//这里这里构建最短路模型 求取最大值
        if(k==1){
            scanf("%d",&w);
            addEdge(u,v,-w);//u-v>=w  v<=u+(-w)
        }
        else if(k==2){
            scanf("%d",&w);
            addEdge(v,u,w);//u-v<=w u<=v+w
        }
        else{
            addEdge(u,v,0);//u=v u-v>=0 u-v<=0 构建两条边
            addEdge(v,u,0);
        }
    }
    for(int i=1;i<=n;i++)
        addEdge(0,i,0);
    if(dfs(0)) printf("Yes");
    else printf("No");
    return 0;
}
