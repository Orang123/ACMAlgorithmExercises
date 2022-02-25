/*
题意:摘自网上
给定1个字符串a，对a进行删除操作，使得剩下的子串是回文字符串，
输出最长的字符串，当有多个相同长度的就输出字典序最小的。
字符串长度<=1000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2399
思路:正反序求解LCS即可输出最长回文子序列,但是注意本题要求在长度相同
条件下字典序最小,这要求在dp时如果dp长度相等,按照当前求出字符串的字典序
去递推,但是因为回文正着读和反着读一样,前二分之一按字典序最小和后二分之一
按字典序最小这样有可能输出后二分之一的回文和前二分之一就不一样了.因此
输出时直接输出前二分之一,然后再从中点逆序输出前二分之一,这样就能把整个
回文串输出,但是要区分长度为奇数和偶数.
*/
//ac 1280ms LCS正向dp 区分长度奇数偶数输出方案
//dp[i][j].len表示正序列的前i个元素和逆序列的前j个元素的LCS长度
//dp[i][j].s表示正序列的前i个元素和逆序列的前j个元素的LCS
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#define N 1100
using namespace std;

int n;
char a[N],b[N];
struct DP{
    int len;
    string s;
}dp[N][N];

int main(){
    for(int i=1;i<N;i++)
        dp[0][i].len=0;
    while(scanf("%s",a+1)!=EOF){
        n=strlen(a+1);
        for(int i=1;i<=n;i++)
            b[i]=a[n-i+1];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i] == b[j]){
                    dp[i][j].len=dp[i-1][j-1].len+1;
                    dp[i][j].s=dp[i-1][j-1].s+a[i];
                }
                else{
                    if(dp[i-1][j].len>dp[i][j-1].len)
                        dp[i][j]=dp[i-1][j];
                    else if(dp[i-1][j].len<dp[i][j-1].len)
                        dp[i][j]=dp[i][j-1];
                    else{
                        //前二分之一按字典序最小和后二分之一
                        //按字典序最小这样有可能输出后二分之一的回文和前二分之一就不一样了.
                        if(dp[i-1][j].s<dp[i][j-1].s)
                            dp[i][j]=dp[i-1][j];
                        else
                            dp[i][j]=dp[i][j-1];
                    }
                }
            }
        }
        if(dp[n][n].len & 1){
            for(int i=0;i<dp[n][n].len/2;i++)
                printf("%c",dp[n][n].s[i]);
            for(int i=dp[n][n].len/2;i>=0;i--)
                printf("%c",dp[n][n].s[i]);
        }
        else{
            for(int i=0;i<dp[n][n].len/2;i++)
                printf("%c",dp[n][n].s[i]);
            for(int i=dp[n][n].len/2-1;i>=0;i--)
                printf("%c",dp[n][n].s[i]);
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 620ms 区间dp 枚举区间长度
//dp[i][j].len表示下标编号在[i,j]内的序列中最长的回文子序列的长度
//dp[i][j].s表示下标编号在[i,j]内的序列中最长的回文子序列
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#define N 1100
using namespace std;

int n;
char a[N];
struct DP{
    int len;
    string s;
}dp[N][N];

int main(){
    while(scanf("%s",a+1)!=EOF){
        n=strlen(a+1);
		for(int i=1;i<=n;i++){
			dp[i][i].len=1;
			dp[i][i].s=a[i];
		}
        for(int l=1;l<n;l++){
        	for(int i=1;i+l<=n;i++){
        		int j=i+l;
        		if(a[i] == a[j]){
        			dp[i][j].len=dp[i+1][j-1].len+2;
        			dp[i][j].s=a[i]+dp[i+1][j-1].s+a[j];
				}
        		else{
        			if(dp[i+1][j].len>dp[i][j-1].len)
						dp[i][j]=dp[i+1][j];
					else if(dp[i+1][j].len<dp[i][j-1].len)
						dp[i][j]=dp[i][j-1];
					else{
						if(dp[i+1][j].s<dp[i][j-1].s)
							dp[i][j]=dp[i+1][j];
						else
							dp[i][j]=dp[i][j-1];
					}
				}

			}
		}
		cout << dp[1][n].s << endl;
    }
    return 0;
}
*/

/*
//ac 540ms 区间dp 逆序枚举区间左端点、右端点
//dp[i][j].len表示下标编号在[i,j]内的序列中最长的回文子序列的长度
//dp[i][j].s表示下标编号在[i,j]内的序列中最长的回文子序列
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#define N 1100
using namespace std;

int n;
char a[N];
struct DP{
    int len;
    string s;
}dp[N][N];

int main(){
    while(scanf("%s",a+1)!=EOF){
        n=strlen(a+1);
		for(int i=1;i<=n;i++){
			dp[i][i].len=1;
			dp[i][i].s=a[i];
		}
        for(int i=n-1;i>=1;i--){
        	for(int j=i+1;j<=n;j++){
        		if(a[i] == a[j]){
        			dp[i][j].len=dp[i+1][j-1].len+2;
        			dp[i][j].s=a[i]+dp[i+1][j-1].s+a[j];
				}
        		else{
        			if(dp[i+1][j].len>dp[i][j-1].len)
						dp[i][j]=dp[i+1][j];
					else if(dp[i+1][j].len<dp[i][j-1].len)
						dp[i][j]=dp[i][j-1];
					else{
						if(dp[i+1][j].s<dp[i][j-1].s)
							dp[i][j]=dp[i+1][j];
						else
							dp[i][j]=dp[i][j-1];
					}
				}

			}
		}
		cout << dp[1][n].s << endl;
    }
    return 0;
}
*/

/*
//ac 770ms 区间dp 逆序枚举区间右端点、左端点
//dp[i][j].len表示下标编号在[i,j]内的序列中最长的回文子序列的长度
//dp[i][j].s表示下标编号在[i,j]内的序列中最长的回文子序列
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#define N 1100
using namespace std;

int n;
char a[N];
struct DP{
    int len;
    string s;
}dp[N][N];

int main(){
    while(scanf("%s",a+1)!=EOF){
        n=strlen(a+1);
		for(int i=1;i<=n;i++){
			dp[i][i].len=1;
			dp[i][i].s=a[i];
		}
        for(int j=2;j<=n;j++){
        	for(int i=j-1;i>=1;i--){
        		if(a[i] == a[j]){
        			dp[i][j].len=dp[i+1][j-1].len+2;
        			dp[i][j].s=a[i]+dp[i+1][j-1].s+a[j];
				}
        		else{
        			if(dp[i+1][j].len>dp[i][j-1].len)
						dp[i][j]=dp[i+1][j];
					else if(dp[i+1][j].len<dp[i][j-1].len)
						dp[i][j]=dp[i][j-1];
					else{
						if(dp[i+1][j].s<dp[i][j-1].s)
							dp[i][j]=dp[i+1][j];
						else
							dp[i][j]=dp[i][j-1];
					}
				}

			}
		}
		cout << dp[1][n].s << endl;
    }
    return 0;
}
*/
