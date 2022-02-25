#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 50100
using namespace std;
typedef long long ll;
//2011WorldFinal 同洛谷P3225[HNOI2012]矿场搭建
//ac vector stack存边 记录pcb判重 390ms
/*
相关概念:
双连通分量(Biconnected Connected component-BBC)
点双连通图:若一个无向图中的去掉任意一个节点,都不会改变此图的连通性,
即不存在割点,则称作点双连通图(Point Biconnected Graph-PBG).
或图中任意两不同点之间都有至少两条点不重复的路径.主要采用前者定义PBG.
点双连通分量:一个无向图中的每一个极大点双连通子图称作此无向图的点双连通分量(Point Biconnected Component-PBC).

注意:
1.对于PBC的求法可以在tarjan求解割点的过程中,当碰到dfn[u]<=low[v]时,就记录一个PBC,并标记u为割点,但是需要
特判的是,如果u点是根节点,如果儿子分支数小于2,那么u实际不是割点,但是它之前所记录的PBC仍然是对的.
2.虽然点双连通分量(pbc)中不存在割点,但是对于原图而言,除过根节点的特殊情形,某个点一定是原图中的割点,
即在原图中删除这个割点,会分离出很多pbc.
3.pbc在原图中的割点可能不止一个.很多个.
4.一个点可能同时位于多个pbc中,一个pbc中至少有两个点,一个点没有连通的概念.
5.割点和点双连通对于有重边的处理情况都是一样的,因为删除一个点后,这个点所连的所有边都会删除.
6.有无重边并不影响点双连通问题的判断.
7.n个点的无向图,最多有n-1个pbc.
8.点双和边双所求解出的环是有区别的.(具体看HDU 3394 图解部分)
边双通求解的极大相并连和极大相交叉的环;
点双连通时求解极大相交叉的环;
对于边双通求解的极大相并连的环,即使ebc中边数大于点数,可能所有边
也都只在一个环内,而点双通求解的极大相交叉的环,如果pbc中满足边数大于点数
那么pbc中所有边都至少在2个环内.
*/

/*
题意是摘抄来的
题意:有一座地下的稀有金属矿由n条隧道和一些连接点组成,其中每条隧道连接两个连接点.
任意两个连接点之间最多有一条隧道.为了降低矿工的危险,你的任务是在一些连接点处安装
太平井和相应的逃生装置,使得不管哪个连接点倒塌,不在此连接点的所有矿工都能到达太平井
逃生(假定除了倒塌的连接点不能通行外,其他所有隧道和连接点完好无损).为了节约成本，
你应当在尽量少的连接点安装太平井。还需要计算当太平井的数目最小时的安装方案总数.

释义:在一张无向图(可能不连通)中,将一些点涂上黑色,使得删掉图中任何一个点时,每个连通分量至少有一个黑点.
问最少能涂几个黑点,并且在涂最少的情况下有几种方案.

链接:http://acm.hdu.edu.cn/showproblem.php?pid=3844

思路:如果要涂最少的黑点,那显然就需要,删除某个点后,原图尽量保持连通不断裂,
否则每个断裂的部分都至少需要一个黑点,那么尽量不能有割点,那么问题转化为了求解
点双连通分量(pbc),现在问最少要设置多少黑点,实际就是问极端情况,显然不能在割点
设置黑点,这样一旦删除割点,那所有点的工人都不可逃生,那么删除的点需要考虑极端情况,
因为如果删除的不是割点,那么整张图只需设置一个点为黑点即可逃生,但是如果删除的点是割点,
那么原图就可能分为好几个连通块,那么每个连通就都至少要设置一个黑点,显然我们需要考虑极端情况,
删除的点在每个割点的可能情形,才能求出最少需要设置几个黑点才能保证所有工人都能逃生,再在此
基础上求解方案数.
这样只需对于pbc中的点在原图中如果是割点,且割点的数目为1,那么说明如果删除该割点,
此pbc肯定会与原图不连通,那么这个pbc中必须得有一个黑点才能逃生那么可放的方案数根据乘法原理
就是ans*=pbc.size()-1;如果该pbc中的点在原图中割点的数目大于等于2,说明删除这个pbc中
某一个割点,那该pbc还能与原图中其余pbc连通,那么该pbc就可以不放置黑点(逃生井),
因为每个点的工人可以逃到别的pbc的逃生井得以逃生.

这里对于原图本身就是PBG(点双连通图),即不存在割点的情况,那么极端考虑需要至少设置2个黑点,
因为万一删除的点刚好是黑点,那么就需要再备用一个,方案数是C[n][2]=n*(n-1)/2.这种情况需要特判.
*/

