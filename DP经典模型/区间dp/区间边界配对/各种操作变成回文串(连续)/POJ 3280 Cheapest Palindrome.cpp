#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
题意:给一段字符串,每个字母的增加或删除代价不同,对字符串中的字母进行
增加或删除求使得这个字符串成为回文串的最小代价.
链接:http://poj.org/problem?id=3280
dp[i][j]代表i~j之间的字符串增加或删除字母使其成为回文串的最小代价
*/

char s[2100],c;
int n,m,dp[2100][2100],add[150],del[150];

int main(){
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        scanf(" %c %d %d",&c,&add[i],&del[i]);
        add[c]=add[i],del[c]=del[i];
    }
    for(int l=1;l<m;l++){
        for(int i=1;i+l<=m;i++){
            int j=i+l;
            if(s[i] == s[j]) dp[i][j]=dp[i+1][j-1];//若两端点相同,则代价还是中间的dp[i+1][j-1]
            else{
                //分别枚举两端点的字符增加或删除的代价,求取最小代价
                dp[i][j]=min(dp[i+1][j]+add[s[i]],dp[i+1][j]+del[s[i]]);//对s[i]进行增加或删除
                dp[i][j]=min(dp[i][j],min(dp[i][j-1]+add[s[j]],dp[i][j-1]+del[s[j]]));//对s[j]进行增加或删除
            }
        }
    }
    printf("%d",dp[1][m]);
    return 0;
}


