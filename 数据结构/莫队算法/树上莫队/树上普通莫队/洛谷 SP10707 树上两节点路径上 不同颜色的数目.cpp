#include<cstdio>
#include<ctype.h>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 40100
#define M 100100
using namespace std;
/*
�����ѹ�,������pos�����СӦ����2*N,һ�㱨wa,�����ǲ���RE ����û����������.
��������������ڵ�·��֮����ֵ���ɫ�������,·��֮��ڵ�ı��������Ҫͨ��
dfs�����õ���ŷ����(��������)����ʾת��,�ظ����ֵĵ�(��������)ʵ�ʲ���������֮���·����,
�ٸ�����lca������ŷ����Ĺ�ϵ����lca�Ƿ�������֮���·����,֮���ٰ�����ͨĪ������ת��
ͳ����ɫ���ִ�������.����lca���ñ��������.

���ŷ����:��Ϊĳ�������ı������лᱻ�丸�ڵ������������ס,���Ʊ�����������,���Ե�����������

Ϊʲô�������εĵ㲻ͳ�ƴ�
����·���Ķ���Ϊ����x��y�����ڵ�������ٵ�·��.
��һ����k�������Σ�˵�����ǿ����ȷ���k������k�������У�Ȼ��������ٵ�y������Ȼ������k�Ǹ��ŵġ���˳������εĵ㲻��ͳ�����
*/

/*
b[N<<1]��dfs�����õ���ŷ����(��������),��Ϊÿ�α�����ֱ���st��ed�����¼һ��������Ҫ2*N�Ŀռ俪��
st[u]�ǵ�һ�α���u��ʱ��ŷ������±�,�����u��Ӧ����ʵ���������ݵ������±�
ed[u]��u���u�������������,׼������ʱ,��Ӧ��ŷ������.
used[u]��������ŷ�����е��ظ�������ͳ�Ƴ�����ɫ������������(һ��add,һ��sub)
tmp[N]��������ɢ��a[N]��ɫ��������,������ɫ��Ȩֵ�е��,����ɢ��������Խ��RE
*/
/*����pos[N<<1]���鿪��һ����2*N,��Ϊ�ֿ��Ƕ�ŷ����b����ֿ�,�������Խ��RE����spoj������WA,���˺þò�֪���Ĵ���*/
int head[N],fa[N][20],dep[N],b[N<<1],st[N],ed[N],num,lg[N],used[N],a[N],tmp[N],pos[N<<1],cnt[N],ans[M],res,k;

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
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
}

/*
��ɢ��:ͨ�׵ؽ����ǵ���Щ������Ϊ����ܴ�������Ͳ�֧�֣������޷���Ϊ������±�������ش���
��Ӱ�����ս����ֻ��Ԫ��֮�����Դ�С��ϵʱ�����ǿ��Խ�ԭ�������ݰ��մӴ�С������������⣬����ɢ����

��Ϊ��ɫ����ı��ֵ����,����cnt�����±�ռ俪���޷������Խ��,
����a������Ҫ��ɢ������,���ǽ�һ����ֵ֮�����Ƚϴ������
������max - ��max > 1������ת����max - ��max = 1�����飬
Ҳ���ǵ�������������ֵ���㷨Ӱ�첻�󣬵��Ǵ�С��ϵӰ��ϴ��ʱ��
���ǰ����ǵĴ�С��ϵ�����1������ʾ��

a���飺 99 55 68 47 100 2888888888
��ɢ�����b����
b���飺 4 2 3 1 5 6
���Կ�����ֵ��Χ��С����൫�Ƕ�Ӧ�±�ĸ����С��ϵ�ǲ���ġ�
*/
void discretization(int n){
    sort(tmp+1,tmp+1+n);
    /*
    ���ǲ�ͬ�����£���ͬ����ʧ���ú�����ȥ���������ظ����ֵ���ֵ��ֻ���µ�һ�γ��ֵ���ֵ��
    unique��Ҫ����������������ʹ��
    */
    int len=unique(tmp+1,tmp+1+n)-tmp-1;
    /*
    lower_bound�Ƕ��ֲ��� upper_bound�Ǵ���(û�е���)
    lower_bound�᷵�ز�ѯ����(tmp)�е�һ�����ڵ��ڲ�ѯ��ֵ(a[i])��λ�õ������±�
    */
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(tmp+1,tmp+1+len,a[i])-tmp;
}

