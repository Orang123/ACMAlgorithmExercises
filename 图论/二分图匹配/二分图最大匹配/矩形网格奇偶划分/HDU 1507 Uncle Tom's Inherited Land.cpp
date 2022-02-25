#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;
//ac 46ms 网格按照坐标之和奇偶划分二分图
/*
题意:一个n*m的网格,由土地和池塘2部分组成,现在有k个池塘,
现在要售卖土地,一次只能卖连续的2块1*2或2*1构成的矩形土地,
问最多能卖几块连续的土地,并输出每一对连续土地的坐标.
注意:网格中土地的个数不会超过50.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1507
思路:很明显1*2的矩形土地在售卖时不能有重叠,不能有公共点,
按照对角线奇偶规则分割n*m网格中的土地为两个集合,构造二分图,
匈牙利算法求解最大匹配.可以按照奇偶性将土地的坐标预先存起来,
直接考虑用奇集合和偶集合中的连续的1*2或2*1点建边.最后按照配对
点输出坐标.
*/

int n,m,k,odd,even,ans,mp[N][N],vis[N],match[N];
vector<int> G[N];
struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

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

int judge(int i,int j){
    if(node2[i].x == node1[j].x && node2[i].y == node1[j].y+1) return 1;
    if(node2[i].x == node1[j].x && node2[i].y == node1[j].y-1) return 1;
    if(node2[i].x == node1[j].x+1 && node2[i].y == node1[j].y) return 1;
    if(node2[i].x == node1[j].x-1 && node2[i].y == node1[j].y) return 1;
    return 0;
}

void init(){
    ans=odd=even=0;
    memset(mp,0,sizeof(mp));
    memset(match,0,sizeof(match));
    for(int i=1;i<=50;i++) G[i].clear();
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        scanf("%d",&k);//n*m网格有k个池塘
        while(k--){
            scanf("%d%d",&x,&y);
            mp[x][y]=1;//标记池塘
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!mp[i][j]){
                    if((i+j)%2) node1[++odd]=Node(i,j);//奇数集合
                    else node2[++even]=Node(i,j);//偶数集合
                }
            }
        }
        for(int i=1;i<=even;i++){//奇数集合和偶数集合中连续的1*2或2*1建边
            for(int j=1;j<=odd;j++){
                if(judge(i,j))
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=even;i++){//考虑每个偶数点的配对
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;//match中记录的是奇数点配对的偶点的编号
        }
        printf("%d\n",ans);
        for(int i=1;i<=odd;i++){//从奇数点 match中找到对应配对的偶点,输出的匹配时偶点->奇点
            if(!match[i]) continue;
            printf("(%d,%d)--(%d,%d)\n",node2[match[i]].x,node2[match[i]].y,node1[i].x,node1[i].y);
        }
    }
    return 0;
}

/*
//ac 46ms 时间戳优化的匈牙利算法避免频繁初始化vis数组
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

int n,m,k,odd,even,ans,mp[N][N],vis[N],match[N];
vector<int> G[N];
struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

int dfs(int u,int clock){
    for(int &v : G[u]){
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(!match[v] || dfs(match[v],clock)){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int judge(int i,int j){
    if(node2[i].x == node1[j].x && node2[i].y == node1[j].y+1) return 1;
    if(node2[i].x == node1[j].x && node2[i].y == node1[j].y-1) return 1;
    if(node2[i].x == node1[j].x+1 && node2[i].y == node1[j].y) return 1;
    if(node2[i].x == node1[j].x-1 && node2[i].y == node1[j].y) return 1;
    return 0;
}

void init(){
    ans=odd=even=0;
    memset(mp,0,sizeof(mp));
    memset(match,0,sizeof(match));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=50;i++) G[i].clear();
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        scanf("%d",&k);
        while(k--){
            scanf("%d%d",&x,&y);
            mp[x][y]=1;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!mp[i][j]){
                    if((i+j)%2) node1[++odd]=Node(i,j);
                    else node2[++even]=Node(i,j);
                }
            }
        }
        for(int i=1;i<=even;i++){
            for(int j=1;j<=odd;j++){
                if(judge(i,j))
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=even;i++){
            if(dfs(i,i)) ans++;
        }
        printf("%d\n",ans);
        for(int i=1;i<=odd;i++){
            if(!match[i]) continue;
            printf("(%d,%d)--(%d,%d)\n",node2[match[i]].x,node2[match[i]].y,node1[i].x,node1[i].y);
        }
    }
    return 0;
}
*/

/*
//ac 31ms
//另一种记录坐标 除取余的办法 (i-1)*m+j-1
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

int n,m,k,ans,mp[N][N],vis[N],match[N],seq[N],cnt;
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

void init(){
    cnt=ans=0;
    memset(mp,-1,sizeof(mp));
    memset(match,0,sizeof(match));
    for(int i=1;i<=50;i++) G[i].clear();
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        scanf("%d",&k);//n*m网格有k个池塘
        while(k--){
            scanf("%d%d",&x,&y);
            mp[x][y]=0;//标记池塘为0
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp[i][j] == -1){//土地为-1
                    //记录mp[i][j]表示的点的编号为cnt
                    //编号为cnt的点对应的x坐标i,y坐标为j,x=seq[cnt]/m+1,y=seq[cnt]%m+1
                    //seq[cnt]编号为cnt的点对应的坐标映射值为(i-1)*m+j-1 方便输出匹配点对的坐标
                    seq[++cnt]=(i-1)*m+j-1;
                    mp[i][j]=cnt;
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!((i+j)%2)) continue;//只建坐标之和为奇数的点发出的单向边 考虑四个方向
                if(j<m && mp[i][j+1])
                    G[mp[i][j]].push_back(mp[i][j+1]);
                if(i<n && mp[i+1][j])
                    G[mp[i][j]].push_back(mp[i+1][j]);
                if(j>1 && mp[i][j-1])
                    G[mp[i][j]].push_back(mp[i][j-1]);
                if(i>1 && mp[i-1][j])
                    G[mp[i][j]].push_back(mp[i-1][j]);
            }
        }
        for(int i=1;i<=cnt;i++){
            //if((seq[i]/m+seq[i]%m)%2 == 0) continue;//偶数点实际是没有建边的
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;//偶数点并没有建立边 所以枚举时会直接退出
        }
        printf("%d\n",ans);
        int x1,y1,x2,y2;
        for(int i=1;i<=cnt;i++){
            if(!match[i]) continue;//cnt个点只有坐标之和为偶数的点match才有值 i的配对点编号为match[i]
            //因为seq[cnt]=(i-1)*m+j-1
            x1=seq[match[i]]/m+1;
            y1=seq[match[i]]%m+1;
            x2=seq[i]/m+1;
            y2=seq[i]%m+1;
            printf("(%d,%d)--(%d,%d)\n",x1,y1,x2,y2);
        }
    }
    return 0;
}
*/
