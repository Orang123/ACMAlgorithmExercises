/*
����:��һ�����ҽ���1��,2��,3��Ӳ��,��ǮN�һ���Ӳ���кܶ��ֶҷ�.
���������������ж����ֶҷ�.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1284
˼·:ÿ��Ӳ�ҿ��Զһ����,�������ȫ��������,��Ϊ��ǡ��װ����
������,����״̬ת�Ʒ���dp[j]+=dp[j-val[i]],dp[0]=1;
*/
#include<bits/stdc++.h>
#define N 32780
using namespace std;
int v,val[4]={0,1,2,3},dp[N];
int main(){
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    //��ö����Ʒ����,��ö�ٱ�������,ֻ�������ͬ��ϵĸ���,���������ͬ��ϲ�ͬ˳��ĸ���
    for(int i=1;i<=3;i++)
        for(int j=val[i];j<N;j++)
            dp[j]+=dp[j-val[i]];
    /*
    //��ö�ٱ������� ��ö����Ʒ����,�������ܿ�������˳��ͬ��������ϵĸ���
    //����leetcode 377. ����ܺ� �� https://leetcode-cn.com/problems/combination-sum-iv/
    for(int j=0;j<=N;j++){
        for(int i=1;i<=3;i++){
            if(j>=val[i])
                dp[j]+=dp[j-val[i]];
        }
    }
    */
    while(scanf("%d",&v)!=EOF)
        printf("%d\n",dp[v]);
    return 0;
}

/*
//ac 109ms һά����ʵ����ȫ����ͳ�Ʒ�����
#include<bits/stdc++.h>
#define N 32780
using namespace std;
int v,val[4]={0,1,2,3},dp[N];
int main(){
    while(scanf("%d",&v)!=EOF){
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        for(int i=1;i<=3;i++)
            for(int j=val[i];j<=v;j++)
                dp[j]+=dp[j-val[i]];
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 234ms ��ά����ʵ��
#include<bits/stdc++.h>
#define N 4
#define M 32780
using namespace std;
int v,val[N]={0,1,2,3},dp[N][M];
int main(){
    while(scanf("%d",&v)!=EOF){
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=1;i<=3;i++){
            for(int j=0;j<=v;j++){
                if(j>=val[i])//ע����������ǰi����Ʒ�������ۼӵ�i����Ʒ ��:dp[i][j-val[i]]
                    dp[i][j]=dp[i-1][j]+dp[i][j-val[i]];
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%d\n",dp[3][v]);
    }
    return 0;
}
*/

/*
��������ö��,��������Ǵ��,��Щ�����������ظ���.
void dfs(int sum){
    if(sum>v)
        return;
    if(sum == v)
        ans++;
    ans[sum]++;
    dfs(sum+1);
    dfs(sum+2);
    dfs(sum+3);
}
*/

/*
bfsö��״̬����ת��,Ҳ�����ĳЩ�ظ��ķ���,���.
*/

/*
//ac 390ms ĸ��������
//ժ�Բ���:https://www.cnblogs.com/Taskr212/p/9561041.html
#include <bits/stdc++.h>
using namespace std;
const int maxn = 32769;
int n,ans[maxn],tans[maxn];
void init()
{
    for(int i = 0; i < maxn; ++i)
    {
        ans[i] = 1;
        tans[i] = 0;
    }
    for(int i = 2; i <= 3; ++i)
    {
        for(int j = 0; j < maxn; ++j)
            for(int k = 0; j+k < maxn; k+=i)
                tans[j+k]+=ans[j];
        for(int j = 0; j < maxn; ++j)
        {
            ans[j] = tans[j];
            tans[j] = 0;
        }
    }
}
int main()
{
    init();
    while(~scanf("%d",&n))
        printf("%d\n",ans[n]);
    return 0;
}
*/
