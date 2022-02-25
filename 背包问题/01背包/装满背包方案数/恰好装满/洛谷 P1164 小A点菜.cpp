#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;
//ac 22ms 01���� ǡ��װ������������
/*
����:n����Ʒ,ÿ����Ʒ�����Ϊw[i],��������Ϊv�ı���,
��ǡ��װ�������ķ�����.
����:https://www.luogu.com.cn/problem/P1164
˼·:01����,���ǳ���״̬dp[0]=1,����״̬Ϊ0.
*/
int n,v,w[N],dp[M];

int main(){
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=w[i];j--)
            dp[j]+=dp[j-w[i]];
    }
    printf("%d",dp[v]);
    return 0;
}

/*
//ac 48ms ��ά����ʵ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,v,w[N],dp[N][M];

int main(){
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=v;j++){
            if(j>=w[i])
                dp[i][j]=dp[i-1][j]+dp[i-1][j-w[i]];
            else
                dp[i][j]=dp[i-1][j];
		}
    }
    printf("%d",dp[n][v]);
    return 0;
}
*/

/*
//��11������ TLE 90�� ����ö������
//���Ҳ���ؼ�֦ ��֦��Ҳ�ᳬʱ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,v,w[N],dp[M],ans;

void dfs(int k,int sum){
    if(sum>v) return;//����v ����ǡ��װ��
    if(sum == v){//ǡ��װ�� ������+1
        ans++;
        return;//�����ۼ� ���ܴ��ڱ����ݻ�v
    }
    if(k == n+1)//��Ʒ���ö�ٵ������һ�� ����
        return;
    dfs(k+1,sum+w[k]);
    dfs(k+1,sum);
}

int main(){
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    sort(w+1,w+1+n);
    ans=0;
    dfs(1,0);
    printf("%d",ans);
    return 0;
}
*/

/*
����11:
input
36 32
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 4 8 16

output
2147483647
*/