int m,dfn[N],low[N],num,cnt,head[N],rt,vis[N],pbc_cnt,block[N];
ll n;
stack<pair<int,int> > s;//pair<u,v> 记录边集两端点
vector<int> pbc[N];//记录每个点双连通分量pbc的所有点的编号

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v,son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            /*
            这里要在栈里压边是因为,如果压点,无法压入u点,
            do while弹栈时,无法正常结束,而且u点还可能要入栈多次,
            这也是压入点所存在的问题,所以要采取在dfs之前在栈中压入边,
            但是因为一个点可能首位相接位于多个pbc中,所以边的两个端点,
            在记录pbc时要判重.
            */
            s.push(make_pair(u,v));
            dfs(v,u);
            if(u == rt) son++;
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                //记录u点为割点,这里对于根节点可能本身不是割点,但是要记录其pbc,
                //在for的外层根据其儿子个数再将其标记为不是割点.
                vis[u]=1;
                pbc_cnt++;//pbc个数+1,对应编号
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    //这里u-v,u和v都需要判重,因为u v都有可能在靠近栈顶的边集中已经记录如pbc
                    //题目样例1中(u)3-2 (u)3-5都市有可能同时入栈的,然后6-3(v),这里3同时作为u出现2次,作为v也出现一次,但已经记录过
                    if(block[tmp.first]!=pbc_cnt){//u点是否已经记录如编号为pbc_cnt的pbc中
                        pbc[pbc_cnt].push_back(tmp.first);
                        block[tmp.first]=pbc_cnt;//记录u点所属的pbc的编号
                    }
                    if(block[tmp.second]!=pbc_cnt){
                        pbc[pbc_cnt].push_back(tmp.second);
                        block[tmp.second]=pbc_cnt;
                    }
                }while(tmp.first!=u);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(u == rt && son<2)//对于u为根节点其儿子数小于2,则只记录其pbc,u点本身却不是割点
        vis[u]=0;
}

int main(){
    int u,v,cas=0;
    while(scanf("%d",&m) && m){
        cas++;
        n=pbc_cnt=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(vis,0,sizeof(vis));
        memset(block,0,sizeof(block));//这里一定要初始化为0,因为block在记录pbc中点的时候要判重
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
            n=n>max(u,v)?n:max(u,v);
        }
        //n个点的无向图最多有n-1个pbc,所以初始化上界<=n-1,不能用m初始化,这样如果m的上界远大于n,会数组越界runtime error
        //因为pbc数组是按N开的
        for(int i=1;i<n;i++) pbc[i].clear();
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                rt=i;
                dfs(i,-1);
            }
        }
        if(pbc_cnt == 1){//特殊情形,原图就是点双连通的,则只需选2个点作为黑点,一个备用
            printf("Case %d: %d %lld\n",cas,2,n*(n-1)/2);//n<=50000 n*n<=25*10^8 int溢出
            continue;
        }
        ll ans1=0,ans2=1;
        for(int i=1;i<=pbc_cnt;i++){
            int cut_num=0;
            for(int &e : pbc[i]){
                if(vis[e])
                    cut_num++;//记录该pbc中割点数目
            }
            if(cut_num == 1){//割点数目为1时,该pbc中就必须设置一个黑点,方案数为pbc中点个数减一
                ans1++;
                ans2*=pbc[i].size()-1;//乘法原理
            }
        }
        printf("Case %d: %lld %lld\n",cas,ans1,ans2);
    }
    return 0;
}
/*
input
9
1 2
2 3
3 4
4 5
5 6
6 7
1 3
3 5
5 7
output
2 4

input
11
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
1 3
3 5
7 9
output
2 4

input
9
1 3
4 1
3 5
1 2
2 6
1 5
6 3
1 6
3 2
output
2 4

input
6
1 2
1 3
2 4
2 5
3 6
3 7
output
4 1
*/

