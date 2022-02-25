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
����:��ƽ���Ҷ˷���һ������Ϊw����Ʒ��������n��������֪�����룬
ֻ��������˷������ǰ���£��ܷ�ͨ�������жϳ���Ʒ��������
(ע:������赱��ƽ������������ͬʱ��ƽ�ͻ����ص�һ����б����!)
����:
˼·:�ж��Ƿ���ǡ��װ������Ϊw�ı���.
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
