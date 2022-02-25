#include<cstdio>
#include<cstring>
#include<vector>
#define N 250
using namespace std;
//ac 16ms
/*
����:n����ţ,m��ţ��,ÿ����ţֻԸ�����ض���ţ������,
����һ��ţ��ֻ�ܷ����һͷ��ţ,һͷ��ţҲֻ�ܷ����һ��ţ��.
�������ж�����ţ����ţ������.
����:http://poj.org/problem?id=1274
˼·:����ͼ���ƥ��.��ţΪ�󼯺�,ţ��Ϊ�Ҽ���.
*/
int n,m,vis[N],match[N],ans;
vector<int> G[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int a,t;
    while(scanf("%d%d",&n,&m)!=EOF){//mʵ��û��
        init();
        for(int i=1;i<=n;i++){//i��ţ���
            scanf("%d",&t);//ÿͷ��ţ��t��Ը����̵�ţ��
            while(t--){
                scanf("%d",&a);//ţ��a
                G[i].push_back(a);//��ţiԸ����ţ��a����
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
