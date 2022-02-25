#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 5010
#define M 50050
using namespace std;
//ac 37ms
/*
����:����ͼ��,�߷ֵ���(����1)��˫��(����0),���нڵ�������ǿ��ͨ����,
������ǿ��ͨ�����ڵ�����ͬ,���ֵ������.
����:https://www.luogu.com.cn/problem/P1726
˼·:tarjan,ǿ��ͨ���������ʱ,ͳ��ÿ��ǿ��ͨ�����Ľڵ����,��¼������
��ǿ��ͨ�������,����յ���ֵ�������Ƿ��������ŵ�ǿ��ͨ������,���,
��Ϊdfsʱ������Ǵӱ�ſ�ǰ�ĵ㿪ʼ��,����SCC���Խ��ǰ��,���ĵ�һ����ı�ž�ԽС.
*/

struct node{
    int to,next;
}edge[M];
struct arr{
    int val,s[N];
}arr0[N];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
stack<int> s;
bool in[N];
int id,block[N],amot[N];

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
        id++;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            amot[id]++;
            s.pop();
        }while(v != u);
    }
}
int main(){
    int n,m,a,b,t,ans=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d %d %d",&a,&b,&t);
        if(t == 1) addEdge(a,b);
        else{
            addEdge(a,b);
            addEdge(b,a);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    //��¼scc��������
    for(int i=1;i<=id;i++){
        if(amot[i]>ans)
            ans=amot[i];
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){//�����ж�ÿ��������scc�ĸ����Ƿ�ﵽ���ֵ,���
        if(amot[block[i]] == ans)
            printf("%d ",i);
    }
    printf("\n");
    return 0;
}

/*
//˼·:tarjan,��ջʱ��¼�������,��ǿ��ͨ����������ͬʱ,���ո����Ӵ�С��,
//������ͬʱ,���յ�һ����ı�Ŵ�С������,��Ϊ����ǿ��ͨ�����ĵ�϶���û��
//�ظ���,�Ǹ���һ����.
#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 5010
#define M 50050
using namespace std;


struct node{
    int to,next;
}edge[M<<1];
struct arr{
    int val,s[N];
    bool operator < (const arr &x)const{
        if(val == x.val) return s[1]<x.s[1];
        else return val>x.val;
    }
}arr0[N];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
stack<int> s;
bool in[N];
int id;

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
        arr0[++id].val=0;
        do{
            v=s.top();
            in[v]=false;
            arr0[id].val++;
            arr0[id].s[arr0[id].val]=v;
            s.pop();
        }while(v != u);
        sort(arr0[id].s+1,arr0[id].s+1+arr0[id].val);//ÿ��ǿ��ͨ�������ֵ���Ҫ�ڼ�¼����������ź�
    }
}
int main(){
    int n,m,a,b,t;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d %d %d",&a,&b,&t);
        if(t == 1) addEdge(a,b);
        else{
            addEdge(a,b);
            addEdge(b,a);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    sort(arr0+1,arr0+1+id);
    printf("%d\n",arr0[1].val);
    for(int i=1;i<=arr0[1].val;i++)
        printf("%d ",arr0[1].s[i]);
    printf("\n");
    return 0;
}
*/
