/*
题意:n个点的树,每条边有长度w,现在有q次询问,每次询问一个距离x,
问从0号点出发所走距离最多x单位长度限制下最多能经过多少点,
同一结点多次经过只算1次.
n<=500,1<=w<=10000,q<=1000.0<=x<=5000000.
同UVA 1407 Caves是同一道题.
2007 Asia Regional Chengdu
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3672
思路:因为有q(q<=1000)次询问,如果将行走距离最大限制x作为背包容量的话,
那么每次询问的x都需要重新dp 求解出0节点子树下最多行使x距离下能经过的
最多点的个数(尽可能多地装满背包).这样复杂度可达:O(q*n*x^2) 显然TLE.
可以将所经过的点的个数作为背包容量.
因为要考虑经过更多节点,本身走过的节点可能要返回去回到初始点,再走别的分支的节点,
实际除过最后一个所走的分支,之前走过的分支的边都恰好走了2遍.因此dp要决策的就是最后
走哪一个分支只走一遍路径长度,总体所走距离较短.
dp[i][j][0/1]表示从以i为根节点的子树i点出发经过恰好j个节点时最少走过的距离.
dp[i][j][0]表示不回到i节点,dp[i][j][1]表示回到i节点.
注意:dp[i][0]是不合法的,因为dp[i][1..j]至少经过了i节点本身,经过距离为0.
初始状态为dp[i][1][0]=dp[i][1][1]=1;其余状态无穷大INF.

有依赖关系,要走到子节点,必须先走到父节点.
*/

//ac 31ms 先dp转移后累加siz[u]+=siz[v]  背包容量上限较小,复杂度较低
//dp[i][j][0/1]表示从以i为根节点的子树i点出发经过恰好j个节点时最少走过的距离.
//dp[i][j][0]表示不回到i节点,dp[i][j][1]表示回到i节点.
//dp[u][j+k][0]=min(dp[u][j+k][0],dp[u][j][1]+dp[v][k][0]+w);
//dp[u][j+k][0]=min(dp[u][j+k][0],dp[u][j][0]+dp[v][k][1]+2*w);
//dp[u][j+k][1]=min(dp[u][j+k][1],dp[u][j][1]+dp[v][k][1]+2*w);
//恰好装满背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 510
using namespace std;

int cnt,head[N],n,x,siz[N],dp[N][M][2];

struct Edge{
    int to,next,w;
}edge[N];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u){
    siz[u]=1;
    dp[u][1][0]=dp[u][1][1]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        int w=edge[i].w;
        dfs(v);
        //j上界siz[u]不包括v子树节点 j下界1,至少包括u节点本身.
        for(int j=siz[u];j>=1;j--){
            //枚举v子树遍历结点个数
            for(int k=1;k<=siz[v];k++){
                //dp要决策的就是在能遍历节点数相同的情况下,尽量选择路径距离较小的分支去遍历
                //以及最后走哪一个分支只走一遍路径长度,总体所走距离较短.其余分支实际都走了两遍.
                //不返回u点的情况2种
                //1.之前兄弟子树遍历j个节点返回u节点 dp[u][j][1] v子树遍历k个节点不返回v节点 dp[v][k][0]
                //其它兄弟子树dp[u][j][1] 边都走了2遍能够返回u点 而u->v这条边因为v子树是最后走的一条分支,不返回v点,
                //u->v这条边实际只走了一遍,因此所走距离+w.
                dp[u][j+k][0]=min(dp[u][j+k][0],dp[u][j][1]+dp[v][k][0]+w);
                //2.之前兄弟子树遍历j个节点不返回u节点 dp[u][j][0] v子树遍历k个节点返回v节点 dp[v][k][1]
                //其它兄弟子树dp[u][j][0]存在一个兄弟子树分支是不返回u点,边只走了1遍,而v子树分支要返回v点,并且还要返回u点,
                //那么从u走到v,再v子树遍历完返回v点再返回u点,u-v这条边走了2遍.所走距离+2w.
                dp[u][j+k][0]=min(dp[u][j+k][0],dp[u][j][0]+dp[v][k][1]+2*w);
                //返回u点的情况:u兄弟子树和v子树都要返回其根节点u、v
                //因此u-v这条边一来一回走了2遍,因此+2w.
                dp[u][j+k][1]=min(dp[u][j+k][1],dp[u][j][1]+dp[v][k][1]+2*w);
            }
        }
        //延迟累加siz[u]
        siz[u]+=siz[v];
    }
}

