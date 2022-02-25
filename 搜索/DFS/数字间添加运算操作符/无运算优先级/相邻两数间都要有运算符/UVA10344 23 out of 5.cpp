/*
题意:摘自网上
输入五个数， 判断是否存在情况使得式子( ( a(1) o a(2) ) o a(3) ) o a(4) ) o4 a(5)等于23。
五个数的任意排序，o为运算符‘+’，‘-’，或‘*’。
链接:https://www.luogu.com.cn/problem/UVA10344
思路:生成全排列,然后dfs枚举三个运算符.
此题不能用类似01背包那个状态转移来做,因为运算过程
结果最大可达50^5=312,500,000,空间复杂度不够.
*/
//ac 70ms 复杂度(5!*3^4)
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 6
using namespace std;

int a[N];

int dfs(int k,int sum){
    if(k == 6){
        if(sum == 23)
            return 1;
        else
            return 0;
    }
    if(dfs(k+1,sum+a[k]))
        return 1;
    if(dfs(k+1,sum-a[k]))
        return 1;
    if(dfs(k+1,sum*a[k]))
        return 1;
    return 0;
}

int main(){
    int flag;
    while(scanf("%d%d%d%d%d",&a[1],&a[2],&a[3],&a[4],&a[5]) && a[1]+a[2]+a[3]+a[4]+a[5]){
        sort(a+1,a+1+5);
        flag=0;
        do{
            if(dfs(2,a[1])){
                flag=1;
                printf("Possible\n");
                break;
            }
        }while(next_permutation(a+1,a+1+5));
        if(!flag)
            printf("Impossible\n");
    }
    return 0;
}
