#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 1000100
using namespace std;
//ac 0ms
//ע���ʼ�� id ����num���ʱ �����,���Ǹ���id�Ͳ�ȷ��,��������������ʼ��Ҳ��Ӧ�ô�
/*
����:����һ��n�������ͨ������ͼ,һ����ġ�����ֵ������Ϊ������ͼ��ɾȥ����ͨ��ĸ���.
�󡰸���ֵ�����������е�ǰm��.������ֵһ���򰴱����������.
����:https://www.luogu.com.cn/problem/UVA10765
˼·:tarjan��������
*/

int n,m,dfn[N],low[N],clock,cnt,head[N];
struct Cut{
    int id,num;
    bool operator < (const Cut &x)const{
        if(num == x.num) return id<x.id;
        else return num>x.num;
    }
}cut[N];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v])
                cut[u].num++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(fa == -1) cut[u].num--;//ע����ڵ�ɾ����ʵ����ͨ���� Ҫ����һ��
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        for(int i=0;i<n;i++){
            cut[i].id=i;//ע������ ���е�idһ��Ҫ��ʼ��,����num�п�����ͬʱ,���Ǹ���idû�г�ʼ��,�����������Ǵ����
            cut[i].num=1;
        }
        while(scanf("%d%d",&u,&v) && (u!=-1||v!=-1)){
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        sort(cut,cut+n);
        for(int i=0;i<m;i++)
            printf("%d %d\n",cut[i].id,cut[i].num);
        printf("\n");
    }
    return 0;
}
