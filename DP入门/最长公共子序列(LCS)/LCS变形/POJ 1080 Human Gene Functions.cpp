/*
题意:摘自网上
给两个DNA序列，在这两个DNA序列中插入若干个'-'，使两段序列长度相等，
使得两串长相等(但是不能使得a的空格对应b的空格位置).
对应位置的两个符号的得分规则给出，求最高得分。
DNA序列长度<=100.
链接:http://poj.org/problem?id=1080
思路:LCS变形.为了使得获得的分数最大,可以枚举a[i]和b[j]匹配或者
a[i]和'-'或b[j]和'-'匹配的情况,求取最大值即可.
注意初始条件是一段序列被匹配完,另一段序列全部和'-'匹配因此
初始条件:
for(int i=1;i<=n;i++)
    dp[i][0]=dp[i-1][0]+score[a[i]]['-'];
for(int i=1;i<=m;i++)
    dp[0][i]=dp[0][i-1]+score['-'][b[i]];
状态转移方程:
dp[i][j]=max(dp[i-1][j-1]+score[a[i]][b[j]],max(dp[i][j-1]+score['-'][b[j]],dp[i-1][j]+score[a[i]]['-']));
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,dp[N][N],score['T'+1]['T'+1];
char a[N],b[N];

//初始化得分规则
void init(){
    score['A']['A']=5;
    score['C']['C'] =5;
    score['G']['G'] =5;
    score['T']['T'] =5;
    score['-']['-'] = -10;
    score['A']['C'] = score['C']['A']=-1;
    score['A']['G'] = score['G']['A']=-2;
    score['A']['T'] = score['T']['A']=-1;
    score['A']['-'] = score['-']['A']=-3;
    score['C']['G'] = score['G']['C']=-3;
    score['C']['T'] = score['T']['C']=-2;
    score['C']['-'] = score['-']['C']=-4;
    score['G']['T'] = score['T']['G']=-2;
    score['G']['-'] = score['-']['G']=-2;
    score['T']['-'] = score['-']['T']=-1;
}

int main(){
    init();
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %s",&n,a+1);
        scanf("%d %s",&m,b+1);
        for(int i=1;i<=n;i++)//b序列匹配完,a序列还没匹配完,则在b序列前加'-'和其匹配
            dp[i][0]=dp[i-1][0]+score[a[i]]['-'];
        for(int i=1;i<=m;i++)//a序列匹配完,b序列还没匹配完,则在a序列前加'-'和其匹配
            dp[0][i]=dp[0][i-1]+score['-'][b[i]];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                //这里有可能a[i]和b[j]是匹配的,但是为了得分最大化,可能会插入'-'和a[i]或b[j]匹配
                //dp[i-1][j-1]+score[a[i]][b[j]] 表示a[i]和b[j]匹配
                //dp[i][j-1]+score['-'][b[j]]  在a[i]前加入'-',b[j]和'-'匹配
                //dp[i-1][j]+score[a[i]]['-'] 在b[j]前加入'-',a[i]和'-'匹配
                dp[i][j]=max(dp[i-1][j-1]+score[a[i]][b[j]],max(dp[i][j-1]+score['-'][b[j]],dp[i-1][j]+score[a[i]]['-']));
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
