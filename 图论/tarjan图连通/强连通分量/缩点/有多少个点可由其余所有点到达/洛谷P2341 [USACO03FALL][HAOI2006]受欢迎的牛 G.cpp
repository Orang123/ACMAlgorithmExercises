#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 10100
#define M 50100
using namespace std;
//ac 133ms
/*
����:ÿͷ��ţ�������Ϊţ���������.��������ţϲ������ţ����һͷ������ţ.
������ţ����������,ÿͷ��ţ����ϲ���Լ���.��ţ֮��ġ�ϲ�����ǿ��Դ��ݵġ���
���Aϲ��B,Bϲ��C,��ôAҲϲ��C.ţ���ﹲ��Nͷ��ţ,
����һЩ��ţ֮��İ�Ľ��ϵ,��������ж���ͷ��ţ���Ե�����.
����:https://www.luogu.com.cn/problem/P2341
˼·:������tarjan���SCC,֮���ٽ�SCC����,��ԭͼת����һ��DAG(�����޻�ͼ),
��������ͼ�еĹ�ϵ����ü������,��ʵ��,�۲췢��DAG�г���Ϊ0�ĵ�(SCC),���
ֻ��һ��,��ô���SCC�еĵ�ͱ��������е�ϲ������,��SCC�е�ĸ�����Ϊ��.
������Ϊ0�ĵ��������1,��������������֮����û�д��ݹ�ϵ��,��ôҲ�Ͳ�����
"������ţ"����������ţ��ϲ��.
*/

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
stack<int> s;
bool in[N];
int block[N],id,SSG[N],de[N];

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
            SSG[id]++;
            s.pop();
        }while(v != u);
    }
}
int main(){
    int n,m,a,b;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d %d",&a,&b);
        addEdge(a,b);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    int deNum=0;
    for(int i=1;i<=n;i++){
        for(int j=head[i];j!=-1;j=edge[j].next){
            if(block[i]!=block[edge[j].to]){//��������Ӧ��ǿ��ͨ������Ų�ͬ,�����Ϊ����������֮��������
                de[block[i]]++;//ͳ��i�ĳ��� ++  ���ﲻ��Ҫ���������½�ͼ
            }
        }
    }
    int ans;
    for(int i=1;i<=id;i++){
        if(!de[i]){
            deNum++;//ͳ�Ƴ���Ϊ0����������
            ans=i;//��¼id
        }
    }
    /*
    ͬһǿ��ͨ�����е�����ţ֮�䶼���໥ϲ����,���ֻҪǿ��ͨ�������ɵĵ�
    ֱ����������� ��������u->v ����u�е�����ţ������ͨv�����е�ţ,
    ����ݴ�����u������ţ��ϲ��v��ţ.
    */
    //������Ϊ0�ĵ����ҽ���1��,����������Ӧ��ǿ��ͨ�����Ľڵ������Ϊ��
    //����������һ��������Ϊ0,������ԭͼ����ǿ��ͨͼֱ�ӿ�������һ����
    if(deNum == 1) printf("%d\n",SSG[ans]);
    //������һ�� ��Ȼ������Щ����Ϊ0��������� ���ǵ�ţ֮���໥��û�й���,
    //�໥��ϲ����,��Ȼ�޷���������ţ��ϲ��������ţ��˵��
    else printf("0\n");
    printf("\n");
    return 0;
}
