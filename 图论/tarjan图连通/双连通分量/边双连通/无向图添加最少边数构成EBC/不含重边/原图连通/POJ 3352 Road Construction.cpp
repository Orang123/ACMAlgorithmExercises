#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;
//ac ���tarjan���SCC���� 16ms
/*
��ظ���:
����ͼ��Ϊ����˫���,���Բ����ֳ������,ͳһֻ�����Ķ�.
1.��˫��ͨͼ:��һ������ͼ�е�ȥ������һ����,������ı��ͼ����ͨ��,
�������ڸ��/��,�������˫��ͨͼ(Edge Biconnected Graph-EBG).
2.��˫��ͨ����:һ������ͼ�е�ÿһ�������˫��ͨ��ͼ����������ͼ�ı�˫��ͨ����(Edge Biconnected Component-EBC).
3.��˫��ͨ��������ֻ��һ����.
4.��˫��ͨ���������������ͼ�еĺ���������Ļ�,�����������ͼ�и������ܵ����,��:�����ಢ���ͼ����ཻ��Ļ�,
���Ǻ�ŷ����·û��ϵ,ŷ����·��ָ����ͼ�����б�һ�λ��ܻص����,�����Ҫ����ͼ�е����б�,�����ص������б�,�����Ǽ���������ӻ�.

���ʶ���:
1.���/�ŵ������˵�ض��ֱ�����ԭͼ��������˫��ͨ����(ebc),һ��ɾ������,
��������˫��ͨ�����ض��Ͽ�,ԭͼ�Ͳ���ͨ��.�����������������û��ֱ�����ߵ�ebc
֮�������һ����,��������������ebc���žͲ���������,��Ϊɾ��ԭ�ȵ���,������ebc�仹�б�,
2��ebc������ͨ,ԭͼ�Ծ�����ͨ��.��ôʹ��ԭͼ��ΪEBG��������߱�Ȼ���ڸ�����Ϊ1��ebc��(������-Ҷ�ӽڵ�)���.
2.��Ϊ����ͼ(������ͨ,������ͨ��ͼͬ��)������˫��ͨ����(EBC)�еĵ㶼�������ظ�,
��������ͼ�а���EBC����ʣ�µ����߶��Ǹ��,��ɾ����һ���߶��ᵼ��ԭͼ����ͨ,
�����������õ���Ȼ��һ��������(������������ɭ��).
�Աȵ�˫��ͨ������Ϊͬһ�����Ϊ����PBC�еĵ�,����PBC����һ�㲻��������.
3.����һ��������,����Ҫʹ�����ɱ�˫��ͨͼ,��Ҫ��ӵı��� == (���ж���Ϊ1�ĵ�ĸ���+1)/2.
���ж���Ϊ1�ĵ�ʵ�ʾ���Ҷ�ӽڵ�.Ҫ��֤��ͨ�Ծͱ����ж�,����Ϊ1,�������б�����,��ȻҶ�ӽڵ�.
�����ӵı�һ���Ǽ���Ҷ�ӽڵ��,����Ҫ������,�����ܸ���Ҷ�ӽڵ��պ�û�б�,�����������ټӱ���.
4.��һ����˫��ͨͼ(EBG)����������䶼����������·��.��������ͼ����ebc�������������ٱ߳�ΪEBG,
���EBG���������ֻ��2��·��,��ʱ�ӱ����������ٵ�.
5.�Ǳ�˫��ͨ��������һ���ǵ�˫��ͨ����,�ǵ�˫��ͨ����һ���Ǳ�˫��ͨ����(��Ϊɾ���������Ȼ������ɾ�������).
6.����ͼebc��������γɵ������������߶���ԭ����ͼ�е���,����ԭͼ���ŵĸ����͵������ı���=ebc_cnt-1

ע��:
1.�������ж���Ϊ1�ĵ�ĸ������Ϊż��,��ôż��+1Ϊ����,��2������,���账��,��������������
����ȡ����,����1-2,1-3,1-4,1-5,4��Ҷ�ӽڵ�"2,3,4,5",ѡ����Ҷ�ӽڵ�����2����,�Ϳ�ʹ���ɱ�˫��ͨͼ.
��ʵ�ʶ�Ϊ1�Ľڵ����Ϊ4,(4+1)/2=5/2=2 int���������������ȡ����,���Ҳ��ȷ.
������ټӱ�����һ���������,֤����ʱ��֪.
2.�Ǳ�˫��ͨͼһ����ǿ��ͨͼ,��ǿ��ͨͼ��һ���Ǳ�˫��ͨͼ(SCC��ɾ��һ����,��Ȼ�㲢û�б��ָ�,
����Ϊ�������,ɾ������Щ��֮�䲢���ɴ�).
*/

