#include<cstdio>
#include<ctype.h>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 40100
#define M 100100
using namespace std;
int head[N],fa[N],dep[N],siz[N],son[N],top[N],b[N<<1],st[N],ed[N],num,used[N],a[N],tmp[N],pos[N<<1],cnt[N],ans[M],res,k;

struct Node{
    int to,next;
    Node(){}
    Node(int to,int next):to(to),next(next){}
}edge[N<<1];

struct seq{
    int l,r,lca,id;
    seq(){}
    seq(int l,int r,int lca,int id):l(l),r(r),lca(lca),id(id){}
    bool operator < (const seq &x)const{
        return pos[l]^pos[x.l]?l<x.l:(pos[l]&1?r<x.r:r>x.r);
    }
}q[M];

inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void init(int n){
    memset(head,-1,sizeof(head));
}

void discretization(int n){
    sort(tmp+1,tmp+1+n);
    int len=unique(tmp+1,tmp+1+n)-tmp-1;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(tmp+1,tmp+1+len,a[i])-tmp;
}


void addEdge(int from,int to){
    edge[k]=Node(to,head[from]);
    head[from]=k++;
    edge[k]=Node(from,head[to]);
    head[to]=k++;
}

void dfs1(int u){
    st[u]=++num;
    b[num]=u;
    siz[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u]){
            fa[v]=u;
            dep[v]=dep[u]+1;
            dfs1(v);
            siz[u]+=siz[v];
            if(siz[v]>siz[son[u]])
                son[u]=v;
        }
    }
    ed[u]=++num;
    b[num]=u;
}

void dfs2(int u,int t){
    top[u]=t;
    if(son[u])
        dfs2(son[u],t);
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u] && v!=son[u])
            dfs2(v,v);
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]])
            x=fa[top[x]];
        else
            y=fa[top[y]];
    }
    return dep[x]<dep[y]?x:y;
}

void add(int x){
    if(!cnt[x]++) res++;
}

void sub(int x){
    if(!--cnt[x]) res--;
}

void calc(int x){
    if(!used[x]) add(a[x]);
    else sub(a[x]);
    used[x]^=1;
}

int main(){
    int n,m,u,v,siz0,_lca;
    n=read(),m=read();
    init(n);
    for(int i=1;i<=n;i++)
        a[i]=tmp[i]=read();
    discretization(n);
    for(int i=1;i<=n-1;i++){
        u=read(),v=read();
        addEdge(u,v);
    }
    dfs1(1);
    dfs2(1,1);
    siz0=sqrt(num);//siz块大小 是括号序列的平方根,因为每条询问的lca l r记录的是括号序列的下标
    for(int i=1;i<=num;i++)
        pos[i]=(i-1)/siz0+1;
    for(int i=1;i<=m;i++){
        u=read(),v=read();
        _lca=lca(u,v);
        if(st[u]>st[v]) swap(u,v);
        if(_lca != u) q[i]=seq(ed[u],st[v],_lca,i);
        else q[i]=seq(st[u],st[v],0,i);
    }
    sort(q+1,q+1+m);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l<q[i].l) calc(b[l++]);
        while(l>q[i].l) calc(b[--l]);
        while(r<q[i].r) calc(b[++r]);
        while(r>q[i].r) calc(b[r--]);
        if(q[i].lca) calc(q[i].lca);
        ans[q[i].id]=res;
        if(q[i].lca) calc(q[i].lca);
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
