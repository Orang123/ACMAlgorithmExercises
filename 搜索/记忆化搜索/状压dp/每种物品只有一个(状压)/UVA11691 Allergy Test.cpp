/*
����:ժ������
����Ҫ�������Դ��������n�ֹ���Դ��Ҫ��⣬��������Դ�������ڸ�һ��������a[i]��
Ҫ�������ٵ�������������Դ������������ÿ���й���ԭ��һ��ע�����ڣ��ڼ���
�Ĺ����У����ٱ�֤ÿ�ֹ���ԭ���е����������ڴ���һ�죬Ҫ�������ٵ��������
������ԭ��ֱ���������еĹ���ԭȫ��������.
n<=20,a[i]<=7.
����:https://www.luogu.com.cn/problem/UVA11691
˼·:���仯����.
dp[sta][k]��ʾ��ǰ��ע��Ĺ���ԭ��״̬Ϊsta,�������һ������������ԭ
ʣ�µ�ʱ��Ϊkʱ,�Ի�δע��Ĺ���ԭҪ��������Ҫ�����ٵ�����.
*/
//ac 70ms ���仯����+״ѹ+vis�Թ���ԭ���ʱ����
//����vis�Թ���ԭ���ʱ���� 2.23s
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[1<<N][8];

int dfs(int sta,int k){
    if(dp[sta][k]!=INF)
        return dp[sta][k];
    if(sta == (1<<n)-1)
        return dp[sta][k]=k;//ʣ�µ�ʱ��Ϊk
    int vis[8];
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++){
        if((sta & 1<<i) || vis[a[i]]) continue;
        vis[a[i]]=1;//��ǰ״̬����ѡ�Ĺ���ԭ������ͬ��ֻ��ѡһ��,�������ظ�����,���������֦,ʱ����2.23s
        //�����i������ԭ��,��i������ԭ�������ڵ�ʱ��Ϊmax(0,a[i]-k-1)
        //��a[i]>kʱ,�ڵ�ǰʱ��ע���i������ԭ,ʹ��k��ʱ��㸲��,�ȵ���һ������ԭ��ʧ��,
        //����1�����i������ԭ,��i������ԭʣ��ʱ��Ϊa[i]-k-1
        //��a[i]<=kʱ,ע���i������ԭ��ʱ����Ҫ��֤,k��ʱ������,��i������ԭǡ��ֻʣ1��ʱ���������,������i������ԭʣ�´��ʱ���Ϊ0
        //���ȴ���ʱ��2���������k+1.
        dp[sta][k]=min(dp[sta][k],dfs(sta|1<<i,max(0,a[i]-k-1))+k+1);
    }
    return dp[sta][k];
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        printf("%d\n",dfs(0,0));
    }
    return 0;
}

/*
//ac 0ms ����� ̰������
//ժ�Բ���:https://www.cnblogs.com/avema/p/3921552.html
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <stack>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <iostream>
#define FFI freopen("in.txt", "r", stdin)
#define maxn 1010
#define INF 0x3f3f3f3f
#define inf 1000000000
#define mod 1000000007
#define ULL unsigned long long
#define LL long long
#define _setm(houge) memset(houge, INF, sizeof(houge))
#define _setf(houge) memset(houge, -1, sizeof(houge))
#define _clear(houge) memset(houge, 0, sizeof(houge))
using namespace std;

const int N = (1<<20)+5;
const int M = 30;

int n;
priority_queue <int> Q;

int main () {
    // FFI;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++ i) {
            int a;
            scanf("%d", &a);
            Q.push(a);
        }
        if(n == 1) {
            printf("%d\n", Q.top());
            Q.pop();
            continue;
        }
        int ans = 0;
        while(!Q.empty()) {
            int a = Q.top();
            Q.pop();
            int b = Q.top();
            Q.pop();
            if(Q.empty()) {
                ans += a+1;
                break;
            }
            ans += b;
            Q.push(a-b+1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
*/
