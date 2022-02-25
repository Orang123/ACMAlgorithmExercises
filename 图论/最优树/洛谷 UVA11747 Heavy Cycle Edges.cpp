#include<cstdio>
#include<algorithm>
#define N 1100
#define M 30000
using namespace std;

/*
题意:给一个图G,按照升序序列输出图中所有环路中边权最大的边权.
链接:https://www.luogu.com.cn/problem/UVA11747
思路:要想输出环路中最大边权,可以考虑kruskal加边的过程,当所加边
构成环的时候,所加的这条边就一定是这个环中最大边权,因为kruskal是
贪心从小到大加边.
*/

int n,m,fa[N];

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=0;i<n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,flag=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y)
            fa[y]=x;
        else{
            if(!flag) printf("%d",edge[i].w);
            else  printf(" %d",edge[i].w);
            flag=1;
        }
    }
    if(!flag) printf("forest");
    printf("\n");
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        kruskal();
    }
    return 0;
}
