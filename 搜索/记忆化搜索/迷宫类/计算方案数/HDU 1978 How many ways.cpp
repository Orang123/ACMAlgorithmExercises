/*
题意:这是一个简单的生存游戏，你控制一个机器人从一个棋盘的起始点(1,1)走到棋盘的终点(n,m)。游戏的规则描述如下：
1.机器人一开始在棋盘的起始点并有起始点所标有的能量。
2.机器人只能向右或者向下走，并且每走一步消耗一单位能量。
3.机器人不能在原地停留。
4.当机器人选择了一条可行路径后，当他走到这条路径的终点时，他将只有终点所标记的能量。
如上图，机器人一开始在(1,1)点，并拥有4单位能量，蓝色方块表示他所能到达的点，如果他
在这次路径选择中选择的终点是(2,4)点，当他到达(2,4)点时将拥有1单位的能量，并开始
下一次路径选择，直到到达(6,6)点。我们的问题是机器人有多少种方式从起点走到终点。
这可能是一个很大的数，输出的结果对10000取模。
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1978
思路:正向从初始状态向到达点对转移方案数,会导致重复计数,因此从目标状态向起始状态转移
方案数,不会重复计算方案数,已经搜索过的状态直接返回结果即可.
*/
//ac 249ms 记忆化搜索 从目标状态(n,m)向起始状态(1,1)转移方案数
//时间复杂度O(n*m)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define mod 10000
using namespace std;

int n,m,mp[N][N],dp[N][N];

int dfs(int x,int y){
    if(dp[x][y])
        return dp[x][y];
    int nx,ny;
    int k=mp[x][y];
    for(int i=0;i<=k;i++){
        for(int j=0;j<=k;j++){
            nx=x+i;
            ny=y+j;
            //不能停留在原点,跳跃的总步数要小于方格上的能量(曼哈顿距离)
            if(i+j==0 || i+j>k || nx>n || ny>m) continue;
            dp[x][y]=(dp[x][y]+dfs(nx,ny))%mod;
        }
    }
    return dp[x][y];
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        dp[n][m]=1;//这条路径若能到达终点则算一种方案
        printf("%d\n",dfs(1,1));
    }
    return 0;
}

/*
//ac 171ms 正向dp 先枚举行 再枚举列
//dp[i][j]表示到达(i,j)点对时的方案总数
//实际初始点是从(1,1)开始按照x 1..n,y 1..m的顺序遍历,方向 右下,
//不会出现某个点没有遍历的情况,前提是格子上的数字不能为0,就是说下一个点肯定都是由之前的状态扩展过的
//否则就会出现所枚举的点因为没有扩展而被遗漏的情形,如果初始点在中间或别的位置,枚举的点对(x,y)有可能还没
//扩展过,就被停止,那这个点的状态就没有计算,最终结果就是错的.
//实际也不会重复计算方案数,因为从dp[x][y]开始扩展开始,之后不会有点能扩展到dp[x][y],因为只能走右或下,因此方案不会重复计数.
//但是直接dfs搜索从初始点到(x,y)的方案数,这会导致重复计数.
#include<cstdio>
#include<iostream>
#include<cstring>
#define mod 10000
using namespace std;

int n,m,mp[110][110],dp[110][110];

int judge(int x,int y){
    if(x<=n && y<=m) return 1;
    else return 0;
}

int main () {
    int T;
	scanf("%d", &T);
	while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        dp[1][1]=1;//从起点开始是一种方案
        //动态规划 不需要再额外判断是否重复遍历,因为本身就是尽可能多地枚举所能到达的点,这些点就是因为相同,才能更新方案数
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int step=mp[i][j];
                //当前点对如果还没到达过,则不扩展状态,实际初始点是(1,1)
                //按照x 1..n,y 1..m的顺序遍历不会出现某个点没有遍历的情况,前提是格子上的数字不能为0
                //if(!dp[i][j]) continue;//实际如果出现这种情况,答案一定是错的
                for(int k=0;k<=step;k++){//枚举从该点mp[i][j]出发所能到达的mp[i+k][j+h]
                    for(int h=0;h<=step;h++){
                        if(k+h==0 || k+h>step || !judge(i+k,j+h)) continue;
                        //从起点开始,规划到达mp[i+k][j+h]需要的方案数dp[i+k][j+h]+dp[i][j],从不同的点出发能到达相同的点,这样到达某个终点就有多种方案
                        dp[i+k][j+h]=(dp[i+k][j+h]+dp[i][j])%mod;
                    }
                }
            }
        }
        printf("%d\n",dp[n][m]);
	}
	return 0;
}
*/

/*
//ac 171ms 正向dp,先枚举列 再枚举行
#include<cstdio>
#include<iostream>
#include<cstring>
#define mod 10000
using namespace std;

int n,m,mp[110][110],dp[110][110];

int judge(int x,int y){
    if(x<=n && y<=m) return 1;
    else return 0;
}

int main () {
    int T;
	scanf("%d", &T);
	while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        dp[1][1]=1;//从起点开始是一种方案
        //动态规划 不需要再额外判断是否重复遍历,因为本身就是尽可能多地枚举所能到达的点,这些点就是因为相同,才能更新方案数
        for(int j=1;j<=m;j++){
            for(int i=1;i<=n;i++){
                int step=mp[i][j];
                for(int k=0;k<=step;k++){//枚举从该点mp[i][j]出发所能到达的mp[i+k][j+h]
                    for(int h=0;h<=step;h++){
                        if(k+h==0 || k+h>step || !judge(i+k,j+h)) continue;
                        //从起点开始,规划到达mp[i+k][j+h]需要的方案数dp[i+k][j+h]+dp[i][j],从不同的点出发能到达相同的点,这样到达某个终点就有多种方案
                        dp[i+k][j+h]=(dp[i+k][j+h]+dp[i][j])%mod;
                    }
                }
            }
        }
        printf("%d\n",dp[n][m]);
	}
	return 0;
}
*/
