/*
题意:n*m的网格,网格上的数字为权重,要求从最左边的一列任意位置到
最右边的一列任意位置,并且实际网格第一行和最后一行是相邻的,即:
从第一行向上走到第0行,实际是走到了第n行,从第n行走到第n+1行,实际
是走到了第1行,共有三种走法,分别是斜向上、向前、斜向下,
求出最小的权重的路径,输出路径经过的行号(按字典序)和最小路径的权值.
1<=n<=10,1<=m<=100.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1619
思路:记忆化搜索,三个方向y值都增大,并且不会重复往回走,无需判重.
dp[x][y]表示从(x,y)出发到达(?,m)(最后一列任意位置)路径上最小的权重和,
注意目标状态不是(n,m)而是只要y==m,到达最后一列即可,而且初始状态也不是
(1,1),而是要枚举(x,1),1<=x<=n,求出最短的路径权值.
*/
//ac 0ms 记忆化搜索
//dp[x][y]表示从(x,y)出发到达(?,m)(最后一列任意位置)路径上最小的权重和
#include<cstring>
#include<algorithm>
#define N 12
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dx[3]={-1,0,1},dp[N][M],mp[N][M],path[M],ans,p,l;

//求出最短路径权值
int dfs(int x,int y){
    if(dp[x][y]!=INF)
        return dp[x][y];
    if(y == m)
        return dp[x][y]=mp[x][y];
    int nx,ny;
    for(int i=0;i<3;i++){
        nx=x+dx[i];
        ny=y+1;//三个方向y值都加1
        if(!nx)//从第一行走到第n行
            nx=n;
        else if(nx == n+1)//从第n行走到第1行
            nx=1;
        dp[x][y]=min(dp[x][y],dfs(nx,ny)+mp[x][y]);
    }
    return dp[x][y];
}

//记录最短路径的行号
void findPath(int x,int y){
    path[++l]=x;//当前路径行号为x
    if(y == m)//到达最后一列 m列时 终止返回
        return;
    int nx;
    vector<int> a;
    for(int i=0;i<3;i++){
        nx=x+dx[i];
        if(!nx)
            nx=n;
        else if(nx == n+1)
            nx=1;
        a.push_back(nx);//将行号记录下来 从小到达排序
    }
    sort(a.begin(),a.end());//当路径不唯一时,按照字典序输出
    for(int i=0;i<a.size();i++){
        if(dp[x][y] == dp[a[i]][y+1]+mp[x][y]){
            findPath(a[i],y+1);
            return;
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        ans=INF;
        l=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            if(ans>dfs(i,1)){
                ans=dp[i][1];//记录最大的权重ans和出发的行号p
                p=i;
            }
        }
        findPath(p,1);//记录最小权重路径的行号
        printf("%d",path[1]);
        for(int i=2;i<=l;i++)
            printf(" %d",path[i]);
        printf("\n%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms 正向dp,由第一列向最后一列转移
//dp[x][y]表示从(?,1)第一列任意位置出发到达(x,y) 路径上最小的权重和
//注意这个做法 dp的阶段应该定义为列,而不能是行,因为按照题意初始状态是
//在第一列的任意位置出发,所以不能将第一行设置为初始状态,这样最小权值会出错,
//初始权值并不是第一行网格位置本身的权值,只能由第一列转移而来,而且当以行作为dp的阶段时,第2、3..n行的第一列的路径
//并没有初始状态 也无法转移
#include<cstring>
#include<algorithm>
#include<vector>
#define N 12
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dx[3]={-1,0,1},dp[N][M],mp[N][M],ans,p,pre[N][M];
vector<int> a;

void printPath(int x,int y){
    if(y == 1){
        printf("%d",x);
        return;
    }
    else{
        printPath(pre[x][y],y-1);//上一个位置是(pre[x][y],y-1),列号必然是减1的
        printf(" %d",x);
    }
}

int main(){
    int nx;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        ans=INF;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=n;i++)
            dp[i][1]=mp[i][1];//初始状态 是第一列网格位置的权值
        for(int j=1;j<m;j++){//将列作为dp的阶段
            for(int i=1;i<=n;i++){//枚举行 做转移
                a.clear();
                for(int k=0;k<3;k++){//将转移的行按照从小到大排序 进行转移
                    nx=i+dx[k];
                    if(!nx)
                        nx=n;
                    else if(nx == n+1)
                        nx=1;
                    a.push_back(nx);
                }
                sort(a.begin(),a.end());
                for(int k=0;k<a.size();k++){
                    if(dp[i][j]+mp[a[k]][j+1]<dp[a[k]][j+1]){
                        dp[a[k]][j+1]=dp[i][j]+mp[a[k]][j+1];
                        pre[a[k]][j+1]=i;//记录到达(a[k],j+1)位置的上一状态的 行号,前一状态的列号一定是y-1 无需记录
                    }
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(ans>dp[i][m]){
                ans=dp[i][m];
                p=i;//记录到达第m列 路径权值最小的行号,方便从目标位置往回输出直到第一列为止
            }
        }
        printPath(p,m);
        printf("\n%d\n",ans);
    }
    return 0;
}
*/
