//ac 0ms 2次完全背包
/*
题意:6种欧元货币,最小的面值永远是1,用最少的货币量组成1~100面值内所有的钱,
只是货币不仅可以正值组成1~100的钱,还可以负值组成,如:3=1+1+1=2+1=3,还可以3=5-2=4-1,
问要构造1~100内面值的钱平均使用多少货币,这些面值中的钱最多使用的货币量是多少.
链接:http://poj.org/problem?id=1252
思路:每种货币可以无线使用,因为组成面值的钱不仅可以正值组成,还以负值组成,因此
两次完全背包,1次正值,1次负值,只是负值背包容量要降序,这样才能保证每种负值货币能够
无限使用.
*/
//注意完全背包无法用天平力距的那种平衡去做,因为正数和负数必有一个是当前物品只能取一次,不能无限取,
//只有01背包那种 用扩大区间 用二维数组记录上一状态,刚好是每个物品2种方法 刚好只取一次
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 7
#define M 150
#define INF 0x3f3f3f3f
using namespace std;

int w[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=6;i++)
            scanf("%d",&w[i]);
        dp[0]=0;
        //正值
        for(int i=1;i<=6;i++){
            for(int j=w[i];j<=M-1;j++)
                dp[j]=min(dp[j],dp[j-w[i]]+1);
        }
        //负值
        for(int i=1;i<=6;i++){
            /*
            //另一种转移 ac 0ms
            for(int j=M-1;j>=w[i]+1;j--)
                dp[j-w[i]]=min(dp[j-w[i]],dp[j]+1);
            */
            //因为每种负值货币的上一状态是dp[j+w[i]],所以j必须降序,
            //才能使得第i种负值货币无限使用
            for(int j=M-1-w[i];j>=1;j--)//上界是100-w[i],因为j+w[i]上一状态最大是100,上界定义为100,j+w[i]就大于背包容量了
                dp[j]=min(dp[j],dp[j+w[i]]+1);
        }
        int sum=0,ans=0;
        for(int i=1;i<=100;i++){
            sum+=dp[i];//因为第一种货币面值永远是1,所以dp[i]永远是合法的
            ans=max(ans,dp[i]);
        }
        printf("%.2f %d\n",1.0*sum/100,ans);
    }
    return 0;
}

/*
//ac 47ms 深度搜索+剪枝 正负6种货币总共12种货币类型
//M设置成2100 就会TLE,深度搜索的深度太深了.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 13
#define M 210
#define INF 0x3f3f3f3f
using namespace std;
//dp[i]=j代表12种货币类型组成面值为i时所使用的最少货币量
int w[N],dp[M];

void dfs(int num,int sum){
    if(sum>M || sum<0)
        return;
    if(num>=dp[sum])
        return;
    dp[sum]=num;
    for(int i=1;i<=12;i++)
        dfs(num+1,sum+w[i]);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=6;i++){
            scanf("%d",&w[i]);
            w[i+6]=-w[i];
        }
        dfs(0,0);
        int sum=0,ans=0;
        for(int i=1;i<=100;i++){
            sum+=dp[i];
            ans=max(ans,dp[i]);
        }
        printf("%.2f %d\n",1.0*sum/100,ans);
    }
    return 0;
}
*/

/*
//ac 0ms bfs广度搜索枚举状态+剪枝 正负6种货币总共12种货币类型
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 13
#define M 210
#define INF 0x3f3f3f3f
using namespace std;
//dp[i]=j代表12种货币类型组成面值为i时所使用的最少货币量
int w[N],dp[M];

struct State{
    int num,sum;
    State(int num=0,int sum=0):num(num),sum(sum){}
};

void bfs(){
    queue<State> Q;
    Q.push(State(0,0));
    while(!Q.empty()){
        State tp=Q.front();
        Q.pop();
        for(int i=1;i<=12;i++){
            if(tp.sum+w[i]>M-1 || tp.sum+w[i]<=0) continue;
            if(tp.num+1>=dp[tp.sum+w[i]]) continue;
            Q.push(State(tp.num+1,tp.sum+w[i]));
            dp[tp.sum+w[i]]=tp.num+1;
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=6;i++){
            scanf("%d",&w[i]);
            w[i+6]=-w[i];
        }
        bfs();
        int sum=0,ans=0;
        for(int i=1;i<=100;i++){
            sum+=dp[i];
            ans=max(ans,dp[i]);
        }
        printf("%.2f %d\n",1.0*sum/100,ans);
    }
    return 0;
}
*/
