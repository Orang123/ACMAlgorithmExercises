#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 100100
#define M 300010
#define INF 0x3f3f3f3f
#define Mod 1000000007
using namespace std;
//ac 135ms tarjan���scc����+�˷�ԭ��
/*
����:������n����ӰԺ,n�����·ֱ���ÿ����ӰԺ��,Ȼ���ӰԺ�ﶼ������,
����Ҫʹ������Ҫһ���ķ���.m������ͨ���������ڵ������������ڵ�ӰԺ.
HXY �и�����,������ܴ�һ���㿪ʼ��,���ص������,
��ô��������·�ϵ����µķ���ֻ��Ҫ�õ�����ͷѼ���.
����ÿ������ֻ����һ��,��ӰԺ�����ظ�ȥ.Ȼ�����뻨�������ٵķ����յ����е�����.
�������յ������������ٻ����Ƕ���,�Լ����ж��ٷ���.
����:https://www.luogu.com.cn/problem/P2194
˼·:���ڻ��еĵ�ֻ���ջ������ٵ�һ���㼴��,���������ճ˷�ԭ��,��ÿ��scc
�����ٻ��ѵĵ��м���,�����۳˼��Ǵ�.tarjan���scc����+�˷�ԭ��
*/

int n,m,head[N],cnt,sum,ans;
int id,dfn[N],low[N],clock,block[N],val[N],minval[N],num[N];
stack<int> s;

struct Edge{
    int to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            if(minval[id]>val[v]){
                num[id]=1;
                minval[id]=val[v];
            }
            else if(minval[id] == val[v])//��С�������ʱ
                num[id]++;//��С���ѵĸ���++
        }while(v!=u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    memset(minval,0x3f,sizeof(minval));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    ans=1;
    for(int i=1;i<=id;i++){
        sum+=minval[i];
        ans*=num[i]%Mod;//Ҫ�Խ��ȡģ
    }
    printf("%d %d",sum,ans);
    return 0;
}
