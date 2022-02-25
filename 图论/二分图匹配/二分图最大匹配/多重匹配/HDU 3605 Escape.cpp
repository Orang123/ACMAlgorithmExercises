#include<cstdio>
#include<cstring>
#include<vector>
#define N 100010
using namespace std;
//ac 1482ms 匈牙利求解多重匹配 link[15][N]用二维数组实现
//还可通过转化为网络流模型去做
//n<=100000,暴力建边将多重匹配转化为最大匹配肯定会TLE
/*
题意:n个人m个星球,每个星期可供居住的人有上限,输入的邻接矩阵
mp[i][j]=1,代表编号为i的人适合居住在编号为j的星球上,现在求所有
人是否都能找到适合居住的星球.
释义:就是N集合(人)+M(星球)集合划分的二分图的多重匹配,M中的点可配对N中的多个点,
但有一定上限,求N中每个点是否都能找到M中的配对点.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3605
思路:由于M中点可配对多个n中的点,所以可将匈牙利算法中的link配对数组
扩展成二维的link[M][N],M<=10,N<=100000.对于当前M中可配对的上限点数
还未满,可以直接配对,当M中可配对点数满了后,再开始枚举M中每个之前配对的N
中的点腾出位置使其失配,直到找到增广路结束.
*/
//cnt[v]是v星球当前已匹配的N集合中人的数量.
//link[v][i]=u,代表星球v匹配的第i个点是N集合中的编号为u的点
int n,m,vis[15],num[15],link[15][N],cnt[15];
vector<int> G[N];

int dfs(int u,int clock){
    for(int &v : G[u]){
        //这里v星球做上标记后,就不会再作为可考虑匹配的星球
        //因为枚举v星球失配那里就已经尝试枚举所有v中已匹配的点了,
        //如果存在增广路,要么是找别的星球匹配,要么是从v星球中拆散的点再去找别的星球匹配
        if(vis[v] == clock) continue;//每次找增广路设置不同时间戳,优化
        vis[v]=clock;
        if(cnt[v]<num[v]){//星球v可匹配上限未满
            link[v][++cnt[v]]=u;//v星球第cnt[v]个匹配的N集合中点的编号为u
            return 1;
        }
        else{//星球v可匹配数量到达上限,
            for(int i=1;i<=cnt[v];i++){
                if(dfs(link[v][i],clock)){//尝试枚举v星球中已匹配的点失配,搜索新的增广路
                    link[v][i]=u;//已找到增广路,更新星球v已匹配的第i的点是N集合中的编号为u的点
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
                if(x)//代表第i个人适合居住在第j个星球
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=m;i++)
            scanf("%d",&num[i]);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(!dfs(i,i)){//一旦第i个人不能找到适合居住的星球就结束输出NO 不优化直接判断ans==n会TLE
                flag=1;
                break;
            }
        }
        if(!flag) printf("YES\n");//所有人都能找到可居住的星球
        else printf("NO\n");
    }
    return 0;
}

/*
//link用vector 采用迭代器遍历 TLE 迭代器iterator很耗时
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
//这个做法是错误的做法,vis数组开成二维只维护一次(如果每次都维护,失配的点会再度考虑之前失配的星球去匹配无线递归),
//对于这种做法人u就不可再考虑v星球匹配,
//也就是每个人匹配一个星球只有一次机会,但是在不断匹配失配搜索增广路的过程中,
//人u有时它会和v星球先匹配再失配再度匹配再失配这都是有可能的.

//vis采用二维数组标记,对于失配的星球v,再度搜索增广路时,
//需要先删掉之前v中那个尝试失配,因为后面可能还会使v星球失配,
//如果不删除原先枚举的点又会枚举一遍.
//v仍旧可作为待匹配的星球再度枚举v星球已匹配点使其失配,
//但其实不必这样,如果存在增广路并且这个失配点一定在v星球中,
//就直接在第一次dfs枚举所有原先和星球匹配的人使其失配即可,
//没能找到增广路时回溯回来枚举v星球已匹配的下一个点使其失配,
//不必深度搜索时再度考虑枚举v星球已匹配点失配,这样递归的深度调用栈复杂度也会加大
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
        if(num[v]){//v星球还能匹配人
            num[v]--;//v星球待匹配人减1
            link[v].push_back(u);
            return 1;
        }
        else{//v星球不能再匹配人时,尝试枚举拆散已匹配点 腾出位置
            int tmp;
            for(it=link[v].begin();it!=link[v].end();it++){
                tmp=*it;//用tmp记录下it迭代器指向的位置的值,因为link[v]删掉*it后,it所记录的位置是原先位置的下一个位置无法恢复
                link[v].erase(it);//这里先把要腾出的位置删除,避免再度遍历到当前的星球 又腾出相同的it
                if(dfs(tmp)){
                    link[v].push_back(u);//重新设置匹配
                    return 1;
                }
                else//如果没有找到增广路,就恢复星球v匹配的编号为tmp的人
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
