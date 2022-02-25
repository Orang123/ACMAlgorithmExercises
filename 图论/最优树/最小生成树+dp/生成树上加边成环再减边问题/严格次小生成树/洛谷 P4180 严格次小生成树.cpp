#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 300100
using namespace std;
/*
�ϸ��С���������Ǳ�Ȩ֮���ϸ���ڣ����ܵ���,Ҳ������ӵı�Ȩһ������mst·��������Ȩ��,
����������������������������Ȩ֮������С����.
����˵ĳͼ����С�������ı�Ȩ��Ϊ88�����������ļ����������ı�Ȩ�ͷֱ�Ϊ88��88��90��100��103��111,
��ô��Ȩ��Ϊ90�����������Ǹ�ͼ���ϸ��С����������������һ�ñ�Ȩ��Ϊ88�����������Ǹ�ͼ�ķ��ϸ��С������
����ʱ������ı�Ȩ�� �� mst�ı�Ȩ������ˣ�.
�ڷ��ϸ��С��������,����ӵıߵı�Ȩһ����С�����ֵ������Ͳ�����С��������,
��mst·��������Ȩ������ӵı�Ȩʱ,��ʱ���γɵ�mst�ı�Ȩ�ͺ�֮ǰ��mst��ͬ�����ڷ��ϸ��С������(���������ϸ��С������),
��ˣ������ϸ��С��������˵,����Ҫ���ϵ����ֵ����Ҫ���ϵĴδ�ֵ��
�����ڳ������ֵ���ڱ�Ȩʱ�����ôδ�ֵ���´𰸣���֤����ȷ��.
max1w[x][i],max2w[x][i] �ֱ��ʾx��������2^i��·���б�Ȩ�����ֵ��x��������2^i��·���б�Ȩ�Ĵδ�ֵ.
*/
int head[N],fa[N][20],dep[N],lg[N],max1w[N][20],max2w[N][20],ver[N],vis[N],cnt;
long long sum,ans=1e18;
struct Node1{
    int u,v,w,vis;
    bool operator <(const Node1 &x)const{
        return w<x.w;
    }
}edge1[M];
struct Node2{
    int to,next,w;
}edge2[N<<1];

void init(int n){
    memset(head,-1,sizeof(head));
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)
        ver[i]=i;
}

int find(int x){
    return ver[x]==x?x:(ver[x]=find(ver[x]));
}

void addEdge(int from,int to,int w){
    edge2[cnt]=(Node2){to,head[from],w};
    head[from]=cnt++;
    edge2[cnt]=(Node2){from,head[to],w};
    head[to]=cnt++;
}

void kruskal(int n,int m){
    int num=0,x,y;
    for(int i=0;i<m;i++){
        x=find(edge1[i].u);
        y=find(edge1[i].v);
        if(x != y){
            ver[x]=y;
            edge1[i].vis=1;//����������ѱ�����mst��
            sum+=edge1[i].w;
            addEdge(edge1[i].u,edge1[i].v,edge1[i].w);//���¹���mst����dfs
            num++;
            if(num == n-1) return;
        }
    }
}

