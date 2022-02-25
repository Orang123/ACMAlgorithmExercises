/*
题意:多重背包模板题.n<=1000,v<=20000
不用单调队列优化会TLE
链接:https://www.acwing.com/problem/content/description/6/
思路:单调队列优化dp.
参考题解:https://www.acwing.com/problem/content/solution/6/1/
参考博客:https://blog.csdn.net/weixin_46503238/article/details/115132242
暂时还未理解单调队列优化.复杂度O(NV)
多重背包单调队列优化 被楼天城称"《男人八题》"-《难人八题》
*/

/*
一共 n 类物品，背包的容量是 m
每类物品的体积为v, 价值为w，个数为s
我们先来回顾一下传统的dp方程
dp[i][j] 表示将前 i 种物品放入容量为 j 的背包中所得到的最大价值
dp[i][j] = max(不放入物品 i，放入1个物品 i，放入2个物品 i, ... , 放入k个物品 i)
这里 k 要满足：k <= s, j - k*v >= 0
不放物品  i = dp[i-1][j]
放k个物品 i = dp[i-1][j - k*v] + k*w
dp[i][j] = max(dp[i-1][j], dp[i-1][j-v] + w, dp[i-1][j-2*v] + 2*w,..., dp[i-1][j-k*v] + k*w)
实际上我们并不需要二维的dp数组，适当的调整循环条件，我们可以重复利用dp数组来保存上一轮的信息
我们令 dp[j] 表示容量为j的情况下，获得的最大价值
那么，针对每一类物品 i ，我们都更新一下 dp[m] --> dp[0] 的值，最后 dp[m] 就是一个全局最优值
dp[m] = max(dp[m], dp[m-v] + w, dp[m-2*v] + 2*w, dp[m-3*v] + 3*w, ...)
接下来，我们把 dp[0] --> dp[m] 写成下面这种形式
dp[0], dp[v],   dp[2*v],   dp[3*v],   ... , dp[k*v]
dp[1], dp[v+1], dp[2*v+1], dp[3*v+1], ... , dp[k*v+1]
dp[2], dp[v+2], dp[2*v+2], dp[3*v+2], ... , dp[k*v+2]
...
dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j]
显而易见，m 一定等于 k*v + j，其中  0 <= j < v
所以，我们可以把 dp 数组分成 j 个类，每一类中的值，都是在同类之间转换得到的
也就是说，dp[k*v+j] 只依赖于 { dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] }
因为我们需要的是{ dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] } 中的最大值，
可以通过维护一个单调队列来得到结果。这样的话，问题就变成了 j 个单调队列的问题
所以，我们可以得到
dp[j]    =     dp[j]
dp[j+v]  = max(dp[j] +  w,  dp[j+v])
dp[j+2v] = max(dp[j] + 2w,  dp[j+v] +  w, dp[j+2v])
dp[j+3v] = max(dp[j] + 3w,  dp[j+v] + 2w, dp[j+2v] + w, dp[j+3v])
...
但是，这个队列中前面的数，每次都会增加一个 w ，所以我们需要做一些转换
dp[j]    =     dp[j]
dp[j+v]  = max(dp[j], dp[j+v] - w) + w
dp[j+2v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w) + 2w
dp[j+3v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w, dp[j+3v] - 3w) + 3w
...
这样，每次入队的值是 dp[j+k*v] - k*w
单调队列问题，最重要的两点
1）维护队列元素的个数，如果不能继续入队，弹出队头元素
2）维护队列的单调性，即：尾值 >= dp[j + k*v] - k*w
本题中，队列中元素的个数应该为 s+1 个，即 0 -- s 个物品 i

作者：lys
链接：https://www.acwing.com/solution/content/6500/
来源：AcWing
*/

/*
作者：o_O
链接：https://www.acwing.com/solution/content/1537/
来源：AcWing
下面代码:
*/
//ac 2259ms
//复杂度O(NV) 1000*20000=2*10^7
#include <bits/stdc++.h>
using namespace std;

