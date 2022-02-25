#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1000100
using namespace std;
//ac 0ms
/*
题意:一个n个计算机的网路中,两台服务器间的链接是双向的,
当断开其中一条链接后就能使得网络中的计算机不互通,
则这条链接就是关键链接,现在求解出网络中的关键链接的数量,
并输出链接的端口链接情况,2端点按照升序输出.
链接:https://www.luogu.com.cn/problem/UVA796
思路:tarjan求解无向连通图中的桥.
*/

int n,m,dfn[N],low[N],num,cnt,head[N],ans;

struct Edge{
    int from,to,next,flag;
    bool operator < (const Edge &x)const{
        if(from == x.from) return to<x.to;//按端点升序排序
        else return from<x.from;
    }
}edge[M];

void addEdge(int from,int to,int flag){
    edge[cnt]=(Edge){from,to,head[from],flag};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v]){
                ans++;//桥数量+1
                if(edge[i].from<edge[i].to)//记录双向边中第一个端点较小的边
                    edge[i].flag=1;
                else
                    edge[i^1].flag=1;
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        ans=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(head,-1,sizeof head);
        for(int i=0;i<n;i++){
            scanf("%d (%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v,0);
                addEdge(v,u,0);
            }
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d critical links\n",ans);
        sort(edge,edge+cnt);
        for(int i=0;i<cnt;i++){
            u=edge[i].from,v=edge[i].to;
            if(edge[i].flag)
                printf("%d - %d\n",u,v);
        }
        printf("\n");
    }
    return 0;
}