/*
����:n�����ξ���,m����·,������ʩ����λ����ĳЩ��·ʩ��,
���ܻᵼ���οͲ��ܴ��������ͨ��,�������������޽�������
�µ�·����ʹ��ʩ����λ�ڵ�·ʩ����Ӱ���ο�����������������.
����:һ������ͼ(���ر߲���һ����ͨ),����Ҫ��Ӽ����߲���ʹ��ͼ��û�и��.
����һ����ͨ������ͼ,�����ڸ�ͼ����Ӽ�����,��ʹ�ø�ͼ��ɱ�˫��ͨͼ.
������Ӽ����߲���ʹ��ͼ����������֮������������·��.
����ԭͼ��֤һ������ͨ��.
����:http://poj.org/problem?id=3352
˼·:�������tarjan���SCC������,��Ҫע����Ƕ����Ѿ��������ĵ�����ж�
�Ƿ���ջ��,�������ǵ�ǰ�ڵ��ǰ���ڵ�.���ֻҪ�ж�dfn[u] == low[u]���γ�ջ.
����EBC���������ÿ����Ķ�,ͳ�Ƴ���Ϊ1�ĵ�ĸ���ans,�����Ϊ(ans+1)/2.
���رߵ�����ͬ�����ò����رߵ�����,���鲻�ܺ������ر�,�������رߵ������Դ�.

����������һ�ִ�������,����һ������ͼ��tarjan���ÿ�����lowֵ,������,���������
��lowֵ��ͬ��������ͬһ��˫��ͨ������(EBC),�������EBC��ֻ��һ������û�����,���Ƕ���
������2������EBC,��Ϊlow[u]ֵ���лر�ʱ��¼����dfn[v]��ֵ(��ʹ��¼low[v],��Ϊdfs�������,
���v���low���ܻ���û�и���),������������lowֵ��һ��,������2�����ֿ�,������Ϊһ��EBC.
*/

