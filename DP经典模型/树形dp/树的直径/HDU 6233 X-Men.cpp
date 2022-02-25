#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
using namespace std;

/*
题意:一棵n个节点的树,有m个点上放置战警,节点直接的距离为1公里,1小时到达,
战警能和与自己距离超过1公里的其它战警相互交流,每个战警若与其它所有战警距离都不超过1,
则他们就会静止不动,求至少需要多长时间才能使得所有战警都静止不动.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=6233
思路:就是求战警本身初始位置路径构成的最大距离,类似与树的直径,只不过这里的初始端点和结束端点本身要有战警,
因为战警是同时行动的,因此最少的时间要在最大距离基础上除以2,向下取整,列如距离为3,实际两个战警只需要同时走1小时,距离就为1,满足条件,
即3/2=1.00
*/

int cnt,n,m,head[N],vis[N],ans;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int dis){
    //战警行走到的节点若本身放置有战警,则计算初始两战警间的距离,求最大值
    if(vis[u]) ans=max(ans,dis);
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u,dis+1);//dis战警行走的距离加1
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d",&u);//记录哪些节点上放置有战警
            vis[u]=1;
        }
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        ans=-1;
        for(int i=1;i<=n;i++){
            if(vis[i])//从节点上放置有战警的点开始遍历 搜索两战警间距离的最大值
                dfs(i,-1,0);
        }
        printf("%d.00\n",ans/2);//距离向下整除2就是最少时间
    }
    return 0;
}
