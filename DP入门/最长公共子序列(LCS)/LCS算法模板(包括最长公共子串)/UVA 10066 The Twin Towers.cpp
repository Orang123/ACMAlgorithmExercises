/*
题意:摘自网上
从前从前在古帝国有2座高塔位于2座城市中，他们的形状不太相同。
但是他们都是用圆柱形的石块一个堆在另一个上面建起来的。每个
圆柱形石块的高度都相同（定为1），但是半径却不一。所以，虽然
2座高塔的形状不一样，但事实上他们可能有许多石块是相同的。
在高塔建成的一千年后，国王要求建筑师拿掉高塔的某些石块，使得
2座高塔的形状大小和高度一样。但同时要尽可​​能让高塔的高度越高越好。
新高塔的石块的顺序也必须和原来的高塔一样。国王认为这样可以代表2座
城市之间的和谐与平等。他为这2座高塔命名为「双子星塔」
现在，你的任务是就是算出这双子星塔的高度。
2座塔石块的数量n,m<=100.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1007
思路:LCS裸题.dp[i][j]表示正序列的前i个元素和逆序列的前j个元素的LCS长度
不能用区间dp那种转移去做,因为LCS一般是2个子序列,长度是不同的,区间dp模型
这种状态转移方程只有一个子序列,转移区间两端点的判定是对同一个序列进行判定.
*/
//ac 0ms 正向dp
//dp[i][j]表示正序列的前i个元素和逆序列的前j个元素的LCS长度
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,a[N],b[N],dp[N][N];

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        //memset(dp,0,sizeof(dp));//无需初始化dp
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i] == b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printf("Twin Towers #%d\n",cas);
        printf("Number of Tiles : %d\n",dp[n][m]);
        printf("\n");
    }
    return 0;
}

/*
//ac 0ms 记忆化搜索
//记忆化搜索需要初始化dp为-1
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,a[N],b[N],dp[N][N];

int dfs(int i,int j){
	if(!i || !j)
		return dp[i][j]=0;
	if(dp[i][j]!=-1)
		return dp[i][j];
	if(a[i] == b[j])
		dp[i][j]=dfs(i-1,j-1)+1;
	else
		dp[i][j]=max(dfs(i-1,j),dfs(i,j-1));
	return dp[i][j];
}

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        printf("Twin Towers #%d\n",cas);
        printf("Number of Tiles : %d\n",dfs(n,m));
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 0ms 正向dp 滚动数组优化
//滚动数组优化需要初始化dp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,a[N],b[N],dp[2][N];

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i] == b[j])
                    dp[i%2][j]=dp[(i-1)%2][j-1]+1;
                else
                    dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][j-1]);
            }
        }
        printf("Twin Towers #%d\n",cas);
        printf("Number of Tiles : %d\n",dp[n%2][m]);
        printf("\n");
    }
    return 0;
}
*/

/*
//打印LCS字符串
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],pos[110][110];
char a[110],b[110];
//打印LCS字符串
void printLCS(int st,int ed){
    if(!st || !ed) return;//当a或b字符串的长度为0时,LCS必为0 结束
    if(pos[st][ed] == 1){//说明a[st] b[ed]是LCS中的元素,这里从LCS第一个元素开始输出,所以回溯后再输出后面的LCS的元素.
        printLCS(st-1,ed-1);
        printf("%c",a[st]);
    }
    else if(pos[st][ed] == 2)//朝着实际LCS(长度最大)所在的区间遍历
        printLCS(st-1,ed);
    else if(pos[st][ed] == 3)
        printLCS(st,ed-1);
}

int main(){
    int len1,len2;
    scanf("%s",a+1);
    scanf("%s",b+1);
    len1=strlen(a+1);
    len2=strlen(b+1);
    for(int i=1;i<=len1;i++){
        for(int j=1;j<=len2;j++){
            if(a[i] == b[j]){
                dp[i][j]=dp[i-1][j-1]+1;
                pos[i][j]=1;//a[i]==a[j] 代表a[i]是LCS中的元素,代表要输出
            }
            else{
                if(dp[i-1][j]>dp[i][j-1]){
                    dp[i][j]=dp[i-1][j];
                    pos[i][j]=2;//[i-1,j]比[i,j-1]LCS的长度更大
                }
                else{
                    dp[i][j]=dp[i][j-1];
                    pos[i][j]=3;//[i,j-1]比[i-1,j]LCS的长度更大
                }
            }
        }
    }
    printLCS(len1,len2);
    return 0;
}
*/

/*
最长公共子串
leetcode 718 最长重复子数组
链接:https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/
给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。
1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100
//dp[i][j] ：以下标i为结尾的A，和以下标j为结尾的B，最长重复子数组长度为dp[i][j]。
class Solution {
public:
    int dp[1100][1100];
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size(),m=nums2.size();
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(nums1[i] == nums2[j]){
                    if(i-1<0 || j-1<0)
                        dp[i][j]=1;
                    else
                        dp[i][j]=dp[i-1][j-1]+1;
                    ans=max(ans,dp[i][j]);
                }
            }
        }
        return ans;
    }
};
*/
