/*
题意:摘自网上
在资讯科学中有一些是关于在某些条件限制下，找出一些计算的最大值。
以历史考试来说好了，学生被要求对一些历史事件根据其发生的年代顺序来排列。
所有事件顺序都正确的学生无疑的可以得满分。但是那些没有全对的人又该如何给分呢？
以下有2种可能的给分方式：每个与标准答案的顺序相同的事件得1分每个在最长（但不一定要连续）
的序列事件中，其相对的顺序亦可以在标准答案发现者，每个事件得1分。
举例说明：如果有4个事件其发生时间的顺序依次是1 2 3 4（就是标准答案啦，
意思是第1个事件发生顺序为1，第2个事件发生的顺序为2，.... ..）。所以如果学生回答
此4个事件发生的顺序依次是1 3 2 4的话，根据上面第1种方法可以得2分（第1个及第4个事件）。
但是如果以上面第2种方法可以得3分（1 2 4或者1 3 4其相对的顺序可以在标准答案发现）
在本问题中，请你写一个程式以第2个方法算出学生该得多少分
学生回答中最长的（不一定是连续的）事件序列，这些事件按照正确的时间顺序相互关联。
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=47
思路:LCS裸题.只是注意输入的格式.
*/
//ac 0ms 正向dp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
using namespace std;

int n,a[N],b[N],dp[N][N];

int main(){
    int x;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            a[x]=i;//时刻x发生第i个事件 而不是a[i]=x(时刻i发生x事件) 否则会wa
        }
        while(scanf("%d",&x)!=EOF){
            b[x]=1;
            for(int i=2;i<=n;i++){
                scanf("%d",&x);
                b[x]=i;
            }
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(a[i] == b[j])
                        dp[i][j]=dp[i-1][j-1]+1;
                    else
                        dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
            printf("%d\n",dp[n][n]);
        }
    }
    return 0;
}
