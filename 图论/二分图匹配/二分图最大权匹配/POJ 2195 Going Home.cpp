#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
//ac 0ms KM算法 slack数组松弛优化
/*
题意:一个n*n的网格上有n个人和n间房子,其中人用'm'表示,
房子用'H'表示,每个人可以水平或垂直走一个单位距离到相邻的
点,而每走一单位距离需要支付1元,直到人进入房间,而每个房间
只能容纳一个人,现在问将这n个人都送进房间需要的最小花费.
n*n网格中最多有n个人,n间房.
链接:http://poj.org/problem?id=2195
思路:n个人和n间房子恰好构成左右两个集合,因为每个人只住一间房,且
一间房只能容纳一个人,每对人和房子间没有公共点,这恰好构构成一个匹配.
一个人走进房子需要的花费就是人和房子的横纵距离和,也就是边权,现在要求解,
n条匹配最小边权和,可以将边权设置为负值,用KM算法求解最大匹配,求出的结果绝对值
是最小的,之后输出时再取负即可.注意顶标的初始化取值,lx要初始化为-INF.
*/
int n,m,num,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d,slack[N];
vector<pair<int,int> > node1,node2;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=num;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

int KM(){
    for(int i=1;i<=num;i++){
        lx[i]=-INF;//因为边权为负,贪心选择绝对值最小的边权,那么初始化为负值 最小的-INF
        ly[i]=0;
        for(int j=1;j<=num;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=num;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=num;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            for(int j=1;j<=num;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
                else slack[j]-=d;//实际没有slack[j]-=d这个操作也能0ms ac
            }
        }
    }
    int ans=0;
    for(int i=1;i<=num;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
    node1.clear();
    node2.clear();
}

int main(){
    char x;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == 'm')
                    node1.push_back(make_pair(i,j));//记录人的坐标
                else if(x == 'H')
                    node2.push_back(make_pair(i,j));//记录房子的坐标
            }
        }
        num=node1.size();
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++)//注意这里node的编号是从0开始,但建在mp里编号从1开始
                //人i走到房子j的花费为人与房子的横纵距离和 权值取负
                mp[i+1][j+1]=-1*(abs(node1[i].first-node2[j].first)+abs(node1[i].second-node2[j].second));
        }
        printf("%d\n",-1*KM());//输出时再取负 变为正值
    }
    return 0;
}

/*
//ac 0ms 最小差值d放在dfs匈牙利里计算求出
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,num,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d;
vector<pair<int,int> > node1,node2;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=num;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
        else
            d=min(d,tp);
    }
    return 0;
}

int KM(){
    for(int i=1;i<=num;i++){
        lx[i]=-INF;
	ly[i]=0;
        for(int j=1;j<=num;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=num;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=num;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=num;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
    node1.clear();
    node2.clear();
}

int main(){
    char x;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == 'm')
                    node1.push_back(make_pair(i,j));
                else if(x == 'H')
                    node2.push_back(make_pair(i,j));
            }
        }
        num=node1.size();
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++)
                mp[i+1][j+1]=-1*(abs(node1[i].first-node2[j].first)+abs(node1[i].second-node2[j].second));
        }
        printf("%d\n",-1*KM());
    }
    return 0;
}
*/

/*
//ac 0ms 最小差值d放在KM while(1)循环内,两层for循环求解
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,num,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d;
vector<pair<int,int> > node1,node2;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=num;v++){
        if(visy[v]) continue;
        if(lx[u]+ly[v] == mp[u][v]){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int KM(){
    for(int i=1;i<=num;i++){
        lx[i]=-INF;
	ly[i]=0;
        for(int j=1;j<=num;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=num;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=num;j++){
                if(!visx[j]) continue;
                for(int k=1;k<=num;k++)
                    if(!visy[k])
                        d=min(d,lx[j]+ly[k]-mp[j][k]);
            }
            for(int j=1;j<=num;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=num;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
    node1.clear();
    node2.clear();
}

int main(){
    char x;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == 'm')
                    node1.push_back(make_pair(i,j));
                else if(x == 'H')
                    node2.push_back(make_pair(i,j));
            }
        }
        num=node1.size();
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++)
                mp[i+1][j+1]=-1*(abs(node1[i].first-node2[j].first)+abs(node1[i].second-node2[j].second));
        }
        printf("%d\n",-1*KM());
    }
    return 0;
}
*/

/*
//ac 94ms EK算法 费用流 源点->男人->房子->汇点
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 10100
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,m,dis[N],incf[N],pre[N],vis[N],num1,num2;
char mp[110][110];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;
                incf[v]=min(incf[u],edge[i].cf);
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

int mcmf(){
    int sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed]*dis[ed];
    }
    return sum;
}

void init(){
    num1=num2=cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'm') node1[++num1]=Node(i,j);
                else if(mp[i][j] == 'H') node2[++num2]=Node(i,j);
            }
        }
        st=0,ed=num1+num2+1;
        for(int i=1;i<=num1;i++){
            addEdge(st,i,1,0);
            addEdge(i+num1,ed,1,0);
            for(int j=1;j<=num2;j++){
                int w=abs(node1[i].x-node2[j].x)+abs(node1[i].y-node2[j].y);
                addEdge(i,j+num1,1,w);
            }
        }
        printf("%d\n",mcmf());
    }
    return 0;
}
*/