//linux�´����ﲻ����index,�������ᱨ��. edge[index]
void addEdge(int from,int to){
    edge[k]=Node(to,head[from]);
    head[from]=k++;
    edge[k]=Node(from,head[to]);
    head[to]=k++;
}

void dfs(int u){
    st[u]=++num;//st��¼�տ�ʼ����u��ʱ��ŷ�������±�
    b[num]=u;//ͬʱ��u��¼ŷ������
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
    ed[u]=++num;//ed��¼u�㼰������������Ϻ��ŷ�������±�
    b[num]=u;
}

int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]];
    if(x == y) return x;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

void add(int x){
    if(!cnt[x]++) res++;
}

void sub(int x){
    if(!--cnt[x]) res--;
}

void calc(int x){
    if(!used[x]) add(a[x]);//used[x]=0ʱ����ŷ�������е�һ��ͳ�Ƹ���ɫʱ,��������ڵ���ֹ�,ͳ������ɫ���ִ���
    /*
    used[x]=1ʱ����ŷ�������������ɫ���±����������,��ôʵ��·���в��������õ�,
    ���Խ�֮ǰ�ۼӵ���ɫ�ټ���������.
    */
    else sub(a[x]);
    used[x]^=1;//��used[x]��1���,����0��Ϊ��1,�ڶ��γ��ּ���ʱ,�ͻ����sub��֮ǰ���ֵĴ�������,�պõ�����,Ȼ��used[x]�����ͱ�Ϊ0�����´�add���Ӵ���
}

int main(){
    int n,m,u,v,siz,_lca;
    n=read(),m=read();
    init(n);
    for(int i=1;i<=n;i++)
        a[i]=tmp[i]=read();
    discretization(n);
    for(int i=1;i<=n-1;i++){
        u=read(),v=read();
        addEdge(u,v);
    }
    dfs(1);//���� ���ĸ����Ϊ���ڵ� ����Ӱ��������·�������Ľڵ���ɫ����
    siz=sqrt(num);//siz���С ���������е�ƽ����,��Ϊÿ��ѯ�ʵ�l��r��¼�����������е��±�
    for(int i=1;i<=num;i++)
        pos[i]=(i-1)/siz+1;
    for(int i=1;i<=m;i++){
        u=read(),v=read();
        _lca=lca(u,v);//���������ɫ�±��lca
        if(st[u]>st[v]) swap(u,v);//u����Զ��ʾŷ�������н�������Ľڵ�
        /*
        ��u����lca,��˵��u��v����ֲ���lca������,��ôŷ��������֮�г����ظ�����,
        �պ�������lca�ڵ�,����Ҫ��¼����֮���·������lca.
        ��������ѯ�������l�˵�����¼��ӦΪu����ŷ�������ʱ�Ľ����±����,��Ϊ����¼st��ʼ���,
        ��Ὣu��֮��������еĽڵ����Ҳ��¼��ȥ,��ʵ����Щ�㲢������������֮���·����.
        */
        if(_lca != u) q[i]=seq(ed[u],st[v],_lca,i);
        /*
        ��u��lca,��˵��v����u��������,��ôŷ������ed[v]��ed[u]���,
        ��ʵ������֮���·��ֻ����[st[u],st[v]]�г����������εĵ�.
        */
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
        /*
        ������ѯ����·���ϻ�����lca,��ôÿ����ɫ�������˺�һ��Ҫ������res��ȥ��,
        �����Ӱ����һ��ѯ�ʵĽ��,��Ϊ������һ��ѯ�ʵ��������������lca��ôres�Ͷ����,
        �����һ������պð���lca�����,��ô����used[x]��ֵΪ1,�������,
        res��ֵ�պü�����,res���ռ���Ľ�������.
        */
        if(q[i].lca) calc(q[i].lca);//������ѯ����·���ϻ�����lca,��ôÿ����ɫ�������˺�һ��Ҫ������res��ȥ��,�����Ӱ����һ��ѯ�ʵĽ��,��Ϊ������һ��ѯ�ʵ��������������lca��ôres�Ͷ����,�����һ������պð���lca�����,��ô����used[x]��ֵΪ1,�������,res��ֵ�պü�����,res���ռ���Ľ�������������
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
