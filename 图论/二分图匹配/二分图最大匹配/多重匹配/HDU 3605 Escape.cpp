#include<cstdio>
#include<cstring>
#include<vector>
#define N 100010
using namespace std;
//ac 1482ms ������������ƥ�� link[15][N]�ö�ά����ʵ��
//����ͨ��ת��Ϊ������ģ��ȥ��
//n<=100000,�������߽�����ƥ��ת��Ϊ���ƥ��϶���TLE
/*
����:n����m������,ÿ�����ڿɹ���ס����������,������ڽӾ���
mp[i][j]=1,������Ϊi�����ʺϾ�ס�ڱ��Ϊj��������,����������
���Ƿ����ҵ��ʺϾ�ס������.
����:����N����(��)+M(����)���ϻ��ֵĶ���ͼ�Ķ���ƥ��,M�еĵ�����N�еĶ����,
����һ������,��N��ÿ�����Ƿ����ҵ�M�е���Ե�.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3605
˼·:����M�е����Զ��n�еĵ�,���Կɽ��������㷨�е�link�������
��չ�ɶ�ά��link[M][N],M<=10,N<=100000.���ڵ�ǰM�п���Ե����޵���
��δ��,����ֱ�����,��M�п���Ե������˺�,�ٿ�ʼö��M��ÿ��֮ǰ��Ե�N
�еĵ��ڳ�λ��ʹ��ʧ��,ֱ���ҵ�����·����.
*/
//cnt[v]��v����ǰ��ƥ���N�������˵�����.
//link[v][i]=u,��������vƥ��ĵ�i������N�����еı��Ϊu�ĵ�
int n,m,vis[15],num[15],link[15][N],cnt[15];
vector<int> G[N];

int dfs(int u,int clock){
    for(int &v : G[u]){
        //����v�������ϱ�Ǻ�,�Ͳ�������Ϊ�ɿ���ƥ�������
        //��Ϊö��v����ʧ��������Ѿ�����ö������v����ƥ��ĵ���,
        //�����������·,Ҫô���ұ������ƥ��,Ҫô�Ǵ�v�����в�ɢ�ĵ���ȥ�ұ������ƥ��
        if(vis[v] == clock) continue;//ÿ��������·���ò�ͬʱ���,�Ż�
        vis[v]=clock;
        if(cnt[v]<num[v]){//����v��ƥ������δ��
            link[v][++cnt[v]]=u;//v�����cnt[v]��ƥ���N�����е�ı��Ϊu
            return 1;
        }
        else{//����v��ƥ��������������,
            for(int i=1;i<=cnt[v];i++){
                if(dfs(link[v][i],clock)){//����ö��v��������ƥ��ĵ�ʧ��,�����µ�����·
                    link[v][i]=u;//���ҵ�����·,��������v��ƥ��ĵ�i�ĵ���N�����еı��Ϊu�ĵ�
                    return 1;
                }
            }
        }
    }
    return 0;
}

void init(){
    for(int i=1;i<=n;i++) G[i].clear();
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
}

int main(){
    int x;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%d",&x);
                if(x)//�����i�����ʺϾ�ס�ڵ�j������
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=m;i++)
            scanf("%d",&num[i]);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(!dfs(i,i)){//һ����i���˲����ҵ��ʺϾ�ס������ͽ������NO ���Ż�ֱ���ж�ans==n��TLE
                flag=1;
                break;
            }
        }
        if(!flag) printf("YES\n");//�����˶����ҵ��ɾ�ס������
        else printf("NO\n");
    }
    return 0;
}

/*
//link��vector ���õ��������� TLE ������iterator�ܺ�ʱ
#include<cstdio>
#include<cstring>
#include<vector>
#define N 100010
using namespace std;

int n,m,vis[15],num[15];
vector<int> G[N],link[15];

int dfs(int u,int clock){
    for(int &v : G[u]){
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(num[v]){
            num[v]--;
            link[v].push_back(u);
            return 1;
        }
        else{
            vector<int>:: iterator it;
            for(it=link[v].begin();it!=link[v].end();it++){
                if(dfs(*it,clock)){
                    link[v].erase(it);
                    link[v].push_back(u);
                    return 1;
                }
            }
        }
    }
    return 0;
}

void init(){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) G[i].clear();
    for(int i=1;i<=10;i++) link[i].clear();
}

int main(){
    int x;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%d",&x);
                if(x)
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=m;i++)
            scanf("%d",&num[i]);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(!dfs(i,i)){
                flag=1;
                break;
            }
        }
        if(flag) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
*/

/*
//��������Ǵ��������,vis���鿪�ɶ�άֻά��һ��(���ÿ�ζ�ά��,ʧ��ĵ���ٶȿ���֮ǰʧ�������ȥƥ�����ߵݹ�),
//��������������u�Ͳ����ٿ���v����ƥ��,
//Ҳ����ÿ����ƥ��һ������ֻ��һ�λ���,�����ڲ���ƥ��ʧ����������·�Ĺ�����,
//��u��ʱ�����v������ƥ����ʧ���ٶ�ƥ����ʧ���ⶼ���п��ܵ�.

//vis���ö�ά������,����ʧ�������v,�ٶ���������·ʱ,
//��Ҫ��ɾ��֮ǰv���Ǹ�����ʧ��,��Ϊ������ܻ���ʹv����ʧ��,
//�����ɾ��ԭ��ö�ٵĵ��ֻ�ö��һ��.
//v�Ծɿ���Ϊ��ƥ��������ٶ�ö��v������ƥ���ʹ��ʧ��,
//����ʵ��������,�����������·�������ʧ���һ����v������,
//��ֱ���ڵ�һ��dfsö������ԭ�Ⱥ�����ƥ�����ʹ��ʧ�伴��,
//û���ҵ�����·ʱ���ݻ���ö��v������ƥ�����һ����ʹ��ʧ��,
//�����������ʱ�ٶȿ���ö��v������ƥ���ʧ��,�����ݹ����ȵ���ջ���Ӷ�Ҳ��Ӵ�
#include<cstdio>
#include<cstring>
#include<vector>
#define N 100100
using namespace std;

int n,m,mp[N][15],vis[N][15],num[15],ans;
vector<int> link[15];
vector<int>:: iterator it;

int dfs(int u){
    for(int v=1;v<=m;v++){
        if(!mp[u][v]) continue;
        if(vis[u][v]) continue;
        vis[u][v]=1;
        if(num[v]){//v������ƥ����
            num[v]--;//v�����ƥ���˼�1
            link[v].push_back(u);
            return 1;
        }
        else{//v��������ƥ����ʱ,����ö�ٲ�ɢ��ƥ��� �ڳ�λ��
            int tmp;
            for(it=link[v].begin();it!=link[v].end();it++){
                tmp=*it;//��tmp��¼��it������ָ���λ�õ�ֵ,��Ϊlink[v]ɾ��*it��,it����¼��λ����ԭ��λ�õ���һ��λ���޷��ָ�
                link[v].erase(it);//�����Ȱ�Ҫ�ڳ���λ��ɾ��,�����ٶȱ�������ǰ������ ���ڳ���ͬ��it
                if(dfs(tmp)){
                    link[v].push_back(u);//��������ƥ��
                    return 1;
                }
                else//���û���ҵ�����·,�ͻָ�����vƥ��ı��Ϊtmp����
                    link[v].push_back(tmp);
            }
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=14;i++) link[i].clear();
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=m;i++)
            scanf("%d",&num[i]);
        for(int i=1;i<=n;i++){
            if(dfs(i)) ans++;
        }
        if(ans == n) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
*/
