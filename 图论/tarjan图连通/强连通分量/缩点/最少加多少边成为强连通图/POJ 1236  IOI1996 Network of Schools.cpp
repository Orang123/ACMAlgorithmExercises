#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 150
using namespace std;

/*
����:һ������ͼ,��:
1)����Ҫѡ��������,������������Щ�������,���Ե���ȫ������.
2)����Ҫ�Ӷ�������,����ʹ�ô��κ�һ���������,���ܵ���ȫ������,����Ϊһ��ǿ��ͨͼ.
����:http://poj.org/problem?id=1236
˼·:��һ�ʾ���tarjan�����,���Ϊ0�ĵ�ĸ���,
�ڶ��������Ϊ0�ĸ���incnt�ͳ���Ϊ0�ĸ���outcnt�����ֵ.
ҪΪÿ�����Ϊ0�ĵ�������,Ϊÿ������Ϊ0�ĵ���ӳ���,
�������Ϊ0�ĵ�ʱ,��ͬʱ����Ϊ0�ĵ�,���ϴ�����Ȼ����ʣ���ʱͼ�Ծɲ���ͨ,
���ȡ���ȡ�������ֵ����,�����ͼֱ��������.
һ��SCG(ǿ��ͨͼ)�е����е�ĳ���ȶ��ǲ�Ϊ0��,���ʹ��DAG��ΪSCG��Ҫ�ӱߵ�
��С������Ϊ���Ⱥ����Ϊ0�ĵ�����ֵ.
*/

struct node{
    int to,next;
}edge[N*(N-1)];

int head[N],cnt;
int dfn[N];
int low[N];
int num;
stack<int> s;
bool in[N];
int block[N],id,inde[N],outde[N];

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=true;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++id;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            s.pop();
        }while(v != u);
    }
}

int main(){
    int n,a[N];
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=0;;j++){
            scanf("%d",&a[j]);
            if(a[j] == 0) break;//����Ϊ0 i����ı߽���.
            addEdge(i,a[j]);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    for(int i=1;i<=n;i++){//����������ͳ��SCC ����ĳ��ȡ����
        for(int j=head[i];j!=-1;j=edge[j].next){
            if(block[i]!=block[edge[j].to]){//��������Ӧ��ǿ��ͨ������Ų�ͬ,�����Ϊ����������֮��������
                inde[block[edge[j].to]]++;//ͳ�����
                outde[block[i]]++;//ͳ��i�ĳ��� ++  ���ﲻ��Ҫ���������½�ͼ
            }
        }
    }
    int incnt=0,outcnt=0;
    for(int i=1;i<=id;i++){
        if(!inde[i]) incnt++;//ͳ������� ���Ϊ0�ͳ���Ϊ0�ĵ�ĸ���
        if(!outde[i]) outcnt++;
    }
    if(id == 1){//���ﲻ���ж�incnt == 1 && outcnt == 1 ��Ϊ����o->o���� ������SCC,�������Ϊ0�ͳ���Ϊ0�ĵ�Ҳ������1��
        printf("1\n");//ֻ��һ��SCC��ʱ�� ������ӱ�,�������SCS
        printf("0\n");
    }
    else{
        printf("%d\n",incnt);
        printf("%d\n",max(incnt,outcnt));
    }
    return 0;
}
