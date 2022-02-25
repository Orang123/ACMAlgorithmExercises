/*
题意:新西兰货币制度包括100美元,50美元,20美元,10美元,
5美元,2美元,1美元,50美分,20美分,10美分和5美分.
请写一个程序确定,给你任意一笔钱,求有多少种方法可以组成这笔钱
(改变排列顺序算同一种)例如20美分可以由4种方法组成:1*20,2*10,10+2*5,4*5.

输出格式要求:
每组数据输出的第一行包括该组数据(有两个小数位,在宽度为6的字段中右对齐),
其后紧跟可能组成该组数据的方法数,在宽度为17的字段中右对齐.
链接:https://www.luogu.com.cn/problem/UVA147
思路:完全背包统计恰好装满方案数,因为数组下标不能有小数,所以要先将,11种货币
中的美元都转换成美分计量扩大100倍.然后对于v需要将其扩大100倍,因为v有小数,
浮点数在计算机中是以有效位数和指数位构成,某些浮点数可能不能精确表示,列如456
实际存储可能是455.99999,如果直接乘100强制转换成int结果是455,因此要加上0.5
再扩大100倍强转int去除小数位后才是本身v所表示的实际美分数值.
并不是所有浮点数都能精确表示,某些浮点数只能表示一个近似值.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 12
#define M 30100
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;

int w[N]={0,10000,5000,2000,1000,500,200,100,50,20,10,5};
ll dp[M];
double v;

int main(){
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    for(int i=1;i<N;i++){
        for(int j=w[i];j<=30000;j++)
            dp[j]+=dp[j-w[i]];
    }
    while(scanf("%lf",&v) && v)
        printf("%6.2f%17lld\n",v,dp[(int)(v*100+0.5)]);
    return 0;
}

/*
//ac 0ms 二维数组实现
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 12
#define M 30100
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;

int w[N]={0,10000,5000,2000,1000,500,200,100,50,20,10,5};
ll dp[N][M];
double v;

int main(){
    memset(dp[0],0,sizeof(dp[0]));
    dp[0][0]=1;//初始状态是一个物品也不装时,只有背包容量为0是合法状态 其余dp[0][1..N]都是不合法的,因此memset置为0
    for(int i=1;i<N;i++){
        for(int j=0;j<=30000;j++){
            if(j>=w[i])
                dp[i][j]=dp[i-1][j]+dp[i][j-w[i]];
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    while(scanf("%lf",&v) && v)
        printf("%6.2f%17lld\n",v,dp[11][(int)(v*100+0.5)]);
    return 0;
}
*/
