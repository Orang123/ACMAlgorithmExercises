#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11000
#define M 100
using namespace std;
//ac 547ms 4284K ������ǰi-1����״̬ȥ����ǰi����״̬
/*
����:n����,����������a[i],a[i+1]֮��������ֻ����'+'��'-',��
�Ƿ����һ������˳��ʹ��n�������������ܱ�k����,n�����ļ���
˳��ֻ���Ǹ�����˳��.
����:http://poj.org/problem?id=1745
˼·:n<=10^4,��Ȼ����ö��������ŵĿ������(O(2^(n-1)))��Ȼ��TLE,���
���Կ���״̬ת��dp,��֪:(a+b)%mod=(a%mod+b%mod)%mod.
���Կ��ǲ��ñ��������ǰi-1����������ģk���ȥ����ǰi����������ģk
���,��ô���ڵ�i��������2��ת��,һ���Ƕ��ڼӷ�,һ���Ƕ��ڼ���.
��dp[i][j]��ʾǰi������������kȡģ�����Ƿ�Ϊj,dp[i][j]=1��ʾΪ��,
dp[i][j]=0��ʾΪ��.��ô���dp[i-1][j]=1,��Ӧ�ľͿ��Ը���ǰi-1������
����ȡģ������i����������ȡģ�õ�ǰi��������ȡģ�Ŀ���״̬,��
dp[i][(j+a[i]%k)%k]=1,��Ϊj�Ѿ���ȡģ������������Բ���ȡģ,
�������ʽֻ�����a[i]Ϊ����,(j+a[i]%k)ҲΪ���������,���Ҫȡģ����
Ϊ��������Ҫ��ȡģ�õ��ĸ����ټ���k,����Ϊ��ͳһ�������Ľ��������,ͳһ
���ڼ���k�Ľ�����ٶ�kȡģ,��:
a[i]=(a[i]%k+k)%k;
dp[i][((j+a[i])%k+k)%k]=1;
dp[i][((j-a[i])%k+k)%k]=1;
�����ù��������Ż���һά,��Ϊ
dp[cal(j+a[i])]=1;
dp[cal(j-a[i])]=1;
������+��-,����j�����ǽ���,dp[j]���ܱ�֤��ǰi-1������״̬
*/
int n,k,a[N],dp[N][M];

int cal(int x){
    return (x%k+k)%k;
}

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i]=cal(a[i]);
    }
    dp[1][a[1]]=1;
    for(int i=2;i<=n;i++){
        //��Ϊ�Ƕ�άdp,�ܹ���֤ǰi-1��״̬��Զ��û�к͵�i��������Ľ��,�������j ���� �����ǿ��Ե�
        for(int j=0;j<k;j++){
            if(dp[i-1][j]){//ǰi-1��������Ԥ���kȡģ ����Ϊj,������Ϊj�Ļ����Ϻ͵�i������ȡģ���� �ɵõ�ǰi����ȡģ����������״̬
                //+/- 2�����ܵ�״̬
                dp[i][cal(j+a[i])]=1;
                dp[i][cal(j-a[i])]=1;
            }
        }
    }
    if(dp[n][0])
        printf("Divisible");
    else
        printf("Not divisible");
    return 0;
}

/*
//ac 438ms 4672K ���������ǰ���ǰi-1��״̬��ȥ���Ƶ� �����01������˼ά������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11000
#define M 100
using namespace std;

int n,k,a[N],dp[N][M];

int cal(int x){
    return (x%k+k)%k;
}

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            //����ȡģ���������,����ǰi���������ȡģ������j����,
            //��ô((j+/-a[i])%k+k)%k��ǰi-1���������������϶�Ҳ�ǳ�����.
            //����ͱ�����˼ά�Ѿ��ܽӽ���
            dp[i][j]=dp[i-1][cal(j+a[i])] || dp[i-1][cal(j-a[i])];
        }
    }
    if(dp[n][0])
        printf("Divisible");
    else
        printf("Not divisible");
    return 0;
}
*/

/*
//ac 454ms 640K ���������Ż��ռ�dp[2][Max]
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int Max = 205;
const int temp = 100;



int main(){
    int n, k, i, j, num, val;
    bool dp[2][Max];
   while(scanf("%d %d", &n, &k) != EOF){
       memset(dp, false, sizeof(dp));
       scanf("%d", &num);
       dp[1][num % k + temp] = true;
       for(i = 2; i <= n; i ++){
           scanf("%d", &num);
           for(j = 0; j < Max; j ++)
               dp[i%2][j] = false;
           for(j = 0; j < Max; j ++)
               if(dp[1 - i%2][j]){
                   val = j - temp + num;
                  val %= k;
                  dp[i%2][val + temp] = true;
                   val = j - temp - num;
                   val %= k;
                   dp[i%2][val + temp] = true;
                }
        }
        if(dp[n%2][temp]) cout << "Divisible" << endl;
       else cout << "Not divisible" << endl;
    }
    return 0;
}
*/

/*
//TLE ����ö������ ʱ�临�Ӷ�O(2^(n-1)) n����֮����n-1�������(+/-)
//ÿ�������ֻ��2�ֿ��� �ӷ������,n�����Ǳ��޶�ȡ��,����Ҳ�޷���֦
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11000
#define M 100
using namespace std;

int n,k,a[N],dp[N][M],flag;

int cal(int x){
    return (x%k+k)%k;
}

int dfs(int i,int sum){
    if(i == n+1){
        if(sum%k == 0)//ֻҪn����������ȡģk����Ϊ0 ���˳�dfs��������
            return 1;
        else
            return 0;
    }
    if(dfs(i+1,sum+a[i])) return 1;
    if(dfs(i+1,sum-a[i])) return 1;
    return 0;//������һ���� ��һ�������
}

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    if(dfs(2,a[1]))//ֻ��ö��n-1���м�������
        printf("Divisible");
    else
        printf("Not divisible");
    return 0;
}
*/

/*
//���Ǻ��������ֱ�Ӷ�a[i]��ֵ����ֵȡ����ȡģ���� ������ѧ���ж�Ӧ֤����
//�ο�����:https://blog.csdn.net/Li_O_Liu/article/details/105443987
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int N,K,i,j,t;
    int num[10010];
    bool dp[10010][110];
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&N,&K);
    for(i=0;i<N;i++){
        scanf("%d",&t);
        num[i]=abs(t)%K;
    }
    dp[0][num[0]]=1;
    for(i=1;i<N;i++)
    {
        for(j=0;j<K;j++)//��������0~K-1�����
        {
            if(dp[i-1][j])//��һ�ִ�������j�����
            {
                t=abs(j+num[i])%K;
                dp[i][t]=1;
                t=abs(j-num[i])%K;
                dp[i][t]=1;
            }
        }
    }
    if(dp[N-1][0])
        printf("Divisible\n");
    else
        printf("Not divisible\n");
    return 0;
}
*/
