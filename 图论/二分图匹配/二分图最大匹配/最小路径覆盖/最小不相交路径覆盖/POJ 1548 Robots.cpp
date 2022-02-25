#include<cstdio>
#include<cstring>
#include<vector>
#define N 25*25
using namespace std;
//ac 16ms DAG上最小路径覆盖
/*
题意:n*n的网格上,某些位置存在垃圾用'G'表示,
每个机器人只能向右或向下走,机器人可以将沿途经过
的'G'上的垃圾捡起来,现在问最少需要派出几个机器人
从(1,1)点出发到东南角结束能将所有的垃圾收集完毕.
注意:每个点的垃圾收集完毕,其它机器人就无需在访问收集.
链接:http://poj.org/problem?id=1548
思路:每个点的垃圾收集完毕,其它机器人就无需在访问收集.
最少需要几个机器人行走的路径才能将所有的G点覆盖
完全,很明显最小不相交路径覆盖.建图只需要建立所有的G构成的DAG即可,
若Gi的横纵坐标都大于等于Gj的横纵坐标则,建立i->j的有向边,构建
好DAG跑一遍匈牙利算法求出最大匹配,则最小路径覆盖=顶点数-最大匹配.
事实上和从(1,1)点出发,在网格东南角结束没关系,主要是要覆盖完所有的G,
自然每个机器人都能到达东南角结束,这个说明就是用来迷惑的.
*/
int k,vis[N],match[N],flag,ans;
vector<int> G[N];
struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    memset(match,0,sizeof(match));
    for(int i=1;i<=N;i++) G[i].clear();
    ans=k=flag=0;
}

int main(){
    int u,v;
    while(1){
        init();
        while(scanf("%d%d",&u,&v) && u+v){
            if(u == -1 && v == -1){
                flag=1;
                break;
            }
            node[++k]=Node(u,v);
        }
        if(flag) break;
        for(int i=1;i<=k;i++){
            for(int j=i+1;j<=k;j++){//每个i 遍历所有的j(j>i)
                //i的横纵坐标都大于等于j的横纵坐标,即j在i的右下方 就建一条i->j有向边
                if(node[i].x<=node[j].x && node[i].y<=node[j].y)
                    G[i].push_back(j);
                else if(node[j].x<=node[i].x && node[j].y<=node[i].y)
                    G[j].push_back(i);
            }
        }
        for(int i=1;i<=k;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",k-ans);
    }
    return 0;
}
