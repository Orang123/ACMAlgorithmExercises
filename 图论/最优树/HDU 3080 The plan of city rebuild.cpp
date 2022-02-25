#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300
#define M 20100
using namespace std;
//kruskal 170ms
/*
题意:现有n1个村庄m1条道路需要重建,还要新添加
n2个村庄,m2条道路,还有q个旧村庄要销毁,其相连的道路
也会被销毁,问修建使得剩余村庄互通的道路最小花费是多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3080
思路:先建边,再将销毁的点标记,加边时跳过含有这些点的边即可.
*/

int n1,m1,n2,m2,n,m,q,fa[N],vis[N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    sort(edge+1,edge+1+m);
    for(int i=0;i<n+q;i++)//因为并不清楚哪些点删掉 所以所有点都初始化
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,sum=0,num=0,flag=0;
    for(int i=1;i<=m;i++){
        if(vis[edge[i].u] || vis[edge[i].v]) continue;
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            num++;
            if(num == n-1){
                flag=1;
                break;
            }
        }
    }
    if(!flag) sum=-1;
    return sum;
}

int main(){
    int T,u,v,w,ans;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n1,&m1);
        for(int i=1;i<=m1;i++){
            scanf("%d%d%d",&u,&v,&w);
            edge[i]=Edge(u,v,w);
        }
        scanf("%d%d",&n2,&m2);
        m=m1+m2;
        for(int i=m1+1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            edge[i]=Edge(u,v,w);
        }
        scanf("%d",&q);
        n=n1+n2-q;
        for(int i=1;i<=q;i++){
            scanf("%d",&u);
            vis[u]=1;
        }
        ans=kruskal();
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("what a pity!\n");
    }
    return 0;
}