/*
//ac 390ms stack点入栈求解pbc 无需存边判重
#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 50100
using namespace std;
typedef long long ll;

int m,dfn[N],low[N],num,cnt,head[N],rt,vis[N],pbc_cnt;
ll n;
stack<int> s;
vector<int> pbc[N];//记录每个点双连通分量pbc的所有点的编号

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v,son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            s.push(v);
            dfs(v,u);
            if(u == rt) son++;
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                vis[u]=1;
                pbc_cnt++;
                int tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc[pbc_cnt].push_back(tmp);
                }while(tmp!=v);
                pbc[pbc_cnt].push_back(u);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(u == rt && son<2)//对于u为根节点其儿子数小于2,则只记录其pbc,u点本身却不是割点
        vis[u]=0;
}

int main(){
    int u,v,cas=0;
    while(scanf("%d",&m) && m){
        cas++;
        n=pbc_cnt=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
            n=n>max(u,v)?n:max(u,v);
        }
        //n个点最多有n-1个pbc
        for(int i=1;i<n;i++) pbc[i].clear();
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                rt=i;
                dfs(i,-1);
            }
        }
        if(pbc_cnt == 1){//特殊情形,原图就是点双连通的,则只需选2个点作为黑点,一个备用
            printf("Case %d: %d %lld\n",cas,2,n*(n-1)/2);//n<=50000 n*n<=25*10^8 int溢出
            continue;
        }
        ll ans1=0,ans2=1;
        for(int i=1;i<=pbc_cnt;i++){
            int cut_num=0;
            for(int &e : pbc[i]){
                if(vis[e])
                    cut_num++;//记录该pbc中割点数目
            }
            if(cut_num == 1){//割点数目为1时,该pbc中就必须设置一个黑点,方案数为pbc中点个数减一
                ans1++;
                ans2*=pbc[i].size()-1;//乘法原理
            }
        }
        printf("Case %d: %lld %lld\n",cas,ans1,ans2);
    }
    return 0;
}
*/

/*
//ac set 记录pcb判重 514ms
#include<cstdio>
#include<set>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 50100
using namespace std;
typedef long long ll;

int m,dfn[N],low[N],num,cnt,head[N],rt,vis[N],pbc_cnt;
ll n;
stack<pair<int,int> > s;
set<int> pbc[N];
set<int>:: iterator it;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v,son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            if(u == rt) son++;
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                vis[u]=1;
                pbc_cnt++;
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc[pbc_cnt].insert(tmp.first);//set不会插入重复元素
                    pbc[pbc_cnt].insert(tmp.second);
                }while(tmp.first!=u);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(u == rt && son<2)
        vis[u]=0;
}

int main(){
    int u,v,cas=0;
    while(scanf("%d",&m) && m){
        cas++;
        n=pbc_cnt=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
            n=n>max(u,v)?n:max(u,v);
        }
        for(int i=1;i<n;i++) pbc[i].clear();
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                rt=i;
                dfs(i,-1);
            }
        }
        if(pbc_cnt == 1){
            //int最大2147483647,N*N<=2500000000 n如果用int会溢出
            printf("Case %d: %d %lld\n",cas,2,n*(n-1)/2);
            continue;
        }
        ll ans1=0,ans2=1;
        for(int i=1;i<=pbc_cnt;i++){
            int cut_num=0;
            for(it=pbc[i].begin();it!=pbc[i].end();it++){
                if(vis[*it])
                    cut_num++;
            }
            if(cut_num == 1){
                ans1++;
                ans2*=pbc[i].size()-1;
            }
        }
        printf("Case %d: %lld %lld\n",cas,ans1,ans2);
    }
    return 0;
}
*/

