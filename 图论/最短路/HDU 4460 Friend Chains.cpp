#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;
//171ms 优化做法
/*
题意:n个朋友,m条关系,关系满足自反性,即有u->v就有v->u,
每条关系的链长都为1,现在要求出最长的关系链,如果存在一个
人和某个人不存在关系链,则输出-1.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4460
思路:可以从每个点u,bfs开始,求出u到其它点的最短距离,比较求出最大距离,
n次bfs时间界 O(n^2),这样大概ac786ms,其实对于一个无向图的两点之间的最远距离,
可以类比求解树的直径的思路去求解,两次bfs,一次从u点bfs求出最长距离的点v,第二次
从v点开始bfs求出最远距离dis,这个dis就是这个连通图中的最远距离,在这个过程中,用两个
标记数组,vis1,vis2,vis1标记哪些点被访问遍历,对于已访问的点不再bfs,vis2是对于每个连通图,
bfs时的标记数组,如果这两次bfs后还有vis1未被标记,则说明原图是不连通的,则输出-1.
*/

int n,m,cnt,vis1[N],vis2[N],dis[N],ans;
map<string,int> mp;
//这种类似树的直径的优化做法用链式前向星会wa,原因不明
vector<int> G[N];

void init(int s){
    memset(vis2,0,sizeof(vis2));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

int bfs(int s){
    int res=s;
    init(s);
    queue <int>Q;
    vis1[s]=vis2[s]=1;
    Q.push(s);
    /*
    这里不能直接用ans记录最远距离,这样可能第一次bfs就已经求出最远距离,
    但第二次bfs没有比ans还大的,则会返回初始点s,dis[s]=0,答案会出错.
    */
    int u,v,maxdis=0;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        if(maxdis<dis[u]){
            maxdis=dis[u];
            res=u;
            ans=max(ans,maxdis);
        }
        for(int i=0;i<G[u].size();i++){
            v=G[u][i];
            if(!vis2[v]){
                dis[v]=dis[u]+1;
                vis1[v]=vis2[v]=1;//两个vis都标记
                Q.push(v);
            }
        }
    }
    return res;
}

int work(int i){
    int u=bfs(i);//从i点开始bfs,搜索距离i点最远的点u
    //从u点开始bfs,搜索距离i点最远的点v,dis[v]就是此连通图中所有点对间的最远距离
    int v=bfs(u);
    return dis[v];
}

int main(){
    int u,v;
    string str1,str2;
    while(scanf("%d",&n)&&n){
        ans=cnt=0;
        mp.clear();
        memset(vis1,0,sizeof(vis1));
        for(int i=1;i<=n;i++){
            cin >> str1;
            mp[str1]=i;
            G[i].clear();
        }
        scanf("%d",&m);
        while(m--){
            cin >> str1 >> str2;
            u=mp[str1],v=mp[str2];
            G[u].push_back(v);
            G[v].push_back(u);
        }
        work(1);//从点1开始 两次bfs.
        for(int i=2;i<=n;i++){
            if(!vis1[i]){//若还有点没遍历 则原图不连通输出-1
                ans=-1;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//748ms n次bfs  O(n^2)
#include<cstdio>
#include<iostream>
#include<map>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],vis[N],dis[N],ans;
map<string,int> mp;
struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}


void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void bfs(int s){
    init(s);
    queue <int>Q;
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
    int u,v;
    string str1,str2;
    while(scanf("%d",&n)&&n){
        ans=cnt=0;
        mp.clear();
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++){
            cin >> str1;
            mp[str1]=i;
        }
        scanf("%d",&m);
        while(m--){
            cin >> str1 >> str2;
            u=mp[str1],v=mp[str2];
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=1;i<=n;i++){
            bfs(i);
            for(int j=1;j<=n;j++)
                ans=max(ans,dis[j]);
        }
        if(ans == INF) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
*/
