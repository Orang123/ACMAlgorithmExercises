/*
题意:摘自网上
给出2*n个选手的坐标，要求将所有的选手分成n组，每组两个人，
所有组的两个人之间的距离之和要最小，输出最小值。
n<=8.
链接:https://www.luogu.com.cn/problem/UVA10911
思路:需要枚举出所有的组合情况,比较求出最小距离和.可以一次枚举1组2个人,
每次已经确定的组用二进位的状态来表示,但是对于同样是选编号是1、2、3、4
的人,组合情况可能是(1,2),(3,4)也可能是(1,3),(2,4)等,也就是对于已选人相同
但是组合不同的情况,对于剩余未选的人间的最短距离是个重叠子问题,
因此记忆化搜索+状态压缩对重叠子问题判重.
dp[sta]表示已选学生二进制位状态为sta时,未选学生配对时各组学生最短的距离之和.
结束状态是当所有人都被分配进组时,即sta == (1<<n)-1.
*/
//ac 160ms 记忆化搜索+状压
//dp[sta]表示已选选手二进制位状态为sta时,未选学生配对时各组学生最短的距离之和
//时间复杂度O(1<<16-1)
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 1e40
using namespace std;

int n;
double dis[N][N],x[N],y[N],dp[1<<16];
char str[N];

double calDis(int i,int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

double dfs(int sta){
    if(dp[sta]!=INF)
        return dp[sta];
    if(sta == (1<<n)-1)
        return 0;
    for(int i=0;i<n;i++){//一次枚举两人
        if(sta & 1<<i)//第i个人已确认分组
            continue;
        for(int j=i+1;j<n;j++){
            if(sta & 1<<j)//第j个人已确认分组
                continue;
            dp[sta]=min(dp[sta],dfs(sta|(1<<i)|(1<<j))+dis[i][j]);
        }
    }
    return dp[sta];
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        n<<=1;//n对人,乘以2才是总人数
        for(int i=0;i<(1<<16);i++)
            dp[i]=INF;
        for(int i=0;i<n;i++)
            scanf("%s%lf%lf",str,&x[i],&y[i]);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++)
                dis[i][j]=calDis(i,j);//dis[i][j]表示选手i与选手j之间的距离
        }
        printf("Case %d: %.2f\n",cas,dfs(0));//初始时,一个选手也没选,状态为0
    }
    return 0;
}

/*
//ac 160ms 记忆化搜索+状压
//dp[sta]表示未选选手二进制位状态为sta时,未选学生配对时各组间学生最短的距离之和
//时间复杂度O(1<<16-1)
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 1e40
using namespace std;

int n;
double dis[N][N],x[N],y[N],dp[1<<16];
char str[N];

double calDis(int i,int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

double dfs(int sta){
    if(dp[sta]!=INF)
        return dp[sta];
    if(!sta)
        return 0;
    for(int i=0;i<n;i++){
        if(!(sta & 1<<i))//不在未选状态 说明已选
            continue;
        for(int j=i+1;j<n;j++){
            if(!(sta & 1<<j))
                continue;
            dp[sta]=min(dp[sta],dfs(sta^(1<<i)^(1<<j))+dis[i][j]);//异或取消未选状态
        }
    }
    return dp[sta];
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        n<<=1;
        for(int i=0;i<(1<<16);i++)
            dp[i]=INF;
        for(int i=0;i<n;i++)
            scanf("%s%lf%lf",str,&x[i],&y[i]);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++)
                dis[i][j]=calDis(i,j);//dis[i][j]表示选手i与选手j之间的距离
        }
        printf("Case %d: %.2f\n",cas,dfs((1<<n)-1));//初始时一个选手也未分配,状态为(1<<n)-1
    }
    return 0;
}
*/

/*
//ac 70ms 正向dp
//刘汝佳习题集上的官方解法
//摘自博客:https://blog.csdn.net/tianwei0822/article/details/94491501
#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 1010;
int x[maxn], y[maxn];
double d[1<<16];
double dis(int a,int b){
    return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}
int n, kase;
int main(){
	while(scanf("%d", &n) == 1 && n){
		char s[maxn];
		n <<= 1;
		for(int i = 0; i < n; ++i){scanf("%s%d%d", s, &x[i], &y[i]);}
		d[0] = 0;
		for(int S = 1; S < (1 << n); ++S){
			d[S] = INF;
			int i, j;
			for(i = 0; i < n; ++i) if(S & (1 << i)) break;
			for(j = i + 1; j < n; ++j) if(S & (1 << j)) d[S] = min(d[S], dis(i, j) + d[S ^ (1 << i) ^ (1 << j)]);
		}
		printf("Case %d: %.2lf\n", ++kase, d[(1 << n) - 1]);
	}
	return 0;
}
*/
