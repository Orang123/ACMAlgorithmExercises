/*
题意:一个数的因子如果只有2、3、5、7则这个数是丑数,从小到大输出丑数序列.
是一个数位dp的问题.
链接:http://poj.org/problem?id=2247
思路:
任意一个丑数一定是另一个丑数乘以2或3或5得到的，我们可以使用一个数组将已经确认
为丑数的数按照从小到大的顺序记录下来，每个丑数都是前面的丑数乘以2、3或5得来的。
如何确保数组中的丑数是排好序的？假设数组中已经有若干个排好序的丑数，并且其中最大
的丑数为M。那么下一个丑数一定是数组中某个数乘以2或3或5或7的结果，所以我们把数组中
的每个数都乘以2，找到第一个大于M的结果M2（小于等于M的结果肯定已经在数组中了，不需要考虑）；
同理，把数组中的每个数都乘以3，找到第一个大于M的结果M3；把数组中的每个数都乘以5，找到第一
个大于M的结果M5。把数组中的每个数都乘以7，找到第一个大于M的结果M7，
那么下一个丑数一定是M2、M3、M5、M7当中的最小值。
*/
#include<cstdio>
#include<algorithm>
using namespace std;
int dp[5900]={1};
int main(){
    int n,a[4]={0};
    for(int i=1;i<5843;i++){
        //新的丑数一定是按之前的丑数*2、3、5、7得到的,这里只记录最小的丑数作为新的丑数,要按照从小到大顺序记录
        dp[i]=min(min(2*dp[a[0]],3*dp[a[1]]),min(5*dp[a[2]],7*dp[a[3]]));
        //这里不用else if是因为有可能有重复元素
        if(dp[i]==2*dp[a[0]]) a[0]++;//用之前的丑数乘以2的 数组下标+1(考虑下一个已经在序列里的丑数乘以因子2、3、5、7)
        if(dp[i]==3*dp[a[1]]) a[1]++;
        if(dp[i]==5*dp[a[2]]) a[2]++;
        if(dp[i]==7*dp[a[3]]) a[3]++;
    }
    while(scanf("%d",&n)&&n){
        if(n%10==1&&n%100!=11)
      		printf("The %dst humble number is %d.\n",n,dp[n-1]);
    	else if(n%10==2&&n%100!=12)
      		printf("The %dnd humble number is %d.\n",n,dp[n-1]);
        else if(n%10==3&&n%100!=13)
      		printf("The %drd humble number is %d.\n",n,dp[n-1]);
    	else
      		printf("The %dth humble number is %d.\n",n,dp[n-1]);
    }
    return 0;
}
