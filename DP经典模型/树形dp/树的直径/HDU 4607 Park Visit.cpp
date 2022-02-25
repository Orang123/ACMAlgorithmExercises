#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;

/*
题意:一棵n个节点的树,现在要访问k个节点,可以从任意节点开始访问,
求所要走的最短路径长度.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4607
思路:可以求出树的直径所包含的节点个数ans,如果k<=ans,则要走k-1长度.
如果k>ans,则这里贪心选择树的直径只走一遍,则对于直径上所连接的其它路径都要
一来一回走两遍,所以最终花费为ans-1+(k-ans)*2,这里除过直径外其余节点的个数就是
所要走的路径的长度,因为其余路径是连在直径上的,所以刚好其余节点数就是其余路径长度.
*/

int cnt,n,m,k,head[N],dis[N],ans,st;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    if(dis[u]>ans){
        st=u;
        ans=dis[u];
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=dis[u]+1;
        dfs(v,u);
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dis[1]=0;
        dfs(1,-1);
        dis[st]=0;
        dfs(st,-1);
        while(m--){
            scanf("%d",&k);
            if(k<=ans+1)//要访问节点数小于直径节点数 直接输出k-1长度
                printf("%d\n",k-1);
            else
                printf("%d\n",ans+(k-ans-1)*2);//直径长度+其余点构成路径长度*2
        }
    }
    return 0;
}
