/*
//题意摘自网上
题意:对于给定n个模特,每个模特有一个体重w[i],和美丽值b[i],模特之间有m条朋友关系,
如果x和y是朋友,那么x的朋友和y的朋友也是朋友.那么这样可以将这些模特根据朋友圈子分类.
现在有个人想开一个party,他希望在模特的体重之和不超过v的情况下使得美丽值之和最大,
问这个最大的魅力值是多少.参加party的模特的要求是对于一个朋友圈子的模特,两种选择,
一种是邀请整个圈子里的模特,或者只邀请这个圈子里的不超过1个模特.
n,v<=1000
链接:https://codeforces.ml/problemset/problem/742/D
思路:分组背包,用并查集将朋友关系中在一个朋友圈的所有人放置在一个组,每个人都等同于
一件组内物品,最后一件物品是所有人作为一件物品,体重是所有人体重之和,美丽值是所有人
美丽值之和.复杂度为1*1000*1000=10^6
*/
//ac 46ms 使用vector 并查集+分组背包
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;

int n,m,v,fa[N],w[N],b[N],dp[M];
//allw allb表示分组后的所有物品的体积和 价值和 代表该组内所有物品都选
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
//ac 46ms 不使用vector 并查集+分组背包
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
            //vis[x]表示实际朋友关系根节点对应的分组编号
            //num[vis[x]]表示该分组编号下物品的个数
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
