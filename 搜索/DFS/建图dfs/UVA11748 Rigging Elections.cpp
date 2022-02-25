/*
����:ժ������
��n����ѡ�ˣ���m����ͶƱ��ÿ���˶Ծ�ѡ�˶���һ��������ÿ�������˾�ѡ��
m���˷ֱ�ͶƱ��ÿ�������ˣ�ʤ���߼������뾺ѡ��ʧ������̭��ʣ��һ����
��ʱ��ֹͣ��ϣ����c�����ʤ��������԰���ÿ�β��뾺ѡ��������ѡ�ˣ�
���Ƿ��п�����c��ѡ�ɹ���
1<=n,m<=100.
����:https://www.luogu.com.cn/problem/UVA11748
˼·:��������������i,j,��m���˵����ȼ���,����i������ռ����������,��i->j��
���ȱ�,����j->i�������.����c�㿪ʼ�����Ƿ����γ�һ����cΪ���ڵ��������,
�����γ�,��˵��c���Ի������ʤ��.����c�����м�ڵ㲻�����˱�Ե�������˵��,
c����������Ʊ�����ȼ���ߵ�,���c���ܻ�ʤ.
*/
//ac 0ms dfs����
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

int n,m,c,vis[N],g[N][N];
vector<int> G[N];

int dfs(int u){
    if(vis[u])
        return 0;
    vis[u]=1;
    int res=1;
    for(int &v : G[u]){
        res+=dfs(v);
    }
    return res;
}

int main(){
    int x;
    while(scanf("%d%d%d",&n,&m,&c) && n+m+c){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            G[i].clear();
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&x);
                g[i][x]=j;//x�����ȼ� Ϊj
            }
        }
        int num=0;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                num=0;
                for(int k=1;k<=m;k++){
                    if(g[k][i]<g[k][j])
                        num++;
                }
                if(num>m/2)//��m���˵�ͶƱ�� ��i���˵�Ʊ��Ҫ���ڵ�j���� ��i->j�������
                    G[i].push_back(j);
                else
                    G[j].push_back(i);
            }
        }
        if(dfs(c) == n)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
