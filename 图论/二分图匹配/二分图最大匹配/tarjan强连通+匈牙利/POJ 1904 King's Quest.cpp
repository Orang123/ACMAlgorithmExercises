#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 4100
#define M 4000100
using namespace std;
//ac 9844ms ����ͼ����+tarjan���scc
//HDU 4685��POJ 1904 ��ǿ�� û������ʼ����ƥ��,��Ҫ���������������ƥ��
/*
����:һ��������n������,���ڶ�Ӧ��n��Ů��,������ҪΪ
n�����Ӷ��ҵ�һλϲ����Ů��,ÿ�����Ӷ���һЩ�Լ�ϲ��
��Ů��,������ʦ���ݸ�������ϲ�������,Ϊÿ��������ѡ��
һ��Ů��,��:һ������ƥ��,��������������,������֪������
ÿ�����Ӷ�����ѡȡ��ЩŮ����Ϊ��ż,��������ʹ����������
ϲ����Ů������ѡȡ�������������û��ϲ����Ů����ѡ�����.
���ÿ�����ӿ���ѡȡŮ���ĸ���,����ЩŮ���ı��(����).
ע��:��������һ����֤��������ƥ��.
����:http://poj.org/problem?id=1904
˼·:��Ȼ���Ӻ�Ů����Ϊ����2���Ϲ��ɶ���ͼ,�����������ǿ϶���
��֤��������ƥ���,�����������ò����������㷨������ƥ��,
����ÿ������i��ϲ����Ů��j,��i->(j+n)�ĵ����,��������ʦ����
������ƥ��,����i��Ů��j,��(j+n)->i�ĵ����.֮��tarjan���scc.
����ժ������.
����ÿ�����Ӻ�Ů��,������Ƕ���ͬһ��ǿ��ͨ������,�����ǿ��Խ��.
��Ϊÿ������ֻ�ܺ�ϲ����Ů�����,��ʼ����ƥ���е��ɷ������֮����
��������ͬ�ı߿��Ի���,��ͬһ��ǿ��ͨ�����еĶ�������Ů����һ��
����ȵ�,������x���Ժ������һ��Ů��a���,Ů��a��ԭ�����y�϶���
�ҵ�����һ��Ů��b���,��Ϊ����Ҳ����Ļ�,��x��a�ز���ͬһ��ǿ��ͨ������.
����һ�������ӿ��Ժ���������ͬһǿ��ͨ������Ů�����,���ⲻ�ᵼ��ͬһ
ǿ��ͨ�����е����������Ҳ���Ů�����.
*/
/*
����õ��㷨��ȷ�����������,����������hack
input
3
2 1 2
3 1 2 3
2 2 3
1 2 3
output
2 1 2
3 1 2 3
2 2 3
�����һ������ѡ��2��Ů��,�ڶ�������ѡ��3��Ů��,���������� ����û��ѡ����
*/
int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id;
stack<int> s;
vector<int> seq;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

void init(){
    clock=id=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
    memset(block,0,sizeof(block));
}

int main(){
    int v;
    init();
    scanf("%d",&n);//n������
    for(int i=1;i<=n;i++){
        scanf("%d",&m);//����i ϲ��m��Ů��
        while(m--){
            scanf("%d",&v);
            addEdge(i,v+n);//�к���Ů������
        }
    }
    for(int i=1;i<=n;i++){//��ʦ�����ĳ�ʼ����ƥ��
        scanf("%d",&v);
        addEdge(v+n,i);//Ů�������ӽ���
    }
    for(int i=1;i<=2*n;i++){//���Ӻ�Ů���ܹ�2n�� ��ʵ��i<=nҲ���Թ�,��Ϊÿ�����ӷ����ı����ٶ��ܸ��ǵ�һ��scc
        if(!dfn[i])
            dfs(i);
    }
    for(int u=1;u<=n;u++){
        seq.clear();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(block[u] == block[v])//����u��Ů��v��ͬһscc,����Խ�鲻Ӱ����������ѡȡ��ż
                seq.push_back(v-n);//Ů��ʵ�ʱ�ż�n
        }
        sort(seq.begin(),seq.end());
        printf("%d",seq.size());
        for(int i=0;i<seq.size();i++)
            printf(" %d",seq[i]);
        printf("\n");
    }
    return 0;
}