int n,m,dfn[N],low[N],num,cnt,head[N],block[N],ebc_cnt,de[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}
//��Ϊ������ͼ,���ͼ��������ͨ��,��ôһ��dfs���ܷ��������ebc,������dfn�����С���ڷ���ebcʱ,
//����������ѷ������ebc�ĵ���ر�ʱ,��ôlowֵ����ͱ��ѷ����dfnС,Ҳ���������,�������û���ر�,
//��ô�͸��������ڷ��ʵ��ѷ����ebc�ĵ�.���Կ��Բ�����in�ж��Ƿ���ջ��.
//���ԭͼ����ͨ,��ôһ����ͨ����ebc������,�ڷ�����һ����ͨ������ebcҲ���������֮ǰ�Ѿ��ֳ�ebc�еĵ�.
//����dfs����dfn[v]!=0,�ǲ���Ҫ�ж�in[v]��ջ��,���Ƕ������رߵ�������߼��Ͼ��û���Ӧ�ü���in[v]���ж�
//(��Ȼ���ӽ��Ҳ�ǶԵ�,��Ϊlowֵ����ͱ��ѷ����ebc��dfnС),û���ر��ǿ�����ȫ���ӵ�
void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
        }
        else if(v!=fa)//������ǰ���ڵ�,��Ϊ�����ᵼ�� u-v�����ĵ���ͼ������һ��EBC,��ʵ�ʲ�����EBC,ʵ��u��v����һ��EBC
            low[u]=min(low[u],dfn[v]);//����low[u]=min(low[u],low[v])Ҳ�ǿ��Ե�
    }
    if(dfn[u] == low[u]){//dfn��low���ʱ,˵��û�лر߻ص�ʱ�������Ľڵ�,��ʼ��ջ ����һ��EBC
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
            block[v]=ebc_cnt;//���õ�ǰ��������ebc�ı��
        }while(v!=u);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    //������ʵ��֤��ԭͼ����ͨ�� ֱ��dfs(1,-1),��ʵ����������Ҳֻ����ԭͼ��ͨ�����
    //����ԭͼ����ͨ��������迼�Ƕ�Ϊ0�������ĵ�,ansҪ��2.
    dfs(1,-1);
    //��ԭͼ��ͨ�ұ������EBG��������� ������Ϊ����Ҳû�ж�Ϊ1�ĵ�.ԭͼ����ͨ����Ҫ���е� ��ΪҪ���Ƕ�Ϊ0�����
    for(int i=0;i<cnt;i+=2){//��Ϊ��˫���+2,���˵�ȶ�+1
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            de[block[u]]++;
            de[block[v]]++;
        }
    }
    for(int i=1;i<=ebc_cnt;i++){
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);//����ԭͼ���������,ֻ�����һ����λ��ӵı߼��ɳ�Ϊ��˫��ͨͼ.
    return 0;
}
/*
//ac tarjan�����+���鼯 32ms
//��Ϊԭ����ͼ�������������һ����2�����������ı�˫��ͨ����(ebc),
//���Կ��԰ѳ������ı��ϵĵ��ò��鼯�ϲ�Ϊһ������,��Щ�������ļ��Ͼ��Ǹ���ebc,
//�����ĵ�Ķȵļ��������֮ǰ�ĸ��������,ÿ��������˵�de[find(u)]�ȶ���+1
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;
int n,m,fa[N],dfn[N],low[N],num,cnt,cut_num,head[N],ebc_cnt,de[N];

struct Edge{
    int to,next;
    Edge(int to=0,int next=0):to(to),next(next){}
}edge[M<<1],cut_edge[M];

void addEdge(int from,int to){
    edge[cnt]=Edge(to,head[from]);
    head[from]=cnt++;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int u,int father){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])//��¼��� ��������������������ϵ�Ķ�
                cut_edge[++cut_num]=Edge(u,v);
            else
                fa[find(u)]=find(v);//����u��vδ�ϲ�֮ǰ��Ȼ�ǲ�ͬ����,��Ϊtarjan ����㶼��δ������.
        }
        else if(v!=father)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    for(int i=1;i<=cut_num;i++){
        u=cut_edge[i].to;
        v=cut_edge[i].next;
        de[find(u)]++;//����Ͳ����ǲ��鼯���Ƚڵ�ı��,û��ȥ���ebc�ĸ���,�����n����Ķȶ���һ��
        de[find(v)]++;
    }
    for(int i=1;i<=n;i++){//����ÿ���㶼��,��Ϊ��֪������ÿ��ebc�������ȸ��ڵ�ı��
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);
    return 0;
}
*/

/*
//ac tarjan�����+���鼯 32ms ���ｫ���鼯���Ƚڵ� �ٴ���pos[find(u)]=++ebc_cnt,���Լ���ebc����Ŀ,��ÿ��ebc���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;
//ac 32ms
int n,m,fa[N],dfn[N],low[N],num,cnt,cut_num,head[N],ebc_cnt,de[N],pos[N];

struct Edge{
    int to,next;
    Edge(int to=0,int next=0):to(to),next(next){}
}edge[M<<1],cut_edge[M];

void addEdge(int from,int to){
    edge[cnt]=Edge(to,head[from]);
    head[from]=cnt++;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int u,int father){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                cut_edge[++cut_num]=Edge(u,v);
            else
                fa[find(u)]=find(v);
        }
        else if(v!=father)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++){
        int x=find(i);
        if(!pos[x]) pos[x]=++ebc_cnt;
    }
    for(int i=1;i<=cut_num;i++){
        u=cut_edge[i].to;
        v=cut_edge[i].next;
        de[pos[find(u)]]++;
        de[pos[find(v)]]++;
    }
    for(int i=1;i<=ebc_cnt;i++){//ֻ�ж�ebc����Ŀ
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);
    return 0;
}
*/

