#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2100
#define M 4000100
using namespace std;
//ac 1344ms
/*
����:ԭͼΪ���ͼ,���������,Ҳ�������,
����Ҫ������߸�Ϊ�����,ʹ������ͼ����������֮���Ծ�
��ͨ�໥�ɴ�,����Ҫ���ÿ������߸��ĺ�ķ�����,
�����Ծ���˫��������˵��2,�����ǵ�����������ߵ�
���˵�(������ʵ�ʵķ���)��1.
����:http://poj.org/problem?id=1438
˼·:��Ϊ�ǻ��ͼ,����ԭͼ��һ����ͨ,��������ķ�,
ʵ�ʶ����ſ��ܲ�һ�����������,�п��������Ҳ����Ϊ��,
����ֻ�轫ͼ����Ϊ�������㶼������ͨ�ɴ������ͼ����.
����Ϊ�˱���˫�������ķ���,���Խ�����ߺ�����߶���2��,�����������
����һ��Ҫ�������Ϊ���,ʵ��tarjan������������.
��ʵ��Ϊ��ʹ���������ͨ,����ߵ���Ŀ��ʵ���Ը���,
�����������������ǰ����ŵ���Ŀ��ȷ����,��������߻��һЩ.
��������Ĵ�Ҳ���Ǿ������ŵ�.
*/
int n,m,dfn[N],low[N],clock,cnt,head[N];

struct Edge{
    int from,to,next,flag,sta;
}edge[M];

void addEdge(int from,int to,int flag){
    edge[cnt]=(Edge){from,to,head[from],flag,-1};//sta���-1���������ߵķ���δ��ȷ��
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //�������߲������� ����״̬��Ϊ-1˵������ߵķ���֮ǰ�Ѿ�ȷ����
        if(!edge[i].flag || edge[i].sta!=-1) continue;
        edge[i].sta=1;//��ǵ�ǰ��ʽΪҪ����������߷���
        edge[i^1].sta=0;//��������Բ���Ҫ ʵ���������߿��������
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            //������Ҫ��֤��˫����,��ʵ�������п����Ǳ��������ڵ�����ߵ����,����Ҫ����ȡ����ԭͼ�Ļر��������
            //���ԭ����Ҫ�� �ŵ�����Ҫ�޶�������ͼ��,�������ԭͼ�������ܱ�֤�����ɴ�,���������һ���������˫���
            //������벻�ܱ�֤�����ɴ�,��������п��ܻ��������.
            //��ʵ��Ϊ��ʹ���������ͨ,����ߵ���Ŀ��ʵ���Ը���,�����������������ǰ����ŵ���Ŀ��ȷ����,��������߻��һЩ.
            if(dfn[u]<low[v])
                edge[i^1].sta=1;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v,flag;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&flag);
            if(flag == 1){
                addEdge(u,v,1);
                addEdge(v,u,0);//������� ʵ�ʲ�������,ֻ��Ϊ�˱���ʱ+2�����,�ж�˫��ߵķ���
            }
            if(flag == 2){
                addEdge(u,v,2);
                addEdge(v,u,2);
            }
        }
        for(int i=1;i<=n;i++){//ԭͼ���ͼ ���ܲ�����ͨ
            if(!dfn[i])
                dfs(i,-1);
        }
        for(int i=0;i<cnt;i+=2){
            if(edge[i].flag){
                if(edge[i].flag == 2 && edge[i].sta && edge[i^1].sta)//�ñ�Ϊ�����
                    printf("%d %d 2\n",edge[i].from,edge[i].to);
                else if(edge[i].flag == 2 && edge[i].sta && !edge[i^1].sta)//ֻ�豣��edge[i]
                    printf("%d %d 1\n",edge[i].from,edge[i].to);
                else if(edge[i].flag == 2 && edge[i^1].sta && !edge[i].sta)//ֻ�豣��edge[i^1]
                    printf("%d %d 1\n",edge[i^1].from,edge[i^1].to);
            }
        }
    }
    return 0;
}

/*
//��������
input
5 5
1 3 2
1 2 2
2 5 2
4 5 1
3 4 2

output
1 3 2
1 2 2
2 5 2
3 4 1

��ʵ�ʿ��ܲ�����Ҫ�����
���ŵĽ��
output
1 3 1
2 1 1
5 2 1
3 4 1

input
4 4
1 2 2
2 3 1
3 4 2
4 2 1

output
1 2 2
3 4 1
*/
