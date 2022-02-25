#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 700
using namespace std;
//ac 0ms
/*
题意:一个n*n的网格,由'#'和'.'组成,其中'#'代表油,
'.'代表水,现在要挖油滴,但是只能按照1*2的矩形(2个'#'组成)挖,
矩形可以横着挖,也可以竖着挖,不能挖有水的'.',矩形挖完一次后
这个网格就没有'#',代表没有油,即不能交叉挖,不能重叠,问最多能
挖多少次油滴.
注:一个比较坑的地方此题n*n网格'#'的个数实际是小于n的,如果vis数组开成n*n,
那匈牙利考虑每个点的配对时,都会memset初始化vis,这样会TLE,所以vis数组大小为N,
或者vis数组设置成N*N vis可以考虑记录时间戳,这样vis每个样例只需初始化即可,不会TLE.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4185
思路:实际上就是求解最多的两个'#'的配对,每配对一次,这两个'#'就不能再
和别的'#'配对了,也就是最多的两个'#'配对的边集不能有公共顶点,显然就是
求解最大匹配,而网格中的#按照#和上下左右所连接的#恰好可以分成两个集合,
剩余的点按照正方形对角线连接就能将这个网格按照奇偶性质分成2个集合,
那么显然问题就转换为匈牙利算法求解二分图最大匹配.
这个代码并没有将二分图的两个集合分出来,而是所有'#'都建了双向边,然后所有点
都考虑配对,这样匈牙利算法计算完,结果要除2.
*/
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int n,cas,id,ans,mp[N][N],cnt,head[N],vis[N],link[N];
struct Edge{
    int to,next;
}edge[4*N];//每个#按照最多连4条边

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int judge(int x,int y){
    if(x>=1 && x<=n && y>=1 && y<=n && mp[x][y])
        return 1;
    return 0;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=id=0;
    cas++;
    memset(link,0,sizeof(link));
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&x);
                if(x == '#') mp[i][j]=++id;//为每个'#'油滴编号
                else mp[i][j]=0;//其余'.'代表水
            }
        }
        /*
                这里建边可以只考虑每个'#'的右下方2个方向,然后建双向边
                if(j<n && mp[i][j+1]){
                    addEdge(mp[i][j],mp[i][j+1]);
                    addEdge(mp[i][j+1],mp[i][j]);
                }
                if(i<n && mp[i+1][j]){
                    addEdge(mp[i][j],mp[i+1][j]);
                    addEdge(mp[i+1][j],mp[i][j]);
                }
        */
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(!mp[i][j]) continue;//坐标[i][j]必须是'#'
                for(int k=0;k<4;k++){//考虑[i][j]#四个方向的'#'连边
                    int x=i+dir[k][0];
                    int y=j+dir[k][1];
                    if(judge(x,y))
                        addEdge(mp[i][j],mp[x][y]);
                }
            }
        }
        for(int i=1;i<=id;i++){
            memset(vis,0,sizeof(vis));//vis初始化,这里vis数组大小不能是N*N,否则会TLE
            if(dfs(i)) ans++;
        }
        //因为X Y两个集合中的点都考虑配对了,所以结果要除2,这里ans一定是偶数,因为本身就是从2个集合出发分别求解的,值都是一样所以就是2倍
        printf("Case %d: %d\n",cas,ans/2);
    }
    return 0;
}

/*
//匈牙利vis数组时间戳优化避免 考虑每个点配对时都初始化vis数组
//每个点配对都设置一个新的clock时间戳,根据vis[v] == clock来确定v点是否已经访问过
//ac 46ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 700
using namespace std;

int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int n,cas,id,ans,mp[N][N],cnt,head[N*N],vis[N*N],link[N*N];
struct Edge{
    int to,next;
}edge[4*N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int judge(int x,int y){
    if(x>=1 && x<=n && y>=1 && y<=n && mp[x][y])
        return 1;
    return 0;
}

int dfs(int u,int clock){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v] == clock) continue;//代表当前点 已经被访问
        vis[v]=clock;//标记访问过点的时间戳为clock
        if(!link[v] || dfs(link[v],clock)){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=id=0;
    cas++;
    memset(link,0,sizeof(link));
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}

int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&x);
                if(x == '#') mp[i][j]=++id;
                else mp[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(!mp[i][j]) continue;
                for(int k=0;k<4;k++){
                    int x=i+dir[k][0];
                    int y=j+dir[k][1];
                    if(judge(x,y))
                        addEdge(mp[i][j],mp[x][y]);
                }
            }
        }
        for(int i=1;i<=id;i++)
            //每个考虑配对的点时间戳都不一样 clock=i 时间戳这个点的编号
            if(dfs(i,i)) ans++;
        printf("Case %d: %d\n",cas,ans/2);
    }
    return 0;
}
*/

