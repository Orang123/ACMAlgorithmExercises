#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 100100
#define M 200100
using namespace std;
typedef long long ll;
//kruskal 437ms 这个贪心的思维用prim不太好实现 虽然它是稠密图
/*
题意:n个点,m条边的图,求取一棵树使得最大的边权,
在所有生成树中是最小的,同时使得边权和是最大的.
链接:http://www.51nod.com/Challenge/Problem.html#problemId=1640
思路:就是求解边权和最大的瓶颈生成树,最大边权最小可以先用kruskal求出
mst最后加入的边,然后边权和最大可以反过来贪心,就是按照边集从大到小去遍历,
小于等于之前的最大边权的尽可能加边,这样求出的边权和就是最大的.好题.
*/

int n,m,fa[N];

struct Edge{
    int u,v;
    ll w;
    Edge(int u=0,int v=0,ll w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

ll kruskal(){
    init();
    sort(edge+1,edge+1+m);
    int x,y,maxw,num=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            num++;
            if(num == n-1){
                maxw=edge[i].w;
                break;
            }
        }
    }
    init();
    ll sum=0;
    num=0;
    for(int i=m;i>=1;i--){//从m开始 是因为有可能最大边权后面的边和它边权相等
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y && edge[i].w<=maxw){
            fa[y]=x;
            sum+=edge[i].w;
            num++;
            if(num == n-1) break;
        }
    }
    return sum;
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%lld",&u,&v,&w);
        edge[i]=Edge(u,v,w);
    }
    printf("%lld\n",kruskal());
    return 0;
}
