/*
题意:摘自网上
给出n和k，有n种化学药剂，型号由1~n，然后给出n * n行代表相应的两种
化学药剂反应后的生成物以及释放的热量，然后给出k个试管，每种试管中
有对应的药剂，要求将m种药剂反应合成一种，不要求反应后药剂的种类，
要求反应所散发的热量最少。
注意：i和j反应可能与j和i反应不同，反应可能吸热，每组测试以/结束。
1<=n<=6,2<=k<=10.
链接:https://www.luogu.com.cn/problem/UVA10604
思路:记忆化搜索,枚举反应的顺序,状态表示成n种化学药剂剩余的数量.
2种状态表示法:
1.dp[11][11][11][11][11][11]=10^6=1000000 6种化学药剂剩余数量下能产生的最小热量
2.因为每种化学药剂最多10个,可以用11进制数表示状态,dp[10*11^5]=1610510
n种化学药剂剩余数量下能产生的最小热量
*/
//ac 80ms 记忆化搜索
//dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][cnt[6]] 6种化学药剂剩余数量下能产生的最小热量
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 7
#define INF 0x3f3f3f3f
using namespace std;

int n,k,type[N][N],heat[N][N],cnt[N],dp[11][11][11][11][11][11];

int judge(){
    int num1=0,num2=0;
    for(int i=1;i<=n;i++){
        if(cnt[i] == 1)
            num1++;//数量为1的药剂
        else if(!cnt[i])
            num2++;//数量为0的药剂
    }
    if(num1 == 1 && num2 == n-1)//结束状态是 只剩下一种药剂数量为1,最后一组反应必然会生成一种新的药剂,其余药剂数量都为0
        return 1;
    return 0;
}

int dfs(){
    int &res=dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][cnt[6]];
    if(res!=INF)
        return res;
    if(judge())
        return res=0;
    for(int i=1;i<=n;i++){
        if(!cnt[i])
            continue;
        cnt[i]--;//第i种反应物质数量减1
        for(int j=1;j<=n;j++){
            if(!cnt[j])
                continue;
            cnt[j]--;//第j种反应物质数量减1
            cnt[type[i][j]]++;//i和j反应产生了新的物质type[i][j]
            res=min(res,dfs()+heat[i][j]);
            cnt[j]++;//回溯后还原
            cnt[type[i][j]]--;
        }
        cnt[i]++;
    }
    return res;
}

int main(){
    int T,x;
    char str[3];
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        memset(cnt,0,sizeof(cnt));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d%d",&type[i][j],&heat[i][j]);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d",&x);
            cnt[x]++;
        }
        scanf("%s",str);
        printf("%d\n",dfs());
    }
    return 0;
}


/*
//ac 100ms 11进制数表示状态
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 7
#define M 2000000//1610510 11^5*10=1610510(最大数的状态)
#define INF 0x3f3f3f3f
using namespace std;

int n,k,type[N][N],heat[N][N],cnt[N],dp[M];

int judge(){
    int num1=0,num2=0,sum=0;
    for(int i=1;i<=n;i++){
        if(cnt[i] == 1)
            num1++;
        else if(!cnt[i])
            num2++;
        sum=sum*11+cnt[i];//N种化学物质数量构成的11进制数(每种化学物质最大10个)
    }
    if(num1 == 1 && num2 == n-1)
        return 0;
    return sum;
}

int dfs(){
    int sta=judge();
    int &res=dp[sta];
    if(res!=INF)
        return res;
    if(!sta)
    	return res=0;
    for(int i=1;i<=n;i++){
        if(!cnt[i])
            continue;
        cnt[i]--;
        for(int j=1;j<=n;j++){
            if(!cnt[j])
                continue;
            cnt[j]--;
            cnt[type[i][j]]++;
            res=min(res,dfs()+heat[i][j]);
            cnt[j]++;
            cnt[type[i][j]]--;
        }
        cnt[i]++;
    }
    return res;
}

int main(){
    int T,x;
    char str[3];
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        memset(cnt,0,sizeof(cnt));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d%d",&type[i][j],&heat[i][j]);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d",&x);
            cnt[x]++;
        }
        scanf("%s",str);
        printf("%d\n",dfs());
    }
    return 0;
}
*/
