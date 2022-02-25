#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 200100//���� ������΢�����,���һ����Ͳ���TLE��,����.������AC,����ж�. 28.63s
typedef long long ll;
using namespace std;
/*
������Ŀ������lca����һ��,������lcaò�Ƹ���.
����:�����������֮��·���������׵�����ֵ.��:vi*wi(cnti) ��ζָ��*����ָ��
val��ʾ����ɫ�ļ�ֵ��cnt��ʾ��ɫ���ֵĴ�����wi��ʾ����ɫ���� cnt[i]�κ�ļ�ֵ
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
    ��Ϊ�������·���ϵ���������˵,�ǹ���Ʒ������ ��Զ���������,
    ��˼���һ���Ǽ��������ǹ�Ʒ��������ߵ���һ�� ����ָ��(���).
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
    ���ﲻ�������ִ��޸ĵ�������st[x]��ŷ�����е��±��Ƿ���Q[i].l Q[i].r���������ж϶�����ֵ�й���,
    ��Ϊ�п��������������Σ�����һ��һ���պõ���,��ʱ��û�й��׵�,��Ҫ����used[b[x].x],
    ��Ϊ1��˵��֮ǰ������add,��Ϊ0˵��֮ǰ������sub�պõ�������Ϊ0.
    */
    if(used[b[x].x]){
        sub(c[b[x].x]);//�ȼ�ȥԭ���������ǹ����������ֵ
        add(b[x].y);//������޸ĺ���ǹ����ӵ�����ֵ
        //used[b[x].x]��״̬����,��Ϊ����ֻ���޸� �����������ְ���b[x].x������.
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
        ����������������޸�ʱ���������ǰ������󶼶Խ��û��Ӱ��,��Ϊ����used�����жϵ�,����������,
        ���ڸտ�ʼ��û�м���һ�ι���ʱ,used Ϊ0,������й��׵�����.�������жϷ� ���������,����cnt�ظ�����.
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
