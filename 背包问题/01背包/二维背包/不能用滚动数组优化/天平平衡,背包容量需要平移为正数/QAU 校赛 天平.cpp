#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int maxn = 10010, INF = 0x7fffffff;

/*
题意:天平的右端放着一件重量为w的物品。现在有n个重量已知的砝码，
只允许在左端放砝码的前提下，能否通过砝码判断出物品的重量。
(注:这里假设当天平的两端重量不同时天平就会向重的一端倾斜到底!)
链接:
思路:判断是否能恰好装满容量为w的背包.
*/
int A[maxn], dp[maxn];
int main()
{
    int w, n;
    cin>> w >> n;
    mem(dp, 0);
    dp[0] = 1;
    for(int i=0; i<n; i++)
    {
        cin>> A[i];
        for(int j=w+1; j>=A[i]; j--)
            if(dp[j-A[i]]) dp[j] = 1;
    }
    if(dp[w])
        cout<< "Yes" <<endl;
    else if(dp[w-1] && dp[w+1])
        cout<< "Yes" <<endl;
    else
        cout<< "No" <<endl;
    return 0;
}