/*
//根据正方形网格的坐标之和的奇偶性质划分二分图的2个集合,只建立一个集合的单向边求解最大匹配,结果不除2
//ac 0ms
//1.
//正方形网格中虚线连接(草稿图例对角线)的点恰好构成二分图的一个集合,
//剩余点构成另一个集合,划分的依据是二分图的两个集合内部的点之间是没有
//连边的,而正方形网格中对角线之间的点恰好没有连边,所以按照对角线连接其余点
//恰好能构造出二分图的一个集合.
//2.
//实际正方形网格中'#'点的二分图集合划分刚好满足坐标之和的奇偶性划分
//①设点(x,y) (x+y)%2==1 坐标和奇数 那么四个方向(x+/-1,y+/-1),而原坐标(x,y)
//一定是1奇1偶,而4个方向相连的'#'坐标要么同时加1要么同时减1,要么一个加1一个减1,
//但最终坐标仍旧是一个奇数一个偶数,坐标之和仍旧是奇数,所以沿着非连接边的对角线
//就能找到所有坐标之和为奇数的点.
//②设点(x,y) (x+y)%2==0 坐标之和偶数,原坐标2种情形:要么都偶数要么都奇数,但对角线方向
//坐标(x+/-1,y+/-1)最终 要么全是偶数要么全是奇数,坐标之和仍旧是偶数,所以延对角线能将
//所有坐标之和为偶数的'#'点找到.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 700
using namespace std;
//odd 代表坐标之和奇数的'#'个数
//even代表坐标之和偶数的'#'个数
//'#'点要少于N
int n,cas,odd,even,ans,mp[N][N],cnt,head[N],vis[N],link[N];
struct Edge{
    int to,next;
}edge[4*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=odd=even=0;
    cas++;
    memset(link,0,sizeof(link));
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&x);
                if(x == '#'){
                    //坐标之和为奇数的为一个集合,坐标之和为偶数的为另一个集合 恰好构成二分图
                    //分开记录点的编号,2个集合中点的编号可以有相同的
                    if((i+j)%2) mp[i][j]=++odd;//奇数  (i+j) & 1也行  & 优先级比 ==低
                    else mp[i][j]=++even;//偶数
                }
                else
                    mp[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //((i+j) & 1) == 0 也行  & 优先级比 ==低
                if((i+j)%2 == 0 || !mp[i][j]) continue;//这里只建立坐标之和为奇数的'#'点构成集合发出的单向边
                //这里必须考虑4个方向,因为坐标之和为奇数的'#'点所连的4个方向的点一定是坐标和为偶数的点
                //而这里只考虑了奇数点出发,所以要考虑4个方向
                if(i>1 && mp[i-1][j])
                    addEdge(mp[i][j],mp[i-1][j]);
                if(j>1 && mp[i][j-1])
                    addEdge(mp[i][j],mp[i][j-1]);
                if(j<n && mp[i][j+1])
                    addEdge(mp[i][j],mp[i][j+1]);
                if(i<n && mp[i+1][j])
                    addEdge(mp[i][j],mp[i+1][j]);
            }
        }
        for(int i=1;i<=odd;i++){//考虑坐标之和为奇数的'#'点去配对偶点
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("Case %d: %d\n",cas,ans);//因为只建了奇点集合到偶点集合的单向边,所以直接输出ans,不必除2
    }
    return 0;
}
*/
