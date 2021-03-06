/*
题意:一个人要从某一层电梯a到另一层电梯b,
每层电梯都只能上或者下特定层数num[i],问你
从a层到b层最少需要按多少次电梯按钮.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1548
思路:bfs,枚举每次可以从当前层上num[floor]层 或下num[floor]层,
每个状态操作数+1,最先出队的 操作数就是最少的.因为每次操作都是+1,
因此普通队列就可.
*/
//ac 15ms bfs
//复杂度O(n) n<=200 n表示最高层数
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
int num[210],n;
struct node{
    int floor, step;
};
int BFS(int a,int b){
    queue<node> Q;
    node v,x;
    static bool visit[210];
    memset(visit, false, sizeof(visit));
    v.floor = a, v.step = 0;
    visit[a] == true;
    Q.push(v);
    while (!Q.empty()){
        v = Q.front();
        Q.pop();
        if (v.floor == b) return v.step;
        x.floor =v.floor+num[v.floor];//上电梯
        if (!visit[x.floor] && x.floor <= n){
            x.step =v.step+ 1;
            visit[x.floor] = true;
            Q.push(x);
        }
        x.floor = v.floor - num[v.floor];//下电梯
        if (!visit[x.floor] && x.floor >= 1){
            x.step = v.step + 1;
            visit[x.floor]=true;
            Q.push(x);
        }
        //if (x.floor == b) return x.step;这里只能判断下电梯后的状态是否到达b因此是不合理的 并不是最先出队的
    }
    return -1;
}
int main(){
    int  a, b;
    while (scanf("%d", &n), n){
        scanf("%d%d", &a, &b);//起始层a 目标层b
        for (int i = 1; i <= n; i++)
            scanf("%d", num + i);//每层楼 能上或下 num[i]层
        printf("%d\n", BFS(a, b));
    }
    return 0;
}

/*
//ac 15ms 最短路 Dijkstra
//把每层当做点 构建有向图,边权为当前层能上下的特定层数
//摘自博客:https://www.cnblogs.com/Deng1185246160/p/3229293.html
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;
const int inf = 1000000;
const int maxn = 210;
int lowcost[maxn],s[maxn],edge[maxn][maxn],n;
void dijkstra(int v0)
{
    int i , j;
    memset(lowcost,0,sizeof(lowcost));
    for(i=1;i<=n;i++)
    {
        lowcost[i] = edge[v0][i];
        s[i] = 0;
    }
//    s[v0] = 1;
    for(i=1;i<=n;i++)
    {
        int min = inf,v=0;
        for(j=1;j<=n;j++)
        {
            if(!s[j] && lowcost[j] < min)
            {
                min = lowcost[j];
                v = j;
            }
        }
        if(min==inf)break;
        s[v] =1;
        for(j=1;j<=n;j++)
        {
            if(!s[j] && edge[v][j] < inf && lowcost[v] + edge[v][j] < lowcost[j])
            {
                lowcost[j] = edge[v][j] + lowcost[v];
            }
        }
    }
}
int main()
{
    int floor_from,floor_to,x[maxn],i,j;
    while(scanf("%d",&n)!=EOF && n)
    {
        scanf("%d %d",&floor_from,&floor_to);
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                if(i==j)
                    edge[i][j] = 0;
                else
                    edge[i][j] = inf;
            }
        }
        for(i=1;i<=n;i++)
        {
            scanf("%d",&x[i]);
            if(i+x[i]<=n)
            {
                edge[i][i+x[i]] =1;
            }
            if(i-x[i]>=1)
            {
                edge[i][i-x[i]] = 1;
            }
        }
        dijkstra(floor_from);
        if(lowcost[floor_to] == inf)
            printf("-1\n");
        else
            printf("%d\n",lowcost[floor_to]);
    }
    return 0;
}
*/

/*
//自己写的最短路 刚开始TLE,后来wa, 一般Dijkstra 我用stl力的优先队列优化
#include<cstdio>
#include<cstring>
#define INF 0x3FFFFFFF
int map[210][210];
bool flag[210];
int cost[210],a[210];

void Dijkstra(int n,int a){
    memset(flag,false,sizeof(flag));
    for(int i=1;i<=n;i++){
        if(i!=a)
            cost[i]=map[a][i];
    }
    flag[a]=true;
    for(int m=1;m<n;m++){
    int tmp=INF,j;
    for(int i=1;i<=n;i++){
        if(!flag[i]){
            if(cost[i]<tmp){
                tmp=cost[i];
                j=i;
            }
        }
    }
    if(tmp == INF)
        break;
        int min_num=j;
        flag[min_num]=true;
        for(int k=1;k<=n;k++){
            if(!flag[k]){
                if(cost[min_num]+map[min_num][k]<cost[k]){
                    cost[k]=cost[min_num]+map[min_num][k];
                }
            }
        }
    }
}

int main(){
    int N,A,B;
    while(scanf("%d",&N),N){
    scanf("%d%d",&A,&B);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++){
            if(i!=j)
                map[i][j]=INF;
            else
                map[i][j]=0;
        }
        for(int i=1;i<=N;i++){
        scanf("%d",a+i);
        if(i+a[i]<=N)
            map[i][i+a[i]]=1;
        if(i-a[i]>=1)
            map[i][i-a[i]]=1;
    }
    Dijkstra(N,A);
    if(cost[B]!=INF)
        printf("%d\n",cost[B]);
    else
        printf("-1\n");
    }
    return 0;
}
*/

