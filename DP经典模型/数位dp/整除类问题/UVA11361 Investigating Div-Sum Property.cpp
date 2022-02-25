/*
����:
���һ����������λ�ϵ�����֮���ܱ�3��������ô�����������Ҳ�ܱ�3������
����������У�����Ҫ����������ƹ㵽�������ϡ�
����A,B,K��������[A,B]�У��ж��ٸ����������ܱ�K���������Ҹ���λ������֮��Ҳ�ܱ�K������
A,B<2^31.K<10000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2346
˼·:��λdp.
*/
//ac 420ms ���仯����
#include<cstdio>
#include<cstring>
#define N 11
#define M 10000

int len,a[N];
int A,B,K,dp[N][100][M];

int dfs(int k,int mod1,int mod2,int limit){
    if(!k)
        return !mod1 && !mod2;
    if(!limit && dp[k][mod1][mod2]!=-1)
        return dp[k][mod1][mod2];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,(mod1+i)%K,(mod2*10+i)%K,limit && i == last);
    if(!limit)
        dp[k][mod1][mod2]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,0,1);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&A,&B,&K);
        if(K>82)//2^31�η�����������λ��Ϊ1999999999,9*9+1=82,���K>82,���λ֮��ȡģ���һ������Ϊ0
            printf("0\n");
        else{
            memset(dp,-1,sizeof(dp));
            printf("%d\n",solve(B)-solve(A-1));
        }
    }
    return 0;
}

/*
//ac 70ms ����
//ժ�Բ���:https://blog.csdn.net/keshuai19940722/article/details/26164549
//��λdp��dp[i][j][x]��ʾ��iΪ��ʱ��n����k��j��n���Լ����ǵ���λ�����ĸ���λ��
//�ϵ�����֮������k��x���������������ÿ��Ҫ�������޵��ٽ�ֵ��
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 15;
const int M = 105;

int a, b, k, n, d[N];
int dp[N][M][M];

void cat(int u) {
    n = 1;
    memset(d, 0, sizeof(d));
    while (u) {
        d[n++] = u%10;
        u /= 10;
    }

    for (int i = 1; i <= n/2; i++)
        swap(d[i], d[n-i+1]);
}

int solve (int u) {
    if (u == 0)
        return 1;

    cat(u);
    memset(dp, 0, sizeof(dp));
    int p = 0, q = 0;

    for (int i = 1; i <= n; i++) {

        for (int j = 0; j <= k; j++) {
            for (int t = 0; t <= k; t++) {

                for (int x = 0; x < 10; x++)
                    dp[i][(j*10+x)%k][(t+x)%k] += dp[i-1][j][t];
            }
        }

        for (int j = 0; j < d[i]; j++)
            dp[i][(p*10+j)%k][(q + j)%k]++;

        p = (p*10+d[i])%k;
        q = (q+d[i])%k;
    }

    if (p == 0 && q == 0)
        dp[n][0][0]++;
    return dp[n][0][0];
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d%d", &a, &b, &k);
        if (k > 100)
            printf("0\n");
        else
            printf("%d\n", solve(b) - solve(a-1));
    }
    return 0;
}
*/
