#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
题意:排成一行的n个骑士,每个都有自身的价值(可能相同),任意相邻的2个均可进行比赛,
输了的会退出比赛,列如a.b.c,d  b和c进行比赛b赢得了比赛后会变成abd,b和a、d相邻.
任意两个骑士间(不一定相邻)的比赛的结果由输入的存储矩阵已给出,若mp[i][j]=1代表i与j进行比赛,i会赢.
问最后冠军价值最大是多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3632
思路:dp[i][j]=1代表骑士i与骑士j相邻可进行比赛,i j之间的骑士已经因为输了比赛而退出了.
*/
int dp[110][110],a[110],mp[110][110];

int main(){
    int T,n,cas=0,ans;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        for(int i=1;i<=n;i++)
            //设置 2个虚节点0、n+1用来表示最终是否只能剩下某一个骑士,0、n+1与任何骑士比赛都不能赢,为了避免dp时判断错误.
            mp[0][i]=mp[n+1][i]=0;
        for(int i=0;i<=n;i++)
            dp[i][i+1]=1;//开始时任意相邻的2个均可进行比赛,包括2个虚节点
        for(int l=2;l<=n+1;l++){//因为初始状态长度为2已经计算,这里计算长度为3的区间
            for(int i=0;i+l<=n+1;i++){
                int j=i+l;
                for(int k=i+1;k<j;k++){//k不能和i j相同,骑士自己不能和自己比赛
                    if(dp[i][k] && dp[k][j]){//若 i可与k比赛 且 k能与j比赛 dp[i][k]和dp[k][j]是上一状态,i~k k~j中间的骑士已经退出
                        if(mp[i][k] || mp[j][k])//若i能赢k  或j能赢k 则最终i就会与j相邻可进行比赛
                            dp[i][j]=1;
                    }
                }
            }
        }
        ans=-1;
        for(int i=1;i<=n;i++)
            //枚举1~n的骑士i 判断1~i个骑士比赛和i~n个骑士比赛是否只能剩下第i个骑士 依次记录可能的最大价值
            if(dp[0][i] && dp[i][n+1] && a[i]>ans)
                ans=a[i];
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}

/*
dp[i][j]记录i~j之间骑士比赛,最终剩下的最大价值骑士的编号
不同骑士价值有相等的时候会出错 此做法错误
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[110][110],mp[110][110],val[110],n;

int main(){
    int T,cas=0,a,b,c;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        cas++;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            dp[i][i]=i;
            if(mp[i][i+1]) dp[i][i+1]=i;
            else dp[i][i+1]=i+1;
        }
        for(int l=2;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                for(int k=i;k<j;k++){
                    a=dp[i][k],b=dp[k+1][j];
                    c=dp[i][j];
//若val[a]==val[c],这时dp[i][j]取a或取之前的c,这个a骑士和c骑士与后面区间的胜者的比赛关系是不确定的,
//都会影响最终剩下的骑士,所以价值也就不一定就是最大的,因此错误
                    if(mp[a][b] && val[a]>val[c])
                        dp[i][j]=a;
                    else if(!mp[a][b] && val[b]>val[c])
                        dp[i][j]=b;
                }
            }
        }
        printf("Case %d: %d\n",cas,val[dp[1][n]]);
    }
    return 0;
}
*/
