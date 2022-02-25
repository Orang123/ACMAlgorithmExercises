#include<cstdio>
#include<cstring>
#define N 500100
int head[N],askHead[N],cnt1,cnt2,fa[N],vis[N],ans[N],visq[N];//ans�����洢lca�Ľ�� visq�ж�ѯ�ʹ�ϵlca�Ƿ񱻼���
struct Node{
    int to,next;
}edge[N<<1];
struct Ask{
    int num,to,next;
}ask[N<<1];//ask �������� ѯ��lca�ı߼���ϵ
/*
tarjan�����㷨,������ָ��һ�α����а����е�lcaѯ��һ���Խ��
ʱ�临�Ӷ�ΪO(n+m),nΪ���е�ĸ���,mΪ����lcaѯ�ʵı߼�����
*/
/*
����ֻ�ǽ����˲��鼯��·��ѹ��˼��,�Ͳ��鼯�ļ��ϲ�˼��ûʲô����,
��find·��ѹ��ʱȥ��¼x��y���������Ǹ���xת�۵�����y���·�������Ƚ��
*/
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);//��findʱ,·��ѹ��,ʹ����һ�β���O(1)ʱ���� ������lca���
}

void addEdge(int from,int to){
    edge[cnt1]=(Node){to,head[from]};
    head[from]=cnt1++;
    edge[cnt1]=(Node){from,head[to]};
    head[to]=cnt1++;
}

void addAsk(int num,int from,int to){
    ask[cnt2]=(Ask){num,to,askHead[from]};
    askHead[from]=cnt2++;
    ask[cnt2]=(Ask){num,from,askHead[to]};
    askHead[to]=cnt2++;
}

void init(int n){
    memset(head,-1,sizeof(head));
    memset(askHead,-1,sizeof(askHead));
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

//O(n+m)
void dfs(int u){
    int v;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){//��������u�ӽڵ�v
        v=edge[i].to;
        if(!vis[v]){
            dfs(v);
            fa[v]=u;//v��������,����ʱ ʹ����fa���ָ���׽��,���������lca,����findʱ �᲻������������lcaת�۽��,���ռ�¼�����Ƚ��
        }
    }
    for(int i=askHead[u];i!=-1;i=ask[i].next){//�������к�u��ѯ�ʹ�ϵ��v
        v=ask[i].to;
        /*
        �����ѯ�߼���v����ѱ����ʹ�,�������lcaѯ�ʶ�Ӧ���±���û�������,��ôlca(u,v)=find(v),
        1.������u��v�Ƿֲ���lca������ʱ,v���findʱ����������������v��㷢��ת�۽���ȥ����u�������ת�۵�,
        Ҳ����lca(u,v),���ﲻ���ظ�����find,��Ϊ��һ�η���u���ʱ,v�ǻ�û������,�ڶ��η���vʱ�Ż����find lca,
        ����Ϊ��(��ͨ�޻�·)�ǲ����ٴη���u����,��˲����ظ�����lca;
        2.���v��㱾�����u����lca,��ô��ʱv����Ȼ��û�л���,Ҳ����fa[v]=v,��ôfind(v)�͵���v,��lca(u,v)=v;
        ���ǵ����ݵ�v���ʱ,��v�����Ϊѯ�ʹ�ϵ�е���ʼ��ʱ,����lca(u,v)�ᱻ�ظ�����һ�Σ�Ϊ�˱����ظ���find����,
        �������visq������¼ѯ�ʹ�ϵ�Ƿ񱻽�������ظ�find
        */
        if(vis[v] && !visq[ask[i].num]){
            ans[ask[i].num]=find(v);
            visq[ask[i].num]=1;//����lcaѯ�ʱ߼�ֻ�ᱻ����һ��,�����ظ�����
        }
    }
}

int main(){
    int n,m,s,x,y;
    scanf("%d%d%d",&n,&m,&s);
    init(n);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    for(int i=0;i<m;i++){
        scanf("%d%d",&x,&y);
        /*
        ����˫���,��Ϊʵ��dfsʱ�����ʵ�lca(x,y)��ϵ�е�x��ʱ,y����ܻ�û�з���,��ʱ���ֻ��xָ��y�ı�,��ô���޷�����lca(x,y)
        ���ѯ�ʱ߼�Ҳ��Ҫ����һ����yָ��x�ı�,�ȷ��ʵ�yʱ,x�պ÷��ʹ�,����ȥ����lca(x,y)
        */
        addAsk(i,x,y);
    }
    dfs(s);
    for(int i=0;i<m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
