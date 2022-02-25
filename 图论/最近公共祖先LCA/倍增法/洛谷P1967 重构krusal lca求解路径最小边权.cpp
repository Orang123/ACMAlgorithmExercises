#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
int head[N],fa[N][20],dep[N],lg[N],cnt,minw[N][20],ver[N],vis[N];//minw[i][j]��ʾi�ڵ㵽��2^j������֮�����С��Ȩ
/*
����װ���صĻ����ô�ͱ�������ߵ�·����Ҫ�����ܴ�
���������������֮��ĵ�·�϶��Ǿ�����ѡ�����ؽϴ�ĵ�·(̰��),
��ô���ع�ԭͼΪһ�����������,��Ȼԭͼ�п��ܲ�����ͨ,������Ҫ�ع�������������,
���������ɭ��.
��ôҪ��𳵴�x�������͵�y���������������صĻ���,��Ȼ��Ȼ�Ǵ�x��㵽y����·������С��Ȩ,�����
x��㵽y�����С�ı�Ȩ.������Խ������lcafa���鱶����ģ�ķ�ʽ,�����ǿ��Ի�һ��˼·���������u,v�����lca,����Ϊt��
��ôu��v����С��Ȩ����u��t����С��Ȩ �� v��t����С��Ȩȡmin.
��һ������minw(Minimum Weight)������minw[i][j]��ʾi�ڵ㵽��2^j������֮�����С��Ȩ��
*/
struct Node1{
    int u,v,w;
    bool operator <(const Node1 &a)const{
        return w>a.w;
    }
}edge1[M];

struct Node2{
    int to,next,w;
}edge2[N<<1];

void init(int n){
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        ver[i]=i;
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
}

void addEdge(int from,int to,int w){
    edge2[cnt]=(Node2){to,head[from],w};
    head[from]=cnt++;
    edge2[cnt]=(Node2){from,head[to],w};
    head[to]=cnt++;
}

int find(int x){
    return ver[x]==x?x:(ver[x]=find(ver[x]));
}

//kruskal������������� �ڱ�֤���е�·��ͨ�Ļ�����,���ؾ����ܴ�(̰��) ����kruskal��Ҫ�Ǳ�̸��Ӷȵ�,ʮ�ֿ��.
void Kruskal(int n,int m){
    int x,y,num=0;
    for(int i=0;i<m;i++){
        x=find(edge1[i].u);
        y=find(edge1[i].v);
        if(x != y){
            ver[x]=y;
            addEdge(edge1[i].u,edge1[i].v,edge1[i].w);
            num++;
            /*
            ������ԭͼ����ͨ��,��������ڵ���-1ʱ�Ѿ�������,��ʱ�ɾ���ؽ���ѭ��,���Ч��.
            ��Ϊɭ����ʵ�ʵı���Ϊ������ȥɭ�������ĸ���,num<n-1,������Ӱ�����յ�ɭ��.
            */
            if(num == n-1) return;
        }
    }
}

void dfs(int u){
    vis[u]=1;
    for(int i=1,k;i<=lg[dep[u]];i++){
        k=fa[u][i-1];
        fa[u][i]=fa[k][i-1];
        minw[u][i]=min(minw[u][i-1],minw[k][i-1]);//��¼��u�ڵ㵽u���ϵ�2^i�η�����֮��ߵ���СȨֵ
    }
    for(int i=head[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            dep[v]=dep[u]+1;//v�����ȼ�1
            fa[v][0]=u;//��¼v���ĸ���Ϊu���
            minw[v][0]=edge2[i].w;//��¼u��v�ڵ�֮ǰ�ߵ�Ȩֵ
            dfs(v);
        }
    }
}

/*
������ʵ�ǽ�������ȡlca���������˼��,
�ڱ����Ĺ�����˳��������(����ż�����ȵ�)minw(·����С��Ȩ).
��������������ʱ,��ʵ�ǽ�x��㵽y����lca�����,��ԭ�ȵ�·���ֳ���
ż�������Ѿ���¼��minw[i][j]��·��,�����Ϳ��Խ���minwȥ�Ƚ�x����y���ֱ�lca����С��Ȩ
*/
int lca(int x,int y){
    int ans=INF;
    if(dep[x]<dep[y]) swap(x,y);
    int i;
    while(dep[x]>dep[y]){
        i=lg[dep[x]-dep[y]];
        ans=min(ans,minw[x][i]);//��x����������Ĺ����м�¼��������·���ı���СȨֵ
        x=fa[x][i];
    }
    if(x == y)
        return ans;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            ans=min(ans,min(minw[x][i],minw[y][i]));//��x��y���ͬʱ������ʱ��¼,x��y��㵽��������Ƚ��·���ϵ���С��Ȩ
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return min(ans,min(minw[x][0],minw[y][0]));//����ȡ���յ�x��y��㵽�丸��(lca)����С��Ȩ
}

int main(){
    int n,m,x,y,q;
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge1[i].u,&edge1[i].v,&edge1[i].w);
    sort(edge1,edge1+m);
    Kruskal(n,m);
    for(int i=1;i<=n;i++){//ԭͼ��һ����ͨ,���ս��������ɭ��
        if(!vis[i])
            dfs(i);//�������ĸ������Ϊ���ڵ㿪ʼ���� ������Ӱ��·����СȨֵ�ļ���
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&x,&y);
        if(find(x) == find(y))//��x����y��� ������ͨ���޷�����
            printf("%d\n",lca(x,y));
        else printf("-1\n");
    }
    return 0;
}
