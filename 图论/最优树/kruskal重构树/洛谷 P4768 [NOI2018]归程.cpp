#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 200100
#define M 400100
#define INF 0x3f3f3f3f
using namespace std;

/*
这代码只有78分 不知道错哪了。。。
输入数据离线:
可以把所有询问全读下来,然后用一些数据结构搞搞,
把对应位置的问题回答上,这种叫离线.

输入数据在线:
不把这个结果回答完,你都得不到正确的下一组输入数据,
一般采用的方式是将上一轮答案和本轮输入取模或者异或之类的当做本轮真正的输入数据.
*/

/*
题意:Yazid要回家,想要回到1号结点,每条道路可能会有积水,有积水时就不能开车
只能步行走过道路的长度，每条道路都有一定的海拔,每天都对应的有水位线,当海拔
不超过水位线时,就会有积水.
链接:https://www.luogu.com.cn/problem/P4768
思路:可以先求出1结点到其余各点的最短路.
对于海拔大于水位线的边,是可以开车不需要花费行使的,那么问题就转化为了,
所有海拔大于水位线的边中的所连接的节点距离1节点的最短距离.关键是如何快速遍历
所有海拔大于水位线的边中的所连接的节点,可以以海拔作为边权值构造kruskal重构树,
点权就为海拔,这样越靠近根节点的点权海拔高度越小,这样可以在kruskal重构树上求解lca(Q次询问时间QlogN)
树形dp时,求解出每个父节点的子树中所有节点距离1节点的最短距离,更新父节点的dis[u],
之后Q次在线询问,直接利用lca的fa数组倍增向上跳,当当前的父亲节点点权小于等于当天水位线
不在高于水位线时,这个最高的父亲节点就是海拔高于水位线的临界值,那么它的子树中所有的边,
都是海拔高于水位线的,直接返回dis[u]子树节点及其本身距离1节点距离最小的值即可.

可以先求出1结点到其余各点的最短路,然后按照海拔高度,重构一棵kruskal最大树,
这样只要按照倍增的原则向上跳,若当前根节点得到点权高度大于当天水位线,则其子树中任意根节点
的点权(海拔)均大于水位线,这样其子树中的任意一个结点均可通过开车互通,需要注意的是若Yazid选择步行
则他的车子会留在原地,而不会再次使用了.因此只要求出这个根节点及其子树中的结点距离1结点的最短距离就可,
那么这个距离即是 yazid步行的最小花费.
*/
int head1[N],head2[N<<1],fa[N<<1][21],cnt1,cnt2,val[N<<1],ver[N<<1],vis[N],dis[N<<1];

struct Node0{
    int u,v,h;
    bool operator < (const Node0 &x)const{
        return h>x.h;
    }
}edge0[M];
struct Node1{
    int to,next,w;
}edge1[M<<1];
struct Node2{
    int to,next;
}edge2[N<<2];

void addEdge1(int from,int to,int w){
    edge1[cnt1]=(Node1){to,head1[from],w};
    head1[from]=cnt1++;
    edge1[cnt1]=(Node1){from,head1[to],w};
    head1[to]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node2){to,head2[from]};
    head2[from]=cnt2++;
    edge2[cnt2]=(Node2){from,head2[to]};
    head2[to]=cnt2++;
}

void init(int n){
    cnt1=cnt2=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    memset(fa,0,sizeof(fa));
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=n;i++)
        ver[i]=i;
}

int find(int x){
    return ver[x]==x?x:(ver[x]=find(ver[x]));
}

void Dijkstra(int s){
    priority_queue<pair<int,int> > Q;
    Q.push(make_pair(dis[s],s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head1[u];i!=-1;i=edge1[i].next){
            v=edge1[i].to;
            if(dis[v]>dis[u]+edge1[i].w){
                dis[v]=dis[u]+edge1[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

void kruskal(int n,int m){
    int num=n,x,y;
    for(int i=0;i<m;i++){
        x=find(edge0[i].u);
        y=find(edge0[i].v);
        if(x!=y){
            num++;
            ver[x]=ver[y]=num;
            val[num]=edge0[i].h;
            addEdge2(x,num);//这里的kruskal 感觉可以只构建单向边 有向树也行
            addEdge2(y,num);
            if(num - n == n-1) return;
        }
    }
}

//这个dfs感觉也可以省略,计算fa数组和 求解子树中距离1结点的最短距离 可以转移到重构kruskal树的地方求解
void dfs(int u,int fath){
    fa[u][0]=fath;
    for(int i=1;i<=19;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(v!=fath){
            dfs(v,u);
            dis[u]=min(dis[u],dis[v]);//更新各个根节点所在子树的所有节点中距离1结点最近的距离
        }
    }
}

int lca(int u,int h){
    for(int i=19;i>=0;i--){
        if(fa[u][i] && val[fa[u][i]]>h)
            u=fa[u][i];//求出深度最浅的没有积水的子树的根节点
    }
    return dis[u];//返回这个子树中所有结点距离1结点的最近的距离
}

int main(){
    int T,n,m,u,v,l,h,Q,K,S,v0,p0,p,lastans=0;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init(2*n-1);
        for(int i=0;i<m;i++){
            scanf("%d%d%d%d",&u,&v,&l,&h);
            edge0[i].u=u,edge0[i].v=v,edge0[i].h=h;
            addEdge1(u,v,l);
        }
        Dijkstra(1);
        sort(edge0,edge0+m);
        kruskal(n,m);
        dfs(2*n-1,0);
        scanf("%d%d%d",&Q,&K,&S);
        while(Q--){
            scanf("%d%d",&v0,&p0);
            v=(v0+K*lastans-1)%n+1;//v是出发点
            p=(p0+K*lastans)%(S+1);//p是当天水位线
            lastans=lca(v,p);
            printf("%d\n",lastans);
        }
    }
    return 0;
}