int n, m;
int f[20002], q[20002], g[20002];
int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) {
        int v, w, s;
        cin >> v >> w >> s;
        memcpy(g, f, sizeof(f));
        for (int j = 0; j < v; ++j) {
            /*
            hh为队首位置
            tt为队尾位置
            数值越大，表示位置越后面
            队首在队尾后面队列为空，即hh>tt时队列为空
            */
            int hh = 0, tt = -1;
            /*
            q[]为单调队列
            存储前个s(物品数量)中的最大值
            数组从头(hh)到尾(tt)单调递减
            */
            for (int k = j; k <= m; k += v) {

                // f[k] = g[k]; //这一行我没理解有什么用，去掉后也能ac？我认为前面使用过了memcpy,这里应该一定是相等的

                //k代表假设当前背包容量为k
                //q[hh]为队首元素（最大值的下标）
                //g[]为dp[i-1][]
                //f[]为dp[i][]

                /*
                维护一个大小为k的区间
                使最大值为前k个元素中最大
                (k - q[hh]) / v 表示拿取物品的数量（相当于最原始的多重背包dp的k）
                */
                if (hh <= tt && (k - q[hh]) / v > s) {
                    hh++;
                }

                /*
                若队内有值，该值就是前k个元素的最大值
                (k - q[hh]) / v 表示拿取物品的数量（相当于最原始的多重背包dp的k）
                q[hh]为队首元素（g[]中前k个数中最大值的下标），g[]为dp[i-1][]
                所以 g[q[hh]]为只考虑前i-1个物品时，拿前q[hh]个物品的最大价值
                */
                if (hh <= tt) {
                    f[k] = max(f[k], g[q[hh]] + (k - q[hh]) / v * w);
                }

                /*
                若队尾元素小于当前元素，则队尾元素出队；
                若队内一个元素比当前元素小，则该元素一定不会被用到（单调队列思想）
                g[q[tt]] + (k - q[tt]) / v * w
                与
                g[k] - (k - j) / v * w
                分别表示队尾元素的值和当前元素的值
                */
                while (hh <= tt && g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w) {
                    tt--;
                }

                //去除了比当前小的元素，保证队列里的元素都比当前元素大，入队
                q[++tt] = k;
            }
        }
    }
    cout << f[m] << endl;
}

/*
//yxc大佬代码 无注释
//ac 992ms 单调队列优化 最优版本
//复杂度O(NV) 1000*20000=2*10^7
#include <iostream>
#include <cstring>

using namespace std;

const int N = 20010;

int dp[N], pre[N], q[N];
int n, m;

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        memcpy(pre, dp, sizeof(dp));
        int v, w, s;
        cin >> v >> w >> s;
        for (int j = 0; j < v; ++j) {
            int head = 0, tail = -1;
            for (int k = j; k <= m; k += v) {

                if (head <= tail && k - s*v > q[head])
                    ++head;

                while (head <= tail && pre[q[tail]] - (q[tail] - j)/v * w <= pre[k] - (k - j)/v * w)
                    --tail;

                if (head <= tail)
                    dp[k] = max(dp[k], pre[q[head]] + (k - q[head])/v * w);

                q[++tail] = k;
            }
        }
    }
    cout << dp[m] << endl;
    return 0;
}
*/

/*
//TLE 二进制优化 复杂度O(∑log(num[i])*v) 1000*log(20000)*20000=14000*20000=2.8*10^8
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 20010
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        m=num[i];
        for(int k=1;m>0;k<<=1){//枚举第i种物品可能的二进制组合
            m-=k;
            if(m<0) k+=m;
            tw=w[i]*k;
            tv=val[i]*k;
            for(int j=v;j>=tw;j--)
                dp[j]=max(dp[j],dp[j-tw]+tv);
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}
*/
