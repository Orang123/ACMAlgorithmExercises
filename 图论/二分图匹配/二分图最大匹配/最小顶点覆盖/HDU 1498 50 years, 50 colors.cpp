#include<cstdio>
#include<cstring>
#include<vector>
#define N 110
using namespace std;
//ac 31ms ��С�㸲�� dfs���ÿ����Ե���ɫ
/*
����:n*n���������в�ͬ��ɫ������(���50����ɫ),
ÿ�ο���ѡ��һ�л�һ��ͬһ��ɫ������ȫ������,
�������ܹ�����Щ��ɫ������ȫ����������Ҫʹ�õ�
��������k,�����������Щ��ɫ,����������������ɫ,�����-1.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1498
˼·:���Խ����е����л���Ϊ2������,һ�������ӦΨһ��
һ���������,����������һ��ƥ��,��ô��POJ 3041��ͬ����,
ÿ�λ���һ�л�һ��ֻ����һ����ɫ������,��ô����ö��ÿһ��
��ɫ,ȥ�����е�ƥ��,�����С���㸲��=���ƥ��,�ж�����,
������k,�����vector.
*/
int n,k,m,mp[N][N],vis[N],match[N],ans,has[55];
vector<int> seq;

int dfs(int u,int color){
    for(int v=1;v<=n;v++){
        if(mp[u][v]!=color || vis[v]) continue;//�жϵ�ǰ������Ե���ɫ�Ƿ�Ϊö�ٵ�color
        vis[v]=1;
        if(!match[v] || dfs(match[v],color)){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void hungary(int color){
    int cnt=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i,color)) cnt++;
    }
    if(cnt>k) seq.push_back(color);//��Ҫ�Ĵ�������k ����seq
}

void init(){
    m=0;
    memset(has,0,sizeof(has));
    seq.clear();
}

int main(){
    while(scanf("%d%d",&n,&k) && n+k){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&mp[i][j]);
                has[mp[i][j]]=1;//has[i]=1,��ʾ��ɫ���Ϊi����
                m=max(mp[i][j],m);//��¼�����ɫ���
            }
        }
        for(int i=1;i<=m;i++){//ö��ÿ����ɫi ���������ж������ٴݻٴ���
            if(!has[i]) continue;//��������ɫ���Ϊi������.
            hungary(i);
        }
        if(!seq.size()) printf("-1\n");
        else{
            int flag=0;
            for(int &i : seq){
                if(!flag){
                    printf("%d",i);
                    flag=1;
                }
                else
                    printf(" %d",i);
            }
            printf("\n");
        }
    }
    return 0;
}

/*
//ac 46ms ÿ��ö��һ����ɫ�����½�������ɫ������ԵĶ���ͼ
#include<cstdio>
#include<cstring>
#include<vector>
#define N 110
using namespace std;

int n,k,m,mp[N][N],vis[N],match[N],ans,has[55];
vector<int> G[N],seq;

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

void hungary(int color){
    int cnt=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) cnt++;
    }
    if(cnt>k) seq.push_back(color);
}

void init(){
    m=0;
    memset(has,0,sizeof(has));
    seq.clear();
}

int main(){
    while(scanf("%d%d",&n,&k) && n+k){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&mp[i][j]);
                has[mp[i][j]]=1;
                m=max(mp[i][j],m);
            }
        }
        for(int k=1;k<=m;k++){//ö��ÿ����ɫk ���������ж������ٴݻٴ���
            if(!has[k]) continue;
            for(int i=1;i<=n;i++) G[i].clear();
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(mp[i][j] == k)//���¹������ɫk��Ե����ж���ͼ
                        G[i].push_back(j);
                }
            }
            hungary(k);
        }
        if(!seq.size()) printf("-1\n");
        else{
            int flag=0;
            for(int &i : seq){
                if(!flag){
                    printf("%d",i);
                    flag=1;
                }
                else
                    printf(" %d",i);
            }
            printf("\n");
        }
    }
    return 0;
}
*/
