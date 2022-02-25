/*
����:����һ��n����������ͼ�Լ�ĳ�����k�������ֵ����С����˳�����
�ӽ��1�����k������·����Ҫ���㲻���ظ�������
��ĸ���<=25.
����:https://www.luogu.com.cn/problem/UVA208
˼·:dfs�����ֵ�������1����k�ڵ������·��,ֻ�Ƕ��ڱ���1���ɴ�k
�������Ҫ��bfs�򲢲鼯����ʱ���ж�,���ֱ����dfs�ж�1��k�����
��Ҫ��������ͼ�����е��,���л��ظ������ܶ����ͬ���,���ӶȾ�̫��.
*/
//ac 0ms dfs+���鼯�ж��Ƿ�ɴ�
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 25
using namespace std;

int n,k,fa[N],vis[N],path[N],cnt;
vector<int> G[N];

int find(int x){
    return fa[x] == x?x:fa[x]=find(fa[x]);
}

void dfs(int u){
    if(u == k){
        cnt++;
        int x=1;
        printf("1");
        while(x!=k){
            printf(" %d",path[x]);
            x=path[x];
        }
        printf("\n");
        return;
    }
    for(int &v : G[u]){
        if(!vis[v]){
            vis[v]=1;
            path[u]=v;
            dfs(v);
            vis[v]=0;
        }
    }
}

int main(){
    int cas=0,u,v;
    while(scanf("%d",&k)!=EOF){
        cas++;
        cnt=0;
        for(int i=1;i<N;i++){
            G[i].clear();
            fa[i]=i;
            vis[i]=0;
        }
        n=0;
        while(scanf("%d%d",&u,&v) && u+v){
            G[u].push_back(v);
            G[v].push_back(u);
            fa[find(u)]=find(v);
            n=max(n,max(u,v));
        }
        for(int i=1;i<=n;i++)
            sort(G[i].begin(),G[i].end());
        printf("CASE %d:\n",cas);
        if(find(1) != find(k)){
            printf("There are 0 routes from the firestation to streetcorner %d.\n",k);
            continue;
        }
        vis[1]=1;
        dfs(1);
        vis[1]=0;
        printf("There are %d routes from the firestation to streetcorner %d.\n",cnt,k);
    }
    return 0;
}

/*
//ac 0ms dfs+bfs���Ƿ�ɴ�
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#define N 25
using namespace std;

int n,k,vis[N],path[N],cnt;
vector<int> G[N];

int bfs(){
	queue<int> Q;
	vis[1]=1;
	Q.push(1);
	int u;
	while(!Q.empty()){
		u=Q.front();
		Q.pop();
		if(u == k)
			return 1;
		for(int &v : G[u]){
			if(!vis[v]){
				vis[v]=1;
				Q.push(v);
			}
		}
	}
	return 0;
}

void dfs(int u){
    if(u == k){
        cnt++;
        int x=1;
        printf("1");
        while(x!=k){
            printf(" %d",path[x]);
            x=path[x];
        }
        printf("\n");
        return;
    }
    for(int &v : G[u]){
        if(!vis[v]){
            vis[v]=1;
            path[u]=v;
            dfs(v);
            vis[v]=0;
        }
    }
}

int main(){
    int cas=0,u,v;
    while(scanf("%d",&k)!=EOF){
        cas++;
        cnt=0;
        for(int i=1;i<N;i++){
            G[i].clear();
            vis[i]=0;
        }
        n=0;
        while(scanf("%d%d",&u,&v) && u+v){
            G[u].push_back(v);
            G[v].push_back(u);
            n=max(n,max(u,v));
        }
        for(int i=1;i<=n;i++)
            sort(G[i].begin(),G[i].end());
        printf("CASE %d:\n",cas);
        if(!bfs()){
            printf("There are 0 routes from the firestation to streetcorner %d.\n",k);
            continue;
        }
        memset(vis,0,sizeof(vis));
        vis[1]=1;
        dfs(1);
        vis[1]=0;
        printf("There are %d routes from the firestation to streetcorner %d.\n",cnt,k);
    }
    return 0;
}
*/
