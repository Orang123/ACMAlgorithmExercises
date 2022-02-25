/*
题意:一个好奇的孩子有一组n块小砖(5<=n<=500).他用这些砖块建造了不同的楼梯.
楼梯由严格按照降序排列的不同大小的台阶组成.楼梯不得具有相等大小的台阶.
每个楼梯至少包括两个台阶,每个台阶至少包含一个砖块.
链接:https://acm.timus.ru/problem.aspx?space=1&num=1017
思路:01背包统计恰好装满的方案数,n为背包容量,但是要注意每节台阶砖块
数不能相等,每个楼梯至少有2个台阶,那么对于每节台阶的所用的砖块数就可
以是1~(n-1)
*/
//ac 15ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define M 510
typedef long long ll;//数字很大int会溢出
using namespace std;

int n;
ll dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d",&n);
    dp[0]=1;
    //枚举每节台阶所用的砖块数,因为至少要2节台阶构成 因此上界不能是n
    //而每节台阶的砖块数都不能相等,因此每次 台阶所用砖块数都是递增的.
    for(int i=1;i<n;i++){
        for(int j=n;j>=i;j--)
            dp[j]+=dp[j-i];
    }
    printf("%lld\n",dp[n]);
    return 0;
}

/*
//ac 15ms 母函数做法
#include<iostream>
using namespace std;
long long int ans[510]={1,1};//起初是(1+x)0和1赋为1，(1+x^2),(1+x^3),,,往里乘

int main(){
    int n;
    cin>>n;
    for(int i=2;i<=n;i++) //从(1+x^2)开始往里乘
        for(int j=n;j>=0;j--) //更新乘进去后的所有可能系数
            if(i+j<=n)  //n后面的系数不关心
                ans[i+j]+=ans[j];
    cout<<ans[n]-1<<endl;
    return 0;
}
*/
