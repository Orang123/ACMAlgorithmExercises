/*
题意:Michael喜欢滑雪百这并不奇怪,因为滑雪的确很刺激.可是为了获得速度,
滑的区域必须向下倾斜,而且当你滑到坡底,你不得不再次走上坡或者等待升降机来载你.
Michael想知道载一个区域中最长底滑坡.区域由一个二维数组给出.数组的每个数字代表点的高度.
下面是一个例子
1  2  3  4  5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
一个人可以从某个点滑向上下左右相邻四个点之一,当且仅当高度减小.在上面的例子中,
一条可滑行的滑坡为24-17-16-1.当然25-24-23-...-3-2-1更长.事实上,这是最长的一条.
输入的第一行表示区域的行数R和列数C(1 <= R,C <= 100)。下面是R行，每行有C个整数，代表高度h，0<=h<=10000。
输出最长区域的长度。
注意:实际题目问的是最多所能走的点的个数
链接:http://poj.org/problem?id=1088
思路:关于记忆化搜索、动态规划、贪心解释很好的博客:https://blog.csdn.net/Harington/article/details/86534326
记忆化搜索 递归地从目标状态(不能走的状态)向初始状态转移,已经搜索
过的重叠子问题直接返回dp[x][y]这个结果就行.
dp[x][y]表示从(x,y)点出发走到不能再走的位置最多所能走的点的个数
*/
//ac 16ms 记忆化搜索 递归地从目标状态(不能走的状态)向初始状态(1,1)转移
//dp[x][y]表示从(x,y)点出发走到不能再走的位置最多所能走的点的个数
//时间复杂度O(n*m)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int map[105][105],k,n,m;
int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int dp[105][105];
bool check(int x,int y){
    if(x<0||x>n-1||y<0||y>m-1)
        return false;
    return true;
}
//记忆化搜索决定已经搜索过的路径没必要重复搜索，剪枝对搜索的路径做出决策，不好的搜索路径应舍弃
int dfs(int x,int y){
    if(dp[x][y])//因为是记忆化搜索，如果dp[x][y]不为0代表从这点开始所枚举的路径是被搜索过得，不要去重复搜索，那就直接用之前所搜索的值就好
        return dp[x][y];
    int xx,yy,res=0;
    for(int j=0;j<4;j++){//枚举方向
        xx=x+dir[j][0];
        yy=y+dir[j][1];
        if(check(xx,yy)&&map[xx][yy]<map[x][y]){
            res=max(dfs(xx,yy),res);//类似dp中的状态转移方程，取max的决策方案
        }
    }
    dp[x][y]=res+1;//因为求解的是滑坡的最大长度
    return dp[x][y];
}
int main(){
    int res=0;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&map[i][j]);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            res=max(res,dfs(i,j));
        printf("%d\n",res);
    return 0;
}

/*
//ac 16ms 我为人人型的动态规划
//参考博客:https://blog.csdn.net/Harington/article/details/86534326
//这题的本质：我们需要找到一个最长的上升子序列，那我们就可以想，这道题的动态规划的状态方程，
//我们稍加思考，我们如果从下往上推，找到最小的点，然后可以用这个点更新上下左右的点，如果从
//这个点到上下左右4个点的上升序列比 这4个点本身的上升序列 变长了就更新并记录。直到找到最大值。
//第一步，我们需要将所有的点按 递增序列排序。
//第二步，我们从最低点更新上下左右的4个点，直到每给个点都用了。
//第三步，输出我们找的过程中的最大值。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int map[105][105],k,n,m;
int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int dp[105][105];
struct Node{
    int x,y,h;
    bool operator <(const Node &x)const{
        return h<x.h;
    }
}node[11000];
bool check(int x,int y){
    if(x<0||x>n-1||y<0||y>m-1)
        return false;
    return true;
}
int main(){
    int len=0;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&map[i][j]);
            node[len++]=(Node){i,j,map[i][j]};
            dp[i][j]=1;
        }
    }
    //按照高度从小到大排序,因为dp前面的结果必须更新到不能再更新为止,才能去更新后面的结果
    sort(node,node+len);
    int x0,y0,ans=1;
    //从高度小的向高度高的dp,才能求得可走的最长的路径
    for(int i=0;i<len;i++){
        int x=node[i].x;
        int y=node[i].y;
        for(int k=0;k<4;k++){
            x0=x+dir[k][0];
            y0=y+dir[k][1];
            if(!check(x0,y0)) continue;
            if(map[x0][y0]<=node[i].h) continue;//因为是从高点向低点走的
            if(dp[x0][y0]>=dp[x][y]+1) continue;
            dp[x0][y0]=dp[x][y]+1;
            ans=max(ans,dp[x0][y0]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
*/