int main(){
    int u,v,w,q,cas=0;
    while(scanf("%d",&n) && n){
        cnt=0;
        cas++;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(v,u,w);
        }
        memset(dp,0x3f,sizeof(dp));
        dfs(0);
        printf("Case %d:\n",cas);
        scanf("%d",&q);
        while(q--){
            scanf("%d",&x);
            for(int i=n;i>=1;i--){//降序考虑 0节点出发遍历节点数i 所走距离是否不超过x,即输出最大遍历节点数.
                //dp[0][i][1](返回0点)一定大于dp[0][i][0](不返回0点)
                //最后一条分支不需要返回 只需判断dp[0][i][0]即可
                if(dp[0][i][0]<=x){
                    printf("%d\n",i);
                    break;
                }
            }
        }
    }
    return 0;
}


/*
//ac 31ms 先累加siz[u]+=siz[v]后dp转移  背包容量上限较大,复杂度较大
//dp[i][j][0/1]表示从以i为根节点的子树i点出发经过恰好j个节点时最少走过的距离.
//dp[i][j][0]表示不回到i节点,dp[i][j][1]表示回到i节点.
//dp[u][j][0]=min(dp[u][j][0],dp[u][j-k][1]+dp[v][k][0]+w);
//dp[u][j][0]=min(dp[u][j][0],dp[u][j-k][0]+dp[v][k][1]+2*w);
//dp[u][j][1]=min(dp[u][j][1],dp[u][j-k][1]+dp[v][k][1]+2*w);
//恰好装满背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 510
using namespace std;

int cnt,head[N],n,x,siz[N],dp[N][M][2];

struct Edge{
    int to,next,w;
}edge[N];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u){
    siz[u]=1;
    dp[u][1][0]=dp[u][1][1]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        int w=edge[i].w;
        dfs(v);
        siz[u]+=siz[v];
        //j下界是2,因为v子树至少选取一个v节点,u之前遍历的兄弟子树至少选取一个u节点.
        for(int j=siz[u];j>=2;j--){
            //实际dp[u][j-k]的合法状态是前面已经遍历的除过当前v子树节点的个数,j-k最大是siz[u]-siz[v]
            //j-k>siz[u]-siz[v]的dp[u][j-k]并不合法,因为之前遍历的兄弟子树节点个数不可能大于siz[u]-siz[v]
            //但是注意k循环结束条件加上j-k<=siz[u]-siz[v]的判断后,k一定要降序,因为如果k升序 刚开始k较小 j-k>siz[u]-siz[v]会直接退出循环
			//但是k增加后j-k又会<= siz[u]-siz[v],又是合法状态了,或者升序要放在 循环里 j-k>siz[u]-siz[v]时 continue即可.
            for(int k=min(siz[v],j-1);k>=1 && j-k<=siz[u]-siz[v];k--){//v子树节点 至少选取一个 v节点 k下界是1
            	//if(j-k>siz[u]-siz[v]) continue;//k升序时 dp[u][j-k]不合法情况不转移
                dp[u][j][0]=min(dp[u][j][0],dp[u][j-k][1]+dp[v][k][0]+w);
                dp[u][j][0]=min(dp[u][j][0],dp[u][j-k][0]+dp[v][k][1]+2*w);
                dp[u][j][1]=min(dp[u][j][1],dp[u][j-k][1]+dp[v][k][1]+2*w);
            }
        }
    }
}

int main(){
    int u,v,w,q,cas=0;
    while(scanf("%d",&n) && n){
        cnt=0;
        cas++;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(v,u,w);
        }
        memset(dp,0x3f,sizeof(dp));
        dfs(0);
        printf("Case %d:\n",cas);
        scanf("%d",&q);
        while(q--){
            scanf("%d",&x);
            for(int i=n;i>=1;i--){
                if(dp[0][i][0]<=x){
                    printf("%d\n",i);
                    break;
                }
            }
        }
    }
    return 0;
}
*/

