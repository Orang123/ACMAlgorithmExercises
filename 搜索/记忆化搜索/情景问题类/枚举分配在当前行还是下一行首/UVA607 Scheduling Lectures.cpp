/*
����:ժ������
����������n���Լ�ÿ�ÿε�ʱ��l,�Լ�����c��Ȼ����n����������Ҫ��ʱ��t[i]��
����1��������Ҫ���ڿ�ʱ���Խ����еĿ��⽲�꣬���ҿ����˳���ܵ�����
һ�����ⲻ�ܷ������ڿν���
����2�����õĿ�ʱ���ٵ�����£������ͬѧ�ǵĲ��������ͣ�
������ȵļ����Ǹ��ݿ�ʱ��ʣ��ʱ��t�����.
DI�ļ��㷽ʽ
1.ʣ��ʱ��tΪ0,badnessΪ0,
2.1<=t<=10,badness=-c,
3.������� badness=(t-10)^2.
n<=1000,1<=l<=500.
����:https://www.luogu.com.cn/problem/UVA607
˼·:����1����ֱ��̰��,�������ܶ�ؿ��ⰲ����ͬһ�ſ���.
����2����������1��������ٿγ�������������,ö��ÿ�ſ��ǰ�����
��ǰ������һ�ſκ��� �������°�������һ�ÿεĿ�ʼ,��������������
�����ٿγ���Ϊ0ʱ,�պ�n�����ⶼ�Ѱ�����.
dp[i][j]��ʾ��ʣ��cnt-i+1�ſΰ���j~n�Ŀ���������������badness.
��Ϊ������⸺����0���ǺϷ�״̬,����ж��ص���������Ҫ��������vis������.
*/
//ac 160ms ���仯����
//dp[i][j]��ʾ��ʣ��cnt-i+1�ſΰ���j~n�Ŀ���������������badness.
//���Ӷ�O(1000*1000)=10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,l,c,t[N],cnt,dp[N][N],vis[N][N];

int getIndex(int val){
    if(!val)
        return 0;
    else if(val>=1 && val<=10)
        return -c;
    else
        return (val-10)*(val-10);

}

int  dfs(int i,int j){
    if(vis[i][j])
        return dp[i][j];
    if(i == cnt+1){
        if(j == n+1)
            return dp[i][j]=0;
        else
            return dp[i][j]=INF;
    }
    dp[i][j]=INF;
    int sum=0;
    for(int k=j;k<=n;k++){
        sum+=t[k];
        if(sum>l)
            break;
        //���������Ǳ�Ȼ�н�� ���Բ�������INF �޽�����
        dp[i][j]=min(dp[i][j],dfs(i+1,k+1)+getIndex(l-sum));
    }
    vis[i][j]=1;
    return dp[i][j];
}

int main(){
    int sum,cas=0;
    while(scanf("%d",&n) && n){
        sum=0;
        cnt=1;
        cas++;
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&l,&c);
        for(int i=1;i<=n;i++){
            scanf("%d",&t[i]);
            sum+=t[i];
            if(sum>l){
                sum=t[i];
                cnt++;
            }
        }
        if(cas!=1)
            printf("\n");
        printf("Case %d:\n",cas);
        printf("Minimum number of lectures: %d\n",cnt);
        printf("Total dissatisfaction index: %d\n",dfs(1,1));
    }
    return 0;
}

/*
//ac 140ms ����dp
//ժ�Բ���:https://www.cnblogs.com/cyd308/p/4771624.html
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int inf=0x3f3f3f3f;

int n,l,c;
    int i,j,k;
    int cas=1,ans;
    int a[1005],sum[1005],dp[1005][1005];

int dissatisfaction(int x)
{
    if(x==0)
        return 0;
    else if(1<=x && x<=10)
        return (-c);
    else
        return (x-10)*(x-10);

}

int main()
{

    while(scanf("%d",&n)!=EOF && n!=0)
    {
        sum[0]=0;
        scanf("%d %d",&l,&c);
        for(i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            sum[i]=sum[i-1]+a[i];
        }
        for(i=0;i<=n;i++)
        {
            dp[i][0]=0;
            for(j=1;j<=n;j++)
                dp[i][j]=inf;
        }

        for(i=1;dp[i-1][n]==inf;i++)
        {
            for(j=i;j<=n && sum[j]<=i*l;j++)
            {
                for(k=j;k>=i-1;k--)
                {
                    if(dp[i-1][k]!=inf && (sum[j]-sum[k])<=l)
                        dp[i][j]=min(dp[i][j],dp[i-1][k]+dissatisfaction(l-sum[j]+sum[k]));
                    else if(sum[j]-sum[k]>l)
                        break;
                }
            }
        }

        for(i=1;i<=n;i++)
        {
            if(dp[i][n]!=inf)
            {
                ans=i;
                break;
            }
        }
        if(cas>1)
            printf("\n");
        printf("Case %d:\nMinimum number of lectures: %d\nTotal dissatisfaction index: %d\n",cas++,ans,dp[ans][n]);
    }
    return 0;
}
*/
