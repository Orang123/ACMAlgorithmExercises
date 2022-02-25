#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
//ac 218ms 求解pbc,在栈里压点,而不压边的做法 较高效
//重边并不会影响该题的结果
//新的定理:"pbc中如果边数大于点数的时候,则这个pbc环内每条边几乎都被2个及2个以上的环共用"
/*
题意:n个点,m条边的无向图(不一定连通,无重边),如果一条边同时被2个及两个以上的环
共用,则称这条边为"冲突边",如果一条边不在任何一个环中,则称其为"正常边",
现在要求出"正常边"和"冲突边".
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3394
思路:对于"正常边",不在任何一个环中,那就是无向图中所有的桥.
对于"冲突边",观察可发现,"对于一个环中,如果边数大于点数的时候,
则这个环内每条边几乎都被2个及2个以上的环共用".那么现在只要求出
无向图中所有可能的环即可,那么是用点双连通分量还是边双连通分量
求所有环呢,对于边双连通所求解出ebc可能是这样"1-2,2-3,1-3,3-4,4-5,3-5",
现在ebc中的边数为6,点数为5,显然边数>点数,但是现在这个ebc内没有
一条边是同时被2个及2个以上的环共用,每条边只在一个环上.注意环是
指除了起点外每个点只经历1次就能回到起点才叫环,而现在3这个点显然
作为2个环的交点,要找别的环必须经过该点,但此时除了起点3显然得经过2次,
显然不是环.所以边双通求解的极大相并连和极大相交叉的环.那么考虑点双连通,
点双连通时求解极大相交叉的环,因为环交叉,所以在找别的环时,可以和中间点交错开,
使得除了起点外,其余点恰好只经过一次.所以求解出pbc,统计pbc的边的个数,判断
是否边数大于点数,若满足则冲突边加上当前pbc内边数.
*/

int n,m,head[N],cnt;
int dfn[N],low[N],clock,block[N],vis[N],ans1,ans2;//ans1 正常边个数 ans2冲突边个数
stack<int> s;
vector<int> pbc;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//计算pbc内的所有冲突边
void cal(){
    memset(vis,0,sizeof(vis));
    for(int &v : pbc)
        vis[v]=1;//将当前pbc内的点做上标记
    int res=0;
    for(int &u : pbc){
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(vis[v])//只记录连向当前pbc内的点
                res++;
        }
    }
    res/=2;//因为是无向边,多加了一次反向边,实际边数要除2
    if(res>pbc.size())//如果满足pbc内边数大于点数
        ans2+=res;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;//父亲节点无需考虑
        if(!dfn[v]){
            /*
            //入栈最好放在这里,如果放在开头for外,会导致每个连通块的根节点都无法出栈,
            因为栈的后进先出特性,虽然结果也并不影响,但s每次都有剩余,每个样例开始前
            都需要清空一下,很麻烦,所以放在for内dfs之前每个连通块的根节点实际是没有
            入栈的,而每次入栈的是v,当前的u实际在上一层dfs时已经作为v入栈了,所以也
            不影响回溯时前面pbc的求取.
            */
            s.push(v);
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])//计算正常边
                ans1++;
            if(dfn[u]<=low[v]){//得到pbc 计算冲突边
                int tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc.push_back(tmp);
                }while(tmp!=v);
                //如果u是割点那么u点至少还要和前驱祖父节点构成另一个pbc,
                //这里不在栈压入u节点,因为可能多个pbc都要用到,do-while结束后手动在当前pbc加入u点即可
                pbc.push_back(u);
                cal();
                pbc.clear();//每次将pbc清空
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    ans1=ans2=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){//原图可能不连通
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d %d\n",ans1,ans2);//原图即使是PBG,也无需特判直接按常规处理即可.
    }
    return 0;
}

/*
//ac 202ms 边集存入栈中,记录pbc时判重,记录pbc边时直接在tarjan里操作
//但是如果只是为了求解pbc中的点,是没有必要在stack里记录边的(考虑返祖边),可以采用较简单的在栈里记录点的办法
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,head[N],cnt;
int dfn[N],low[N],clock,block[N],pbc_cnt,ans1,ans2;
stack<pair<int,int> > s;
vector<int> pbc;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;//父亲节点无需考虑
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                ans1++;
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                int num=0;
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    num++;//每条边都是当前pbc中的边
                    if(block[tmp.first]!=pbc_cnt){
                        pbc.push_back(tmp.first);
                        block[tmp.first]=pbc_cnt;
                    }
                    if(block[tmp.second]!=pbc_cnt){
                        pbc.push_back(tmp.second);
                        block[tmp.second]=pbc_cnt;
                    }
                }while(tmp.first!=u);
                if(num>pbc.size()) ans2+=num;//当pbc边数大于点数时,所有边都是冲突边
                pbc.clear();
            }
        }
        //pbc中的边 这里只记录返祖边也就是回边,即u点在v点之后访问的,所有边都记录不判断,
        //那么如果有前向边会导致下一个pbc在记录的时候将当前pbc中的点也记录进去,那么结果就会出错
        else if(dfn[u]>dfn[v]){
            s.push(make_pair(u,v));//只记录返祖边,如果不判断dfn[u]>dfn[v],到了祖先节点时与之相对应的前向边又会多余记录一次
            low[u]=min(low[u],dfn[v]);//u点时间戳较v点晚,但能回到的某一时刻的点的时间戳不一定比v点的时间戳晚
        }
    }
}

void init(){
    ans1=ans2=pbc_cnt=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
*/

/*
//ac 218ms 求解pbc vector判重
//重边并不会影响该题的结果
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,head[N],cnt;
int dfn[N],low[N],clock,block[N],vis[N],pbc_cnt,ans1,ans2;
stack<pair<int,int> > s;
vector<int> pbc;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void cal(){
    memset(vis,0,sizeof(vis));
    for(int &v : pbc)
        vis[v]=1;
    int res=0;
    for(int &u : pbc){
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(vis[v])
                res++;
        }
    }
    res/=2;
    if(res>pbc.size())
        ans2+=res;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                ans1++;
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    if(block[tmp.first]!=pbc_cnt){
                        pbc.push_back(tmp.first);
                        block[tmp.first]=pbc_cnt;
                    }
                    if(block[tmp.second]!=pbc_cnt){
                        pbc.push_back(tmp.second);
                        block[tmp.second]=pbc_cnt;
                    }
                }while(tmp.first!=u);
                cal();
                pbc.clear();
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    ans1=ans2=pbc_cnt=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
*/

/*
//ac 249ms 求解pbc set判重
//重边并不会影响该题的结果
#include<cstdio>
#include<cstring>
#include<stack>
#include<set>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,head[N],cnt;
int dfn[N],low[N],clock,vis[N],pbc_cnt,ans1,ans2;
stack<pair<int,int> > s;
set<int> pbc;
set<int>:: iterator it;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void cal(){
    memset(vis,0,sizeof(vis));
    //set 不能用 for(int &v : pbc)这种 c++11写法
    for(it=pbc.begin();it!=pbc.end();it++)
        vis[*it]=1;
    int res=0;
    for(it=pbc.begin();it!=pbc.end();it++){
        for(int i=head[*it];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(vis[v])
                res++;
        }
    }
    res/=2;
    if(res>pbc.size())
        ans2+=res;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                ans1++;
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc.insert(tmp.first);
                    pbc.insert(tmp.second);
                }while(tmp.first!=u);
                cal();
                pbc.clear();
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    ans1=ans2=pbc_cnt=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
*/
