#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int N=200100;
/*
三个大根堆：
C[u]里装的是点分树中u的子树所有点到点分树中u的父亲的距离。
B[u]里装的是点分树中u的所有儿子的C的最大值。
A里装的是所有BB的最大值与次大值之和。
A的堆顶就是答案。
（我一开始一直以为两个堆就行，对第三个对表示疑惑，又懒得深入想，一直翻题解。千万不能犯懒不想啊）
我们找答案可以快速找到。问题是怎么维护？
因为我们是点分树，深度小，可以直接一个一个跳到根暴力修改维护。具体一些就是设删的点为xx，跳到一个点uu把xx的贡献从C[u]中删掉，然后重新跟新B[u]和A。
至此本题得到解决，就是我代码常数太大。
*/
struct que{
    priority_queue<int> x,y;
    inline void push(int a){x.push(a);}
    inline void del(int a){y.push(a);}
    //在取最大值时, 若 排序堆 和 删除堆 的 堆顶元素相同, 就意味着这个元素已经被删除了, 把它们双双弹出.
    inline int top(){while(y.size()&&x.top()==y.top())x.pop(),y.pop();return x.top();}
    inline int size(){return x.size()-y.size();}
    inline void pop(){while(y.size()&&x.top()==y.top())x.pop(),y.pop();x.pop();}
    inline int sectop(){int a=top();pop();int b=top();push(a);return b;}
}A,B[N],C[N];
int cnt,head[N];
int light[N],tot,n,m;
int root,size[N],g[N],vis[N],all,f[N];
int dep[N],mn[N*2][24],num,dfn[N];
int Log[N];
struct edge{
    int to,nxt;
}e[N*2];
inline void add_edge(int u,int v){
    cnt++;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
inline void dfs(int u,int f){
    dfn[u]=++num;
    dep[u]=dep[f]+1;
    mn[num][0]=dep[u];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==f)continue;
        dfs(v,u);
        mn[++num][0]=dep[u];
    }
}
inline void getroot(int u,int f){
    g[u]=0;size[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==f||vis[v])continue;
        getroot(v,u);
        g[u]=max(g[u],size[v]);
        size[u]+=size[v];
    }
    g[u]=max(g[u],all-size[u]);
    if(g[u]<g[root])root=u;
}
inline int getdep(int x,int y){
    int a=dfn[x];
    int b=dfn[y];
    if(a>b)swap(a,b);
    int len=Log[b-a+1];
    return min(mn[a][len],mn[b-(1<<len)+1][len]);
}
inline int dis(int x,int y){
    return dep[x]+dep[y]-2*getdep(x,y);
}
inline void work(int u,int ff){
    C[root].push(dis(u,f[root]));
    size[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==ff||vis[v])continue;
        work(v,u);
        size[u]+=size[v];
    }
}
inline void pusha(int x){
    if(B[x].size()>=2)A.push(B[x].top()+B[x].sectop());
}
inline void dela(int x){
    if(B[x].size()>=2)A.del(B[x].top()+B[x].sectop());
}
inline void build(int u,int ff){
    f[u]=ff;vis[u]=1;
    B[u].push(0);
    work(u,0);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(vis[v])continue;
        root=0,all=size[v];
        getroot(v,0);
        v=root;
        build(root,u);
        B[u].push(C[v].top());
    }
    pusha(u);
}
inline void on(int x){
    dela(x);
    B[x].del(0);
    pusha(x);
    for(int i=x;f[i];i=f[i]){
        dela(f[i]);
        B[f[i]].del(C[i].top());
        C[i].del(dis(x,f[i]));
        if(C[i].size())B[f[i]].push(C[i].top());
        pusha(f[i]);
    }
}
inline void off(int x){
    dela(x);
    B[x].push(0);
    pusha(x);
    for(int i=x;f[i];i=f[i]){
        dela(f[i]);
        if(C[i].size())B[f[i]].del(C[i].top());
        C[i].push(dis(x,f[i]));
        B[f[i]].push(C[i].top());
        pusha(f[i]);
    }
}
void prework(){
    for(int j=1;j<=Log[num];j++)
        for(int i=1;i+(1<<j)-1<=num;i++)
            mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
}
inline int read(){
    int sum=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){sum=sum*10+ch-'0';ch=getchar();}
    return sum*f;
}
int main(){
    n=read();
    Log[0]=-1;for(int i=1;i<=200000;i++)Log[i]=Log[i>>1]+1;
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add_edge(u,v);add_edge(v,u);
    }
    dfs(1,0);
    prework();
    g[0]=n;root=0;all=n;
    getroot(1,0);build(root,0);
    tot=n;
    m=read();
    char s;
    while(m--){
        s=getchar();
        if(s=='G'){
            if(tot<=1)printf("%d\n",tot-1);
            else printf("%d\n",A.top());
        }
        else{
            int x=read();
            if(light[x]==0)on(x),tot--;
            else off(x),tot++;
            light[x]^=1;
        }
    }
    return 0;
}
