#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20100
#define M 100100
using namespace std;
/*
��ظ���:
���:����һ������ͼ,���ɾ��һ���ߺ�ͼ�е���ͨ������������,���������Ϊ�Ż��߸��.
���ر�:ֻҪ����dfn[u]<low[v],���Ǹ��.
���ر�:����������������,�Լ���ö����ж���������ʱ,���Ǹ��,��Ϊɾ��һ���߻��б�������,��ͨ�Բ���.
�������۵ĸ�߶��������رߵ�����ͼ��.�������رߵ������Ҫһ����¼���������Ķ�ά�������ж�.

�����ߵĹ�ϵ:
1.�и�㲻һ��������,����һ�����ڸ��.����һ�����ڸ���е����⵱ֻ��2����һ��������ʱ,���ŵ�û�и��.
2.�����ŵ����˵�,���ٴ���һ�����.
*/
struct node{
    int to,next;
    bool cut;
}edge[M<<1];//����ͼ��˫��� ���M*2
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int cutCnt;

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}
//O(E) EΪ�� ���㷨�ǽ��������رߵ�������
void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            /*
            ȥ���Ⱥ� ��Ϊ��dfn[u]>=low[v]ʱ,����v������u-v������Ҳ�ܻص�u��u֮ǰ���,
            ˵��u-v���Ǹ��(��),��֮dfn[u]<low[v],˵��v������u-v������ֻ����ͨ
            v��v���֮��Ľ��,�޷���ͨu��u֮ǰ�Ľ��,˵��u-v�Ǹ��.
            dfn[u]>low[v]ʱ,u���ǻ�·�����ӵ�ǰ��ĵ�,����֮��ĵ�.
            dfn[u]==low[v]ʱ,u������ǻ�·�����ӵ�ǰ��ĵ�.
            �������u���ܻص�����Ҳû������һ���ص����׵�·����ôu-v�����߾��Ǹ��.
            */
            if(dfn[u]<low[v]){//�������رߵ���������ж�edgeNum[u][v] == 1
                edge[i].cut=true;//��u-v v-u�߶���Ϊ���
                edge[i^1].cut=true;
                cutCnt++;//������ͼ�еĸ�߼�1 ���㷴���
            }
        }
        //u��u�ĸ��׽ڵ�v֮������߿϶��Ǹ��,��Ϊû���ر�,ɾ��������u��vһ������ͨ.�������low[u],ֱ��Ĭ��dfn[v]<low[u]
        else if(v!=fa)//������ڸ��׽ڵ����if�ж��ǲ���ʡ�Ե�
            /*
            ����Ҳ������low[u]=min(low[u],low[v]),��Ϊ�ж�������dfn[u]<low[v],
            ������ʹ��low[u]��С,��Ӱ����,dfn[u]>=low[v]��������ǲ����ڸ�ߵ�.
            ����dfn[u]==low[v]��Ȼ���Ǹ��,��Ϊ��ʹ�Ͽ�u-v�����߻��Ǵ���v�ĺ�������
            �лص�u�������.
            ��Ϊ���ɻ������Ƚڵ����ֱ����������һ���ڵ�ı߱���Ͳ��Ǹ��
            */
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int n,m,a,b;
    int len=M<<1;
    for(int i=0;i<len;i++)
        edge[i].cut=false;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&a,&b);
        addEdge(a,b);
        addEdge(b,a);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            dfs(i,-1);
        }
    }
    printf("%d\n",cutCnt);
    for(int i=1;i<=n;i++){
        for(int j=head[i];j!=-1;j=edge[j].next)
            if(edge[j].cut)//���Ǹ��������������˵� ��Ϊ������ͼ��Ե��,ʵ�������������cutCnt��2��
                printf("%d %d\n",i,edge[j].to);
    }
    printf("\n");
    return 0;
}
/*
7 9
2 3
3 6
6 2
6 7
3 1
1 4
4 5
5 4
5 1
*/
