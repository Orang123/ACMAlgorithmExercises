/*
题意:摘自网上
给定m，n，k，将m分解成n份，然后依照每份的个数排定字典序，
而且划分时要求a[i-1]<=a[i]，并且a[1]+a[2]+...+a[n]=m，
然后输出字典序排在k位的划分方法。
1<=m<=220,1<=n<=10,k>=1
链接:https://www.luogu.com.cn/problem/UVA10581
思路:记忆化搜索,因为要计算字典序第k位,所以从小到大枚举
每一位上的可能取值,结束状态是当分到n份时,m已经被分完,统计方案数.
dp[i][j][k]表示第i位为j时,剩下未分的数值为k时的方案数.
*/
//ac 10ms 记忆化搜索
//dp[i][j][k]表示第i位为j时,剩下未分的数值为k时的方案数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 230
using namespace std;

int m,n,k,dp[N][M][M];

int dfs(int i,int j,int s){
    int &res=dp[i][j][s];
    if(res!=-1)
        return res;
    if(i == n){
        if(!s)//n个数划分完成,刚好使得a[1]+a[2]+...+a[n]=m,是合理的方案. 返回1
            return res=1;
        else
            return res=0;
    }
    res=0;
    //结束条件是剩下的(n-i)位都分配t已经比s大了,就剪枝 不合法
    for(int t=j;(n-i)*t<=s;t++)//枚举第i+1位是t,剩下未分配的是s-t
        res+=dfs(i+1,t,s-t);
    return res;
}

void print(){
    int t=1,s=m;
    for(int i=1;i<=n;i++){//判断第i位的数值j
        for(int j=t;;j++){
            ll cnt=dp[i][j][s-j];
            if(k>cnt)//当前k比cnt大,说明k在更后面的次序,k减去cnt,同时j++继续往后判断
                k-=cnt;
            else{//当前次序k 比cnt小,说明第i位就是j
                printf("%d\n",j);
                s-=j;//剩余未分配的数值为s-j
                t=j;//下一位的初始值是当前的j
                break;
            }
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,-1,sizeof(dp));
        scanf("%d%d%d",&m,&n,&k);
        for(int i=1;i*n<=m;i++)//枚举第1位的值i,最坏情况是n个位都是i恰好n*i=m,如果最小的字典序n*i>m,就统计完最大的字典序了
            dfs(1,i,m-i);
        print();
    }
    return 0;
}
