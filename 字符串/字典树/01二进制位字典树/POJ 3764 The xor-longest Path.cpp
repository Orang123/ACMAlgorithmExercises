/*
����:ժ������
n��������������������·��Ȩֵw�������ֵ��
n<=100000.w<2^31.
����:http://poj.org/problem?id=3764
˼·:dfsԤ�������0���������ÿ��������ֵdp[v],
����������(u,v)�ļ�·�������ֵΪdp[u]^dp[v],������
�����е�����ֵ����01�ֵ���,֮��ö��ÿ��������ֵ
��01�ֵ������Һ������ֵ���ĵ�,�����������ֵ.
*/

//ac 704ms
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 3200010
#define M 100010
using namespace std;

int n,tr[N][2],cnt,dp[M],ans;

int head[M],num;
struct Edge{
	int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
	edge[num]=(Edge){to,head[from],w};
	head[from]=num++;
}

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(int val){
    int son,rt=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;//val ��iλΪson(0��1)
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

int findWord(int val){
    int son,rt=0,res=0;
    for(int i=30;i>=0;i--){//���31λ,int�Ϳ��Դ洢
        son=val>>i & 1;
        if(tr[rt][son^1]){//������ں���sonֵ��ͬ��,���iλ����Ϊ1
            res|=1<<i;//��¼·��������ֵ
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

void dfs(int u,int fa){
    insertWord(dp[u]);
    int v,w;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        w=edge[i].w;
        if(v == fa)
            continue;
        dp[v]=dp[u]^w;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        ans=0;
        cnt=-1;
        newNode();
        memset(head,-1,sizeof(head));
        num=0;
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        dfs(0,-1);
        for(int i=0;i<n;i++)
            ans=max(ans,findWord(dp[i]));
        printf("%d\n",ans);
    }
    return 0;
}

/*
//TLE stl vector��ͼ ����ʱ�䳬ʱ
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 3200010
#define M 100010
using namespace std;

int n,tr[N][2],cnt,dp[M],ans;
vector<pair<int,int> > G[M];

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(int val){
    int son,rt=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;//val ��iλΪson(0��1)
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

int findWord(int val){
    int son,rt=0,res=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]){
            res|=1<<i;
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

void dfs(int u,int fa){
    insertWord(dp[u]);
    int v,w;
    for(int i=0;i<G[u].size();i++){
        v=G[u][i].first;
        w=G[u][i].second;
        if(v == fa)
            continue;
        dp[v]=dp[u]^w;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        ans=0;
        cnt=-1;
        newNode();
        for(int i=0;i<n;i++)
            G[i].clear();
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            G[u].push_back(make_pair(v,w));
            G[v].push_back(make_pair(u,w));
        }
        dfs(0,-1);
        for(int i=0;i<n;i++)
            ans=max(ans,findWord(dp[i]));
        printf("%d\n",ans);
    }
    return 0;
}
*/
