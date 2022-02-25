/*
����:ժ������
����n*n�ľ���a[i][j]�����i�����˺͵�j��Ů��֮�������ȣ�
����Ůһһ��Ժ����������֮�͡�
n<=16.
����:http://lightoj.com/volume_showproblem.php?problem=1011
˼·:ʵ������������������İ˻ʺ�,��ȡ����֮���ƥ��,ȡn��
��ͬ�в�ͬ�е�λ��,Ҫ��Ȩֵ�����.�������˻ʺ���������⸴�Ӷ����ɴ�16!.
����1:KM�㷨��ȡ����ƥ��,�к���ƥ��,���Ӷ�O(n^3)=16^3=4096
����2:��Ϊn<=16,��С����״ѹ.�����ڰ˻ʺ������������϶Ի�δѡȡ������һ��
״̬ѹ��,dp[sta]��ʾΪѡȡ�е�״̬Ϊstaʱ�ܻ�ô���������,������ö����ʱ
�����ص�������Ϳɳ���ʱ�䷵�ؽ��,���������ʱ�临�Ӷ�,ʱ�临�Ӷȿɴ�O(1<<16)=65536
*/
//ac 182ms ���仯����+״ѹ
//dp[sta]��ʾΪѡȡ�е�״̬Ϊstaʱ�ܻ�ô���������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 16
using namespace std;

int n,a[N][N],dp[1<<16];

int dfs(int sta,int row){
    int &res=dp[sta];
    if(res)
        return res;
    if(!sta)//�����ж�ѡȡ��
        return 0;
    for(int i=0;i<n;i++){
        if(sta & 1<<i)//��i�л�δѡȡ
            res=max(res,dfs(sta ^ 1<<i,row+1)+a[row][i]);//row+1 �ж���һ��
    }
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                scanf("%d",&a[i][j]);
        }
        printf("Case %d: %d\n",i,dfs((1<<n)-1,0));//��ʼδѡȡ������n��
    }
    return 0;
}

/*
//TLE �˻ʺ�ģ�Ⱪ������
//ժ�Բ���:https://blog.csdn.net/qq_34374664/article/details/54586529
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 20;
int dp[maxn][maxn], book[maxn], max1, n;
void dfs(int i, int ans)
{
    if(i == n+1)
    {
        if(ans > max1) max1 = ans;
        return;
    }
    for(int j = 1; j <= n; j++)
    {
        if(book[j])
            continue;
        book[j] = 1;
        ans += dp[i][j];
        dfs(i+1, ans);
        book[j] = 0;
        ans -= dp[i][j];
    }
}
int main()
{
    int t, ca = 1;
    scanf("%d", &t);
    while(t--)
    {
        memset(book, 0, sizeof(book));
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &dp[i][j]);
        max1 = -1;
        dfs(1,0);
        printf("Case %d: %d\n",ca++, max1);

    }
    return 0;
}
*/

/*
//ac 567ms ����dp
//ժ�Բ���:https://www.cnblogs.com/wangzhili/p/3950255.html
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 16;
int dp[MAXN][1 << MAXN], mat[MAXN][MAXN];
int main(){
    int t, n, CASE(0);
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i = 0;i < n;i ++){
            for(int j = 0;j < n;j ++) scanf("%d", &mat[i][j]);
        }
        int len = (1 << n);
        memset(dp, 0, sizeof dp);
        for(int i = 0;i  < n; i ++) dp[0][1 << i] = mat[0][i];
        for(int i = 1;i < n;i ++){
            for(int j = 0;j < n;j ++){
                for(int k = 0;k < len;k ++){
                    if(!dp[i-1][k] || (1 << j) & k) continue;
                    dp[i][k|(1 << j)] = max(dp[i][k|(1 << j)], dp[i-1][k]+mat[i][j]);
                }
            }
        }
        printf("Case %d: %d\n", ++CASE, dp[n-1][len-1]);
    }
    return 0;
}
*/
