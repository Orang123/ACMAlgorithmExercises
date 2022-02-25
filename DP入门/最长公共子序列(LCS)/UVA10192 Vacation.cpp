/*
题意:
你打算休息一下，出去度假，但你真的不知道该去哪个城市。所以，你向你的父母寻求帮助。
你母亲说：“我的儿子，你必须去巴黎、马德里、里斯本和伦敦。但按这个顺序去才有趣。
”然后你父亲说：“儿子，如果你打算旅行，先去巴黎，然后去里斯本，再去伦敦，最后去马德里。
我知道我在说什么。”现在你有点困惑了，因为你没有预料到这种情况。你害怕如果你听从你父亲
的建议会伤害你母亲。但是如果你听从母亲的建议，你也害怕伤害你的父亲。但情况可能会变得更糟，
因为如果你忽视他们的建议，你会伤害他们两人！因此，你决定尽可能地遵循他们的建议。因此，你
意识到“巴黎-里斯本-伦敦”的秩序更能满足你的父母。之后你可以说你不能去马德里，尽管你会非常喜欢的。
你为了不让他们伤心，你要尽可能的满足他们给的意见,问最多能去几个城市。
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1133
思路:LCS裸题.
*/
//ac 0ms 正向dp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,dp[N][N];
char a[N],b[N];

int main(){
    int cas=0;
    while(gets(a+1) && a[1]!='#'){//这里不能用scanf 会TLE 不知何原因
        cas++;
        gets(b+1);
        n=strlen(a+1);
        m=strlen(b+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i] == b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printf("Case #%d: you can visit at most %d cities.\n",cas,dp[n][m]);
    }
    return 0;
}
