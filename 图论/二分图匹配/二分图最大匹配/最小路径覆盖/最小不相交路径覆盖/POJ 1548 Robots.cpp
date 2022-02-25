#include<cstdio>
#include<cstring>
#include<vector>
#define N 25*25
using namespace std;
//ac 16ms DAG����С·������
/*
����:n*n��������,ĳЩλ�ô���������'G'��ʾ,
ÿ��������ֻ�����һ�������,�����˿��Խ���;����
��'G'�ϵ�����������,������������Ҫ�ɳ�����������
��(1,1)����������Ͻǽ����ܽ����е������ռ����.
ע��:ÿ����������ռ����,���������˾������ڷ����ռ�.
����:http://poj.org/problem?id=1548
˼·:ÿ����������ռ����,���������˾������ڷ����ռ�.
������Ҫ�������������ߵ�·�����ܽ����е�G�㸲��
��ȫ,��������С���ཻ·������.��ͼֻ��Ҫ�������е�G���ɵ�DAG����,
��Gi�ĺ������궼���ڵ���Gj�ĺ���������,����i->j�������,����
��DAG��һ���������㷨������ƥ��,����С·������=������-���ƥ��.
��ʵ�Ϻʹ�(1,1)�����,�������Ͻǽ���û��ϵ,��Ҫ��Ҫ���������е�G,
��Ȼÿ�������˶��ܵ��ﶫ�Ͻǽ���,���˵�����������Ի��.
*/
int k,vis[N],match[N],flag,ans;
vector<int> G[N];
struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node[N];

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
    memset(match,0,sizeof(match));
    for(int i=1;i<=N;i++) G[i].clear();
    ans=k=flag=0;
}

int main(){
    int u,v;
    while(1){
        init();
        while(scanf("%d%d",&u,&v) && u+v){
            if(u == -1 && v == -1){
                flag=1;
                break;
            }
            node[++k]=Node(u,v);
        }
        if(flag) break;
        for(int i=1;i<=k;i++){
            for(int j=i+1;j<=k;j++){//ÿ��i �������е�j(j>i)
                //i�ĺ������궼���ڵ���j�ĺ�������,��j��i�����·� �ͽ�һ��i->j�����
                if(node[i].x<=node[j].x && node[i].y<=node[j].y)
                    G[i].push_back(j);
                else if(node[j].x<=node[i].x && node[j].y<=node[i].y)
                    G[j].push_back(i);
            }
        }
        for(int i=1;i<=k;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",k-ans);
    }
    return 0;
}
