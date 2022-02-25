#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#define N 110
#define M 110
using namespace std;
//kruskal 0ms
/*
题意:n个村庄,存在不超过75条道路,现在要每月去维护一些道路,使得
n个村庄相互连通,问维护道路的最少花费是多少.
输入第一个字母代表村庄编号,第一个数字是有多少村庄和其相连,后续分别为
连接的村庄编号和边权.
链接:http://poj.org/problem?id=1251
思路:mst.
*/
int n,m,fa[N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    int x,w;
    char u,v;
    while(scanf("%d",&n) && n){
        m=0;
        for(int i=1;i<n;i++){
            cin >> u >> x;//scanf getchar 会runtime error 不知为何
            while(x--){
                cin >> v >> w;
                edge[++m]=Edge(u-'A'+1,v-'A'+1,w);
            }
        }
        printf("%d\n",kruskal());
    }
    return 0;
}
