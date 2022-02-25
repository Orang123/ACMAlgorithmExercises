#include<cstdio>
#include<cstring>
#include<vector>
#define N 110
#define M 1100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//ac 873ms ��С·������
/*
����floyd��ʼ��һ��Ҫ���Լ����Լ�����Ϊ0,ȫ������ΪINF��wa.
ʵ��ȫ������ΪINF�������i->k->k->i�����Ļ�·,mp[i][i]�����
���³�mp[i][k]+mp[k][i]����ֵ,���������ӦΪ0,���Ⲣ��Ӱ��
���ඥ��Ե���̾���,���Ҵ���ʵ�ʲ�ͬ������(����)�п�����
�ص���ͬ,����ʼʱ�䲻ͬ,�����п���һ������ص���x,�¸�����
�ص㻹��x,��ʱ���õ����Լ����Լ�mp[i][i]�������,��ֱ�ӳ�ʼ��INF�����.
*/

/*
����:n������,m��˫���·,ÿ����·��һ������,����Ҫ
��һЩ���е���������,������q������,ÿ��������Ҫ��ĳ������
������,��Ȼֻ�������Լ�һ�˺������,���ڹ�����Ҫ���ѵİ���ȥ��
ʣ�µ�����,�ʹ���������Ҫ�������ѵİ������ܽ�q���������������.
ÿ��������p,t���ɷֱ����������ĳ��к��͵���ʱ���,
ÿ����������ʱÿ��λʱ��һ����λ�ľ���,����һ������������ŵ�·����һ������,
����ÿ���˿�������ѡ���ʼ�ĳ��кͿ�ʼ��ʱ��.
ע��:
1.��������Ҳ��ѡ��һ��·��������,ͬһҪ������ĳ��пɱ�������Ѿ���.
��:��������·�߿ɽ���.
2.��ͬ����,�п���������ĵص�����ͬ��,���ʹ�ʱ�䲻ͬ,��˻��õ�mp[i][i]�������Ի�,
���Գ�ʼ��һ��Ҫ��mp[i][i]�Լ����Լ�����Ϊ0,����ȫ����INF,��������mp[i][i]Ϊĳ����·�ָ�ľ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3991
˼·:��POJ 3216һ��,���߰��յ�ǰ����ʼʱ���+������������̾���<=��һ�����ʹ�ʱ�佨�����.
��С���ཻ·������ת��Ϊ��С���ཻ·������=������-���ƥ��-1.
��Ϊ��������Ҳ�Ḳ��ѡ��һ��·������,��˽��Ҫ��ȥ���� ��˼�1.
*/

int cas,n,m,q,vis[M],match[M],ans;
ll mp[N][N];
vector<int> G[M];

struct Node{
    int p;
    ll t;
}node[M];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(match[v] == -1 || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

//����������Ƭ����̾���պ�Ҳ������������ͨ������
//����С���ཻ��·������ת��Ϊ����С���ཻ��·������
void floyd(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                if(mp[i][j]>mp[i][k]+mp[k][j])
                    mp[i][j]=mp[i][k]+mp[k][j];
        }
    }
}

void init(){
    ans=0;
    cas++;
    //floyd����ֱ�ӳ�ʼ��INF,ֱ�ӳ�ʼ��INF�ᵼ��mp[i][i]��ֵ����,
    //����Ҫ���Լ����Լ�����Ϊ0����.
    //memset(mp,0x3f,sizeof(mp));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            mp[i][j]=i==j?0:INF;//i==j�Ի�������0
    }
    memset(match,-1,sizeof(match));
    for(int i=1;i<=q;i++) G[i].clear();
}

int main(){
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&q);
        init();
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            mp[u][v]=mp[v][u]=w;
        }
        for(int i=1;i<=q;i++)
            scanf("%d%lld",&node[i].p,&node[i].t);
        floyd();
        for(int i=1;i<=q;i++){
            for(int j=1;j<=q;j++){
                if(i == j) continue;
                //��ͬ������node[i].p��node[j].p�ĵص������ͬ,Ҳ���ǻ��õ�mp[i][i]�������Ի�,
                //���ʹ�ʱ��node[i].t��node[j].tҪ��ͬ
                if(node[i].t+mp[node[i].p][node[j].p]<=node[j].t)
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=q;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("Case %d: %d\n",cas,q-ans-1);//��С·������=������-���ƥ��
    }
    return 0;
}
