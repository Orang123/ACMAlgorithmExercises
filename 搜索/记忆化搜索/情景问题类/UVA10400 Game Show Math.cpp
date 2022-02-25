/*
����:
����p����ֵ���������������ֵ֮�����+��- ��*  ��/�����㣬
Ҫ���ҵ�һ����ʽ����ʹ����ʽ��ֵ����Ŀ��ֵ�����ÿ��������
�����ȼ�,��Զ���մ������ҵ�˳��һ�ν�ϼ���.
Ҫ���ڽ�Ϲ����м���Ľ��������[-32000,32000]��Χ��,����Ӧ��
����ʱ,������������Ӧ��.
0<n<=100.
����:https://www.luogu.com.cn/problem/UVA10400
˼·:��������ö��ÿ������֮�����������(+��-��*��/),ֻ����Ϊ
n<=100,ֱ�Ӽ����TLE.���Է���������Ĺ����ж���ǰk-1�����õ���
������Ϊsum,���״̬���ܻ��ظ�������,���֮ǰ���ܵõ�Ŀ��ֵ,
�´��ٴ�������ʱ�Ͳ����ظ�����.
��˼��仯����.
dp[i][j]=1��ʾǰi-1�����õ�������Ϊj ���״̬���޷��õ�Ŀ��ֵ��.
��ʼ״̬����Ϊ-1,��Ϊ�����±겻��Ϊ��,��������ͳһ�������ĸ�����Χ
32000.����dp����Ŀռ临�Ӷ�Ϊ100*64000=6.4*10^6
*/
//ac 80ms ���仯����
//dp[i][j]=1��ʾǰi-1�����õ�������Ϊj ���״̬���޷��õ�Ŀ��ֵ��.
//���Ӷ�O(100*64000)=6.4*10^6
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
#define M 65000
#define maxn 32000
using namespace std;

int p,a[N],res,cnt,dp[N][M];
char ans[210];

int check(int val){
    return val>=-maxn && val<=maxn;
}

int dfs(int k,int sum){
    if(dp[k][sum+maxn]!=-1)
        return 0;
    dp[k][sum+maxn]=1;
    if(k == p+1){
        if(sum == res)
            return 1;
        else
            return 0;
    }
    ans[cnt++]='+';
    if(check(sum+a[k]) && dfs(k+1,sum+a[k]))
        return 1;
    cnt--;
    ans[cnt++]='-';
    if(check(sum-a[k]) && dfs(k+1,sum-a[k]))
        return 1;
    cnt--;
    ans[cnt++]='*';
    if(check(sum*a[k]) && dfs(k+1,sum*a[k]))
        return 1;
    cnt--;
    ans[cnt++]='/';
    if(sum%a[k] == 0 && dfs(k+1,sum/a[k]))//������ΪԽ��ԽС,ֻ���ж��Ƿ����� �����ж��Ƿ񳬹�[-32000,32000]�����Χ
        return 1;
    cnt--;
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(dp,-1,sizeof(dp));
        scanf("%d",&p);
        for(int i=1;i<=p;i++)
            scanf("%d",&a[i]);
        scanf("%d",&res);
        if(dfs(2,a[1])){
            for(int i=1,j=0;i<=p;i++,j++){
                printf("%d",a[i]);
                if(i!=p)
                    printf("%c",ans[j]);
                else
                    printf("=");
            }
            printf("%d\n",res);
        }
        else
            printf("NO EXPRESSION\n");
    }
    return 0;
}
