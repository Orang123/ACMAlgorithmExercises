/*
����:������ͼ�������������ظ����߲������ظ�
����:https://www.luogu.com.cn/problem/UVA539
˼·:dfsö��ÿ����,���Ե���ĵ�,��¼�·��.
ע���ǶԱ������,���Ե������,��Ϊ������ظ���.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
using namespace std;

int n,m,mp[N][N],ans;

void dfs(int u,int s){
    if(s>ans)
        ans=s;
    for(int i=0;i<n;i++){
        if(mp[u][i]){
            mp[u][i]=mp[i][u]=0;
            dfs(i,s+1);
            mp[u][i]=mp[i][u]=1;
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=0;
        memset(mp,0,sizeof(mp));
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=mp[v][u]=1;
        }
        for(int i=0;i<n;i++)
            dfs(i,0);
        printf("%d\n",ans);
    }
    return 0;
}
