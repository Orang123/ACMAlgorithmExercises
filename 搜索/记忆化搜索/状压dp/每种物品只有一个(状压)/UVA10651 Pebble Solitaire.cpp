/*
题意:摘自网上
Pebble Solitaire是一款有趣的游戏。你会得到一个上面有一排小洞的板，
这些洞最初只有一个没有被鹅卵石占据。 游戏的目的是从棋盘上移除尽可
能多的鹅卵石。如果满足以下条件，你就可以进行移动：如果存在三个相邻的、
能连成一条直线的洞（不妨称它们为A，B和C），中间为B，其中A是空的，
但B和C上均有一个石子。那么你可以把C上的石子移到A上，并拿走B中的石子。
你可以继续移动石子，直到无法再移动为止。在这个问题中，我们来看一个简单
的游戏变体，即一个沿着一条线放置十二个小洞的板。 每次游戏开始时，有一
些洞上被放有石子。你的任务是使尽可能少的鹅卵石留在棋盘上。
在 a) 中有两种可能的移动，分别是8->6和7->9。
b) 为 a) 选择第二种移动方式的结果，此时又有两种移动方式，分别是5->7或者6->4。
c) 作为 b) 做出第一种选择的结果，此时再没有其它的移动方式了。

简而言之就是给出12个序列由'o','-'组成,转化规则'oo-' -> '--o','-oo'->'o--',问最后最少剩下几个'o'。
链接:https://www.luogu.com.cn/problem/UVA10651
思路:就是要枚举连续的三位,看是否满足i,i+1为'o',i+2为'-',将i,i+1转为'-',i+2转为'o'.
或是i,i-1为'o',i-2为'-',将i,i-1转为'-',i-2转为'o'.但是在转化的过程中,12个小洞的'o'和
'-'的情况需要用二进制位来表示状态的唯一性,而且再不断转化过程中会出现重叠子问题,需要记录
这些重叠子问题的答案.
记忆化搜索,dp[cur]表示从cur状态(包括cur)所能变化转移的所有状态中'o'最少的个数.
*/
//ac 0ms 记忆化搜索 判断字符串str计算当前状态
//dp[cur]=1/0 代表当前棋盘上鹅卵石的二进制位的状态之前是否得到过,1代表已经出现过,0代表还未出现
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 13
#define INF 0x3f3f3f3f
using namespace std;

int n,dp[1<<12],ans;
char str[N];

//计算当前状态 'o'表示的二进制位1
int calState(){
    int sta=0;
    for(int i=1;i<=12;i++){
        if(str[i] == 'o')
            sta|=1<<i-1;
    }
    return sta;
}

//计算当前状态str中,'o'的个数
int calNum(){
    int cnt=0;
    for(int i=1;i<=12;i++){
        if(str[i] == 'o')
            cnt++;
    }
    return cnt;
}

void dfs(int cur){
    if(dp[cur])
        return;
    dp[cur]=1;
    ans=min(ans,calNum());
    for(int i=1;i<=12;i++){
        if(str[i] == 'o'){
            //判断i,i+1等于'o' i+2等于'-'
            if(i<=10 && str[i+1] == 'o' && str[i+2] == '-'){
                str[i]=str[i+1]='-';//i、i+1变为'-',i+2变为'o'
                str[i+2]='o';
                dfs(calState());
                str[i]=str[i+1]='o';
                str[i+2]='-';
            }
            //判断i,i-1等于'o' i-2等于'-'
            if(i>=3 && str[i-1] == 'o' && str[i-2] == '-'){
                str[i]=str[i-1]='-';//i、i-1变为'-',i-2变为'o'
                str[i-2]='o';
                dfs(calState());
                str[i]=str[i-1]='o';
                str[i-2]='-';
            }
        }
    }
}

