#include<cstdio>
#include<cstring>
#define N 250
using namespace std;
//2008 Asia Harbin Regional Contest
//ac 31ms dfs交叉染色划分2个集合
/*
题意:n个学生有m条相互认识的关系,现在要将所有的学生分成两组,
使得同组内的学生相互之间不认识,如果存在这样的两组,就将相互认识的一对学生
安排到双人间,现在问最多能安排几对学生到双人间.
释义:判断m对关系构成的图是否看划分为二分图,不能输出"No",否则就求出最大匹配.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2444
思路:判断是否是二分图,可以判断原图是否存在长度为奇数的回路,若存在则不是二分图,
若不存在长度为奇数的回路,则为二分图,直接匈牙利求解最大匹配.判断回路长度的奇偶性
可以用dfs/bfs进行交叉染色,即黑白黑白...白黑 010101...10这样,如果某个点已遍历过即
找到一条回路,判断当前点与遍历过的点的染色是否相同,若相同则该回路长度一定为奇数,若
不相同则回路长度为偶数.之后匈牙利无向图求解最大匹配,结果要除2,因为并没有将点划分开,
是从所有点考虑匹配的.其实可以根据染色后的结果,染色为0作为左集合,1作为右集合,只考虑
左集合中点用匈牙利去配对,这样直接输出结果即可,总的复杂度也会降低.

why存在长度为奇数的回路就不是二分图?
如果存在长度为奇数的回路,eg:1-2-3-1,如果将1、2分别放到左、右2个集合中,
那么3和1、2都有连边,3不能放在任何一个集合中,无法划分3放到哪个集合中,
主要原因是3同时连接了左集合和右集合中的点,导致其无法划分到左右2个集合中.
如果1、3放到左右集合,那么2也同样无法放置;同样2、3放到左右集合,那么1无法放置.
但是对于长度为偶数的回路,eg:1-2-3-4-1,1、2、3、4可以分别放置在左、右、左、右集合中,
这个可行的原因是每个点连接的两个点的要么都是左集合要么都是右集合,所以它就可以划分到右集合或左集合.
因为长度为偶数的回路,尾部相接的点(实际首部)和尾部的前驱颜色刚好是相同的,而长度为奇数,前驱颜色和尾部相接点
颜色是不同的,这就导致该点无法划分如左右集合.

无向图转换为二分图需要划分的两个集合可通过交叉染色法来分,若不存在奇环,则颜色为0(黑色)的点可作为一个集合,
颜色为1(白色)的点可作为另一个集合.
*/
int n,m,cnt,head[N],vis[N],match[N],ans;
struct Edge{
    int to,next;
}edge[N*N];//最坏的边数可能达到完全图因为是无向图所以*2 N*(N-1)/2*2=N*(N-1)

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}
//vis[u]==0,代表u点颜色为黑色;vis[u]==1,代表u点颜色为白色
//vis[u]==-1,代表u点还未染色,还未遍历.
int dfs(int u,int fa,int color){
    vis[u]=color;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;//前驱节点的颜色和当前节点肯定是不同的
        if(vis[v]!=-1){//如果v节点已经被染色,即出现了回路,判断当前节点u和v的颜色是否相同
            if(vis[u] == vis[v]) return 1;//颜色相同,回路长度为奇数,无法划分成二分图.
            continue;//否则颜色不同回路长度为偶数,不继续遍历(避免死循环)
        }
        if(dfs(v,u,color^1)) return 1;
    }
    return 0;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || hungary(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(vis,-1,sizeof(vis));//初始化未染色标记-1
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i] == -1){
                if(dfs(i,-1,0)){//存在奇回路,不是二分图输出"No"
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;i++){//枚举所有点(2个集合中的所有点)去匹配的 结果要除2
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans/2);
    }
    return 0;
}

/*
//ac 15ms 根据交叉染色法将原图分为颜色为0(黑色)和1(白色)的两个集合,
//匈牙利求最大匹配只遍历其中一个集合的点,减少时间复杂度.
#include<cstdio>
#include<cstring>
#define N 250
using namespace std;

int n,m,cnt,head[N],color[N],vis[N],match[N],ans;
struct Edge{
    int to,next;
}edge[N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int fa,int col){
    color[u]=col;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(color[v]!=-1){
            if(color[u] == color[v]) return 1;
            continue;
        }
        if(dfs(v,u,col^1)) return 1;
    }
    return 0;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || hungary(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(color,-1,sizeof(color));
    memset(vis,-1,sizeof(vis));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(color[i] == -1){
                if(dfs(i,-1,0)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;i++){
            //这里只遍历颜色为0即黑色的集合中的点,结果无需除2,直接输出,也可以只遍历颜色为1(白色)集合中的点
            if(color[i]) continue;
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 31ms bfs交叉染色划分2个集合
#include<cstdio>
#include<cstring>
#include<queue>
#define N 250
using namespace std;

int n,m,cnt,head[N],vis[N],match[N],ans;
struct Edge{
    int to,next;
}edge[N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int bfs(int s,int color){
    queue<int> Q;
    vis[s]=color;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(vis[v]!=-1){
                if(vis[v] == vis[u]) return 1;
                continue;
            }
            vis[v]=vis[u]^1;
            Q.push(v);
        }
    }
    return 0;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || hungary(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(vis,-1,sizeof(vis));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i] == -1){
                if(bfs(i,1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans/2);
    }
    return 0;
}
*/

/*
//ac 31ms (len[u]-len[v]+1) & 1 判断dfs记录路径中每个点的长度,作差+1就是遇到回路的长度
//这里不会出现先遍历一个分支,再遍历到一个分支出现上一个分支回路,
//作差时导致减掉公共长度后,分支所在的长度作差的情况,因为是深度搜索如果有连边就会一路搜索下去,
//直到发现遍历过的点构成环,u点和v点(已访问的点)永远在一个分支上,len[u]-len[v]+1就是回路的长度.
#include<cstdio>
#include<cstring>
#define N 250
using namespace std;

int n,m,cnt,head[N],vis[N],match[N],ans,len[N];
struct Edge{
    int to,next;
}edge[N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int fa){
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(vis[v]){
            //v点先于u点访问,len[u]-len[v] 减掉v点前面没用的部分的长度,+1是指u和v相连构成环的那一条边
            //因为是深度搜索 会保证u、v在同一条链上
            if((len[v]-len[u]+1) & 1) return 1;
            continue;
        }
        len[v]=len[u]+1;
        if(dfs(v,u)) return 1;
    }
    return 0;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || hungary(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(len,0,sizeof(len));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                if(dfs(i,-1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans/2);
    }
    return 0;
}
*/
