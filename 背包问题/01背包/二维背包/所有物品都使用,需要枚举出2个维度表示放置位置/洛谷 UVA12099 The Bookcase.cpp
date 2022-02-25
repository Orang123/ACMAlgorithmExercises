#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 80
#define M 2500
#define INF 0x3f3f3f3f
using namespace std;
//ac 230ms 贪心+01背包
//和POJ 1948类似
/*
题意:给出n本书的高h和宽w,要求做一个三层的书架,
将所有书放入书架中,每层不能为空,每层的高度为当
层最高的书的高度,每层的宽度为该层所有书的宽度和
书架的宽度为三层的最大宽度,书架的高度为三层的
高度和,求书架三层面积的最小值,即:书架高度乘宽度的最小值
n<=70,h<=300,w<=30.
链接:https://www.luogu.com.cn/problem/UVA12099
思路:所有书按照高度降序排序.
影响面积的因素有每层的宽度和高度,而每本书的宽度和高度
间并没有直接的关系,显然需要枚举出每本书放在哪一层,要么放
第一层,要么放第二层,要么放第三层,然后判断每本书是不是该书架上
放进去的第一本书,是的话 书架高度就是第一本书高度,直到所有书都
放进书架上,判断是否三层书架上都有书,之后记录最小面积即可.但是
n<=70,3s时限肯定TLE.
于是考虑dp,首先高度最高的那本书所放的层,该层高度一定是这本书的高度,
那么高度最高的书先放置在第三层上.考虑dp[i][j][k]代表将前i本书放置在
前两层上,第一层宽度为j,第二层宽度为k的情况下,前两层最小的高度和.
实际可以滚动数组优化掉第一维度i,可以将所有书按高度从高到低排好,这样
dp状态转移时,如果当前第i本书是该层所放置的第一本书,那么当前层的高度
就是第i本书的高度,否则考虑放置第i本书在该层和不放置第i本书在该层的
前i-1本书的最优解比较求出当前最优解.因为第i本书即可放置在第一层,也可
放置在第二层,那么初始状态dp[0][0]=0,代表前两层一本书也没有放,高度和为0,
其余状态都是INF,因为实际的前2层书架的宽度一定要和前两层书架的高度和对应上,
不能有多余.
*/
//dp[i][j][k]代表将前i本书(除过第一本最高的)放置在前两层上,第一层宽度为j,第二层宽度为k的情况下,前两层最小的高度和.
//滚动数组可优化掉数组第一维度i,即dp[j][k]
int n,dp[M][M],sum;
struct Book{
    int h,w;
    bool operator <(const Book &x)const{
        return h>x.h;
    }
}bk[N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&bk[i].h,&bk[i].w);
            sum+=bk[i].w;//所有书的宽度和
        }
        sort(bk+1,bk+1+n);//书按照高度降序排
        dp[0][0]=0;//初始状态 前两层 宽度为0
        int maxw=sum-bk[1].w;//默认高度最高的书 放置在第三层,第三层的高即为书高
        for(int i=2;i<=n;i++){//从第2高的书开始放,越往后书本高度越低
            //注意j一定要降序,因为dp[j+bk[i].w][k]=min(dp[j+bk[i].w][k],dp[j][k]);
            //这里的dp[j][k]必须表示前i-1本书的最优解,如果j升序,dp[j][k]会是第i本书已经放入第一层的状态,
            //因为在j较小时dp[j+bk[i].w][k]已经更新过了.
            for(int j=maxw;j>=0;j--){
                //同样k也必须降序,因为dp[j][k+bk[i].w]=min(dp[j][k+bk[i].w],dp[j][k]);
                //dp[j][k]必须表示前i-1本书的最优解,如果k升序,同样会导致dp[j][k]是第i本书已经放入第二层的状态
                for(int k=maxw;k>=0;k--){
                    if(dp[j][k] == INF) continue;//不合法状态 不更新
                    if(!j)
                        //如果第1层还未放置书本,考虑将第i本书放入,高度就为第1层高度即:dp[0][k]+bk[i].h
                        //和前i-1本书的最优解比较,更新dp[j+bk[i].w][k]
                        dp[j+bk[i].w][k]=min(dp[j+bk[i].w][k],dp[0][k]+bk[i].h);
                    else
                        //如果第1层已经放置过书,那么高度已经确定了就是dp[j][k]
                        //和前i-1本书的最优解比较,更新dp[j+bk[i].w][k]
                        dp[j+bk[i].w][k]=min(dp[j+bk[i].w][k],dp[j][k]);
                    if(!k)
                        //如果第2层还未放置书本,考虑将第i本书放入,高度就为第2层高度即:dp[j][0]+bk[i].h
                        //和前i-1本书的最优解比较,更新dp[j][k+bk[i].w]
                        dp[j][k+bk[i].w]=min(dp[j][k+bk[i].w],dp[j][0]+bk[i].h);
                    else
                        //如果第2层已经放置过书,那么高度已经确定了就是dp[j][k]
                        //和前i-1本书的最优解比较,更新dp[j][k+bk[i].w]
                        dp[j][k+bk[i].w]=min(dp[j][k+bk[i].w],dp[j][k]);
                }
            }
        }
        int ans=INF;
        //因为要确保三层都至少放置一本书,所以前两层的下限从1开始
        for(int i=1;i<=maxw;i++){
            for(int j=1;j<=maxw;j++){
                if(dp[i][j] == INF) continue;
                int h=dp[i][j]+bk[1].h;//总高度为前两层的最小高度+第三层的高度(第一本书的高度)
                int w=max(sum-i-j,max(i,j));//第三层的宽度为sum-i-j,书架的宽度为三层的最大宽度
                ans=min(ans,w*h);//书架面积w*h,求最小值
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 540ms 减法的状态转移方程
//dp[j-bk[i].w][k] dp[j][k-bk[i].w]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 80
#define M 2500
#define INF 0x3f3f3f3f
using namespace std;

int n,dp[M][M],sum;
struct Book{
    int h,w;
    bool operator <(const Book &x)const{
        return h>x.h;
    }
}bk[N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&bk[i].h,&bk[i].w);
            sum+=bk[i].w;
        }
        sort(bk+1,bk+1+n);
        int maxw=sum-bk[1].w;
        dp[0][0]=0;
        for(int i=2;i<=n;i++){
            //j k必须降序 才能保证dp[j-bk[i].w][k]和dp[j][k-bk[i].w]是前i-1本书的最优解
            for(int j=maxw;j>=0;j--){//下界0 是为了能够遍历到初始状态dp[0][0]
                for(int k=maxw;k>=0;k--){
                    if(j >= bk[i].w){//保证j-bk[i].w数组下标不为负
                        if(dp[j-bk[i].w][k]!=INF && j == bk[i].w)
                             //j == bk[i].w 刚好是第一层 只放入第i本书时
                             dp[j][k]=min(dp[j][k],dp[0][k]+bk[i].h);
                        else
                            //前i-1本书的最优解与放入第i本书的最优解比较结果,因为第一层已经放入书了,所以高度就是dp[j-bk[i].w][k]
                            dp[j][k]=min(dp[j][k],dp[j-bk[i].w][k]);
                    }
                    if(dp[j][k-bk[i].w]!=INF && k >= bk[i].w){
                        if(k == bk[i].w)
                            dp[j][k]=min(dp[j][k],dp[j][0]+bk[i].h);
                        else
                            dp[j][k]=min(dp[j][k],dp[j][k-bk[i].w]);
                    }
                }
            }
        }
        int ans=INF;
        for(int i=1;i<=maxw;i++){
            for(int j=1;j<=maxw;j++){
                if(dp[i][j] == INF) continue;
                int h=dp[i][j]+bk[1].h;
                int w=max(sum-i-j,max(i,j));
                ans=min(ans,w*h);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//TLE 暴力搜索 O(n^3) n<=70
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 80
#define M 2500
#define INF 0x3f3f3f3f
using namespace std;

int n,ans,h1,h2,h3;
struct Book{
    int h,w;
    bool operator <(const Book &x)const{
        return h>x.h;
    }
}bk[N];

//O(n^3) n<=70
void dfs(int i,int w1,int w2,int w3){
    if(i == n+1){
        if(w1 && w2 && w3)
            ans=min(ans,max(max(w1,w2),w3)*(h1+h2+h3));
        return;
    }
    dfs(i+1,w1+bk[i].w,w2,w3);
    if(!w2)
        h2=bk[i].h;
    dfs(i+1,w1,w2+bk[i].w,w3);
    if(!w3)
        h3=bk[i].h;
    dfs(i+1,w1,w2,w3+bk[i].w);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&bk[i].h,&bk[i].w);
        }
        sort(bk+1,bk+1+n);
        h1=bk[1].h;
        dfs(2,bk[1].w,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 30ms
//洛谷网友_J_C_ 30ms的做法
#include <cstdio>
#include <cstdlib>

#include <algorithm>

namespace my
{
	inline void getmin(int& a, int b) { if (b < a) a = b; }
	inline int max(int a, int b, int c)
	{
		if (a > b) return a > c ? a : c;
		return b > c ? b : c;
	}
}

const int maxn(71), maxw(31);
class book
{
public:
	int h, w;
	bool operator<(const book& b) const
	{ return h > b.h; }
}all[maxn];
int forward[maxn];

int T;
int n;

bool exist[maxn * maxw];
int posw[maxn * maxw], end;

inline void get_exist(int now, int v)
{
	for (int i(forward[now]); i >= v; --i)
		exist[i] |= exist[i - v];
	exist[v] = true;
	end = 0;
	for (int i(0); i <= forward[now]; ++i)
		if (exist[i]) posw[end++] = i;
}

int bVis[2][maxn * maxw][maxn * maxw], NextVis(1), next;
int dp[2][maxn * maxw][maxn * maxw];

inline void init()
{
	exist[0] = true;
	for (int i(1); i != maxn * maxw; ++i) exist[i] = false;
	end = 0;
	posw[end++] = 0;
	next = 0;
}

inline void moveto(int i, int j, int k, int v)
{
	if (bVis[i][j][k] == NextVis + 1) my::getmin(dp[i][j][k], v);
	else bVis[i][j][k] = NextVis + 1, dp[i][j][k] = v;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		init();
		scanf("%d", &n);
		for (int i(1); i <= n; ++i)
		{
			scanf("%d%d", &all[i].h, &all[i].w);
		}
		std::sort(all + 1, all + 1 + n);
		for (int i(1); i <= n; ++i) forward[i] = forward[i - 1] + all[i].w;
		bVis[0][0][0] = ++NextVis;
		dp[0][0][0] = all[1].h;
		next = 0;
		int ans(2123456789);
		for (int i(1); i <= n; ++i)
		{
			get_exist(i, all[i].w);
			for (int j(0); j != end; ++j)
			{
				int w2(posw[j]);
				for (int k(0); k != end; ++k)
				{
					int w3(posw[k]);
					int w1(forward[i] - w2 - w3);
					if (w1 < 0) break;
					if (bVis[next][w2][w3] == NextVis)
					{
						if (i == n)
						{
							if (w1 && w2 && w3)
								my::getmin(ans, my::max(w1, w2, w3) * dp[next][w2][w3]);
						}
						else
						{
							moveto(next ^ 1, w2, w3, dp[next][w2][w3]);
							if (w2 != 0)
								moveto(next ^ 1, w2 + all[i + 1].w, w3, dp[next][w2][w3]);
							else
								moveto(next ^ 1, w2 + all[i + 1].w, w3, dp[next][w2][w3] + all[i + 1].h);
							if (w3 != 0)
								moveto(next ^ 1, w2, w3 + all[i + 1].w, dp[next][w2][w3]);
							else
								moveto(next ^ 1, w2, w3 + all[i + 1].w, dp[next][w2][w3] + all[i + 1].h);
						}
					}
				}
			}
			++NextVis;
			next ^= 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
*/