int main(){
    scanf("%d",&n);
    while(n--){
        memset(dp,0,sizeof(dp));
        scanf("%s",str+1);
        ans=strlen(str+1);
        dfs(calState());
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms 记忆化搜索
//dp[cur]表示从cur状态(包括cur)所能变化转移的所有状态中'o'最少的个数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 13
using namespace std;

int n,dp[1<<12];
char str[N];

int calInitState(){
    int sta=0;
    for(int i=1;i<=12;i++){
        if(str[i] == 'o')
            sta|=1<<i-1;
    }
    return sta;
}

int calNum(int sta){
    int cnt=0;
    while(sta){
        if(sta & 1)
            cnt++;
        sta>>=1;
    }
    return cnt;
}

int dfs(int cur){
    if(dp[cur]!=-1)
        return dp[cur];
    dp[cur]=calNum(cur);
    int sta;
    for(int i=1;i<=12;i++){
        //判断i,i+1等于'o' i+2等于'-'
        if(i<=10 && (cur & 1<<i-1) && (cur & 1<<i) && !(cur & 1<<i+1)){
        	int sta=cur;
            sta^=1<<i-1;//i、i+1变为'-',i+2变为'o'
            sta^=1<<i;
            sta|=1<<i+1;
            dp[cur]=min(dp[cur],dfs(sta));
        }
        //判断i,i-1等于'o' i-2等于'-'
        if(i>=3 && (cur & 1<<i-1) && (cur & 1<<i-2) && !(cur & 1<<i-3)){
        	int sta=cur;
            sta^=1<<i-1;//i、i-1变为'-',i-2变为'o'
            sta^=1<<i-2;
            sta|=1<<i-3;
            dp[cur]=min(dp[cur],dfs(sta));//回溯后还原
        }
    }
    return dp[cur];
}

int main(){
    scanf("%d",&n);
    while(n--){
    	memset(dp,-1,sizeof(dp));
        scanf("%s",str+1);
        printf("%d\n",dfs(calInitState()));
    }
    return 0;
}
*/

/*
//ac 0ms 记忆化搜索 位运算进行状态更新
//dp[cur]=1/0 代表当前棋盘上鹅卵石的二进制位的状态之前是否得到过,1代表已经出现过,0代表还未出现
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 13
#define INF 0x3f3f3f3f
using namespace std;

int n,dp[1<<12],ans;
char str[N];

int calInitState(){
    int sta=0;
    for(int i=1;i<=12;i++){
        if(str[i] == 'o')
            sta|=1<<i-1;
    }
    return sta;
}

int calNum(int sta){
    int cnt=0;
    while(sta){
        if(sta & 1)
            cnt++;
        sta>>=1;
    }
    return cnt;
}

void dfs(int cur){
    if(dp[cur])
        return;
    dp[cur]=1;
    ans=min(ans,calNum(cur));
    for(int i=1;i<=12;i++){
        //判断i,i+1等于'o' i+2等于'-'
        if(i<=10 && (cur & 1<<i-1) && (cur & 1<<i) && !(cur & 1<<i+1)){
            cur^=1<<i-1;//i、i+1变为'-',i+2变为'o'
            cur^=1<<i;
            cur|=1<<i+1;
            dfs(cur);
            cur|=1<<i-1;//回溯后还原
            cur|=1<<i;
            cur^=1<<i+1;
        }
        //判断i,i-1等于'o' i-2等于'-'
        if(i>=3 && (cur & 1<<i-1) && (cur & 1<<i-2) && !(cur & 1<<i-3)){
            cur^=1<<i-1;//i、i-1变为'-',i-2变为'o'
            cur^=1<<i-2;
            cur|=1<<i-3;
            dfs(cur);//回溯后还原
            cur|=1<<i-1;
            cur|=1<<i-2;
            cur^=1<<i-3;
        }
    }
}

int main(){
    scanf("%d",&n);
    while(n--){
        memset(dp,0,sizeof(dp));
        scanf("%s",str+1);
        ans=strlen(str+1);
        dfs(calInitState());
        printf("%d\n",ans);
    }
    return 0;
}
*/
