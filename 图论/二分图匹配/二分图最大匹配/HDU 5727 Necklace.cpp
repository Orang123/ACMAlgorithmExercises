#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 11
#define INF 0x3f3f3f3f
using namespace std;
//���ƥ�佨ģ����
//��дö��ȫ����TLE ��֪��ԭ��,������stl��next_permutation��Ī���������
/*
����:��n������ʯ,n����ʯ,��m������,eg:u-v
��ʾ��ʯu����ʯv����ʱ,��ʯu�ͻ�������,
����Ҫ����2n��ʯ�����ɻ�������,������ٻ�
�ж�����ʯ�������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5727
˼·:��Ϊ�����ɻ��ε�����,�����Ƚ���ʯ�̶�һ��λ��ö��ʣ��
n-1����ʯ��ȫ�����ٿ���ö�����е���ʯi���������2����ʯ��j��j+1֮��,
���������ʯ����ʯj��j+1���ڲ��������ʱ������ʯi����ʯj�������,
֮��������������ƥ��cnt��������������n��������ʯ�ڲ������������ʯ�������,
��ôn-cnt����ʣ�»�����������ʯ,����ÿ�����бȽ�n-cnt����Сֵ���Ǵ�.

��ʵ���Ҳ��������ʯö��ȫ����,������ʯ,��Ϊ��ʯ ��ʯ������Ϊn.
*/

int n,m,mp[N][N],vis[N],match[N],ans,a[N];
vector<int> G[N];

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

void hungary(){
    for(int i=1;i<=n;i++) G[i].clear();
    for(int i=1;i<=n;i++){//ö��Ҫ�������ʯi
        int l,r;//l����a[j] r����a[j+1]
        for(int j=1;j<=n;j++){//ö���������ڵ���ʯj��j+1
            l=a[j];
            if(j == n) r=a[1];//j==nʱ,���ڵ���ʯΪa[n]��a[1]
            else r=a[j+1];
            if(!mp[i][l] && !mp[i][r])//����ʯi��l��r�����ᷢ����Ӧ������,��i->j�������
                G[i].push_back(j);
        }
    }
    int cnt=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) cnt++;
    }
    //���ƥ���������ܲ���Ĳ������������ʯ����,
    //��n-���ƥ�����ʣ������������ʯ����ÿ������ȡ��Сֵ
    ans=min(ans,n-cnt);
}

void permutation(int cnt){
    //���ʣ�±���������ʯ�����Ѿ��ﵽ0(��С),�Ͳ�����ö��ȫ������.
    if(!ans) return;
    if(cnt == n+1){
        hungary();//ö������ʯȫ����,���ǲ�����ʯ
        return;
    }
    for(int i=2;i<=n;i++){//��ֵ1�Ѿ��̶��ڵ�һ��λ��,���Դ�2��ʼ
        if(!vis[i]){
            vis[i]=1;
            a[cnt]=i;
            permutation(cnt+1);
            vis[i]=0;
        }
    }
}

void init(){
    ans=INF;
    memset(mp,0,sizeof(mp));
    memset(vis,0,sizeof(vis));
    //��Ϊ�ǻ�����,����123��321���ظ���,��˹̶���һ��λ�÷�1,
    //ö��ʣ��n-1��λ�õ�ȫ���м���.
    a[1]=1;
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=1;
        }
        permutation(2);//��һ��λ���Ѿ��̶�,�ӵڶ���λ�ÿ�ʼö��
        printf("%d\n",ans);
    }
    return 0;
}

/*
//stl ö��ȫ���й���
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,mp[N][N],vis[N],match[N],ans,a[N];
vector<int> G[N];

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

void hungary(){
    for(int i=1;i<=n;i++) G[i].clear();
    for(int i=1;i<=n;i++){
        int l,r;
        for(int j=1;j<=n;j++){
            l=a[j];
            if(j == n) r=a[1];
            else r=a[j+1];
            if(!mp[i][l] && !mp[i][r])
                G[i].push_back(j);
        }
    }
    int cnt=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) cnt++;
    }
    ans=min(ans,n-cnt);
}

void permutation(int cnt){
    if(!ans) return;
    if(cnt == n+1){
        hungary();
        return;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            a[cnt]=i;
            permutation(cnt+1);
            vis[i]=0;
        }
    }
}

void init(){
    ans=INF;
    memset(mp,0,sizeof(mp));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) a[i]=i;
    a[1]=vis[1]=1;
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        if(!n){
            printf("0\n");
            continue;
        }
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=1;
        }
        do{
            hungary();
        }while(next_permutation(a+2,a+n+1) && ans);
        //permutation(2);
        printf("%d\n",ans);
    }
    return 0;
}
*/