void dfs(int u){
    vis[u]=1;
    for(int i=1,k;i<=lg[dep[u]];i++){
        k=fa[u][i-1];//kΪu�����ϵ�2^(i-1)�������Ƚ��ı��
        fa[u][i]=fa[k][i-1];
        max1w[u][i]=max(max1w[u][i-1],max1w[k][i-1]);//ͳ��u�㵽�����ϵ�2^i�η������Ƚ��·�������Ȩ�����ֵ
        max2w[u][i]=max(max2w[u][i-1],max2w[k][i-1]);//ͳ��u�㵽�����ϵ�2^i�η������Ƚ��·�������Ȩ�Ĵδ�ֵ
        /*
        ��u�����ϵ�2������Ϊ2^(i-1)�η�����·���ڵı�Ȩ�����ֵ�����,
        ��ômaxw1[u][i]��Ȩ�Ĵδ�ֵȡ��2���������ֵ�Ľ�С��,
        �ٺ�֮ǰ���������Ĵ�С��ȡ�ϴ�ֵΪmax2[u][i]�ı�Ȩ�δ�ֵ.
        ֮���Ի�Ҫ�ͱ����Ѿ��������max2[u][i]�δ�ֵ�Ƚ�����Ϊ
        max1w[u][i-1]��max1w[k][i-1]��С���п��ܱ�֮ǰ�������max2[u][i]�δ�ֵ��ҪС,
        �������Ҫȡ�δ�ֵ,��Ҫ�ٱȽ�.�����Сֵȡ����max1w[k][i-1],��֮ǰ�δ�ֵ��ȡ����max2w[u][i-1],
        ���max2w[u][i-1]���п��ܱ�max1w[k][i-1]��Ҫ���.
        */
        if(max1w[u][i-1] != max1w[k][i-1])
            max2w[u][i]=max(max2w[u][i],min(max1w[u][i-1],max1w[k][i-1]));
        /*
        ��u�����ϵ�2������Ϊ2^(i-1)�η�����·���ڵı�Ȩ�����ֵ���,��ô��Сֵ��ֻ�ܿ���max2w[u][i-1],max2w[k][i-1]�нϴ���,
        �����ſ��Ա��⵱ö�ٲ���mst�ı�Ȩ�պõ���·���б�Ȩ�ϴ�ֵʱ��ѡ�ı�Ȩ�δ�ֵ�����ֵ���,�������ܹ�����ϸ��С������,
        ��Ȩֵ��ҪС��mst��.
        */
    }
    for(int i=head[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            dep[v]=dep[u]+1;
            fa[v][0]=u;
            max1w[v][0]=edge2[i].w;//���ﲻ�ܳ�ʼ��max2w[v][0],��Ϊ����ȡmax2w[v][1]=(max2w[v][0],max2w[k][0])�������������Ȩ,�����Ǵδ��Ȩ
            dfs(v);
        }
    }
}

