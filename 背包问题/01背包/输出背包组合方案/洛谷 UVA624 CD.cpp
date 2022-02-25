#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;
//ac 50ms 01背包尽可能多地装满,按照题目输入顺序输出物品组合方案
/*
题意:你正在一个漫长的行车之旅中,你有一个磁带机,但是你
最喜欢的音乐在CD(音轨)上.你需要把他们放在磁带机上.你有
一个可以存下N分钟长的磁带,磁带里有若干音轨,你需要选择
一个最优方案使得未用空间最小.
注意:
1.一片CD里没有超过20个音轨
2.没有音轨比N分钟长
3.音轨互不重复
4.每一个音轨的长度是一个int范围的数
5.N同时也是一个int你的程序需要找到一个最优方案(包含若干音轨),
并且按照原输入顺序输出输入格式:每一行有一个N和其他音轨的时长
输出格式:一套磁带里放的音轨选择 和他们时间的总和.
链接:https://www.luogu.com.cn/problem/UVA624
思路:就是01背包炉头,因为要按输入顺序输出组合方案,所以
要逆序先从第n个物品开始放,最后考虑放第1个物品,然后输出方案时
就可以从第一个物品开始遍历.
*/
//vis[i][j]=1代表背包容量为j时,最优解放入了第i个物品
//vis[i][j]=0代表背包容量为j时,最优解没有放入了第i个物品
//注意这里vis[i][j]只是单纯地表示第i个物品在背包容量j时最优解情况是否装入,不能代表实际的递推关系
int n,v,val[N],dp[M],sum,vis[N][M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=n;i>=1;i--){//因为要按照输入顺序输出物品价值,所以逆序先放入第n个,最后放第1个
            for(int j=v;j>=val[i];j--){
                //这里if(dp[j]<=dp[j-val[i]]+val[i])可以<= 实际方案可能不同
                //最后一个样例45 8 4 10 44 43 12 9 8 2 是按<=输出的,<输出的是43 2
                if(dp[j]<dp[j-val[i]]+val[i]){//这里是严格小于,因为没有PTA L3-001那种按照字典序价值升序输出的要求
                    dp[j]=dp[j-val[i]]+val[i];
                    vis[i][j]=1;//标记当前最优解 容量为j时放入了物品i
                }
            }
        }
        //注意这里 并不是j-=val[i],最终可能所有物品输出完毕了,dp[j]仍然不为0,
        //因为并不是恰好装满背包即:dp[v]==v,所以并不能根据j或dp[j]为0来判断
        //样例90 8 10 23 1 2 3 4 5 7 方案全部输出完后,dp[35]=35,如果这样判断dp[j]是否为0会死循环
        //这里只有前0个物品的初始状态dp[j]=0,dp完成后,若有一个物品的体积为1,则除了dp[0]==0外,其余dp[j]都不等0
        for(int i=1,j=v;i<=n;i++){//从编号为1的物品考虑输出,因为编号越靠前的物品越是最后加入背包的
            if(vis[i][j]){
                //背包容量不断骤减,因为在背包容量不同时最优解的方案可能是不同的,
                //因此需要背包容量要减去当前第i个物品,才能使得当前剩余容量是在最大容量v下的最优解方案,
                //之后再依次判断第i+1个物品是否在最优解中
                j-=val[i];
                printf("%d ",val[i]);
            }
        }
        printf("sum:%d\n",dp[v]);
    }
    return 0;
}

/*
//ac 40ms vis[i][j]标记背包容量为j时是否选用第i个物品 恰好装满背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;

int n,v,val[N],dp[M],sum,vis[N][M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        dp[0]=0;
        for(int i=n;i>=1;i--){
            for(int j=v;j>=val[i];j--){
                if(dp[j]<dp[j-val[i]]+val[i]){
                    dp[j]=dp[j-val[i]]+val[i];
                    vis[i][j]=1;
                }
            }
        }
        for(int i=v;i>=0;i--){
        	if(dp[i]>0){
        		v=i;
        		break;
			}
		}
		int i=1,j=v;
		while(j){
			if(vis[i][j]){
				printf("%d ",val[i]);
				j-=val[i];
			}
			i++;
		}
        printf("sum:%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 40ms 二维数组进行01背包 递归输出方案
//递归输出方案不能输出字典序
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;

int n,v,val[N],dp[N][M],sum;

void print(int i,int j){
	if(!i)//i=0,所有物品的方案已经判断出来
		return;
	//前i个物品和前i-1个物品最优解相同,说明没选第i个物品
	//这个做法不能输出字典序,在j不能全部装下前i个或前i-1个物品,时它会认为没有选择第i个物品,
    //而实际字典序方案 可能是选择了第i个的物品的,所以递归无法输出字典序方案,只能说是能输出其中一种方案.
	//转而递归向前一个状态再判断
	if(dp[i][j] == dp[i-1][j])
		print(i-1,j);
	else{//否则i个物品和前i-1个物品最优解不同,说明肯定是dp[i][j]>dp[i-1][j],即:选了第i个物品后 最优解被更新
        //j-val[i],因为本身v就可能有剩余,所以从最大的开始递减判断前i个和前i-1个是否在最大的相同容量下最优解相同
		print(i-1,j-val[i]);//因为要按照输入顺序输出方案,所以先递归判断前面物品进行输出再输出后面的物品
		printf("%d ",val[i]);//输出第i个物品的价值
	}
}

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=0;j<=v;j++){
            	if(j>=val[i])
            		dp[i][j]=max(dp[i-1][j],dp[i-1][j-val[i]]+val[i]);
            	else
            		dp[i][j]=dp[i-1][j];
            }
        }
        print(n,v);
        printf("sum:%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 50ms 二维数组进行01背包 正向循环输出方案
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;

int n,v,val[N],dp[N][M],sum;

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        //因为循环只能正着从第1个物品开始判断,所以01背包逆序从n开始放入背包,将第1个物品作为结束状态
        for(int i=n;i>=1;i--){
            for(int j=0;j<=v;j++){
            	if(j>=val[i])
            		dp[i][j]=max(dp[i+1][j],dp[i+1][j-val[i]]+val[i]);
            	else
            		dp[i][j]=dp[i+1][j];
            }
        }
        int tp=v;
        for(int i=1;i<=n;i++){
        	if(dp[i][tp]!=dp[i+1][tp]){
        		printf("%d ",val[i]);
        		tp-=val[i];
			}
		}
        printf("sum:%d\n",dp[1][v]);
    }
    return 0;
}
*/
