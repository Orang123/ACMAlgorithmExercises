/*
����:n������,m��·,һ��ʼm��·��˫���,Ҫ�޸ĳɵ����,
��ͼ�� ���ܵ����м���,�������ɻ�����ͨͼ�ĸ���.
��ʵ���������ͨ����ͼ��һ������û�е���ͨ��(��)�ĸ���.
����:https://codeforces.ml/problemset/problem/659/E
˼·:����һ����.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
int n,m,head[N],cnt,vis[N],flag;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa) continue;
        if(vis[v]){//ֻҪ�ظ����ʹ��Ҳ��Ǹ��ڵ���˵���л�,�������ܽ���,�ð������ͨͼ���е����������
            flag=1;
            continue;
        }
        dfs(v,u);
    }
}

int main(){
    int u,v,ans=0;
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        flag=0;
        if(!vis[i]){
            dfs(i,0);
            if(!flag)
                ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
