/*
//����ժ������
����:���ڸ���n��ģ��,ÿ��ģ����һ������w[i],������ֵb[i],ģ��֮����m�����ѹ�ϵ,
���x��y������,��ôx�����Ѻ�y������Ҳ������.��ô�������Խ���Щģ�ظ�������Ȧ�ӷ���.
�����и����뿪һ��party,��ϣ����ģ�ص�����֮�Ͳ�����v�������ʹ������ֵ֮�����,
�������������ֵ�Ƕ���.�μ�party��ģ�ص�Ҫ���Ƕ���һ������Ȧ�ӵ�ģ��,����ѡ��,
һ������������Ȧ�����ģ��,����ֻ�������Ȧ����Ĳ�����1��ģ��.
n,v<=1000
����:https://codeforces.ml/problemset/problem/742/D
˼·:���鱳��,�ò��鼯�����ѹ�ϵ����һ������Ȧ�������˷�����һ����,ÿ���˶���ͬ��
һ��������Ʒ,���һ����Ʒ����������Ϊһ����Ʒ,����������������֮��,����ֵ��������
����ֵ֮��.���Ӷ�Ϊ1*1000*1000=10^6
*/
//ac 46ms ʹ��vector ���鼯+���鱳��
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;

int n,m,v,fa[N],w[N],b[N],dp[M];
//allw allb��ʾ������������Ʒ������� ��ֵ�� ���������������Ʒ��ѡ
int allw[N],allb[N];
vector<int> G[N];

int find(int x){
    return fa[x] == x ? x :fa[x]=find(fa[x]);
}

int main(){
    int x,y;
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&m,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    while(m--){
        scanf("%d%d",&x,&y);
        x=find(x),y=find(y);
        if(x!=y){
            fa[x]=y;
        }
    }
    for(int i=1;i<=n;i++){
        x=find(i);
        G[x].push_back(i);
        allw[x]+=w[i];
        allb[x]+=b[i];
    }
    for(int i=1;i<=n;i++){
        if(!G[i].size()) continue;
        for(int j=v;j>=1;j--){
            for(int &k : G[i]){
                if(j>=w[k])
                    dp[j]=max(dp[j],dp[j-w[k]]+b[k]);
            }
            if(G[i].size()>1 && j>=allw[i])
                dp[j]=max(dp[j],dp[j-allw[i]]+allb[i]);
        }
    }
    printf("%d",dp[v]);
    return 0;
}

/*
//ac 46ms ��ʹ��vector ���鼯+���鱳��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;

int n,m,v,fa[N],a[N],b[N],dp[M];
int num[N],w[N][N],val[N][N],vis[N];

int find(int x){
    return fa[x] == x ? x :fa[x]=find(fa[x]);
}

int main(){
    int x,y,k;
    memset(vis,0,sizeof(vis));
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&m,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    while(m--){
        scanf("%d%d",&x,&y);
        x=find(x),y=find(y);
        if(x!=y){
            fa[x]=y;
        }
    }
    k=0;
    for(int i=1;i<=n;i++){
        int x=find(i);
        if(!vis[x]){
            vis[x]=++k;
            num[k]++;
            w[k][num[k]]=a[i];
            val[k][num[k]]=b[i];
        }
        else{
            //vis[x]��ʾʵ�����ѹ�ϵ���ڵ��Ӧ�ķ�����
            //num[vis[x]]��ʾ�÷���������Ʒ�ĸ���
            num[vis[x]]++;
            w[vis[x]][num[vis[x]]]=a[i];
            val[vis[x]][num[vis[x]]]=b[i];
        }
    }
    for(int i=1;i<=k;i++){
        if(num[i] == 1) continue;
        for(int j=1;j<=num[i];j++){
            w[i][num[i]+1]+=w[i][j];
            val[i][num[i]+1]+=val[i][j];
        }
        num[i]++;
    }
    for(int i=1;i<=k;i++){
        for(int j=v;j>=1;j--){
            for(int t=1;t<=num[i];t++)
                if(j>=w[i][t])
                    dp[j]=max(dp[j],dp[j-w[i][t]]+val[i][t]);
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/
