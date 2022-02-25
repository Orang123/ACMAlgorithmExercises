#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 850
using namespace std;
//ac 219ms 二维01背包
//和UVA12099 类似
/*
题意:给出了n个围栏段,现在要将这些围栏段拼凑成三段,不能有剩余
使得三段长度能构成一个三角形,求能构成的最大面积,不能构成三角形
输出-1.
链接:http://poj.org/problem?id=1948
思路:类似UVA 12099,只要确定出2条边的长度,第三条边就能确定.
dp[i][j][k]代表前i个围栏段拼凑出第一条边长度为j,第二条边长度
为k,这样第三条边就是(围栏段总长度-j-k),注意此时dp[i][j][k]并
不能代表该三条边能构成合法的三角形,还需要再次判断.实际滚动数组
优化掉了第一维度i,只有二维dp[j][k].
*/
int n,li[N],dp[M][M],sum;

//任意两边之长均大于第三边 才能构成三角形
int check(int a,int b,int c){
    return a+b>c && b+c>a && a+c>b;
}

int cal(int a,int b,int c){
    double p=sum/2.0;//海伦公式 周长的一般 要用浮点数求精确值 用int会wa
    return sqrt(p*(p-a)*(p-b)*(p-c))*100;
}

int main(){
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++){
        scanf("%d",&li[i]);
        sum+=li[i];
    }
    int len=sum/2;
    dp[0][0]=1;//恰好装满背包
    for(int i=1;i<=n;i++){
        //注意j k都必须降序 才能保证dp[j-li[i]][k] dp[j][k-li[i]]是前i-1个围栏段的状态
        // j k的下界都是0 这样才会遍历到初始状态dp[0][0]
        for(int j=len;j>=0;j--){
            for(int k=len;k>=0;k--){
                //第i个围栏段拼接到第1条边或第2条边 只要其中一条成立 则dp[i][j][k]合法
                if((j>=li[i] && dp[j-li[i]][k]) || (k>=li[i] && dp[j][k-li[i]]))
                    dp[j][k]=1;
            }
        }
    }
    int ans=-1;
    for(int i=1;i<=len;i++){
        for(int j=1;j<=len;j++){
            if(dp[i][j] && check(i,j,sum-i-j))
                ans=max(ans,cal(i,j,sum-i-j));
        }
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 532ms 记忆化搜索+剪枝
//这个对重复阶段的标记,严格来说不能说成记忆化搜索,因为这只是说当前阶段之前搜索过了,
//但是它并不构成某个新的方案的子问题,就是说并没有dp阶段性,子问题构成大问题的组合这个想法
//真正意义上的记忆化搜索,往往是把重叠子问题的方案数值 记录下来,等到重复搜索到的时候直接返回这个值,它具备dp的最优子结构性质.
//而这里只是单纯的对搜索重复状态的剪枝.
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 550
using namespace std;
int n,li[N],sum,ans;
bool vis[N][M][M];

int check(int a,int b,int c){
    return a+b>c && b+c>a && a+c>b;
}

int cal(int a,int b,int c){
    double p=sum/2.0;
    return p*(p-a)*(p-b)*(p-c);
}

void dfs(int k,int a,int b,int c){
    if(vis[k][a][b]) return;//第k个物品 已经选定2条边的长度 a、b这个状态之前已经搜索过,那么之后必然是重复的搜索 返回
    vis[k][a][b]=1;//标记这种状态已访问过
    //剪枝 三角形每条边的长度 都不能超过周长的一半
    //还可以根据均值不等式剪枝 即只判断a>sum/3,因为三角形面积最大的情况是三条边长最接近的时候 证明在此:https://www.zybang.com/question/58b4e6b1be64233113578c3d1e1a9c99.html
    //但注意只能判断一条边a>sum/3.其余两条边不能判,因为实际可能并不能刚好凑出等边三角形,必然可能有1或2条边都大于sum/3,否则会导致不能遍历到所有情况
    if(a>sum/2 || b>sum/2 || c>sum/2) return;
    if(k == n+1){//所有的围栏都选完 判断是否构成三角形
        if(check(a,b,c))
            ans=max(ans,cal(a,b,c));//这里注意利用海伦公式计算时先别直接开方进行泰勒级数展开,只记录要开方的最大值,能减少复杂度
        return;
    }
    dfs(k+1,a+li[k],b,c);//将第k个围栏拼到第1条边
    dfs(k+1,a,b+li[k],c);//将第k个围栏拼到第2条边
    dfs(k+1,a,b,c+li[k]);//将第k个围栏拼到第3条边
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&li[i]);
        sum+=li[i];
    }
    ans=-1;
    dfs(0,0,0,0);
    if(ans!=-1)//有合法三角形
        printf("%d",(int)(sqrt(ans)*100));
    else
        printf("-1");
    return 0;
}
*/