/*
//ac 16ms 人人为我型 动态规划
//参考博客:https://blog.csdn.net/Harington/article/details/86534326
//这种给记忆化搜索差不多，你的目的是求每一个结点的最长升子序列，那你这个点的值取决什么呢？
//是不是取决与他上下左右4个点的最长上升子序列，那用递归就好写了，但是把他转化成动态规划，
//这个思路就是找到状态方程，那我们把这个问题分解，就是求每个点的上升子序列，那我们找到边界，
//就是最低的那个点。这个人人为我型和我为人人型的唯一不一样就是这里，我为人人型 是用这个点更新其他4个点，
//而人人为我型就是用周围4个点更新这个一个点。找到一个周围4个点没法更新他的，不就是最低的那个点么？
//我们就想出了这个状态方程，从边界往上推，直到推到最后一个点（最高的点）
//第一步，先进行点排序递增排序。
//第二步，找到最小的点，用上下左右的点更新他，然后次小，一直到最大，（排完序后一个循环就OK）
//第三步，找的过程中记录每个点的状态，并找到最大值.
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
	int n ,m;
struct node{
	int x;
	int y;
	int data;
};

bool cmp(node a, node b){
	return a.data < b.data;
}

bool check(int x, int y){
	if( x >= 1 && y >= 1 && x <= n && y <= m)
		return 1;
	else
		return 0;
}

int main (){

	int high[105][105];
	int maxLen[105][105];
	int to[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int ans = 1;
	cin >> n >> m;
	int k = 0;
	node s[10006];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &high[i][j]);
			s[++k].data = high[i][j];
			s[k].x = i;
			s[k].y = j;
			maxLen[i][j] = 1;
		}
	}
	sort(s + 1, s + k + 1, cmp);
	for(int i = 1 ; i <= k; i++){
		int x1, y1;

		for(int j = 0; j < 4; j++){
			int x = s[i].x;
			int y = s[i].y;
			x1 = x + to[j][0];
			y1 = y + to[j][1];
			if(check(x1, y1)){
				if(high[x][y] > high[x1][y1]){
					maxLen[x][y] = max(maxLen[x1][y1] + 1, maxLen[x][y]);
					ans = max(ans, maxLen[x][y]);
				}
			}
		}
	}
	cout << ans <<  endl;
	return 0;
}
*/

/*
//dfs暴力搜索 类背包dp阶段性剪枝 TLE
//这个做法 很明显会超时,因为每次的起点都不同,每次搜索都需要初始化dp数组重新计算
//dp[x][y]表示从出发点到达(x,y)最多所走的路径长度
//剪枝1 如果当前从(1,1)出发所走的路径长度不比之前到达(x,y)更长 就不必再搜索下去

//为啥一定要 从结束状态向初始状态推最优解主要原因是:
//如果从初始状态 推所走到状态的最优解,它这个 还是会往下继续搜索的,而且先搜索到的还不一定是最优,
//剪枝的高效性就无法保证,而终止状态去逆推,因为已经停下了,不能再往下继续搜索了,就不会重复搜索,
//而且它是保证了对于子阶段的状态已经就是最优的了,所以才更高效吧.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,mp[N][N],dp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ans;

void dfs(int x,int y,int sum){
    if(sum<=dp[x][y])//剪枝1 如果当前从(1,1)出发获得奶酪不比之前获得的多 就不必再搜索下去
        return;
    dp[x][y]=sum;
    ans=max(ans,sum);
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>n || ny<1 || ny>n)
            continue;
        if(mp[nx][ny]>=mp[x][y])
            continue;
        dfs(nx,ny,sum+1);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            //这个做法 很明显会超时,因为每次的起点都不同,每次搜索都需要初始化dp数组重新计算
            memset(dp,0,sizeof(dp));
            dfs(i,j,1);
        }
    }
    printf("%d\n",ans);
    return 0;
}
*/
