#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
#define M 1000100
using namespace std;
//ac 15ms 01�����ֳ�2�Ѿ��������,��ֵ�Ͳ�ֵ��С
/*
����:n��ʯͷ,ÿ��ʯͷ������val[i],����Ҫ���n��ʯͷ
�ֳ�2��,Ҫ��2��ʯͷ����֮�͵Ĳ�ֵ��С,��������С��ֵ.
����:https://vjudge.net/problem/URAL-1005
https://acm.timus.ru/problem.aspx?space=1&num=1005
˼·:��01����������������ʯͷ����֮�͵�һ��,�������
�������ص��������,ʣ�µľ�����һ��(�ϴ��),�����.
*/
int n,val[N],dp[M],sum;

int main(){
    memset(dp,0,sizeof(dp));//�����ܶ��װ�뱳��
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
        sum+=val[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=sum/2;j>=val[i];j--)
            dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
    }
    printf("%d",sum-2*dp[sum/2]);
    return 0;
}

/*
//ac 15ms ����ö������
//��Ϊn<=20,����2^20=10^6 1s�ڻ���,һ��n����30,2^n�ͱȽϱ�ը��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
#define M 1000100
using namespace std;

int n,val[N],dp[M],sum,ans;

void dfs(int k,int res){
    if(res>sum/2) return;
    if(res>ans)
        ans=res;
    if(k == n+1) return;
    dfs(k+1,res+val[k]);
    dfs(k+1,res);
}

int main(){
    memset(dp,0,sizeof(dp));//�����ܶ��װ�뱳��
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
        sum+=val[i];
    }
    dfs(1,0);
    printf("%d",sum-2*ans);
    return 0;
}
*/
