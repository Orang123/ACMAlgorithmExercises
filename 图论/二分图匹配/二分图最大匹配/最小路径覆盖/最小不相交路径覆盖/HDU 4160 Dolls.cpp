#include<cstdio>
#include<cstring>
#include<vector>
#define N 550
using namespace std;
//ac 15ms ��С���ཻ·������
/*
����:n��������,��w(���),l(����),h(�߶�),
��һ��������i��w��l��h����ָ�궼С��������jʱ,
��ʱ�Ϳ��Խ�������i����������j���,ÿ���������ڲ�
���ֻ��Ƕ��һ��������,���ڰ��������׷�,���������
��������������¶��������,ע����¶����������������ڲ�
���ܺ��кܶ�������,����ֻ������¶���������Щ�����޵�����
��С����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4160
˼·:��Ϊÿ���������ڲ����ֻ��Ƕ��һ��������,�����Ա�Ƕ��
��Ƕ�׵������޿��Կ���һ��ƥ��,��ôʵ��ÿ����¶���������������
�����ڲ�Ƕ�׵�������ǡ�ÿ��Կ���һ����·��,��ÿ����¶�������������,
���ǿ��Կ����������ཻ��·��(ÿ����ͬ����������޵ı˴��ڲ��������ǲ��ཻ��),
Ҫ����¶�����������������Ŀ����,��ÿ�������޿�����,����ת��Ϊ��
�����м���·���������еĵ�,��:��С���ཻ·������,������������
����߾��������޼��Ƕ�׹�ϵ,������������i��w��l��h��С��������j,
����i->j�������,����ǡ�ù�����DAG,���������������ƥ��,
����С���ཻ·������=������-���ƥ��.
*/
int n,vis[N],match[N],ans;
vector<int> G[N];

struct Node{
    int w,l,h;
}node[N];

int dfs(int u){
    for(int &v : G[u]){
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
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&node[i].w,&node[i].l,&node[i].h);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i == j) continue;
                //������i�Ŀ������߶��ϸ�С��������jʱ,�ͽ���i->j�������.
                if(node[i].w<node[j].w && node[i].l<node[j].l && node[i].h<node[j].h)
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans);//��С���ཻ·������=������-���ƥ��
    }
    return 0;
}