/*
//TLE MLE 空间复杂度可达 nx=500*5000000=2.5*10^9 时间复杂度可达 q*n*x^2 =很大.
//dp[i][j][0/1]表示以i为根节点的子树根节点i出发在长度j限制下最多能遍历子树节点个数
//dp[i][j][0]表示不返回i点,dp[i][j][1]表示返回i点.
//尽可能多地装满背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5000//M根本开不出来 5000000 编译不过
using namespace std;

int cnt,head[N],n,x,dp[N][M][2];

struct Edge{
    int to,next,w;
}edge[N];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u){
    //初始条件 尽可能多地装满背包 下界为0,因为在x时间下恰好走完最后一条边剩余时间刚好为0,u-v边上
    //uv两点的时间都是0 但都是合法的 需要算上
    for(int i=0;i<=x;i++)
    	dp[u][i][0]=dp[u][i][1]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        int w=edge[i].w;
        dfs(v);
        for(int j=x;j>=w;j--){
            for(int k=0;k<=j-w;k++){
                dp[u][j][0]=max(dp[u][j][0],dp[u][j-k-w][1]+dp[v][k][0]);
                if(j-k-2*w>=0)
                	dp[u][j][0]=max(dp[u][j][0],dp[u][j-k-2*w][0]+dp[v][k][1]);
                if(j-k-2*w>=0)
                	dp[u][j][1]=max(dp[u][j][1],dp[u][j-k-2*w][1]+dp[v][k][1]);
            }
        }
    }
}

int main(){
    int u,v,w,q,cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(v,u,w);
        }
        printf("Case %d:\n",cas);
        scanf("%d",&q);
        while(q--){
            scanf("%d",&x);
            memset(dp,0,sizeof(dp));//尽可能多地装满背包
            dfs(0);
            printf("%d\n",dp[0][x][0]);//最终肯定不返回0点 遍历节点数才是最多的
        }
    }
    return 0;
}
*/

/*
//ac 31ms 树形背包+q次询问 x距离限制作为验证标准 二分最大遍历的节点
//摘自博客:https://www.cnblogs.com/Spare-No-Effort/p/14157957.html
//在根节点0确定条件下 dp[0][i][0] 随着遍历节点数i的增多,其所走的距离dp[0][i][0]一定是单调增加的,满足单调性 因此可以二分.
#include <cstdio>
#include <cctype>
#include <cstring>
#define rr register
using namespace std;
const int N=511; struct node{int y,w,next;}e[N];
int dp[N][N][2],siz[N],as[N],ans[N],n,Test;
inline signed iut(){
	rr int ans=0; rr char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans;
}
inline void print(int ans){
	if (ans>9) print(ans/10);
	putchar(ans%10+48);
}
inline signed min(int a,int b){return a<b?a:b;}
inline void dfs(int x){
	dp[x][1][0]=dp[x][1][1]=0,siz[x]=1;
	for (rr int i=as[x];i;i=e[i].next){
		dfs(e[i].y),siz[x]+=siz[e[i].y];
		for (rr int j=siz[x]-siz[e[i].y];j;--j)
		for (rr int o=siz[e[i].y];o;--o){
			dp[x][j+o][0]=min(dp[x][j+o][0],dp[x][j][1]+dp[e[i].y][o][0]+e[i].w);
			dp[x][j+o][0]=min(dp[x][j+o][0],dp[x][j][0]+dp[e[i].y][o][1]+e[i].w*2);
			dp[x][j+o][1]=min(dp[x][j+o][1],dp[x][j][1]+dp[e[i].y][o][1]+e[i].w*2);
		}
	}
}
signed main(){
	while (1){
		n=iut(); if (!n) return 0;
		printf("Case %d:\n",++Test);
		memset(as,0,sizeof(as)),
		memset(dp,42,sizeof(dp));
		for (rr int i=1;i<n;++i){
			rr int x=iut()+1,F=iut()+1,w=iut();
			e[i]=(node){x,w,as[F]},as[F]=i;
		}
		dfs(1);
		for (rr int i=1;i<=n;++i)
		    ans[i]=min(dp[1][i][0],dp[1][i][1]);
		for (rr int Q=iut();Q;--Q){
			rr int W=iut();
		    rr int l=1,r=n;
		    while (l<r){
		    	rr int mid=(l+r+1)>>1;
		    	if (ans[mid]>W) r=mid-1;
		    	    else l=mid;
			}
			print(l),putchar(10);
		}
	}
}
*/
