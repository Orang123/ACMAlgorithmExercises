#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
using namespace std;
//ac 47ms
/*
����:nͷţ,m����ϵ,���A��ΪB�ܻ�ӭ,B��ΪC�ܻ�ӭ,
��ôţAҲ��ΪţC�ܻ�ӭ,��:A->B->C,����Ҫ����ж���ͷţ������ţ�Ͽ�.
����:����������ͼ��,�ж��ٸ�������������е㵽�������.
����:http://poj.org/problem?id=2186
˼·:N<=10111,�����ⷨ,���Ǵ�ÿ���㿪ʼ�������е�,����ж�ÿ���㱻����Ĵ���,
����ﵽn-1,˵���õ��ܴ��������е㵽��,��O(N^2),��ȻTLE.�������floyd�����ݱհ�,
O(N^3)ʱ�临�Ӷ�,O(N^2)�ռ临�Ӷ�,TLE,MLE.
���Կ���tarjan���ǿ��ͨ����(SCC)������ת���������޻�ͼ(DAG).
����:��DAG��������ҽ���һ����ĳ���Ϊ0ʱ,���������е㶼�ɴ�õ�(���Ի�ͼ���).
��ô�����ͳ��SCC�ĳ���,�������Ϊ0�ĵ�ǡ��һ��,�������SCC�е�ĸ���,������Ϊ
����Ϊ0�ĵ����1,���Ȼ������һ���㲻�ɴ�õ�,��˵��û��һ����ɴ������㵽��õ�.
*/

int n,m,dfn[N],low[N],in[N],num,cnt,head[N],id,block[N],outde[N],amout[N];
stack<int> s;
struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
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
            s.pop();
            in[v]=0;
            amout[id]++;
            block[v]=id;
        }while(v!=u);
    }
}

int main(){
    int u,v,ans=0;
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u] != block[v])
            outde[block[u]]++;//ͳ�Ƴ���
    }
    int k;
    for(int i=1;i<=id;i++){
        if(!outde[i]){
            ans++;//��¼����Ϊ0�ĵ�ĸ���
            k=i;
        }
    }
    if(ans == 1) printf("%d",amout[k]);
    else printf("0");
    return 0;
}
