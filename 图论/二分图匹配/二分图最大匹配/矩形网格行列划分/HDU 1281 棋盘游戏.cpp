#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;
//ac 0ms ö�ٱ�Ҫƥ���link[i]��ʾ��link[i]�����i
/*
����:һ��n*m����������,�����������Ϸ������е�'��',
������������������ͬһ��ͬһ��,�������Ǿͻ��໥����,
������ֻ�в���λ�ÿ��Է���'��'.����������ܷż���'��',
�����м���λ���Ǳ�����õ�,�����������Щλ�÷���'��',
�������ܷ���'��'�������ͻ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1281
˼·:������������ͬһ��ͬһ��,��ô���������������б�Ȼ��
�ǲ�һ��,�����ص���,��ô��Ȼһ�����ĺ���ڷſ��Կ���n*m����
���к��е�һ��ƥ��,���е��к����е���ǡ�ÿ��Է�Ϊ��������,
�������к��С��к�����û�й�����,�������ڷ�'��'����Ŀ
�����ת��Ϊ����������к������м����Ŀɷ���'��'λ��
���п��ܵ����ƥ��.���п��ܷ���'��'�����м佨��->�е������,
Ȼö��ÿ����ƥ������б�ɾ��,�������ƥ��,������ƥ����Ŀ����,
��˵�����ж�λ�����λ�ñ���Ҫ�ڷ�'��',����Ͳ��Ǳ�Ҫλ��.
*/
int cas,n,m,k,mp[N][N],vis[N],match[N],link[N],ans,cnt;

int dfs(int u){
    for(int v=1;v<=n;v++){
        if(!mp[u][v] || vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int hungary(){
    int num=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) num++;
    }
    return num;
}

void init(){
    ans=0;
    cas++;
    memset(mp,0,sizeof(mp));
}

int main(){
    int u,v;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        init();
        while(k--){
            scanf("%d%d",&u,&v);
            mp[u][v]=1;
        }
        cnt=hungary();
        for(int i=1;i<=m;i++)
            link[i]=match[i];//link[i]��ʾ��link[i]�����i
        for(int i=1;i<=n;i++){//ö��ɾ��ÿ����ƥ���,�ж����ƥ���Ƿ�����
            for(int j=1;j<=m;j++){
                if(!mp[i][j]) continue;
                if(link[j]!=i) continue;//����ƥ���,��������������֤�ж�
                mp[i][j]=0;
                if(hungary() != cnt)
                    ans++;
                mp[i][j]=1;
            }
        }
        printf("Board %d have %d important blanks for %d chessmen.\n",cas,ans,cnt);
    }
    return 0;
}

/*
//ac 0ms ö�ٱ�Ҫƥ���link[i]��ʾ��i�����link[i]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110

using namespace std;
int cas,n,m,k,mp[N][N],vis[N],match[N],link[N],ans,cnt;

int dfs(int u){
    for(int v=1;v<=n;v++){
        if(!mp[u][v] || vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int hungary(){
    int num=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) num++;
    }
    return num;
}

void init(){
    ans=0;
    cas++;
    memset(mp,0,sizeof(mp));
}

int main(){
    int u,v;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        init();
        while(k--){
            scanf("%d%d",&u,&v);
            mp[u][v]=1;
        }
        cnt=hungary();
        for(int i=1;i<=m;i++)
            link[match[i]]=i;//link[i]��ʾ��i�����link[i]
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!mp[i][j]) continue;
                if(link[i]!=j) continue;
                mp[i][j]=0;
                if(hungary() != cnt)
                    ans++;
                mp[i][j]=1;
            }
        }
        printf("Board %d have %d important blanks for %d chessmen.\n",cas,ans,cnt);
    }
    return 0;
}
*/

/*
//ac 31ms ֱ�Ӽ�¼k��'��'������ƥ��ö�������ܷ�'��'������ɾ���ָ�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int cas,n,m,k,mp[N][N],vis[N],match[N],ans,cnt;
int x[N*N],y[N*N];

int dfs(int u){
    for(int v=1;v<=n;v++){
        if(!mp[u][v] || vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int hungary(){
    int num=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) num++;
    }
    return num;
}

void init(){
    ans=0;
    cas++;
    memset(mp,0,sizeof(mp));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        init();
        for(int i=1;i<=k;i++){
            scanf("%d%d",&x[i],&y[i]);
            mp[x[i]][y[i]]=1;
        }
        cnt=hungary();
        for(int i=1;i<=k;i++){//ö�����г�������,������ƥ�������hungary()�Ľ�����ƥ���ǲ����,����Ӱ����
            mp[x[i]][y[i]]=0;
            if(hungary() != cnt)
                    ans++;
            mp[x[i]][y[i]]=1;
        }
        printf("Board %d have %d important blanks for %d chessmen.\n",cas,ans,cnt);
    }
    return 0;
}
*/
