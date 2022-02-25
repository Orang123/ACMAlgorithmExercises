#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20100
#define M 100100
using namespace std;
//ac 114ms
/*
��ظ���:
���:���������ͼ����,û�е�����ͨ,ǿ��ͨ�ĸ���,����һ������ͼ,��
����һ����ɾ�������ͼ�ļ�����ͨ������������,��ô�����������ͼ�ĸ��(�ֳƸ).
��ͨ����:����ͼG�ļ�����ͨ��ͼ��ΪG����ͨ����(Connected Component).

�ر߲���Ӱ������������,��Ϊ��ʹ���ر�,���ֻҪɾ����������������б߶���Ͽ�,
�����ر߲�����Ӱ������ж�.Ҳ����Ӱ���˫��ͨ������.
*/

/*
����:����һ��n����,m���ߵ�����ͼ,��ͼ�ĸ��.
����:https://www.luogu.com.cn/problem/P3388
˼·:tarjan�������ͼ�еĸ��.
*/

struct node{
    int to,next;
}edge[M<<1];//����ͼ��˫��� ���M*2
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int root;//ÿ��dfsʱ�ĵ�һ����� ��:root���ڵ�
bool cut[N];//�ж��Ƿ���

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){//O(E) EΪ��
    dfn[u]=low[u]=++num;
    int v,son=0;//son������ڵ������ ֻ���ж�rootʱ��Ч
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){//����Ƿ�֧��β�ڵ�,������ڵ�϶����Ǹ��,Ҳ����������if
            dfs(v,u);
            if(u == root)//or fa == -1
                son++;//ÿ��root���ÿ����һ��δ���ʵĵ�ʱ ��������++,��Ϊ������ͼ,��Щ����ܻᱻ֮ǰ���������ʹ�
            low[u]=min(low[u],low[v]);//��v�ܻص��������Ľ����ôuҲ���Իص�
            /*
            ��u���Ǹ��ڵ�ʱ,ֻҪ����һ���ӽڵ����ܻص��Ĵ�����ڵ������ķ��ʱ��,
            ˵����ͨ��u���,v�޷��ص�u֮ǰ�Ľ��,˵��u�Ǹ��,
            ���ﵱdfn[u]<low[v]ʱ,vֻ�ܻص�u֮������Ľڵ�,��ôɾ��u��Ȼʹ��u v֮��Ľڵ���u�Ͽ�.
            ��dfn[u]==low[v]ʱ,���˵��v���ܻص�u��,��ôɾ��u��,Ҳ��Ȼʹ��u v֮��Ľڵ���u�Ͽ�.
            Ҳ����˵��v�ܻص�u,��ôu v ֮��Ľڵ�x�����Ǹ��,��Ϊlow[x]=dfn[u],����x�ĸ���dfn[fa]>low[x]
            ���������ж�u==root,����root���,��ֻ��һ������,Ҳ�������������,����ʱɾ�����ڵ�,
            ��Ϊֻ��һ������,root�ڵ������Ȼ����ͨ��.
            */
            if(u != root && dfn[u]<=low[v])//����ĳ��������֧ ���Ǹ��,���Ƕ���һ���������Ǹ��
                cut[u]=true;//����������ͳ�Ƹ�����Ŀ,��Ϊu����п��ܻ��� ��������ĸ��
            /*
            ��uΪ���ڵ�������2������ʱ,˵��֮ǰ�ȷ��ʵĵ�һ��������û�б������ڶ��������Ľڵ�,
            ����2����������root�����Ϊý�����ӵ�,ɾ�������Żᵼ��2����������ͨ.
            ���ﲻ�ܷ���for����,��Ϊɾ�����ڵ�����ڵ����������з�֧�����Ϊһ����ͨ����,
            ���Զ���ÿ����֧��Ҫ������++,���ֻ���жϸõ��Ƿ��Ǹ��,�ǿ��Է���forѭ�������.
            ����son==1,ֻ��һ����֧�ǲ���¼��,���ǵ�son>=2ʱ,����¼����ͨ����ʵ���ټ�¼��һ��,
            ����������н������+1.
            */
            else if(u == root && son>=2)
                cut[u]=true;
        }
        /*
        �������u�������ѱ������ĸ��׽ڵ�fa,��Ȼ�����˻�ѭ��,����ɾ�����׽ڵ�fa��,
        ��Ȼ��ʹ��u��fa����,���Զ���u������,��v�Ǹ��׽ڵ�,����Ҫ����low[u],����ʱ,
        dfn[u]<low[v]ֱ���ж�u���׽ڵ�Ϊ���ͺ�.��Ȼȥ��if(v!=fa),��Ϊif(!dfn[v])���ж���,
        low[u]=min(low[u],low[v]),low[v]<=dfn[v],���Ҳ�����.
        */
        else if(v!=fa)
        /*
        ���ﲻ����low[u]=min(low[u],low[v]),��Ϊ��low[u]Ϊlow[v]ʱ,
        low[v]�ǻ��dfn[v]С��,��ô�����ݵ�v��,�ж�v���Ǹ��ʱ,
        ����dfn[u]<=low[v],����ʱ,low[v]�ͻ��dfn[u]С,��Ϊ
        low[u]=min(low[u],dfn[v]),low[u]ȡ�˽�С��low[u],�����ж�ʱ,
        ����dfn[u]�жϵ�,��ʱdfn[u]�����Ǳ�low[v]С�ڵ��ڵ�,������Ϊ
        ��ʱlow[u]ȡ��low[v]�ᵼ��dfn[u]>low[v]�����.
        */
            low[u]=min(low[u],dfn[v]);
    }
}
/*
//��һ�����ɾ������ʣ����ͨ������д��
void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            dfs(v,u,k);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v])
                cut[u]++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(fa < 0) cut[u]--;
}
*/

int main(){
    int n,m,a,b;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&a,&b);
        addEdge(a,b);//��������ͼ,˫���,����������ͨ��
        addEdge(b,a);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){//ԭͼ��һ������ͨͼ,�����Ƿ�ɢ��,��˵ö�δ������ÿ�������dfs
            root=i;//���ڵ�Ϊ��һ�����ʵ�i���
            dfs(i,-1);//��һ�η���rootʱ �����ڸ��׽��ĸ��� ��Ϊ-1
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(cut[i])
            ans++;//ͳ�Ƹ��ĸ���
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        if(cut[i])
            printf("%d ",i);//������ı��
    printf("\n");
    return 0;
}
