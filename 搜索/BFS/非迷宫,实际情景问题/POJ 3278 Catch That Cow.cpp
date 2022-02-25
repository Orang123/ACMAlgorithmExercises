/*
题意:农户和牛在一个数轴上,农户和牛的位置分别为n,k .
牛的位置不变,农户有三种移动方式:
1.从n移动到n+1位置.
2.从n移动到n-1位置.
3.从n移动到2*n位置.
且每种移动方式都需要花费1分钟,问农户最少需要多久能找到他的牛.
1<=n,k<=100000
链接:http://poj.org/problem?id=3278
思路:bfs搜索,对于每个位置都有三种移动方式pos+1,pos-1,pos*2,
三种移动方式对应的剪枝分别是pos+1<=k,pos-1>=0,pos<k.其实不加剪枝
也是可以ac的.
因为bfs对于每个位置都会考虑三种走法的方案同时刻入队,而同时刻的方案
用时是一样的,出队时第一次达到的位置的状态用时一定是最少的,即用vis数组
标记已经扩展过的pos状态不再重复入队.
*/
//ac 16ms bfs
//因为每个位置只会扩展一次 时间复杂度O(max(2*k,10^5))=10^5
#include<cstdio>
#include<queue>
#include<cstring>
#define N 100010
using namespace std;

int n,k,vis[N];
struct State{
    int pos,m;
    State(int pos=0,int m=0):pos(pos),m(m){}
};

int bfs(){
    queue<State> Q;
    vis[n]=1;
    Q.push(State(n,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.pos == k)
            break;
        Q.pop();
        //pos+1 不能超过k 否则还得往回走 无意义
        if(tp.pos+1<=k && !vis[tp.pos+1]){
            vis[tp.pos+1]=1;
            Q.push(State(tp.pos+1,tp.m+1));
        }
        //pos-1的下界至少为0 数组下标不能为负
        if(tp.pos-1>=0 && !vis[tp.pos-1]){
            vis[tp.pos-1]=1;
            Q.push(State(tp.pos-1,tp.m+1));
        }
        //乘以2当前的pos一定不能大于k,否则回到k只会用时更大 注意tp.pos*2<N要加上 不然会RE.n,k<=10^5
        if(tp.pos<k && tp.pos*2<N && !vis[tp.pos*2]){
            vis[tp.pos*2]=1;
            Q.push(State(tp.pos*2,tp.m+1));
        }
    }
    return tp.m;
}

int main(){
    memset(vis,0,sizeof(vis));
    scanf("%d%d",&n,&k);
    printf("%d",bfs());
    return 0;
}

/*
//TLE dfs
//dp[pos]表示达到当前pos位置所用的最少时间
//这里dfs需要用dp[pos]剪枝,因为先行深度搜索到的方案到达的位置用时可能并不是最少的,
//回溯后 后续的走法方案可能使得dp[pos]更少,剪枝:如果后续的方案到达pos时的m用时不能比之前的dp[pos]用时更少就不必搜索下去了
//因为先行走的方案不能保证一定是最少的,有可能前面走的方案都是较大的,所以实际剪枝的效率并不高.
//复杂度O(3^10^5) TLE
#include<cstdio>
#include<queue>
#include<cstring>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,k,dp[N],ans;

//复杂度O(3^10^5) TLE
void dfs(int pos,int m){
    //剪枝:如果后续的方案到达pos时的m用时不能比之前的dp[pos]用时更少就不必搜索下去了
    if(m>=dp[pos])
        return;
    //更新到达pos的最少用时
    dp[pos]=m;
    if(pos == k){
        //遍历所有方案 求解出到达k点的最少用时
        ans=min(ans,m);
        return;
    }
    if(pos+1<=k)
        dfs(pos+1,m+1);
    if(pos-1>=0)
        dfs(pos-1,m+1);
    if(pos*2<2*k && pos*2<N)
        dfs(pos*2,m+1);
}

int main(){
    ans=INF;
    memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&k);
    dfs(n,0);
    printf("%d",ans);
    return 0;
}
*/

/*
//TLE dfs迭代加深搜索  log(k)/log(pos)>tot-m+1剪枝
//复杂度O(3^10^5) TLE
#include<cstdio>
#include<cmath>
#include<cstring>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,k,dp[N],ans;

//复杂度O(3^10^5) TLE
int dfs(int pos,int m,int tot){
    //剪枝1:如果后续的方案到达pos时的m用时不能比之前的dp[pos]用时更少就不必搜索下去了
    if(m>=dp[pos])
        return 0;
    //更新到达pos的最少用时
    dp[pos]=m;
    //剪枝2:如果剩下的距离考虑乘2增长,实际需要时间为log(k)/log(pos)比规定实现tot下剩余时间还长 则返回
    //注意这里不能用abs(k-pos)>tot-m来剪枝,因为这是需要时间最长的做法,但实际可以通过乘2减少时间,
    //abs(k-pos)>tot-m并不代表 这个方案需要的时间就真的比tot大
    if(log(k)/log(pos)>tot-m+1)//+1是因为log(k)/log(pos)并不是一个确切值,有误差,如果不加1,样例的结果是5
        return 0;
    if(pos == k)
        return 1;
    if(pos+1<=k){
        if(dfs(pos+1,m+1,tot))
            return 1;
    }

    if(pos-1>=0){
        if(dfs(pos-1,m+1,tot))
            return 1;
    }
    if(pos*2<2*k && pos*2<N){
        if(dfs(pos*2,m+1,tot))
            return 1;
    }
    return 0;
}

int main(){
    ans=INF;
    scanf("%d%d",&n,&k);
    for(int i=0;i<N;i++){
        memset(dp,0x3f,sizeof(dp));
        if(dfs(n,0,i)){
            printf("%d",i);
            break;
        }
    }
    return 0;
}
*/

/*
//ac 32ms 动态规划一维数组模拟做法
//摘自博客:https://blog.csdn.net/weixin_37517391/article/details/73611936
//dp[x]表示从N出发到x所需要的最小时间
//那么得到如下转移方程
//如果x < N的话，那么只能通过走路来转移，所以dp[x] = N - x，x <= N时候
//而x > N时候，可以通过2种方式来转移
//（1）走路转移 dp[x] = dp[x-1] + 1
//（2）跳跃加走路转移
//当x为偶数的时候
//dp[x] = min(dp[x],dp[x/2]+1,dp[x/2+1]+3)
//当x为奇数的时候
//dp[x] = min(dp[x],dp[(x-1)/2]+2,dp[(x+1)/2]+2)

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int N,K;
const int MAX = 100005;
int dp[MAX];

int main(){
	cin>>N>>K;
	for(int i = 0;i <= K;i++){
		dp[i] = abs((int)(N - i));
	}
	for(int i = N+1;i <= K;i++){
		if(i & 1) // 奇数
		{
			dp[i] = min(dp[i],dp[(i-1)/2]+2);
			dp[i] = min(dp[i],dp[i-1]+1);
			dp[i] = min(dp[i],dp[(i+1)/2]+2);
		}
		else{
			dp[i] = min(dp[i],dp[i/2]+1);
			dp[i] = min(dp[i],dp[i-1]+1);
			dp[i] = min(dp[i],dp[i/2 + 1]+3);
		}
	}
	cout<<dp[K]<<endl;
	return 0;
}
*/
