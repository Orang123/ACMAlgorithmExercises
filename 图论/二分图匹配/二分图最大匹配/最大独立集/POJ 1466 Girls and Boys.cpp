#include<cstdio>
#include<cstring>
#include<vector>
#define N 550
using namespace std;
//ac 500ms ��������
/*
����:��n��ѧ��,��ͬ��Ů֮�����������ϵ,
��:������ϵһ����һ��һŮ,����Ҫ����Щ����
��ϵ���ҵ���󼯺�,�����������������ѧ��֮��
������������ϵ,����ѧ���������.
����:�����=��ͼ����������,���մ���������ϵ�������.
ע��:�����в�û�и�������˭����˭��Ů,ֻ��������ϵ��ѧ�����Ա�һ���ǲ�ͬ��.
ʵ��������ϵ����Ů���Լ�����,�Ⲣ����Ӧʵ�ʽ��,Ҳ�ɲ�����,�������е���������.
����:http://poj.org/problem?id=1466
˼·:����������ϵ�ǰ���һ��һŮ���ӵ�,Ҳ����������ϵ
��������������ɫһ���ǲ�ͬ��,�������˽���Ⱦɫ��,���
��������ϵ���ɵ�����ͼһ���Ƕ���ͼ,�������ʵ���Ȼ����������
������ͼ����������=������-���ƥ��.����û���ý���Ⱦɫ������
2������,������е����ܱ�������,���/2.
*/
int n,m,vis[N],match[N],ans;
vector<int> G[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(match[v] == -1 || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(match,-1,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=0;i<n;i++){
            scanf("%d: (%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                G[u].push_back(v);
                G[v].push_back(u);
            }
        }
        for(int i=0;i<n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans/2);
    }
    return 0;
}
