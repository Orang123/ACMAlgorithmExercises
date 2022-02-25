#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;
//ac 0ms 枚举必要匹配边link[i]表示行link[i]配对列i
/*
题意:一个n*m的网格棋牌,可以在棋盘上放象棋中的'车',
即任意两个车不能在同一行同一列,否则他们就会相互攻击,
棋盘中只有部分位置可以放置'车'.现在问最多能放几个'车',
并且有几个位置是必须放置的,即如果不在这些位置放置'车',
棋盘上能放置'车'的总数就会减少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1281
思路:两个车不能在同一行同一列,那么任意两个车的行列必然都
是不一样,不会重叠的,那么显然一个车的合理摆放可以看做n*m棋盘
上行和列的一对匹配,所有的行和所有的列恰好可以分为两个集合,
集合内行和行、列和列是没有关联的,现在最多摆放'车'的数目
问题就转化为了求解所有行和所有列间代表的可放置'车'位置
所有可能的最大匹配.所有可能放置'车'的行列间建行->列的有向边,
然枚举每条已匹配的行列边删除,再求最大匹配,如果最大匹配数目减少,
则说明行列定位的这个位置必须要摆放'车',否则就不是必要位置.
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
            link[i]=match[i];//link[i]表示行link[i]配对列i
        for(int i=1;i<=n;i++){//枚举删除每条已匹配边,判断最大匹配是否会减少
            for(int j=1;j<=m;j++){
                if(!mp[i][j]) continue;
                if(link[j]!=i) continue;//不是匹配边,不进行匈牙利验证判断
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
//ac 0ms 枚举必要匹配边link[i]表示行i配对列link[i]
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
            link[match[i]]=i;//link[i]表示行i配对列link[i]
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
//ac 31ms 直接记录k个'车'的行列匹配枚举所有能放'车'的行列删除恢复
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
        for(int i=1;i<=k;i++){//枚举所有车的行列,本身不在匹配的行列hungary()的结果最大匹配是不变的,不会影响结果
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
