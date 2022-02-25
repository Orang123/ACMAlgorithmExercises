#include<cstdio>
#include<cstring>
#include<vector>
#define N 350
using namespace std;
//ac 16ms
/*
����:n�ſγ�,һ��7��,ÿ����Կ���12�ſ�,�������
���ſγ̵��ŷ�ʱ��ʹ�ò�ͬ�γ̼�ʱ�䲻��ͻ,ͬʱ����
������һ����ѡ�Ŀγ������.
����:http://poj.org/problem?id=2239
˼·:���Խ�n�ſγ���Ϊ�󼯺�,�γ̵İ���ʱ�������Ϊ
�Ҽ���,ÿ�ſγ̿ɿ��ŵ�ʱ��Ͷ�Ӧ��ʱ���������,Ҫʹ��
�γ̰���û�г�ͻ,��Ȼ���߲����й�����,����Ҫʹ������ѡ��
�γ������,����������ƥ��.
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
    int a,b;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){//�γ�i
            scanf("%d",&m);//�γ�i�ɰ�����m��ʱ�����
            while(m--){
                scanf("%d%d",&a,&b);//a-����,b-�����ڵڼ��ſ�
                G[i].push_back((a-1)*12+b);//һ��ɿ���12�ſ�,���Կγ̱�ž�Ϊ(a-1)*12+b
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
