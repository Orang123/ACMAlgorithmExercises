/*
题意:
"Help Jimmy" 是在下图所示的场景上完成的游戏
场景中包括多个长度和高度各不相同的平台。地面是最低的平台，高度为零，长度无限。
Jimmy老鼠在时刻0从高于所有平台的某处开始下落，它的下落速度始终为1米/秒。
当Jimmy落到某个平台上时，游戏者选择让它向左还是向右跑，它跑动的速度也是1米/秒。
当Jimmy跑到平台的边缘时，开始继续下落。Jimmy每次下落的高度不能超过MAX米，不然就会摔死，游戏也会结束。
设计一个程序，计算Jimmy到底地面时可能的最早时间。
1 <= N <= 1000，-20000 <= X, X1[i], X2[i] <= 20000，0 < H[i] < Y <= 20000（i = 1..N）
链接:http://poj.org/problem?id=1661
思路:每次下落时,必然只能从当前高度的台子的左侧或右侧,下落到低于当前台子的最高高度的
台子上,然后再走到这个台子的左侧或右侧,再接着下一个台子继续往下降,如果下面还有别的台子
能接住人,就不能直接下落到地面,除非当前x坐标不再下面任何一个台子的坐标范围内,则可以直接
下落到地面.整个过程整体下落的高度是固定的,不同点是从一个台子降落到另一个台子,可以选择
走左侧或走右侧,这两侧的距离是不同的.而且从高度不同的台子往下落,可能会落到同一个台子的同一侧,
因此对于某个台子的左侧或右侧有可能会被重复搜索到,而不同台子降落到地面需要的最少时间与前面的
较高层的台子无关,因此存在最优子结构、重叠子问题,显然记忆化搜索.
首先要对台子降序排列.
dp[k][0]表示第k大的台子从左侧降落落到地面所花的最少时间
dp[k][1]表示第k大的台子从右侧降落落到地面所花的最少时间
dp[k][d]=INF,表示在降落高度限制为maxh下无解,dp[k][d]=-1表示初始状态,还未更新.
其余值均表示有解
*/
//ac 0ms 记忆化搜索
//时间复杂度(1000*2)=2000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,maxh,x1[N],x2[N],h[N],dp[N][2];

struct Node{
    int x1,x2,h;
    bool operator <(const Node &x)const{
        return h>x.h;//按照高度降序排列
    }
}node[N];

int dfs(int x,int k,int d){//当前在第k个台子上
    if(dp[k][d] != -1)
        return dp[k][d];
    dp[k][d]=INF;//INF无解也需要记录
    for(int i=k+1;i<=n+1;i++){
        //当前第k个台子位置的横坐标在第i个台子的左右侧范围内 且高度不超过maxh 即可降落
        if(i!=n+1 && x>=node[i].x1 && x<=node[i].x2 && node[k].h-node[i].h<=maxh){
            //x-node[i].x1移动到第i个台子左侧,node[i].x2-x移动到第i个台子右侧,降落高度都是node[k].h-node[i].h
            dp[k][d]=min(x-node[i].x1+dfs(node[i].x1,i,0),node[i].x2-x+dfs(node[i].x2,i,1))+node[k].h-node[i].h;
            //找第一个满足条件的最高的台子降下,就结束,不结束的话这里会直接判断到n+1直接落到地面,
            //但中间是有台子会接住它,需要横向移动才能继续往下降的
            break;
        }
        if(i == n+1 && node[k].h<=maxh)//当前面台子都不在第k个台子降落范围时,即可直接降落到地面
            dp[k][d]=node[k].h;
    }
    return dp[k][d];
}

int main(){
    int T,x,y;
    scanf("%d",&T);

    while(T--){
        memset(dp,-1,sizeof(dp));
        scanf("%d%d%d%d",&n,&x,&y,&maxh);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&node[i].x1,&node[i].x2,&node[i].h);
        sort(node+1,node+1+n);
        node[0].h=y;//初始高度为y
        printf("%d\n",dfs(x,0,0));
    }
    return 0;
}

/*
//ac 47ms dfs+剪枝
//dp[k][0]表示从初始高度降落到第k大的台子左侧所花的最少时间
//dp[k][1]表示从初始高度降落到第k大的台子右侧所花的最少时间
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,maxh,x1[N],x2[N],h[N],dp[N][2],ans;

struct Node{
    int x1,x2,h;
    bool operator <(const Node &x)const{
        return h>x.h;
    }
}node[N];

void dfs(int x,int pre,int k,int time){
	if(k == n+1){
		if(node[pre].h<=maxh && time+node[pre].h<ans)
			ans=time+node[pre].h;
		return;
	}
	if(time>=ans)
		return;
	if(x>=node[k].x1 && x<=node[k].x2 && node[pre].h-node[k].h<=maxh){
		time+=node[pre].h-node[k].h;
		if(x-node[k].x1+time<dp[k][0]){//剪枝:如果当前方案 不能比之前更优则不进行搜索
			dp[k][0]=x-node[k].x1+time;
			dfs(node[k].x1,k,k+1,dp[k][0]);
		}
		if(node[k].x2-x+time<dp[k][1]){
			dp[k][1]=node[k].x2-x+time;
			dfs(node[k].x2,k,k+1,dp[k][1]);
		}
	}
	else//第k个不满足降落条件 判断下一个
		dfs(x,pre,k+1,time);
}

int main(){
    int T,x,y;
    scanf("%d",&T);
    while(T--){
    	ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d%d%d",&n,&x,&y,&maxh);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&node[i].x1,&node[i].x2,&node[i].h);
        sort(node+1,node+1+n);
        node[0].h=y;
        dfs(x,0,1,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/
