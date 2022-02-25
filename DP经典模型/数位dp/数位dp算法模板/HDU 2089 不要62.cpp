/*
����:ͳ������ [n,m] �в���4��62�������ж��ٸ���
n,m<=10^6.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2089
˼·:������λdp.
�ֱ�ͳ�Ƴ�0~m��0~n-1�Ĳ���4��62�ĸ��������,dp����
����ֻ��ʼ��һ��,��Ϊ�ڶ���dfs�����õ�һ��dfs���仯��dpֵ���͸��Ӷ�.
*/
//ac 0ms ���仯����
//dp[k][pre]��ʾn����λ��k��ĩβ(�������������λ�±�)�ⲿ���ܹ��ɵ����в�����ԭʼn�����ִ����㲻���֡�4����"62"�����ִ��ĸ���
//pre == 0��ʾ��һλ����6
//pre == 1��ʾ��һλ��6
//�ռ临�Ӷ�O(8*2)=16
//ʱ�临�Ӷ�O(10*8*2)=160
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 8
using namespace std;

int n,m,len,a[N],dp[N][2];

int dfs(int k,int pre,int limit){
    if(!k)
        return 1;
    if(!limit && dp[k][pre]!=-1)
        return dp[k][pre];
    int last=limit?a[k]:9,ans=0;
    for(int i=0;i<=last;i++){
        if(i == 4 || (pre == 1 && i == 2)) continue;
        ans+=dfs(k-1,i == 6,limit && i == last);
    }
    //���ֻ��ʼ��һ��dp����,�����Ҫ����!limit
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,1);
}

int main(){
    memset(dp,-1,sizeof(dp));//dp����ֻ�ó�ʼ��һ��
    while(scanf("%d%d",&n,&m) && n+m){
        len=0;
        //�������������dfs,����dpֻ��ʼ����һ��,��һ�ζ�m��dfs��dpֵ,ͬ�������ڵڶ��ζ�n-1��dfs,
        printf("%d\n",solve(m)-solve(n-1));
    }
    return 0;
}

/*
//ac 46ms ��������O(n)���� ͳ���������ǲ�����4��62�ĸ���
//ժ�Բ���:https://www.cnblogs.com/2000liuwei/p/10604834.html
#include<string.h>
#include<stdio.h>
int d[1000010];
int c[10];
int e[1000010];
int main()
{
    int a,b,ans=0;
    memset(e,0,sizeof(d));
    for(int i=1;i<1000000;i++)
    {
        int flag=0;
        memset(c,0,sizeof(c));
        c[1]=i/100000;
        c[2]=i%100000/10000;
        c[3]=i%10000/1000;
        c[4]=i%1000/100;
        c[5]=i%100/10;
        c[6]=i%10;
        for(int j=1;j<=6;j++)
        {
           if(c[j]==4)
           {
               flag=1;
           break;
    }
           if(c[j]==6&&c[j+1]==2)
           {
               flag=1;
           break;
    }
        }
        if(!flag)
        ans++;
        d[i]=ans;
    }
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        if(a==0&&b==0)break;
        printf("%d\n",d[b]-d[a-1]);
    }
    return 0;
}
*/

/*
//ac 15ms ������� û��ô��
//ժ�Բ���:https://www.cnblogs.com/wenruo/p/4725005.html
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int dp[10][10];
int d[10];

void init()
{
    dp[0][0] = 1;
    for (int i = 1; i <= 7; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = 0; k <= 9; ++k)
                if (j != 4 && !(j == 6 && k == 2))
                    dp[i][j] += dp[i - 1][k];
}

int solve(int n)
{
    int ans = 0;
    int len = 0;
    while (n) {
        ++len;
        d[len] = n % 10;
        n /= 10;
    }
    d[len + 1] = 0;
    for (int i = len; i >= 1; --i) {
        for (int j = 0; j < d[i]; ++j) {
            if (d[i + 1] != 6 || j != 2)
                ans += dp[i][j];
        }
        if (d[i] == 4 || (d[i + 1] == 6 && d[i] == 2))
            break;
    }
    return ans;
}

int main()
{
    int m, n;
    init();
    while (scanf("%d%d", &m, &n) == 2) {
        if (n == 0 && m == 0) break;
        printf("%d\n", solve(n + 1) - solve(m));
    }
    return 0;
}
*/

/*
//ac 187ms dfs���� �����ص���������,������̫С
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 8
using namespace std;

int n,m,len,a[N],dp[N][2];

int dfs(int k,int pre,int limit){
    if(!k)
        return 1;
    //if(!limit && dp[k][pre]!=-1)
        //return dp[k][pre];
    int last=limit?a[k]:9,ans=0;
    for(int i=0;i<=last;i++){
        if(i == 4 || (pre == 1 && i == 2)) continue;
        ans+=dfs(k-1,i == 6,limit && i == last);
    }
    //���ֻ��ʼ��һ��dp����,�����Ҫ����!limit
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,1);
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        len=0;
        memset(dp,-1,sizeof(dp));
        //�������������dfs,����dpֻ��ʼ����һ��,��һ�ζ�m��dfs��dpֵ,ͬ�������ڵڶ��ζ�n-1��dfs,
        printf("%d\n",solve(m)-solve(n-1));
    }
    return 0;
}
*/