//����lca�����Ĺ��� ��ȡx��y·���ϵ�����Ȩ��δ��Ȩ wΪδ����mst�еı�Ȩ
int lca(int x,int y,int w){
    int k,res=-1;
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]){
        k=lg[dep[x]-dep[y]];
        /*
        ��w������Ȩ����,��ô����wһ����������Ȩ,��ô��ѡ��δ����mst�еı�Ȩȥ�滻����Ȩ,�滻��ı�Ȩ��Ҳ����֮ǰmst�ı�Ȩ��
        ���w������Ȩ���,��Ϊ�˱����滻��ı�Ȩ��֮ǰmst�ı�Ȩ��һ��,����ѡ��wȥ�滻max2��Ȩ�δ�ֵ,
        ����wҲһ���Ǵ���max2�δ�ֵ��,ͬ�����յ��滻��ı�Ȩ��Ҳ����֮ǰmst�ı�Ȩ��.
        */
        res=max(res,max1w[x][k]!=w?max1w[x][k]:max2w[x][k]);
        x=fa[x][k];
    }
    if(x == y) return res;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i] != fa[y][i]){
            res=max(res,max1w[x][i]!=w?max1w[x][i]:max2w[x][i]);//������Ҫͬʱ�ȶ�x��y���ͬʱ������������·���еı�Ȩ���ֵ
            res=max(res,max1w[y][i]!=w?max1w[y][i]:max2w[y][i]);
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    res=max(res,max1w[x][0]!=w?max1w[x][0]:max2w[x][0]);//���Ƚ�x��y��㵽�丸�׽��(lca)��Ȩ
    res=max(res,max1w[y][0]!=w?max1w[y][0]:max2w[y][0]);
    return res;
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge1[i].u,&edge1[i].v,&edge1[i].w);
    sort(edge1,edge1+m);
    kruskal(n,m);
    dfs(1);
    for(int i=0;i<m;i++){
        if(!edge1[i].vis){
            int res=lca(edge1[i].u,edge1[i].v,edge1[i].w);//�����lca,���������lca�����Ĺ������x��y·���ϱ�Ȩ�����ֵ
            /*
            ��edge1[i].u��edge1[i].v������Ȩ����mst�л������,����ͬʱɾȥ
            mst��edge1[i].u��edge1[i].v��·����Ȩ�����ֵ�͹������ϸ��С������
            ֮����Ҫ�滻·���ϵı�Ȩ���ֵ����Ϊ,mst Kruskalÿ�μ���ı�һ������С��,
            ����Ϊѡ��mst�еı�Ȩһ�����ڵ���·���ϵ�����Ȩ��,����ǰ����ľͲ���mst��,
            mst�ڹ���ʱ��Ӧ�ð�����δ����mst�еı�Ȩ����mst����
            */
            ans=min(ans,sum-res+edge1[i].w);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
/*
����ȡx��y·���ϵ�����Ȩ�ֳ���2�����,��������lca(x,y),
��ȥ�ֱ����x��lca(x,y)��y��lca(x,y)������Ȩ��������Ƚ�,
û�б�Ҫ��ô��,ֱ���ڵ�һ����ȡlca�Ĺ�����Ͱ�x��y������Ȩ������.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 300100
using namespace std;
int head[N],fa[N][20],dep[N],lg[N],max1w[N][20],max2w[N][20],ver[N],vis[N],cnt;
long long sum,ans=1e18;
struct Node1{
    int u,v,w,vis;
    bool operator <(const Node1 &x)const{
        return w<x.w;
    }
}edge1[M];
struct Node2{
    int to,next,w;
}edge2[N<<1];

void init(int n){
    memset(head,-1,sizeof(head));
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)
        ver[i]=i;
}

int find(int x){
    return ver[x]==x?x:(ver[x]=find(ver[x]));
}

void addEdge(int from,int to,int w){
    edge2[cnt]=(Node2){to,head[from],w};
    head[from]=cnt++;
    edge2[cnt]=(Node2){from,head[to],w};
    head[to]=cnt++;
}

void kruskal(int n,int m){
    int num=0,x,y;
    for(int i=0;i<m;i++){
        x=find(edge1[i].u);
        y=find(edge1[i].v);
        if(x != y){
            ver[x]=y;
            edge1[i].vis=1;
            sum+=edge1[i].w;
            addEdge(edge1[i].u,edge1[i].v,edge1[i].w);
            num++;
            if(num == n-1) return;
        }
    }
}

void dfs(int u){
    vis[u]=1;
    for(int i=1,k;i<=lg[dep[u]];i++){
        k=fa[u][i-1];
        fa[u][i]=fa[k][i-1];
        max1w[u][i]=max(max1w[u][i-1],max1w[k][i-1]);
        max2w[u][i]=max(max2w[u][i-1],max2w[k][i-1]);
        if(max1w[u][i-1] != max1w[k][i-1])
            max2w[u][i]=max(max2w[u][i],min(max1w[u][i-1],max1w[k][i-1]));
    }
    for(int i=head[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            dep[v]=dep[u]+1;
            fa[v][0]=u;
            max1w[v][0]=edge2[i].w;
            dfs(v);
        }
    }
}

int lca(int x,int y){
    int k;
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]){
        k=lg[dep[x]-dep[y]];
        x=fa[x][k];
    }
    if(x == y) return x;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i] != fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int getMaxw(int x,int y,int w){
    int res=-1,k;
    while(dep[x]>dep[y]){
        k=lg[dep[x]-dep[y]];
        res=max(res,max1w[x][k]!=w?max1w[x][k]:max2w[x][k]);
        x=fa[x][k];
    }
    return res;

}

int main(){
    int n,m,x,y,res,maxu,maxv;
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge1[i].u,&edge1[i].v,&edge1[i].w);
    sort(edge1,edge1+m);
    kruskal(n,m);
    dfs(1);
    for(int i=0;i<m;i++){
        if(!edge1[i].vis){
            res=lca(edge1[i].u,edge1[i].v);
            maxu=getMaxw(edge1[i].u,res,edge1[i].w);
            maxv=getMaxw(edge1[i].v,res,edge1[i].w);
            ans=min(ans,sum-max(maxu,maxv)+edge1[i].w);
        }
    }
    printf("%lld\n",ans);
    return 0;
}*/