/*
//洛谷的另一种dfs搜索做法 看懂思路了,代码是洛谷网友"安好"的
//首先看到割点就是Tarjan搞 但是怎么搞
//首先假设我们把所有的点双都缩点 那么我们一定可以得到一棵树 然后我们就会发现
//1.叶子节点(只含有一个割点的点双)必须建 因为叶子节点如果不建 一旦割点被爆就死翘了
//2.非叶节点(含有两个或两个以上的割点的点双)不用建 因为即使一个割点被爆了也可以沿着另一个割点走到一个叶节点
//3.还有一种情况就是整个联通块都是点双(即不含割点的点双) 这样我们讨论点双的大小
//如果只有一个点 那么这个点必须建 数据没有卡这个的点所以我没写(其实是我忘写了 然后还过了)
//如果有两个或两个以上的点 那么要建两个 一个被爆了还可以走另一个
//方案数就是乘法原理的问题了 注意叶节点那里出口不能建在割点上
//所以先Tarjan求割点再dfs一下每个联通块就好了。

#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
int head[505],dfn[505],low[505],vis[505],stack[505];
bool cut[505],in_stack[505];
int n,m,cnt,num,tot,deg,ans1,T,cases,root,top;
ll ans2;
struct node
{
    int from;
    int to;
    int next;
}e[1010];
inline void first()
{
    memset(head,0,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(cut,0,sizeof(cut));
    memset(vis,0,sizeof(vis));
    top=cnt=tot=n=ans1=T=0; ans2=1;
}
inline void insert(int from,int to)
{
    e[++num].from=from;
    e[num].to=to;
    e[num].next=head[from];
    head[from]=num;
}
inline int read()
{
    int x=0,f=1; char c=getchar();
    while (c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while (c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
void Tarjan(int now,int father)//求割点
{
    dfn[now]=low[now]=++tot;
    for(int i=head[now];i;i=e[i].next)
        {
            int v=e[i].to;
            if(!dfn[v])
            {
                Tarjan(v,now);
                low[now]=min(low[now],low[v]);
                if(low[v]>=dfn[now])
                {
                    if(now==root) deg++;
                    else cut[now]=true;
                }
            }
            else if(v!=father) low[now]=min(low[now],dfn[v]);//不要跟求环混了 具体原理去网上找
        }
}
void dfs(int x)//遍历每个连通块
{
    vis[x]=T;//标记
    if(cut[x]) return;
    cnt++;//数量
    for(int i=head[x];i;i=e[i].next)
    {
        int v=e[i].to;
        if(cut[v]&&vis[v]!=T) num++,vis[v]=T;//统计割点数目。
        //如果是割点且标记不与遍历的的连通块相同就修改标记。
        if(!vis[v])dfs(v);
    }
}
int main()
{
    m=read();
    while (m)
    {
        first();
        for (int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            n=max(n,max(u,v));//这个地方要处理一下
            insert(u,v); insert(v,u);
        }
        for (int i=1;i<=n;i++)
        {
            if (!dfn[i]) Tarjan(root=i,0);
            if (deg>=2) cut[root]=1;//根节点的割点
            deg=0;//不要忘记是多组数据
        }
        for (int i=1;i<=n;i++)
            if (!vis[i]&&!cut[i])//不是割点
            {
                T++; cnt=num=0;//T为连通块的标记
                dfs(i);
                if (!num) ans1+=2,ans2*=cnt*(cnt-1)/2;//建两个 别忘记除以二 因为两个建立的出口没有差异
                if (num==1) ans1++,ans2*=cnt;//建一个
            }
        printf("Case %d: %d %lld\n",++cases,ans1,ans2);
        m=read();
    }
    return 0;
}
*/
