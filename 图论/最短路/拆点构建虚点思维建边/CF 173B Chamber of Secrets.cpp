#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 2100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:一个nxm的矩形网络,现有一束从第一行射入的光线,
每个网格上的'#'代表柱子,如果柱子不施加魔法,则光线的
方向不会发生改变,如果对柱子施加魔法,光线在经过柱子时,
方向会发生90度转弯,现在问最少需要对几个柱子施加魔法,
才能使得从第一行左侧射入的光线发生偏转能笔直沿着x轴右侧
射出.
链接:https://codeforces.ml/problemset/problem/173/B
思路:可以将对柱子施加魔法看作在柱子位置[i,j]方向从第i行横向
转变为第j列纵向,建一条i->j+n,j+n->i的双向边.
*/

int n,m,cnt,head[N],vis[N],dis[N];
struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
}

void bfs(int s){
    init(s);
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v]){
                dis[v]=dis[u]+1;
                vis[v]=1;
                Q.push(v);
            }
        }
    }
}

int main(){
    char x;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf(" %c",&x);
            if(x == '#'){//是柱子 就考虑这个点 方向的转变 i行转变为j列
                addEdge(i,j+n);//行的点编号为1~n 列的点编号为j+n 即n+1~n+m
                addEdge(j+n,i);//双向建边是互通的,既能从行到列,也能从列转换到行
            }
        }
    }
    bfs(1);
    if(!dis[n])
        printf("-1");
    else
        printf("%d",dis[n]);
    return 0;
}
