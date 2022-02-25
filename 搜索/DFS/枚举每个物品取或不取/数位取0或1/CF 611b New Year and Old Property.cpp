/*
题意:[l,r]区间内的数2进制位只含1个0的个数是多少。
1<=l,r<=10^18.
链接:https://codeforces.ml/problemset/problem/611/b
思路:可以从1开始枚举,每次左移一位,如果本身没有0,就只左移不加1,
保证有一个0,本身有0或没有0,都要左移一位+1。
*/
//ac 31ms
//最坏2^64,但实际并不是每次都枚举2个dfs,而且还设有r的大小限制.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

ll l,r,cnt;

void dfs(ll x,int flag){
    if(x>r) return;
    if(flag && x>=l && x<=r)
        cnt++;
    if(!flag)//二进制位还没有1个是0
        dfs(x<<1,1);//选择右移一位末位是0,后面的dfs右移后都是+1,因为要计算二进制位只有一个0的个数
    dfs((x<<1)+1,flag);//这里有可能全是1,也有可能只有一个0
}

int main(){
    scanf("%lld%lld",&l,&r);
    dfs(1,0);//初始1 是还没有0的,所以flag=0
    printf("%lld",cnt);
    return 0;
}

/*
bfs也很容易
*/
