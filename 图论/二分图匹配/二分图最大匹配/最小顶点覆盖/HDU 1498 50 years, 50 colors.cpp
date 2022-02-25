#include<cstdio>
#include<cstring>
#include<vector>
#define N 110
using namespace std;
//ac 31ms 最小点覆盖 dfs标记每次配对的颜色
/*
题意:n*n的网格上有不同颜色的气球(最多50种颜色),
每次可以选择一行或一列同一颜色的气球全部击破,
现在问总共有哪些颜色的气球全部击破所需要使用的
次数大于k,请升序输出这些颜色,若不存在这样的颜色,则输出-1.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1498
思路:可以将所有的行列划分为2个集合,一个气球对应唯一的
一组行列配对,很明显这是一组匹配,那么和POJ 3041不同的是,
每次击破一行或一列只能是一种颜色的气球,那么可以枚举每一种
颜色,去跑行列的匹配,求出最小顶点覆盖=最大匹配,判断其结果,
若大于k,则加入vector.
*/
int n,k,m,mp[N][N],vis[N],match[N],ans,has[55];
vector<int> seq;

int dfs(int u,int color){
    for(int v=1;v<=n;v++){
        if(mp[u][v]!=color || vis[v]) continue;//判断当前行列配对的颜色是否为枚举的color
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
    if(cnt>k) seq.push_back(color);//需要的次数大于k 存入seq
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
                has[mp[i][j]]=1;//has[i]=1,表示颜色编号为i存在
                m=max(mp[i][j],m);//记录最大颜色编号
            }
        }
        for(int i=1;i<=m;i++){//枚举每种颜色i 跑匈牙利判断其最少摧毁次数
            if(!has[i]) continue;//不存在颜色编号为i的气球.
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
//ac 46ms 每次枚举一种颜色都重新建立该颜色行列配对的二分图
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
        for(int k=1;k<=m;k++){//枚举每种颜色k 跑匈牙利判断其最少摧毁次数
            if(!has[k]) continue;
            for(int i=1;i<=n;i++) G[i].clear();
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(mp[i][j] == k)//重新构造该颜色k配对的行列二分图
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
