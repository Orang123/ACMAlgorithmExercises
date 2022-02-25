/*
题意:题意摘自网上
输入正整数n，问最少需要几次乘除法可以从x得到x^n？
每次乘除得到的新的次数,可以在下次计算时使用。
在计算过程中x的指数应当总是正整数。
n<=1000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4120
思路:枚举当前次数a[k]与前面的a[1..k-1]结合做乘法或除法,
迭代加深搜索枚举每次搜索的深度,当满足时 直接返回输出最小操作次数.
一个剪枝是用当前a[1..k]中的最大次数maxn做乘法结合,即maxn+maxn
依次类推,在剩余的dep-k次结合中最大能获得的最大次数是maxn<<(dep-k)
如果这个值比n还小,就说明当前操作得到的次数过小,返回.
*/
//ac 490ms IDA*
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,a[N];

int dfs(int k,int dep){
    if(a[k] == n)
        return 1;
    int maxn=0;
    for(int i=0;i<=k;i++)
        maxn=max(maxn,a[i]);
    if(maxn << (dep-k) < n)//没有这个剪枝会TLE
        return 0;
    //每次计算都是上一次的a[k]和之前得到的幂次 相计算
    for(int i=k;i>=0;i--){//降序 先算乘法 更容易尽早使得幂次到达n
        a[k+1]=a[k]+a[i];//乘法 次数相加
        if(a[k+1]>n)
            continue;
        if(dfs(k+1,dep))
            return 1;
        a[k+1]=a[k]-a[i];//除法次数相减
        if(a[k+1]<=0)
            continue;
        if(dfs(k+1,dep))
            return 1;
    }
    return 0;
}

int main(){
    a[0]=1;
    while(scanf("%d",&n) && n){
        for(int i=0;;i++){
            if(dfs(0,i)){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}

/*
此题bfs不好模拟状态,不好对状态进行判重
*/

/*
//TLE dfs+剪枝爆搜
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],ans,vis[N];

void dfs(int k){
    if(a[k] == n){
    	if(k<ans)
    		ans=k;
        return;
	}
	if(k>=ans)
		return;
	if(ans!=INF){
    	int maxn=0;
    	for(int i=0;i<=k;i++)
        	maxn=max(maxn,a[i]);
    	if(maxn << (ans-k) < n)
        	return;
	}
    vis[a[k]]=1;
    for(int i=k;i>=0;i--){
        a[k+1]=a[k]+a[i];
        if(a[k+1]>n)
            continue;
        dfs(k+1);
        a[k+1]=a[k]-a[i];
        //之所以要对次数做vis标记,是因为没有IDA*的深度限制,除法会不断地得到重复的之前出现过的次数,导致dfs死循环.
        if(a[k+1]<=0 || vis[a[k+1]])
            continue;
        dfs(k+1);
    }
    vis[a[k]]=0;
}

int main(){
    a[0]=1;
    while(scanf("%d",&n) && n){
    	ans=INF;
    	dfs(0);
    	printf("%d\n",ans);
    }
    return 0;
}
*/
