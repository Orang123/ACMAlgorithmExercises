#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 100100
typedef long long ll;//AC 31.22s 总时间比倍增慢,但最后一个点比lca快.
using namespace std;
int head[N],fa[N],dep[N],siz[N],son[N],top[N],c[N],a[N<<1],st[N],ed[N],num,pos[N<<1],cnt[N],used[N],k,num1,num2;
ll res,v[N],w[N],ans[N];
struct seq{
    int l,r,id,t,lca;
    bool operator <(const seq &x)const{
        if(pos[l]!=pos[x.l]) return l<x.l;
        if(pos[r]!=pos[x.r]) return r<x.r;
        return t<x.t;
    }
}Q[N];

struct Node{
    int to,next;
}edge[N<<1];

struct B{
    int x,y;
}b[N];

void init(int n){
    memset(head,-1,sizeof(head));
}

void addEdge(int from,int to){
    edge[k]=(Node){to,head[from]};
    head[from]=k++;
}

void dfs1(int u){
    st[u]=++num;
    a[num]=u;
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
    a[num]=u;
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
    cnt[x]++;
    res+=v[x]*w[cnt[x]];
}

void sub(int x){
    res-=v[x]*w[cnt[x]];
    cnt[x]--;
}

void calc(int x){
    used[x]?sub(c[x]):add(c[x]);
    used[x]^=1;
}

void change(int x,int i){
    if(used[b[x].x]){
        sub(c[b[x].x]);
        add(b[x].y);
    }
    swap(c[b[x].x],b[x].y);
}


int main(){
    int n,m,q,a0,b0,type,_lca,siz;
    scanf("%d%d%d",&n,&m,&q);
    init(n);
    for(int i=1;i<=m;i++)
        scanf("%lld",&v[i]);
    for(int i=1;i<=n;i++)
        scanf("%lld",&w[i]);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&a0,&b0);
        addEdge(a0,b0);
        addEdge(b0,a0);
    }
    dfs1(1);
    dfs2(1,1);
    siz=pow(num,2.0/3.0);
    for(int i=1;i<=num;i++)
        pos[i]=(i-1)/siz+1;
    for(int i=1;i<=n;i++)
        scanf("%d",&c[i]);
    while(q--){
        scanf("%d%d%d",&type,&a0,&b0);
        if(type){
            _lca=lca(a0,b0);
            if(st[a0]>st[b0]) swap(a0,b0);
            if(_lca == a0)
                Q[++num1]=(seq){st[a0],st[b0],num1,num2,0};
            else
                Q[++num1]=(seq){ed[a0],st[b0],num1,num2,_lca};
        }
        else
            b[++num2]=(B){a0,b0};

    }
    sort(Q+1,Q+1+num1);
    int l=1,r=0,t=0;
    for(int i=1;i<=num1;i++){
        while(t<Q[i].t) change(++t,i);
        while(t>Q[i].t) change(t--,i);
        while(l<Q[i].l) calc(a[l++]);
        while(l>Q[i].l) calc(a[--l]);
        while(r<Q[i].r) calc(a[++r]);
        while(r>Q[i].r) calc(a[r--]);
        if(Q[i].lca) calc(Q[i].lca);
        ans[Q[i].id]=res;
        if(Q[i].lca) calc(Q[i].lca);
    }
    for(int i=1;i<=num1;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
