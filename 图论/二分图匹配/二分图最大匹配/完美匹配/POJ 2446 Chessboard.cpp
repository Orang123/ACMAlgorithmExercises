#include<cstdio>
#include<cstring>
#define N 40
using namespace std;
//ac 16ms 矩形网格奇偶划分二分图+匹配数*2是否等于非空洞数(n*m-k)
/*
题意:n*m的矩形网格,一些格子时空洞,现在要用1*2或2*1的小矩形
覆盖非空洞的网格,问是否能将非空洞的格子全部覆盖,若能输出"YES",
否则输出"NO".
链接:http://poj.org/problem?id=2446
思路:奇偶划分矩形网格的二分图集合求解最大匹配,很明显全部覆盖非空洞
的格子时,所有的非空洞的点都要包含在匹配中的边集,如果最大匹配*2==所有非空洞的格子,
则输出"YES",否则"NO".
还可通过判断是否完美匹配来判断是匹配边集是否能覆盖所有非空洞点.
*/

int n,m,k,cnt,mp[N][N],odd,even,head[N*N],vis[N*N],match[N*N],ans;
struct Edge{
    int to,next;
}edge[N*N*4];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
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
    odd=even=ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(mp,-1,sizeof(mp));
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v;
    //int num=0;
    init();
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++){
        scanf("%d%d",&u,&v);
        mp[v][u]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!mp[i][j]) continue;
            //num++;
            if((i+j)%2) mp[i][j]=++odd;
            else mp[i][j]=++even;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!mp[i][j] || (i+j)%2 == 0) continue;
            if(i<n && mp[i+1][j])
                addEdge(mp[i][j],mp[i+1][j]);
            if(j<m && mp[i][j+1])
                addEdge(mp[i][j],mp[i][j+1]);
            if(i>1 && mp[i-1][j])
                addEdge(mp[i][j],mp[i-1][j]);
            if(j>1 && mp[i][j-1])
                addEdge(mp[i][j],mp[i][j-1]);
        }
    }
    for(int i=1;i<=odd;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }
    //if(ans*2 == num) printf("YES");//也可以预先统计出非空洞点的个数num
    if(ans*2 == n*m-k) printf("YES");//一个匹配边含2个非空洞点 要乘2,总共n*m个点,k个空洞,非空洞n*m-k
    else printf("NO");
    return 0;
}

/*
//ac 16ms 奇偶性质划分+判断是否完美匹配
//需要先判断奇偶两集合点数是否相等,不相等不存在完美匹配,
//相等再进一步匈牙利判断每个点是否有配对点,若都有则是完美匹配.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;

int n,m,k,cnt,mp[N][N],odd,even,head[N*N],vis[N*N],match[N*N],ans;
struct Edge{
    int to,next;
}edge[N*N*4];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
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
    odd=even=ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(mp,-1,sizeof(mp));
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v;
    init();
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++){
        scanf("%d%d",&u,&v);//输入表示的是第v行第u列 一个坑点
        mp[v][u]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!mp[i][j]) continue;
            if((i+j)%2) mp[i][j]=++odd;
            else mp[i][j]=++even;
        }
    }
    //如果二分图两集合点数不相等,则不存在完美匹配,因为较大集合中的点必然会有剩余未配对的点.
    if(even != odd){
        printf("NO");
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!mp[i][j] || (i+j)%2 == 0) continue;
            if(i<n && mp[i+1][j])
                addEdge(mp[i][j],mp[i+1][j]);
            if(j<m && mp[i][j+1])
                addEdge(mp[i][j],mp[i][j+1]);
            if(i>1 && mp[i-1][j])
                addEdge(mp[i][j],mp[i-1][j]);
            if(j>1 && mp[i][j-1])
                addEdge(mp[i][j],mp[i][j-1]);
        }
    }
    int flag=0;
    for(int i=1;i<=even;i++){
        memset(vis,0,sizeof(vis));
        if(!dfs(i)){
            flag=1;
            break;
        }
    }
    if(!flag) printf("YES");//如果even集合每个点都有配对点 则是完美匹配.(此时even == odd)
    else printf("NO");//even集合存在未配对的点,则匹配边集无法覆盖所有非空洞网格,必然会有非空洞网格剩余.
    return 0;
}
*/
