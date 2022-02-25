/*
题意:摘自网上
有N个作业（N<=15)，每个作业需耗时，有一个截止期限。超期多少天就要扣多少分。
问最少被扣多少分，且按字典序输出做作业顺序。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1074
思路:状压dp.dp[sta]表示已做的作业状态为sta时做完这些作业最少减少的分数
*/
//ac 15ms 记忆化搜索
//时间复杂度O((1<<n)*n)
//dp[sta]表示已做的作业状态为sta时做完这些作业最少减少的分数
//time[sta]表示已做作业状态为sta时所花费的总时间
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,time[1<<N],dp[1<<N],pre[1<<N],record[1<<N];
struct Course{
    char s[M];
    int d,t;
}course[N];

void init(){
    memset(dp,-1,sizeof(dp));
    memset(time,0,sizeof(time));
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i & 1<<j)
                time[i]+=course[j].t;
        }
    }
}

int dfs(int cur){
    if(dp[cur]!=-1)
        return dp[cur];
    dp[cur]=cur?INF:0;
    int sta,res1,res2;
    for(int i=n-1;i>=0;i--){
        if(cur & 1<<i){
            sta=cur ^ 1<<i;
            res1=dfs(sta);
            res2=time[sta]+course[i].t-course[i].d;
            if(res2<=0)
                res2=0;
            if(res1+res2<dp[cur]){
                dp[cur]=res1+res2;
                pre[cur]=sta;
                record[cur]=i;
            }
        }
    }
    return dp[cur];
}

void print(int sta){
    if(!sta)
        return;
    print(pre[sta]);
    printf("%s\n",course[record[sta]].s);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s %d %d",course[i].s,&course[i].d,&course[i].t);
        init();
        printf("%d\n",dfs((1<<n)-1));
        print((1<<n)-1);
    }
    return 0;
}

/*
//ac 15ms 记忆化搜索
//dp[sta]表示已做的作业状态为(1<<n)-1-sta时做完这些作业最少减少的分数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,time[1<<N],dp[1<<N],pre[1<<N],record[1<<N];
struct Course{
    char s[M];
    int d,t;
}course[N];

void init(){
    memset(dp,-1,sizeof(dp));
    memset(time,0,sizeof(time));
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i & 1<<j)
                time[i]+=course[j].t;
        }
    }
}

int dfs(int cur){
    if(dp[cur]!=-1)
        return dp[cur];
    dp[cur]=cur == (1<<n)-1?0:INF;//(1<<n) -1表示已经把所有作业选择完了
    int sta,res1,res2;
    for(int i=n-1;i>=0;i--){
        if(!(cur & 1<<i)){
            sta=cur | 1<<i;
            res1=dfs(sta);
            //这里time总时间对应的状态为(1<<n)-1-sta
            res2=time[(1<<n)-1-sta]+course[i].t-course[i].d;
            if(res2<=0)
        		res2=0;
            if(res1+res2<dp[cur]){
                dp[cur]=res1+res2;
                pre[cur]=sta;
                record[cur]=i;
            }
        }
    }
    return dp[cur];
}

void print(int sta){
    if(sta == (1<<n)-1)
        return;
    print(pre[sta]);
    printf("%s\n",course[record[sta]].s);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s %d %d",course[i].s,&course[i].d,&course[i].t);
        init();
        printf("%d\n",dfs(0));
        print(0);
    }
    return 0;
}
*/

/*
//ac 15ms 正向dp 移方程 dp[i]=min(dp[i],dp[sta]+res)
//dp[sta]表示已做的作业状态为sta时做完这些作业最少减少的分数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,time[1<<N],dp[1<<N],pre[1<<N],record[1<<N];
struct Course{
    char s[M];
    int d,t;
}course[N];

void init(){
    memset(dp,0x3f,sizeof(dp));
    memset(time,0,sizeof(time));
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i & 1<<j)
                time[i]+=course[j].t;
        }
    }
}

void print(int sta){
    if(!sta)
        return;
    print(pre[sta]);
    printf("%s\n",course[record[sta]].s);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s %d %d",course[i].s,&course[i].d,&course[i].t);
        init();
        int sta,res;
        dp[0]=0;//初始状态
        for(int i=0;i<(1<<n);i++){
        	for(int j=n-1;j>=0;j--){//这里j要降序才能保证 结果相同时,方案字典序最小 写成递推不好解释这里降序,有点玄学
        		if(i & 1<<j){
        			sta=i ^ 1<<j;
        			res=time[sta]+course[j].t-course[j].d;
        			if(res<=0)
        				res=0;
					if(dp[sta]+res<dp[i]){
						dp[i]=dp[sta]+res;
						pre[i]=sta;
						record[i]=j;
					}
				}
			}
		}
		printf("%d\n",dp[(1<<n)-1]);
        print((1<<n)-1);
    }
    return 0;
}
*/

/*
//ac 15ms 正向dp 转移方程 dp[sta]=min(dp[sta],dp[i]+res)
//dp[sta]表示已做的作业状态为sta时做完这些作业最少减少的分数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,time[1<<N],dp[1<<N],pre[1<<N],record[1<<N];
struct Course{
    char s[M];
    int d,t;
}course[N];

void init(){
    memset(dp,0x3f,sizeof(dp));
    memset(time,0,sizeof(time));
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i & 1<<j)
                time[i]+=course[j].t;
        }
    }
}

void print(int sta){
    if(!sta)
        return;
    print(pre[sta]);
    printf("%s\n",course[record[sta]].s);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s %d %d",course[i].s,&course[i].d,&course[i].t);
        init();
        int sta,res;
        dp[0]=0;
        for(int i=0;i<(1<<n);i++){
        	for(int j=n-1;j>=0;j--){//这里j要降序才能保证 结果相同时,方案字典序最小
        		if(!(i & 1<<j)){//j作业还未写
        			sta=i | 1<<j;//下一状态要加上j
        			res=time[i]+course[j].t-course[j].d;
        			if(res<=0)
        				res=0;
					if(dp[i]+res<dp[sta]){
						dp[sta]=dp[i]+res;
						pre[sta]=i;
						record[sta]=j;
					}
				}
			}
		}
		printf("%d\n",dp[(1<<n)-1]);
        print((1<<n)-1);
    }
    return 0;
}
*/
