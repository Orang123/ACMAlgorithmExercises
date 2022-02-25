#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 200100//这题 数组稍微开大点,最后一个点就不会TLE了,不懂.此题以AC,洛谷有毒. 28.63s
typedef long long ll;
using namespace std;
/*
这类题目好像倍增lca会慢一点,树剖求lca貌似更快.
题意:求解树上两点之间路径上所贡献的愉悦值.即:vi*wi(cnti) 美味指数*新奇指数
val表示该颜色的价值，cnt表示颜色出现的次数，wi表示该颜色出现 cnt[i]次后的价值
*/
int head[N],fa[N][20],lg[N],c[N],a[N<<1],st[N],ed[N],num,dep[N],pos[N<<1],cnt[N],used[N],k,num1,num2;
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
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
}

void addEdge(int from,int to){
    edge[k]=(Node){to,head[from]};
    head[from]=k++;
}

void dfs(int u){
    st[u]=++num;
    a[num]=u;
    for(int i=1;i<=lg[dep[u]];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u][0]){
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    }
    ed[u]=++num;
    a[num]=u;
}

int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]];
    if(x == y) return x;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i] != fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

void add(int x){
    cnt[x]++;
    res+=v[x]*w[cnt[x]];
}

void sub(int x){
    /*
    因为对于这个路径上的游览点来说,糖果的品尝次数 永远都是升序的,
    因此减掉一定是减掉这种糖果品尝次数最高的那一次 新奇指数(最低).
    */
    res-=v[x]*w[cnt[x]];
    cnt[x]--;
}

void calc(int x){
    used[x]?sub(c[x]):add(c[x]);
    used[x]^=1;
}

void change(int x,int i){
    /*
    这里不能用那种待修改的游览点st[x]在欧拉序中的下标是否在Q[i].l Q[i].r区间内来判断对愉悦值有贡献,
    因为有可能它出现了两次，贡献一增一减刚好抵消,此时是没有贡献的,需要根据used[b[x].x],
    若为1则说明之前进行了add,若为0说明之前进行了sub刚好抵消贡献为0.
    */
    if(used[b[x].x]){
        sub(c[b[x].x]);//先减去原先游览点糖果种类的愉悦值
        add(b[x].y);//再添加修改后的糖果增加的愉悦值
        //used[b[x].x]的状态不变,因为这里只是修改 并不是区间又包括b[x].x这个序号.
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
    dfs(1);
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
        /*
        对于这个做法而言修改时间戳放在最前放在最后都对结果没有影响,因为是用used数组判断的,而不是区间,
        对于刚开始还没有计算一次贡献时,used 为0,不会进行贡献的增减.而区间判断法 会进行增减,导致cnt重复增加.
        */
        while(l<Q[i].l) calc(a[l++]);
        while(l>Q[i].l) calc(a[--l]);
        while(r<Q[i].r) calc(a[++r]);
        while(r>Q[i].r) calc(a[r--]);
        while(t<Q[i].t) change(++t,i);
        while(t>Q[i].t) change(t--,i);
        if(Q[i].lca) calc(Q[i].lca);
        ans[Q[i].id]=res;
        if(Q[i].lca) calc(Q[i].lca);
    }
    for(int i=1;i<=num1;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
